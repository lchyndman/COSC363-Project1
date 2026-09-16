#include <iostream>
#include <fstream>
#include <climits>
#include <GL/freeglut.h>
#include <cmath>
#include <array>
#include "legoman.h"
#include "skybox.h"
#include "loadTGA.h"
#include "particles.h"
#include "conveyor.h"
#define _USE_MATH_DEFINES
using namespace std;




GLuint conveyortxId[4];   //Texture ids
void loadConveyorTexture() {
	glGenTextures(4, conveyortxId); 	

	glBindTexture(GL_TEXTURE_2D, conveyortxId[0]);
    loadTGA("../metall005-new-tileable.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, conveyortxId[2]);
	loadTGA("../flamesign.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
}

void drawSpawnHole(void){
	// front face
	glPushMatrix();
		glTranslatef(0, 0, 0.5*TILE_WIDTH+0.5*TILE_HEIGHT);
		glScalef(TILE_LENGTH, SPAWN_HOLE_HEIGHT, TILE_HEIGHT);
		glutSolidCube(1);
	glPopMatrix();
	
	// back face
	glPushMatrix();
		glTranslatef(0, 0, -0.5*TILE_WIDTH-0.5*TILE_HEIGHT);
		glScalef(TILE_LENGTH, SPAWN_HOLE_HEIGHT, TILE_HEIGHT);
		glutSolidCube(1);	
	glPopMatrix();
	
	// top face
	glPushMatrix();
		glTranslatef(0, 0.5*INGOT_HEIGHT+1.5*TILE_HEIGHT, 0);
		glScalef(TILE_LENGTH, TILE_HEIGHT, TILE_WIDTH+2*TILE_HEIGHT);
		glutSolidCube(1);
	glPopMatrix();

	// bottom face
	glPushMatrix();
		glTranslatef(0, -0.5*INGOT_HEIGHT-1.5*TILE_HEIGHT, 0);
		glScalef(TILE_LENGTH, TILE_HEIGHT, TILE_WIDTH+2*TILE_HEIGHT);
		glutSolidCube(1);
	glPopMatrix();

	//black wall
	glPushMatrix();
		glTranslatef(-0.5*TILE_LENGTH,0,0);
		glScalef(0.1,SPAWN_HOLE_HEIGHT,TILE_WIDTH);
		glColor3f(0,0,0);
		glutSolidCube(1);
	glPopMatrix();

}

void drawSpawnHoles(void){
	// need to draw some edges to hide the spawning/despawning of the blocks
	glColor3f(0.2, 0.3, 0.2);
	glPushMatrix();
	glTranslatef(0.5*SPAWN_BOX_LENGTH+0.5*TILE_LENGTH, 0.5*SPAWN_HOLE_HEIGHT-0.5*RAIL_HEIGHT,0);
	drawSpawnHole();
	glPopMatrix();
	glColor3f(0.3, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(0.5*SPAWN_BOX_LENGTH+0.5*TILE_LENGTH, 0.5*SPAWN_HOLE_HEIGHT-0.5*RAIL_HEIGHT-DROP_HEIGHT,SPIRAL_WIDTH);
	drawSpawnHole();
	glPopMatrix();
}


void drawTorch() {
	// torch will consist of a tank, 1 cyl 2 spheres, pipe, 1 cyl, and nozzzle, 1 cyl
	// plus a bracket
	// the bottom of the nozzle will be centered at the origin

	//nozzle
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		GLUquadric *q;
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, TORCH_PIPE_RADIUS, TORCH_NOZZLE_RADIUS, TORCH_NOZZLE_LENGTH, 50, 20);
		gluDeleteQuadric(q);
	glPopMatrix();
	// pipe
	glPushMatrix();
		glTranslatef(0, TORCH_PIPE_LENGTH, 0);
		glRotatef(90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, TORCH_PIPE_RADIUS, TORCH_PIPE_RADIUS, TORCH_PIPE_LENGTH, 50, 20);
		gluDeleteQuadric(q);
	glPopMatrix();

	glColor3f(1,0,0);

	// tank cylinder
	glPushMatrix();
		glTranslatef(0, TORCH_PIPE_LENGTH+TORCH_TANK_LENGTH, 0);
		glRotatef(90, 1, 0, 0);
		q = gluNewQuadric();
		gluCylinder(q, TORCH_TANK_RADIUS, TORCH_TANK_RADIUS, TORCH_TANK_LENGTH, 50, 20);	
		gluDeleteQuadric(q);
	glPopMatrix();

	// tank sign
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, conveyortxId[2]);
	glColor3f(1,1,1);
	glNormal3f(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-TORCH_TANK_RADIUS, TORCH_NOZZLE_LENGTH + TORCH_PIPE_LENGTH-0.5*TORCH_TANK_LENGTH, TORCH_TANK_RADIUS);
		glTexCoord2f(1,0);
		glVertex3f(TORCH_TANK_RADIUS,TORCH_NOZZLE_LENGTH + TORCH_PIPE_LENGTH-0.5*TORCH_TANK_LENGTH, TORCH_TANK_RADIUS);
		glTexCoord2f(1,1);
		glVertex3f(TORCH_TANK_RADIUS,TORCH_NOZZLE_LENGTH + TORCH_PIPE_LENGTH+0.5*TORCH_TANK_LENGTH, TORCH_TANK_RADIUS);
		glTexCoord2f(0,1);
		glVertex3f(-TORCH_TANK_RADIUS,TORCH_NOZZLE_LENGTH + TORCH_PIPE_LENGTH+0.5*TORCH_TANK_LENGTH, TORCH_TANK_RADIUS);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glColor3f(1,0,0);
	// bottom tank sphere 
	glPushMatrix();
		glTranslatef(0, TORCH_PIPE_LENGTH,0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluSphere(q, TORCH_TANK_RADIUS, 32, 32);
		gluDeleteQuadric(q);
	glPopMatrix();
	
	// top tank sphere
	glPushMatrix();
		glTranslatef(0, TORCH_PIPE_LENGTH+TORCH_TANK_LENGTH,0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluSphere(q, TORCH_TANK_RADIUS, 32, 32);
		gluDeleteQuadric(q);
	glPopMatrix();

	glColor3f(0.3,0.3,0.3);

	// bracket top
	glPushMatrix();
		glTranslatef(0, TORCH_NOZZLE_LENGTH + TORCH_PIPE_LENGTH, -0.5*TILE_LENGTH-PRESS_SHAFT_WIDTH+1.05);
		glScalef(PRESS_SHAFT_WIDTH, PRESS_SHAFT_WIDTH, TILE_LENGTH+0.5*PRESS_SHAFT_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// bracket shaft
	glPushMatrix();
		glTranslatef(0, -TORCH_TANK_LENGTH-0.5*TORCH_PIPE_LENGTH+TORCH_NOZZLE_LENGTH, -TILE_LENGTH-0.5*PRESS_SHAFT_WIDTH);
		glScalef(PRESS_SHAFT_WIDTH, (TORCH_TANK_LENGTH+TORCH_NOZZLE_LENGTH+TORCH_PIPE_LENGTH)*2, PRESS_SHAFT_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// brack base
	glPushMatrix();
		glTranslatef(0, -0.5*(TORCH_TANK_LENGTH+TORCH_NOZZLE_LENGTH+TORCH_PIPE_LENGTH)*2-0.5*PRESS_SHAFT_WIDTH-2, -0.5*TILE_LENGTH);
		glScalef(PRESS_SHAFT_WIDTH,PRESS_SHAFT_WIDTH,TILE_LENGTH);
		glutSolidCube(1);
	glPopMatrix();
}

void drawPaintCan(void){
	// we can build our paint can out of 3 parts
	

	// a n shaped bracket over the tiles

	// the bottom of the bracket will be centered on the origin

	// bottom bracket
	glPushMatrix();
		glTranslatef(0,0.5*PRESS_SHAFT_WIDTH,0);
		glScalef(PRESS_SHAFT_WIDTH,PRESS_SHAFT_WIDTH,PAINT_BRACKET_LENGTH);
		glutSolidCube(1);
	glPopMatrix();

	// front bracket
	glPushMatrix();
		glTranslatef(0,0.5*PAINT_BRACKET_HEIGHT+PRESS_SHAFT_WIDTH,0.5*(PAINT_BRACKET_LENGTH-PRESS_SHAFT_WIDTH));
		glScalef(PRESS_SHAFT_WIDTH, PAINT_BRACKET_HEIGHT, PRESS_SHAFT_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// back bracket
	glPushMatrix();
		glTranslatef(0,0.5*PAINT_BRACKET_HEIGHT+PRESS_SHAFT_WIDTH,-0.5*(PAINT_BRACKET_LENGTH-PRESS_SHAFT_WIDTH));
		glScalef(PRESS_SHAFT_WIDTH, PAINT_BRACKET_HEIGHT,PRESS_SHAFT_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// top bracket
	glPushMatrix();
		glTranslatef(0,1.5*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT,0);
		glScalef(PRESS_SHAFT_WIDTH,PRESS_SHAFT_WIDTH,PAINT_BRACKET_LENGTH);
		glutSolidCube(1);
	glPopMatrix();


	// 3 paint cans over the top of the bracket
	
	// front can
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT,2*PAINT_CAN_RADIUS);
		glRotatef(-90, 1, 0, 0);
		GLUquadric *q;
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, PAINT_CAN_RADIUS, PAINT_CAN_RADIUS, PAINT_CAN_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();

	// middle can
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT,0);
		glRotatef(-90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, PAINT_CAN_RADIUS, PAINT_CAN_RADIUS, PAINT_CAN_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();

	// back can
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT,-2*PAINT_CAN_RADIUS);
		glRotatef(-90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, PAINT_CAN_RADIUS, PAINT_CAN_RADIUS, PAINT_CAN_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();


	// can tops
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT+PAINT_CAN_LENGTH,-2*PAINT_CAN_RADIUS);
		glRotatef(-90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDisk(q, 0, PAINT_CAN_RADIUS , 50, 20);
		gluDeleteQuadric(q);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT+PAINT_CAN_LENGTH,+2*PAINT_CAN_RADIUS);
		glRotatef(-90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDisk(q, 0, PAINT_CAN_RADIUS , 50, 20);
		gluDeleteQuadric(q);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,2*PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT+PAINT_CAN_LENGTH,0);
		glRotatef(-90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDisk(q, 0, PAINT_CAN_RADIUS , 50, 20);
		gluDeleteQuadric(q);
	glPopMatrix();

	// 3 nozzles evnly spaced on the inside of the bracket

	// top nozzle
	glPushMatrix();
		glTranslatef(0,PRESS_SHAFT_WIDTH+PAINT_BRACKET_HEIGHT,0);
		glRotatef(90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, 1, PAINT_NOZZLE_RADIUS, PAINT_NOZZLE_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();

	// back nozzle
	glPushMatrix();
		glTranslatef(0,PRESS_SHAFT_WIDTH+0.5*PAINT_BRACKET_HEIGHT,-0.5*PAINT_BRACKET_LENGTH+PRESS_SHAFT_WIDTH);
		// glRotatef(90, 1, 0, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, 1, PAINT_NOZZLE_RADIUS, PAINT_NOZZLE_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();

	// front nozzle
	glPushMatrix();
		glTranslatef(0,PRESS_SHAFT_WIDTH+0.5*PAINT_BRACKET_HEIGHT,0.5*PAINT_BRACKET_LENGTH-PRESS_SHAFT_WIDTH);
		glRotatef(180, 0, 1, 0);
		q = gluNewQuadric();
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, 1, PAINT_NOZZLE_RADIUS, PAINT_NOZZLE_LENGTH, 50, 2);
		gluDeleteQuadric(q);
	glPopMatrix();
}

void drawTrack(float t){
	float t1 = fmod(t, POLE_PERIOD);
	// 3 parts, top rail, bottom rail, pole for spiral section

	// top rail
	glPushMatrix();
		glTranslatef(0.5*(RAIL_LENGTH-TILE_LENGTH), -0.5*(RAIL_HEIGHT+TILE_HEIGHT), 0);
		glScalef(RAIL_LENGTH, RAIL_HEIGHT, RAIL_WIDTH);
		glutSolidCube(1);
	glPopMatrix();
	

	// bottom rail
	glPushMatrix();
		glTranslatef(0.5*RAIL_LENGTH, -DROP_HEIGHT-0.5*(RAIL_HEIGHT+TILE_HEIGHT), SPIRAL_WIDTH);
		glScalef(RAIL_LENGTH, RAIL_HEIGHT, RAIL_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// Pole
	glPushMatrix();
		glTranslatef(STRAIGHT_LENGTH, -0.5*(POLE_HEIGHT+DROP_HEIGHT), 0.5*SPIRAL_WIDTH);
		glRotatef(-t1*360/POLE_PERIOD, 0, 1, 0);
		glRotatef(-90, 1, 0, 0); // rotate cylinder upwards 
		GLUquadric *q;
        q = gluNewQuadric();
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,conveyortxId[0]);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluQuadricNormals(q, GLU_SMOOTH);
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture (q, GL_TRUE);

        gluCylinder(q, POLE_WIDTH, POLE_WIDTH, POLE_HEIGHT, 30, 1); 
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	// pole top and bottom
	glPushMatrix(); // Top  Disk
		glColor3f(0.3,0.3,0.3);
		glTranslatef(STRAIGHT_LENGTH,0.5*(POLE_HEIGHT-DROP_HEIGHT),0.5*SPIRAL_WIDTH);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, POLE_WIDTH, 30, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
	glPopMatrix();

	glPushMatrix(); // Bottom  Disk
		glTranslatef(STRAIGHT_LENGTH,-0.5*(POLE_HEIGHT+DROP_HEIGHT),0.5*SPIRAL_WIDTH);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, POLE_WIDTH, 30, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
	glPopMatrix();

}

void drawPress(float extension){
	
    float y_scale = PRESS_SHAFT_MIN_LENGTH + extension * PRESS_SHAFT_RANGE;
    // cylinder on a rectangular shaft

	// bracket top
	glPushMatrix();
		glTranslatef(0, -0.5*PRESS_SHAFT_WIDTH, -0.5*(TILE_LENGTH+PRESS_SHAFT_WIDTH));
		glScalef(PRESS_SHAFT_WIDTH, PRESS_SHAFT_WIDTH, TILE_LENGTH);
		glutSolidCube(1);
	glPopMatrix();

	//bracket shaft
	glPushMatrix();
		glTranslatef(0, -0.5*(PRESS_Y_POSITION+TILE_HEIGHT), -TILE_LENGTH-0.5*PRESS_SHAFT_WIDTH);
		glScalef(PRESS_SHAFT_WIDTH, PRESS_Y_POSITION+TILE_HEIGHT, PRESS_SHAFT_WIDTH);
		glutSolidCube(1);
	glPopMatrix();

	// bracket base
	glPushMatrix();
		glTranslatef(0, -PRESS_SHAFT_WIDTH-PRESS_Y_POSITION,-0.5*(TILE_LENGTH+2*PRESS_SHAFT_WIDTH));
		glScalef(PRESS_SHAFT_WIDTH,PRESS_SHAFT_WIDTH,TILE_LENGTH);
		glutSolidCube(1);
	glPopMatrix();

    // shaft
    glPushMatrix();
        glTranslatef(0, -0.5*y_scale , 0); // position top of shaft at origin
        glScalef(PRESS_SHAFT_WIDTH, y_scale, PRESS_SHAFT_WIDTH);
        glutSolidCube(1);
    glPopMatrix();

    // Cylinder
    glPushMatrix();
        glTranslatef(0, -y_scale-PRESS_CYLINDER_HEIGHT, 0); // position top of cylinder at bottom of piston
		glRotatef(720*extension, 0, 1, 0);
        glRotatef(-90, 1, 0, 0); // rotate cylinder downwards 
        GLUquadric *q;
        q = gluNewQuadric();
		glColor3f(1,1,1);
		
		glBindTexture(GL_TEXTURE_2D,conveyortxId[0]);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluQuadricNormals(q, GLU_SMOOTH);
		
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture (q, GL_TRUE);
        gluCylinder(q, PRESS_CYLINDER_RADIUS, PRESS_CYLINDER_RADIUS, PRESS_CYLINDER_HEIGHT, 30, 1); 
		gluDeleteQuadric(q);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor3f(0,0,0);
	glPushMatrix(); // Bottom  Disk
		glTranslatef(0,-y_scale-PRESS_CYLINDER_HEIGHT,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, PRESS_CYLINDER_RADIUS, 30, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();
	glColor3f(0.3,0.3,0.3);
	glPushMatrix(); // Top  Disk
		glTranslatef(0,-y_scale,0);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, PRESS_CYLINDER_RADIUS, 30, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

}

float tileX(float t){
	float t1 = fmod(t, TOTAL_TIME);
	float x;
	if (t1 >= TOP_START && t1 < SPIRAL_START) { // in the straight moving left to right
		x = X_SPEED  * t1;
	} else if (t1 >= SPIRAL_START && t1 < BOTTOM_START) { // spiraling downwards
        float angle = (t1 - SPIRAL_START) * M_PI / (BOTTOM_START - SPIRAL_START);
		x = STRAIGHT_LENGTH + 0.5*SPIRAL_WIDTH*sin(angle);
	} else {
		x = STRAIGHT_LENGTH - X_SPEED*(t1-BOTTOM_START); // moving right to left
	}

	return x;
}

float tileY(float t){
	float t1 = fmod(t, TOTAL_TIME);
	float y;
	if (t1 >= TOP_START && t1 < SPIRAL_START) { // in the straight moving left to right
		y = 0;
	} else if (t1 >= SPIRAL_START && t1 < BOTTOM_START) { // spiraling downwards
		y = -1 * Y_SPEED * (t1 - SPIRAL_START);
	} else {
		y = -1 * DROP_HEIGHT; // moving right to left
	}

	return y;
}

float tileZ(float t){
	float t1 = fmod(t, TOTAL_TIME);
	float z;
	if (t1 >= TOP_START && t1 < SPIRAL_START) { // in the straight moving left to right
		z = 0;
	} else if (t1 >= SPIRAL_START && t1 < BOTTOM_START) { // spiraling downwards
        float angle = (t1 - SPIRAL_START) * M_PI / (BOTTOM_START - SPIRAL_START);
		z =0.5*SPIRAL_WIDTH + 0.5*SPIRAL_WIDTH*-cos(angle);
	} else {
		z = SPIRAL_WIDTH; // moving right to left
	}
	return z;
}

float tileAngle(float t) {
	float t1 = fmod(t, TOTAL_TIME);
	float angle;
	if (t1 >= TOP_START && t1 < SPIRAL_START) { // in the straight moving left to right
		angle = 0;
	} else if (t1 >= SPIRAL_START && t1 < BOTTOM_START) { // spiraling downwards
        angle = (t1 - SPIRAL_START) * -180 / (BOTTOM_START - SPIRAL_START);
	} else {
		angle = -180;
	}
	return angle;
}

void drawSpawnBox(void){
	glColor3f(0.3,0.3,0.3);
	glPushMatrix();
		glScalef(SPAWN_BOX_LENGTH,SPAWN_BOX_HEIGHT,SPAWN_BOX_WIDTH);
		glutSolidCube(1);
	glPopMatrix();
}

void drawConveyorTile(){
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();

		glScalef(TILE_LENGTH,TILE_HEIGHT,TILE_WIDTH);
		glutSolidCube(1);
	glPopMatrix();
}

void positionTile(float t, float phase) {
	glPushMatrix();
    float x = tileX(t + phase*TOTAL_TIME);
    float y = tileY(t + phase*TOTAL_TIME);
	float z = tileZ(t + phase*TOTAL_TIME);
	float rotation = tileAngle(t + phase*TOTAL_TIME);
    glTranslatef(x,y,z);
	glRotatef(rotation, 0, 1, 0);
    drawConveyorTile();
    glPopMatrix();
}

void positionHead(float t, float phase) {
	float t1 = fmod(t + phase*TOTAL_TIME, TOTAL_TIME);

	glPushMatrix();
   		float x = tileX(t + phase*TOTAL_TIME);
		float y = tileY(t + phase*TOTAL_TIME) + 1.21 + 4.86 + 1.75+1.21;
		float z = tileZ(t + phase*TOTAL_TIME);
		float rotation = tileAngle(t + phase*TOTAL_TIME);
		glTranslatef(x,y,z);
		glRotatef(rotation, 0, 1, 0);
		if (t1 < TORCH_START){
			ingot();
		} else if (TORCH_START <= t1 && t1 < PRESS_START){
			meltingIngot(t1);
		} else if (PRESS_START <= t1 && t1 < PAINT_START) {
			headNoTexture();
		} else {
			head();
		}
    glPopMatrix();
	configureLighting();
}

void positionPress(float t) {
	float t1 = fmod(t-0.9, TOTAL_TIME); // time within total cycle 
	float t2 = fmod(t1, PRESS_PERIOD); // time within presss cycle
	float extension;
	if (t2 < PRESS_DOWN_TIME || t2 > PRESS_UP_TIME) {
		extension = 0;
	} else {
		float t3 = t2 - PRESS_DOWN_TIME;
		extension = sin(M_PI*t3/(PRESS_UP_TIME-PRESS_DOWN_TIME)); 

	}
	glPushMatrix();
		glTranslatef(PRESS_X_POSITION,PRESS_Y_POSITION,PRESS_Z_POSITION);
	 	drawPress(extension);
	glPopMatrix();
}

void updateConveyor(float t){
	glPushMatrix();
		glTranslatef(0,-2*TILE_HEIGHT,SPIRAL_WIDTH/2);
		drawSpawnBox();
	glPopMatrix();
	drawSpawnHoles();
	
	glPushMatrix();
		glTranslatef(TORCH_X_POSITION,24,0);
		drawTorch();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(PAINT_X_POSITION, -0.5-DROP_HEIGHT-PRESS_SHAFT_WIDTH-0.5*TILE_HEIGHT, SPIRAL_WIDTH);
		drawPaintCan();
	glPopMatrix();

	positionPress(t);
	drawTrack(t);
	for (float i = 0; i <= N_TILES; i++) {
		positionTile(t, i/N_TILES);
		positionHead(t, i/N_HEADS);
	}
}