#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H

/************************************
    Macros definitions start here
*************************************/

#define MAX_CARS_ALLOWED 512
#define NOT_USED_VAR(X) (void)(X)
// timer callback func variablesw
#define timerID (0)
#define timeInMS (500)
//end of timer callback func variables

/************************************
    Structs definitions start here?? I want definitions in .c and declarations in .h?
*************************************/

//3 vectors struct
struct Vector3f{
    float x;
    float y;
    float z;
};
struct Car{
    struct Vector3f carPosition;
    float carSpeed;
};
struct Tank{
    struct Vector3f tankTranslate;
    float tankSpeed;
};
//Keeps info about whole game state
struct gameState{
    struct Car carNumber[MAX_CARS_ALLOWED];
    struct Tank tankMainPlayer;
    int WindowWidth;
    int WindowHeight;
    int yi;
    int actionOnGoing;
};

void init(void);
void initRenderingObjects(struct Vector3f *aScale, struct Vector3f *aRotation, struct Vector3f *aTranslation,struct gameState *gs);
void drawRoad(const struct Vector3f aScale,const struct Vector3f aRotation,const struct Vector3f aTranslation);
void drawCubeTank(const struct Tank tank);
void drawCar(const struct Car cars);

#endif