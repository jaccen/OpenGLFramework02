#version 400


/* input */
in vec3 f_eyeDirection;
in vec3 f_lightDirection;
in float f_lightDistance;
in vec2 f_textureCoord;


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
uniform PointLight u_light;
uniform	PhongMaterial u_material;
uniform float u_gamma;
uniform sampler2D u_texture;
uniform sampler2D u_normalTexture;


/* calculate phong */
vec3 Phong()
{	
	// Get normal with normal texture.
	vec3 normal = texture(u_normalTexture, f_textureCoord).xyz;
	
	// Convert normal's range ( -1.0 ~ 1.0 ).
	normal = normal * 2.0 - 1.0;

	float lambert = max(dot(f_lightDirection, normal), 0.0);
	float halfLambert = lambert * 0.5  + 0.5;
	halfLambert = halfLambert * halfLambert;
	
	vec3 diffuseColor = u_material.diffuse * halfLambert * u_light.diffuse;
	vec3 ambientColor = u_material.ambient * u_light.ambient;
	vec3 specularColor = vec3(0.0);
	
	if (lambert > 0.0)
	{
		vec3 reflectionLightDirection = reflect(-f_lightDirection, normal);
		vec3 specularColor = u_light.specular * u_material.specular * pow(max(dot(reflectionLightDirection, f_eyeDirection), 0.0), u_material.shininess);
	}
	
	float lightAttenuation = 1.0 / (u_light. constantAttenuation
								  + u_light.linearAttenuation * f_lightDistance
								  + u_light.quadraticAttenuation * f_lightDistance * f_lightDistance);
	
	return (diffuseColor + ambientColor + specularColor) * lightAttenuation;
}


/* main function */
void main()
{
	// Calculate color.
	vec3 color = Phong() * texture(u_texture, f_textureCoord).xyz;

	// Gamma correction.
	fragmentColor = vec4(pow(color, vec3(1.0 / u_gamma)), 1.0);
}
