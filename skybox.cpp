#include <iostream>
#include <fstream>
#include <climits>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
GLuint txId[4];   //Texture ids

//-- Function to load textures ---------------------------------------------
void loadTexture() {
	glGenTextures(4, txId); 	

	glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadTGA("../boiler_room_1k.tga"); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


// Draws a Skysphere
void drawSkySphere(float radius, int slices, int stacks) {
    glBindTexture(GL_TEXTURE_2D, txId[2]); 
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GL_SMOOTH);
    
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        
        // Flip sphere inside-out
        glScalef(-1, 1, 1);
        glColor3f(1,1,1);
        glRotatef(-90, 1,0,0);
        gluSphere(quad, radius, slices, stacks); 
        
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    gluDeleteQuadric(quad);
}

