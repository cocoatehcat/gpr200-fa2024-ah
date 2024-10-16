#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec2 TexCoord;

//uniform float uTime;
//uniform vec4 uColor = vec4(1.0);

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if (texColor.a < 0.1) {
		discard;
	}
	FragColor = texColor;
	//FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.5);
    //FragColor = Color * (sin(uTime) * 0.5 + 0.5); 
	//This is the hard code: vec4(1.0f, 0.2f, 0.7f, 1.0f);
} 