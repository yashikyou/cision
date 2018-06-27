//
//  main.cpp
//  cision
//
//  Created by cxy on 2018/6/26.
//  Copyright © 2018年 cxy. All rights reserved.
//


#import <Foundation/Foundation.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mode);

string read_shader_source(const char* filename);

const GLchar* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 position; \n"
"void main() { \n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
"}";

void render() {
    
}

int main() {
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* win = glfwCreateWindow(640, 480, "Cision", NULL, NULL);
    
    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(win);
    glfwSetKeyCallback(win, key_callback);
    
    // glew init
    glewExperimental = true;
    
    if (glewInit()) {
        return -1;
    }
    
    // paint triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // read glsl
    const GLchar * glsl[1];
    
    string gl_str = read_shader_source("/Users/cxy/project/private/cision/cision/vertex-shader.glsl");
    cout << gl_str << "read file over ~" << endl;
    glsl[0] = gl_str.c_str();
    
    glShaderSource(vertexShader, 1, glsl, NULL);
    glCompileShader(vertexShader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    // read glsl
    gl_str = read_shader_source("/Users/cxy/project/private/cision/cision/fragment-shader.glsl");
    cout << gl_str << "read file over ~" << endl;
    glsl[0] = gl_str.c_str();
    
    glShaderSource(fragmentShader, 1, glsl, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::LINK::SHADER_FAILED\n" << infoLog << endl;
    }
    
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    
    glUseProgram(shaderProgram);
    
    someopen

    while(!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        render();
        
        glfwSwapBuffers(win);
    }
    
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
    return 0;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, GL_TRUE);
    }
}

string read_shader_source(const char* filename) {
    ifstream file(filename);
    
    if (!file.good()) {
        cout << "failed to load file " << filename;
    }
    
    return string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}
