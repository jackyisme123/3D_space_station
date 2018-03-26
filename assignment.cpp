//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: Skybox.cpp
//  See Lab03.pdf for details
//  ========================================================================

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
#include "loadBMP.h"

using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;		//Camera rotation
GLUquadricObj*	q;
GLuint texId[27];

float lgt_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
float angle = -10.0;  //Rotation angle for viewing
float cam_hgt = 300;
float look_x=-0;
float look_z=-115.;  //Camera parameters
float eye_x = 0;
float eye_z = 0;
float sun1_angle = 0.0;
int sun0_angle = 0;
int ring1_height = 490;
int ring2_height = 470;
int ring3_height = 450;
int ring4_height = 430;
int ring5_height = 410;
int direction1 = 0;
int direction2 = 1;
int direction3 = 1;
int direction4 = 1;
int direction5 = 1;
int door_y = -88;
int door_direction = 0;
float light_gray = 0.82745;
float silver = 0.75294;
float dark_gray = 0.662745;
float khaki[3] = {0.9412, 0.9020, 0.5490};
int ship_x = -500;
int ship_y = 700;
int ship_z = -500;
int ship_direction = 0;
int ship_angle=270;
int right_arm_angle = 0;
int left_arm_angle = 0;
int left_arm_direction = 0;
int right_arm_direction = 1;
int wheel_angle = 0;
int earth_angle = 0;
int robot_x=0;
int robot_y = 10;
int robot_z=0;
bool robot_in_house=true;
bool door_open = false;
int robot_direction = 0;
int robot_power = 3;
int robot_speed = 5;
int up_speed =1;
bool spin_over =false;
int robot_angle=0;
int spin_acc = 0;
bool is_spinned = false;
float ring1_1 = 0;
float ring1_2 = 1;
float ring1_3 = 0;
float ring2_1 = 0;
float ring2_2 = 1;
float ring2_3 = 0;
float ring3_1 = 0;
float ring3_2 = 1;
float ring3_3 = 0;
int pole_height = -700;
const int N = 18;		//Number of vertices of the base polygon
int theta = -20;
float PI = 3.1415926;
float ball_theta1 = 0;
float ball_theta2 = 0;
float ball_theta_acceleration = 0.5;
int ball1_direction = 0;
int ball2_direction = 2;
float ball_speed = 0;
int camera_flag = 0;
float look_at_backup[5]={0};
int teapot_angle = 0;


