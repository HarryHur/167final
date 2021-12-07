/**************************************************
Scene.cpp contains the implementation of the draw command
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"
#include <typeinfo>
#include "DepthShader.h"

// The scene init definition 
#include "Scene.inl"


using namespace glm;
// make this with depth shader address

void Scene::draw(DepthShader *depthShader) {
    glUseProgram(depthShader->program);
    // Pre-draw sequence: assign uniforms that are the same for all Geometry::draw call.  These uniforms include the camera view, proj, and the lights.  These uniform do not include modelview and material parameters.


    // Light space
    depthShader -> view = light["sun"] -> view;
    depthShader -> projection = light["sun"] -> proj;
    
    
    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack; // HW3: You will update this matrix_stack during the depth-first search while loop.
    
    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_M = glm::mat4(1.0f); // HW3: You will update this current modelview during the depth first search.  Initially, we are at the "world" node, whose modelview matrix is just camera's view matrix.

    // HW3: The following is the beginning of the depth-first search algorithm.
    // HW3: The depth-first search for the node traversal has already been implemented (cur, dfs_stack).
    // HW3: All you have to do is to also update the states of (cur_VM, matrix_stack) alongside the traversal.  You will only need to modify starting from this line.
    dfs_stack.push( cur );
    matrix_stack.push(cur_M);
    
    while( ! dfs_stack.empty() ){
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the size of the graph.
        // Note that, at any time, the stack does not contain repeated element.
        if (dfs_stack.size() > node.size() ){
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }
        
        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        cur_M = matrix_stack.top();   matrix_stack.pop(); // (HW3 hint: you should do something here)
        
        // draw all the models at the current node
        for ( unsigned int i = 0; i < cur -> models.size(); i++ ){
            // Prepare to draw the geometry. Assign the modelview and the material.
            glm::mat4 M = cur -> modeltransforms[i];
            // (HW3 hint: you should do something here)
            
            depthShader -> model = cur_M * M; // HW3: Without updating cur_VM, modelview would just be camera's view matrix.
            
            // The draw command
            depthShader -> setUniforms();
            ( cur -> models[i] ) -> geometry -> draw();
        }
        
        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( unsigned int i = 0; i < cur -> childnodes.size(); i++ ){
            cur -> childnodes[i];
            glm::mat4 T = cur -> childtransforms[i];

            dfs_stack.push( cur -> childnodes[i] );
            matrix_stack.push(cur_M * T);// (HW3 hint: you should do something here)
        }
        
    } // End of DFS while loop.
    // HW3: Your code will only be above this line.


}

void Scene::draw(SurfaceShader *surfaceShader) {
    glUseProgram(surfaceShader->program);
    // Pre-draw sequence: assign uniforms that are the same for all Geometry::draw call.  These uniforms include the camera view, proj, and the lights.  These uniform do not include modelview and material parameters.
    camera -> computeMatrices();
    surfaceShader -> view = camera -> view;
    surfaceShader -> projection = camera -> proj;
    surfaceShader -> viewLS = light["sun"] -> view;
    surfaceShader -> projectionLS = light["sun"] -> proj;
    
    // Define stacks for depth-first search (DFS)
    std::stack < Node* > dfs_stack;
    std::stack < mat4 >  matrix_stack; // HW3: You will update this matrix_stack during the depth-first search while loop.
    
    // Initialize the current state variable for DFS
    Node* cur = node["world"]; // root of the tree
    mat4 cur_M = glm::mat4(1.0f);
    
    // HW3: The following is the beginning of the depth-first search algorithm.
    // HW3: The depth-first search for the node traversal has already been implemented (cur, dfs_stack).
    // HW3: All you have to do is to also update the states of (cur_VM, matrix_stack) alongside the traversal.  You will only need to modify starting from this line.
    dfs_stack.push( cur );
    matrix_stack.push(cur_M);
    
    while( ! dfs_stack.empty() ){
        // Detect whether the search runs into infinite loop by checking whether the stack is longer than the size of the graph.
        // Note that, at any time, the stack does not contain repeated element.
        if (dfs_stack.size() > node.size() ){
            std::cerr << "Error: The scene graph has a closed loop." << std::endl;
            exit(-1);
        }
        
        // top-pop the stacks
        cur = dfs_stack.top();        dfs_stack.pop();
        cur_M = matrix_stack.top();   matrix_stack.pop(); // (HW3 hint: you should do something here)
        
        // draw all the models at the current node
        for ( unsigned int i = 0; i < cur -> models.size(); i++ ){
            // Prepare to draw the geometry. Assign the modelview and the material.
            cur -> models[i];
            glm::mat4 M = cur -> modeltransforms[i];
            // (HW3 hint: you should do something here)
            
            surfaceShader -> model = cur_M * M; // HW3: Without updating cur_VM, modelview would just be camera's view matrix.
            surfaceShader -> material  = ( cur -> models[i] ) -> material;
            
            // The draw command
            surfaceShader -> setUniforms();
            ( cur -> models[i] ) -> geometry -> draw();
        }

        // Continue the DFS: put all the child nodes of the current node in the stack
        for ( unsigned int i = 0; i < cur -> childnodes.size(); i++ ){
            cur -> childnodes[i];
            glm::mat4 T = cur -> childtransforms[i];

            dfs_stack.push( cur -> childnodes[i] );
            matrix_stack.push(cur_M * T);// (HW3 hint: you should do something here)
        }
        
    } // End of DFS while loop.
}
