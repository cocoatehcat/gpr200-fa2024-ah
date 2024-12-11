#version 330 core
out vec4 FragColor;
in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

//uniform float uTime;
//uniform vec4 uColor = vec4(1.0);

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

// we testing boys
uniform float ambientStrength;
uniform float specularStrength;
uniform int shine;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if (texColor.a < 0.1) {
		discard;
	}

	//float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 reflectDir = reflect(-lightDir, norm);
	// Changed to Blinn-Phong
	vec3 halfDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(norm, halfDir), 0.0), shine);
	vec3 specular = specularStrength * spec * lightColor;

	vec4 result = vec4(ambient + diffuse + specular, 1.0) * texColor;

	FragColor = result;
	//FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.5);
    //FragColor = Color * (sin(uTime) * 0.5 + 0.5); 
	//This is the hard code: vec4(1.0f, 0.2f, 0.7f, 1.0f);
} 