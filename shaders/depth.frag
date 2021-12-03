#version 330 core

out vec4 fragColor;
void main(void){
    float near = 0.01f;
    float far = 10.0f;
    float ndc_z = 2 * gl_FragCoord.z - 1;
    float lin_z = (2.0 * near * far) / (far + near - ndc_z * (far - near)); 
    fragColor = vec4(vec3(lin_z / (far - near)), 1.0f);
}
