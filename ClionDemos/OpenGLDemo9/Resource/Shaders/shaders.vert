#version 330 core
layout (location = 0)  in vec3 aPos;
layout (location = 1)  in vec3 aColor;
layout (location = 2)  in vec2 aTextCoord;
out vec4 vertexColor;
out vec2 TextCoord;
uniform mat4 RotationMatrix;
void main(){
    gl_Position = RotationMatrix * vec4(aPos.x, -aPos.y, aPos.z, 1.0f);
    vertexColor = vec4(aColor, 1.0f);
    TextCoord = vec2(aTextCoord.x, aTextCoord.y);
}