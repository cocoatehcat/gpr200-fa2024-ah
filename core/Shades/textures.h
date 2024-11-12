#pragma once

#include "../ew/external/glad.h"

namespace Texts {
	class Textures {
	public:
		void createEBO(int num, unsigned int* eb);
		void genAndBind(unsigned int* texts);
		void textParamsNear();
		void textParamsLin();
		void checkData(int* x, int* y, unsigned char* dat, unsigned int *ID);
	};
}