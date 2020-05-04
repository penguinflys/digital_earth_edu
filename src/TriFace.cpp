#include "TriFace.h"
#include <math.h>
#include "utils.h"


namespace DE{


double CVect8D::getNormal()
{
	return sqrt(x*x+y*y+z*z);
}

CVect8D& CVect8D::operator = (const CVect8D& vect)
{
	x=vect.x;
	y=vect.y;
	z=vect.z;
	b=vect.b;
	l=vect.l;
	h=vect.h;
	m=vect.m;
	n=vect.n;
	return *this;
}

CVect8D operator + (const CVect8D& vect1,const CVect8D& vect2)
{
	CVect8D vec;
	vec.x=vect1.x+vect2.x;
	vec.y=vect1.y+vect2.y;
	vec.z=vect1.z+vect2.z;
	vec.b=vect1.b+vect2.b;
	vec.l=vect1.l+vect2.l;
	vec.h=vect1.h+vect2.h;
	vec.m=vect1.m+vect2.m;
	vec.n=vect1.n+vect2.n;
	return vec;
}
CVect8D operator - (const CVect8D& vect1,const CVect8D& vect2)
{
	CVect8D vec;
	vec.x=vect1.x-vect2.x;
	vec.y=vect1.y-vect2.y;
	vec.z=vect1.z-vect2.z;
	vec.b=vect1.b-vect2.b;
	vec.l=vect1.l-vect2.l;
	vec.h=vect1.h-vect2.h;
	vec.m=vect1.m-vect2.m;
	vec.n=vect1.n-vect2.n;
	return vec;
}
CVect8D operator / (const CVect8D& vect1,float val)
{
	CVect8D vec;
	vec.x=vect1.x/val;
	vec.y=vect1.y/val;
	vec.z=vect1.z/val;
	return vec;
}
CVect8D operator * (const CVect8D& vect1,float val)
{
	CVect8D vec;
	vec.x=vect1.x*val;
	vec.y=vect1.y*val;
	vec.z=vect1.z*val;
	return vec;
}
ostream& operator << (ostream &out, const CVect8D& vect){
	out << std::fixed << setw(10) << setprecision(4) << setfill(' ')<<std::showpos << "CVec8D:"
	<< " X:"<<vect.x<<" Y:"<<vect.y<<" Z:"<<vect.z
	<< " B:"<<vect.b<<" L:"<<vect.l<<" H:"<<vect.h
	<< " M:"<<vect.m<<" N:"<<vect.n;
	return out;
}

double distance( CVect8D vect1, CVect8D vect2)
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
		CVect8D pt;
		pt.x=vdata[i][0]; pt.y=vdata[i][1]; pt.z=vdata[i][2];
		SetBLH(pt,ptr_dem);
		SetMN(pt,ptr_tex);
		pts.push_back(pt);
	}
	pFaces->empty();
	for(int i=0;i<20;i++)
	{
		TriFace tri;
		tri.vertid[0]=tindices[i][0];
		tri.vertid[1]=tindices[i][1];
		tri.vertid[2]=tindices[i][2];
		pFaces->push_back(tri);
	}
	currentLevel=0;
	radius=pts[0].getNormal();
}
void CSphericTriangles::getNormalVector(TriFace& triFace,CVect8D& normalVector)
{
	normalVector.x=(pts[triFace.vertid[0]].x+pts[triFace.vertid[1]].x+pts[triFace.vertid[2]].x)/3;
	normalVector.y=(pts[triFace.vertid[0]].y+pts[triFace.vertid[1]].y+pts[triFace.vertid[2]].y)/3;
	normalVector.z=(pts[triFace.vertid[0]].z+pts[triFace.vertid[1]].z+pts[triFace.vertid[2]].z)/3;
}
void CSphericTriangles::getMidEdgePoint(TriFace& triFace,CVect8D& midPt1,CVect8D& midPt2,CVect8D& midPt3)
{
	midPt1=(pts[triFace.vertid[0]]+pts[triFace.vertid[1]])/2.0;
	midPt2=(pts[triFace.vertid[1]]+pts[triFace.vertid[2]])/2.0;
	midPt3=(pts[triFace.vertid[2]]+pts[triFace.vertid[0]])/2.0;
	midPt1=midPt1*radius/midPt1.getNormal();
	SetBLH(midPt1,ptr_dem);
	SetMN(midPt1,ptr_tex);
	midPt1.level++;
	midPt2=midPt2*radius/midPt2.getNormal();
	SetBLH(midPt2,ptr_dem);
	SetMN(midPt2,ptr_tex);
	midPt2.level++;
	midPt3=midPt3*radius/midPt3.getNormal();
	SetBLH(midPt3,ptr_dem);
	SetMN(midPt3,ptr_tex);
	midPt3.level++;


}
void CSphericTriangles::outputEdgsLength(ofstream& ofile)
{
	for(vector<TriFace>::iterator it=pFaces->begin();it!=pFaces->end();it++)
	{
		double edge0,edge1,edge2;
		long id0,id1,id2;
		id0=it->vertid[0]; id1=it->vertid[1];id2=it->vertid[2];
		CVect8D pt0=pts[id0];
		CVect8D pt1=pts[id1];
		CVect8D pt2=pts[id2];
		edge0=(pt0+(pt1*-1)).getNormal();
		edge1=(pt1+(pt2*-1)).getNormal();
		edge2=(pt2+(pt0*-1)).getNormal();
		double area=getArea(*it);
		ofile<<it->vertid[0]<<","<<it->vertid[1]<<","<<it->vertid[2]<<","<<edge0<<","<<edge1<<","<<edge2<<","<<area<<endl;
	}
}
double CSphericTriangles::getArea(TriFace& triFace)
{
	double x0,y0,x1,y1,x2,y2,z0,z1,z2;
	x0=pts[triFace.vertid[0]].x;
	x1=pts[triFace.vertid[1]].x;
	x2=pts[triFace.vertid[2]].x;
	y0=pts[triFace.vertid[0]].y;
	y1=pts[triFace.vertid[1]].y;
	y2=pts[triFace.vertid[2]].y;
	z0=pts[triFace.vertid[0]].z;
	z1=pts[triFace.vertid[1]].z;
	z2=pts[triFace.vertid[2]].z;
	return 	((y1-y0)*(z2-z0) + (z1-z0)*(x2-x0) + (x1-x0)*(y2-y0)) - ((y2-y0)*(z1-z0) + (z2-z0)*(x1-x0) + (x2-x0)*(y1-y0));
}

