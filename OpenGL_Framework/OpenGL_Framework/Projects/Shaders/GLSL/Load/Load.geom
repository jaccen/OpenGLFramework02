#version 400


/* 入力・出力する図形要素 */
layout (points) in;									// プリミティブの種類
layout (triangle_strip, max_vertices = 4) out;		// プリミティブの種類と頂点の数


/* 出力 */
out vec2 gTexCoord;									// テクスチャ座標


/* 入力定数 */
uniform float Width;								// 幅の半分
uniform float Height;								// 高さの半分
uniform mat4 OrthographicProjectionMatrix ;			// プロジェクション行列


/* 中央揃え */
void Center()
{
    // 幅と高さの半分
    float HalfWidth = Width / 2.0;
    float HalfHeight = Height /2.0;

    gl_Position = OrthographicProjectionMatrix  * (vec4(-HalfWidth, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(HalfWidth, Height, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 1.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(-HalfWidth, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(0.0, 0.0);
	EmitVertex();
	
	gl_Position = OrthographicProjectionMatrix  * (vec4(HalfWidth, 0.0, 0.0, 0.0) + gl_in[0].gl_Position);
	gTexCoord = vec2(1.0, 0.0);
	EmitVertex();
}


/* メイン関数 */
void main()
{
    // 中央揃えで処理を行う
    Center();
	
	EndPrimitive();
}


