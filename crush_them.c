#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbackFunctions.h"
#include "drawFunctions.h"

int main(int argc, char** argv){
    
    //initialization of glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //initialize Window
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(2000, 100); //TODO edit this to width/2, height/2 to center it on one screen
    glutCreateWindow("Crush them!");

    //callback functions
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyboardInput);
    //TODO ontimer
    // initialize stuff
    init();

    // start program
    glutMainLoop(); 
    return 0;
}
