#include "drawFunctions.h"
#include "callbackFunctions.h"
#include <GL/glut.h>

/************************************
    Functions definitions start here
*************************************/

void init(void){
    glClearColor(0.0, 0.0 , 0.0, 0.0);
    glClearDepth(1.0);
    glLineWidth(1);
    glShadeModel(GL_FLAT);
}

void drawRoad(const struct Vector3f aScale,const struct Vector3f aRotation,const struct Vector3f aTranslation){
    
    glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glScalef(aScale.x, aScale.y, aScale.z);
        glRotatef(aRotation.x, 1, 0, 0);
        glRotatef(aRotation.y, 0, 1, 0);
        glRotatef(aRotation.z, 0, 0, 1);
        glTranslatef(aTranslation.x, aTranslation.y, aTranslation.z);
        glLineWidth(1);


        // all sizes are 1m and then they get scaled with glScale into proper sizes.
        GLfloat width = 1;
        GLfloat height = 0.1; // road is just above 0, because lookAt points at 0 on yaxis
        GLfloat depth = 0; 

        glColor3f(0, 1.0, 1.0); //TODO road color only one and not rainbow if i use 4
        glBegin(GL_QUADS);
            glVertex3f(-width,-height, depth);//bottom left
            glVertex3f(width, -height, depth);//bottom right
            glVertex3f(width, height, depth);//top right
            glVertex3f(-width, height, depth);//top left
        glEnd();
        //draw lanes on road
        
        glEnable(GL_LINE_STIPPLE);
        glLineStipple (3, 0xF00F); // dashed lines
        glLineWidth(5);
        glBegin(GL_LINES);
                glColor3f(1, 1, 1);
                //left line
                glVertex3f(-width/3, -height, depth-0.001); // z-axis, -0.001 is just so we see lines
                glVertex3f(-width/3, height, depth-0.001);  // they are just tiny bit above road it self
                //right line                                // better solution?
                glVertex3f(width/3, -height, depth-0.001); 
                glVertex3f(width/3, height, depth-0.001);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        
        glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}
void drawCubeTank(const struct Tank tank){
    glPushMatrix();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable( GL_DEPTH_TEST );
        glScalef(1, 1, 3); // size of tank, adjustable only here, change that?
        glTranslatef(tank.tankTranslate.x, tank.tankTranslate.y, tank.tankTranslate.z);
        glBegin(GL_QUADS);
            /* blue - green - red - light blue - */

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
            // dark green - right
            glColor3f(1, 0, 1);
            glVertex3f(0.5, 0, -0.5);
            glVertex3f(0.5, 1, -0.5);
            glVertex3f(0.5, 1, +0.5);
            glVertex3f(0.5, 0, +0.5); 

            //lblue - left
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
            
        glDisable( GL_DEPTH_TEST );
        glEnd();
        
    glPopMatrix();
}
void drawCar(const struct Car car){
    
    glPushMatrix();
        //TODO check glRotate, when you want it to rotate?
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glScalef(1, 1, 1);
        //glRotatef(aRotation.x, 1, 0, 0);
        //glRotatef(aRotation.y, 0, 1, 0);
        //glRotatef(aRotation.z, 0, 0, 1);
        glTranslatef(car.carPosition.x, car.carPosition.y, car.carPosition.z);

        glBegin(GL_QUADS);
            /* blue - green - red - light blue - */

            //front and back
            //blue - front
            glColor3f(0, 0, 1);
            glVertex3f(-0.5, -0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(0.5, -0.5, -0.5); 

            //purple - back
            glColor3f(1, 0, 1);
            glVertex3f(-0.5, -0.5, +0.5);
            glVertex3f(-0.5, 0.5, +0.5);
            glVertex3f(0.5, 0.5, 0.5);
            glVertex3f(0.5, -0.5, 0.5); 
            
            //sides
            //purple - right
            glColor3f(1, 0, 1);
            glVertex3f(0.5, -0.5, -0.5);
            glVertex3f(0.5, 0.5, -0.5);
            glVertex3f(0.5, 0.5, +0.5);
            glVertex3f(0.5, -0.5, +0.5); 

            //lblue - left
            glColor3f(1, 0, 0);
            glVertex3f(-0.5, -0.5, -0.5);
            glVertex3f(-0.5, 0.5, -0.5);
            glVertex3f(-0.5, 0.5, +0.5);
            glVertex3f(-0.5, -0.5, +0.5); 

            // top and bottom
            //white
            glColor3f(1, 1, 1);
            glVertex3f(-0.5, -0.5, +0.5);
            glVertex3f(+0.5, -0.5, +0.5);
            glVertex3f(+0.5, -0.5, -0.5);
            glVertex3f(-0.5, -0.5, -0.5);

            //yellow
            glColor3f(1, 1, 0);
            glVertex3f(0.5, +0.5, +0.5);
            glVertex3f(-0.5, +0.5, +0.5);
            glVertex3f(-0.5, +0.5, -0.5);
            glVertex3f(0.5, +0.5, -0.5);
        glDisable( GL_DEPTH_TEST );
        glEnd();
    glPopMatrix();
}
void initRenderingObjects(struct Vector3f *aScale, struct Vector3f *aRotation, struct Vector3f *aTranslation,struct gameState *gamestate){
    //Should I put Scale,Rotation and Trasnaltion in init() function?
    //Road should be initialized on very start, should I mix it with those funcs or keep here?
    //Road should be initialized once only, do I need to keep checking on it? Future versions of game?
    //roadScalef
    aScale->x = 6; // road width will be 6m - prone to change -- if it changes, need to account change with car positions and how much tank can move to left and right
    aScale->y = 1; // road will be 1m thick - no reason to change
    aScale->z = 1000; // road length will be 500m - prone to change
    //roadRotation
    aRotation->x = 90; 
    aRotation->y = 0;
    aRotation->z = 0;
    //roadTranslation
    aTranslation->x = 0;
    aTranslation->y = 0;
    aTranslation->z = 0;
    // tank translate
    tank.tankTranslate.x = 0; // its 0 on start, it changes during gameplay
    tank.tankTranslate.y = 0; // should always stay 0
    tank.tankTranslate.z = 5; // TODO: can be changed, for now it forces tank on begining of screen(NOT ROAD)
    gamestate->tankMainPlayer = tank;

    //TODO Fix gameplay here
    //TODO all cars should spawn in back, on max range, and then drive towards player
    //TODO dont let cars go out of road
    //Initialize cars, should be reedited in future.
    int min_distance = -100;
    for(int i = 0; i < 15; i++){
        min_distance += 10;
        if(i%2 == 0)
            gamestate->carNumber[i].carPosition.x = (rand() % 5);
        else
            gamestate->carNumber[i].carPosition.x = -(rand() % 5);
        gamestate->carNumber[i].carPosition.y = 0.5;
        gamestate->carNumber[i].carPosition.z = min_distance;
        if (min_distance == -10){
            min_distance = -95;
        }
    }
}
