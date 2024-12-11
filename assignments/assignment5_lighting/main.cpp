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

// IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

cam::Camera camera = cam::Camera();

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.mouse_callback(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.scroll_callback(window, xoffset, yoffset); 
}

// Lighting
glm::vec3 lightPos(1.0f, 1.0f, 1.0f);

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
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f
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
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lighting", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	 
	//Initialization goes here!

	// Library Variable
	Shades::Shaders shad = Shades::Shaders();
	Texts::Textures tee = Texts::Textures();

	// Mouse controls
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

	// Position for XYZ
	shad.XYZPosition(0, 3, 8, 0);

	// Color RGBA
	shad.XYZPosition(1, 3, 8, 3);
	
	// Texture
	shad.XYZPosition(2, 2, 8, 6);

	// Light Cube VAO
	unsigned int lightVAO;
	shad.createVAO(1, &lightVAO);

	// For Light
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	shad.XYZPosition(1, 2, 8, 3);

	// EBO
	unsigned int EBO;
	tee.createEBO(1, &EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// EBO positions
	shad.XYZPosition(0, 3, 3, 0);

	// Doing texture stuff
	unsigned int texture;
	tee.genAndBind(&texture);

	// Loading and generating the texture
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;

	// Loading in data
	unsigned char* data = stbi_load("assets/cactus.png", &width, &height, &nrChannels, 0);
	tee.checkData(&width, &height, data, &texture);
	

	// set wrapping options, will test/edit later
	tee.textParamsNear();

	// Free data
	stbi_image_free(data);

	// Position for XYZ
	//shad.XYZPosition(0, 3, 5, 0);
	
	// Color RGBA
	//shad.XYZPosition(1, 2, 5, 3);

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


	// Testing this out for lighting
	// Reading files, help from https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
	std::string vertexLightShaderSo;
	std::string fragmentLightShaderSo;
	std::tie(vertexLightShaderSo, fragmentLightShaderSo) = shad.readFile("assets/lightvert.vert", "assets/lightfrag.frag");

	const char* vertexLightShaderSource = vertexLightShaderSo.c_str();
	const char* fragmentLightShaderSource = fragmentLightShaderSo.c_str();

	// Check if Shader Compiles

	// Vertex Shader
	unsigned int vertexLightShader = glCreateShader(GL_VERTEX_SHADER);
	shad.assignShader(vertexLightShader, 1, vertexLightShaderSource, success, infoLog);

	// Fragment shader
	unsigned int fragmentLightShader = glCreateShader(GL_FRAGMENT_SHADER);
	shad.assignShader(fragmentLightShader, 1, fragmentLightShaderSource, success, infoLog);

	// Creating a program
	unsigned int shaderLightProgram = glCreateProgram();
	shad.createProgram(shaderLightProgram, vertexLightShader, fragmentLightShader, success, infoLog);

	//Setting uniforms
	//glUniform1i(glGetUniformLocation(shaderProgram, "texture"), 0);

	// Once the shader objects are linked to the program object, these are no longer needed
	// Can be kept and recompiled and changed, although
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Binding texture (let's hope this works)
	int textureTest = glGetUniformLocation(shaderProgram, "ourTexture");
	glUniform1i(textureTest, 0);

	float prevTime = 0;

	glm::vec3 rotate = camera.createPos();

	// Light floats
	float lightColor = (1.0f, 1.0f, 1.0f);
	float lightMove = (1.0f, 1.0f, 1.0f);
	float ambiMove = 0.1f;
	float specMove = 0.5f;
	int shineMove = 2;

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

		// Time
		int timeLoc = glGetUniformLocation(shaderProgram, "uTime");
		glUniform1f(timeLoc, time);

		// Light Uniform
		int lightCol = glGetUniformLocation(shaderProgram, "lightColor");
		glUniform3fv(lightCol, 1, &lightColor);

		int lightPosition = glGetUniformLocation(shaderProgram, "lightPos");
		glUniform3fv(lightPosition, 1, &lightMove); // coords for the lightPos vector. Should change to be more efficent later (later me changed them)

		int viewPosi = glGetUniformLocation(shaderProgram, "viewPos");
		glUniform3fv(viewPosi, 1, &camera.cameraPos[0]);

		// ImGUI mathy stuff
		int ambiStrength = glGetUniformLocation(shaderProgram, "ambientStrength");
		glUniform3fv(ambiStrength, 1, &ambiMove); // should affect the ambient part of the lights

		int specStrength = glGetUniformLocation(shaderProgram, "specularStrength");
		glUniform3fv(specStrength, 1, &specMove); // should affect the specular part of the lights

		int shineStrength = glGetUniformLocation(shaderProgram, "shine");
		glUniform3iv(shineStrength, 1, &shineMove); // shininess!

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

		// Textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

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

		// Making Light cube!
		glUseProgram(shaderLightProgram);

		// Projection
		unsigned int projLoc1 = glGetUniformLocation(shaderLightProgram, "proj");
		glUniformMatrix4fv(projLoc1, 1, GL_FALSE, glm::value_ptr(proj));

		// Set view
		unsigned int viewLoc1 = glGetUniformLocation(shaderLightProgram, "view");
		glUniformMatrix4fv(viewLoc1, 1, GL_FALSE, &view[0][0]);

		// Setting up model
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		unsigned int modelLoc = glGetUniformLocation(shaderLightProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//binding and displaying cube
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// IMGUI test
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//Create settings window
		ImGui::Begin("Settings");
		ImGui::DragFloat3("Light Position", (float*)&lightMove, 0.1f);
		ImGui::ColorEdit3("LightColor", (float*)&lightColor);
		ImGui::SliderFloat("Ambient K", (float*)&ambiMove, 0.0f, 1.0f);
		ImGui::Text("Diffuse");
		ImGui::SliderFloat("Specular", (float*)&specMove, 0.0f, 1.0f);
		ImGui::SliderInt("Shininess", (int*)&shineMove, 2, 1024);
		ImGui::End();

		// Actually rendering it
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2); //Returns GLFW_PRESS or GLFW_RELEASE

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Unlocks
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Locks

		bool mouseON = false;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2)) {
			mouseON = true;
			while (mouseON == true) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2)) {
					mouseON = false;
				}
			}
			
		}

		//Drawing happens here!
		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}



