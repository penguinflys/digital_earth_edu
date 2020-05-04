#pragma once
#include <vector>
#include <fstream>
using namespace std;

class CVect3D{
public:
	CVect3D(){level=0;}
	~CVect3D(){}
public:
	double getNormal();
	CVect3D& operator = (const CVect3D& vect);
	//CVect3D& operator /= (float val);

public:
	double x;
	double y;
	double z;
	int level;
};
class TriFace{
public:
	TriFace(){level=0;};
	~TriFace(){};
public:
	long pt[3];
	int level;
};
CVect3D operator + (const CVect3D& vect1,const CVect3D& vect2);
CVect3D operator /(const CVect3D& vect1,float val);
CVect3D operator *(const CVect3D& vect1,float val);
double distance( CVect3D vect1, CVect3D vect2);
class CSphericTriangles
{
public:
	CSphericTriangles(void);
	~CSphericTriangles(void);
public:
	//CVect3D pt[3];
	vector<CVect3D> pts;
	vector<TriFace>* pFaces;
	double radius;
	int currentLevel;
public:
	void getNormalVector(TriFace& triFace,CVect3D& normalVector);
	void getMidEdgePoint(TriFace& triFace,CVect3D& midPt1,CVect3D& midPt2,CVect3D& midPt3);
	void nextLevel();
	void createIcosahedron();
	void outputEdgsLength(ofstream& ofile);
	double getArea(TriFace& triFace);
};
