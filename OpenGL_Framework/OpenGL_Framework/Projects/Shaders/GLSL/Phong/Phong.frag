#version 400


/* input */
in vec3 f_position;
in vec3 f_normal;


/* output */
layout (location = 0) out vec4 fragmentColor;


/* struct */
struct PointLight
{
	vec3 position;
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};


struct PhongMaterial
{
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess;
};


/* uniform value */
uniform	PhongMaterial u_material;
uniform PointLight u_light;
uniform float u_gamma;


/* calculate phong */
vec3 Phong()
{
	vec3 lightDifference = u_light.position - f_position;
	vec3 lightDirection = normalize(lightDifference);
	float lightDistance = length(lightDifference);

	float lambert = max(dot(lightDirection, f_normal), 0.0);
	float halfLambert = lambert * 0.5  + 0.5;
	halfLambert = halfLambert * halfLambert;
	
	vec3 diffuseColor = u_material.diffuse * halfLambert * u_light.diffuse;
	vec3 ambientColor = u_material.ambient * u_light.ambient;
	
	vec3 specularColor = vec3(0.0);
	
	if (lambert > 0.0)
	{
		vec3 reflectionLightDirection = reflect(-lightDirection, f_normal);
		vec3 specularColor = u_light.specular * u_material.specular * pow(max(dot(reflectionLightDirection, -f_position), 0.0), u_material.shininess);
	}
	
	return diffuseColor + ambientColor + specularColor;
}


/* main function */
void main()
{
	// calculate color
	vec3 color = Phong();

	// gamma correction
	fragmentColor = vec4(pow(color, vec3(1.0 / u_gamma)), 1.0);
}
