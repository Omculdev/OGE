#include <GLAD/glad.h>	
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <stdexcept>
#include <iostream>
#include <cmath>

GLfloat x = 0;
GLfloat y = 0;
GLfloat z = 3;
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		z += 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		z -= 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		x -= 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		x += 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		y += 0.1f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		y -= 0.1f;
	}
	
}
GLfloat sizex = 0.5f;
GLfloat sizey = 0.5f;
GLfloat sizez = 0.5f;
GLfloat poscenteroffsetx = sizex / 2.0f;
GLfloat poscenteroffsety = sizey / 2.0f;
GLfloat poscenteroffsetz = sizez / 2.0f;
GLfloat negcenteroffsetx = -1 * sizex / 2.0f;
GLfloat negcenteroffsety = -1* sizey / 2.0f;
GLfloat negcenteroffsetz = -1* sizez / 2.0f;
GLfloat vertices[] = {
	negcenteroffsetx, negcenteroffsety, negcenteroffsetz, // A
	negcenteroffsetx, negcenteroffsety, poscenteroffsetz, // B
	poscenteroffsetx, negcenteroffsety, poscenteroffsetz, // C
	poscenteroffsetx, negcenteroffsety, negcenteroffsetz, // D
	negcenteroffsetx, poscenteroffsety, negcenteroffsetz, // A1
	negcenteroffsetx, poscenteroffsety, poscenteroffsetz, // B1
	poscenteroffsetx, poscenteroffsety, poscenteroffsetz, // C1
	poscenteroffsetx, poscenteroffsety, negcenteroffsetz //D1
};
GLuint indexes[] = {
	0,2,3, // ACD
	0,1,2, // ABC
	4,6,7, // A1C1D1
	4,5,6, // A1B1C1
	0,4,5, // AA1B1
	0,1,5, // ABB1
	2,3,6, // CDC1
	3,6,7, // DC1D1
	0,3,4, // ADA1
	3,4,7, // DA1D1
	1,2,5, // BCB1
	2,5,6 //CB1C1
};
GLfloat colors[] = {
	0.0f, 0.1f, 0.0f,
	0.0f, 0.2f, 0.0f,
	0.0f, 0.3f, 0.0f,
	0.0f, 0.4f, 0.0f,
	0.0f, 0.7f, 0.0f,
	0.0f, 0.8f, 0.0f,
	0.0f, 0.9f, 0.0f,
	0.0f, 1.0f, 0.0f
};
glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f);
glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 back = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
glm::vec3 normals[] = {
	glm::normalize(forward + up + left), //A
	glm::normalize(back + up + left), //B
	glm::normalize(back+ up + right), //C
	glm::normalize(forward + up + right), //D
	glm::normalize(forward + down + left), //A1
	glm::normalize(back + down + left), //B1
	glm::normalize(back + down + right), //C1
	glm::normalize(forward + down+ right) //D1
};
GLfloat AmbientLight = 0.1f;
GLfloat Brightness = 5.0f;
glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 LightPosition = glm::vec3(3.0f, 3.0f, 3.0f);
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::lookAt(
	glm::vec3(x, y, z),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f)
);
glm::mat4 projection = glm::perspective(
	glm::radians(45.0f),
	1000.0f/1000.0f,
	0.1f,
	100.0f
);
GLuint VBO, EBO;
GLuint VAO;
GLuint VertexShader, FragmentShader;
GLuint ShaderProgram;
GLuint ModelLoc, ViewLoc, ProjectionLoc;
GLuint AmbientLightLoc, BrightnessLoc, LightColorLoc, LightPositionLoc;
const char* VertexShaderSource = R"(
	#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float ambientlight;
uniform float brightness;
uniform vec3 lightposition;
uniform vec3 lightcolor;

layout (location = 0) in vec3 vertexposition;
layout (location = 1) in vec3 colorin;
layout (location = 2) in vec3 Normal;

out vec4 colorout;


void main() {
	vec3 normal = normalize(Normal);
    vec3 distancetolightsource = normalize(vertexposition - lightposition);
    float difflight = max(dot(distancetolightsource, normal), 0.0);
    vec3 diffuse = difflight * lightcolor * colorin;
    vec3 ambient = lightcolor* colorin * ambientlight;
    colorout = vec4(ambient + diffuse, 1.0);
    gl_Position = projection * view * model * vec4(vertexposition, 1.0); 
}
)";
const char* FragmentShaderSource = R"(
	#version 330 core

	in vec4 colorout;

	out vec4 finalcolor;

	void main() {
		finalcolor = colorout;
	}
)";
void init_buffers() {
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);
}
void init_vertex_arrays() {
	glGenVertexArrays(1, &VAO);
}
void init_shaders() {
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(VertexShader);
	glCompileShader(FragmentShader);
}
void init_shader_program() {
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}
void init_light_locs() {
	AmbientLightLoc = glGetUniformLocation(ShaderProgram, "ambientlight");
	BrightnessLoc = glGetUniformLocation(ShaderProgram, "brightness");
	LightPositionLoc = glGetUniformLocation(ShaderProgram, "lightposition");
	LightColorLoc = glGetUniformLocation(ShaderProgram, "lightcolor");
}
void init_matrix_locs() {
	ModelLoc = glGetUniformLocation(ShaderProgram, "model");
	ViewLoc = glGetUniformLocation(ShaderProgram, "view");
	ProjectionLoc = glGetUniformLocation(ShaderProgram, "projection");
}
void send_vertices_data_to_vram() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(normals), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(normals), normals);
}
void send_indexes_to_vram() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_DYNAMIC_DRAW);
}
void init_attrib_pointers() {
	glVertexAttribPointer(0, 3, GL_FLOAT ,GL_FALSE, 3 * sizeof(GLfloat), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(vertices)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (void*)(sizeof(vertices) + sizeof(colors)));

	for (int i = 0; i < 3; i++) {
		glEnableVertexAttribArray(i);
	}
}
void create_vertex_array() {
	glBindVertexArray(VAO);
	send_vertices_data_to_vram();
	send_indexes_to_vram();
	init_attrib_pointers();
	glBindVertexArray(0);
}
void send_matrices_to_shader() {
	glUniformMatrix4fv(ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
void send_lighting_data_to_shader() {
	glUniform1f(AmbientLightLoc, AmbientLight);
	glUniform1f(BrightnessLoc, Brightness);
	glUniform3fv(LightPositionLoc, 1, glm::value_ptr(LightPosition));
	glUniform3fv(LightColorLoc, 1, glm::value_ptr(LightColor));
}
void init_depth() {
	glEnable(GL_DEPTH_TEST);
}
void init_everything() {
	init_buffers();
	init_vertex_arrays();
	init_shaders();
	init_shader_program();
	init_light_locs();
	init_matrix_locs();
	create_vertex_array();
	init_depth();
}
void draw() {
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	send_matrices_to_shader();
	send_lighting_data_to_shader();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(0));
}
void handle_matrix_updates() {
	view = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}
int mains() {
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
	init_everything();
	glViewport(0, 0, 1000, 1000);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(
			0.0f,
			0.0f,
			0.0f,
			1.0f
		);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		handle_matrix_updates();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}