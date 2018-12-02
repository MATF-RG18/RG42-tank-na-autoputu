#include "drawFunctions.h"
#include "callbackFunctions.h"
#include "lightingFunctions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

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
}
void drawSun(){
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(20, 10, -30);
        setVertexColor(1, 1, 0);
        glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
void drawSquare(){
    //?Could send lights/colors here per object...
        glBegin(GL_QUADS);
            //green - front
            glNormal3f(0, 1, 0);
            setVertexColor(0, 0, 1);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 0, -0.5);

            //green - back
            glNormal3f(0, 0, -1);
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
        glTranslatef(road.roadTranslation.x, road.roadTranslation.y, road.roadTranslation.z);
        glScalef(road.roadScale.x, road.roadScale.y, road.roadScale.z);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);
        
        glLineWidth(1);
        struct Vector3f v3f = {1, 1, 1};

        setVertexColor(0.3, 0.3, 0.3);
        glBegin(GL_POLYGON);
            glNormal3f(0, 1, 0);
            glVertex3f(-v3f.x,-v3f.y, v3f.z);//bottom left
            glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
            glVertex3f(v3f.x, v3f.y, v3f.z);//top right
            glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();

        glLineWidth(4);
        glBegin(GL_LINES);
                setVertexColor(1, 1, 1);
                //left line
                glNormal3f(0, 1, 0);
                glVertex3f(-v3f.x/3, -v3f.y, v3f.z-0.1); // z-axis, -0.01 is just so we see lines
                glVertex3f(-v3f.x/3, v3f.y, v3f.z-0.1);  // they are just tiny bit above road it self
                //right line                                // better solution?
                glNormal3f(0, 1, 0);
                glVertex3f(v3f.x/3, -v3f.y, v3f.z-0.1); 
                glVertex3f(v3f.x/3, v3f.y, v3f.z-0.1);
        glEnd();
    glPopMatrix();
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
void drawCubeTank(const struct Tank tank){
    glPushMatrix();
        glTranslatef(tank.tankTranslate.x, tank.tankTranslate.y, tank.tankTranslate.z);
        glScalef(tank.tankScale.x, tank.tankScale.y, tank.tankScale.z);
        drawSquare();
    glPopMatrix();
}
void drawCar(const struct Car car){
    glPushMatrix();
        glTranslatef(car.carPosition.x, car.carPosition.y, car.carPosition.z);
        glScalef(car.carScale.x, car.carScale.y, car.carScale.z);
        glRotatef(car.carRotate.x, 1, 0, 0);
        glRotatef(car.carRotate.y, 0, 1, 0);
        glRotatef(car.carRotate.z, 0, 0, 1);
        drawSquare();
    glPopMatrix();
}
void tankInit(){
    gs.tankMainPlayer.tankTranslate.x = 0;
    gs.tankMainPlayer.tankTranslate.y = -1; // need to fix inside tank drawing , and put 0 here. Its gonna be same effect, just cleaner ?
    gs.tankMainPlayer.tankTranslate.z = 280; 
    
    gs.tankMainPlayer.tankScale.x = 1;
    gs.tankMainPlayer.tankScale.y = 1;
    gs.tankMainPlayer.tankScale.z = 3;

    gs.tankMainPlayer.tankSpeed = 30; 
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
void carsInit(){
    // Init cars
    gs.car.numOfCars = 1; // used for drawing cars.

    srand(time(NULL));
    gs.car.setOfCarXPositionsAllowedValues[0] = -3.;
    gs.car.setOfCarXPositionsAllowedValues[1] = 0;
    gs.car.setOfCarXPositionsAllowedValues[2] = 3.;
    gs.car.ZSpawnPoint = 300; // How far away from tank, cars should spawn
    gs.car.carSpeed = 30; 
    
    for(int i = 0; i < MAX_CARS_ALLOWED; i++){
        gs.carArray[i].carScale.x = 1;
        gs.carArray[i].carScale.y = 1;
        gs.carArray[i].carScale.z = 1;
        
        gs.carArray[i].carRotate.x = 0;
        gs.carArray[i].carRotate.y = 180; //cars need to go forward
        gs.carArray[i].carRotate.z = 0;

        gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
        gs.carArray[i].carPosition.y = -1; //need to fix inside car drawing , and put 0 here. Its gonna be same effect, just cleaner ?
        gs.carArray[i].carPosition.z = gs.car.ZSpawnPoint;
    }
    //Timers for callback onTimer function
    gs.car.timeCarSpawn = 1000;   // 1 sec
}
/* todo: later figure if I want this even
void rightSideRoadInit(){
    //same as road, move it to side(left and right), different collor
    gs.sideRoad.roadScale.x = 3; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.sideRoad.roadScale.y = 4; // 
    gs.sideRoad.roadScale.z = 1; // road is 300m long.
    //Road is starting in 0,0,300 and goes until 0,0,-300

    gs.sideRoad.roadRotation.x = 90; //angle
    gs.sideRoad.roadRotation.y = 90;  //angle
    gs.sideRoad.roadRotation.z = 0;  //angle

    gs.sideRoad.roadTranslation.x = 3;
    gs.sideRoad.roadTranslation.y = 0;
    gs.sideRoad.roadTranslation.z = 0;

    gs.sideRoad2.roadScale.x = 3; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.sideRoad2.roadScale.y = 4; // 
    gs.sideRoad2.roadScale.z = 1; // road2 is 300m long. 
    //Road is starting in 0,0,-300 and goes until 0,0,-900
    gs.sideRoad2.roadRotation.x = 90; //angle
    gs.sideRoad2.roadRotation.y = 90;  //angle
    gs.sideRoad2.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-300 goes until 0,0,-900
    gs.sideRoad2.roadTranslation.x = 3;
    gs.sideRoad2.roadTranslation.y = 0;
    gs.sideRoad2.roadTranslation.z = 30;

    gs.sideRoad3.roadScale.x = 3; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    gs.sideRoad3.roadScale.y = 4; // 
    gs.sideRoad3.roadScale.z = 1; // road3 is 300m long
    
    gs.sideRoad3.roadRotation.x = 90; //angle
    gs.sideRoad3.roadRotation.y = 90;  //angle
    gs.sideRoad3.roadRotation.z = 0;  //angle

    //Road 3 is 300m long and is starting on 0,0,-900 goes until 0,0,-1500
    gs.sideRoad3.roadTranslation.x = 3;
    gs.sideRoad3.roadTranslation.y = 0;
    gs.sideRoad3.roadTranslation.z = 60;
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

        glColor3f(.45, .27, .13);
        glBegin(GL_POLYGON);
            glVertex3f(-v3f.x,-v3f.y, v3f.z);//bottom left
            glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
            glVertex3f(v3f.x, v3f.y, v3f.z);//top right
            glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();
    glPopMatrix();
}*/
void skyInit(){
    gs.sky.skyColor.x = 0.6;
    gs.sky.skyColor.y = 0.8;
    gs.sky.skyColor.z = 1;
    gs.sky.dayTimer = 30;
    gs.sky.flag = 0; // while its 0 its day, when 1 its night
}
void initRenderingObjects(){
    roadInit();
    carsInit();
    //rightSideRoadInit();
    tankInit();
    skyInit();
    gs.cameraMovement = 0;
    gs.lightModifier = 0.0;
    gs.numberOfCrushes = 0;
}
