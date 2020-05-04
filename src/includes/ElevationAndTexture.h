#ifndef DE_ELEVATIONANDTEXTURE_H
#define DE_ELEVATIONANDTEXTURE_H

#include <string>
// #include "DataIO.h"
#include <gdal/gdal_priv.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "gdal2cv.h"

namespace DE{

// FIXME dynamic_cast to RasterImage fails, find why. 
GDALDataset* LoadRasterToDataset(std::string strRasterPath);
void setImageData(unsigned char *imageArray, int size);
std::vector<cv::Mat> showHistogram(const cv::Mat& , int, int , float , float, bool);


class DEMModel{

public:
    // range of the heat map colors
    std::vector<std::pair<cv::Vec3b,double> > color_range;
    // define the corner points
    // Note that GDAL library can natively determine this
    // cv::Point2f a(-0.3f,0.5f);
    cv::Point2i dem_tl_lb;// top left corner storing (l,b)/ langtitude,latitude;
    cv::Point2i dem_bl_lb;// bottom left corner storing (l,b)/ langtitude,latitude;
    cv::Point2i dem_br_lb;// bottom right corner storing (l,b)/ langtitude,latitude;
    cv::Point2i dem_tr_lb;// top right corner storing (l,b)/ langtitude,latitude;
public:
    // std::string dempath;
    cv::Mat dem;
    cv::Mat dem_extented;
    GDALDataset* poDEMDataset;
    GDALRasterBand* poDEMBand;
	double padfGeotransform[6];

public:
    DEMModel(const std::string dempath){    
        poDEMDataset = LoadRasterToDataset(dempath);
        poDEMBand = poDEMDataset->GetRasterBand(1);
        // poDataset->GetGeoTransform(padfGeotransform);
        
        printf( "Size is %dx%dx%d\n", poDEMDataset->GetRasterXSize(), poDEMDataset->GetRasterYSize(), poDEMDataset->GetRasterCount() );
        if( poDEMDataset->GetProjectionRef()  != NULL )
            printf( "Projection is `%s'\n", poDEMDataset->GetProjectionRef() );
        if( poDEMDataset->GetGeoTransform( padfGeotransform ) == CE_None )
        {
            printf( "Origin = (%.6f,%.6f)\n",
                    padfGeotransform[0], padfGeotransform[3] );
            printf( "Pixel Size = (%.6f,%.6f)\n",
                    padfGeotransform[1], padfGeotransform[5] );
        }
        int             nBlockXSize, nBlockYSize;
        poDEMBand->GetBlockSize( &nBlockXSize, &nBlockYSize );
        printf( "Block=%dx%d Type=%s, ColorInterp=%s\n",
                nBlockXSize, nBlockYSize,
                GDALGetDataTypeName(poDEMBand->GetRasterDataType()),
                GDALGetColorInterpretationName(
                    poDEMBand->GetColorInterpretation()) );

        if( poDEMBand->GetOverviewCount() > 0 )
            printf( "Band has %d overviews.\n", poDEMBand->GetOverviewCount() );
        if( poDEMBand->GetColorTable() != NULL )
            printf( "Band has a color table with %d entries.\n",
                    poDEMBand->GetColorTable()->GetColorEntryCount() );

        dem = cv::imread(dempath, cv::IMREAD_LOAD_GDAL | cv::IMREAD_ANYDEPTH );
        std::cout<<"Types with initial dataloader opencv: "<<dem.type()<<std::endl;
        KGDAL2CV cvtclient;
        dem = cvtclient.ImgReadByGDAL(dempath.data());
        cvtclient.Close();
        std::cout<<"Types with selfmade dataloader opencv: "<<dem.type()<<std::endl;
        dem_extented = PaddingBorder(dem);
        // string ty =  DE::type2str( dem.type() );
        // printf("Matrix: %s %dx%d \n", ty.c_str(), dem.cols, dem.rows );
        dem_tl_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(.0,.0)));
        dem_bl_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(.0,dem.size().height)));
        dem_br_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(dem.size().width,dem.size().height)));
        dem_tr_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(dem.size().width,0)));

    };
    ~DEMModel(){GDALClose(poDEMDataset);};
    std::pair<int,int> GetMinMax(GDALRasterBand* const);
    double GT(int i){return padfGeotransform[i];}
    // cv::Point2d GetGeoCoordinate(const cv::Point2d& );
    double GetHeight(const double& , const double& , const double&);
    cv::Point2d LERP( const cv::Point2d&, const cv::Point2d&, const double& );
    double LERP(const int& , const int& , const double& );
    double BLERP(const cv::Mat& mat, const cv::Point2i& lb, const cv::Point2i& lt, const cv::Point2i& rb, const cv::Point2i& rt, cv::Point2d pix);
    cv::Vec3b GetDEMCOlor( const double& );
    cv::Point2d World2Pixel( const cv::Point2d&, const cv::Size&);
    cv::Point2d Pixel2World(const cv::Point2d& pixel);
    cv::Point2i validpixel(const cv::Mat& dem, cv::Point2i& pix);
    cv::Mat PaddingBorder(const cv::Mat& dem);
    void AddColor( cv::Vec3b& pix, const uchar& b, const uchar& g, const uchar& r );
    // cv::Point2d Pixel2World( const int& x, const int& y, const cv::Size& size );
    template <typename DATATYPE, int N>
    cv::Vec<DATATYPE,N> LERP( cv::Vec<DATATYPE,N> const& minColor, cv::Vec<DATATYPE,N> const& maxColor, double const& t );
};

