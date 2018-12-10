#include "callbackFunctions.h"
#include "drawFunctions.h"
#include "lightingFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "image.h"

/************************************
    Functions definitions start here
*************************************/

void onDisplay(void){
    //Light position
    
    //remove old content
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setting camera position and where it looks at
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  0, 3, gs.tankMainPlayer.tankTranslate.z+8, // camera position 
                0, 0, gs.cameraMovement-10, // camera looks at this spot
                0, 1, 0  // normal vector 
            );

    light();
    //Rendering section

    drawRoad(gs.road);
    drawRoad(gs.road2);
    drawRoad(gs.road3);
    drawSideRoad(gs.rightSideRoad);
    drawSideRoad(gs.rightSideRoad2);
    drawSideRoad(gs.rightSideRoad3);
    drawSideRoad(gs.leftSideRoad);
    drawSideRoad(gs.leftSideRoad2);
    drawSideRoad(gs.leftSideRoad3);

    glDisable(GL_LIGHTING);
    drawScore();
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHT0);
    lightForSun();
    drawSun();
    glDisable(GL_LIGHT1);

    glEnable(GL_LIGHT0);
    
    for (int i = 0; i < gs.car.numOfCars; i++){
        drawCar(gs.carArray[i]); 
    }
    
    drawCubeTank(gs.tankMainPlayer);
    // draw all on main buffer
    glutSwapBuffers();
}

