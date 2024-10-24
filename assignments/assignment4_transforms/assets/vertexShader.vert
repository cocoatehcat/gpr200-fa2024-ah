#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 Color; //Varying
out vec2 TexCoord;
uniform float uTime;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   //Color = aColor; // Pass-through
   TexCoord = aTexCoord;
   vec3 pos = aPos;
   //pos.y += sin(uTime * 4.0 + pos.x) / 4.0;
   gl_Position = proj * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}