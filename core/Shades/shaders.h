#pragma once

#include "../ew/external/glad.h"
#include <fstream>
#include <sstream>
#include <tuple>

namespace Shades {
	class Shaders {
	public:
		void createVAO(int num, unsigned int* va);
		void createVBO(int num, unsigned int* vb);
		void XYZPosition(int index, GLint in2, int length, int voidNum);
		std::tuple<std::string, std::string> readFile(const char* vertexPath, const char* fragmentPath);
		void assignShader(unsigned int ver, int i, const char* source, int wee, char log[]);
		void checkFail(unsigned int shader, int wee, char log[]);
		void createProgram(unsigned int prog, unsigned int vert, unsigned int frag, int wee, char log[]);
		void checkCompile(unsigned int prog, int wee, char log[]);
	};
}