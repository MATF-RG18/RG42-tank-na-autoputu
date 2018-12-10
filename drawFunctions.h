#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H
#include <GL/gl.h>
#include <stdbool.h>
/************************************
    Macros definitions start here
*************************************/

#define MAX_CARS_ALLOWED 10
#define NOT_USED_VAR(X) (void)(X)



//Create game state.
struct gameState gs;
GLuint names[1]; // used for texture
/************************************
    Structs definitions start here
*************************************/

//3 vectors struct
struct Vector3f{
    float x;
    float y;
    float z;
};
struct Car{
    float carSpeed;
    int setOfCarXPositionsAllowedValues[3];
    int ZSpawnPoint;
    int numOfCars;
    int timeCarSpawn;
    struct Vector3f carScale;
    struct Vector3f carTranslate;
    struct Vector3f carRotate;
};
struct Tank{
    struct Vector3f tankTranslate;
    struct Vector3f tankScale;
    float tankSpeed;
    int v; // its used as vector of movement of tank,towards left, stands in spot, towards right -1, 0 , 1
    int prevDir;
    int currDir;
};
struct Road{
    struct Vector3f roadScale;
    struct Vector3f roadRotation;
    struct Vector3f roadTranslation;
};
struct Sky{
    struct Vector3f skyColor;
    int dayTimer;
    int flag;
};
struct Sun{
    struct Vector3f sunRotate;
    struct Vector3f sunTranslate;
    struct Vector3f lightCoef;
    int quadrant;
    float mod;
};
//Keeps info about whole game state
struct gameState{
    struct Car carArray[MAX_CARS_ALLOWED];
    struct Car car;
    struct Sun sun;
    struct Road road, road2, road3;
    struct Sky sky;
    struct Road rightSideRoad, rightSideRoad2, rightSideRoad3;
    struct Road leftSideRoad, leftSideRoad2, leftSideRoad3;
    struct Tank tankMainPlayer;
    int WindowWidth;
    int WindowHeight;
    int actionOnGoing;
    float cameraMovement;
    int numberOfCrushes;
    float lightModifier;
};

void init(void);
void initRenderingObjects();
void drawSquare();
void drawRoad(const struct Road road);
void drawCubeTank(const struct Tank tank);
void drawCar(const struct Car cars);
void drawSun();
void tankInit();
void roadInit();
void skyInit();
void carInit();
void drawScore();
void sunInit();
void skyChangeFunction();
void rightSideRoadInit();
void leftSideRoadInit();
void drawSideRoad(const struct Road road);
bool collisionCheck(struct Tank tank, struct Car car);
#endif
