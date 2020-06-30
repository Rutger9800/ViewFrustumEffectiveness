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
    gl_Position = mvpMatrix * vec4(vertex,1);

    fragPos = vec3(modelMatrix * vec4(vertex,1));//this makes vertex position in worldspace
    //fNormal = normal;
    fNormal = vec3(modelMatrix * vec4(normal,0));
    texCoord = uv;
}

