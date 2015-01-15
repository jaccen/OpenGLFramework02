#version 400


// サブルーチンを定義
subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;


/* 入出力するプリミティブの種類 */
layout (points) in;										// 点( 入力 )
layout (triangle_strip, max_vertices = 4) out;			// 三角形ストリップ( 出力 )


/* 入力 */
in vec2 v_size[];										// サイズ
in float v_angle[];										// 角度
in vec4 v_color[];										// 色
in vec2 v_textureSize[];								// テクスチャのサイズ
in vec2 v_textureUpperLeft[];							// テクスチャの左上座標
in vec2 v_textureLowerRight[];							// テクスチャの右下座標


/* 出力 */
out vec4 g_color;										// 色
out vec2 g_textureCoord;								// テクスチャ座標


/* ユニフォーム変数 */
uniform mat4 billboardMatrix;							// ビルボード行列
uniform mat4 viewProjectionMatrix;						// ビュープロジェクション行列


/* ベクトルを( 原点から )Z軸回転させる */
vec4 RotationVectorAxisZ(vec2 vector, float radian)
{
	vec4 resultVector;

	resultVector.x = vector.x * cos(radian) - vector.y * sin(radian);
	resultVector.y = vector.x * sin(radian) + vector.y * cos(radian);
	resultVector.z = 0.0;
	resultVector.w = 0.0;

	return resultVector;
}


/* 透視投影時の処理 */
subroutine (RenderPassType)
void PerspectiveProcess()
{
	// サイズの半分を求める
	float halfWidth = 0.5 * v_size[0].x;
	float halfHeight = 0.5 * v_size[0].y;
	
	// テクスチャ座標を求める
	vec2 textureCoordUpperLeft = v_textureUpperLeft[0] / v_textureSize[0];
	vec2 textureCoordLowerRight = v_textureLowerRight[0] / v_textureSize[0];

	// 各座標を求める
	vec2 direction = vec2(-halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordUpperLeft.y);
	EmitVertex();
	
	direction = vec2(halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	EmitVertex();

	direction = vec2(-halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	EmitVertex();
	
	direction = vec2(halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordLowerRight.y);
	EmitVertex();
}


/* 正投影時の処理 */
subroutine (RenderPassType)
void OrthographicProcess()
{
	// サイズの半分を求める
	float halfWidth = 0.5 * v_size[0].x;
	float halfHeight = 0.5 * v_size[0].y;

	// テクスチャ座標を求める
	vec2 textureCoordUpperLeft = v_textureUpperLeft[0] / v_textureSize[0];
	vec2 textureCoordLowerRight = v_textureLowerRight[0] / v_textureSize[0];

	vec2 direction = vec2(-halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(-halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = textureCoordUpperLeft;
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(halfWidth, halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = textureCoordLowerRight;
	g_color = v_color[0];
	EmitVertex();
	
	direction = vec2(halfWidth, -halfHeight);
	gl_Position = viewProjectionMatrix * (gl_in[0].gl_Position + RotationVectorAxisZ(direction, v_angle[0]));
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	g_color = v_color[0];
	EmitVertex();
}


/* メイン関数 */
void main()
{
	// カメラに合わせた処理を行う
	RenderPass();
	
	// 処理終了
	EndPrimitive();
}
