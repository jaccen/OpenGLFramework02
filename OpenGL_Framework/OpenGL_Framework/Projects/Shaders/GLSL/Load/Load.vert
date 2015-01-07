#version 400


/* 入力 */
layout (location = 0) in vec3 VertexPosition;		// 頂点座標


/* メイン関数 */
void main()
{
	// 頂点座標を設定
	gl_Position = vec4(VertexPosition, 1.0);
}
