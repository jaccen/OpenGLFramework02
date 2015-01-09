#version 400


/* 入力 */
layout (location = 0) in vec3 position;					// 頂点座標
layout (location = 1) in vec2 size;						// サイズ
layout (location = 2) in float angle;					// 角度
layout (location = 3) in vec4 color;					// 色
layout (location = 4) in vec2 textureUpperLeft;			// テクスチャの左上座標
layout (location = 5) in vec2 textureLowerRight;		// テクスチャの右下座標
layout (location = 6) in vec2 textureSize;				// テクスチャのサイズ


/* 出力 */
out vec2 v_size;										// サイズ
out float v_angle;										// 角度
out vec4 v_color;										// 色
out vec2 v_textureUpperLeft;							// テクスチャの左上座標
out vec2 v_textureLowerRight;							// テクスチャの右下座標
out vec2 v_textureSize;									// テクスチャのサイズ


/* メイン関数 */
void main()
{
	gl_Position = vec4(position, 1.0);
	v_size = size;
	v_angle = angle;
	v_color = color;
	v_textureUpperLeft = textureUpperLeft;
	v_textureLowerRight = textureLowerRight;
	v_textureSize = textureSize;
}
