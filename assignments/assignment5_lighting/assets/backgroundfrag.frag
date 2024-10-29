#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec2 TexCoord;
in vec2 UV;

//uniform float uTime;
//uniform vec4 uColor = vec4(1.0);

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord * 9);
	FragColor = texColor;
	

    //FragColor = Color * (sin(uTime) * 0.5 + 0.5); 
	//This is the hard code: vec4(1.0f, 0.2f, 0.7f, 1.0f);
} 