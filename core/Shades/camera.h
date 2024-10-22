#pragma once

#include "../ew/external/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cam {
	class Camera {
	public:
		void processInput(GLFWwindow* window);

		glm::vec3 getPos() { return cameraPos; }
		glm::vec3 getFront() { return cameraFront; }
		glm::vec3 getUp() { return cameraUp; }

	private:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));
	};
}