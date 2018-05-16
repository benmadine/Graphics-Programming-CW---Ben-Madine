#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <intrin.h>

#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader();

	void Binding(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	void initFragVert(const std::string& vertFile, const std::string& fragFile);
	void initFragVertGeom(const std::string& geomFileVert, const std::string& geomFileFrag, const std::string& geomFileGeo);
	GLuint programGetter() { return shaderProgram; }

	std::string Shader::loadingShader(const std::string& fileName);
	void Shader::CheckError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::ShaderCreator(const std::string& text, unsigned int type);


#pragma region Uniform 
	// uniform functions
	// ------------------------------------------------------------------------
	void setTheBoolean(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation
			(shaderProgram, name.c_str()), (int)value);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheIntegar(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheFloatValue(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheVector2Value(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setTheVector2Value(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheVectorThreeValue(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setTheVectorThreeValue(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheVectorFourValue(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setTheVectorFourValue(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheMatrixTwoValue(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setTheMatrixThreeValue(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void swtTheMatrixFourValue(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderProgram, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}

#pragma endregion

	~Shader();

protected:
private:
	static const unsigned int numberOfShaders = 3; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint shaderProgram; // Track the shader program
	GLuint shaders[numberOfShaders]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