class TextureModel
{
private:
    cv::Point2i tex_tl_lb;// top left corner storing (l,b)/ langtitude,latitude;
    cv::Point2i tex_bl_lb;// bottom left corner storing (l,b)/ langtitude,latitude;
    cv::Point2i tex_br_lb;// bottom right corner storing (l,b)/ langtitude,latitude;
    cv::Point2i tex_tr_lb;// top right corner storing (l,b)/ langtitude,latitude;
public:
    GDALDataset* poTEXDataset;
    std::map<std::string, GDALRasterBand*> BandDict;
    double padfGeotransform[6];
    cv::Mat tex;
public:
    TextureModel(std::string texPath) {
        poTEXDataset = (GDALDataset*)GDALOpen(texPath.data(),GA_ReadOnly);
        uint nbands = poTEXDataset->GetRasterCount();
        for(uint i = 1; i <= nbands; ++i){
            GDALRasterBand* poband = poTEXDataset->GetRasterBand(i);
            std::string strColorName = GDALGetColorInterpretationName(poband->GetColorInterpretation());
            BandDict.insert(std::pair<std::string, GDALRasterBand*>(strColorName,poband));

        }
        if( poTEXDataset->GetGeoTransform( padfGeotransform ) == CE_None )
        {
            printf( "Origin = (%.6f,%.6f)\n",
                    padfGeotransform[0], padfGeotransform[3] );
            printf( "Pixel Size = (%.6f,%.6f)\n",
                    padfGeotransform[1], padfGeotransform[5] );
        }
        KGDAL2CV cvtclient;
        tex = cvtclient.ImgReadByGDAL(texPath.data());
        cvtclient.Close();
        std::cout<<"Types with selfmade dataloader opencv: "<<tex.type()<<std::endl;
        tex_tl_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(.0,.0)));
        tex_bl_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(.0,tex.size().height)));
        tex_br_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(tex.size().width,tex.size().height)));
        tex_tr_lb = static_cast<cv::Point2i>(Pixel2World(cv::Point2d(tex.size().width,0)));
    }

    ~TextureModel() {GDALClose(poTEXDataset);}

    std::pair<double,double> GetTextureCoordinatesMN(const double& l,const double& b);
    // double GetTextureCoordinatesN(const double& l,const double& b);
    double GT(int i){return padfGeotransform[i];}
    cv::Point2d Pixel2World(const cv::Point2d& pixel);
    cv::Point2d World2Pixel( const cv::Point2d&, const cv::Size&);
};



} //namespace DE






#endif