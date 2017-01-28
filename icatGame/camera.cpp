
#include "Header.h"
#define MAX_VERTICAL_ANGLE 85
#define MAX_SHAKE_TIME 1
Camera::Camera(int windowWidth, int windowHeight)
{
	m_position = glm::vec3(0.0, 0.0, 700.0);
	m_horizontalAngle = 0.0;
	m_verticalAngle = 0.0;
	m_FOV = 45.0;
	m_nearplane = 0.1;
	m_farplane = 1000;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	m_aspectratio = windowWidth / windowHeight;
	m_upVector = glm::vec3(0, 1, 0);
}
Camera::~Camera()
{
}
void Camera::setPosition(glm::vec3 &position)
{
	m_position = position;
}
const glm::vec3& Camera::GetPosition()
{
	return m_position;
}
void Camera::SetFOV(float FOV)
{
	m_FOV = FOV;
}
const float Camera::GetFOV()
{
	return m_FOV;
}
void Camera::LookAt(glm::vec3 direction)
{
	assert(m_position != direction);
	glm::vec3 location = glm::normalize(direction - m_position);
	m_verticalAngle = glm::radians(asinf(-location.y));
	m_horizontalAngle = -glm::radians(atan2f(-location.x, -location.z));
	normalizeAngles();
}

void Camera::normalizeAngles()
{
	m_horizontalAngle = fmodf(m_horizontalAngle, 360.0f);
	if (m_horizontalAngle < 0.0f)
	{
		m_horizontalAngle += 360.0f;
	}
	if (m_verticalAngle > MAX_VERTICAL_ANGLE)
	{
		m_verticalAngle = MAX_VERTICAL_ANGLE;
	}
	else if (m_verticalAngle < -MAX_VERTICAL_ANGLE)
	{
		m_verticalAngle = -MAX_VERTICAL_ANGLE;
	}
}
glm::mat4 Camera::orientation()
{
	glm::mat4 orientation;
	orientation = glm::rotate(orientation,
		glm::radians(m_verticalAngle), glm::normalize(m_upVector));
	orientation = glm::rotate(orientation,
		glm::radians(m_horizontalAngle), glm::normalize(m_upVector));
	return orientation;
}
glm::mat4 Camera::modelMatrix(){
	glm::mat4 retVal;
	return retVal;
}
glm::mat4 Camera::projectionMatrix(){
	return glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.001f, 1000.0f);
}
glm::mat4 Camera::viewMatrix(){
	return orientation() *glm::translate(glm::mat4(), -m_position);
}
glm::mat4 Camera::mvpMatrix(){
	return projectionMatrix()*viewMatrix();
}

void Camera::setAspectRatio(float aspectRatio) {
	this->m_aspectratio = aspectRatio;
}