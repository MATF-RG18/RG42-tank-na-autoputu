#include "drawFunctions.h"
#include "callbackFunctions.h"
#include <GL/glut.h>
#include <time.h>

/************************************
    Functions definitions start here
*************************************/
//TODO: There is something wrong in drawing or Makefile. 
//TODO: sometimes(after doing make) tank shows up in rly weird spot
//TODO: make sure that make is working then rest

void init(void){
    glClearColor(0.6, 0.8 , 1, 0.0);
    glClearDepth(1.0);
    glLineWidth(1);
    glShadeModel(GL_FLAT);
    initRenderingObjects(); 
}
void drawSun(){
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(20, 10, -30);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();
}
void drawRoad(const struct Road road){
    
    glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslatef(road.roadTranslation.x, road.roadTranslation.y, road.roadTranslation.z);
        glScalef(road.roadScale.x, road.roadScale.y, road.roadScale.z);
        glRotatef(road.roadRotation.x, 1, 0, 0);
        glRotatef(road.roadRotation.y, 0, 1, 0);
        glRotatef(road.roadRotation.z, 0, 0, 1);
        
        glLineWidth(1);
        struct Vector3f v3f = {1, 1, 1};

        glColor3f(0.3, 0.3, 0.3);
        glBegin(GL_POLYGON);
            glVertex3f(-v3f.x,-v3f.y, v3f.z);//bottom left
            glVertex3f(v3f.x, -v3f.y, v3f.z);//bottom right
            glVertex3f(v3f.x, v3f.y, v3f.z);//top right
            glVertex3f(-v3f.x, v3f.y, v3f.z);//top left
        glEnd();
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple (3, 0xFFFF); // dashed lines
        glLineWidth(4);
        glBegin(GL_LINES);
                glColor3f(1, 1, 1);
                //left line
                glVertex3f(-v3f.x/3, -v3f.y, v3f.z-0.1); // z-axis, -0.01 is just so we see lines
                glVertex3f(-v3f.x/3, v3f.y, v3f.z-0.1);  // they are just tiny bit above road it self
                //right line                                // better solution?
                glVertex3f(v3f.x/3, -v3f.y, v3f.z-0.1); 
                glVertex3f(v3f.x/3, v3f.y, v3f.z-0.1);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}
void drawCubeTank(const struct Tank tank){
    
    glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable( GL_DEPTH_TEST );
        glTranslatef(tank.tankTranslate.x, tank.tankTranslate.y, tank.tankTranslate.z);
        glScalef(tank.tankScale.x, tank.tankScale.y, tank.tankScale.z);
        glBegin(GL_QUADS);
            /* blue - green - red - light blue - */

            //blue
            glColor3f(0, 0, 1);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 0, -0.5); 

            //green - back
            glColor3f(0, 1, 0);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(0.5, 1, 0.5);
            glVertex3f(0.5, 0, 0.5); 
            
            //sides
            // purple - right
            glColor3f(1, 0, 1);
            glVertex3f(0.5, 0, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(0.5, 0, +0.5); 

            //purple - left
            glColor3f(1, 0, 1);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 0, +0.5); 

            // top and bottom
            //white
            glColor3f(1, 1, 1);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(+0.5, 0, +0.5);
            glVertex3f(+0.5, 0, -0.5);
            glVertex3f(-0.5, 0, -0.5);

            //yellow
            glColor3f(1, 1, 0);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
            
        glEnd();
        
    glPopMatrix();
}
void drawCar(const struct Car car){
    
    glPushMatrix();
        //TODO check glRotate, when you want it to rotate? during crush or smth, will need Struct instead hardcode numbers for rotation
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glTranslatef(car.carPosition.x, car.carPosition.y, car.carPosition.z);
        glScalef(car.carScale.x, car.carScale.y, car.carScale.z);
        //glRotatef(car.carRotate.x, 1, 0, 0);
        //glRotatef(car.carRotate.y, 0, 1, 0);
        //glRotatef(car.carRotate.z, 0, 0, 1);
        glBegin(GL_QUADS);
            /* blue - green - red - light blue - */

            //front and back
            //blue - front
            glColor3f(0, 0, 1);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 0, -0.5); 

            //purple - back
            glColor3f(1, 0, 1);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(0.5, 1, 0.5);
            glVertex3f(0.5, 0, 0.5); 
            
            //sides
            //purple - right
            glColor3f(1, 0, 1);
            glVertex3f(0.5, 0, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(0.5, 0, +0.5); 

            //lblue - left
            glColor3f(1, 0, 0);
            glVertex3f(-0.5, 0, -0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 0, +0.5); 

            // top and bottom
            //white
            glColor3f(1, 1, 1);
            glVertex3f(-0.5, 0, +0.5);
            glVertex3f(+0.5, 0, +0.5);
            glVertex3f(+0.5, 0, -0.5);
            glVertex3f(-0.5, 0, -0.5);

            //yellow
            glColor3f(1, 1, 0);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(-0.5, 1, +0.5);
            glVertex3f(-0.5, 1, -0.5);
            glVertex3f(0.5, 1, -0.5);
        glDisable( GL_DEPTH_TEST );
        glEnd();
    glPopMatrix();
}
void initRenderingObjects(){
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

    gs.tankMainPlayer.tankTranslate.x = 0;
    gs.tankMainPlayer.tankTranslate.y = -1; // need to fix inside tank drawing , and put 0 here. Its gonna be same effect, just cleaner ?
    gs.tankMainPlayer.tankTranslate.z = 280; 
    gs.cameraMovement = 0;
    gs.tankMainPlayer.tankScale.x = 1;
    gs.tankMainPlayer.tankScale.y = 1;
    gs.tankMainPlayer.tankScale.z = 3;

    gs.tankMainPlayer.tankSpeed = 30; 
    
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
        gs.carArray[i].carRotate.y = 0;
        gs.carArray[i].carRotate.z = 0;

        gs.carArray[i].carPosition.x = gs.car.setOfCarXPositionsAllowedValues[rand()%3];
        gs.carArray[i].carPosition.y = -1; //need to fix inside car drawing , and put 0 here. Its gonna be same effect, just cleaner ?
        gs.carArray[i].carPosition.z = gs.car.ZSpawnPoint;
    }
    //Timers for callback onTimer function
    gs.car.timeCarSpawn = 1000;   // 1 sec

    gs.numberOfCrushes = 0;
}
