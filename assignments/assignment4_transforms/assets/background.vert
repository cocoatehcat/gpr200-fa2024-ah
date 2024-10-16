#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aUV;

out vec3 Color; //Varying
out vec2 TexCoord;
out vec2 UV;
uniform float uTime;
void main()
{
   //gl_Position = vec4(aPos, 1.0);
   UV = aUV;
   Color = aColor; // Pass-through
   TexCoord = aTexCoord;
   vec3 pos = aPos;
   pos.x *= 4.0;
   pos.y *= 4.0;
   pos.y += sin(uTime * 4.0 + pos.x) / 4.0;
   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}