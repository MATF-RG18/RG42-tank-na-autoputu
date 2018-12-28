#include "callbackFunctions.h"
#include "drawFunctions.h"
#include "lightingFunctions.h"
#include "drawInitFunctions.h"
#include "mathFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

/************************************
    Functions definitions start here
*************************************/

void onDisplay(void) {
    //remove old content
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //setting camera position and where it looks at
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 4, gs.tankMainPlayer.tankPosition.z + 8, // camera position
              0, 0, gs.cameraMovement - 10, // camera looks at this spot
              0, 1, 0  // normal vector
    );

    light();

    //Rendering section

    drawRoad(gs.road, false);
    drawRoad(gs.leftSideRoad, true);
    drawRoad(gs.rightSideRoad, true);
    drawRoad(gs.road2, false);
    drawRoad(gs.rightSideRoad2, true);
    drawRoad(gs.leftSideRoad2, true);
    drawRoad(gs.road3, false);
    drawRoad(gs.rightSideRoad3, true);
    drawRoad(gs.leftSideRoad3, true);


    glDisable(GL_LIGHTING);
    char scoreAsString[32];
    int a = sprintf(scoreAsString, "Crushed: %d", gs.numberOfCrushes);
    if (a < 0)
        exit(1);
    drawMessage(scoreAsString, gs.WindowWidth - (13 * 12), gs.WindowHeight - 30);
    if (gs.gameover == true && gs.actionOnGoing == 0) {
        drawMessage("Game over", gs.WindowWidth / 2 - 60, gs.WindowHeight / 2);
        glutSwapBuffers();
        sleep(3);
        exit(0);
    }
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHT0);
        lightForSun();
        drawSun();
    glDisable(GL_LIGHT1);
    glEnable(GL_LIGHT0);

    for (int i = 0; i < gs.car.numOfCars; i++) {
        drawCar(gs.carArray[i]);
    }

    drawCubeTank(gs.tankMainPlayer);

    if (gs.tankMainPlayer.shoot)
        drawBullet();

    for (int i = 0; i < MAX_FENCE_ALLOWED; i++) {
        drawFence(gs.fenceLeftArray[i]);
        drawFence(gs.fenceRightArray[i]);
    }
    glutSwapBuffers();
}

void onReshape(int w, int h) {
    gs.WindowWidth = w;
    gs.WindowHeight = h;
    glViewport(0, 0, gs.WindowWidth, gs.WindowHeight); //width and height of screen where stuff is drawn in end
    //projection of what camera sees
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, gs.WindowWidth / (GLfloat) gs.WindowHeight, 1, 300.0f); // angle, ratio, near clip, far clip
}

