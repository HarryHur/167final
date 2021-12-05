/***********************
This is a shader consisting of vertex shader and fragment shader.
It has the external file reading and compilation capability.
Example:
Shader myshader;
myshader.read_source( <vtxshader_path>, <fragshader_path >);
myshader.compile();
The resulting shader program is the class member "program."
So, to use the program, simply call
glUseProgram(myshader.program);
The users are welcomed to subclass this Shader class. For example,
class ShaderForMyProject : Shader{
public:
    GLuint some_uniform_variable_position;
    GLfloat some_uniform_variable_value;
}
to further encapsulate various parameters that are associated with
your shader.
 ***********************/

#include "Shader.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <cstring>
#include "Material.h"
#include "Camera.h"

#ifndef __DEPTHSHADER_H__
#define __DEPTHSHADER_H__

struct DepthShader: Shader {
    // modelview and projection
    glm::mat4 view = glm::mat4(1.0f); GLuint view_loc;
    glm::mat4 model = glm::mat4(1.0f); GLuint model_loc;
    glm::mat4 projection = glm::mat4(1.0f); GLuint projection_loc;

    // Responsible for finding variables we have and save address
    // Only model and projection needed
    void initUniforms(){
        view_loc  = glGetUniformLocation( program, "view" );
        model_loc  = glGetUniformLocation( program, "model" );
        projection_loc = glGetUniformLocation( program, "projection" );
        
    }
    void setUniforms(){
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection[0][0]);
    }
};

#endif 
