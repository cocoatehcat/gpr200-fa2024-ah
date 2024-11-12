#include "textures.h"

namespace Texts {
	void Textures::createEBO(int num, unsigned int* eb) {
		glGenBuffers(num, eb);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *eb);
	}

	void Textures::genAndBind(unsigned int *texts) {
		glGenTextures(0, texts);
		//glBindTexture(GL_TEXTURE_2D, *texts);
	}

	void Textures::textParamsNear() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Textures::textParamsLin() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void Textures::checkData(int* x, int* y, unsigned char* dat, unsigned int *ID) {
		if (dat) {
			glBindTexture(GL_TEXTURE_2D, *ID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *x, *y, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		// print didn't want to work so else cry?
		//printf("Failed to load texture");
	}
}