#include <iostream>
#include <fstream>
#include <climits>
#include <GL/freeglut.h>
#include <cmath>
#include <array>
#include "legoman.h"
#include "skybox.h"
#include "conveyor.h"
#include "particles.h"
#include "gear.h"

#define _USE_MATH_DEFINES
using namespace std;


float startTime;
float elapsedTime;

bool wireframeMode = false; // true whem in wireframe mode

float phi = 0;	//tilt angle of camera
float theta = -M_PI/2; // pan angle of camera

float cam_x = 0; // position of camera
float cam_y = 0;
float cam_z = 150;

float look_x; // position of point the camera is looking at
float look_y;
float look_z;

const float CAMERA_BOX = 200;

void updateCamera(void){
	look_x = 100*cos(theta)+ cam_x; // need to update position of the point that the camera is looking at
	look_y = 100*sin(phi)+cam_y;
	look_z = 100*sin(theta)+cam_z;
}

void timer(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME); // Time in milliseconds
    elapsedTime = (currentTime - startTime) / 1000.0f; // Convert to seconds
	updatePaintQueue(elapsedTime);
	updateFireQueue(elapsedTime);
	// spotlights(elapsedTime);
    glutPostRedisplay(); 
    glutTimerFunc(16, timer, 0);
}

void special(int key, int x, int y) { // handdles special key actions that control where the camera looks
	if 		(key == GLUT_KEY_LEFT) 	theta-= 0.1; // left and right
	else if (key == GLUT_KEY_RIGHT) theta+= 0.1;
	else if (key == GLUT_KEY_UP) 	phi+= 0.1; // look up and down
	else if (key == GLUT_KEY_DOWN) 	phi-= 0.1;
	theta = fmod(theta, 2*M_PI);
	phi = fmod(phi, 2*M_PI);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){ // handles keyboard callbacks for camera movement and wireframe
	float temp_x = cam_x;
	float temp_y = cam_y;
	float temp_z = cam_z;

	if (key == 'w'){
		cam_x += cos(theta);
		cam_z += sin(theta);
	} else if (key == 's'){
		cam_x -= cos(theta);
		cam_z -= sin(theta);
	} else if (key == 'a'){
		cam_x += sin(theta);
		cam_z -= cos(theta);
	} else if (key == 'd'){
		cam_x -= sin(theta);
		cam_z += cos(theta);
	} else if (key == ' '){
		cam_y++;
	} else if (key == 'z'){
		cam_y--;
	} else if (key == 'q'){
		if (wireframeMode){
			wireframeMode = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_LIGHTING);
		} else{
			wireframeMode = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_LIGHTING);
		}
	} else if (key == 'r'){
		cam_x = 0;
		cam_y = 0;
		cam_z = 150;
		phi = 0;
		theta = -M_PI/2;
	}
	if (abs(cam_x) > CAMERA_BOX){
		cam_x = temp_x;
	}
	if (abs(cam_y) > CAMERA_BOX ) {
		cam_y = temp_y;
	}
	if (abs(cam_z) > CAMERA_BOX) {
		cam_z = temp_z;
	}


	glutPostRedisplay();
}



void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	updateCamera();
	gluLookAt(cam_x, cam_y, cam_z, look_x, look_y, look_z, 0., 1., 0.);

	glDepthMask(GL_FALSE);
	drawSkySphere(1000, 40,40);
	glDepthMask(GL_TRUE);
	
	glPushMatrix();
		glTranslatef(-0.5*STRAIGHT_LENGTH, 0.5*DROP_HEIGHT,-0.5*SPIRAL_WIDTH);
		glPushMatrix();
			updateConveyor(elapsedTime);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(PAINT_X_POSITION, -DROP_HEIGHT+0.5*PAINT_BRACKET_HEIGHT-0.5*PRESS_SHAFT_WIDTH+0.5*TILE_HEIGHT-1, SPIRAL_WIDTH);
			drawPaintParticles();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(TORCH_X_POSITION, TORCH_TANK_LENGTH+TORCH_PIPE_LENGTH, 0);
			drawFireParticles();
		glPopMatrix();
		drawGearSystem(elapsedTime);
	glPopMatrix();
	glutSwapBuffers();
} 


void initialize(void) {
	configureLighting();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
		glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	glLoadIdentity();
	loadTexture();
	loadLegoTexture();
	loadParticleTexture();
	loadConveyorTexture();
	gluPerspective(110., 1, 10., 1500.);   //Camera Frustum
    
}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(1080, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Factory");

	initialize();

	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);

	glutTimerFunc(16, timer, 0);

	glutMainLoop();

	return 0; 
}