void onKeyboardInput(unsigned char key, int x, int y) {
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch (key) {
        case 27: // ESC BUTTON
            glDeleteTextures(2, names);
            exit(0);
        case 'g': // GO
        case 'G':
            if (gs.actionOnGoing == 0) {
                glutTimerFunc((unsigned) gs.car.carSpeed, onTimer, carSpeedTimer);
                if (gs.car.numOfCars < MAX_CARS_ALLOWED)
                    glutTimerFunc((unsigned) gs.car.timeCarSpawn, onTimer, carSpawnTimer);
                glutTimerFunc((unsigned) gs.tankMainPlayer.tankSpeed, onTimer, tankMovementTimer);
                glutPostRedisplay();
                gs.actionOnGoing = 1;
            }
            break;
        case 'p': // PAUSE
        case 'P':
            if (gs.actionOnGoing == 1) {
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
        case 'f':
        case 'F':
            if(gs.actionOnGoing == false && gs.fullscreen == false){
                glutFullScreen();
                glutPostRedisplay();
                gs.fullscreen = true;
            }else if(gs.actionOnGoing == false && gs.fullscreen == true){
                glutReshapeWindow(1300, 700);
                glutPostRedisplay();
                gs.fullscreen = false;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void onKeyboardUp(unsigned char key, int x, int y) {
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    switch (key) {
        // left
        case 'a':
        case 'A':
            if (gs.tankMainPlayer.currDir == -1) {
                gs.tankMainPlayer.currDir = gs.tankMainPlayer.prevDir;
                gs.tankMainPlayer.prevDir = 0;
            }
            break;
            // right
        case 'd':
        case 'D':
            if (gs.tankMainPlayer.currDir == 1) {
                gs.tankMainPlayer.currDir = gs.tankMainPlayer.prevDir;
                gs.tankMainPlayer.prevDir = 0;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void tankShoot(int button, int state, int x, int y) {
    NOT_USED_VAR(x);
    NOT_USED_VAR(y);
    if (gs.actionOnGoing == 1) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                gs.tankMainPlayer.shoot = true;
                if (gs.bullet.Charging == 0 && gs.tankMainPlayer.shoot) {
                    glPushMatrix();
                    glLoadIdentity();
                    setBulletMatrix();
                    glPopMatrix();
                }
            }
        }
    }
}

void onMousePassive(int x, int y) {
    NOT_USED_VAR(y);
    if (gs.actionOnGoing == 0)
        return;
    gs.tankMainPlayer.turretRotate.x = 0.1f * (gs.lastMouseX - x);
    gs.lastMouseX = x;
    gs.lastMouseX = gs.WindowWidth / 2;
}

void onTimer(int timer) {
    if (timer == carSpeedTimer) {
        skyChangeFunction();
        // this timer moves cars, checks collisions with tank/bomb and re spawns cars.
        if (gs.actionOnGoing) {
            if (gs.tankMainPlayer.shoot) { // same comment as one in tankMovementTimer
                gs.bullet.bulletPosition.x -= gs.bullet.bulletDirection.x;
                gs.bullet.bulletPosition.y -= 0.03f;
                gs.bullet.bulletPosition.z -= gs.bullet.bulletDirection.z;
                gs.bullet.Charging++;
                gs.bullet.needToResetBullet = false;

                if (gs.bullet.bulletPosition.y <= 0) { // 0 on Y is when bomb reaches floor
                    gs.bullet.needToResetBullet = true;
                    gs.bullet.Charging = 0;
                }
            }
            for (int i = 0; i < gs.car.numOfCars; i++) {
                if (!gs.bullet.needToResetBullet &&
                    collisionCheck(gs.bullet.bulletPosition, gs.carArray[i].carPosition, gs.bullet.bulletScale,
                                   gs.carArray[i].carScale)) {
                    gs.bullet.needToResetBullet = true;
                    gs.bullet.Charging = 0;
                    if (gs.carArray[i].showShield == 0) {
                        resetCar(i);
                        gs.numberOfCrushes++;
                    }
                    if (gs.carArray[i].shieldOpacity > 0) {
                        gs.carArray[i].shieldOpacity -= 0.5f;
                        if (gs.carArray[i].shieldOpacity == 0)
                            gs.carArray[i].showShield = 0;
                    }
                    break;
                }
                for (int j = 0; j < MAX_FENCE_ALLOWED; j++) {
                    if (collisionCheck(gs.bullet.bulletPosition, gs.fenceLeftArray[j].fencePosition,
                                       gs.bullet.bulletScale, gs.fenceLeftArray[j].fenceScale)) {
                        gs.bullet.needToResetBullet = true;
                        gs.bullet.Charging = 0;
                    } else if (collisionCheck(gs.bullet.bulletPosition, gs.fenceRightArray[j].fencePosition,
                                              gs.bullet.bulletScale, gs.fenceRightArray[j].fenceScale)) {
                        gs.bullet.needToResetBullet = true;
                        gs.bullet.Charging = 0;
                    }
                }
                gs.carArray[i].carPosition.z += 1;
                if (gs.carArray[i].carPosition.z - 10 >= gs.tankMainPlayer.tankPosition.z + 10) { // car is not crushed and it moved behind tank
                    if (gs.numberOfCrushes >= 10) {
                        if (gs.carArray[i].shieldOpacity < 1) {
                            gs.carArray[i].shieldOpacity += 0.5f;
                            gs.carArray[i].showShield = 1;
                        }
                    }
                    resetCar(i);
                } else if (collisionCheck(gs.tankMainPlayer.tankPosition, gs.carArray[i].carPosition,
                                          gs.tankMainPlayer.tankScale, gs.carArray[i].carScale)) {
                    if (gs.carArray[i].showShield == 1 && gs.carArray[i].shieldOpacity == 1) { // If there is collision with car with full shield. Game over.
                        gs.gameover = true;
                        gs.actionOnGoing = 0;
                    } else {
                        if (gs.carArray[i].shieldOpacity > 0)
                            gs.carArray[i].shieldOpacity -= 0.5f;
                        if (gs.carArray[i].shieldOpacity == 0)
                            gs.carArray[i].showShield = 0;
                    }
                    gs.numberOfCrushes++;
                    resetCar(i);
                }
            }
            if (gs.bullet.needToResetBullet) {
                gs.tankMainPlayer.shoot = false;
            }
        }
    } else if (timer == carSpawnTimer) {//This timer makes cars spawn nicely on beginning
        gs.car.numOfCars++;
    } else if (timer == tankMovementTimer) {
        //this timer moves tank left right on keyboard press, keeps tank moving forward and makes road infinite length
        //reason to have shoot here as well as in carSpeedTimer
        // is that collision can be missed in one timer only..
        if (gs.actionOnGoing) {
            if (gs.tankMainPlayer.shoot) {
                gs.bullet.bulletPosition.x -= gs.bullet.bulletDirection.x;
                gs.bullet.bulletPosition.y -= 0.03f;
                gs.bullet.bulletPosition.z -= gs.bullet.bulletDirection.z;
                gs.bullet.Charging++;
                gs.bullet.needToResetBullet = false;
                if (gs.bullet.bulletPosition.y <= 0) { //  0 on Y is when bomb reaches floor
                    gs.bullet.needToResetBullet = true;
                    gs.bullet.Charging = 0;
                }
                for (int i = 0; i < gs.car.numOfCars; i++) {
                    if (!gs.bullet.needToResetBullet &&
                        collisionCheck(gs.bullet.bulletPosition, gs.carArray[i].carPosition,
                                       gs.bullet.bulletScale, gs.carArray[i].carScale)) {
                        gs.bullet.Charging = 0;
                        if (gs.carArray[i].showShield == 0) {
                            resetCar(i);
                            gs.numberOfCrushes++;
                        }
                        if (gs.carArray[i].shieldOpacity > 0) {
                            gs.carArray[i].shieldOpacity -= 0.5f;
                            if (gs.carArray[i].shieldOpacity == 0)
                                gs.carArray[i].showShield = 0;
                        }
                        gs.bullet.needToResetBullet = true;
                        break;
                    }
                }
                if (gs.bullet.needToResetBullet) {
                    gs.tankMainPlayer.shoot = false;
                }
            }
            // moves tank left and right when keyboard input comes in.
            if (gs.tankMainPlayer.currDir == -1) {
                if (gs.tankMainPlayer.tankPosition.x >= -3.8f)
                    gs.tankMainPlayer.tankPosition.x -= 0.2f;
            } else if (gs.tankMainPlayer.currDir == 1) {
                if (gs.tankMainPlayer.tankPosition.x <= 3.8f)
                    gs.tankMainPlayer.tankPosition.x += 0.2f;
            }
            gs.tankMainPlayer.tankPosition.z -= 1; // keeps moving tank forward
            gs.cameraMovement -= 1; // keeps moving camera with tank
            //makes road infinite
            if (gs.tankMainPlayer.tankPosition.z == gs.road2.roadPosition.z) {
                fenceInit(gs.fenceLeftArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceLeftArray);
                fenceInit(gs.fenceRightArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceRightArray);
                // Road 1 should be copied in back, behind road 3
                gs.road.roadPosition.z = gs.road3.roadPosition.z - gs.road.roadScale.z;
                gs.leftSideRoad.roadPosition.z = gs.leftSideRoad3.roadPosition.z - gs.leftSideRoad.roadScale.z;
                gs.rightSideRoad.roadPosition.z = gs.rightSideRoad3.roadPosition.z - gs.rightSideRoad.roadScale.z;
            } else if (gs.tankMainPlayer.tankPosition.z == gs.road3.roadPosition.z) {
                fenceInit(gs.fenceLeftArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceLeftArray);
                fenceInit(gs.fenceRightArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceRightArray);
                // Road 2 should be copied in back, behind road 1
                gs.road2.roadPosition.z = gs.road.roadPosition.z - gs.road2.roadScale.z;
                gs.leftSideRoad2.roadPosition.z = gs.leftSideRoad.roadPosition.z - gs.leftSideRoad2.roadScale.z;
                gs.rightSideRoad2.roadPosition.z = gs.rightSideRoad.roadPosition.z - gs.rightSideRoad2.roadScale.z;
            } else if (gs.tankMainPlayer.tankPosition.z == gs.road.roadPosition.z) {
                fenceInit(gs.fenceLeftArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceLeftArray);
                fenceInit(gs.fenceRightArray[0].fencePosition.x, (int) gs.tankMainPlayer.tankPosition.z,
                          gs.fenceRightArray);
                // Road 3 should be copied in back, behind road 2
                gs.road3.roadPosition.z = gs.road2.roadPosition.z - gs.road3.roadScale.z;
                gs.leftSideRoad3.roadPosition.z = gs.leftSideRoad2.roadPosition.z - gs.leftSideRoad3.roadScale.z;
                gs.rightSideRoad3.roadPosition.z = gs.rightSideRoad2.roadPosition.z - gs.rightSideRoad3.roadScale.z;
            }
        }
    } else
        return;
    if (gs.actionOnGoing) {
        glutPostRedisplay();
        if (timer == carSpeedTimer)
            glutTimerFunc((unsigned) gs.car.carSpeed, onTimer, carSpeedTimer);
        else if (timer == carSpawnTimer && (gs.car.numOfCars < MAX_CARS_ALLOWED))
            glutTimerFunc((unsigned) gs.car.timeCarSpawn, onTimer, carSpawnTimer);
        else if (timer == tankMovementTimer)
            glutTimerFunc((unsigned) gs.tankMainPlayer.tankSpeed, onTimer, tankMovementTimer);
    }
}
