#include<iostream>
#include<pangolin/pangolin.h>
using namespace pangolin;

#include "DataIO.h"
#include "ElevationAndTexture.h"
#include <string>
#include "TriFace.h"
#include <iostream>

// TODO convert C style code to CPP and make it easier to output vertices to be in or out to config file.

void CorrectTextureCoordiante(DE::CSphericTriangles& sphere, const DE::TriFace& face){
    float& m0 = sphere.pts[face.vertid[0]].m;
    float& m1 = sphere.pts[face.vertid[1]].m;
    float& m2 = sphere.pts[face.vertid[2]].m;
    if ((m0 - m1) * (m0 - m1) + (m0 - m2) * (m0 - m2) + (m1 - m2) * (m1 - m2) > 1.5)
    {
        if (m0 - 0.0 < 0.2){
            if (m1 - 0.0 < 0.2){
                if (m2 - 1.0 < 0.2){ m2 -= 1.0; }
            }
            else if (m1 - 1.0 < 0.2){
                if (m2 - 0.0 < 0.2){ m1 -= 1.0; }
                else if (m2 - 1 < 0.2) { m0 += 1.0; }
            }
        }
        else if (m0 - 1.0 < 0.2){
            if (m1 - 0.0 < 0.2){
                if (m2 - 0.0 < 0.2) { m0 -= 1.0;}
                else if (m2 - 1.0 < 0.2) { m1 += 1.0;}
            }
            else if (m1 - 1.0 < 0.2){
                if (m2 - 0.0 < 0.2) { m2 += 1.0;}
            }
        }
    }
}
void DrawSphere(DE::CSphericTriangles& sphere)
{
    // paint the surface with default color.
	for (uint16_t i = 0; i < (*(sphere.pFaces)).size(); i++) {/* color information here */ 
		DE::CVect8D normalvector;
		DE::TriFace& face=(*(sphere.pFaces))[i];
        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glBegin(GL_TRIANGLES); 
        CorrectTextureCoordiante(sphere, face);
        glTexCoord2f(sphere.pts[face.vertid[0]].m,sphere.pts[face.vertid[0]].n);// bind texture coordinates
		glVertex3f(sphere.pts[face.vertid[0]].x,sphere.pts[face.vertid[0]].y,sphere.pts[face.vertid[0]].z);
        glTexCoord2f(sphere.pts[face.vertid[1]].m,sphere.pts[face.vertid[1]].n);// bind texture coordinates
		glVertex3f(sphere.pts[face.vertid[1]].x,sphere.pts[face.vertid[1]].y,sphere.pts[face.vertid[1]].z);
        glTexCoord2f(sphere.pts[face.vertid[2]].m,sphere.pts[face.vertid[2]].n);// bind texture coordinates
		glVertex3f(sphere.pts[face.vertid[2]].x,sphere.pts[face.vertid[2]].y,sphere.pts[face.vertid[2]].z);
		glEnd();
        // glDisable(GL_TEXTURE_2D);
	}

    // paint lines to be red.

	// for (uint16_t i = 0; i < (*(sphere.pFaces)).size(); i++) {/* color information here */ 
	// 	DE::TriFace& face=(*(sphere.pFaces))[i];
    //     glBegin(GL_LINE_LOOP); 
	// 	glColor3f(1.0f,0.0f,0.0f);
	// 	glVertex3f(sphere.pts[face.vertid[0]].x,sphere.pts[face.vertid[0]].y,sphere.pts[face.vertid[0]].z);
	// 	glVertex3f(sphere.pts[face.vertid[1]].x,sphere.pts[face.vertid[1]].y,sphere.pts[face.vertid[1]].z);
	// 	glVertex3f(sphere.pts[face.vertid[2]].x,sphere.pts[face.vertid[2]].y,sphere.pts[face.vertid[2]].z);
    //     glColor3f(0.0f,0.0f,0.0f);
    //     glEnd();
	// }
	
}

