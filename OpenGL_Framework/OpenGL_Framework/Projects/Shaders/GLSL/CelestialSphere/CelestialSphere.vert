#version 400


/* input */
layout (location = 0) in vec3 v_position;			// use
layout (location = 1) in vec3 v_normal;				// unuse
layout (location = 2) in vec2 v_textureCoord;		// use
layout (location = 3) in vec4 v_color;				// unuse 
layout (location = 4) in vec4 v_tangent;			// unuse 
layout (location = 5) in ivec4 v_boneIndex;			// unuse 
layout (location = 6) in vec4 v_boneWeight;			// unuse 


/* output */
out vec2 f_textureCoord;


/* uniform variable */
uniform mat4 u_modelMatrix;


/* uniform block */
layout (std140) uniform BackgroundCameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 viewProjectionMatrix;
} backgroundCamera;


/* main function */
void main()
{
	f_textureCoord = v_textureCoord;

	// set vertex position
	mat4 mvp = backgroundCamera.viewProjectionMatrix * u_modelMatrix;
	gl_Position = mvp * vec4(v_position, 1.0);
}
