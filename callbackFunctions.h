#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

/************************************
    Functions declarations start here
*************************************/

// timer callback func variables
#define carSpeedTimer (0)
#define carSpawnTimer (1)
#define tankMovementTimer (2)
#define skyColorTimer (3)
//end of timer callback func variables
//TODO move this into callbackfunctions?

// callback functions
void onDisplay(void);
void onReshape(int w, int h);
void onKeyboardInput(unsigned char key, int x, int y);
void onKeyboardUp(unsigned char key, int x, int y);
void onTimer(int timer);
#endif
