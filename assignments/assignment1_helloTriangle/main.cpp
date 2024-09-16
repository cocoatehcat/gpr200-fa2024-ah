#include <stdio.h>
#include <math.h>
#include <fstream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Shades/shaders.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	// X	 Y	   Z	 R	   G	B	  A
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
};

// Compiling a shader
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color; //Varying
uniform float uTime;
void main()
{
   Color = aColor; // Pass-through
   vec3 pos = aPos;
   pos.y += sin(uTime * 4.0 + pos.x) / 4.0;
   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
in vec4 Color;
uniform float uTime;
uniform vec4 uColor = vec4(1.0);

void main()
{
    FragColor = Color * (sin(uTime) * 0.5 + 0.5); 
	//This is the hard code: vec4(1.0f, 0.2f, 0.7f, 1.0f);
} 
)";

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
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

	// VAO
	unsigned int VAO;
	shad.createVAO(1, &VAO);

	// VBO
	unsigned int VBO;
	shad.createVBO(1, &VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position for XYZ
	shad.XYZPosition(0, 3, 7, 0);
	
	// Color RGBA
	shad.XYZPosition(1, 4, 7, 3);
	
	// Reading files, help from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
	//const char* vertexShaderSource;
	//const char* fragmentShaderSource;
	//std::tie(vertexShaderSource, fragmentShaderSource) = shad.readFile("vertexShader.vert", "fragmentShader.frag");

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

	// Once the shader objects are linked to the program object, these are no longer needed
	// Can be kept and recompiled and changed, although
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// Counting number of seconds passed since the beginning
		float time = (float)glfwGetTime();

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Knows what program to use
		glUseProgram(shaderProgram);
		int timeLoc = glGetUniformLocation(shaderProgram, "uTime");
		glUniform1f(timeLoc, time);

		// Binding Vertex aray and draw it
		glBindVertexArray(VAO);
		// Draw Call
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
