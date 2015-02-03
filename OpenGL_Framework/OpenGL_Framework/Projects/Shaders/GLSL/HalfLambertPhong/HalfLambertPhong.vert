#version 400


/* input */
layout (location = 0) in vec3 v_position;			// Use
layout (location = 1) in vec3 v_normal;				// Use
layout (location = 2) in vec3 v_textureCoord;		// Unused 
layout (location = 3) in vec3 v_color;				// Unused 
layout (location = 4) in vec3 v_tangent;			// Unused 
layout (location = 5) in ivec4 v_boneIndex;			// Unused 
layout (location = 6) in vec4 v_boneWeight;			// Unused 


/* output */
out vec3 f_position;
out vec3 f_normal;


/* uniform variable */
uniform mat4 modelMatrix;


/* uniform block */
layout (std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
} cameraData;


/* main function */
void main()
{
	f_position = vec3(modelMatrix * vec4(v_position, 1.0));
	f_normal = normalize(mat3(modelMatrix) * v_normal);
	
	mat4 MVP = cameraData.viewProjectionMatrix * modelMatrix;
	gl_Position = MVP * vec4(v_position, 1.0);
}
