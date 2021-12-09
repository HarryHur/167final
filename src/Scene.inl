/**************************************************
Scene.inl contains the definition of the scene graph
*****************************************************/
#include "Scene.h"
#include "Cube.h"
#include "Obj.h"

using namespace glm;
void Scene::init(void){
    // Create a geometry palette
    geometry["cube"] = new Cube;
    geometry["teapot"] = new Obj;
    geometry["bunny"] = new Obj;
    geometry["cube"] -> init();
    geometry["teapot"] -> init("models/teapot.obj");
    geometry["bunny"] -> init("models/bunny.obj");
    
    // Create a material palette
    material["wood"] = new Material;
    material["wood"] -> ambient = vec4(0.1f,0.1f,0.1f,1.0f);
    material["wood"] -> diffuse = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> specular = vec4(0.3f,0.15f,0.1f,1.0f);
    material["wood"] -> shininess = 100.0f;
    
    material["ceramic"] = new Material;
    material["ceramic"] -> ambient = vec4(0.02f, 0.07f, 0.2f, 1.0f);
    material["ceramic"] -> diffuse = vec4(0.1f, 0.25f, 0.7f, 1.0f);
    material["ceramic"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["ceramic"] -> shininess = 150.0f;
 
    material["silver"] = new Material;
    material["silver"] -> ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    material["silver"] -> diffuse = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    material["silver"] -> specular = vec4(0.9f, 0.9f, 0.9f, 1.0f);
    material["silver"] -> shininess = 50.0f;
    
    material["turquoise"] = new Material;
    material["turquoise"] -> ambient = vec4(0.1f, 0.2f, 0.17f, 1.0f);
    material["turquoise"] -> diffuse = vec4(0.2f, 0.375f, 0.35f, 1.0f);
    material["turquoise"] -> specular = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    material["turquoise"] -> shininess = 100.0f;
    
    material["bulb"] = new Material;
    material["bulb"] -> ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    material["bulb"] -> specular = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    material["bulb"] -> emision = vec4(1.0f,0.2f,0.1f,1.0f);
    material["bulb"] -> shininess = 200.0f;
    
    // Create a model palette
    model["teapot1"] = new Model;
    model["teapot1"] -> geometry = geometry["teapot"];
    model["teapot1"] -> material = material["silver"];
    model["teapot2"] = new Model;
    model["teapot2"] -> geometry = geometry["teapot"];
    model["teapot2"] -> material = material["ceramic"];
    model["table piece"] = new Model;
    model["table piece"] -> geometry = geometry["cube"];
    model["table piece"] -> material = material["wood"];
    model["bunny"] = new Model;
    model["bunny"] -> geometry = geometry["bunny"];
    model["bunny"] -> material = material["turquoise"];
    model["bulb"] = new Model;
    model["bulb"] -> geometry = geometry["cube"];
    model["bulb"] -> material = material["bulb"];
    model["ground"] = new Model;
    model["ground"] -> geometry = geometry["cube"];
    model["ground"] -> material = material["ceramic"];
    
    model["bigbunny"] = new Model;
    model["bigbunny"] -> geometry = geometry["bunny"];
    model["bigbunny"] -> material = material["bulb"];

    model["water1"] = new Model;
    model["water1"] -> geometry = geometry["cube"];
    model["water1"] -> material = material["ceramic"];

    model["water2"] = new Model;
    model["water2"] -> geometry = geometry["cube"];
    model["water2"] -> material = material["ceramic"];
    
    
    // Create a light palette
    light["sun"] = new Light;
    light["sun"] -> position = 1.75f * vec4(3.0f,2.0f,1.0f,0.0f);
    light["sun"] -> color = 1.0f*vec4(1.0f,1.0f,1.0f,1.0f);
    light["sun"] -> computeMatrices();
    
    
    // Build the scene graph
    node["table"] = new Node;
    node["table top"] = new Node;
    node["table leg"] = new Node;
    node["teapot1"] = new Node;
    node["teapot2"] = new Node;
    node["bunny"] = new Node;
    node["ground"] = new Node;

    node["bigbunny"] = new Node;
    node["water1"] = new Node;
    node["water2"] = new Node;

    node["table"] -> childnodes.push_back( node["table top"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.0f,1.2f,0.0f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,-0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(-0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,0.4f)) );
    node["table"] -> childnodes.push_back( node["table leg"] );
    node["table"] -> childtransforms.push_back( translate(vec3(0.9f,0.0f,-0.4f)) );
    
    node["table leg"] -> models.push_back( model["table piece"] );
    node["table leg"] -> modeltransforms.push_back( translate(vec3(0.0f,0.5f,0.0f)) * scale(vec3(0.2f,1.0f,0.2f)) );
    
    node["table top"] -> models.push_back( model["table piece"] );
    node["table top"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.1f,0.0f)) * scale(vec3(2.0f,0.2f,1.0f)) );
    node["table top"] -> childnodes.push_back( node["teapot1"] );
    node["table top"] -> childtransforms.push_back( translate(vec3(-0.8f,0.7f,0.0f)) * rotate( 180.0f*float(M_PI)/180.0f, vec3(-0.5f, 1.0f, 0.0f) )  );
    node["table top"] -> childnodes.push_back( node["teapot2"] );
    node["table top"] -> childtransforms.push_back( translate(vec3( 0.5f,0.7f,0.0f)) * rotate( 330.0f*float(M_PI)/180.0f, vec3(0.0, 1.0f, 0.9f) ) );
    
    node["teapot1"] -> models.push_back( model["teapot1"] );
    node["teapot1"] -> modeltransforms.push_back( scale(vec3(0.5f)) );
    node["teapot2"] -> models.push_back( model["teapot2"] );
    node["teapot2"] -> modeltransforms.push_back( scale(vec3(1.0f,1.5f,1.0f)) * scale(vec3(0.5f)) );
    
    node["bunny"] -> models.push_back( model["bunny"] );
    node["bunny"] -> modeltransforms.push_back( scale(vec3(1.2f)) * translate(vec3(0.0f,1.0f,0.0f)) );
    
