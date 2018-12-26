#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

/************************************
    Functions declarations start here
*************************************/

// timer callback func variables
#define carSpeedTimer (0)
#define carSpawnTimer (1)
#define tankMovementTimer (2)
//end of timer callback func variables

// callback functions
void onDisplay(void);

void onReshape(int w, int h);

void onKeyboardInput(unsigned char key, int x, int y);

void onKeyboardUp(unsigned char key, int x, int y);

void onMousePassive(int x, int y);

void tankShoot(int button, int state, int x, int y);

void onTimer(int timer);

#endif
