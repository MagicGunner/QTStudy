#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
in vec2 TextCoord;
uniform sampler2D texture0;
uniform sampler2D texture1;
void main() {
    //    FragColor = mix(texture(texture1, TextCoord), texture(texture0, TextCoord), 0.5);
    FragColor = texture(texture1, TextCoord);
}