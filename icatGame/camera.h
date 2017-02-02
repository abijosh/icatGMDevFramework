#pragma once
class Camera
{
public:
	Camera(int windowWidth, int windowHeight);
	~Camera();;
	void setPosition(glm::vec3 &position);
	const glm::vec3& GetPosition();
	void SetAspRatio(float ratio);
	float GetAspRatio();
	float GetNearPlane();
	void setNearAndFarPlane(float nearplane, float farplane);
	float GetFarPlane();
	const float GetFOV();
	void SetFOV(float view);
	void LookAt(glm::vec3 direction);

	glm::mat4 orientation();
	glm::mat4 modelMatrix();
	glm::mat4 projectionMatrix();
	glm::mat4 viewMatrix();
	glm::mat4 mvpMatrix();

    void setAspectRatio(float aspectRatio);

private:
	void normalizeAngles();

private:
	glm::vec3 m_position;
	glm::vec3 m_upVector;
	int windowWidth, windowHeight;
	float m_aspectratio, m_nearplane, m_farplane, m_FOV, m_horizontalAngle, m_verticalAngle;


};

