#include "callbackFunctions.h"
#include "drawFunctions.h"
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

/************************************
    Functions definitions start here
*************************************/

void onDisplay(void){
    //remove old content
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setting camera position and where it looks at
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  0, 3, gs.tankMainPlayer.tankTranslate.z+10, // camera position 
                0, 0, gs.cameraMovement-20, // camera looks at this spot
                0, 1, 0  // normal vector 
            ); 
            //
    glutPostRedisplay();
    //Rendering section
    drawRoad(gs.road);
    drawRoad(gs.road2);
    drawRoad(gs.road3);
    drawCubeTank(gs.tankMainPlayer);

    for(int i = 0; i < gs.car.numOfCars; i++){
        drawCar(gs.carArray[i]); 
    }
    
    //drawSun(); // TODO fix sun :)
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
    gluPerspective(60, gs.WindowWidth/(GLfloat)gs.WindowHeight, 1, 200.0); // angle, ratio, near clip, far clip
}

void onKeyboardInput(unsigned char key, int x, int y){
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch(key){
        case 27: // ESC BUTTON
            printf("Number of cars crashed: %d\n", gs.numberOfCrushes);
            exit(0);
            break;
        case 'g': // GO
        case 'G':
            if(gs.actionOnGoing == 0){
                glutTimerFunc(gs.car.timeCarSpawn, onTimer, timerID1);
                glutTimerFunc(gs.car.carSpeed, onTimer, timerID); //TODO delta movement
                glutTimerFunc(gs.tankMainPlayer.tankSpeed, onTimer, timerID2);
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
        case 's': // slow down tank
        case 'S':
            break;
        // left
        case 'a': 
        case 'A': //TODO delta movement
            if(gs.tankMainPlayer.tankTranslate.x - 3 >= -4) // left wall is not hit yet
                gs.tankMainPlayer.tankTranslate.x -= 3;
            glutPostRedisplay();
            break;
        // right
        case 'd':
        case 'D'://TODO delta movement
            if(gs.tankMainPlayer.tankTranslate.x + 3 <= 4) // right wall is not hit yet
                gs.tankMainPlayer.tankTranslate.x += 3;
            glutPostRedisplay();
            break;
        case 'w':
        case 'W': // can be used to speed up tank
            break;
    }    
    glutPostRedisplay();
}

void onTimer(int timer){  
    //? For car colision with tank, cars and tank need to be same speed, why is that? Is it ok to be?
    if(timer == timerID){
        //this timer moves cars
        for(int i = 0; i < gs.car.numOfCars; i++){
            gs.carArray[i].carPosition.z += 1;
            if(gs.carArray[i].carPosition.z - 10 >= gs.tankMainPlayer.tankTranslate.z + 10){ // respawn car
                gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
                gs.carArray[i].carPosition.z = gs.tankMainPlayer.tankTranslate.z - gs.car.ZSpawnPoint;
            }else if(gs.carArray[i].carPosition.z == gs.tankMainPlayer.tankTranslate.z &&
                    gs.carArray[i].carPosition.x == gs.tankMainPlayer.tankTranslate.x &&
                    gs.carArray[i].carPosition.y == gs.tankMainPlayer.tankTranslate.y){ // Colision check
                gs.numberOfCrushes++;
                gs.carArray[i].carPosition.z = gs.tankMainPlayer.tankTranslate.z - 10 - gs.car.ZSpawnPoint;// figure number instead -10 if needed
                gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
            }

        }
    }else if(timer == timerID1){
        //This timer makes cars spawn in proper timers, by increasing number of cars that can be spawned.
        if(gs.car.numOfCars < MAX_CARS_ALLOWED)
            gs.car.numOfCars++;
        else
            return;
    }else if(timer == timerID2){
        if(gs.actionOnGoing){
            gs.tankMainPlayer.tankTranslate.z -= 1;
            gs.cameraMovement -= 1;
            if(gs.tankMainPlayer.tankTranslate.z == gs.road2.roadTranslation.z){
                // Road 1 should be copied in back, behind road 3
                gs.road.roadTranslation.z = gs.road3.roadTranslation.z - 2*gs.road.roadScale.z;
            }else if(gs.tankMainPlayer.tankTranslate.z == gs.road3.roadTranslation.z){
                // Road 2 should be copied in back, behind road 1
                gs.road2.roadTranslation.z = gs.road.roadTranslation.z - 2*gs.road2.roadScale.z;
            }else if(gs.tankMainPlayer.tankTranslate.z == gs.road.roadTranslation.z){
                // Road 3 should be copied in back, behind road 2
                gs.road3.roadTranslation.z = gs.road2.roadTranslation.z - 2*gs.road3.roadScale.z;
            }
        }
    }else
        return;

    if(gs.actionOnGoing){
        glutPostRedisplay();
        if(timer == timerID)
            glutTimerFunc(gs.car.carSpeed, onTimer, timerID);
        else if(timer == timerID1)
            glutTimerFunc(gs.car.timeCarSpawn, onTimer, timerID1);
        else if(timer == timerID2)
            glutTimerFunc(gs.tankMainPlayer.tankSpeed, onTimer, timerID2);
    }
}