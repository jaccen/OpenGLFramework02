#version 400


/* 入力 */
in vec2 gTexCoord;								// テクスチャ座標


/* 出力 */
layout (location = 0) out vec4 FragColor;		// フラグメントカラー


/* 定数 */
uniform sampler2D Texture;			            // テクスチャ


/* メイン関数 */
void main()
{
	// フラグメントカラーを設定
	FragColor = texture(Texture, gTexCoord);
}