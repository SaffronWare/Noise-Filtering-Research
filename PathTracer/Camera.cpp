#include "Camera.h"

glm::mat4 Camera::getOrientation()
{
	return orientation;
}

glm::vec3 Camera::getFront()
{
	return orientation[2];
}

glm::vec3 Camera::getRight()
{
	return orientation[0];
}

glm::vec3 Camera::getUp()
{
	return orientation[1];
}

glm::vec3 Camera::getPixelv(glm::vec2 uv)
{
	return position + glm::vec3(uv, focal_length) * orientation;
}

Ray Camera::shootRay(glm::vec2 uv)
{
	return Ray::facingPoint(position, getPixelv(uv));
}
