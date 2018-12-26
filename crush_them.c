#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbackFunctions.h"
#include "drawInitFunctions.h"
#include "drawFunctions.h"

int main(int argc, char **argv) {

    //initialization of glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //initialize Window
    glutInitWindowSize(1300, 700);
    glutInitWindowPosition(gs.WindowWidth / 2, gs.WindowHeight / 2);

    glutCreateWindow("Crush them!");
    //glutFullScreen();

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
