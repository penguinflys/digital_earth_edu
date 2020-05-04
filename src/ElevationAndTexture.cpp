#include "ElevationAndTexture.h"
#include <gdal/gdal_priv.h>
// #include "DataIO.h"
#include <iostream>
#include <limits>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


namespace DE{

cv::Mat DEMModel::PaddingBorder(const cv::Mat& dem){
    int cols = dem.cols;
    int rows = dem.rows;
    // opencv copy function requires datatype CV_8U. not useful
    cv::Mat dem_with_boader(rows+2,cols+2,CV_16S,cv::Scalar(std::numeric_limits<int16_t>::min()));
    // copy dem to dem with padding border
    for (int16_t i = 1; i< cols+1; ++i)
        for(int16_t j = 1; j< rows+1; ++j)
            dem_with_boader.at<int16_t>(j,i) = dem.at<int16_t>(j-1,i-1);
    // cols boader.
    for (int16_t i = 0; i < cols; i++)
    {
        dem_with_boader.at<int16_t>(0,i+1) = dem.at<int16_t>(rows-1,i);
        dem_with_boader.at<int16_t>(rows+1,i+1) = dem.at<int16_t>(0,i);
    }
    // rows boader. 
    for (int16_t j = 0; j < rows; j++)
    {
        dem_with_boader.at<int16_t>(j+1,0) = dem.at<int16_t>(j,cols-1);
        dem_with_boader.at<int16_t>(j+1,cols+1) = dem.at<int16_t>(j,0);
    }
    // four corners
    dem_with_boader.at<int16_t>(0,0) = dem.at<int16_t>(0,0);
    dem_with_boader.at<int16_t>(rows+1,0) = dem.at<int16_t>(rows-1,0);
    dem_with_boader.at<int16_t>(0,cols+1) = dem.at<int16_t>(0,cols-1);
    dem_with_boader.at<int16_t>(rows+1,cols+1) = dem.at<int16_t>(rows-1,cols-1);

    return dem_with_boader;
    
}
/*
 * Interpolate Colors
*/
template <typename DATATYPE, int N>
cv::Vec<DATATYPE,N> DEMModel::LERP( cv::Vec<DATATYPE,N> const& minColor,
                          cv::Vec<DATATYPE,N> const& maxColor,
                          double const& t ){
    cv::Vec<DATATYPE,N> output;
    for( int i=0; i<N; i++ ){
        output[i] = (uchar)(((1-t)*minColor[i]) + (t * maxColor[i]));
    }
    return output;
}
/*
 * Compute the dem color, opengl automatically interpolate them as a trainglar
*/
cv::Vec3b DEMModel::GetDEMCOlor( const double& elevation ){
    // if the elevation is below the minimum, return the minimum
    if( elevation < color_range[0].second ){
        return color_range[0].first;
    }
    // if the elevation is above the maximum, return the maximum
    if( elevation > color_range.back().second ){
        return color_range.back().first;
    }
    // otherwise, find the proper starting index
    int idx=0;
    double t = 0;
    for( int x=0; x<(int)(color_range.size()-1); x++ ){
        // if the current elevation is below the next item, then use the current
        // two colors as our range
        if( elevation < color_range[x+1].second ){
            idx=x;
            t = (color_range[x+1].second - elevation)/
                (color_range[x+1].second - color_range[x].second);
            break;
        }
    }
    // interpolate the color
    return LERP( color_range[idx].first, color_range[idx+1].first, t);
}
std::pair<int,int> DEMModel::GetMinMax(GDALRasterBand* const poBand){
    int bGotMin, bGotMax;
    double adfMinMax[2];
    adfMinMax[0] = poBand->GetMinimum( &bGotMin );
    adfMinMax[1] = poBand->GetMaximum( &bGotMax );
    if( ! (bGotMin && bGotMax) )
        GDALComputeRasterMinMax((GDALRasterBandH)poBand, FALSE, adfMinMax);
    printf( "Min=%.3f, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
    return std::make_pair<int,int>(adfMinMax[0],adfMinMax[1]);
}
cv::Point2d DEMModel::Pixel2World(const cv::Point2d& pixel){
    //Xgeo = l = langtitude
    //Ygeo = b = lantitude
    double Xgeo = GT(0) + pixel.x*GT(1) + pixel.y*GT(2);
    double Ygeo = GT(3) + pixel.x*GT(4) + pixel.y*GT(5);
    return cv::Point2d(Xgeo,Ygeo);//Point2d : <l,b>
}
cv::Point2d DEMModel::World2Pixel(const cv::Point2d& coordinate, const cv::Size2i& dem_size){
    // relate this to the dem points 
    // ASSUMING THAT DEM DATA IS ORTHORECTIFIED
    // coordiante.x = l = longtitude in range [-180, 180]
    // coordiante.y = b = latatitude in range [-90, 90]
    if(coordinate.x > 180 or coordinate.x < -180)   {std::cerr<< "Value Error Coordinate B: X"<<std::endl;}
    if(coordinate.y > 90 or coordinate.y < -90)     {std::cerr<< "Value Error Coordinate L: Y"<<std::endl;}
    //x = l, y = b;

    
    double demRatioX = ((coordinate.x - dem_tl_lb.x)/(dem_tr_lb.x - dem_tl_lb.x));
    double demRatioY = ((coordinate.y - dem_tl_lb.y)/(dem_bl_lb.y - dem_tl_lb.y));
    if (demRatioX > 1. or demRatioY > 1. or demRatioX < .0  or demRatioY < .0){
        std::cerr<< "Value Wrong "<<std::endl;
        throw std::invalid_argument("Invalid Ratio of Points");
    }

    cv::Point2d output;
    output.x = demRatioX * dem_size.width;
    output.y = demRatioY * dem_size.height;

    return output;

}
// Row-colum problem https://stackoverflow.com/questions/25642532/opencv-pointx-y-represent-column-row-or-row-column
double DEMModel::BLERP(const cv::Mat& mat_extented, const cv::Point2i& lb, const cv::Point2i& lt, const cv::Point2i& rb, const cv::Point2i& rt, cv::Point2d pix){
    // allert! 
    // mat_extented is the dem mat file with border padding.
    // lb, lt rb rt are all 
    if(lb.y-lt.y != 1 or rt.x-lt.x !=1 or rb.x - lt.x != 1 or rb.y - lt.y != 1){
        std::cerr<<"lb:"<<lb<<"\nrb:"<<rb<<"\nlt:"<<lt<<"\nrt:"<<rt<<std::endl;
        throw std::invalid_argument("Invalid Coorner Points");
    }
    // max left -> 2159    max right -> 4319
    // std::cout<<"mat<0,0>:"<<mat_extented.at<int16_t>(0,0)<<std::endl;
    // std::cout<<"mat<1,0>:"<<mat_extented.at<int16_t>(2,0)<<std::endl;
    // std::cout<<"mat<0,1>:"<<mat_extented.at<int16_t>(0,2)<<std::endl;
    // std::cout<<"mat<lb>:"<<mat_extented.at<int16_t>(lb)<<std::endl;
    // std::cout<<"mat<lt>:"<<mat_extented.at<int16_t>(lt)<<std::endl;
    // cv::Point2i pt = cv::Point2i(4321,10);
    
    double v1 = LERP(mat_extented.at<int16_t>(lt),mat_extented.at<int16_t>(lb),(pix.y-lt.y)/(lb.y-lt.y));
    double v2 = LERP(mat_extented.at<int16_t>(rt),mat_extented.at<int16_t>(rb),(pix.y-rt.y)/(rb.y-rt.y));
    return LERP(v1,v2,(pix.x-lb.x)/(rb.x-lb.x));
}
double DEMModel::LERP(const int& v1, const int& v2, const double& t){
    // v1 has smaller coordiante value, t is distance to v1
    return (1-t)*v1 + t*v2;
}
cv::Point2d DEMModel::LERP( cv::Point2d const& p1, cv::Point2d const& p2, const double& t ){
    return cv::Point2d( ((1-t)*p1.x) + (t*p2.x),
                        ((1-t)*p1.y) + (t*p2.y));
}

double DEMModel::GetHeight(const double& l, const double& b, const double& scale){
    //  l langtitude [-180,180], b latitude [-90,90]
    if (b > 90.1 or b < -90.1){std::cout<<"Value Error"<<std::endl;throw std::invalid_argument("Value Error latitude: b");}
    if (l > 180.1 or l < -180.1){std::cout<<"Value Error"<<std::endl;throw std::invalid_argument("Value Error latitude: l");}
    cv::Point2d pt(l,b);
    cv::Size2i sz(poDEMBand->GetXSize(),poDEMBand->GetYSize());//width = range of langtitude, height = range of latitude
    cv::Point2d pix = World2Pixel(pt,sz);
    pix += cv::Point2d(1.0,1.0);
    double fix = 0.0000001; //ensure the correctness of test for int-like double like (180.0+fix,0+fix)-> (180+fix,0+fix)
    // opencv coordiante system:
    // 0/0---X-------->
    //  |
    //  |   lt------rt
    //  Y   |       |
    //  |   |  +pix |
    //  |   lb------rb
    //  v
    cv::Point2i lt(floor(pix.x + fix),floor(pix.y + fix));
    cv::Point2i lb(floor(pix.x + fix),ceil(pix.y + fix));
    cv::Point2i rt(ceil(pix.x + fix),floor(pix.y + fix));
    cv::Point2i rb(ceil(pix.x + fix),ceil(pix.y + fix));
    // std::cout<<"interpolated pix:"<<pix<<"\n"<<"4 corners:[x,y]\n"<<lt<<"........"<<rt<<"\n"<<lb<<"........"<<rb<<std::endl;
    // validpixel(this->dem_borders,lt);
    // validpixel(this->dem_borders,rt);
    // validpixel(this->dem_borders,lb);
    // validpixel(this->dem_borders,rb);
    double value = BLERP(dem_extented, lb, lt, rb, rt, pix);
    return value*scale;
}
cv::Point2i DEMModel::validpixel(const cv::Mat& dem, cv::Point2i& pix){
    // warning opencv has no ability to check whether a pixel is valid for accessing image value.
    // for example, if a image has size(rows = 100, cols = 100)
    // image<type>.at(101 or 200 ,10) is aceessible, but only (100,100) not accessible
    try
    {
        int16_t v = dem.at<int16_t>(pix);
        std::cout<<v<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    if (pix.x < dem.rows and pix.y < dem.cols){return pix;}
    return cv::Point2i(-1,-1);
}
cv::Point2d TextureModel::Pixel2World(const cv::Point2d& pixel){
    //Xgeo = l = langtitude
    //Ygeo = b = lantitude
    double Xgeo = GT(0) + pixel.x*GT(1) + pixel.y*GT(2);
    double Ygeo = GT(3) + pixel.x*GT(4) + pixel.y*GT(5);
    return cv::Point2d(Xgeo,Ygeo);//Point2d : <l,b>
}
cv::Point2d TextureModel::World2Pixel(const cv::Point2d& coordinate, const cv::Size2i& dem_size){
    // relate this to the dem points 
    // ASSUMING THAT DEM DATA IS ORTHORECTIFIED
    // coordiante.x = l = longtitude in range [-180, 180]
    // coordiante.y = b = latatitude in range [-90, 90]
    if(coordinate.x > 180 or coordinate.x < -180)   {std::cerr<< "Value Error Coordinate B: X"<<std::endl;}
    if(coordinate.y > 90 or coordinate.y < -90)     {std::cerr<< "Value Error Coordinate L: Y"<<std::endl;}
    //x = l, y = b;

    // static cast problem.
    double texRatioX = ((coordinate.x - tex_tl_lb.x)/(tex_tr_lb.x - tex_tl_lb.x));
    double texRatioY = ((coordinate.y - tex_tl_lb.y)/(tex_bl_lb.y - tex_tl_lb.y));
    if (texRatioX > 1. or texRatioY > 1. or texRatioX < .0  or texRatioY < .0){
        std::cerr<< "Value Wrong "<<std::endl;
        throw std::invalid_argument("Ratio of Points out of range");
    }

    cv::Point2d output;
    output.x = texRatioX * dem_size.width;
    output.y = texRatioY * dem_size.height;

    return output;

}
std::pair<double,double> TextureModel::GetTextureCoordinatesMN(const double& l,const double& b){
    cv::Point2d pt = World2Pixel(cv::Point2d(l,b),tex.size());
    double m = pt.x / tex.cols;
    double n = pt.y / tex.rows;
    if (m > 1 or n > 1 or m < 0 or n < 0){
        std:: cout<< "Texture coordinates wrong."; 
        throw std::invalid_argument(" texture coordinates Out of range");}
    return std::pair<double,double>(m,n);
}

// fixme damm get wrong somehow.
std::vector<cv::Mat> showHistogram(const cv::Mat& src, int nbands, int nhistSize, float lowbound, float upbound, bool showWindow = false){
    if( src.empty() )
    {
        std::cerr<<"no src! please check cv::Mat Variable"<<std::endl;
        throw std::bad_alloc();
    }
    std::vector<cv::Mat> bands_planes;
    std::vector<cv::Mat> bands_hists(nbands);
    cv::split(src,bands_planes);
    float range[] = {lowbound,upbound};
    const float* histRange = {range};
    bool uniform = true, accumulate = false;
    for( int i = 0; i < nbands; ++i){
        cv::calcHist(&bands_planes[i],1,0,cv::Mat(),bands_hists[i],1,&nhistSize,&histRange,uniform,accumulate);
    }
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/nhistSize );
    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );
    for( int i = 0; i < nbands; ++i){
        cv::normalize(bands_hists[i], bands_hists[i], 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

        cv::Scalar color(std::rand()%255, std::rand()%255, std::rand()%255);
        // std::cout<<color<<std::endl;
        for(int j = 1; j< nhistSize; ++j){
            cv::line( histImage, cv::Point( bin_w*(j-1), hist_h - cvRound(bands_hists[i].at<float>(j-1)) ),
                cv::Point( bin_w*(j), hist_h - cvRound(bands_hists[i].at<float>(j)) ),
                color, 2, 8, 0  );
        }
    }
    if(showWindow){
        cv::namedWindow("Source image", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
        cv::resizeWindow("Source image",800,600);
        cv::imshow("Source image", src);
        cv::namedWindow("calcHist Demo", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
        cv::resizeWindow("calcHist Demo",800,600);
        cv::imshow("calcHist Demo", histImage );
        cv::waitKey(0);
    }

    return bands_hists;
}

GDALDataset* LoadRasterToDataset(std::string strRasterPath){
    // GDALAllRegister();
    GDALRegister_GTiff();
    GDALDataset* poDataset = (GDALDataset*)GDALOpen(strRasterPath.data(), GA_ReadOnly);
    if (poDataset == nullptr){
        std::cerr<<"Failed to load Dataset"<<std::endl;
        throw std::bad_alloc();
    }
    // TODO Support more than one band.
    if (poDataset->GetRasterCount() != 1){
        std::cerr<< "this dataset has more than one band, please give explicite Function to convert to double format"<<std::endl;
    }
    // return dynamic_cast<RasterImageDataset*>(poDataset);
    return poDataset;
}



void setImageData(unsigned char *imageArray, int size){
    for (int i = 0; i < size; i++){
        imageArray[i] = (unsigned char)(rand() / (RAND_MAX / 255.0));
    }
}

} // namespace DE
