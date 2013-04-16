//include librarii de opengl, glut si glu
#pragma once
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

//includes
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Maze.h"
#include "glut.h"
#include "camera.h"

//defines
#define angleSpeed   0.1f
#define coneHeight	 0.4f
#define backTPS		-1.5f
#define radTPS		-0.5f
#define deplTPS		-1.5f


float	safeSpace =	 1.0f;
float   coneBase  =	 0.3f;

//CAMERAS

//fps
Camera FPScam;
bool fps_ON = false;

//tps
Camera TPScam;
bool tps_ON = false;

//map view
bool mapViewON = true;

//maze
static Maze maze;

//light components
GLfloat ambient4f  [] = {0.2, 0.2, 0.2, 1.0};
GLfloat specular4f [] = {1.0, 1.0, 1.0, 1.0};


GLfloat diffuse4f     [] = {230/250.0f, 142/250.0f, 32/250.0f, 1.0}; //maze color
GLfloat diffuse4fPORT [] = {1.0, 0.0, 0.0, 1.0};					 //portal color
GLfloat diffuse4fCHR  [] = {0.0, 0.0, 1.0, 1.0};					 //character color

GLfloat shininess = 0;

//wins
int  wins = 0;
bool transition  = true;

//other
float xRot = 360-90;
char * file;


void init();
void renderPlayer(){

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4fCHR);

	glPushMatrix();		
			
			glTranslatef(maze.character.x, maze.character.y+0.2,0);	
			glRotatef(xRot,1,0,0);
			glRotatef(FPScam.angle*180/3.14,0,1,0);			
			glutSolidCone(coneBase,coneHeight,30,30);		

	glPopMatrix();

}


void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setup view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(maze.character.Distance(maze.specialPower)<safeSpace/2){
		coneBase  = 0.2f;
		safeSpace = 0.8f;
		maze.sp = false;
	}

	if(maze.character.Distance(maze.bluePortal)<safeSpace/2 && wins>0){
		wins--;
		transition = true;
	}

	if(maze.character.Distance(maze.portal)<safeSpace/2 && wins<4){
		wins++;
		transition = true;
	}


	if(transition){

		
		sprintf(file, "levels/maze%d",wins);
		
		//restoring defaults	
		maze = Maze(file);
		maze.checkCeilFloor = true;
		coneBase = 0.3f;
		safeSpace = 1.0f;
		transition = false;
		
		std::cout<<file<<"\n";
		FPScam.position =maze.character;

	}

	maze.character = FPScam.position;

	//setup camera
	if(fps_ON){		
		FPScam.render();
	}else if(tps_ON){

		TPScam = FPScam;
		TPScam.rotateFPS_OX(radTPS);	
		TPScam.translate_Forward(deplTPS);		
		TPScam.render();

	}else{
		gluLookAt(	maze.n/2, maze.n/2, 25,	//eye
					maze.n/2, maze.m/2, 0,	//center
					0,1,0);					//up
	}

	//rendering the map
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
	maze.renderMap();

	//rendering the portal	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4fPORT);
	maze.renderPortal();

	//rendering the player
	if(!fps_ON){
		renderPlayer();
	}

	//rendering special power
	if(maze.sp)
		maze.renderSpecialPower();

	//swap buffers6
	glutSwapBuffers();
}



void reshape(int width, int height){
	//set viewport
	glViewport(0,0,width,height);

	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)width/(float)height,0.1f,100);
}