void BindCVMat2GLTexture(cv::Mat& image, GLuint& imageTexture)
{
    if(image.empty()){
        std::cout << "image empty" << std::endl;
        throw std::bad_alloc();
    }
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glGenTextures(1, &imageTexture);
    glBindTexture(GL_TEXTURE_2D, imageTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture clamping method
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    cv::cvtColor(image, image, CV_RGB2BGR);

    glTexImage2D(GL_TEXTURE_2D,         // Type of texture
                0,                   // Pyramid level (for mip-mapping) - 0 is the top level
                GL_RGB,              // Internal colour format to convert to
                image.cols,          // Image width  i.e. 640 for Kinect in standard mode
                image.rows,          // Image height i.e. 480 for Kinect in standard mode
                0,                   // Border width in pixels (can either be 1 or 0)
                GL_RGB,              // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                GL_UNSIGNED_BYTE,    // Image data type
                image.ptr());        // The actual image data itself
} 

struct InteractionUnit
{
    int dx,dy = 0;
    double zZoom = 1;
};

void RenderScene(InteractionUnit ctrlele, DE::CSphericTriangles &sphere)
{
    glPushMatrix();
        // glTranslatef(0, 0, (GLfloat)ctrlele.zZoom);
        // glRotatef((GLfloat)ctrlele.dx, 1.0, 0.0, 0.0);
        // glRotatef((GLfloat)ctrlele.dy, 0.0, 1.0, 0.0);
        glPushMatrix();
            DrawSphere(sphere);
        glPopMatrix();
    glPopMatrix();
}
// TODO Convernsion from GL_Texture to Pangolin::texture
int main(int argc, char** argv){
    const std::string strDEMFileName = "data/dem_geotiff/alwdgg.tif";
    const std::string strTEXFILEName = "data/texture/bio_2400.tiff";
    DE::CSphericTriangles SPHERE(strDEMFileName,strTEXFILEName);
    SPHERE.createIcosahedron();
    InteractionUnit CTRLELE;
    // glBindTexture(GL_TEXTURE_2D,EARTHSURFACE);
    // glBindTexture()

    // pangolin::GlTexture texture(width,height,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);
    // texture.Upload(SPHERE.ptr_tex->tex.ptr(),GL_RGB,GL_UNSIGNED_BYTE);
    // texture.SetLinear();
    // init();
    // pangolin::glDrawTexture(GL_TEXTURE_2D,EARTHSURFACE);
    // InitTexture(SPHERE,EARTHSURFACE);
    // load Configuration Data
    ParseVarsFile("config/app.cfg"); // temperily useless, deteils can be seen in the file

    // Create OpenGL Window in a single line
    CreateWindowAndBind("Digital Earth Main Window",640,480);

    // 3D Mouse handler requires depth testing to be enabled
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_NORMALIZE);
    //Define a Camera Render Object, Which models the physical world in Euclidean Space.
    OpenGlRenderState s_cam(
        ProjectionMatrix(640,480,420,420,320,240,0.1,1000),
        ModelViewLookAt(-0,0.5,-3,0,0,0,AxisY));
    
    // Configure the width of UI window
    const int UI_WIDTH = 180;

    // Add named OpenGL viewport to window and provide 3D Handler
    pangolin::View& d_cam = pangolin::Display("RenderView")
        .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -640.0f/480.0f)
        .SetHandler(new pangolin::Handler3D(s_cam));

    // Add named Panel and bind to variables beginning 'ui'
    // A Panel is just a View with a default layout and input handling
    CreatePanel("ui").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));
    
    // Safe and efficient binding of named variables.
    // Specialisations mean no conversions take place for exact types
    // and conversions between scalar types are cheap.

    // pangolin::Var<bool> a_button("ui.A_Button",false,false);
    Var<bool> levelup("ui.Level+",false,false);
    // RegisterGuiVarChangedCallback((GuiVarChangedCallbackFn)SPHERE.nextLevel(),nullptr,"ui.Level+");
    Var<bool> save_window("ui.Save_Window",false,false);
    Var<bool> record_cube("ui.Record_Window",false,false);
    Var<bool> save_sphere("ui.Save Sphere",false,false);
    // Demonstration of how we can register a keyboard hook to alter a Var
    // TODO Connect UI Pannel with Control Unit.
    Var<double> zoom("ui.zoom",CTRLELE.zZoom,0,20);
    Var<int> dx("ui.dx",CTRLELE.dx);
    Var<int> dy("ui.dy",CTRLELE.dy);
    // TODO Rotation around the center of Sphere Option.
    // RegisterKeyPressCallback('n',      [&](){SPHERE.nextLevel();});
    RegisterKeyPressCallback(PANGO_SPECIAL + PANGO_KEY_UP,      [&](){CTRLELE.zZoom *= 1.1;});
    RegisterKeyPressCallback(PANGO_SPECIAL + PANGO_KEY_DOWN,    [&](){CTRLELE.zZoom /= 1.1;});
    RegisterKeyPressCallback(PANGO_SPECIAL + PANGO_KEY_LEFT,    [&](){CTRLELE.dx = (CTRLELE.dx+1) % 360;});
    RegisterKeyPressCallback(PANGO_SPECIAL + PANGO_KEY_RIGHT,   [&](){CTRLELE.dy = (CTRLELE.dy-1) % 360;});
    
    // Default hooks for exiting (Esc) and fullscreen (tab).
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width = SPHERE.ptr_tex->tex.cols;
    int height = SPHERE.ptr_tex->tex.rows;
    // int nrChannels = 3;
    // unsigned char *data = ;
    cv::cvtColor(SPHERE.ptr_tex->tex, SPHERE.ptr_tex->tex, CV_RGB2BGR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, SPHERE.ptr_tex->tex.ptr());
    // glGenerateMipmap(GL_TEXTURE_2D);

    while(!ShouldQuit()){
        // clear the screen in every loop.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        // Acitvate efficiently by object
        d_cam.Activate(s_cam);

        if (Pushed(levelup)){
            SPHERE.nextLevel();
        }

        if (Pushed(save_sphere)){
            std::ofstream ofile;
            ofile.open("utils/sphere.txt");
            ofile<<"ptId0,ptId1,ptId2,edge0-1,edge1-2,edge2-0,area"<<endl;
            SPHERE.outputEdgsLength(ofile);
            ofile.close();
        }

        // glColor3f(1.0,1.0,1.0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        RenderScene(CTRLELE,SPHERE);
        // pangolin::glDrawTexture(GL_TEXTURE_2D,EARTHSURFACE);
        // DrawSphere(SPHERE);
        // glDrawColouredCube();
        // std::cout<<ZOOM.Get()<<std::endl;
        glDrawAxis(0.1);
        // texture.RenderToViewport();
        // glDraw_y0(0.1,20);
        // Swap frames and Process Events
        FinishFrame();

    }
    std::cout << "Hello Digital Earth"<< std::endl;
    return 0;
}
