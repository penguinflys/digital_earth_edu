#include "TriFace.h"
#include <math.h>
double CVect3D::getNormal()
{
	return sqrt(x*x+y*y+z*z);
}
CVect3D& CVect3D::operator = (const CVect3D& vect)
{
	x=vect.x;
	y=vect.y;
	z=vect.z;
	return *this;
}
//CVect3D& CVect3D::operator /= (float val)
//{
//	x/=val;
//	y/=val;
//	z/=val;
//	return *this;
//}
CVect3D operator + (const CVect3D& vect1,const CVect3D& vect2)
{
	CVect3D vec;
	vec.x=vect1.x+vect2.x;
	vec.y=vect1.y+vect2.y;
	vec.z=vect1.z+vect2.z;
	return vec;
}
CVect3D operator / (const CVect3D& vect1,float val)
{
	CVect3D vec;
	vec.x=vect1.x/val;
	vec.y=vect1.y/val;
	vec.z=vect1.z/val;
	return vec;
}
CVect3D operator * (const CVect3D& vect1,float val)
{
	CVect3D vec;
	vec.x=vect1.x*val;
	vec.y=vect1.y*val;
	vec.z=vect1.z*val;
	return vec;
}
double distance( CVect3D vect1, CVect3D vect2)
{
	return (vect1+(vect2*-1)).getNormal();
}
void CSphericTriangles::createIcosahedron()
{
	const double X=.525731112119133606;
	const double Z=.850650808352039932;
	double vdata[12][3] = { {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}}; 
	long tindices[20][3] = { {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},{3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},{10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}}; 
	for(int i=0;i<12;i++)
	{
		CVect3D pt;
		pt.x=vdata[i][0]; pt.y=vdata[i][1]; pt.z=vdata[i][2];
		pts.push_back(pt);
	}
	pFaces->empty();
	for(int i=0;i<20;i++)
	{
		TriFace tri;
		tri.pt[0]=tindices[i][0];
		tri.pt[1]=tindices[i][1];
		tri.pt[2]=tindices[i][2];
		pFaces->push_back(tri);
	}
	currentLevel=0;
	radius=pts[0].getNormal();
}
CSphericTriangles::CSphericTriangles(void)
{
	pFaces=new vector<TriFace>;
	currentLevel=0;
	radius=1;
}

CSphericTriangles::~CSphericTriangles(void)
{
	if(pFaces) delete pFaces;
}
void CSphericTriangles::getNormalVector(TriFace& triFace,CVect3D& normalVector)
{
	normalVector.x=(pts[triFace.pt[0]].x+pts[triFace.pt[1]].x+pts[triFace.pt[2]].x)/3;
	normalVector.y=(pts[triFace.pt[0]].y+pts[triFace.pt[1]].y+pts[triFace.pt[2]].y)/3;
	normalVector.z=(pts[triFace.pt[0]].z+pts[triFace.pt[1]].z+pts[triFace.pt[2]].z)/3;
}
void CSphericTriangles::getMidEdgePoint(TriFace& triFace,CVect3D& midPt1,CVect3D& midPt2,CVect3D& midPt3)
{
	midPt1=(pts[triFace.pt[0]]+pts[triFace.pt[1]])/2.0;
	midPt2=(pts[triFace.pt[1]]+pts[triFace.pt[2]])/2.0;
	midPt3=(pts[triFace.pt[2]]+pts[triFace.pt[0]])/2.0;
	midPt1=midPt1*radius/midPt1.getNormal();
	midPt1.level++;
	midPt2=midPt2*radius/midPt2.getNormal();
	midPt2.level++;
	midPt3=midPt3*radius/midPt3.getNormal();
	midPt3.level++;


}
void CSphericTriangles::outputEdgsLength(ofstream& ofile)
{
	for(vector<TriFace>::iterator it=pFaces->begin();it!=pFaces->end();it++)
	{
		double edge0,edge1,edge2;
		long id0,id1,id2;
		id0=it->pt[0]; id1=it->pt[1];id2=it->pt[2];
		CVect3D pt0=pts[id0];
		CVect3D pt1=pts[id1];
		CVect3D pt2=pts[id2];
		edge0=(pt0+(pt1*-1)).getNormal();
		edge1=(pt1+(pt2*-1)).getNormal();
		edge2=(pt2+(pt0*-1)).getNormal();
		double area=getArea(*it);
		ofile<<it->pt[0]<<","<<it->pt[1]<<","<<it->pt[2]<<","<<edge0<<","<<edge1<<","<<edge2<<","<<area<<endl;
	}
}
double CSphericTriangles::getArea(TriFace& triFace)
{
	double x0,y0,x1,y1,x2,y2,z0,z1,z2;
	x0=pts[triFace.pt[0]].x;
	x1=pts[triFace.pt[1]].x;
	x2=pts[triFace.pt[2]].x;
	y0=pts[triFace.pt[0]].y;
	y1=pts[triFace.pt[1]].y;
	y2=pts[triFace.pt[2]].y;
	z0=pts[triFace.pt[0]].z;
	z1=pts[triFace.pt[1]].z;
	z2=pts[triFace.pt[2]].z;
	return 	((y1-y0)*(z2-z0) + (z1-z0)*(x2-x0) + (x1-x0)*(y2-y0)) - ((y2-y0)*(z1-z0) + (z2-z0)*(x1-x0) + (x2-x0)*(y1-y0));
}

void CSphericTriangles::nextLevel()
{
	vector<TriFace>* pNewTriFaces=new vector<TriFace>;
	long currentPtCount=pts.size();
	for(vector<TriFace>::iterator it=pFaces->begin();it!=pFaces->end();it++)
	{
		CVect3D newPoint0,newPoint1,newPoint2;
		getMidEdgePoint(*it,newPoint0,newPoint1,newPoint2);

		pts.push_back(newPoint0);
		long newPt0ID=currentPtCount++;
		pts.push_back(newPoint1);
		long newPt1ID=currentPtCount++;
		pts.push_back(newPoint2);
		long newPt2ID=currentPtCount++;
	
		TriFace newfaces[4];
		newfaces[0].pt[0]=it->pt[0];
		newfaces[0].pt[1]=newPt0ID;
		newfaces[0].pt[2]=newPt2ID;
		pNewTriFaces->push_back(newfaces[0]);

		newfaces[1].pt[0]=newPt0ID;
		newfaces[1].pt[1]=newPt1ID;
		newfaces[1].pt[2]=newPt2ID;
		newfaces[1].level++;
		pNewTriFaces->push_back(newfaces[1]);

		newfaces[2].pt[0]=newPt0ID;
		newfaces[2].pt[1]=it->pt[1];
		newfaces[2].pt[2]=newPt1ID;
		pNewTriFaces->push_back(newfaces[2]);

		newfaces[3].pt[0]=newPt1ID;
		newfaces[3].pt[1]=it->pt[2];
		newfaces[3].pt[2]=newPt2ID;
		pNewTriFaces->push_back(newfaces[3]);
	}
	delete pFaces;
	pFaces=pNewTriFaces;
	currentLevel++;
}
