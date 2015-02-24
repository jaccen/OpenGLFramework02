#version 400


/* input */
layout (location = 0) in vec3 v_position;			// use
layout (location = 1) in vec3 v_normal;				// use
layout (location = 2) in vec2 v_textureCoord;		// use
layout (location = 3) in vec4 v_color;				// unuse 
layout (location = 4) in vec4 v_tangent;			// use
layout (location = 5) in ivec4 v_boneIndex;			// unuse
layout (location = 6) in vec4 v_boneWeight;			// unuse 


/* output */
out vec3 f_eyeDirection;
out vec3 f_lightDirection;
out float f_lightDistance;
out vec2 f_textureCoord;


/* subroutine */
subroutine mat4 CameraFunction();


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


/* uniform variable */
uniform mat4 u_modelMatrix;
uniform vec3 u_eyePosition;
uniform PointLight u_light;
subroutine uniform CameraFunction u_cameraFunction;


/* uniform block */
layout (std140) 
uniform MainCamera
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
} u_mainCameraData;


layout (std140)
uniform BackgroundCamera
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
} u_backgroundCameraData;


// Get main camera's view projection matrix.
subroutine (CameraFunction)
mat4 GetMainViewProjectionMatrix()
{
	return u_mainCameraData.viewProjectionMatrix;
}

// Get background camera's view projection matrix.
subroutine (CameraFunction)
mat4 GetBackgroundViewProjectionMatrix()
{
	return u_backgroundCameraData.viewProjectionMatrix;
}


/* main function */
void main()
{
	// Create tangent space matrix.
	vec3 normal = normalize(mat3(u_modelMatrix) * v_normal);
	vec3 tangent = normalize(mat3(u_modelMatrix) * v_tangent.xyz);
	vec3 binormal = normalize(cross(normal, tangent)) * v_tangent.w;
	
	mat3 tangentSpaceMatrix = mat3(tangent.x, binormal.x, normal.x,
								   tangent.y, binormal.y, normal.y,
								   tangent.z, binormal.z, normal.z);

	// Calculate eye direction and light direction.
	vec3 position = vec3(u_modelMatrix * vec4(v_position, 1.0));
	
	f_eyeDirection = normalize(tangentSpaceMatrix * (u_eyePosition - position));
	f_lightDirection = normalize(tangentSpaceMatrix * (u_light.position - position));
	f_lightDistance = length(u_light.position - position);

	// Set texture coord.
	f_textureCoord = v_textureCoord;

	// Set vertex position.
	mat4 mvp = u_cameraFunction() * u_modelMatrix;
	gl_Position = mvp * vec4(v_position, 1.0);
}
