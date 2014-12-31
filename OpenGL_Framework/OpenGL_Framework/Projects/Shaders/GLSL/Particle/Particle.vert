#version 400


/* 入力 */
layout (location = 0) in vec3 vertexPosition;			// 頂点座標
layout (location = 1) in float angle;					// 角度
layout (location = 2) in float width;					// 幅
layout (location = 3) in float height;					// 高さ
layout (location = 4) in vec4 color;					// 色


/* 出力 */
out float v_angle;										// 角度
out float v_width;										// 幅
out float v_height;										// 高さ
out vec4 v_color;										// 色


/* メイン関数 */
void main()
{
	// すべての値をそのままジオメトリシェーダーへ送る
	gl_Position = vec4(vertexPosition, 1.0);
	v_angle = angle;
	v_width = width;
	v_height = height;
	v_color = color;
}
