#include "camera.h"

namespace cam {
	void Camera::processInput(GLFWwindow* window) {
		const float cameraSpeed = 0.05f; // can be adjusted
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}				
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; 
		}
		//if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { // Figure this out more later
		//	cameraPos += cameraSpeed * 2;
		//}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraRight)) * cameraSpeed;
		}
	}
}