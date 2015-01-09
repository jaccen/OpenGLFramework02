#version 400


/* 入力 */
in vec4 g_color;												// 色
in vec2 g_textureCoord;											// テクスチャ座標


/* 出力 */
layout (location = 0) out vec4 f_fragmentColor;					// フラグメント色


/* ユニフォーム変数 */
uniform sampler2D Texture;										// テクスチャ


/* メイン関数 */
void main()
{
	vec4 textureColor = texture(Texture, g_textureCoord);
	f_fragmentColor = textureColor * g_color;
}