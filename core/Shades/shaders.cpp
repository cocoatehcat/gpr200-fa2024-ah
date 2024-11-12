#include "shaders.h"

namespace Shades {
	void Shaders::createVAO(int num, unsigned int* va) {
		glGenVertexArrays(num, va);
		glBindVertexArray(*va);
	}

	void Shaders::createVBO(int num, unsigned int* vb) {
		glGenBuffers(num, vb);
		glBindBuffer(GL_ARRAY_BUFFER, *vb);
	}	

	void Shaders::XYZPosition(int index, GLint in2, int length, int voidNum) {
        glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, in2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void*)(sizeof(float) * voidNum));
		
	}

    std::tuple<std::string, std::string> Shaders::readFile(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath); // I am going wrong somewhere around here
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        //const char* vShaderCode = vertexCode.c_str();
        //const char* fShaderCode = fragmentCode.c_str();

        return {vertexCode, fragmentCode};
    }

    void Shaders::assignShader(unsigned int ver, int i, const char* source, int wee, char log[]) {
        glShaderSource(ver, i, &source, NULL);
        glCompileShader(ver);

        checkFail(ver, wee, log);
    }

    void Shaders::checkFail(unsigned int shader, int wee, char log[]) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &wee);

        if (!wee)
        {
            glGetShaderInfoLog(shader, 512, NULL, log);
            printf("ERROR::SHADER::COMPILATION_FAILED\n%s", log);
        }
    }

    void Shaders::createProgram(unsigned int prog, unsigned int vert, unsigned int frag, int wee, char log[]) {
        glAttachShader(prog, vert);
        glAttachShader(prog, frag);
        glLinkProgram(prog);
        glUseProgram(prog);

        checkCompile(prog, wee, log);
    }

    void Shaders::checkCompile(unsigned int prog, int wee, char log[]) {
        glGetProgramiv(prog, GL_LINK_STATUS, &wee);
        if (!wee) {
            glGetProgramInfoLog(prog, 512, NULL, log);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", log);
        }
    }
}