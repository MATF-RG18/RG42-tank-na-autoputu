#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H

/************************************
    Macros definitions start here
*************************************/

#define MAX_CARS_ALLOWED 10
#define NOT_USED_VAR(X) (void)(X)

// timer callback func variables
#define timerID (0)
#define timerID1 (1)
#define timerID2 (2)
#define timerID3 (3)
//end of timer callback func variables

//Create game state.
struct gameState gs;

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
    struct Vector3f carPosition;
    struct Vector3f carRotate;
};
struct Tank{
    struct Vector3f tankTranslate;
    struct Vector3f tankScale;
    float tankSpeed;
};
struct Road{
    struct Vector3f roadScale;
    struct Vector3f roadRotation;
    struct Vector3f roadTranslation;
};
//Keeps info about whole game state
struct gameState{
    struct Car carArray[MAX_CARS_ALLOWED];
    struct Car car;
    struct Road road;
    struct Road road2;
    struct Road road3;
    struct Tank tankMainPlayer;
    int WindowWidth;
    int WindowHeight;
    int actionOnGoing;
    float cameraMovement;
    int numberOfCrushes;
};

void init(void);
void initRenderingObjects();
void drawRoad(const struct Road road);
void drawCubeTank(const struct Tank tank);
void drawCar(const struct Car cars);
void drawSun();
#endif