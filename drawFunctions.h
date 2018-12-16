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
    int showShield;
    float shieldOpacity;
    int lastZPoint;
    int lastCar;
};
struct Tank{
    struct Vector3f tankTranslate;
    struct Vector3f tankScale;
    struct Vector3f rotateTurret;
    float tankSpeed;
    int prevDir;
    int currDir;
    bool shoot;
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
    struct Vector3f sunPosition;
    struct Vector3f lightDirection;
};

struct Bullet{
    struct Vector3f position;
    struct Vector3f direction;
    struct Vector3f scale;
    bool needToResetBullet;
    int Charging;
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
    struct Bullet bullet;
    int WindowWidth;
    int WindowHeight;
    int actionOnGoing;
    float cameraMovement;
    int numberOfCrushes;
    float lightModifier;
    int lastMouseX;
    bool leftMouseDown;
    bool gameover;
};

void init(void);
void initRenderingObjects(void);
void drawSquare(void);
void drawRoad(const struct Road road);
void drawCubeTank(const struct Tank tank);
void drawCar(const struct Car cars);
void drawSun(void);
void tankInit(void);
void roadInit(void);
void skyInit(void);
void carInit(void);
void drawScore(void);
void sunInit(void);
void skyChangeFunction(void);
void setTankTurretMatrix(void);
void rightSideRoadInit(void);
void drawBullet(void);
struct Vector3f getDirection(struct Vector3f a, struct Vector3f b);
void leftSideRoadInit(void);
void drawSideRoad(const struct Road road);
bool collisionCheck(struct Vector3f a, struct Vector3f b, struct Vector3f asize, struct Vector3f bsize);
struct Vector3f normalize(struct Vector3f);
void drawEndGame(void);
void drawSingleColorSquare(void);
void bulletInit(void);
#endif
