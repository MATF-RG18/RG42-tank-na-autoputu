#include "drawFunctions.h"
#include "lightingFunctions.h"
#include "drawInitFunctions.h"
#include "image.h"
#include "mathFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <string.h>

/************************************
    Functions definitions start here
*************************************/

void drawSquare(void) {
    struct Vector3f v3f = {.5f, .5f, .5f};
    glBegin(GL_QUADS);
    //blue - front
    glNormal3f(0, 1, 0);
    setVertexColor(0, 0, 1);
    glVertex3f(-v3f.x, 0, -v3f.z);
    glVertex3f(-v3f.x, 1, -v3f.z);
    glVertex3f(v3f.x, 1, -v3f.z);
    glVertex3f(v3f.x, 0, -v3f.z);

    //green - back
    glNormal3f(0, -1, 0);
    setVertexColor(0, 1, 0);
    glVertex3f(-v3f.x, 0, v3f.z);
    glVertex3f(-v3f.x, 1, v3f.z);
    glVertex3f(v3f.x, 1, v3f.z);
    glVertex3f(v3f.x, 0, v3f.z);

    //sides
    // purple - right
    glNormal3f(1.0f, 0.0, 0.0);
    setVertexColor(1, 0, 1);
    glVertex3f(v3f.x, 0, -v3f.z);
    glVertex3f(v3f.x, 1, -v3f.z);
    glVertex3f(v3f.x, 1, +v3f.z);
    glVertex3f(v3f.x, 0, +v3f.z);

    //brown- left
    glNormal3f(-1.0f, 0.0, 0.0);
    setVertexColor(1, 0.6f, 0);
    glVertex3f(-v3f.x, 0, -v3f.z);
    glVertex3f(-v3f.x, 1, -v3f.z);
    glVertex3f(-v3f.x, 1, +v3f.z);
    glVertex3f(-v3f.x, 0, +v3f.z);

    // top and bottom
    //white - bottom
    glNormal3f(0, -1, 0);
    setVertexColor(1, 1, 1);
    glVertex3f(-v3f.x, 0, v3f.z);
    glVertex3f(+v3f.x, 0, v3f.z);
    glVertex3f(+v3f.x, 0, -v3f.z);
    glVertex3f(-v3f.x, 0, -v3f.z);

    //yellow - top
    glNormal3f(0.0, 1.0f, 0.0);
    setVertexColor(1, 1, 0);
    glVertex3f(v3f.x, 1, +v3f.z);
    glVertex3f(-v3f.x, 1, +v3f.z);
    glVertex3f(-v3f.x, 1, -v3f.z);
    glVertex3f(v3f.x, 1, -v3f.z);
    glEnd();
}

void drawRoad(struct Road road, bool texturesEnabled) {
    struct Vector3f v3f = {.5f, .5f, .5f};
    if (texturesEnabled == false) {
        glPushMatrix();
        glTranslatef(road.roadPosition.x, road.roadPosition.y + v3f.y, road.roadPosition.z);
        glScalef(road.roadScale.x, road.roadScale.y, road.roadScale.z);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);


        setVertexColor(0.3f, 0.3f, 0.3f);
        glNormal3f(0, 1, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(-1, -1);
        glVertex3f(-v3f.x, -v3f.y, v3f.z);//bottom left
        glTexCoord2f(1, -1);
        glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
        glTexCoord2f(1, 1);
        glVertex3f(v3f.x, v3f.y, v3f.z);//top right
        glTexCoord2f(-1, 1);
        glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();
        glLineWidth(4);
        glBegin(GL_LINES);
        setVertexColor(1, 1, 1);
        //left line
        glNormal3f(0, 1, 0);
        glVertex3f(-v3f.x / 3, -v3f.y, (v3f.z - 0.01f));
        glVertex3f(-v3f.x / 3, v3f.y, (v3f.z - 0.01f));
        //right line
        glNormal3f(0, 1, 0);
        glVertex3f(v3f.x / 3, -v3f.y, (v3f.z - 0.01f));
        glVertex3f(v3f.x / 3, v3f.y, (v3f.z - 0.01f));
        glEnd();
        glPopMatrix();
    } else {
        glPushMatrix();
        glTranslatef(road.roadPosition.x, road.roadPosition.y + v3f.y, road.roadPosition.z);
        glScalef(road.roadScale.x, road.roadScale.y, road.roadScale.z);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);

        glLineWidth(1);

        glBindTexture(GL_TEXTURE_2D, names[0]);
        setVertexColor(.7f, .7f, .7f);
        glNormal3f(0, 1, 0);

        glBegin(GL_QUADS);
        glTexCoord2f(-1, -1);
        glVertex3f(-v3f.x, -v3f.y, v3f.z);//bottom left
        glTexCoord2f(1, -1);
        glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
        glTexCoord2f(1, 1);
        glVertex3f(v3f.x, v3f.y, v3f.z);//top right
        glTexCoord2f(-1, 1);
        glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    }
}

void drawMessage(char string[MAX_LEN], int x, int y) {
    glColor3f(1, 0, 0);
    glMatrixMode(GL_PROJECTION); // Take current project matrix
    glPushMatrix();  // Push so we work with new "copy" matrix
    glLoadIdentity(); // Identity
    glMatrixMode(GL_MODELVIEW); // Add modelMatrix to it
    glPushMatrix(); // push so we work with new "copy" matrix
    glLoadIdentity(); // identity
    gluOrtho2D(0.0, gs.WindowWidth, 0.0, gs.WindowHeight); // work within window
    //set the position of the text in the window using the x and y coordinates
    glRasterPos2i(x, y);
    //get the length of the string to display
    int len = (int) strlen(string);
    //loop to display character by character
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    glMatrixMode(GL_PROJECTION); // put Projection matrix back in
    glPopMatrix(); // Pop 2nd copy matrix
    glMatrixMode(GL_MODELVIEW); // Put Model back in
    glPopMatrix(); // Pop 1st copy matrix
    glutPostRedisplay(); // print all on screen
}

