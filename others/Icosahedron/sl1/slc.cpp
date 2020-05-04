#ifndef GLUT_DISABLE_ATEXIT_HACK  
#define GLUT_DISABLE_ATEXIT_HACK 
#endif 
//#define _CRT_TERMINATE_DEFINED
#include "triface.h"
#include <GL/glut.h>//包含相应的头文件
 ofstream ofile;
int dx = 0, dy = 0;
double zZoom=1;
CSphericTriangles sphere;

//#define X .525731112119133606
//#define Z .850650808352039932 
void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);//设置着色模式
	glEnable(GL_DEPTH_TEST);  //开启深度测试
	glEnable(GL_LIGHTING);//开启光照
	glEnable(GL_NORMALIZE);//开启法向量自动规范化
	GLfloat ambientLight[]={1.0f,1.0f,1.0f,1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
	//创建一个白色光源
	GLfloat light_position[] = { -1.0,- 1.0, 0.0, 0.0 };
	GLfloat light_ambient[] = { 1, 1, 1, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,light_diffuse);
	//glEnable(GL_LIGHT0);//启用第0个光源

	GLfloat light_position1[] = { 1.0, 1.0, 0.0, 0.0 };
	GLfloat light_ambient1[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse1[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT,light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,light_diffuse1);
	glEnable(GL_LIGHT1);//启用第0个光源
	sphere.createIcosahedron();
}
void DrawSphere(CSphericTriangles& sphere)
{
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//镜面反射指数
	for (int i = 0; i < (*(sphere.pFaces)).size(); i++) {/* color information here */ 
		CVect3D normalvector;
		TriFace& face=(*(sphere.pFaces))[i];
		sphere.getNormalVector(face,normalvector);
		GLfloat mat_ambient1[] = { 0.2,0.2,0.2 };
		GLfloat mat_diffuse1[] = { 0.8,0.8,0.8 };
		GLfloat mat_ambient2[] = { 0.2,0,0 };
		GLfloat mat_diffuse2[] = { 0.2,0,0 };
		if(face.level % 2==0)
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
		}
		else
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
		}
		glBegin(GL_TRIANGLES); 
		glNormal3f(normalvector.x,normalvector.y,normalvector.z);
		glVertex3f(sphere.pts[face.pt[0]].x,sphere.pts[face.pt[0]].y,sphere.pts[face.pt[0]].z);
		glVertex3f(sphere.pts[face.pt[1]].x,sphere.pts[face.pt[1]].y,sphere.pts[face.pt[1]].z);
		glVertex3f(sphere.pts[face.pt[2]].x,sphere.pts[face.pt[2]].y,sphere.pts[face.pt[2]].z);
		glEnd();
	}
	GLfloat mat_ambient3[] = { 1,0,0};
	GLfloat mat_diffuse3[] = { 1,0,0 };
	//GLfloat mat_specular2[] = { 0.0, 0.0, 0.6, 1.0 };
	//GLfloat mat_shininess[] ={ 10.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glBegin(GL_LINES); 
	for (int i = 0; i < (*(sphere.pFaces)).size(); i++) {/* color information here */ 
		TriFace& face=(*(sphere.pFaces))[i];
		glColor3f(1,0,0);
		glVertex3f(sphere.pts[face.pt[0]].x,sphere.pts[face.pt[0]].y,sphere.pts[face.pt[0]].z);
		glVertex3f(sphere.pts[face.pt[1]].x,sphere.pts[face.pt[1]].y,sphere.pts[face.pt[1]].z);
		glVertex3f(sphere.pts[face.pt[2]].x,sphere.pts[face.pt[2]].y,sphere.pts[face.pt[2]].z);
		glVertex3f(sphere.pts[face.pt[0]].x,sphere.pts[face.pt[0]].y,sphere.pts[face.pt[0]].z);
	}
	glEnd();
}

