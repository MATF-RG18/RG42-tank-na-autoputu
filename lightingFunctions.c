#include <GL/glut.h>
#include <GL/gl.h>
#include "lightingFunctions.h"
#include "drawFunctions.h"
#include "callbackFunctions.h"

void light(){

    //Light coeffs
    GLfloat light_position[] = {1, 1, 1, 0};
    GLfloat light_ambient[] = {0, 0, 0, 1};
    GLfloat light_diffuse[] = {1, 1, 1, 1};
    GLfloat light_specular[] = {1, 1, 1, 1};
    
    // Light parameters
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //? Can be in init or main? Dont need to call light this many times from onDisplay
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void setVertexColor(float R, float G, float B)
{
    GLfloat diffuse[] = {R - gs.lightModifier, G - gs.lightModifier, B - gs.lightModifier, 1};
    GLfloat ambient[] = {R + gs.lightModifier, G + gs.lightModifier, B + gs.lightModifier, 1};
    GLfloat specular[] = {1, 1, 1, 1};
    GLfloat shininess = 50;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
