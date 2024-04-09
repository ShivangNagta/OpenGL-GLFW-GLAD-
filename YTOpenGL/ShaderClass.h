#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
using namespace std;

#include<glad/glad.h>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<cerrno>

string get_file_contents(const char* filename);

class Shader {
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
};


#endif 