void CSphericTriangles::nextLevel()
{
	vector<TriFace>* pNewTriFaces=new vector<TriFace>;
	long currentPtCount=pts.size();
	for(vector<TriFace>::iterator it=pFaces->begin();it!=pFaces->end();it++)
	{
		CVect8D newPoint0,newPoint1,newPoint2;
		getMidEdgePoint(*it,newPoint0,newPoint1,newPoint2);

		pts.push_back(newPoint0);
		long newPt0ID=currentPtCount++;
		pts.push_back(newPoint1);
		long newPt1ID=currentPtCount++;
		pts.push_back(newPoint2);
		long newPt2ID=currentPtCount++;
	
		TriFace newfaces[4];
		newfaces[0].vertid[0]=it->vertid[0];
		newfaces[0].vertid[1]=newPt0ID;
		newfaces[0].vertid[2]=newPt2ID;
		pNewTriFaces->push_back(newfaces[0]);

		newfaces[1].vertid[0]=newPt0ID;
		newfaces[1].vertid[1]=newPt1ID;
		newfaces[1].vertid[2]=newPt2ID;
		newfaces[1].level++;
		pNewTriFaces->push_back(newfaces[1]);

		newfaces[2].vertid[0]=newPt0ID;
		newfaces[2].vertid[1]=it->vertid[1];
		newfaces[2].vertid[2]=newPt1ID;
		pNewTriFaces->push_back(newfaces[2]);

		newfaces[3].vertid[0]=newPt1ID;
		newfaces[3].vertid[1]=it->vertid[2];
		newfaces[3].vertid[2]=newPt2ID;
		pNewTriFaces->push_back(newfaces[3]);
	}
	delete pFaces;
	pFaces=pNewTriFaces;
	currentLevel++;
}
void CSphericTriangles::SetBLH(CVect8D& vec, DEMModel* dem){
	vec.b = atan2(vec.z,sqrt(vec.y*vec.y + vec.x*vec.x));
	vec.l = atan2(vec.y,vec.x);
	vec.b = RAD2DMS(vec.b);
	vec.l = RAD2DMS(vec.l);
	// std::cout<<"Before Setting Elevation:\n";
	// std::cout<<vec<<std::endl;
	vec.h = dem->GetHeight(vec.l, vec.b, 0.00001);
	vec.b = DMS2RAD(vec.b);
	vec.l = DMS2RAD(vec.l);
	SetXYZ(vec);
}
void CSphericTriangles::SetBLH(CVect8D& vec){
	vec.b = atan2(vec.z,sqrt(vec.y*vec.y + vec.x*vec.x));
	vec.l = atan2(vec.y,vec.x);
 	vec.h = 0;
}
void CSphericTriangles::SetXYZ(CVect8D& vec){
	double r_prime = (this->radius + vec.h)*cos(vec.b);
    vec.x = r_prime * cos(vec.l);
    vec.y = r_prime * sin(vec.l);
    vec.z = (this->radius + vec.h) * sin(vec.b);
}
void CSphericTriangles::SetMN(CVect8D& vec, TextureModel* tex){
	vec.l = RAD2DMS(vec.l);
	vec.b = RAD2DMS(vec.b);
	std::pair<double,double> mn = tex->GetTextureCoordinatesMN(vec.l,vec.b);
	vec.l = DMS2RAD(vec.l);
	vec.b = DMS2RAD(vec.b);
	
	vec.m = mn.first;
	vec.n = mn.second;
}
} //namespace DE