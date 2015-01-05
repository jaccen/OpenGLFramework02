#version 400


/* input */
in vec3 f_position;
in vec3 f_normal;


/* output */
layout (location = 0) out vec4 fragmentColor;


/* struct */
struct Material
{
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;			// position is world space
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};


/* uniform value */
uniform	Material material;
uniform Light light;


/* main function */
void main()
{
	vec3 lightDirection = normalize(light.position - f_position);
	
	// calculate half lambert
	float lambert = max(dot(lightDirection, f_normal), 0.0);
	float halfLambert = lambert * 0.5  + 0.5;
	halfLambert = halfLambert * halfLambert;
	
	vec3 diffuseColor = material.diffuse * halfLambert * light.diffuse;
	vec3 ambientColor = material.ambient * light.ambient;
	
	vec3 specularColor = vec3(0.0);
	
	if (lambert > 0.0)
	{
		vec3 reflectionLightDirection = reflect(-lightDirection, f_normal);
		vec3 specularColor = light.specular * material.specular * pow(max(dot(reflectionLightDirection, -f_position), 0.0), material.shininess);
	}
	
	vec3 color = diffuseColor + ambientColor + specularColor;
	
	fragmentColor = vec4(color, 1.0);
}