void keyboard(unsigned char ch, int x, int y){
	switch(ch){
		case 27:	//esc
			exit(0);
			break;
		
		case 'c':
			if(fps_ON){		

				fps_ON    = false;
				tps_ON	  = false;
				mapViewON = true;

			}else if(mapViewON){

				mapViewON = false;
				fps_ON    = false;
				tps_ON    = true;
			
			}else if(tps_ON){

				tps_ON    = false;
				mapViewON = false;
				fps_ON    = true;
			}

			break;

	
		case 'q':
				FPScam.translate_Up(angleSpeed);
			break;
		case 'e':
				FPScam.translate_Up(-angleSpeed);
			break;

		case 'y':
				FPScam.rotateFPS_OY(-angleSpeed);

				if(maze.wall(FPScam.position,safeSpace))
					FPScam.rotateFPS_OY(angleSpeed);
				else if(!tps_ON)
					FPScam.angle+=-angleSpeed;


				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OY(angleSpeed);
					}else
						FPScam.angle+=-angleSpeed;
				}

			break;

			case 'u':
				FPScam.rotateFPS_OY(angleSpeed);

				if(maze.wall(FPScam.position,safeSpace))
					FPScam.rotateFPS_OY(-angleSpeed);
				else if(!tps_ON)
					FPScam.angle+=angleSpeed;


				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OY(-angleSpeed);
					}else
						FPScam.angle+=angleSpeed;
				}

			break;
		case 'x':			
				FPScam.rotateFPS_OX(-angleSpeed);

				if(!tps_ON){
					xRot+=-angleSpeed*180/3.14;					
				}

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					maze.checkCeilFloor = false;

					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OX(angleSpeed);
					}else{
						xRot+=-angleSpeed*180/3.14;
					}

					maze.checkCeilFloor = true;
				}
			break;

			case 'X':			
				FPScam.rotateFPS_OX(angleSpeed);

				if(!tps_ON){
					xRot+=angleSpeed*180/3.14;					
				}

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);

					maze.checkCeilFloor = false;
					
					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OX(-angleSpeed);
					}else{
						xRot+=angleSpeed*180/3.14;
					}

					maze.checkCeilFloor = true;
				}
			break;

		case 'z':
				FPScam.rotateFPS_OZ(-angleSpeed);

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OZ(angleSpeed);
					}
				}

		case 'Z':
				FPScam.rotateFPS_OZ(angleSpeed);

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test colision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.rotateFPS_OZ(-angleSpeed);
					}
				}
		
		default:
			break;
	}

	glutPostRedisplay();

}

void special(int key,int x,int y)
{
	int playerX = maze.character.x;
	int playerY = maze.character.y;

	switch(key)
	{
		case GLUT_KEY_UP:
				FPScam.translate_Forward(0.1);
				if(tps_ON){
					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
				}
				if(maze.wall(FPScam.position,safeSpace))
					FPScam.translate_Forward(-0.1);
			break;

		case GLUT_KEY_DOWN:
				FPScam.translate_Forward(-0.1);	

				//test collision
				if(maze.wall(FPScam.position,safeSpace))
					FPScam.translate_Forward(0.1);

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test collision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.translate_Forward(0.1);
					}
				}
			break;

		case GLUT_KEY_LEFT:
				FPScam.translate_Right(-0.1);
				if(maze.wall(FPScam.position,safeSpace))
					FPScam.translate_Right(0.1);

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test collision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.translate_Right(0.1);
					}
				}
			break;

		case GLUT_KEY_RIGHT:
				FPScam.translate_Right(0.1);
				if(maze.wall(FPScam.position,safeSpace))
					FPScam.translate_Right(-0.1);

				if(tps_ON){

					TPScam = FPScam;
					TPScam.rotateFPS_OX(radTPS);	
					TPScam.translate_Forward(deplTPS);
					
					//test collision
					if(maze.wall(TPScam.position,safeSpace)){	
						FPScam.translate_Right(-0.1);
					}
				}
			break;
	}
	
	glutPostRedisplay();
}


//idle
void idle(){

}

void init(){



	file = (char*)malloc(12*sizeof(char));
	sprintf(file, "levels/maze0");
	maze = Maze(file);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//init window
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Escape the maze");

	//initialize cameras	
	FPScam.init(maze.character.x, maze.character.y, maze.character.z);
	FPScam.angle = 0;	

	//====================light================//
	const GLfloat globalAmbientColor4f [] = {0.2, 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor4f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);	

	//5glEnable(GL_CULL_FACE);
	

	// setare parametrii lumina 0
	GLfloat position4f [] = {maze.n/2,maze.m/2,0};
	GLfloat color4f [] = {0.8,0.8,0.8,1};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, color4f);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color4f);
	glLightfv(GL_LIGHT0, GL_POSITION, position4f);
	glEnable(GL_LIGHT0);

}



int main(int argc, char *argv[]){

	//init glut
	glutInit(&argc, argv);
	init();

	std::cout <<"\nMap: " << maze.n << "x" << maze.m<<"\n\n";
	for(int i = 0; i<maze.n; i++){
		for(int j = 0; j<maze.m; j++){
			std::cout<<maze.map[i][j];
		}
		std::cout<<"\n";
	}


	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutIdleFunc(idle);
	

	//z test on
	glEnable(GL_DEPTH_TEST);

	//set background
	glClearColor(0.0,0.2,0.2,1.0);


	//loop
	glutMainLoop();
	return 0;
}
