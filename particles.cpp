#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <list>
#include <GL/freeglut.h>
#include <climits>
#include "loadBMP.h"
using namespace std;

#include "conveyor.h"
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
#define _USE_MATH_DEFINES
using namespace std;


//-- Globals ---------------------------------------------------------------
const float PAINT_PERIOD = PRESS_PERIOD;
const float SPRAY_TIME = TILE_WIDTH / X_SPEED;
const float SPRAY_START = 0.5*(PAINT_PERIOD-SPRAY_TIME);
const float SPRAY_END = 0.5*(PAINT_PERIOD+SPRAY_START)+0.5;
const float PAINT_OFFSET = 0.8;
const float PAINT_SPEED = 30;
const float PAINT_SPREAD = 5;

const float FIRE_SPREAD = 1;
const float FIRE_SPEED = 10;
const float FIRE_DISTANCE = 8;
const float FIRE_LIFETIME = FIRE_DISTANCE / FIRE_SPEED;

GLuint particletxId[1];		//Texture id

struct particle	{	//A particle 
	float t;			//Life time  
	float size;		//Size   
	float pos[3];	//Position
	float vel[3];	//Velocity
	float col[3] = {0,0,0};
};

list<particle> paintList; // list of paint particles
list<particle> fireList; // list of fire particles

//--------------------------------------------------------------------------
void loadParticleTexture() {
	glGenTextures(1, particletxId);

	glBindTexture(GL_TEXTURE_2D, particletxId[0]);
	loadBMP("../Glow.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

//-- Draws a single particle as two texture mapped quads -------------------
void drawParticle(float size, float px, float py, float pz) {
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, particletxId[0]);


	glPushMatrix();
		glTranslatef(px, py, pz);
		glScalef(size, size, size);

		glBegin(GL_QUADS);
			//A quad on the xy-plane
			glTexCoord2f(0, 0);
			glVertex3f(-0.5, -0.5, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0.5, -0.5, 0);
			glTexCoord2f(1, 1);
			glVertex3f(0.5, 0.5, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-0.5, 0.5, 0);

			//A quad on the yz-plane
			glTexCoord2f(0, 0);
			glVertex3f(0, -0.5, -0.5);
			glTexCoord2f(1, 0);
			glVertex3f(0, 0.5, -0.5);
			glTexCoord2f(1, 1);
			glVertex3f(0, 0.5, 0.5);
			glTexCoord2f(0, 1);
			glVertex3f(0, -0.5, 0.5);
		glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void newFireParticle(void){
	float x = (2 * (rand() / (float)RAND_MAX) - 1)*FIRE_SPREAD;
	float y = 0;
	float z = (2 * (rand() / (float)RAND_MAX) - 1)*FIRE_SPREAD;

	particle p = { 0 };
	p.t = 0;
	p.pos[0] = x;
	p.pos[1] = y;
	p.pos[2] = z; 

	// have velocities point towards tip

	p.vel[0] = -1*(x / FIRE_LIFETIME);
	p.vel[1] = -FIRE_SPEED;
	p.vel[2] = -1*(z / FIRE_LIFETIME);

	p.size = 3;

	fireList.push_back(p);
}



//-- Creates a new particle and initializes its data fields ----------------
void newPaintParticle() {
	particle p = { 0 };
	// top particle
	p.t = 0;
	p.pos[0] = 0;
	p.pos[1] = 0.5*PAINT_BRACKET_HEIGHT;
	p.pos[2] = 0; 

	p.vel[0] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;
	p.vel[1] = -PAINT_SPEED*PAINT_BRACKET_HEIGHT/PAINT_BRACKET_LENGTH;
	p.vel[2] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;

	p.size = 1.5;

	paintList.push_back(p);
	// front particle
	p = { 0 };
	p.t = 0;
	p.pos[0] = 0;
	p.pos[1] = 0;
	p.pos[2] = 0.5*PAINT_BRACKET_LENGTH-PRESS_SHAFT_WIDTH; 

	p.vel[0] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;
	p.vel[1] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;
	p.vel[2] = -PAINT_SPEED;

	p.size = 1.5;

	paintList.push_back(p);
	// back particle
	p = { 0 };
	p.t = 0;
	p.pos[0] = 0;
	p.pos[1] = 0;
	p.pos[2] = -0.5*PAINT_BRACKET_LENGTH+PRESS_SHAFT_WIDTH; 

	p.vel[0] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;
	p.vel[1] = (2 * (rand() / (float)RAND_MAX) - 1)*PAINT_SPREAD;
	p.vel[2] = PAINT_SPEED;

	p.size = 1.5;

	paintList.push_back(p);
}

//-- Updates the particle queue --------------------------------------------
void updatePaintQueue(float time) {
	float t1 = fmod(time+ PAINT_OFFSET, PAINT_PERIOD) ;
	const float LIFETIME = PAINT_BRACKET_HEIGHT / PAINT_SPEED;
	list<particle>::iterator it;
	particle p;
	float tval;

	while (!paintList.empty() && (paintList.front().t > LIFETIME)){
		paintList.pop_front();
	}


	for (it = paintList.begin(); it != paintList.end(); it++) {
		tval = it->t;
		it->t = tval + 0.016;
		for (int i = 0; i < 3; i++)	(it->pos[i]) += (it->vel[i])*0.016;
	
	}
	if (t1 > SPRAY_START && t1 <= SPRAY_END/2){
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
		newPaintParticle();
	}
}


void updateFireQueue(float time) {
	list<particle>::iterator it;
	particle p;
	float tval;
	float delta;
	while (!fireList.empty() && (fireList.front().t > FIRE_LIFETIME)){
		fireList.pop_front();
	}


	for (it = fireList.begin(); it != fireList.end(); it++) {
		tval = it->t;
		it->t = tval + 0.016;
		delta = it->t / FIRE_LIFETIME;
		if (delta < 0.5) {
			it->col[0] = 1.0f;                   // Red stays max
			it->col[1] = 0.6f * delta * 2.0f;    
			it->col[2] = 0.0f;                   
		} else {
			it->col[0] = 1.0f - (delta - 0.5f) * 2.0f;  // Red decreases
			it->col[1] = 0.6f - (delta - 0.5f) * 1.2f;  
			it->col[2] = (delta - 0.5f) * 2.0f;         // Blue increases
		}
		for (int i = 0; i < 3; i++)	(it->pos[i]) += (it->vel[i])*0.016;
	
	}
	newFireParticle();
}


void drawPaintParticles(void){
    list<particle>::iterator it;
	for (it = paintList.begin(); it != paintList.end(); it++) {
        glColor3f(1*0.5,0.82*0.5,0.16*0.5);
		drawParticle(it->size, it->pos[0], it->pos[1], it->pos[2]);
	}
}

void drawFireParticles(void) {
	list<particle>::iterator it;
	for (it = fireList.begin(); it != fireList.end(); it++) {
		glColor3f(it->col[0], it->col[1],it->col[2]);
		drawParticle(it->size, it->pos[0], it->pos[1], it->pos[2]);
	}
}