#include "drawFunctions.h"
#include "callbackFunctions.h"
#include "lightingFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "image.h"
#include <math.h>

/************************************
    Functions definitions start here
*************************************/

void init(void){
    initRenderingObjects(); 
    glClearColor(gs.sky.skyColor.x, gs.sky.skyColor.y, gs.sky.skyColor.z, 0);
    glClearDepth(1.0);
    glLineWidth(1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/* Draw functions */
void drawSun(){
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

void skyChangeFunction(){
    if (gs.sun.sunRotate.z >= 360){ // instead of moduo 360
        gs.sun.sunRotate.z = 0;
    }
    gs.sun.sunRotate.z += 0.30;   //TODO: fix math in code, this number is paper math
    //Decerement until first reaches 0, that will be night color
    if (gs.sky.flag == 0)
    {
        gs.sky.skyColor.x = (gs.sky.skyColor.x - 0.001);
        gs.sky.skyColor.y = (gs.sky.skyColor.y - 0.001);
        gs.sky.skyColor.z = (gs.sky.skyColor.z - 0.001);
        if (gs.lightModifier < 0.4)
            gs.lightModifier += 0.001;
        if (gs.sky.skyColor.x < 0)
            gs.sky.flag = 1;
    }
    if (gs.sky.flag == 1)
    {
        gs.sky.skyColor.x = (gs.sky.skyColor.x + 0.001);
        gs.sky.skyColor.y = (gs.sky.skyColor.y + 0.001);
        gs.sky.skyColor.z = (gs.sky.skyColor.z + 0.001);
        if (gs.lightModifier > 0)
            gs.lightModifier -= 0.001;
        if (gs.sky.skyColor.x > 0.6)
            gs.sky.flag = 0;
    }
    //Increment until u reach day.. (0.6, 0.8, 1, 0) <- day color
    glClearColor(gs.sky.skyColor.x, gs.sky.skyColor.y, gs.sky.skyColor.z, 0);
    

    if (gs.sun.quadrant == 1)
    {
        gs.sun.lightCoef.x -= gs.sun.mod;
        if (gs.sun.lightCoef.x <= -1)
        {
            gs.sun.lightCoef.x = -1;
            gs.sun.quadrant = 2;
        }
    }
    else if (gs.sun.quadrant == 2)
    {
        gs.sun.lightCoef.x += gs.sun.mod;
        if (gs.sun.lightCoef.x >= 0)
        {
            gs.sun.lightCoef.x = 0;
            gs.sun.quadrant = 3;
        }
    }
    else if (gs.sun.quadrant == 3)
    {
        gs.sun.lightCoef.x += gs.sun.mod;
        if (gs.sun.lightCoef.x >= 1)
        {
            gs.sun.lightCoef.x = 1;
            gs.sun.quadrant = 4;
        }
    }
    else if (gs.sun.quadrant == 4)
    {
        gs.sun.lightCoef.x -= gs.sun.mod;
        if (gs.sun.lightCoef.x <= 0)
        {
            gs.sun.lightCoef.x = 0;
            gs.sun.quadrant = 1;
        }
    }
}
void drawSquare(){
        glBegin(GL_QUADS);
            //blue - front
            glNormal3f(0, 1, 0);
            setVertexColor(0, 0, 1);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 0, -0.5);

            //green - back
            glNormal3f(0, -1, 0);
            setVertexColor(0, 1, 0);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(0.5, 1, 0.5);
            glVertex3f(0.5, 0, 0.5);

            //sides
            // purple - right
            glNormal3f(1.0, 0.0, 0.0);
            setVertexColor(1, 0, 1);
            glVertex3f(0.5, 0, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(0.5, 0, +0.5);

            //brown- left
            glNormal3f(-1.0, 0.0, 0.0);
            setVertexColor(1, 0.6, 0);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 0, +0.5);

            // top and bottom
            //white - bottom
            glNormal3f(0, -1, 0);
            setVertexColor(1, 1, 1);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(+0.5, 0, +0.5);
            glVertex3f(+0.5, 0, -0.5);
            glVertex3f(-0.5, 0, -0.5);

            //yellow - top
            glNormal3f(0.0, 1.0, 0.0);
            setVertexColor(1, 1, 0);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
        glEnd();
}
void drawRoad(const struct Road road){
    glPushMatrix();
        struct Vector3f v3f = {.5, .5, .5};

        glTranslatef(road.roadTranslation.x, road.roadTranslation.y-1.5f, road.roadTranslation.z);
        glScalef(road.roadScale.x * 2.f, road.roadScale.y, road.roadScale.z * 2.f);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);

        drawSingleColorSquare();
        
        glLineWidth(4);
        glBegin(GL_LINES);
                setVertexColor(1, 1, 1);
                //left line
                glNormal3f(0, 1, 0);
                glVertex3f(-v3f.x/3, -v3f.y, v3f.z-1.01); // z-axis, -1.01 is just so we see lines
                glVertex3f(-v3f.x/3, v3f.y, v3f.z-1.01);  // they are just tiny bit above road it self
                //right line                                // better solution?
                glNormal3f(0, 1, 0);
                glVertex3f(v3f.x/3, -v3f.y, v3f.z-1.01); 
                glVertex3f(v3f.x/3, v3f.y, v3f.z-1.01);
        glEnd();
    glPopMatrix();
}

void drawSingleColorSquare(){
    glBegin(GL_QUADS);
        //blue - front
        glNormal3f(0, 1, 0);
        setVertexColor(.3, .3, .3);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 1, -0.5);
        glVertex3f(0.5, 1, -0.5);
        glVertex3f(0.5, 0, -0.5);

        //green - back
        glNormal3f(0, -1, 0);
        setVertexColor(.3, .3, .3);
        glVertex3f(-0.5, 0, +0.5);
        glVertex3f(-0.5, 1, +0.5);
        glVertex3f(0.5, 1, 0.5);
        glVertex3f(0.5, 0, 0.5);

        //sides
        // purple - right
        glNormal3f(1.0, 0.0, 0.0);
        setVertexColor(.3, .3, .3);
        glVertex3f(0.5, 0, -0.5);
        glVertex3f(0.5, 1, -0.5);
        glVertex3f(0.5, 1, +0.5);
        glVertex3f(0.5, 0, +0.5);

        //brown- left
        glNormal3f(-1.0, 0.0, 0.0);
        setVertexColor(.3, .3, .3);
        glVertex3f(-0.5, 0, -0.5);
        glVertex3f(-0.5, 1, -0.5);
        glVertex3f(-0.5, 1, +0.5);
        glVertex3f(-0.5, 0, +0.5);

        // top and bottom
        //white - bottom
        glNormal3f(0, -1, 0);
        setVertexColor(.3, .3, .3);
        glVertex3f(-0.5, 0, +0.5);
        glVertex3f(+0.5, 0, +0.5);
        glVertex3f(+0.5, 0, -0.5);
        glVertex3f(-0.5, 0, -0.5);

        //yellow - top
        glNormal3f(0.0, 1.0, 0.0);
        setVertexColor(.3, .3, .3);
        glVertex3f(0.5, 1, +0.5);
        glVertex3f(-0.5, 1, +0.5);
        glVertex3f(-0.5, 1, -0.5);
        glVertex3f(0.5, 1, -0.5);
    glEnd();
}

