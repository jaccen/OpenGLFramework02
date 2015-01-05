#version 400


// 頂点座標と頂点カラー
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 vertexColor;


// フラグメントシェーダーに送る色
out vec4 color;


// サブルーチン
subroutine void PrimitiveTypeFunction();
subroutine uniform PrimitiveTypeFunction PrimitiveProcess;


uniform mat4 viewProjectionMatrix;		// ビュープロジェクション行列
uniform float pointSize;				// 点のサイズ



// 点特有の処理
subroutine (PrimitiveTypeFunction)
void PointProcess()
{
	gl_PointSize = pointSize;
}


// 線特有の処理
subroutine (PrimitiveTypeFunction)
void LineProcess()
{
}


/* メイン関数 */
void main()
{
	// 点のサイズを設定
	gl_PointSize = pointSize;

	// ビュープロジェクション行列と頂点座標をかけた値を最終的な頂点座標とする
	gl_Position = viewProjectionMatrix * vec4(vertexPosition, 1.0);
	
	// 頂点カラーをそのままコピー
    color = vertexColor;

	// 各プリミティブ特有の処理
	PrimitiveProcess();
}
