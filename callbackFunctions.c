#include "callbackFunctions.h"
#include "drawFunctions.h"
#include <GL/glut.h>


/************************************
    Functions definitions start here
*************************************/


void onDisplay(void){
    //remove old content
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setting camera position and where it looks at
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();// TODO:not best position of camera, if i need to put on begining of road
    gluLookAt(  0, 3, 20, // camera position 
                0, 0, 0, // camera looks at this spot
                0, 1, 0  // normal vector 
            ); 
    
    //Rendering section
    
    drawRoad(roadScale, roadRotation, roadTranslation);
    drawCubeTank(gs.tankMainPlayer);
    for(int i = 0; i < 15; i++)
        drawCar(gs.carNumber[i]);    
    // draw all on main buffer
    glutSwapBuffers();
}

void onReshape(int w, int h){
    gs.WindowWidth = w;
    gs.WindowHeight = h;
    glViewport(0,0, gs.WindowWidth, gs.WindowHeight); //width and height of screen where stuff is drawn in end
    initRenderingObjects(&roadScale, &roadRotation, &roadTranslation, &gs); // TODO Where should I have this function? Maybe in timer?, decide when u rebuild drawing cars
    
    //projection of what camera sees
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, gs.WindowWidth/(GLfloat)gs.WindowHeight, 1.0, 1000.0); // angle, ratio, near clip, far clip
}

void onKeyboardInput(unsigned char key, int x, int y){
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    //TODO a lot stuff here
    switch(key){
        case 27: // ESC BUTTON
            exit(0);
            break;
        case 'g': // GO
        case 'G':
            if(gs.actionOnGoing == 0){
                gs.actionOnGoing = 1;
                glutTimerFunc(timeInMS, onTimer, timerID);
            }
            break;
        case 's': // slow down instead of stop
        case 'S': //TODO different bind for stop!
            if(gs.actionOnGoing == 1){
                gs.actionOnGoing = 0;
            }
            break;
        // left
        case 'a': 
        case 'A': 
            if(gs.tankMainPlayer.tankTranslate.x > -4) // left wall is not hit yet
                gs.tankMainPlayer.tankTranslate.x--;
            break;
        // right
        case 'd':
        case 'D':
            if(gs.tankMainPlayer.tankTranslate.x < 4) // right wall is not hit yet
                gs.tankMainPlayer.tankTranslate.x++;
            break;
        case 'w':
        case 'W': // can be used to speed up
            break;
    }
    glutPostRedisplay();
}

void onTimer(int timer){
    //TODO a lot stuff here
    NOT_USED_VAR(timer);
    if(timerID == 0){
        // movement of road ID
    }
    glutPostRedisplay();
    glutTimerFunc(timeInMS, onTimer, timerID);
}