void drawScore(){
    glColor3f(1, 0 ,0);
    glMatrixMode(GL_PROJECTION); // Take current project matrix
    glPushMatrix();  // Push so we work with new "copy" matrix
        glLoadIdentity(); // Identity
        glMatrixMode(GL_MODELVIEW); // Add modelMatrix to it
            glPushMatrix(); // push so we work with new "copy" matrix
                glLoadIdentity(); // identity
                gluOrtho2D(0.0, gs.WindowWidth, 0.0, gs.WindowHeight); // work within window
                    //add score drawing with bitmap
                    char scoreAsString[32];
                    int a = sprintf(scoreAsString,"Crushed: %d",gs.numberOfCrushes);
                    if(a < 0)
                        exit(1);
                    //set the position of the text in the window using the x and y coordinates
                    glRasterPos2i(gs.WindowWidth-(13*12),gs.WindowHeight-30); // 13*12 is:13 letters if number of crushed vehicles is > 1000, 12 is size of ~chars
                    //get the length of the string to display
                    int len = (int) strlen(scoreAsString);
                    //loop to display character by character
                    for (int i = 0; i < len; i++){
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,scoreAsString[i]);
                    }
                glMatrixMode(GL_PROJECTION); // put Projection matrix back in
            glPopMatrix(); // Pop 2nd copy matrix
        glMatrixMode(GL_MODELVIEW); // Put Model back in
    glPopMatrix(); // Pop 1st copy matrix
    glutPostRedisplay(); // print all on screen
}

