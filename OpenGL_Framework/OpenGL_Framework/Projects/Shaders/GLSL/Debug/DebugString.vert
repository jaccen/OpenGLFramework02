#version 400


/* 入力 */
layout (location = 0) in vec3 VertexPosition;		// 頂点座標( 原点を前提 )


/* 定数 */
uniform vec3 Position;                              // 座標


/* メイン関数 */
void main()
{
	// 頂点座標を設定
	gl_Position = vec4((VertexPosition + Position), 1.0);
}
