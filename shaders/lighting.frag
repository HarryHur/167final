#version 330 core

in vec4 position; // raw position in the model coord
in vec4 positionLS;
in vec3 normal;   // raw normal in the model coord


uniform mat4 model; // from model coord to eye coord 
uniform mat4 view;      // from world coord to eye coord

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
const int maximal_allowed_lights = 10;
uniform bool enablelighting;
uniform int nlights;
uniform vec4 lightpositions[ maximal_allowed_lights ];
uniform vec4 lightcolors[ maximal_allowed_lights ];

// shadowMap
uniform sampler2D shadowMap; 


// Output the frag color
out vec4 fragColor;

// float computeShadow() {
//     // Use if else to prevent occlusion that's clipped
//     vec3 positionLS = positionLS.xyz / positionLS.w; // Clip-space to NDC
// 	positionLS = positionLS * 0.5 + 0.5;	// shifts from [-1, 1] to [0, 1]
// 	float sampledDepth = texture(shadowMap, positionLS.xy).r; 
//     return sampledDepth;
// 	//fragColor = vec4(vec3(sampledDepth), 1.f);
// }

void main (void){
    if (!enablelighting){
        // Default normal coloring (you don't need to modify anything here)
        vec3 N = normalize(normal);
        fragColor = vec4(0.5f*N + 0.5f , 1.0f);
    } else {
        mat4 modelview = view * model;
        vec3 N = normalize(inverse(transpose(mat3(modelview))) * normal);
        vec4 position_eye = modelview * position; //lightposition in eye frame, want to be a vector from lightposition. vector a -> b 
        vec4 temp = emision;
        //vec3 L = vec3(0.0f);
        vec3 view_direction = normalize(-vec3(position_eye));

        for (int i = 0 ; i < nlights; i++){
             vec4 L = view * lightpositions[i]; //light position
             vec3 l = normalize(position_eye.w * vec3(L) - vec3(position_eye) * L.w);
             vec3 h = normalize(view_direction + l);
           // Multiply everything but ambient with 1 - computeShadow
          temp += lightcolors[i] * (ambient + diffuse * max(dot(N,l),0)+ specular * pow(max(dot(N,h),0),shininess));
        }
        fragColor = temp;
        //HW3: You will compute the lighting here.
    }
    
    
}