void drawEndGame(){
    glColor3f(1, 0 ,0);
    glMatrixMode(GL_PROJECTION); // Take current project matrix
    glPushMatrix();  // Push so we work with new "copy" matrix
        glLoadIdentity(); // Identity
        glMatrixMode(GL_MODELVIEW); // Add modelMatrix to it
            glPushMatrix(); // push so we work with new "copy" matrix
                glLoadIdentity(); // identity
                gluOrtho2D(0.0, gs.WindowWidth, 0.0, gs.WindowHeight); // work within window
                    //add score drawing with bitmap
                    char gameOver[11] = "Game over!";
                    //set the position of the text in the window using the x and y coordinates
                    glRasterPos2i(gs.WindowWidth/2 - 60,gs.WindowHeight/2);
                    //get the length of the string to display
                    int len = (int)strlen(gameOver);
                    //loop to display character by character
                    for (int i = 0; i < len; i++){
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
                    }
                glMatrixMode(GL_PROJECTION); // put Projection matrix back in
            glPopMatrix(); // Pop 2nd copy matrix
        glMatrixMode(GL_MODELVIEW); // Put Model back in
    glPopMatrix(); // Pop 1st copy matrix
    glutPostRedisplay(); // print all on screen
}

void drawCubeTank(const struct Tank tank)
{   
    glPushMatrix();
        // Start matrix at the position of the tank
        glTranslatef(tank.tankTranslate.x, tank.tankTranslate.y, tank.tankTranslate.z);
        // Save the tank-scale, we dont want that to apply to the turret and gun
        glPushMatrix();
            glScalef(tank.tankScale.x, tank.tankScale.y, tank.tankScale.z);
            drawSquare();
        glPopMatrix();
        // Move the matrix up by the tank height, so we get the turret ontop of the tank
        glTranslatef(0, tank.tankScale.y, 0);
        // This will rotate the turret and gun
        glRotatef(gs.tankMainPlayer.rotateTurret.x, 0, 1, 0);
        struct Vector3f turretSize;
        turretSize.x = tank.tankScale.x / 1.2;
        turretSize.y = tank.tankScale.y / 1.2;
        turretSize.z = tank.tankScale.z / 1.2;
        // Save the turret-scale, we dont want that to apply to the gun
        glPushMatrix();
            glScalef(turretSize.x, turretSize.y, turretSize.z);
            drawSquare();
        glPopMatrix();

        // Dont really need to save matrix here, since this is the last transformations we do anyway
        glPushMatrix();
            float barrelLenght = 1.5;

            // Start by moving the barrel origin to the edge of the turret
            float barrelZPosition = turretSize.z * 0.5;
            // Then move the barrel by half its lenght, so that we push the rest of the barrel out of the turret
            barrelZPosition += barrelLenght * 0.5;
            
            // Move the barrel UP by half the turret-size, so that its centered on the turret
            float barrelYPosition = turretSize.y * 0.5;

            glTranslatef(0, barrelYPosition, -barrelZPosition);
            glScalef(0.2, 0.2, barrelLenght);
            glutSolidSphere(1, 20, 20);
        glPopMatrix();
    glPopMatrix();
}

