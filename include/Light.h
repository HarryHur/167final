/**************************************************
Light is a class for a camera object.
*****************************************************/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#ifndef __LIGHT_H__
#define __LIGHT_H__

struct Light {
    glm::vec4 position = glm::vec4(3.0f, 2.0f, 1.0f, 0.0f);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    float near_plane = 0.5f, far_plane = 12.0f;
    glm::mat4 proj = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, near_plane, far_plane);  
    glm::vec3 newposition = glm::vec3(position.x, position.y, position.z) * 1.75f;
    glm::mat4 view = glm::lookAt( newposition, 
                                  glm::vec3( 0.0f, 0.0f,  0.0f), 
                                  glm::vec3( 0.0f, 1.0f,  0.0f));  
    glm::mat4 lightSpaceMatrix = proj * view;

    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    GLuint depthMap;
    GLuint depthMapFBO; 

    Light(){
        // FBO stuff
        glGenFramebuffers(1, &depthMapFBO);  

        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  
    }
};

#endif 
