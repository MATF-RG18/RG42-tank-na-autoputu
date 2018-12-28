//
// Created by aleksandar on 24.12.18..
//

#include "mathFunctions.h"
#include "drawFunctions.h"
#include <stdbool.h>
#include <GL/glut.h>
#include <math.h>

bool collisionCheck(struct Vector3f a, struct Vector3f b, struct Vector3f aSize, struct Vector3f bSize) {
    // Collision x-axis
    bool collisionX = a.x + aSize.x >= b.x && b.x + bSize.x >= a.x;
    // Collision y-axis
    bool collisionY = a.y + aSize.y >= b.y && b.y + bSize.y >= a.y;
    //Collision z-axis
    bool collisionZ = a.z + aSize.z >= b.z && b.z + bSize.z >= a.z;
    // Collision only if on all three axes

    return collisionX && collisionY && collisionZ;
}

struct Vector3f getDirection(struct Vector3f a, struct Vector3f b) {
    struct Vector3f result = b;
    result.x -= a.x;
    result.y -= a.y;
    result.z -= a.z;
    return normalize(result);
}

struct Vector3f normalize(struct Vector3f a) {
    float len = (float) (sqrt((a.x * a.x) + (a.y * a.y) + (a.z + a.z)));
    struct Vector3f result;
    if (len == 0) {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    result.x = a.x / len;
    result.y = a.y / len;
    result.z = a.z / len;
    return result;
}

void setBulletMatrix(void) {
    // Start matrix at the position of the tank
    glTranslatef(gs.tankMainPlayer.tankPosition.x, gs.tankMainPlayer.tankPosition.y, gs.tankMainPlayer.tankPosition.z);

    // Move the matrix up by the tank height, so we get the turret ontop of the tank
    glTranslatef(0, gs.tankMainPlayer.tankScale.y, 0);

    // This will rotate the turret and gun
    glRotatef(gs.tankMainPlayer.turretRotate.x, 0, 1, 0);
    struct Vector3f turretSize;
    turretSize.x = gs.tankMainPlayer.tankScale.x / 1.2f;
    turretSize.y = gs.tankMainPlayer.tankScale.y / 1.2f;
    turretSize.z = gs.tankMainPlayer.tankScale.z / 1.2f;

    float barrelLength = 1.5f;

    // Start by moving the barrel origin to the edge of the turret
    float barrelZPosition = turretSize.z * 0.5f;
    // Then move the barrel by half its lenght, so that we push the rest of the barrel out of the turret
    barrelZPosition += barrelLength * 0.5f;

    // Move the barrel UP by half the turret-size, so that its centered on the turret
    float barrelYPosition = turretSize.y * 0.5f;
    glTranslatef(0, barrelYPosition, -barrelZPosition);

    GLfloat bulletMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, bulletMatrix);

    gs.bullet.bulletPosition.x = bulletMatrix[12];
    gs.bullet.bulletPosition.y = bulletMatrix[13];
    gs.bullet.bulletPosition.z = bulletMatrix[14];
    
    gs.bullet.bulletDirection.x = (bulletMatrix[8]*1.3);
    gs.bullet.bulletDirection.y = (bulletMatrix[9]*1.3);
    gs.bullet.bulletDirection.z = (bulletMatrix[10]*1.3);
    
}

void setSunMatrix(void) {
    glRotatef(gs.sun.sunRotate.x, 1, 0, 0);
    glRotatef(gs.sun.sunRotate.y, 0, 1, 0);
    glRotatef(gs.sun.sunRotate.z, 0, 0, 1);
    glTranslatef(gs.sun.sunTranslate.x, gs.sun.sunTranslate.y,
                 gs.sun.sunTranslate.z + gs.tankMainPlayer.tankPosition.z);
    GLfloat sunPositionMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, sunPositionMatrix);

    gs.sun.sunPosition.x = sunPositionMatrix[12];
    gs.sun.sunPosition.y = sunPositionMatrix[13];
    gs.sun.sunPosition.z = sunPositionMatrix[14];
    
    struct Vector3f direction = getDirection(gs.tankMainPlayer.tankPosition, gs.sun.sunPosition);
    gs.sun.lightDirection.x = direction.x;
    gs.sun.lightDirection.y = direction.y;
    gs.sun.lightDirection.z = direction.z;
}

