#include <iostream>
#include <fstream>
#include <climits>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
#include "legoman.h"
#include "conveyor.h"

const float HEAD_HEIGHT = 4.86 + 1.75+2+1.75+1.21;

GLuint legotxId[1];   //Texture ids

void loadLegoTexture(void){
	glGenTextures(1, legotxId); 
	glBindTexture(GL_TEXTURE_2D, legotxId[0]);
	loadTGA("../legoface.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
}


void head(void){
	glPushMatrix(); // Main Head Cylinder
		glTranslatef(0,-4.86,0);
		glScalef(1,-1,1);
		glRotatef(90, 1,0,0);
		GLUquadric *q;
		q = gluNewQuadric();
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, legotxId[0]);

		gluQuadricNormals(q, GLU_SMOOTH);
		gluQuadricDrawStyle(q, GLU_FILL);
		glEnable(GL_TEXTURE_2D);
		gluQuadricTexture (q, GL_TRUE);

		gluCylinder(q, 10.11/2, 10.11/2, 4.86, 32, 3);
		gluDeleteQuadric(q);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor3f(1,0.82,0.16);
	glPushMatrix(); // Top Head Torus
		glRotatef(90,1,0,0);
		glutSolidTorus(1.75,10.11/2-1.75,32,32);
	glPopMatrix();

	glPushMatrix(); // Top Head Disk
		glTranslatef(0,1.75,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 10.11/2-1.75, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Bottom Head Torus
		glTranslatef(0,-4.86,0);
		glRotatef(90,1,0,0);
		glutSolidTorus(1.75,10.11/2-1.75,32,32);
	glPopMatrix();

	glPushMatrix(); // Bottom Head Disk
		glTranslatef(0,-4.86-1.75,0);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 10.11/2-1.75, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Top Head Cylinder
		glTranslatef(0,1.75,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluCylinder(q, 3.98/2, 3.98/2, 2, 10, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Top Top Head Disk
		glTranslatef(0,1.75+2,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 3.98/2, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // bottom Head Cylinder
		glTranslatef(0,-4.86-1.75,0);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluCylinder(q, 6.52/2, 6.52/2, 1.21, 10, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();
}

void headNoTexture(void){
	glColor3f(0.2,0.2,0.2);
	glPushMatrix(); // Main Head Cylinder
		glTranslatef(0,-4.86,0);
		glScalef(1,-1,1);
		glRotatef(90, 1,0,0);
		GLUquadric *q;
		q = gluNewQuadric();
		gluQuadricNormals(q, GLU_SMOOTH);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluCylinder(q, 10.11/2, 10.11/2, 4.86, 32, 3);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Top Head Torus
		glRotatef(90,1,0,0);
		glutSolidTorus(1.75,10.11/2-1.75,32,32);
	glPopMatrix();

	glPushMatrix(); // Top Head Disk
		glTranslatef(0,1.75,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 10.11/2-1.75, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Bottom Head Torus
		glTranslatef(0,-4.86,0);
		glRotatef(90,1,0,0);
		glutSolidTorus(1.75,10.11/2-1.75,32,32);
	glPopMatrix();

	glPushMatrix(); // Bottom Head Disk
		glTranslatef(0,-4.86-1.75,0);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 10.11/2-1.75, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Top Head Cylinder
		glTranslatef(0,1.75,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluCylinder(q, 3.98/2, 3.98/2, 2, 10, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // Top Top Head Disk
		glTranslatef(0,1.75+2,0);
		glRotatef(-90, 1,0,0);
		q = gluNewQuadric();
		gluDisk(q, 0, 3.98/2, 24, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();

	glPushMatrix(); // bottom Head Cylinder
		glTranslatef(0,-4.86-1.75,0);
		glRotatef(90, 1,0,0);
		q = gluNewQuadric();
		gluCylinder(q, 6.52/2, 6.52/2, 1.21, 10, 3);
		gluQuadricDrawStyle(q, GLU_FILL);
		gluDeleteQuadric(q);
	glPopMatrix();
}

void ingot(void){
	glPushMatrix();
		glColor3f(0.2,0.2,0.2);
		glTranslatef(0,-4.86-1.75+4,0);
		glScalef(10,10,10);
		glutSolidCube(1);
	glPopMatrix();
}

void configureLighting(void){
	float white[4]  = {1., 1., 1., 1.};
	float lightPos[4] = {150., 50., 0., 1.};  
    float lightAmbient[4]  = {0.2, 0.2, 0.2, 1.};  
    float lightDiffuse[4]  = {1., 1., 1., 1.};  
    float lightSpecular[4] = {0.5, 0.5, 0.5, 1.};
	glClearColor(1., 1., 1., 1.);




	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

}




void meltingIngot(float time) {
    // heating progress
    float heat = std::min((time - TORCH_START) / (PRESS_START - TORCH_START), 1.0f);


    GLfloat hotColor[] = {1.0f, 0.2f, 0.1f, 1.0f};       
    GLfloat glowColor[] = {1.0f, 0.3f, 0.1f, 1.0f};     
    GLfloat specular[] = {0.3f, 0.1f, 0.1f, 1.0f};       
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};     

    // apply heat effect if in heating phase
    if (heat > 0) {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, hotColor);
        glMaterialfv(GL_FRONT, GL_AMBIENT, hotColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, glowColor);  
    } else {
        // cold state 
        GLfloat coldColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, coldColor);
        glMaterialfv(GL_FRONT, GL_EMISSION, black);
    }

    // Draw ingot
    glPushMatrix();
        glTranslatef(0, -4.86f - 1.75f + 4, 0);
        glScalef(INGOT_HEIGHT, INGOT_HEIGHT, INGOT_HEIGHT);
        glutSolidCube(1);
    glPopMatrix();

    // Reset emission
    glMaterialfv(GL_FRONT, GL_EMISSION, black);
	
}