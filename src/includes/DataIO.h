#ifndef DE_RASTERIMAGE_H
#define DE_RASTERIMAGE_H
#include <string>
#include <gdal/gdal_priv.h>
#include <memory> // unique pointer
// #include "TriFace.h"


// this file is extension for image dataset. because there might be multiple files on a single dataset.
// both RasterImageBand and RasterImageDataset should provide various operation on these iamges.
namespace DE{

class RasterImageBand:public GDALRasterBand{

public:
	const std::string sPath;
	uint8_t *pafScanline = nullptr;
	double padfGeoTransform[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

public:
	RasterImageBand() = default;
	RasterImageBand(std::string sPath) : sPath(sPath){};
	~RasterImageBand() { delete[] pafScanline; }

	friend std::ostream & operator<<(std::ostream &os, const RasterImageBand &img);
private:
	// void LoadImage();
};


// All Operations towards dataset are warped here, because i want the application layer to be as
// easy as possible, it might looks simple but i want it manageable and easily extentable.
class RasterImageDataset:public GDALDataset{

private:
	std::string strDatasetPath;

public:

	RasterImageDataset() = default;
	~RasterImageDataset(){ GDALClose( (GDALDatasetH) this );}
	std::string getDatasetPath();
};



} // namespace DE


#endif /* IMAGE_H */