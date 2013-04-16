#include "maze.h"



void Maze::readInput(char *inputFile){
  	
	std::ifstream input(inputFile);
	input >> n;
	input >> m;
	char current;
	bool FirstPortal = true;
	sp = false;

	for(int i = 0; i < n; i++){

		map.push_back(std::vector<char> ());

		for(int j = 0; j < m; j++){

			input >> current;
			map[i].push_back(current);

			//character found
			if(map[i][j] == 'c'){ 
				character = Vector3D(i, j, 0);
			}

			//portal
			if(map[i][j] == 'x' || map[i][j] == 'y'){
				

				if(FirstPortal){
						bluePortal = Vector3D(i, j, 0);
						bluePortalRot = map[i][j];
						FirstPortal = false;
				}else{
					portal   =  Vector3D(i, j, 0);
					portalRot = map[i][j];
				}
			}

			if(map[i][j]=='s'){
				specialPower = Vector3D(i,j,0);
				sp = true;
			}


		}
	}

}


//==== CONSTRUCTOR ===//
Maze::Maze(char *inputFile){

	readInput(inputFile);

	int i = bluePortal.x;
	int j = bluePortal.y;
	
	
	if(! (i+1< n && map[i+1][j] == 'c'
		||i-1>=0 && map[i-1][j] == 'c'
		||j+1< m && map[i][j+1] == 'c'
		||j-1>=0 && map[i][j-1] == 'c')){
			//=>false assumption;
			Vector3D aux  = bluePortal;
			char auxR     = bluePortalRot;

			bluePortal    = portal;
			bluePortalRot = portalRot;
			portal        = aux;
			portalRot     = auxR;
	}	

}

//default constructor;
Maze::Maze(){}

void Maze::renderMap(){
	

	for(int i = 0; i<n; i++)
		for(int j = 0; j<m; j++){
			glPushMatrix();
			if(map[i][j]=='#'){
				glTranslatef(i, j, 0);
				glutSolidCube(0.95);
			}
			glPopMatrix();
		}
}

void Maze::renderPortal(){

	//red portal
	glPushMatrix();

		glTranslatef(portal.x, portal.y, 0);

		if(portalRot=='y'){ //the thorus needs a rotation on z axis
			glRotatef(90,0,1,0);
		}else{					//the thorus needs a rotation on y axis
			glRotatef(90,1,0,0);
		}

		glutSolidTorus(0.1, 0.2, 30, 30);
	glPopMatrix();

	//blue portal
	glPushMatrix();
		
		GLfloat diffuse4fPORT  [] = {0.0, 0.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4fPORT);
		glTranslatef(bluePortal.x, bluePortal.y, 0);

		if(bluePortalRot=='y'){ //the thorus needs a rotation on z axis
				glRotatef(90,0,1,0);
			}else{					//the thorus needs a rotation on y axis
				glRotatef(90,1,0,0);
			}

		glutSolidTorus(0.1, 0.2, 30, 30);

	glPopMatrix();
}

void Maze::renderSpecialPower(){

	GLfloat diffuseSP  [] = {1.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseSP);

	glPushMatrix();

		glTranslatef(specialPower.x,specialPower.y,specialPower.z);
		glRotatef(90,1,0,0);	
		glutSolidTeapot(0.3);

	glPopMatrix();
}


bool Maze::wall(Vector3D obj, float safeSpace){

	float z = (float)obj.z;


	//checking ceil and floor collisions
	if((z<0||z>1)&&checkCeilFloor){
		return true;
	}

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++){
		
			if(map[i][j]=='#'&& obj.Distance(Vector3D(i,j,0))<safeSpace)
				return true;
		
		}

	return false;
}

