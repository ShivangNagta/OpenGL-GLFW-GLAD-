#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\n";
const char* fragment_shader_source1 =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"     fragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n";
const char* fragment_shader_source2 =
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"     fragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	float verticesTriangle1[] = {
		 0.5f,  1.0f, 0.0f,  
		-0.5f,  1.0f, 0.0f,
		-0.5f,  0.8f, 0.0f,

		-0.5f,  0.8f, 0.0f,
		-0.3f,  0.8f, 0.0f,
		-0.3f, -0.1f, 0.0f,

		-0.3f, -0.1f, 0.0f,
		 0.5f,  0.1f, 0.0f,
		 0.5f, -0.1f, 0.0f,

		 0.3f, -0.1f, 0.0f,
		 0.3f, -1.0f, 0.0f,
		 0.5f, -1.0f, 0.0f,

		 0.3f, -0.8f, 0.0f,
		-0.5f, -1.0f, 0.0f,
		-0.5f, -0.8f, 0.0f
	};
	float verticesTriangle2[] = {
	     0.5f,  1.0f, 0.0f,
	     0.5f,  0.8f, 0.0f,
     	-0.5f,  0.8f, 0.0f,

		-0.5f,  0.8f, 0.0f,
		-0.5f, -0.1f, 0.0f,
		-0.3f, -0.1f, 0.0f,

		-0.3f, -0.1f, 0.0f,
		-0.3f,  0.1f, 0.0f,
		 0.5f,  0.1f, 0.0f,

		 0.3f, -0.1f, 0.0f,
		 0.5f, -0.1f, 0.0f,
		 0.5f, -1.0f, 0.0f,

		 0.3f, -1.0f, 0.0f,
		 0.3f, -0.8f, 0.0f,
		-0.5f, -1.0f, 0.0f
	};
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragment_shader_source1, NULL);
	glCompileShader(fragmentShader1);

	GLuint fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragment_shader_source2, NULL);
	glCompileShader(fragmentShader2);

	GLuint shaderProgram1 = glCreateProgram();
	GLuint shaderProgram2 = glCreateProgram();

	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);


	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	//first
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle1), verticesTriangle1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

    //second
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle2), verticesTriangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 15);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 15);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		};
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		};

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1,VAO);
	glDeleteBuffers(1, VBO);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}