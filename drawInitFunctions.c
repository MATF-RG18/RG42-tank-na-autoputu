//
// Created by aleksandar on 24.12.18..
//

#include "drawInitFunctions.h"
#include "mathFunctions.h"
#include "drawFunctions.h"
#include "image.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>

void init(void){
    initRenderingObjects();
    srand(time(NULL));
    glClearColor(gs.sky.skyColor.x, gs.sky.skyColor.y, gs.sky.skyColor.z, 0);
    glClearDepth(1.0f);
    glLineWidth(1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void tankInit(){
    gs.tankMainPlayer.tankPosition.x = 0;
    gs.tankMainPlayer.tankPosition.y = 0;
    gs.tankMainPlayer.tankPosition.z = 280;

    gs.tankMainPlayer.tankScale.x = 1;
    gs.tankMainPlayer.tankScale.y = 1;
    gs.tankMainPlayer.tankScale.z = 3;

    gs.tankMainPlayer.turretRotate.x = 0;

    gs.tankMainPlayer.tankSpeed = 30;
    gs.tankMainPlayer.currDir = 0;
    gs.tankMainPlayer.prevDir = 0;

    gs.lastMouseX = gs.WindowHeight/2;

    gs.tankMainPlayer.shoot = false;
}

void bulletInit(){

    glPushMatrix();
    glLoadIdentity();
        setBulletMatrix();
    glPopMatrix();

    gs.bullet.needToResetBullet = false;
    gs.bullet.Charging = 0;

    gs.bullet.bulletScale.x = 1;
    gs.bullet.bulletScale.y = 1;
    gs.bullet.bulletScale.z = 1;
}

void roadInit(struct Road *road1, struct Road *road2, struct Road *road3, int posX, int sizeX){
    road1->roadScale.x = road2->roadScale.x = road3->roadScale.x = sizeX;
    road1->roadScale.y = road2->roadScale.y = road3->roadScale.y = 1;
    road1->roadScale.z = road2->roadScale.z = road3->roadScale.z = 600; // road goes from 300 to -300

    road1->roadRotation.x = road2->roadRotation.x = road3->roadRotation.x = 90;
    road1->roadRotation.y = road2->roadRotation.y = road3->roadRotation.y = 0;
    road1->roadRotation.z = road2->roadRotation.z = road3->roadRotation.z = 0;

    road1->roadPosition.x = road2->roadPosition.x = road3->roadPosition.x = posX;
    road1->roadPosition.y = road2->roadPosition.y = road3->roadPosition.y = 0;

    road1->roadPosition.z = 0;
    road2->roadPosition.z = road1->roadPosition.z - road2->roadScale.z;
    road3->roadPosition.z = road2->roadPosition.z - road3->roadScale.z;
}

void carsInit(){
    // Init cars
    gs.car.numOfCars = 1; // used for drawing cars.

    gs.car.setOfCarXPositionsAllowedValues[0] = -3;
    gs.car.setOfCarXPositionsAllowedValues[1] = 0;
    gs.car.setOfCarXPositionsAllowedValues[2] = 3;
    gs.car.ZSpawnPoint = 300; // How far away from tank, cars should spawn
    gs.car.carSpeed = 30;
    for(int i = 0; i < MAX_CARS_ALLOWED; i++){
        gs.carArray[i].carScale.x = 1;
        gs.carArray[i].carScale.y = 1;
        gs.carArray[i].carScale.z = 1;

        gs.carArray[i].carRotate.x = 0;
        gs.carArray[i].carRotate.y = 180; //cars need to go forward
        gs.carArray[i].carRotate.z = 0;

        gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[i % 3];
        gs.carArray[i].carPosition.y = 0;
        gs.carArray[i].carPosition.z = gs.car.ZSpawnPoint + i*30;

        gs.car.showShield = 0;
        gs.car.shieldOpacity = 0;
    }
    //Timers for callback onTimer function
    gs.car.timeCarSpawn = 1000;   // 1 sec
    gs.car.lastZPoint = -200;
}

void skyInit(){
    gs.sky.skyColor.x = 0.6f;
    gs.sky.skyColor.y = 0.8f;
    gs.sky.skyColor.z = 1;
    gs.sky.flag = 0; // while its 0 its peak of day, when 1 its peak of night
}

void sunInit(){
    gs.sun.sunRotate.x = 0;
    gs.sun.sunRotate.y = 0;
    gs.sun.sunRotate.z = 0;
    gs.sun.sunTranslate.x = 0;
    gs.sun.sunTranslate.y = 45; // it doesnt go trough road with this value
    gs.sun.sunTranslate.z = -50;
}

void imageInit(){
    //Code taken from class and edited for own needs.
    Image * image;
    image = image_init(0,0);
    image_read(image, "sand.bmp");//TODO ABS PATH FOR CMAKE, RELATIVE OTHERWISE?
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}

void fenceInit(float x, int z, struct Fence *fence1){
    for(int i = 0; i<MAX_FENCE_ALLOWED; i++) {
        fence1[i].fencePosition.x = x;
        fence1[i].fencePosition.y = 0;
        fence1[i].fencePosition.z = z - i * 20;

        fence1[i].fenceScale.x = .5f;
        fence1[i].fenceScale.y = 3;
        fence1[i].fenceScale.z = 5;
    }
}

void initRenderingObjects(){
    roadInit(&gs.road, &gs.road2, &gs.road3, 0, 12);
    roadInit(&gs.leftSideRoad, &gs.leftSideRoad2, &gs.leftSideRoad3, -24, 36);
    roadInit(&gs.rightSideRoad, &gs.rightSideRoad2, &gs.rightSideRoad3, 24, 36);
    carsInit();
    tankInit();
    fenceInit(-6.2f, (int)gs.tankMainPlayer.tankPosition.z, gs.fenceLeftArray);
    fenceInit(+6.2f, (int)gs.tankMainPlayer.tankPosition.z, gs.fenceRightArray);
    skyInit();
    sunInit();
    bulletInit();
    imageInit();
    gs.cameraMovement = 0;
    gs.numberOfCrushes = 0;
    gs.gameover = false;
}