void drawBullet(){  
    glPushMatrix();
        glTranslatef(gs.bullet.position.x, gs.bullet.position.y, gs.bullet.position.z);
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(.3, .3, .3);
        glutSolidSphere(0.3, 10, 10);
        glDisable(GL_LIGHT1);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);
    glPopMatrix();
}

void drawCar(const struct Car car){
    glPushMatrix();
    glTranslatef(car.carTranslate.x, car.carTranslate.y, car.carTranslate.z); // use same Translate for Car and for Shield
    glPushMatrix();
        glScalef(car.carScale.x, car.carScale.y, car.carScale.z);
        glRotatef(car.carRotate.x, 1, 0, 0);
        glRotatef(car.carRotate.y, 0, 1, 0);
        glRotatef(car.carRotate.z, 0, 0, 1);
        drawSquare();
    glPopMatrix();
    if(car.showShield == 1){
        glPushMatrix();
                glEnable(GL_BLEND);
                glEnable(GL_COLOR_MATERIAL);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glColor4f(1, 0, 0, car.shieldOpacity);
                glutSolidSphere(car.carScale.y + 0.3, 10, 10); // Spawns shield around car.
                glDisable(GL_BLEND);
                glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawSideRoad(const struct Road road){
    glPushMatrix();
        glTranslatef(road.roadTranslation.x, road.roadTranslation.y, road.roadTranslation.z);
        glScalef(road.roadScale.x, road.roadScale.y, road.roadScale.z);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);
        
        glLineWidth(1);
        struct Vector3f v3f = {1, 1, 1};
        glBindTexture(GL_TEXTURE_2D, names[0]);
        setVertexColor(1,1,1);
        glNormal3f(0, 1, 0);
        glBegin(GL_QUADS);
            glTexCoord2f(-2, -2);
            glVertex3f(-v3f.x,-v3f.y, v3f.z);//bottom left
            glTexCoord2f(2, -2);
            glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
            glTexCoord2f(2, 2);
            glVertex3f(v3f.x, v3f.y, v3f.z);//top right
            glTexCoord2f(-2, 2);
            glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

bool collisionCheck(struct Vector3f a, struct Vector3f b, struct Vector3f asize, struct Vector3f bsize){
    // Collision x-axis
    bool collisionX = a.x + asize.x >= b.x && b.x + bsize.x >= a.x;
    // Collision y-axis
    bool collisionY = a.y + asize.y >= b.y && b.y + bsize.y >= a.y;
    //Collision z-axis
    bool collisionZ = a.z + asize.z >= b.z && b.z + bsize.z >= a.z;
    // Collision only if on all three axes

    return collisionX && collisionY && collisionZ;
}

struct Vector3f getDirection(struct Vector3f a, struct Vector3f b)
{
    struct Vector3f result = b;
    result.x -= a.x;
    result.y -= a.y;
    result.z -= a.z;
    return normalize(result);
}

struct Vector3f normalize(struct Vector3f a){
    float len = sqrt((a.x*a.x)+(a.y*a.y)+(a.z+a.z));
    struct Vector3f result;
    if(len == 0){
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    result.x = a.x / len;
    result.y = a.y / len;
    result.z = a.z / len;
    return result;
}

/* Object initializer functions */ //?Move these in separate file?

void tankInit(){
    gs.tankMainPlayer.tankTranslate.x = 0;
    gs.tankMainPlayer.tankTranslate.y = -1;
    gs.tankMainPlayer.tankTranslate.z = 280; 
    
    gs.tankMainPlayer.tankScale.x = 1;
    gs.tankMainPlayer.tankScale.y = 1;
    gs.tankMainPlayer.tankScale.z = 3;

    gs.tankMainPlayer.rotateTurret.x = 0;

    gs.tankMainPlayer.tankSpeed = 30; 
    gs.tankMainPlayer.currDir = 0;
    gs.tankMainPlayer.prevDir = 0;

    gs.lastMouseX = gs.WindowHeight/2;

    gs.tankMainPlayer.shoot = false;
}
void roadInit(){
    gs.road.roadScale.x = 6; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.road.roadScale.y = 1; // 
    gs.road.roadScale.z = 300; // road is 300m long.
    //Road is starting in 0,0,300 and goes until 0,0,-300

    gs.road.roadRotation.x = 90; //angle
    gs.road.roadRotation.y = 0;  //angle
    gs.road.roadRotation.z = 0;  //angle

    gs.road.roadTranslation.x = 0;
    gs.road.roadTranslation.y = 0;
    gs.road.roadTranslation.z = 0;

    gs.road2.roadScale.x = 6; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.road2.roadScale.y = 1; // 
    gs.road2.roadScale.z = 300; // road2 is 300m long. 
    //Road is starting in 0,0,-300 and goes until 0,0,-900
    gs.road2.roadRotation.x = 90; //angle
    gs.road2.roadRotation.y = 0;  //angle
    gs.road2.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-300 goes until 0,0,-900
    gs.road2.roadTranslation.x = 0;
    gs.road2.roadTranslation.y = 0;
    gs.road2.roadTranslation.z = -600;

    gs.road3.roadScale.x = 6; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.road3.roadScale.y = 1; // 
    gs.road3.roadScale.z = 300; // road3 is 300m long
    
    gs.road3.roadRotation.x = 90; //angle
    gs.road3.roadRotation.y = 0;  //angle
    gs.road3.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-900 goes until 0,0,-1500
    gs.road3.roadTranslation.x = 0;
    gs.road3.roadTranslation.y = 0;
    gs.road3.roadTranslation.z = -1200;
}

void setTankTurretMatrix(void)
{
    // Start matrix at the position of the tank
    glTranslatef(gs.tankMainPlayer.tankTranslate.x, gs.tankMainPlayer.tankTranslate.y, gs.tankMainPlayer.tankTranslate.z);

    // Move the matrix up by the tank height, so we get the turret ontop of the tank
    glTranslatef(0, gs.tankMainPlayer.tankScale.y, 0);

    // This will rotate the turret and gun
    glRotatef(gs.tankMainPlayer.rotateTurret.x, 0, 1, 0);
    struct Vector3f turretSize;
    turretSize.x = gs.tankMainPlayer.tankScale.x / 1.2;
    turretSize.y = gs.tankMainPlayer.tankScale.y / 1.2;
    turretSize.z = gs.tankMainPlayer.tankScale.z / 1.2;

    float barrelLenght = 1.5;

    // Start by moving the barrel origin to the edge of the turret
    float barrelZPosition = turretSize.z * 0.5;
    // Then move the barrel by half its lenght, so that we push the rest of the barrel out of the turret
    barrelZPosition += barrelLenght * 0.5;

    // Move the barrel UP by half the turret-size, so that its centered on the turret
    float barrelYPosition = turretSize.y * 0.5;
    glTranslatef(0, barrelYPosition, -barrelZPosition);
}

void bulletInit(){

    glPushMatrix();
        glLoadIdentity();
        setTankTurretMatrix();

        GLfloat bulletMatrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, bulletMatrix);

        gs.bullet.position.x = bulletMatrix[12];
        gs.bullet.position.y = bulletMatrix[13];
        gs.bullet.position.z = bulletMatrix[14];

        gs.bullet.direction.x = bulletMatrix[8] * 1.3;
        gs.bullet.direction.y = bulletMatrix[9] * 1.3;
        gs.bullet.direction.z = bulletMatrix[10] * 2.3;
    glPopMatrix();

    gs.bullet.needToResetBullet = false;
    gs.bullet.Charging = 0;

    gs.bullet.scale.x = 1;
    gs.bullet.scale.y = 1;
    gs.bullet.scale.z = 1;
}
void carsInit(){
    // Init cars
    gs.car.numOfCars = 1; // used for drawing cars.

    srand(time(NULL));
    gs.car.setOfCarXPositionsAllowedValues[0] = -4;
    gs.car.setOfCarXPositionsAllowedValues[1] = 0;
    gs.car.setOfCarXPositionsAllowedValues[2] = 4;
    gs.car.ZSpawnPoint = 300; // How far away from tank, cars should spawn
    gs.car.carSpeed = 30; 
    
    for(int i = 0; i < MAX_CARS_ALLOWED; i++){
        gs.carArray[i].carScale.x = 1;
        gs.carArray[i].carScale.y = 1;
        gs.carArray[i].carScale.z = 1;
        
        gs.carArray[i].carRotate.x = 0;
        gs.carArray[i].carRotate.y = 180; //cars need to go forward
        gs.carArray[i].carRotate.z = 0;

        gs.carArray[i].carTranslate.x = gs.car.setOfCarXPositionsAllowedValues[i % 3];
        gs.carArray[i].carTranslate.y = -1;
        gs.carArray[i].carTranslate.z = gs.car.ZSpawnPoint;      
        
        gs.car.lastZPoint = gs.carArray[i].carTranslate.z;
        gs.car.showShield = 0;
        gs.car.shieldOpacity = 0;
    }
    //Timers for callback onTimer function
    gs.car.timeCarSpawn = 1000;   // 1 sec
    gs.car.lastCar = MAX_CARS_ALLOWED;
}
void rightSideRoadInit(){
    //same as road, move it to side(left and right), different collor
    gs.rightSideRoad.roadScale.x = 18;   // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.rightSideRoad.roadScale.y = 1;   //
    gs.rightSideRoad.roadScale.z = 300; // road is 300m long.
    //Road is starting in 0,0,300 and goes until 0,0,-300

    gs.rightSideRoad.roadRotation.x = 90; //angle
    gs.rightSideRoad.roadRotation.y = 0;  //angle
    gs.rightSideRoad.roadRotation.z = 0;  //angle

    gs.rightSideRoad.roadTranslation.x = gs.rightSideRoad.roadScale.x + gs.road.roadScale.x;
    gs.rightSideRoad.roadTranslation.y = 0;
    gs.rightSideRoad.roadTranslation.z = 0;

    gs.rightSideRoad2.roadScale.x = 18;   // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.rightSideRoad2.roadScale.y = 1;   //
    gs.rightSideRoad2.roadScale.z = 300; // road2 is 300m long.
    //Road is starting in 0,0,-300 and goes until 0,0,-900
    gs.rightSideRoad2.roadRotation.x = 90; //angle
    gs.rightSideRoad2.roadRotation.y = 0;  //angle
    gs.rightSideRoad2.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-300 goes until 0,0,-900
    gs.rightSideRoad2.roadTranslation.x = gs.rightSideRoad2.roadScale.x + gs.road2.roadScale.x;
    gs.rightSideRoad2.roadTranslation.y = 0;
    gs.rightSideRoad2.roadTranslation.z = -600;

    gs.rightSideRoad3.roadScale.x = 18;   // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.rightSideRoad3.roadScale.y = 1;   //
    gs.rightSideRoad3.roadScale.z = 300; // road3 is 300m long

    gs.rightSideRoad3.roadRotation.x = 90; //angle
    gs.rightSideRoad3.roadRotation.y = 0;  //angle
    gs.rightSideRoad3.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-900 goes until 0,0,-1500
    gs.rightSideRoad3.roadTranslation.x = gs.rightSideRoad3.roadScale.x + gs.road3.roadScale.x;
    gs.rightSideRoad3.roadTranslation.y = 0;
    gs.rightSideRoad3.roadTranslation.z = -1200;
}
void leftSideRoadInit()
{
    //same as road, move it to side(left and right), different collor
    gs.leftSideRoad.roadScale.x = 18; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.leftSideRoad.roadScale.y = 1; //
    gs.leftSideRoad.roadScale.z = 300; // road is 300m long.
    //Road is starting in 0,0,300 and goes until 0,0,-300

    gs.leftSideRoad.roadRotation.x = 90; //angle
    gs.leftSideRoad.roadRotation.y = 0;  //angle
    gs.leftSideRoad.roadRotation.z = 0;  //angle

    gs.leftSideRoad.roadTranslation.x = -gs.leftSideRoad.roadScale.x - gs.road.roadScale.x;
    gs.leftSideRoad.roadTranslation.y = 0;
    gs.leftSideRoad.roadTranslation.z = 0;

    gs.leftSideRoad2.roadScale.x = 18; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and left
    gs.leftSideRoad2.roadScale.y = 1; //
    gs.leftSideRoad2.roadScale.z = 300; // road2 is 300m long.
    //Road is starting in 0,0,-300 and goes until 0,0,-900
    gs.leftSideRoad2.roadRotation.x = 90; //angle
    gs.leftSideRoad2.roadRotation.y = 0;  //angle
    gs.leftSideRoad2.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-300 goes until 0,0,-900
    gs.leftSideRoad2.roadTranslation.x = -gs.leftSideRoad.roadScale.x - gs.road.roadScale.x;
    gs.leftSideRoad2.roadTranslation.y = 0;
    gs.leftSideRoad2.roadTranslation.z = -600;

    gs.leftSideRoad3.roadScale.x = 18; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and left
    gs.leftSideRoad3.roadScale.y = 1; //
    gs.leftSideRoad3.roadScale.z = 300; // road3 is 300m long

    gs.leftSideRoad3.roadRotation.x = 90; //angle
    gs.leftSideRoad3.roadRotation.y = 0;  //angle
    gs.leftSideRoad3.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-900 goes until 0,0,-1500
    gs.leftSideRoad3.roadTranslation.x = -gs.leftSideRoad.roadScale.x - gs.road.roadScale.x;
    gs.leftSideRoad3.roadTranslation.y = 0;
    gs.leftSideRoad3.roadTranslation.z = -1200;
}
void skyInit(){
    gs.sky.skyColor.x = 0.6;
    gs.sky.skyColor.y = 0.8;
    gs.sky.skyColor.z = 1;
    gs.sky.dayTimer = 30;
    gs.sky.flag = 0; // while its 0 its peak of day, when 1 its peak of night
}
void sunInit(){
    gs.sun.sunRotate.x = 0;
    gs.sun.sunRotate.y = 0;
    gs.sun.sunRotate.z = 0;
    gs.sun.sunTranslate.x = 0;
    gs.sun.sunTranslate.y = 45; // it doesnt go trough road with this value
    gs.sun.sunTranslate.z = -50;
    gs.sun.lightCoef.x = 0;
    gs.sun.lightCoef.y = 1;
    gs.sun.lightCoef.z = 1;
    gs.sun.mod = 0.0033; //TODO: fix math in code, this number is paper math
    gs.sun.quadrant = 1;
}

void imageInit(){
    //Code taken from class and edited for own needs.
    Image * image;
    image = image_init(0,0);
    image_read(image, "sand.bmp");
    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                image->width, image->height, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    image_done(image);
}
void initRenderingObjects(){
    roadInit();
    carsInit();
    leftSideRoadInit();
    rightSideRoadInit();
    tankInit();
    skyInit();
    sunInit();
    bulletInit();
    imageInit();
    gs.cameraMovement = 0;
    gs.lightModifier = 0.0;
    gs.numberOfCrushes = 0;
    gs.gameover = false;
}
