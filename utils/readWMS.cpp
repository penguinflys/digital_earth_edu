#include "GDAL_WMS.h"
#include <vector>
#include <fstream>
#include "gdal_priv.h"
#include "cpl_conv.h" //for CPLMalloc()
#include "cpl_string.h"
#include "fstream"
#include "iostream"
#include "stdio.h"



	typedef unsigned short DT_16U;
	typedef  char   Byte;  
	typedef  short   DT_16S;  

	F




using namespace std;
int  nXSize;
int  nYSize;


void readWMS()
{
	typedef unsigned short DT_16U;
	typedef  char   Byte;  
	typedef  short   DT_16S;  

    //注册文件格式
    GDALAllRegister();
   
    const char* pszFile = "F:\\test2_8bit_2.tif";
    GDALDataset *poDataset;
    
    poDataset = (GDALDataset*) GDALOpen( pszFile,GA_ReadOnly );
    if( poDataset == NULL )
    {
        printf( "File: %s不能打开！\n",pszFile);
		getchar();
        
    }
	////判断写入格式是否可用Create()或CreateCopy()
	//const char *pszFormat ="GTIFF";
	//GDALDriver *poDriver;
	//char **papszMetadata;

	//poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);

	//if(poDriver==NULL)
	//{
	//		printf("The type of this Format is wrong.\n");
	//        getchar();
	//	    exit(1);
	//}  
	//papszMetadata=poDriver->GetMetadata();
	//if(CSLFetchBoolean(papszMetadata,GDAL_DCAP_CREATE,FALSE))
	//	printf("Driver %s supports Create() method.\n",pszFormat );
	//if(CSLFetchBoolean(papszMetadata,GDAL_DCAP_CREATECOPY,FALSE))
	//    printf("Driver %s supports CreateCopy() method.\n",pszFormat );
	//char ** papszMetadataLocation=NULL;


	//尝试使用CreateCopy()来创建新文件
	//const char* psz_Write_File = "F:\\test_Write.tif";
	//GDALDataset  *poDstDS;
	//poDstDS= poDriver->CreateCopy(psz_Write_File,poDataset,FALSE,NULL,NULL,NULL);
	//
 //   if( poDstDS != NULL )
	//{
	//	printf("We are done, press any keyborad to close the dataset properly.\n");
 //      GDALClose( (GDALDatasetH) poDstDS );
	//}

 ////   输出图像的格式信息

 //   printf( "Driver: %s/%s\n",
 //       poDataset->GetDriver()->GetDescription(),
 //       poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME) );
 //
 //   //输出图像的大小和波段个数
 //   printf( "Size is %dx%dx%d\n",
 //       poDataset->GetRasterXSize(),poDataset->GetRasterYSize(),
 //       poDataset->GetRasterCount());
 //int a=poDataset->GetRasterCount();
 //   //输出图像的投影信息
 //   if( poDataset->GetProjectionRef() != NULL )
 //       printf( "Projection is '%s'\n", poDataset->GetProjectionRef() );
 
    //输出图像的坐标和分辨率信息
   double padfGeoTransform[6];
   poDataset->GetGeoTransform(padfGeoTransform);
    //if( poDataset->GetGeoTransform( padfGeoTransform) == CE_None )
    //{
    //    printf( "Origin =(%.6f,%.6f)\n",
    //        padfGeoTransform[0], padfGeoTransform[3]);
 
    //    printf( "PixelSize = (%.6f,%.6f)\n",
    //        padfGeoTransform[1], padfGeoTransform[5]);
    //}
 
    GDALRasterBand *poBand;
    //int            nBlockXSize, nBlockYSize;
    //int            bGotMin, bGotMax;
    //double     adfMinMax[2];
 
    //读取第一个波段
    poBand = poDataset->GetRasterBand( 1 );
    //设置datatype
	GDALDataType dataType =poBand->GetRasterDataType();
 
    //获取图像的块大小并输出
    //poBand->GetBlockSize(&nBlockXSize, &nBlockYSize );
    //printf( "Block=%dx%d, Type=%s, ColorInterp=%s\n",
    //    nBlockXSize, nBlockYSize,
    //    GDALGetDataTypeName(poBand->GetRasterDataType()),
    //    GDALGetColorInterpretationName(
    //    poBand->GetColorInterpretation()));
 
    //获取该波段的最大值最小值，如果获取失败，则进行统计
    //adfMinMax[0] = poBand->GetMinimum( &bGotMin);
    //adfMinMax[1] = poBand->GetMaximum( &bGotMax);
 
    //if( ! (bGotMin&& bGotMax) )
    //    GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
 
    //printf( "Min=%.3f,Max=%.3f\n", adfMinMax[0], adfMinMax[1] );
 
    //输出图像的金字塔信息
    //if( poBand->GetOverviewCount() > 0 )
    //    printf( "Band has %d overviews.\n", poBand->GetOverviewCount() );
 
    //输出图像的颜色表信息
    //if( poBand->GetColorTable() != NULL)
    //    printf( "Band has a color table with %d entries.\n",
    //    poBand->GetColorTable()->GetColorEntryCount() );


   nXSize = poBand->GetXSize();
   nYSize = poBand->GetYSize();

	Byte *pafScanline=new Byte[nXSize*nYSize];
	//DT_16S *pafScanline;


   
    //读取图像的第一行数据
  //  pafScanline = (DT_16S*) CPLMalloc(sizeof(DT_16S)*nXSize*nYSize);

	for(int i=0;i<nXSize*nYSize;i++)
	{
		pafScanline[i]=0;
	}
    poBand->RasterIO(GF_Read,
		                              0, 
									  0, 
									  nXSize,
									  nYSize, 
                                      pafScanline, 
									  nXSize,
									  nYSize,
									  GDALDataType(poBand->GetRasterDataType()),
									  0, 
									  0 );
	//for(int i=0;i++;i<nXSize)
	//{
	//	printf("%d\n",*pafScanline++);
	//}
	//printf("%d\n",*poBand);


	 Byte **data=new Byte *[nXSize];


	long t=0,i=0,j=0;
	for(long i=0;i<nYSize;i++)
	{

		 data[i]=new Byte [nXSize];
	}
	//cout<<"输出元数据组data："<<endl;
	//FILE *fp=fopen("F:\\test.txt","w");
	for(long i=0;i<nYSize;i++)
	{

		//printf("\n");
		for(long j=0;j<nXSize;j++)
		{
			data[i][j]=pafScanline[t++];
		//	cout<<"/t"<<data[i][j];
			//printf("%d\t",data[i][j]);
			//fprintf(fp,"%d ",data[i][j]);
		}
		//fprintf(fp,"\n");
	}
	cout<<endl;
	 
	//仿射变换求地理坐标
	//printf("%.6f\t%.6f\t%.6f\t%.6f\t%.6\t%.6f\t%.6f\t",padfGeoTransform[0],padfGeoTransform[1],padfGeoTransform[2],padfGeoTransform[3],padfGeoTransform[4],padfGeoTransform[5]);

	


	//double Xp,Yp;
	//for(long i=0;i<nYSize;i++)
	//{

	//	for(long j=0;j<nXSize;j++)
	//	{
	//		Xp=padfGeoTransform[0]+i*padfGeoTransform[1]+j*padfGeoTransform[2];
	//		Yp=padfGeoTransform[3]+i*padfGeoTransform[4]+j*padfGeoTransform[5];
	//	}

	//}

	//释放内存






 
    CPLFree(pafScanline);
    
    //关闭文件
    GDALClose((GDALDatasetH)poDataset);



	//return(*data);
}