#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 vertex_Pos;

void main()
{
    FragColor = vec4(vertex_Pos, 1.0);
}
