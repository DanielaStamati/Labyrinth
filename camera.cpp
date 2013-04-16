#include "camera.h"

Camera::Camera(){
}
Camera::~Camera(){
}

void Camera::init(float x, float y,float z){

  position = Vector3D(x,y,z);
	up = Vector3D(0,0,1);
	forward = Vector3D(0,1,0);
	right = Vector3D(1,0,0);
}

void Camera::translate_Forward(float dist){

	position += forward*dist;
}
void Camera::translate_Up(float dist){

	position +=	up*dist;
	
}
void Camera::translate_Right(float dist){
	
	position +=	right*dist;

}

void Camera::rotateFPS_OY(float angle){

	Vector3D new_forward = forward * cos(angle) + right * sin(angle); 
	new_forward.Normalize();
	right = new_forward.CrossProduct(up);
	right.Normalize();
	forward = new_forward;
}
void Camera::rotateFPS_OX(float angle){

	Vector3D new_forward = forward * cos(angle) + up * sin(angle); 
	new_forward.Normalize();
	up = right.CrossProduct(new_forward);
	up.Normalize();
	forward = new_forward;

}
void Camera::rotateFPS_OZ(float angle){

	Vector3D new_right = right * cos(angle) + up * sin(angle); 	
	new_right.Normalize();
	up = right.CrossProduct(forward);
	up.Normalize();
	right = new_right;

}



void Camera::render(){
	Vector3D center = position + forward;

	gluLookAt(	position.x, position.y, position.z, 
				center.x, center.y, center.z,
				up.x, up.y, up.z);
}
