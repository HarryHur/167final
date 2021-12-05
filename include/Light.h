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
};

#endif 
