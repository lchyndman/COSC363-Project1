#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include "conveyor.h"


float R(float theta, int N_TEETH, float TOOTH_SIZE, float GEAR_RADIUS) { // gear tooth function
    return sin(theta * N_TEETH / 2) * TOOTH_SIZE + GEAR_RADIUS;
}

void computeEdgeNormal(float theta, float normal[3], int N_TEETH, float TOOTH_SIZE) {
    float dRdtheta = cos(theta * N_TEETH / 2) * N_TEETH/2 * TOOTH_SIZE;
    
    normal[0] = cos(theta) - dRdtheta * sin(theta);
    normal[1] = sin(theta) + dRdtheta * cos(theta);
    normal[2] = 0;
    
    float len = sqrt(normal[0]*normal[0] + normal[1]*normal[1]);
    normal[0] /= len;
    normal[1] /= len;
    normal[2] = 0;
}

void drawGear(int N_TEETH, float TOOTH_SIZE, float GEAR_RADIUS, float GEAR_WIDTH, int N_THETA) {
    std::vector<float> vertices;
    std::vector<float> edgeNormals;
    std::vector<float> sideNormals;
    
    for (int i = 0; i <= N_THETA; i++) {
        float theta = 2 * M_PI * i / N_THETA;
        float r = R(theta, N_TEETH, TOOTH_SIZE, GEAR_RADIUS);
        
        // generating points along edge
        vertices.push_back(r * cos(theta));
        vertices.push_back(r * sin(theta));
        vertices.push_back(GEAR_WIDTH/2);   
        
        vertices.push_back(r * cos(theta));
        vertices.push_back(r * sin(theta)); 
        vertices.push_back(-GEAR_WIDTH/2);  
        
        // edge normals
        float normal[3];
        computeEdgeNormal(theta, normal, N_TEETH, TOOTH_SIZE);
        edgeNormals.insert(edgeNormals.end(), normal, normal+3);
        edgeNormals.insert(edgeNormals.end(), normal, normal+3);
        
        // Side normals
        sideNormals.push_back(0); sideNormals.push_back(0); sideNormals.push_back(1);  // top
        sideNormals.push_back(0); sideNormals.push_back(0); sideNormals.push_back(-1); // bottom
    }
    
    // edge
    glBegin(GL_QUAD_STRIP);
    for (size_t i = 0; i < vertices.size()/3; i++) {
        glNormal3fv(&edgeNormals[i*3]);
        glVertex3fv(&vertices[i*3]);
    }
    glEnd();
    
    // top face
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0, 0, 1);
    for (int i = 0; i <= N_THETA; i++) {
        float theta = 2.0f * M_PI * i / N_THETA;
        glVertex3f(0, 0, GEAR_WIDTH/2);
        glVertex3f(R(theta, N_TEETH, TOOTH_SIZE, GEAR_RADIUS)*cos(theta), R(theta, N_TEETH, TOOTH_SIZE, GEAR_RADIUS)*sin(theta), GEAR_WIDTH/2);
    }
    glEnd();
    
    // bottom face
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0, 0, -1);
    for (int i = 0; i <= N_THETA; i++) {
        float theta = 2.0f * M_PI * i / N_THETA;
        glVertex3f(0, 0, -GEAR_WIDTH/2);
        glVertex3f(R(theta, N_TEETH, TOOTH_SIZE, GEAR_RADIUS)*cos(theta), R(theta, N_TEETH, TOOTH_SIZE, GEAR_RADIUS)*sin(theta), -GEAR_WIDTH/2);
    }
    glEnd();
}

void drawGearSystem(float time){
    // we want to draw gears at the top and bottom of the pole, 
    // along the sides of the conveyor rails and on the side of the spawn box

    // top of the pole
    glPushMatrix();
        glColor3f(0.3,0.3,0.3);
        glTranslatef(STRAIGHT_LENGTH, 1+0.5*POLE_HEIGHT-0.5*DROP_HEIGHT, 0.5*SPIRAL_WIDTH);
        glRotatef(-360*time/POLE_PERIOD,0,1,0);
        glRotatef(90, 1, 0, 0);
        drawGear(20, 0.1*POLE_WIDTH, POLE_WIDTH+0.5, 2, 100);
    glPopMatrix();

    // bottom of the pole
    glPushMatrix();
        glColor3f(0.3,0.3,0.3);
        glTranslatef(STRAIGHT_LENGTH, -1-0.5*POLE_HEIGHT-0.5*DROP_HEIGHT, 0.5*SPIRAL_WIDTH);
        glRotatef(-360*time/POLE_PERIOD,0,1,0);
        glRotatef(90, 1, 0, 0);
        drawGear(20, 0.1*POLE_WIDTH, POLE_WIDTH+0.5, 2, 100);
    glPopMatrix();

    // spawn box
    glPushMatrix();
        glColor3f(0.3,0.3,0.3);
        glTranslatef(0.5*SPAWN_BOX_LENGTH+0.5*TILE_LENGTH, 0.5*SPAWN_HOLE_HEIGHT-TILE_HEIGHT, 0.5*TILE_WIDTH+TILE_HEIGHT);
        glRotatef(-360*time/POLE_PERIOD,0,0,1);
        drawGear(20, 1, 0.5*TILE_LENGTH-2, 4, 100);
    glPopMatrix();

    // despawn box
    glPushMatrix();
        glColor3f(0.3,0.3,0.3);
        glTranslatef(0.5*SPAWN_BOX_LENGTH+0.5*TILE_LENGTH, 0.5*SPAWN_HOLE_HEIGHT-TILE_HEIGHT-DROP_HEIGHT, 0.5*TILE_WIDTH+TILE_HEIGHT+SPIRAL_WIDTH);
        glRotatef(360*time/POLE_PERIOD,0,0,1);
        drawGear(20, 1, 0.5*TILE_LENGTH-2, 4, 100);
    glPopMatrix();
}