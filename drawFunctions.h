#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H

#include <GL/glut.h>
#include <stdbool.h>

/************************************
    Macro definitions start here
*************************************/

#define MAX_CARS_ALLOWED 10
#define NOT_USED_VAR(X) (void)(X)
#define MAX_LEN 50
#define MAX_FENCE_ALLOWED 45

//Create game state.
struct gameState gs;
GLuint names[1]; // used for texture

/************************************
    Structs declarations start here
*************************************/

struct Vector3f {
    float x;
    float y;
    float z;
};

struct Car {
    float carSpeed;
    int setOfCarXPositionsAllowedValues[3];
    int ZSpawnPoint;
    int numOfCars;
    int timeCarSpawn;
    struct Vector3f carScale;
    struct Vector3f carPosition;
    struct Vector3f carRotate;
    int showShield;
    float shieldOpacity;
    long long lastZPoint;
};

struct Tank {
    struct Vector3f tankPosition;
    struct Vector3f tankScale;
    struct Vector3f turretRotate; //can be moved to turret struct if it gets made
    float tankSpeed;
    int prevDir;
    int currDir;
    bool shoot;
};

struct Road {
    struct Vector3f roadScale;
    struct Vector3f roadRotation;
    struct Vector3f roadPosition;
};

struct Sky {
    struct Vector3f skyColor;
    int flag;
};

struct Sun {
    struct Vector3f sunRotate;
    struct Vector3f sunTranslate;
    struct Vector3f sunPosition;
    struct Vector3f lightDirection;
};

struct Bullet {
    struct Vector3f bulletPosition;
    struct Vector3f bulletDirection;
    struct Vector3f bulletScale;
    bool needToResetBullet;
    int Charging;
};

struct Fence {
    struct Vector3f fencePosition;
    struct Vector3f fenceScale;
};

struct gameState {
    struct Car carArray[MAX_CARS_ALLOWED];
    struct Car car;
    struct Sun sun;
    struct Road road, road2, road3;
    struct Sky sky;
    struct Road rightSideRoad, rightSideRoad2, rightSideRoad3;
    struct Road leftSideRoad, leftSideRoad2, leftSideRoad3;
    struct Tank tankMainPlayer;
    struct Bullet bullet;
    struct Fence fenceLeftArray[MAX_FENCE_ALLOWED], fenceRightArray[MAX_FENCE_ALLOWED];
    int WindowWidth;
    int WindowHeight;
    int actionOnGoing;
    float cameraMovement;
    int numberOfCrushes;
    int lastMouseX;
    bool gameover;
};


/************************************
    Functionss declarations start here
*************************************/

void drawBullet(void);

void drawSquare(void);

void drawRoad(struct Road road, bool texturesEnabled);

void drawCubeTank(struct Tank tank);

void drawCar(struct Car cars);

void drawSun(void);

void drawMessage(char string[MAX_LEN], int x, int y);

void resetCar(int i);

void skyChangeFunction(void);

void drawFence(struct Fence fence);

#endif
