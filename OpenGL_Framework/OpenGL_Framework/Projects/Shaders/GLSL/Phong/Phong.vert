#version 400


/* input */
layout (location = 0) in vec3 v_position;			// use
layout (location = 1) in vec3 v_normal;				// use
layout (location = 2) in vec2 v_textureCoord;		// use
layout (location = 3) in vec4 v_color;				// unused 
layout (location = 4) in vec4 v_tangent;			// unused 
layout (location = 5) in ivec4 v_boneIndex;			// unused 
layout (location = 6) in vec4 v_boneWeight;			// unused 


/* output */
out vec3 f_position;
out vec3 f_normal;


/* subroutine */
subroutine mat4 CameraFunction();


/* uniform variable */
uniform mat4 u_modelMatrix;
subroutine uniform CameraFunction u_cameraFunction;


/* uniform block */
layout (std140) uniform MainCameraData
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
	f_position = vec3(u_modelMatrix * vec4(v_position, 1.0));
	f_normal = normalize(mat3(u_modelMatrix) * v_normal);
	
	mat4 mvp = u_cameraFunction() * u_modelMatrix;
	gl_Position = mvp * vec4(v_position, 1.0);
}
