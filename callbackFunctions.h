#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

/************************************
    Struct init start here
*************************************/

struct gameState gs;
struct Vector3f roadScale;
struct Vector3f roadRotation;
struct Vector3f roadTranslation;
struct Tank tank;
/************************************
    Functions declarations start here
*************************************/

// callback functions
void onDisplay(void);
void onReshape(int w, int h);
void onKeyboardInput(unsigned char key, int x, int y);
void onTimer(int timer);
#endif
