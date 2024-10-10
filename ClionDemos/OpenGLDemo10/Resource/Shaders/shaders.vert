#version 330 core
layout (location = 0)  in vec3 aPos;
layout (location = 1)  in vec2 aTextCoord;
out vec2 TextCoord;
uniform mat4 RotationMatrix;
void main(){
    gl_Position = RotationMatrix * vec4(aPos.x, -aPos.y, aPos.z, 1.0f);
    TextCoord = vec2(aTextCoord.x, aTextCoord.y);
}