#include "callbackFunctions.h"
#include "drawFunctions.h"
#include "lightingFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

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
    glutPostRedisplay();
    //Rendering section
    drawRoad(gs.road);
    drawRoad(gs.road2);
    drawRoad(gs.road3);
    glDisable(GL_LIGHTING);
    drawScore();
    glEnable(GL_LIGHTING);
    //drawSun();
    //drawSideRoad(gs.sideRoad);
    //drawSideRoad(gs.sideRoad2);
    //drawSideRoad(gs.sideRoad3);

    for(int i = 0; i < gs.car.numOfCars; i++){
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
    gluPerspective(60, gs.WindowWidth/(GLfloat)gs.WindowHeight, 1, 200.0); // angle, ratio, near clip, far clip
}

void onKeyboardInput(unsigned char key, int x, int y){
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch(key){
        case 27: // ESC BUTTON
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
    if (timer == carSpeedTimer)
    {
        //this timer moves cars
        for(int i = 0; i < gs.car.numOfCars; i++){
            gs.carArray[i].carPosition.z += 1;
            if(gs.carArray[i].carPosition.z - 10 >= gs.tankMainPlayer.tankTranslate.z + 10){ // respawn car
                gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
                gs.carArray[i].carPosition.z = gs.tankMainPlayer.tankTranslate.z - gs.car.ZSpawnPoint;
            }else if(gs.carArray[i].carPosition.z == gs.tankMainPlayer.tankTranslate.z &&
                    gs.carArray[i].carPosition.x == gs.tankMainPlayer.tankTranslate.x &&
                    gs.carArray[i].carPosition.y == gs.tankMainPlayer.tankTranslate.y){ // Colision check TODO: not ideal way to check collision
                gs.numberOfCrushes++;
                gs.carArray[i].carPosition.z = gs.tankMainPlayer.tankTranslate.z - 70 - gs.car.ZSpawnPoint;// figure number instead -70 if needed
                gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
            }
        }
    }
    else if (timer == carSpawnTimer)
    {
        //This timer makes cars spawn in proper timers
        if(gs.car.numOfCars < MAX_CARS_ALLOWED)
            gs.car.numOfCars++;
        else
            return;
    }
    else if (timer == tankMovementTimer)
    {
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
    }else if(timer == skyColorTimer){
        
        if(gs.actionOnGoing){
            
            //Decerement until first reaches 0, that will be night color
            if (gs.sky.flag == 0)
            {
                gs.sky.skyColor.x = (gs.sky.skyColor.x - 0.001);
                gs.sky.skyColor.y = (gs.sky.skyColor.y - 0.001);
                gs.sky.skyColor.z = (gs.sky.skyColor.z - 0.001);
                if (gs.lightModifier < 0.4)
                    gs.lightModifier += 0.001;
                if(gs.sky.skyColor.x < 0)
                    gs.sky.flag = 1;
            }
            if (gs.sky.flag == 1)
            {
                gs.sky.skyColor.x = (gs.sky.skyColor.x + 0.001);
                gs.sky.skyColor.y = (gs.sky.skyColor.y + 0.001);
                gs.sky.skyColor.z = (gs.sky.skyColor.z + 0.001);
                if (gs.lightModifier > 0)
                    gs.lightModifier -= 0.001;
                if(gs.sky.skyColor.x > 0.6)
                    gs.sky.flag = 0;
            }
            //Increment until u reach day.. (0.6, 0.8, 1, 0) <- day color
            glClearColor(gs.sky.skyColor.x, gs.sky.skyColor.y, gs.sky.skyColor.z, 0);
            glutPostRedisplay();
        }
    }
    else
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
