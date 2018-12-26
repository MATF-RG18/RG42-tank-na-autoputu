//
// Created by aleksandar on 24.12.18..
//

#ifndef CRUSH_THEM_MATHFUNCTIONS_H
#define CRUSH_THEM_MATHFUNCTIONS_H

#include <stdbool.h>
#include "drawFunctions.h"

void setBulletMatrix(void);

void setSunMatrix(void);

bool collisionCheck(struct Vector3f a, struct Vector3f b, struct Vector3f aSize, struct Vector3f bSize);

struct Vector3f normalize(struct Vector3f);

struct Vector3f getDirection(struct Vector3f a, struct Vector3f b);


#endif //CRUSH_THEM_MATHFUNCTIONS_H