#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbackFunctions.h"
#include "drawFunctions.h"
#include "lightingFunctions.h"

int main(int argc, char** argv){
    
    //initialization of glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //initialize Window
    //glutInitWindowSize(1300, 700);
    //glutInitWindowPosition(2000, 100); //TODO edit this to width/2, height/2 to center it on one screen
    
    glutCreateWindow("Crush them!");
    glutFullScreen();

    //callback functions
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyboardInput);
    glutPassiveMotionFunc(onMousePassive);
    glutMouseFunc(tankShoot);
    glutKeyboardUpFunc(onKeyboardUp);
    // initialize stuff
    
    init();
    // start program
    glutMainLoop(); 
    return 0;
}
