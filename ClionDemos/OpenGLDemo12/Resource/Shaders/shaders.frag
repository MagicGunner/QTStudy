#version 330 core
out vec4 FragColor;
in vec2 TextCoord;
uniform float mixValue;
uniform sampler2D texture0;
uniform sampler2D texture1;
void main() {
    FragColor = mix(texture(texture0, TextCoord), texture(texture1, TextCoord), mixValue);
}