#include <stdio.h>
#include <math.h>
#include <fstream>

#include <ew/external/glad.h>
#include <ew/external/stb_image.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shades/shaders.h>
#include <Shades/textures.h>
#include <Shades/camera.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

cam::Camera camera = cam::Camera();

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.mouse_callback(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.scroll_callback(window, xoffset, yoffset);
}

/*
float vertices[] = {
	// X	 Y	   Z	 R	   G	B	  A (removed for now)	Texture coords
	 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,                        1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,                       1.0f, 0.0f, // bottom right
	// -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top left
	 //second triangle
	// 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom right
	 -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,                      0.0f, 0.0f, // bottom left
	 -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,                      0.0f, 1.0f, // top left
}; */

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

glm::vec3 cubePositions[] = {
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
	glm::vec3(camera.createPos()),
};

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!

	// Library Variable
	Shades::Shaders shad = Shades::Shaders();
	Texts::Textures tee = Texts::Textures();

	// Mouse controls
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback); // how are these supposed to work?

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Enabled Depth for 3D objects
	glEnable(GL_DEPTH_TEST);

	// VAO
	unsigned int VAO;
	shad.createVAO(1, &VAO);

	// VBO
	unsigned int VBO;
	shad.createVBO(1, &VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	unsigned int EBO;
	tee.createEBO(1, &EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// EBO positions
	shad.XYZPosition(0, 3, 3, 0);

	// Doing texture stuff
	unsigned int texture;
	tee.genAndBind(&texture);

	// set wrapping options, will test/edit later
	tee.textParamsNear();

	// Loading and generating the texture
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;

	// Loading in data
	unsigned char* data = stbi_load("assets/cactus.png", &width, &height, &nrChannels, 0);
	tee.checkData(&width, &height, data);
	stbi_image_free(data);

	// Position for XYZ
	shad.XYZPosition(0, 3, 5, 0);
	
	// Color RGBA
	shad.XYZPosition(1, 2, 5, 3);

	// Texture positions
	//shad.XYZPosition(2, 2, 8, 6);
	
	
	// Reading files, help from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
	std::string vertexShaderSo;
	std::string fragmentShaderSo;
	std::tie(vertexShaderSo, fragmentShaderSo) = shad.readFile("assets/vertexShader.vert", "assets/fragmentShader.frag");

	const char* vertexShaderSource = vertexShaderSo.c_str();
	const char* fragmentShaderSource = fragmentShaderSo.c_str();

	// Check if Shader Compiles
	int  success = 0;
	char infoLog[512];

	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	shad.assignShader(vertexShader, 1, vertexShaderSource, success, infoLog);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shad.assignShader(fragmentShader, 1, fragmentShaderSource, success, infoLog);

	// Creating a program
	unsigned int shaderProgram = glCreateProgram();
	shad.createProgram(shaderProgram, vertexShader, fragmentShader, success, infoLog);

	//Setting uniforms
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);

	// Once the shader objects are linked to the program object, these are no longer needed
	// Can be kept and recompiled and changed, although
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float prevTime = 0;

	glm::vec3 rotate = camera.createPos();

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Counting number of seconds passed since the beginning
		float time = (float)glfwGetTime();

		float deltaTime = time - prevTime;

		prevTime = time;

		// Getting input
		camera.processInput(window, deltaTime);

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Binding texture
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		// Knows what program to use
		glUseProgram(shaderProgram);
		int timeLoc = glGetUniformLocation(shaderProgram, "uTime");
		glUniform1f(timeLoc, time);

		// Binding texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Messing around with persepctive, replace with screen width and height later to see?
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); moving this down

		// Going 3D!
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		// Making the view
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // moving scene back to make it seems right to us
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getUp());

		// Projection
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

		// Retrieve uniform locations
		//unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "proj");

		//pass to shaders
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Binding Vertex aray and draw it
		glBindVertexArray(VAO);
		// Draw Call
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);


		for (unsigned int i = 0; i < 20; i++) { //change to 20 later
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle) * time, rotate);
			model = glm::scale(model, cubePositions[i]);
			unsigned int modelLoc1 = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model));

			// DRAW THE SUCKERS
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}



