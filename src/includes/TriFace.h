#ifndef DE_TRI_FACE_H
#define DE_TRI_FACE_H
#include <vector>
#include <fstream>
#include "ElevationAndTexture.h"

using namespace std;

namespace DE{

class CSphericTriangles;

class CVect8D{
public:
	CVect8D(){level=0;}
	~CVect8D(){}
	// friend class TriFace, CSphericTriangles;
public:
	double getNormal();
	CVect8D& operator = (const CVect8D& vect);
	//CVect3D& operator /= (float val);
	friend void XYZ2BLH(const CVect8D& vec);
	friend void BLH2XYZ(const CSphericTriangles& sphere, const CVect8D& vec);
	friend ostream& operator << (ostream &out, const CVect8D& vect);
public:
	// spatial coordinate
	double x;
	double y;
	double z;
	// geographical coordinate
	double b = 0.0;
	double l = 0.0;
	double h = 0.0;
	// opengl texture coordinates
	float m = 0.0;
	float n = 0.0;
	// level of Sphere
	int level;
	
};



class TriFace{
public:
	TriFace(){level=0;};
	~TriFace(){};
	// friend class CVect8D;
public:
	long vertid[3];
	int level;
};
CVect8D operator + (const CVect8D& vect1,const CVect8D& vect2);
CVect8D operator /(const CVect8D& vect1,float val);
CVect8D operator *(const CVect8D& vect1,float val);
ostream& operator << (ostream &out, const CVect8D& vect);
double distance( CVect8D vect1, CVect8D vect2);

class CSphericTriangles
{
	
public:
	CSphericTriangles(const std::string& strDEMFileName, const std::string& strTEXFileName){
		pFaces=new vector<TriFace>;
		currentLevel=0;
		radius=1;
		ptr_dem = new DEMModel(strDEMFileName);
		ptr_tex = new TextureModel(strTEXFileName);}
	~CSphericTriangles(){if(pFaces) delete pFaces;	if(ptr_dem) delete ptr_dem;}
public:
	//CVect3D pt[3];
	vector<CVect8D> pts;
	vector<TriFace>* pFaces;
	double radius;
	int currentLevel;
public:
	DEMModel* ptr_dem;
	TextureModel* ptr_tex;
	// TextureModel tex;
public:
	void getNormalVector(TriFace& triFace,CVect8D& normalVector);
	void getMidEdgePoint(TriFace& triFace,CVect8D& midPt1,CVect8D& midPt2,CVect8D& midPt3);
	void nextLevel();
	void createIcosahedron();
	void outputEdgsLength(ofstream& ofile);
	double getArea(TriFace& triFace);
	void SetBLH(CVect8D& vec, DEMModel* dem);
	void SetMN(CVect8D& vec, TextureModel* tex);
	void SetBLH(CVect8D& vec);
	void SetXYZ(CVect8D& vec);
};

} //namespace

#endif // DE_TRI_FACE_H