void loadGLTextures()				// Load bitmaps And Convert To Textures
{
	glGenTextures(27, texId); 		// Create texture ids
	// *** left ***
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	loadTGA("left1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	// *** front ***
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	loadTGA("front1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	// *** right ***
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	loadTGA("right1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	// *** back***
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	loadTGA("back1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	// *** top ***
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	loadTGA("top1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	// *** down ***
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	loadTGA("down1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    //sun1
    glBindTexture(GL_TEXTURE_2D, texId[6]);  //Use this texture name for the following OpenGL texture
	loadBMP("Sun.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //sun0
    glBindTexture(GL_TEXTURE_2D, texId[7]);  //Use this texture name for the following OpenGL texture
	loadBMP("sun0.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //wall
    glBindTexture(GL_TEXTURE_2D, texId[8]);  //Use this texture name for the following OpenGL texture
	loadBMP("wall.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //door
    glBindTexture(GL_TEXTURE_2D, texId[9]);  //Use this texture name for the following OpenGL texture
	loadBMP("door.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //stainless
    glBindTexture(GL_TEXTURE_2D, texId[10]);  //Use this texture name for the following OpenGL texture
	loadBMP("stainless.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //earth
    glBindTexture(GL_TEXTURE_2D, texId[11]);  //Use this texture name for the following OpenGL texture
	loadBMP("earth.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // *** road ***
	glBindTexture(GL_TEXTURE_2D, texId[12]);
	loadBMP("road.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);    
    
    //photo
    glBindTexture(GL_TEXTURE_2D, texId[13]);
	loadBMP("startrek1.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    
    glBindTexture(GL_TEXTURE_2D, texId[14]);
	loadBMP("startrek2.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  
    
    glBindTexture(GL_TEXTURE_2D, texId[15]);
	loadBMP("startrek3.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    
    glBindTexture(GL_TEXTURE_2D, texId[16]);
	loadBMP("startrek4.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    
    glBindTexture(GL_TEXTURE_2D, texId[17]);
	loadBMP("startrek5.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texId[18]);
	loadBMP("startrek6.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texId[19]);
	loadBMP("startrek7.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[20]);
	loadBMP("federation.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[21]);
	loadBMP("pic1.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texId[22]);
	loadBMP("pic2.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[23]);
	loadBMP("pic3.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[24]);
	loadBMP("pic4.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[25]);
	loadBMP("starfleet.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, texId[26]);
	loadBMP("klingon.bmp");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    
}

//========================================================================================

void skybox(){
	glEnable(GL_TEXTURE_2D);

  ////////////////////// LEFT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1000,  0, 1000);
  glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0., -1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000., -1000);
  glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 1000, 1000);
  glEnd();

  ////////////////////// FRONT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[1]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1000,  0, -1000);
  glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0., -1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000, -1000);
  glTexCoord2f(0.0, 1.0); glVertex3f(-1000,  1000, -1000);
  glEnd();

 ////////////////////// RIGHT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(1000,  0, -1000);
  glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0, 1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000,  1000);
  glTexCoord2f(0.0, 1.0); glVertex3f(1000,  1000,  -1000);
  glEnd();


  ////////////////////// REAR WALL ////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f( 1000, 0, 1000);
  glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 0,  1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 1000,  1000);
  glTexCoord2f(0.0, 1.0); glVertex3f( 1000, 1000, 1000);
  glEnd();
  
  /////////////////////// TOP //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[4]);
  glBegin(GL_QUADS);
  glTexCoord2f(1.0, 0.0); glVertex3f(-1000, 1000, -1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(1000, 1000,  -1000);
  glTexCoord2f(0.0, 1.0); glVertex3f(1000, 1000,  1000);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1000, 1000, 1000);
  glEnd();
  
  /////////////////////// FLOOR //////////////////////////
  glBindTexture(GL_TEXTURE_2D, texId[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 0., 1000);
  glTexCoord2f(0.0, 0.0); glVertex3f(1000, 0.,  1000);
  glTexCoord2f(1.0, 0.0); glVertex3f(1000, 0., -1000);
  glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 0., -1000);
  glEnd();
  
}





//---------------------------------------------------------------------
void initialise(void) 
{
    float black[4] = {0.0, 0.0, 0.0, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

	q =  gluNewQuadric ( );
	loadGLTextures(); 
    

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glClearColor (0.0, 0.0, 0.0, 0.0);

    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);
	glEnable(GL_COLOR_MATERIAL);
	
	gluQuadricDrawStyle (q, GLU_FILL );
	gluQuadricNormals	(q, GLU_SMOOTH );

	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture (q, GL_TRUE);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(70.0, 1.0, 100.0, 5000.0);   //Perspective projection
}

GLvoid DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)  
{  
    GLfloat vertex[4];   
  
    const GLfloat delta_angle = 2.0*M_PI/num_segments;  
    glBegin(GL_TRIANGLE_FAN);  
  
    vertex[0] = cx;  
    vertex[1] = cy;  
    vertex[2] = cz;  
    vertex[3] = 1.0;          
    glVertex4fv(vertex);  
  
    //draw the vertex on the contour of the circle   
    for(int i = 0; i < num_segments ; i++)  
    {  
        vertex[0] = std::cos(delta_angle*i) * r + cx;  
        vertex[1] = std::sin(delta_angle*i) * r + cy;  
        vertex[2] = cz;  
        vertex[3] = 1.0;  
        glVertex4fv(vertex);  
    }  
  
    vertex[0] = 1.0 * r + cx;  
    vertex[1] = 0.0 * r + cy;  
    vertex[2] = cz;  
    vertex[3] = 1.0;  
    glVertex4fv(vertex);  
    glEnd();  
}

void mySolidCylinder( GLUquadric* quad,  
                     GLdouble base,  
                     GLdouble top,  
                     GLdouble height,  
                     GLint slices,  
                     GLint stacks )  
{  
    gluCylinder(quad, base, top, height, slices, stacks);  
    //top   
    DrawCircleArea(0.0, 0.0, height, top, slices);  
    //base   
    DrawCircleArea(0.0, 0.0, 0.0, base, slices);  
}  


    void drawRing(int inRadius, int outRadius, int height)
{
    glTranslatef(0, height, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(inRadius, outRadius, 15, 15);
    
}


void drawTree()
{
    
    glPushMatrix();//cylinder
      glColor3f(0.0, 0.0, 0.0);
	  glTranslatef(0, 500, 0);
      glRotatef(90, 1, 0, 0);
	  GLUquadric *q1;
      q1 = gluNewQuadric();
      mySolidCylinder(q1, 3, 3, 100, 50, 50);
      gluQuadricDrawStyle(q1, GLU_FILL);
	glPopMatrix(); 
    
    glPushMatrix(); //top
      glRotatef(teapot_angle, 0, 1, 0);
      glTranslatef(0, 500, 0);
      glScalef(10.0, 10.0, 10.0);
      glutSolidTeapot(1);
    glPopMatrix(); 
    
    glPushMatrix(); //ring
      glColor3f(0.85, 0.85, 0.10);
      drawRing(2, 30, ring1_height);      
    glPopMatrix();
    glPushMatrix(); //ring
      glColor3f(0,1,0);
      drawRing(2, 40, ring2_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
      glColor3f(1, 0, 0);
      drawRing(2, 50, ring3_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
      glColor3f(0.90, 0.91, 0.98);
      drawRing(2, 40, ring4_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
      glColor3f(0, 0, 1);
      drawRing(2, 30, ring5_height);      
    glPopMatrix();     
}

void drawShadowTree()
{
    
    glPushMatrix();//cylinder
     // glColor3f(0.0, 0.0, 0.0);
	  glTranslatef(0, 500, 0);
      glRotatef(90, 1, 0, 0);
	  GLUquadric *q1;
      q1 = gluNewQuadric();
      mySolidCylinder(q1, 3, 3, 100, 50, 50);
      gluQuadricDrawStyle(q1, GLU_FILL);
	glPopMatrix(); 
    
    glPushMatrix(); //top
      glRotatef(teapot_angle, 0, 1, 0);
      glTranslatef(0, 500, 0);
      glScalef(10.0, 10.0, 10.0);
      glutSolidTeapot(1);
    glPopMatrix(); 
    
    glPushMatrix(); //ring
     // glColor3f(0.85, 0.85, 0.10);
      drawRing(2, 30, ring1_height);      
    glPopMatrix();
    glPushMatrix(); //ring
    //  glColor3f(0,1,0);
      drawRing(2, 40, ring2_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
    //  glColor3f(1, 0, 0);
      drawRing(2, 50, ring3_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
    //  glColor3f(0.90, 0.91, 0.98);
      drawRing(2, 40, ring4_height);      
    glPopMatrix(); 
    glPushMatrix(); //ring
    //  glColor3f(0, 0, 1);
      drawRing(2, 30, ring5_height);      
    glPopMatrix();     
}

void drawRoad()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[12]);
    glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 1.0); glVertex3f(-50, 1.2, -700);
      glTexCoord2f(0.0, 0.0); glVertex3f(-50, 1, 50);
      glTexCoord2f(1.0, 0.0); glVertex3f(50, 1, 50);
      glTexCoord2f(1.0, 1.0); glVertex3f(50, 1.2, -700);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 1.0); glVertex3f(-50, 1.3, -700);
      glTexCoord2f(0.0, 0.0); glVertex3f(629.29, 1.3, 0);
      glTexCoord2f(1.0, 0.0); glVertex3f(700, 1.3, -70.71);
      glTexCoord2f(1.0, 1.0); glVertex3f(0, 1.3, -770.71);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
      
      glTexCoord2f(1.0, 0.0); glVertex3f(700, 1, -70.71);
      glTexCoord2f(1.0, 1.0); glVertex3f(0, 1, 629.29);
      glTexCoord2f(0.0, 1.0); glVertex3f(70.71, 1, 700);
      glTexCoord2f(0.0, 0.0); glVertex3f(770.71, 1, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(1.0, 0.0); glVertex3f(-700, 1, 70.71);
      glTexCoord2f(1.0, 1.0); glVertex3f(0, 1, 770.71);
      glTexCoord2f(0.0, 1.0); glVertex3f(70.71, 1, 700);
      glTexCoord2f(0.0, 0.0); glVertex3f(-629.29, 1, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 1.0); glVertex3f(-50, 1, -700);
      glTexCoord2f(0.0, 0.0); glVertex3f(-770.71, 1, 0);
      glTexCoord2f(1.0, 0.0); glVertex3f(-700, 1, 70.71);
      glTexCoord2f(1.0, 1.0); glVertex3f(0, 1, -629.29);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
}


float degreeToRadians(int theta)
{
    return (theta)*PI/180;
} 

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void drawChargingTower()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId[12]);
    float vx[N] = {0., 8., 11., 11., 10.4, 9.5, 8., 6., 3., 0., -3., -6., -8., -9.5, -10.4, -11., -11., -8.};
    float vy[N] = {0};
    float vz[N] = {19.4, 8., 5., 0., -4., -8., -11., -12., -12.4, -12.5, -12.4, -12., -11., -8., -4., 0., 5., 8.};
    float wx[N], wy[N], wz[N];
    
   for (int j=0; j<25; j++) 
        {
        glPushMatrix();
        glTranslatef(0, j*20, 0); 
        glRotatef(-20*j, 0, 1, 0); 
        glBegin(GL_QUAD_STRIP);
       
            for(int i = 0; i < N; i++)
                {
                wx[i] = vx[i] * cos(degreeToRadians(theta)) + vz[i] * sin(degreeToRadians(theta));
                wy[i] = vy[i] + 20;
                wz[i] = (-vx[i]) * sin(degreeToRadians(theta)) + vz[i] * cos(degreeToRadians(theta));
                if(i > 0) normal(vx[i-1], vy[i-1], vz[i-1], vx[i], vy[i], vz[i], wx[i], wy[i], wz[i]);
                float si[19] = {0, 0.15,0.2,0.25,0.3,0.35,0.4,0.433,0.467,0.5,0.533,0.567,0.6,0.65,0.7,0.75,0.8,0.85,1};
                glTexCoord2f(si[i], 0.0);
                 glVertex3f(vx[i], vy[i], vz[i]);
                glTexCoord2f(si[i], 1.0);
                 glVertex3f(wx[i], wy[i], wz[i]);
                }
             glTexCoord2f(1.0, 0.0); glVertex3f(vx[0], vy[0], vz[0]);
             glTexCoord2f(1.0, 1.0); glVertex3f(wx[0], wy[0], wz[0]);            
        glEnd();
        glPopMatrix();
        } 
        glDisable(GL_TEXTURE_2D);
}


void drawHouse()
{
    glEnable(GL_TEXTURE_2D);
    ////door
    glPushMatrix();
      glTranslatef(0, door_y, -258.807621);      
        glBindTexture(GL_TEXTURE_2D, texId[9]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 115, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -115, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -115, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 115, -1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 115, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -115, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -115, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 115, 1);
        glEnd(); 
        ////federation
        glBindTexture(GL_TEXTURE_2D, texId[20]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.5); glVertex3f(-120, 115, 1.2);
            glTexCoord2f(0.0, 0.0); glVertex3f(-120, -5, 1.2);
            glTexCoord2f(1.0, 0.0); glVertex3f(120, -5, 1.2);
            glTexCoord2f(1.0, 0.5); glVertex3f(120, 115, 1.2);
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(0, 120, -259.807621);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 100, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -100, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -100, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 100, -1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 100, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -100, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -100, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 100, 1);
        glEnd(); 
        ////federation
        glBindTexture(GL_TEXTURE_2D, texId[20]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-120, 20, 1.2);
            glTexCoord2f(0.0, 0.5); glVertex3f(-120, -100, 1.2);
            glTexCoord2f(1.0, 0.5); glVertex3f(120, -100, 1.2);
            glTexCoord2f(1.0, 1.0); glVertex3f(120, 20, 1.2);
        glEnd();
        
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-150, 0, -259.807621);
      glRotatef(240, 0, 1, 0);
      glTranslatef(150, 0, 0);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, 1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, -1);
        glEnd();
        
        ////pic
        glBindTexture(GL_TEXTURE_2D, texId[21]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.02, 1.0); glVertex3f(-120, 120, -1.2);
            glTexCoord2f(0.02, 0.0); glVertex3f(-120, -20, -1.2);
            glTexCoord2f(1.02, 0.0); glVertex3f(120, -20, -1.2);
            glTexCoord2f(1.02, 1.0); glVertex3f(120, 120, -1.2);
        glEnd();
        
    glPopMatrix();
    glPushMatrix();
      glTranslatef(150, 0, -259.807621);
      glRotatef(120, 0, 1, 0);
      glTranslatef(-150, 0, 0);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, 1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, -1);
        glEnd(); 
        ////pic
        glBindTexture(GL_TEXTURE_2D, texId[23]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.015, 1.0); glVertex3f(-120, 120, -1.2);
            glTexCoord2f(0.015, 0.0); glVertex3f(-120, -20, -1.2);
            glTexCoord2f(1.015, 0.0); glVertex3f(120, -20, -1.2);
            glTexCoord2f(1.015, 1.0); glVertex3f(120, 120, -1.2);
        glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0, 0, 259.807621);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, 1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, -1);
        glEnd();
        ////photo
        
        glBindTexture(GL_TEXTURE_2D, texId[13]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.15, 1.0); glVertex3f(-20, 120, -1.2);
            glTexCoord2f(0.15, 0.0); glVertex3f(-20, 60, -1.2);
            glTexCoord2f(1.15, 0.0); glVertex3f(20, 60, -1.2);
            glTexCoord2f(1.15, 1.0); glVertex3f(20, 120, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[14]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.15, 1.0); glVertex3f(-95, 40, -1.2);
            glTexCoord2f(0.15, 0.0); glVertex3f(-95, -20, -1.2);
            glTexCoord2f(1.15, 0.0); glVertex3f(-55, -20, -1.2);
            glTexCoord2f(1.15, 1.0); glVertex3f(-55, 40, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[15]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.15, 1.0); glVertex3f(55, 40, -1.2);
            glTexCoord2f(0.15, 0.0); glVertex3f(55, -20, -1.2);
            glTexCoord2f(1.15, 0.0); glVertex3f(95, -20, -1.2);
            glTexCoord2f(1.15, 1.0); glVertex3f(95, 40, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[16]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.15, 1.0); glVertex3f(-132.5, -40, -1.2);
            glTexCoord2f(0.15, 0.0); glVertex3f(-132.5, -100, -1.2);
            glTexCoord2f(1.15, 0.0); glVertex3f(-92.5, -100, -1.2);
            glTexCoord2f(1.15, 1.0); glVertex3f(-92.5, -40, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[17]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.2, 1.0); glVertex3f(-57.5, -40, -1.2);
            glTexCoord2f(0.2, 0.0); glVertex3f(-57.5, -100, -1.2);
            glTexCoord2f(1.2, 0.0); glVertex3f(-17.5, -100, -1.2);
            glTexCoord2f(1.2, 1.0); glVertex3f(-17.5, -40, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[18]);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.2, 1.0); glVertex3f(17.5, -40, -1.2);
            glTexCoord2f(0.2, 0.0); glVertex3f(17.5, -100, -1.2);
            glTexCoord2f(1.2, 0.0); glVertex3f(57.5, -100, -1.2);
            glTexCoord2f(1.2, 1.0); glVertex3f(57.5, -40, -1.2);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, texId[19]);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.2, 1.0); glVertex3f(92.5, -40, -1.2);
            glTexCoord2f(0.2, 0.0); glVertex3f(92.5, -100, -1.2);
            glTexCoord2f(1.2, 0.0); glVertex3f(132.5, -100, -1.2);
            glTexCoord2f(1.2, 1.0); glVertex3f(132.5, -40, -1.2);
        glEnd();
        
    glPopMatrix();
    glPushMatrix();
      glTranslatef(-150, 0, 259.807621);
      glRotatef(-240, 0, 1, 0);
      glTranslatef(150, 0, 0);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, -1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, 1);
        glEnd();
        ////pic
        glBindTexture(GL_TEXTURE_2D, texId[22]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.02, 1.0); glVertex3f(-120, 120, 1.2);
            glTexCoord2f(0.02, 0.0); glVertex3f(-120, -20, 1.2);
            glTexCoord2f(1.02, 0.0); glVertex3f(120, -20, 1.2);
            glTexCoord2f(1.02, 1.0); glVertex3f(120, 120, 1.2);
        glEnd();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(150, 0, 259.807621);
      glRotatef(-120, 0, 1, 0);
      glTranslatef(-150, 0, 0);
      glBindTexture(GL_TEXTURE_2D, texId[8]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, -1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, -1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, -1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, -1);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, texId[10]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-150, 200, 1);
            glTexCoord2f(0.0, 0.0); glVertex3f(-150, -200, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(150, -200, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(150, 200, 1);
        glEnd();
        
        ////pic
        glBindTexture(GL_TEXTURE_2D, texId[24]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
        glBegin(GL_QUADS);
            glTexCoord2f(0.03, 1.0); glVertex3f(-120, 120, 1.2);
            glTexCoord2f(0.03, 0.0); glVertex3f(-120, -20, 1.2);
            glTexCoord2f(1.03, 0.0); glVertex3f(120, -20, 1.2);
            glTexCoord2f(1.03, 1.0); glVertex3f(120, 120, 1.2);
        glEnd();
    glPopMatrix();
    glPushMatrix();//EARTH LIGHT
        glRotatef(earth_angle, 0.0, -1.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, texId[11]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTranslatef(0, 175, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
        GLUquadricObj*	q;        
        q =  gluNewQuadric ( );
        gluQuadricTexture (q, GL_TRUE);
         gluSphere(q, 20, 40, 40);
         gluQuadricDrawStyle (q, GLU_FILL );
        gluQuadricNormals	(q, GLU_SMOOTH );
    glPopMatrix();
    
       
    glDisable(GL_TEXTURE_2D);
    ////ROOF
    glPushMatrix();
      glColor3f(1, 1, 1);
      glTranslatef(0, 200, 0);
      glRotatef(-90, 1, 0, 0);
      glutSolidCone(350, 150, 50, 50);      
    glPopMatrix();
    
    ////charing tower
    glPushMatrix();
        glTranslatef(0, pole_height, 0);
        drawChargingTower();
    glPopMatrix();
    
    ////physical model
    
    //holder
    glPushMatrix();
    glTranslatef(0, -60, 250);
    glPushMatrix();
        glTranslatef(0, 100, 0);
        glScalef(3, 3, 3);
        glutSolidIcosahedron();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 100, 0);
        glRotatef(ball_theta1, 0, 0, 1);
        glTranslatef(0, -100, 0);
        glPushMatrix();    
        //line
        glColor4f(1, 1, 1, 1);
        glBegin(GL_LINES);
        glVertex3f(0,50,0);
        glVertex3f(0,100,0);
        glEnd();
        //ball
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[25]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTranslatef(0, 50, 0);
        glRotatef(-180, 0, 1, 0);
        glRotatef(-90, 1, 0, 0);
        GLUquadricObj*	q_ball1;        
        q_ball1 =  gluNewQuadric ( );
        gluQuadricTexture (q_ball1, GL_TRUE);
         gluSphere(q_ball1, 5, 40, 40);
         gluQuadricDrawStyle (q_ball1, GLU_FILL );
        gluQuadricNormals	(q_ball1, GLU_SMOOTH );
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 100, 0);
        glRotatef(ball_theta2, 0, 0, 1);
        glTranslatef(0, -100, 0);
        glPushMatrix(); 
        //line
        glColor4f(1, 1, 1, 1);
        glBegin(GL_LINES);
        glVertex3f(50,100,0);
        glVertex3f(0,100,0);
        glEnd();
        //ball
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId[26]);
        glTranslatef(50, 100, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(180, 0, 1, 0);
        glRotatef(-135, 1, 0, 0);
        GLUquadricObj*	q_ball2;        
        q_ball2 =  gluNewQuadric ( );
        gluQuadricTexture (q_ball2, GL_TRUE);
         gluSphere(q_ball2, 5, 40, 40);
         gluQuadricDrawStyle (q_ball2, GLU_FILL );
        gluQuadricNormals	(q_ball2, GLU_SMOOTH );
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPopMatrix();
    glPopMatrix();
    
    
    
    
      
}

void drawShadowSpaceship()
{
    ////body
    
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glPushMatrix();
          //glColor3f(light_gray, light_gray, light_gray);            
          glutSolidSphere(20, 20, 20);
        glPopMatrix();
        
        
       // glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
          GLUquadric *q1;
          q1 = gluNewQuadric();
          mySolidCylinder(q1, 100, 100, 3, 20, 20);
          gluQuadricDrawStyle(q1, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 2);
          GLUquadric *q2;
          q2 = gluNewQuadric();
          mySolidCylinder(q2, 100, 96, 3, 20, 20);
          gluQuadricDrawStyle(q2, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -2);
          GLUquadric *q3;
          q3 = gluNewQuadric();
          mySolidCylinder(q3, 96, 100, 3, 20, 20);
          gluQuadricDrawStyle(q3, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 4);
          GLUquadric *q4;
          q4 = gluNewQuadric();
          mySolidCylinder(q4, 96, 92, 3, 20, 20);
          gluQuadricDrawStyle(q4, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -4);
          GLUquadric *q5;
          q5 = gluNewQuadric();
          mySolidCylinder(q5, 92, 96, 3, 20, 20);
          gluQuadricDrawStyle(q5, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 6);
          GLUquadric *q6;
          q6 = gluNewQuadric();
          mySolidCylinder(q6, 92, 88, 3, 20, 20);
          gluQuadricDrawStyle(q6, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -6);
          GLUquadric *q7;
          q7 = gluNewQuadric();
          mySolidCylinder(q7, 88, 92, 3, 20, 20);
          gluQuadricDrawStyle(q7, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 8);
          GLUquadric *q8;
          q8 = gluNewQuadric();
          mySolidCylinder(q8, 88, 84, 3, 20, 20);
          gluQuadricDrawStyle(q8, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -8);
          GLUquadric *q9;
          q9 = gluNewQuadric();
          mySolidCylinder(q9, 84, 88, 3, 20, 20);
          gluQuadricDrawStyle(q9, GLU_FILL);  
        glPopMatrix();
        glPushMatrix();
          glTranslatef(0, 0, 10);
          GLUquadric *q10;
          q10 = gluNewQuadric();
          mySolidCylinder(q10, 84, 80, 3, 20, 20);
          gluQuadricDrawStyle(q10, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -10);
          GLUquadric *q11;
          q11 = gluNewQuadric();
          mySolidCylinder(q11, 80, 84, 3, 20, 20);
          gluQuadricDrawStyle(q11, GLU_FILL);  
        glPopMatrix();
    glPopMatrix();
    ////tail
    glPushMatrix();
      glTranslatef(0, -15, 80);
          glPushMatrix();
              glScalef(5, 20, 5);
              glutSolidCube(1);
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, 0);                       
              glRotatef(-90, 0, 1, 0); 
              GLUquadric *q12;
              q12 = gluNewQuadric();
              mySolidCylinder(q12, 5, 5, 60, 20, 20);
              gluQuadricDrawStyle(q12, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, -10);
              GLUquadric *q13;
              q13 = gluNewQuadric();
              mySolidCylinder(q13, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(q13, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, -10);
              GLUquadric *q14;
              q14 = gluNewQuadric();
              mySolidCylinder(q14, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(q14, GLU_FILL); 
          glPopMatrix();
          
          glPushMatrix();
              glTranslatef(30, -10, 20);
              GLUquadric *q15;
              q15 = gluNewQuadric();
              mySolidCylinder(q15, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(q15, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, 20);
              GLUquadric *q16;
              q16 = gluNewQuadric();
              mySolidCylinder(q16, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(q16, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          
          
    glPopMatrix();
    
    
}

void drawSpaceship()
{
    ////body
    
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glPushMatrix();
          glColor3f(light_gray, light_gray, light_gray);            
          glutSolidSphere(20, 20, 20);
        glPopMatrix();
        
        
        glColor3f(0.5, 0.5, 0.5);
        glPushMatrix();
          GLUquadric *q1;
          q1 = gluNewQuadric();
          mySolidCylinder(q1, 100, 100, 3, 20, 20);
          gluQuadricDrawStyle(q1, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 2);
          GLUquadric *q2;
          q2 = gluNewQuadric();
          mySolidCylinder(q2, 100, 96, 3, 20, 20);
          gluQuadricDrawStyle(q2, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -2);
          GLUquadric *q3;
          q3 = gluNewQuadric();
          mySolidCylinder(q3, 96, 100, 3, 20, 20);
          gluQuadricDrawStyle(q3, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 4);
          GLUquadric *q4;
          q4 = gluNewQuadric();
          mySolidCylinder(q4, 96, 92, 3, 20, 20);
          gluQuadricDrawStyle(q4, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -4);
          GLUquadric *q5;
          q5 = gluNewQuadric();
          mySolidCylinder(q5, 92, 96, 3, 20, 20);
          gluQuadricDrawStyle(q5, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 6);
          GLUquadric *q6;
          q6 = gluNewQuadric();
          mySolidCylinder(q6, 92, 88, 3, 20, 20);
          gluQuadricDrawStyle(q6, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -6);
          GLUquadric *q7;
          q7 = gluNewQuadric();
          mySolidCylinder(q7, 88, 92, 3, 20, 20);
          gluQuadricDrawStyle(q7, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, 8);
          GLUquadric *q8;
          q8 = gluNewQuadric();
          mySolidCylinder(q8, 88, 84, 3, 20, 20);
          gluQuadricDrawStyle(q8, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -8);
          GLUquadric *q9;
          q9 = gluNewQuadric();
          mySolidCylinder(q9, 84, 88, 3, 20, 20);
          gluQuadricDrawStyle(q9, GLU_FILL);  
        glPopMatrix();
        glPushMatrix();
          glTranslatef(0, 0, 10);
          GLUquadric *q10;
          q10 = gluNewQuadric();
          mySolidCylinder(q10, 84, 80, 3, 20, 20);
          gluQuadricDrawStyle(q10, GLU_FILL);  
        glPopMatrix();
        
        glPushMatrix();
          glTranslatef(0, 0, -10);
          GLUquadric *q11;
          q11 = gluNewQuadric();
          mySolidCylinder(q11, 80, 84, 3, 20, 20);
          gluQuadricDrawStyle(q11, GLU_FILL);  
        glPopMatrix();
    glPopMatrix();
    ////tail
    glPushMatrix();
      glTranslatef(0, -15, 80);
          glPushMatrix();
              glScalef(5, 20, 5);
              glutSolidCube(1);
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, 0);                       
              glRotatef(-90, 0, 1, 0); 
              GLUquadric *q12;
              q12 = gluNewQuadric();
              mySolidCylinder(q12, 5, 5, 60, 20, 20);
              gluQuadricDrawStyle(q12, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, -10);
              GLUquadric *q13;
              q13 = gluNewQuadric();
              mySolidCylinder(q13, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(q13, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, -10);
              GLUquadric *q14;
              q14 = gluNewQuadric();
              mySolidCylinder(q14, 6, 6, 30, 20, 20);
              gluQuadricDrawStyle(q14, GLU_FILL); 
          glPopMatrix();
          
          glPushMatrix();
              glTranslatef(30, -10, 20);
              GLUquadric *q15;
              q15 = gluNewQuadric();
              mySolidCylinder(q15, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(q15, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, 20);
              GLUquadric *q16;
              q16 = gluNewQuadric();
              mySolidCylinder(q16, 10, 10, 10, 20, 20);
              gluQuadricDrawStyle(q16, GLU_FILL); 
          glPopMatrix();
          glPushMatrix();
              glTranslatef(30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, 30);
              glutSolidTorus(2, 10, 20,20);
          glPopMatrix();
          
          float lgt_pos1[] = {0.0f, 0.0f, 2.0f, 1.0f};
          
          
          glColor3f(1, 0.5, 0); 
          glPushMatrix();
              glTranslatef(30, -10, 31);
              glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);   //light position            
                glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);
                glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01); 
              GLUquadric *q17;
              q17 = gluNewQuadric();
              gluDisk(q17, 0, 8, 10, 10);
              gluQuadricDrawStyle(q17, GLU_FILL);
          glPopMatrix();
          glPushMatrix();
              glTranslatef(-30, -10, 31);
              glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);   //light position            
                glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);
                glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01); 
              GLUquadric *q18;
              q18 = gluNewQuadric();
              gluDisk(q18, 0, 8, 10, 10);
              gluQuadricDrawStyle(q18, GLU_FILL);
          glPopMatrix();
          
          
    glPopMatrix();
    
    
}

void drawWheel()
{
      ////wheel
    
    glColor3f(0, 0, 0); 
    glPushMatrix();
        glutSolidTorus(2, 5, 20, 20);
    glPopMatrix();
    glColor3f(1, 1, 1);
    glPushMatrix();
        glTranslatef(0, 0, 2);
        GLUquadric *q1;
        q1= gluNewQuadric();
        gluDisk(q1, 0, 5, 20, 20);
        gluQuadricDrawStyle(q1, GLU_FILL);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 0, -2);
        GLUquadric *q2;
        q2= gluNewQuadric();
        gluDisk(q2, 0, 5, 20, 20);
        gluQuadricDrawStyle(q2, GLU_FILL);
    glPopMatrix();  
}

void drawArm()
{
    glPushMatrix();   
        glColor3f(1, 1, 1);     
        glutSolidSphere(3, 20, 20); 
        glRotatef(90, 0, 0, 1);
        glPushMatrix();
            glTranslatef(0, -10, 0);
            glRotatef(-90, 1, 0, 0);
            GLUquadric *q8;
            q8= gluNewQuadric();
            gluCylinder(q8, 2, 2, 10, 20, 20);
            gluQuadricDrawStyle(q8, GLU_FILL);
        glPopMatrix();
        glPushMatrix();//finger
            glTranslatef(0, -10, 0);
            glutSolidSphere(3, 20, 20);            
            glColor3f(0, 0, 0);
            glPushMatrix();            
                glTranslatef(2, -3, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(3, -3.5, 0);                
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(3, -4, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(3, -4.5, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(2, -5, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();            
                glTranslatef(-2, -3, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-3, -3.5, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-3, -4, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);;
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-3, -4.5, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-2, -5, 0);
                glRotatef(-90, 1, 0, 0);
                glutSolidTorus(0.5, 0.5, 10, 10);
            glPopMatrix();
           
        glPopMatrix();
    glPopMatrix();
}

void drawRobot()
{    
    ////bottom
    glColor3f(1, 1, 1);
    glPushMatrix();
        glTranslatef(0, 0, -10);
        GLUquadric *q1;
        q1= gluNewQuadric();
        gluCylinder(q1, 2, 2, 20, 20, 20);
        gluQuadricDrawStyle(q1, GLU_FILL);
    glPopMatrix();
    
    glPushMatrix();
        glRotatef(wheel_angle, 0, 0, 1);
        glPushMatrix();
            glTranslatef(0, 0, -10);
            drawWheel();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, 0, 10);
            drawWheel();
        glPopMatrix();
    glPopMatrix();
    ////body
    glPushMatrix();
        glRotatef(-90, 1, 0, 0); 
        GLUquadric *q2;
        q2= gluNewQuadric();
        gluCylinder(q2, 4, 4, 8, 30, 30);
        gluQuadricDrawStyle(q2, GLU_FILL);
    glPopMatrix(); 
    glPushMatrix();
        glTranslatef(0, 8, 0);
        glPushMatrix();
            glTranslatef(0, 12, 0);
            glRotatef(-90, 1, 0, 0);
            GLUquadric *q5;
            q5= gluNewQuadric();
            gluDisk(q5, 0, 8, 20, 20);
            gluQuadricDrawStyle(q5, GLU_FILL); 
        glPopMatrix();
        glColor3f(ring1_1, ring1_2, ring1_3);
        glPushMatrix();
            drawRing(1, 5, -6);
        glPopMatrix(); 
        glColor3f(ring2_1, ring2_2, ring2_3);
        glPushMatrix();
            drawRing(1, 5, -4);
        glPopMatrix(); 
        glColor3f(ring3_1, ring3_2, ring3_3);
        glPushMatrix();
            drawRing(1, 5, -2);
        glPopMatrix(); 
        glColor3f(1, 1, 1);        
        glRotatef(-90, 1, 0, 0);
        GLUquadric *q3;
        q3= gluNewQuadric();
        gluDisk(q3, 0, 8, 20, 20);
        gluQuadricDrawStyle(q3, GLU_FILL); 
        GLUquadric *q4;
        q4= gluNewQuadric();
        gluCylinder(q4, 8, 8, 12, 30, 30);
        gluQuadricDrawStyle(q4, GLU_FILL);        
    glPopMatrix();
    ////neck
    glPushMatrix();
        glColor3f(0, 0, 0);
        for (int i=1; i<=5; i+=2)
        {
            glPushMatrix();
            glTranslatef(0, 20+i, 0);
           // glRotatef(-90, 1, 0, 0);
            drawRing(1, 3, 0);
            glPopMatrix();          
        }
    glPopMatrix();
    ////head
    glColor3f(khaki[0], khaki[1], khaki[2]);
    glPushMatrix();
        glTranslatef(0, 25, 0);
        glScalef(8, 4.0, 12.0);
        glutSolidCube(1);
    glPopMatrix();
    glColor3f(0.529, 0.808, 0.922);
    glPushMatrix();
        glTranslatef(6, 25, 3);        
        glRotatef(-90, 0, 1, 0);
        GLUquadric *q6;
        q6= gluNewQuadric();
        gluDisk(q6, 0, 1, 20, 20);
        gluQuadricDrawStyle(q6, GLU_FILL); 
    glPopMatrix(); 
    glPushMatrix();
        glTranslatef(6, 25, -3);        
        glRotatef(-90, 0, 1, 0);
        GLUquadric *q7;
        q7= gluNewQuadric();
        gluDisk(q7, 0, 1, 20, 20);
        gluQuadricDrawStyle(q7, GLU_FILL); 
    glPopMatrix(); 
    glColor3f(1, 0.4, 0.1);
    glPushMatrix();
        glTranslatef(5, 25, -3);        
        glRotatef(-90, 0, 1, 0);
        glutSolidTorus(1, 2, 20, 20); 
    glPopMatrix();
    glPushMatrix();
        glTranslatef(5, 25, 3);        
        glRotatef(-90, 0, 1, 0);
        glutSolidTorus(1, 2, 20, 20); 
    glPopMatrix();
    ////arm
    glColor3f(1, 1, 1);
    
    //right arm
    glPushMatrix();
        glTranslatef(0, 15, 10.5);
        glRotatef(right_arm_angle, 0, 0, 1);
        drawArm();
    glPopMatrix();
    //left arm
    glPushMatrix();
        glTranslatef(0, 15, -10.5);
        glRotatef(left_arm_angle, 0, 0, 1); 
        drawArm();
    glPopMatrix();
       
}

//---------------------------------------------------------------------
void display(void)
{
	float shadowMat[16] ={900,0,0,0,0,0,0,-1,0,0,900,0,0,0,0,900};
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye_x, cam_hgt, eye_z, look_x, 300, look_z, 0, 1, 0);  //camera rotation
    //gluLookAt (ship_x, ship_y, ship_z, 0, 300, 0, 0, 1, 0);  //camera rotation      
    glColor4f(1.0, 1.0, 1.0, 1.0);
    
    //Sun1
	glBindTexture(GL_TEXTURE_2D, texId[6]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	glPushMatrix();	
        glRotatef(sun1_angle, 0.0, -1.0, 0.0);
        glTranslatef(300.0, 900.0, 0.0);
	    glRotatef(-90., 1.0, 0., 0.0);   //make the sphere axis vertical
        glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	    gluSphere ( q, 16.0, 144, 68 );
    glPopMatrix();

    ////Sun0
	glBindTexture(GL_TEXTURE_2D, texId[7]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	glPushMatrix();	
        glTranslatef(0.0, 900.0, 0.0);
        glRotatef(sun0_angle, 0, 1, 0);
	    glRotatef(-90., 1.0, 0., 0.0);   //make the sphere axis vertical
        glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos);
	    gluSphere ( q, 48.0, 412, 204 );
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
    ////tree
    //shadow
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(-500.0, -350, 600.0);
        glColor4f(0.1, 0.1, 0.1, 0.1); 
        drawShadowTree();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    //tree
    glPushMatrix();	
    glTranslatef(-500.0, -300, 600.0);
    drawTree();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(600.0, -300, 300.0);
        glColor4f(0.1, 0.1, 0.1, 0.1); 
        drawShadowTree();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPushMatrix();	    
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(600.0, -300, 300.0);
    drawTree();
    glPopMatrix();
    
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(-300.0, -300, -700.0);
        glColor4f(0.1, 0.1, 0.1, 0.1); 
        drawShadowTree();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPushMatrix();	    
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-300.0, -300, -700.0);
    drawTree();
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
   //draw house
    glPushMatrix();	
    glTranslatef(0.0, 200.0, 0.0);
    drawHouse();
    glPopMatrix();
    
    //draw road
    glPushMatrix();
 
    drawRoad();
    glPopMatrix();
    
   // draw spaceship
   glDisable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(0, 2, 0);
        glMultMatrixf(shadowMat);
        glTranslatef(ship_x, 0, ship_z);
        glColor4f(0.1, 0.1, 0.1, 0.1);         	    
        glRotatef(ship_angle, 0, 1, 0);
        drawShadowSpaceship();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(ship_x, ship_y, ship_z);    	    
    glRotatef(ship_angle, 0, 1, 0);
    drawSpaceship();
    glPopMatrix();
    
    //draw robot
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(robot_x, robot_y, robot_z);
    glRotatef(robot_angle, 0, 1, 0);
    drawRobot();
    glPopMatrix();
    
    
    //draw sky box
    glPushMatrix();
	skybox();
    glPopMatrix();
    
    
    
	glutSwapBuffers();
}

//--------------------------------------------------------------
 void special(int key, int x, int y)
 {
	if(key == GLUT_KEY_LEFT) lookAngle -= 0.1;  //Change direction
	else if(key == GLUT_KEY_RIGHT) lookAngle += 0.1;
	else if(key == GLUT_KEY_DOWN)
	{ //Move backward
		eye_x -= 5*sin(lookAngle);
		eye_z += 5*cos(lookAngle);
	}
	else if(key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 5*sin(lookAngle);
		eye_z -= 5*cos(lookAngle);
	}
    else if(key == GLUT_KEY_F1)
    {
        printf("%d %d\n", ball1_direction, ball2_direction);
        if(camera_flag == 0)
        {
            look_at_backup[0] = eye_x;
            look_at_backup[1] = cam_hgt;
            look_at_backup[2] =eye_z;
            look_at_backup[3] =look_x;
            look_at_backup[4] =look_z;            
            camera_flag = 1;
        }
        else
        {
            eye_x=look_at_backup[0];
            cam_hgt = look_at_backup[1];
            eye_z = look_at_backup[2];
            look_x = look_at_backup[3];
            look_z = look_at_backup[4];
            camera_flag = 0;
        }
    }

	look_x = eye_x + 100*sin(lookAngle);
	look_z = eye_z - 100*cos(lookAngle);
    
    if(eye_x >= 850) eye_x=850;
    else if(eye_x <= -850) eye_x=-850;
    if(eye_z >=850) eye_z=850;
    else if(eye_z<=-850) eye_z=-850;
    
    
	glutPostRedisplay();
}
//-------------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if(button == 3) cam_hgt+=5;
	else if(button == 4) cam_hgt-=5;
	if(cam_hgt > 1000) cam_hgt = 1000;
	else if(cam_hgt < 0) cam_hgt = 0;
    glutPostRedisplay();
    
}

void timer(int value)
{   

    if(camera_flag == 1)
    {
        eye_x=ship_x;
        cam_hgt = ship_y;
        eye_z = ship_z;
        look_x = 0;
        look_z = 0;
    } 
    //~ else
    //~ {
        //~ eye_x=look_at_backup[0];
        //~ cam_hgt = look_at_backup[1];
        //~ eye_z = look_at_backup[2];
        //~ look_x = look_at_backup[3];
        //~ look_z = look_at_backup[4];
    //~ }
    
    //printf("%f %f %f %d %d\n", ball_theta1, ball_theta2, ball_speed, ball1_direction, ball2_direction);
    sun0_angle += 2;
    earth_angle ++;
    if(sun0_angle>360) sun0_angle=0;
    sun1_angle += 0.5;
    if(ship_x == -500 && ship_z == -500)
    {
        ship_direction = 0;
        ship_angle=270;
    } 
    else if(ship_x==500&&ship_z==-500)
    {
        ship_direction = 1;
        ship_angle=180;
    }
    else if(ship_x==500&&ship_z==500)
    {
        ship_direction = 2;
        ship_angle=90;
    }
    else if(ship_x==-500&&ship_z==500)
    {
        ship_direction = 3;
        ship_angle=0;
    }
    
    if(ship_direction == 0) 
    {
       ship_x+=5; 
       ship_y+=1;
    }
    else if(ship_direction == 1) 
    {
       ship_z+=5; 
       ship_y-=1;
    }
    else if(ship_direction == 2) 
    {
       ship_x-=5; 
       ship_y-=1;
    }
    else if(ship_direction == 3) 
    {
       ship_z-=5; 
       ship_y+=1;
    }
    
    
    if(ring1_height>=490) direction1 = 1;
    else if(ring1_height<=410) direction1 = 0;
    if(ring2_height>=490) direction2 = 1;
    else if(ring2_height<=410) direction2 = 0;
    if(ring3_height>=490) direction3 = 1;
    else if(ring3_height<=410) direction3 = 0;
    if(ring4_height>=490) direction4 = 1;
    else if(ring4_height<=410) direction4 = 0;
    if(ring5_height>=490) direction5 = 1;
    else if(ring5_height<=410) direction5 = 0;
    
    if(direction1 == 1) ring1_height -= 3;
    else ring1_height +=3;
    if(direction2 == 1) ring2_height -= 2;
    else ring2_height +=2;
    if(direction3 == 1) ring3_height -= 1;
    else ring3_height +=1;
    if(direction4 == 1) ring4_height -= 2;
    else ring4_height +=2;
    if(direction5 == 1) ring5_height -= 3;
    else ring5_height +=3;
    
    if((robot_x<=160 || robot_x >=360) && robot_z==0) door_direction = 1;
    else if((robot_x>=160 && robot_x <=360) && robot_z==0) door_direction = 0;
    
    if (door_direction ==0 && door_y<=100) door_y += 2;
    else if(door_direction ==1 && door_y>=-88) door_y -= 2;
    
    if(left_arm_angle >=30) left_arm_direction = 1;
    else if(left_arm_angle <= -30) left_arm_direction = 0;
    if(right_arm_angle>=30) right_arm_direction = 1;
    else if(right_arm_angle <= -30) right_arm_direction =0;
    if(left_arm_direction==0) left_arm_angle += 2;
    else if(left_arm_direction==1 ) left_arm_angle-= 2;
    if(right_arm_direction==0) right_arm_angle += 2;
    else if(right_arm_direction==1) right_arm_angle-=2;
    wheel_angle ++;
    
    if (robot_x == 0 && robot_z == 0 && robot_y == 10) 
    {
        if(robot_power==3) robot_direction =1; //E 
        else robot_direction = 7; //UP
    } 
    else if(robot_x == 700 && robot_z ==0)
    {
        if(robot_power==3) robot_direction =2; //NW
        else robot_direction = 6; //W  
    }
    else if(robot_x == 0 && robot_z == 700) robot_direction = 3; //SW
    else if(robot_x == -700 && robot_z ==0) robot_direction = 4; //SE
    else if(robot_x == 0 && robot_z == -700) robot_direction =5; //NE
    else if (robot_y == 200 && spin_over) robot_direction =8; //DOWN
    
    if(robot_direction == 1) 
    {
        robot_x += robot_speed;
        spin_over = false;
        is_spinned = false;
    }
    else if(robot_direction == 2) 
    {
        robot_angle = 225;
        robot_x -= robot_speed;
        robot_z += robot_speed;
    }
    else if(robot_direction == 3)
    {
        robot_angle = 135;
        robot_x -= robot_speed;
        robot_z -= robot_speed;
        robot_power = 2;
    }
    else if(robot_direction == 4)
    {
        robot_angle = 45;
        robot_x+=robot_speed;
        robot_z-=robot_speed;
        
    }
    else if(robot_direction == 5)
    {
        robot_angle = -45;
        robot_x+=robot_speed;
        robot_z+=robot_speed;
        robot_power = 1;
    }
    else if(robot_direction == 6)
    {
        robot_angle = 180;
        robot_x -=robot_speed;
        robot_power = 0;
    }
    else if(robot_direction ==7)
    {
        robot_y += up_speed;
        pole_height+= up_speed;
        if(pole_height >= -510)
        {
            pole_height =-510;
        }
        if(robot_y>=200) 
        {
            robot_y=200;
            robot_angle += spin_acc;
            if(spin_acc <=100 && !is_spinned) spin_acc+=3;
            if(robot_angle >= 10000)
            {  
                is_spinned = true;              
                robot_angle+=spin_acc;
                spin_acc -=3;
                
            }
            if(spin_acc == 0) 
                {
                    robot_angle = 0;
                    spin_over = true;
                }
        }
        if (robot_angle > 12000) robot_power =3;
        else if (robot_angle > 10000) robot_power =2;
        else if(robot_angle>5000) robot_power =1;
        
        
        
    }
    else if(robot_direction ==8)
    {
        robot_power = 3;
        robot_y-=up_speed;
        pole_height -= up_speed;
        if(robot_y<=10) robot_y=10;
        if(pole_height<=-700) pole_height = -700;
    }
    
    if (robot_power ==3) 
    {
        ring1_1 = 0;
        ring1_2 = 1;
        ring1_3 = 0;
        ring2_1 = 0;
        ring2_2 = 1;
        ring2_3 = 0;
        ring3_1 = 0;
        ring3_2 = 1;
        ring3_3 = 0;        
    }
    else if (robot_power ==2) 
    {
        ring1_1 = 0;
        ring1_2 = 1;
        ring1_3 = 0;
        ring2_1 = 0;
        ring2_2 = 1;
        ring2_3 = 0;
        ring3_1 = 1;
        ring3_2 = 0;
        ring3_3 = 0;        
    }
    else if (robot_power ==1) 
    {
        ring1_1 = 0;
        ring1_2 = 1;
        ring1_3 = 0;
        ring2_1 = 1;
        ring2_2 = 0;
        ring2_3 = 0;
        ring3_1 = 1;
        ring3_2 = 0;
        ring3_3 = 0;        
    }
    else if (robot_power ==0) 
    {
        ring1_1 = 1;
        ring1_2 = 0;
        ring1_3 = 0;
        ring2_1 = 1;
        ring2_2 = 0;
        ring2_3 = 0;
        ring3_1 = 1;
        ring3_2 = 0;
        ring3_3 = 0;        
    }
    
    if (ball_theta1 == 0 && ball_theta2 == -90 && ball1_direction ==0 && ball2_direction==2) ball1_direction = 1;//up
    else if(ball_theta1 == 0 && ball_theta2 != -90) ball1_direction = 0;//stop
    else if(ball_theta1 == -90 && ball_theta2 ==-90) 
    {
        ball1_direction = 2;//down
        ball_speed = 0;
    }
    
    if(ball_theta2 == -90 && ball_theta1 ==0 && ball2_direction ==0 && ball1_direction ==2) ball2_direction = 1;//up
    else if(ball_theta2 ==-90 && ball_theta1 !=0) ball2_direction =0;//stop
    else if(ball_theta2==0 && ball_theta1==0) 
    {
        ball2_direction =2;//down
        ball_speed = 0;
    }
    
    if (ball_theta1 <=-90) ball_theta1=-90;
    else if(ball_theta1>=0) ball_theta1 =0;
    if(ball_theta2<=-90) ball_theta2 =-90;
    else if(ball_theta2>=0) ball_theta2=0;
        
    if(ball1_direction ==1)
    {        
        
        ball_speed -= ball_theta_acceleration;
        ball_theta1 -= ball_speed;
        if (ball_theta1 <=-90) ball_theta1=-90;
    }
    else if(ball1_direction == 2)
    {
        ball_speed += ball_theta_acceleration;
        ball_theta1 += ball_speed;
        if(ball_theta1>=0) ball_theta1 =0;
    }
    if(ball2_direction ==1)
    {
        ball_speed -= ball_theta_acceleration;
        ball_theta2 += ball_speed;
        if(ball_theta2>=0) ball_theta2=0;
    }
    else if(ball2_direction == 2)
    {       
        ball_speed += ball_theta_acceleration;
        ball_theta2 -= ball_speed;
        if (ball_theta2<=-90) ball_theta2 =-90;
        
    }
    
    teapot_angle +=5;
    if (teapot_angle == 360) teapot_angle = 0;     
    
	glutTimerFunc(50, timer, value);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize (700, 700); 
   glutInitWindowPosition (50, 50);

   glutCreateWindow ("Space Station");
   initialise();
   glutDisplayFunc(display); 
   glutSpecialFunc(special);
   glutMouseFunc(mouse);
   glutTimerFunc(50, timer, 0);
   glutMainLoop();
   return 0;
}