//
    node["ground"] -> models.push_back( model["ground"] );
    node["ground"] -> modeltransforms.push_back( translate(vec3(0.0f,-0.5f,0.0f)) * scale(vec3(20.0f,1.0f,10.0f)) );
    
    node["bigbunny"] -> models.push_back( model["bigbunny"]);
    node["bigbunny"] -> modeltransforms.push_back ( scale(vec3(1.2f)) * translate(vec3(0.0f,1.0f,0.0f)));

    node["water1"] -> models.push_back( model["water1"]);
    node["water1"] -> modeltransforms.push_back (scale(vec3(0.02f,0.5f,0.1f)) * translate(vec3(0.0f,-0.5f,0.0f)));

    node["water2"] -> models.push_back( model["water2"]);
    node["water2"] -> modeltransforms.push_back (scale(vec3(0.02f,0.5f,0.1f)) * translate(vec3(0.0f,-0.5f,0.0f)));


    node["world"] -> childnodes.push_back( node["table"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    node["world"] -> childnodes.push_back( node["bunny"] );
    node["world"] -> childtransforms.push_back( translate(vec3(-2.3f,0.0f,0.0f)) * rotate( 180.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));
    node["world"] -> childnodes.push_back( node["ground"] );
    node["world"] -> childtransforms.push_back( mat4(1.0f) );
    
    node["world"] -> childnodes.push_back( node["bigbunny"] );
    node["world"] -> childtransforms.push_back( translate(vec3(2.3f,0.0f,0.0f)) * rotate( 0.0f*float(M_PI)/180.0f, vec3(0.0f, 1.0f, 0.0f) ));

    node["world"] -> childnodes.push_back( node["water1"] );
    node["world"] -> childtransforms.push_back( translate(vec3(-1.4f,1.6f,0.0f)) * rotate( 0.0f *float(M_PI)/180.0f, vec3(0.0f,1.0f, 0.0f)));    
    
    node["world"] -> childnodes.push_back( node["water2"] );
    node["world"] -> childtransforms.push_back( translate(vec3(1.2f,2.2f,0.3f)) * rotate( 330.0f *float(M_PI)/180.0f, vec3(0.0f,1.0f, 0.0f)));    

    // Put a camera
    camera = new Camera;
    camera -> target_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> eye_default = vec3( 0.0f, 1.0f, 5.0f );
    camera -> up_default = vec3( 0.0f, 1.0f, 0.0f );
    camera -> reset();
    
    // Initialize shader
    shader = new SurfaceShader;
    shader -> read_source( "shaders/projective.vert", "shaders/lighting.frag" );
    shader -> compile();
    shader -> initUniforms();

    depthShader = new DepthShader;
    depthShader -> read_source( "shaders/projective.vert", "shaders/depth.frag" );
    depthShader -> compile();
    depthShader -> initUniforms();
}
