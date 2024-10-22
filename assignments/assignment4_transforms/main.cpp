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

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


float vertices[] = {
	// X	 Y	   Z	 R	   G	B	  A (removed for now)	Texture coords
	 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,                        1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,                       1.0f, 0.0f, // bottom right
	// -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top left
	 //second triangle
	// 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom right
	 -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,                      0.0f, 0.0f, // bottom left
	 -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,                      0.0f, 1.0f, // top left
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 createPos() {
	float x, y, z;
	x = ew::RandomRange(-20.0f, 20.0f);
	y = ew::RandomRange(-20.0f, 20.0f);
	z = ew::RandomRange(-20.0f, 20.0f);
	return glm::vec3(x, y, z);
}

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

	/*
	// Generating texture two
	unsigned int texture2;
	tee.genAndBind(&texture2);
	tee.textParamsLin();

	// Loading in data
	data = stbi_load("assets/Little_Pink_Man_02.png", &width, &height, &nrChannels, 0);
	tee.checkData(&width, &height, data);
	stbi_image_free(data);
	*/

	// Position for XYZ
	shad.XYZPosition(0, 3, 8, 0);
	
	// Color RGBA
	shad.XYZPosition(1, 3, 8, 3);

	// Texture positions
	shad.XYZPosition(2, 2, 8, 6);
	
	
	// Reading files, help from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
	std::string vertexShaderSo;
	std::string fragmentShaderSo;
	std::tie(vertexShaderSo, fragmentShaderSo) = shad.readFile("assets/vertexShader.vert", "assets/fragmentShader.frag");

	/*std::string str = "string";
	const char *cstr = str.c_str();*/

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

	/*
	// Creating for background
	// Reading files, help from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
	std::string vertexBackShaderSo;
	std::string fragmentBackShaderSo;
	std::tie(vertexBackShaderSo, fragmentBackShaderSo) = shad.readFile("assets/background.vert", "assets/backgroundfrag.frag");

	/*std::string str = "string";
	const char *cstr = str.c_str();

	const char* vertexBackShaderSource = vertexBackShaderSo.c_str();
	const char* fragmentBackShaderSource = fragmentBackShaderSo.c_str();

	// Check if Shader Compiles
	//int  success = 0;
	//char infoLog[512];

	// Vertex Shader
	unsigned int vertexBackShader = glCreateShader(GL_VERTEX_SHADER);
	shad.assignShader(vertexBackShader, 1, vertexBackShaderSource, success, infoLog);

	// Fragment shader
	unsigned int fragmentBackShader = glCreateShader(GL_FRAGMENT_SHADER);
	shad.assignShader(fragmentBackShader, 1, fragmentBackShaderSource, success, infoLog);

	// Creating a program
	unsigned int shaderBackProgram = glCreateProgram();
	shad.createProgram(shaderBackProgram, vertexBackShader, fragmentBackShader, success, infoLog);
	*/


	//Setting uniforms
	glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);
	//glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

	// Once the shader objects are linked to the program object, these are no longer needed
	// Can be kept and recompiled and changed, although
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//glDeleteShader(vertexBackShader);
	//glDeleteShader(fragmentBackShader);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// Counting number of seconds passed since the beginning
		float time = (float)glfwGetTime();

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Knows what program to use take 2 (AKA background)
		//glUseProgram(shaderBackProgram);
		//int timeBackLoc = glGetUniformLocation(shaderBackProgram, "uTime");
		//glUniform1f(timeBackLoc, time);

		// Binding texture
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture2);

		//glBindVertexArray(VAO); // let's hope this works
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw call

		// Knows what program to use
		glUseProgram(shaderProgram);
		int timeLoc = glGetUniformLocation(shaderProgram, "uTime");
		glUniform1f(timeLoc, time);

		// Binding texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);


		// Messing around with persepctive, replace with screen width and height later to see?
		//glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); moving this down

		// Going 3D!
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		// Making the view
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // moving scene back to make it seems right to us

		// Projection
		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		// Retrieve uniform locations
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "proj");

		//pass to shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));



		// Binding Vertex aray and draw it
		glBindVertexArray(VAO);
		// Draw Call
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		for (unsigned int i = 0; i < 20; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, createPos());
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle) * time, createPos());
			model = glm::scale(model, createPos());
			unsigned int modelLoc1 = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, glm::value_ptr(model));

			// DRAW THE SUCKERS
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}