void onReshape(int w, int h){
    gs.WindowWidth = w;
    gs.WindowHeight = h;
    glViewport(0,0, gs.WindowWidth, gs.WindowHeight); //width and height of screen where stuff is drawn in end
    //projection of what camera sees
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, gs.WindowWidth/(GLfloat)gs.WindowHeight, 1, 300.0); // angle, ratio, near clip, far clip
}
void onKeyboardInput(unsigned char key, int x, int y){
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch(key){
        case 27: // ESC BUTTON
            glDeleteTextures(2, names);
            exit(0);
            break;
        case 'g': // GO
        case 'G':
            if(gs.actionOnGoing == 0){
                glutTimerFunc(gs.car.timeCarSpawn, onTimer, carSpeedTimer);
                glutTimerFunc(gs.car.carSpeed, onTimer, carSpawnTimer);
                glutTimerFunc(gs.tankMainPlayer.tankSpeed, onTimer, tankMovementTimer);
                glutTimerFunc(gs.sky.dayTimer, onTimer, skyColorTimer);
                glutPostRedisplay();
                gs.actionOnGoing = 1;
            }
            break;
        case 'p': // PAUSE
        case 'P':
            if(gs.actionOnGoing == 1){
                gs.actionOnGoing = 0;
            }
            break;
        // left
        case 'a': 
        case 'A':
            gs.tankMainPlayer.prevDir = gs.tankMainPlayer.currDir;
            gs.tankMainPlayer.currDir = -1;
            gs.tankMainPlayer.prevDir = 0;
            break;
        // right
        case 'd':
        case 'D':
            gs.tankMainPlayer.prevDir = gs.tankMainPlayer.currDir;
            gs.tankMainPlayer.currDir = 1;
            gs.tankMainPlayer.prevDir = 0;
            break;
    }    
    glutPostRedisplay();
}
void onKeyboardUp(unsigned char key, int x, int y){
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch(key){
        // left
        case 'a': 
        case 'A':
            if(gs.tankMainPlayer.currDir == -1){
                gs.tankMainPlayer.currDir = gs.tankMainPlayer.prevDir;
                gs.tankMainPlayer.prevDir = 0;
            }
            break;
        // right
        case 'd':
        case 'D':
            if(gs.tankMainPlayer.currDir == 1){
                gs.tankMainPlayer.currDir = gs.tankMainPlayer.prevDir;
                gs.tankMainPlayer.prevDir = 0;
            }
            break;
    }    
    glutPostRedisplay();
}
void onTimer(int timer){
    if (timer == carSpeedTimer){
        //this timer moves cars
        for(int i = 0; i < gs.car.numOfCars; i++){
            gs.carArray[i].carTranslate.z += 1;
            if(gs.carArray[i].carTranslate.z - 10 >= gs.tankMainPlayer.tankTranslate.z + 10){ // respawn car
                gs.carArray[i].carTranslate.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
                gs.carArray[i].carTranslate.z = gs.tankMainPlayer.tankTranslate.z - gs.car.ZSpawnPoint - 10;
            }else if(collisionCheck(gs.tankMainPlayer, gs.carArray[i])){
                gs.numberOfCrushes++;
                gs.carArray[i].carTranslate.z = gs.tankMainPlayer.tankTranslate.z - 70 - gs.car.ZSpawnPoint;// figure number instead -70 if needed
                gs.carArray[i].carTranslate.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
            }
        }
    }else if (timer == carSpawnTimer)    {
        //This timer makes cars spawn in proper timers
        if(gs.car.numOfCars <= MAX_CARS_ALLOWED)
            gs.car.numOfCars++;
        else
            return;
    }else if (timer == tankMovementTimer){
        if(gs.actionOnGoing){
            // moves tank left and right when keyboard input comes in.
            if (gs.tankMainPlayer.currDir == -1)
            {
                if(gs.tankMainPlayer.tankTranslate.x >= -3.8)
                    gs.tankMainPlayer.tankTranslate.x -= 0.2;
            }
            else if (gs.tankMainPlayer.currDir == 1)
            {
                if(gs.tankMainPlayer.tankTranslate.x <= 3.8)
                    gs.tankMainPlayer.tankTranslate.x += 0.2;
            }
            gs.tankMainPlayer.tankTranslate.z -= 1; // keeps moving tank forward
            gs.cameraMovement -= 1; // keeps moving camera with tank
            //makes road infinite
            if(gs.tankMainPlayer.tankTranslate.z == gs.road2.roadTranslation.z){
                // Road 1 should be copied in back, behind road 3
                gs.road.roadTranslation.z = gs.road3.roadTranslation.z - 2*gs.road.roadScale.z;
                gs.leftSideRoad.roadTranslation.z = gs.leftSideRoad3.roadTranslation.z - 2 * gs.leftSideRoad.roadScale.z;
                gs.rightSideRoad.roadTranslation.z = gs.rightSideRoad3.roadTranslation.z - 2 * gs.rightSideRoad.roadScale.z;
            }else if(gs.tankMainPlayer.tankTranslate.z == gs.road3.roadTranslation.z){
                // Road 2 should be copied in back, behind road 1
                gs.road2.roadTranslation.z = gs.road.roadTranslation.z - 2*gs.road2.roadScale.z;
                gs.leftSideRoad2.roadTranslation.z = gs.leftSideRoad.roadTranslation.z - 2 * gs.leftSideRoad2.roadScale.z;
                gs.rightSideRoad2.roadTranslation.z = gs.rightSideRoad.roadTranslation.z - 2 * gs.rightSideRoad2.roadScale.z;
            }else if(gs.tankMainPlayer.tankTranslate.z == gs.road.roadTranslation.z){
                // Road 3 should be copied in back, behind road 2
                gs.road3.roadTranslation.z = gs.road2.roadTranslation.z - 2*gs.road3.roadScale.z;
                gs.leftSideRoad3.roadTranslation.z = gs.leftSideRoad2.roadTranslation.z - 2 * gs.leftSideRoad3.roadScale.z;
                gs.rightSideRoad3.roadTranslation.z = gs.rightSideRoad2.roadTranslation.z - 2 * gs.rightSideRoad3.roadScale.z;
            }
        }
    }else if(timer == skyColorTimer){
        if(gs.actionOnGoing)
            skyChangeFunction();
    }else
        return;
    if(gs.actionOnGoing){
        glutPostRedisplay();
        if (timer == carSpeedTimer)
            glutTimerFunc(gs.car.carSpeed, onTimer, carSpeedTimer);
        else if (timer == carSpawnTimer)
            glutTimerFunc(gs.car.timeCarSpawn, onTimer, carSpawnTimer);
        else if(timer == tankMovementTimer)
            glutTimerFunc(gs.tankMainPlayer.tankSpeed, onTimer, tankMovementTimer);
        else if (timer == skyColorTimer)
            glutTimerFunc(gs.sky.dayTimer, onTimer, skyColorTimer);
    }
}
