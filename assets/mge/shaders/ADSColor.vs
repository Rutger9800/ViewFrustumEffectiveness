#version 330

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 fNormal;
out vec3 fragPos;
out vec2 texCoord;

void main (void) {
    gl_Position = mvpMatrix * vec4(vertex,1);//need the 1 to indicate position 0 would be direction

    fragPos = vec3(modelMatrix * vec4(vertex,1));//make vertex position in worldspace
    fNormal = vec3(modelMatrix * vec4(normal,0));
    //fNormal = normal;
    texCoord = uv;
}