void drawCubeTank(struct Tank tank) {
    glPushMatrix();
    // Start matrix at the position of the tank
    glTranslatef(tank.tankPosition.x, tank.tankPosition.y, tank.tankPosition.z);
    // Save the tank-scale, we dont want that to apply to the turret and gun
    glPushMatrix();
    glScalef(tank.tankScale.x, tank.tankScale.y, tank.tankScale.z);
    drawSquare();
    glPopMatrix();
    // Move the matrix up by the tank height, so we get the turret ontop of the tank
    glTranslatef(0, tank.tankScale.y, 0);
    // This will rotate the turret and gun
    glRotatef(gs.tankMainPlayer.turretRotate.x, 0, 1, 0);
    struct Vector3f turretSize;
    turretSize.x = (tank.tankScale.x / 1.2f);
    turretSize.y = (tank.tankScale.y / 1.2f);
    turretSize.z = (tank.tankScale.z / 1.2f);
    // Save the turret-scale, we dont want that to apply to the gun
    glPushMatrix();
    glScalef(turretSize.x, turretSize.y, turretSize.z);
    drawSquare();
    glPopMatrix();

    // Dont really need to save matrix here, since this is the last transformations we do anyway
    glPushMatrix();
    float barrelLength = 1.5f;

    // Start by moving the barrel origin to the edge of the turret
    float barrelZPosition = (turretSize.z * 0.5f);
    // Then move the barrel by half its length, so that we push the rest of the barrel out of the turret
    barrelZPosition += barrelLength * 0.5f;

    // Move the barrel UP by half the turret-size, so that its centered on the turret
    float barrelYPosition = (turretSize.y * 0.5f);

    glTranslatef(0, barrelYPosition, -barrelZPosition);
    glScalef(0.2f, 0.2f, barrelLength);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    glPopMatrix();
}

void drawBullet(void) {
    glPushMatrix();
    glTranslatef(gs.bullet.bulletPosition.x, gs.bullet.bulletPosition.y, gs.bullet.bulletPosition.z);
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(.3f, .3f, .3f);
    glutSolidSphere(0.3f, 10, 10);
    glDisable(GL_LIGHT1);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glPopMatrix();
}

void drawCar(struct Car cars) {
    glPushMatrix();
    glTranslatef(cars.carPosition.x, cars.carPosition.y,
                 cars.carPosition.z); // use same Translate for Car and for Shield
    glPushMatrix();
    glScalef(cars.carScale.x, cars.carScale.y, cars.carScale.z);
    glRotatef(cars.carRotate.x, 1, 0, 0);
    glRotatef(cars.carRotate.y, 0, 1, 0);
    glRotatef(cars.carRotate.z, 0, 0, 1);
    drawSquare();
    glPopMatrix();
    if (cars.showShield == 1) {
        glPushMatrix();
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1, 0, 0, cars.shieldOpacity);
        glutSolidSphere(cars.carScale.y + 0.3f, 10, 10); // Spawns shield around car.
        glDisable(GL_BLEND);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }
    glPopMatrix();
}

void resetCar(int i) {
    gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand() % 3];
    gs.carArray[i].carPosition.z = gs.car.lastZPoint - 10; // reposition car
    gs.car.lastZPoint = (int) gs.carArray[i].carPosition.z; // last car spawn point.
}

void drawFence(struct Fence fence) {
    glPushMatrix();
    glTranslatef(fence.fencePosition.x, fence.fencePosition.y, fence.fencePosition.z);
    glScalef(fence.fenceScale.x, fence.fenceScale.y, fence.fenceScale.z);
    setVertexColor(0.51f, 0.25f, 0.0);
    glutSolidCube(1);
    glPopMatrix();
}

void drawSun(void) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(gs.sun.sunRotate.x, 1, 0, 0);
    glRotatef(gs.sun.sunRotate.y, 0, 1, 0);
    glRotatef(gs.sun.sunRotate.z, 0, 0, 1);
    glTranslatef(gs.sun.sunTranslate.x, gs.sun.sunTranslate.y, gs.sun.sunTranslate.z);
    setVertexColor(1, 1, 0);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}

void skyChangeFunction(void) {
    /* When sun is in center of sky, flag is 0 and after that sun is going down->light decreasing
     * When sun is down, flag is 1 and after that sun is going up -> light increasing
     */

    if (gs.sun.sunRotate.z >= 360) { // instead of moduo 360
        gs.sun.sunRotate.z = 0;
    }
    gs.sun.sunRotate.z += 0.3f;   //Math done on paper for this number

    //Decrement until first reaches 0, that will be night color
    if (gs.sky.flag == 0) {
        gs.sky.skyColor.x -= 0.001f;
        gs.sky.skyColor.y -= 0.001f;
        gs.sky.skyColor.z -= 0.001f;
        if (gs.sky.skyColor.x < 0)
            gs.sky.flag = 1;
    }
    if (gs.sky.flag == 1) {
        gs.sky.skyColor.x += 0.001f;
        gs.sky.skyColor.y += 0.001f;
        gs.sky.skyColor.z += 0.001f;
        if (gs.sky.skyColor.x > 0.6f)
            gs.sky.flag = 0;
    }
    //Increment until u reach day.. (0.6, 0.8, 1, 0) <- day color
    glClearColor(gs.sky.skyColor.x, gs.sky.skyColor.y, gs.sky.skyColor.z, 0);
}