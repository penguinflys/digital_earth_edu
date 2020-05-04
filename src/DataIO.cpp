#include "DataIO.h"
#include "gdal/gdal_priv.h"
#include <iostream>

// overload operator, for debug purpose.

namespace DE
{
// Because there might be multiple images in one Dataset, althrough current only one image.

// RasterImageBand* RasterImageDataset::getImageBand(int i){
// 	return dynamic_cast<RasterImageBand*>(this->poDataset->GetRasterBand(i));
// }

// void RasterImageDataset::GetOverview(){
// 	if (this->poDataset != nullptr){
// 		int RasterCount = this->poDataset->GetRasterCount();
// 		int RasterXSize = this->poDataset->GetRasterXSize();
// 		int SummaryRefCount = this->poDataset->GetSummaryRefCount();
// 		int RasterYSize = this->poDataset->GetRasterYSize();
// 		std::cout<<"********************** Dataset Info **********************\n";
// 		std::cout<< "This Dataset has:\n";
// 		std::cout<< "Rastercounts: \t" 		<< RasterCount<<"\n";
// 		std::cout<< "RasterXSize: \t"		<< RasterXSize<<"\n";
// 		std::cout<< "RasterYSize: \t" 		<< RasterYSize<<"\n";
// 		std::cout<< "SummaryRefCount: \t" 	<< SummaryRefCount<<"\n";
// 	}
// }

std::ostream &operator<<(std::ostream &os, const RasterImageBand &img)
{
	os << img.sPath << std::endl;
	os << "Origin = "	  << img.padfGeoTransform[0] << "," << img.padfGeoTransform[3] << std::endl;
	os << "Pixel Size = " << img.padfGeoTransform[1] << "," << img.padfGeoTransform[5] << std::endl;
	return os;
}

std::string RasterImageDataset::getDatasetPath(){
	return this->strDatasetPath;
}



} // namespace DE