//void Icosahedron1()
//{
//	static GLfloat vdata[12][3] = { {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}}; 
//	static GLuint tindices[20][3] = { {1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},{3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},{10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}}; 
//			GLfloat mat_ambient2[] = { 0.2,0.2,0.2 };
//			GLfloat mat_diffuse2[] = { 0.8,0.8,0.8 };
//			//GLfloat mat_specular2[] = { 0.0, 0.0, 0.6, 1.0 };
//			//GLfloat mat_shininess[] ={ 10.0 };
//			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
//			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
//			//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
//			//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//镜面反射指数
//	for (int i = 0; i < 20; i++) {/* color information here */ 
//		GLfloat xCenter= vdata[tindices[i][0]][0]+vdata[tindices[i][1]][0]+vdata[tindices[i][2]][0];
//		GLfloat yCenter= vdata[tindices[i][0]][1]+vdata[tindices[i][1]][1]+vdata[tindices[i][2]][1];
//		GLfloat zCenter= vdata[tindices[i][0]][2]+vdata[tindices[i][1]][2]+vdata[tindices[i][2]][2];
//		glBegin(GL_TRIANGLES); 
//		glNormal3f(xCenter,yCenter,zCenter);
//	//	glNormal3fv(&vdata[tindices[i][0]][0]);
//		glVertex3fv(&vdata[tindices[i][0]][0]);
//	//	glNormal3fv(&vdata[tindices[i][1]][0]);
//		glVertex3fv(&vdata[tindices[i][1]][0]);
//	//	glNormal3fv(&vdata[tindices[i][2]][0]);
//		glVertex3fv(&vdata[tindices[i][2]][0]);
//		glEnd();
//
//	}
//				GLfloat mat_ambient3[] = { 1,0,0};
//			GLfloat mat_diffuse3[] = { 1,0,0 };
//			//GLfloat mat_specular2[] = { 0.0, 0.0, 0.6, 1.0 };
//			//GLfloat mat_shininess[] ={ 10.0 };
//			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
//			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
//		glBegin(GL_LINES); 
//	for (int i = 0; i < 20; i++) {/* color information here */ 
//		glColor3f(1,0,0);
//		glVertex3fv(&vdata[tindices[i][0]][0]);
//		glVertex3fv(&vdata[tindices[i][1]][0]);
//		glVertex3fv(&vdata[tindices[i][2]][0]);
//		glVertex3fv(&vdata[tindices[i][0]][0]);
//	}
//	glEnd();
//}
void TEN()
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
 	//face 0 
	glNormal3f(1,1,1);//为后面顶点定义法向量
	glVertex3f(0,1,0); //0   
	glNormal3f(1,1,1);
	glVertex3f(0,0,1); //1 
	glNormal3f(1,1,1);
	glVertex3f(1,0, 0);//2 
	//face 1
	glNormal3f(0,-1,0);
	glVertex3f(0,0,1); //1       
	glNormal3f(0,-1,0);
	glVertex3f(0,0, 0);//3  
	glNormal3f(0,-1,0);
	glVertex3f(1,0, 0);//2
	//face 2
	glNormal3f(-1,0,0);
	glVertex3f(0,1,0); //0       
	glNormal3f(-1,0,0);
	glVertex3f(0,0,1); //1       
	glNormal3f(-1,0,0);
	glVertex3f(0,0, 0);//3 
	//face 3
	glNormal3f(0,0,-1);
	glVertex3f(0,1,0); //0       
	glNormal3f(0,0,-1);
	glVertex3f(1,0, 0);//2
	glNormal3f(0,0,-1);
	glVertex3f(0,0, 0);//3  
	glEnd();     
	glPopMatrix();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0,0,zZoom);
		glRotatef ((GLfloat) dx, 1.0, 0.0, 0.0);
		glRotatef((GLfloat) dy,0.0,1.0,0.0); 
		glPushMatrix();//绘制四面体
			GLfloat mat_ambient1[] = { 0,0,0.2,1.0 };
			GLfloat mat_diffuse1[] = { 0,0,8,1.0 };
			GLfloat mat_specular1[] = { 0.0, 0.0, 0, 1.0 };
			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
			//TEN();
			DrawSphere(sphere);
		glPopMatrix();

		//glPushMatrix();
		//	GLfloat mat_ambient2[] = { 0.2,0,0,1.0 };
		//	GLfloat mat_diffuse2[] = { 0.8,0,0,1.0 };
		//	GLfloat mat_specular2[] = { 0.0, 0.0, 0.6, 1.0 };
		//	GLfloat mat_shininess[] ={ 10.0 };
		//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
		//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
		//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
		//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//镜面反射指数
		//	glTranslatef(-1,0,0);
		//	glutSolidSphere (1.0, 100, 100);
		//glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
	
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	  case 'w':
		  dx = (dx + 1) % 360;
		  glutPostRedisplay();
		  break;
	  case 's':
		  dx = (dx - 1) % 360;
		  glutPostRedisplay();
		  break;
	  case 'a':
		  dy = (dy + 1) % 360;
		  glutPostRedisplay();
		  break;
	  case 'd':
		  dy = (dy - 1) % 360;
		  glutPostRedisplay();
		  break;
	  case 'i':
		  zZoom = zZoom*1.1;
		  glutPostRedisplay();
		  break;
	   case 'o':
		  zZoom = zZoom/1.1;
		  glutPostRedisplay();
		  break;
	   case 'r'://递归剖分
		  sphere.nextLevel();
		  glutPostRedisplay();
		  break;
	   case 'p':
	    ofile.open("d:\\sphere.txt");
		ofile<<"ptId0,ptId1,ptId2,edge0-1,edge1-2,edge2-0,area"<<endl;
		sphere.outputEdgsLength(ofile);
		ofile.close();
		  break;
	  default:
		  break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}