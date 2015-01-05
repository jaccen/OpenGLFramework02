#version 400


/* input */
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;


/* output */
out vec3 f_position;
out vec3 f_normal;


/* uniform value */
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
