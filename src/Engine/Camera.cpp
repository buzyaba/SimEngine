#include <Engine/Camera.hpp>

Camera::Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, 
        GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp){
	cameraPos = camPos;
	cameraFront = camFront;
	cameraUp = camUp;

	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projectionMatrix = glm::perspective(FOV, width/height, nearPlane, farPlane);
}


Camera::~Camera(){

}

void Camera::moveCamera(glm::vec3 camPos){
	cameraPos = camPos;
	viewMatrix = glm::lookAt(cameraPos,	cameraPos + cameraFront, cameraUp);
}

void Camera::rotateCamera(glm::vec3 camFront){
	cameraFront = camFront;
	viewMatrix = glm::lookAt(cameraPos,	cameraPos + cameraFront, cameraUp);
}

void Camera::rotateUpCamera(glm::vec3 camUp){
	cameraUp = camUp;
	viewMatrix = glm::lookAt(cameraPos,	cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getViewMatrix() {

	return viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix() {

	return projectionMatrix;
}

glm::vec3 Camera::getCameraPosition() {

	return cameraPos;
}

glm::vec3 Camera::getCameraFront() {
	return cameraFront;
}

glm::vec3 Camera::getCameraUp() {
	return cameraUp;
}