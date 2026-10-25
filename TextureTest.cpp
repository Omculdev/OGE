#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/glm.hpp>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION 
#include <STB_IMAGE/stb_image.h>
#include <iostream>
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	

}
int width, height, numberofchannels;
unsigned char* data1 = stbi_load("C:\\Users\\Roma\\Downloads\\myKING.jpg", &width, &height, &numberofchannels, 4);
GLfloat vertices1[] = {
	0, 0, 0,		1.0f, 0, 0, 1.0f,		1.0f, 1.0f,
	0, 0.5f, 0,		0, 1.0f, 0, 1.0f,		1.0f, 0.0f,
	0.5f, 0, 0,		0, 0, 1.0f, 1.0f,		0.0f, 1.0f,
	0.5f, 0.5f,		0, 1.0f, 0, 0, 1.0f,	0.0f, 0.0f,
};
GLuint indeces1[] = {
	0,1,2,
	1,2,3
};
GLuint VBO1, EBO1;
GLuint VAO1;
GLuint shaderprogram1, vertexshader1, fragmentshader1;
const char* vertexshadersource = R"(
	#version 330 core

	layout (location = 0) in vec3 position;
	layout (location = 1) in vec4 colorin;
	layout (location = 2) in vec2 texcordsin;
	
	out vec4 color_out;
	out vec2 texcords_out;
	void main() {
		gl_Position = vec4(position, 1.0);
		texcords_out = texcordsin;
		color_out = colorin; 
})";
const char* fragmentshadersource = R"(
	#version 330 core

	in vec4 color_out;
	in vec2 texcords_out;

	out vec4 final_color;
	uniform sampler2D texturesampler;
	
	void main() {
		
		final_color = texture(texturesampler, texcords_out);
})";

GLuint texture;

void init() {
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &EBO1);
	glGenVertexArrays(1, &VAO1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data1);

	vertexshader1 = glCreateShader(GL_VERTEX_SHADER);
	fragmentshader1 = glCreateShader(GL_FRAGMENT_SHADER);
	shaderprogram1 = glCreateProgram();
	glShaderSource(vertexshader1, 1, &vertexshadersource, NULL);
	glShaderSource(fragmentshader1, 1, &fragmentshadersource, NULL);
	GLint success;
	GLchar infoLog[512];

	glCompileShader(vertexshader1);
	glGetShaderiv(vertexshader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexshader1, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER ERROR:\n" << infoLog << std::endl;
	}

	glCompileShader(fragmentshader1);
	glGetShaderiv(fragmentshader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentshader1, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER ERROR:\n" << infoLog << std::endl;
	}
	glAttachShader(shaderprogram1, vertexshader1);
	glAttachShader(shaderprogram1, fragmentshader1);
	glLinkProgram(shaderprogram1);
	glGetProgramiv(shaderprogram1, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderprogram1, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK ERROR:\n" << infoLog << std::endl;
	};
	glDeleteShader(vertexshader1);
	glDeleteShader(fragmentshader1);
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces1), indeces1, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(0));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3 + sizeof(GLfloat) * 4));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

}
void draw1() {
	glUseProgram(shaderprogram1);
	glBindVertexArray(VAO1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));
}
int maim() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 1000, "hello world", NULL, NULL);
	if (!window) {
		throw std::runtime_error("failed to create window");
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("failed to init opengl functions");
	}
	glViewport(0, 0, 1000, 1000);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	init();
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(
			0.0f,
			0.0f,
			0.0f,
			1.0f
		);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw1();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}