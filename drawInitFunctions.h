//
// Created by aleksandar on 24.12.18..
//

#ifndef CRUSH_THEM_DRAWINITFUNCTIONS_H
#define CRUSH_THEM_DRAWINITFUNCTIONS_H

#include "drawFunctions.h"


void init(void);

void initRenderingObjects(void);

void tankInit(void);

void carsInit(void);

void skyInit(void);

void sunInit(void);

void roadInit(struct Road *road1, struct Road *road2, struct Road *road3, int posX, int sizeX);

void bulletInit(void);

void fenceInit(float x, int z, struct Fence *fence1);

#endif //CRUSH_THEM_DRAWINITFUNCTIONS_H