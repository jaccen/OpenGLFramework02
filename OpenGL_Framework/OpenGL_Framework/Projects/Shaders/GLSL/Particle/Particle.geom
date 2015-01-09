#version 400


/* 入出力するプリミティブの種類 */
layout (points) in;										// 点( 入力 )
layout (triangle_strip, max_vertices = 4) out;			// 三角形ストリップ( 出力 )


/* 入力 */
in float v_angle[];										// 角度
in float v_width[];										// 幅
in float v_height[];									// 高さ
in vec4 v_color[];										// 色


/* 出力 */
out vec4 g_color;										// 色
out vec2 g_textureCoord;								// テクスチャ座標


/* ユニフォーム変数 */
uniform mat4 billboardMatrix;							// ビルボード行列
uniform mat4 modelMatrix;								// モデル行列
uniform mat4 viewProjectionMatrix;						// ビュープロジェクション行列
uniform vec2 textureCoordUpperLeft;						// テクスチャ座標の左上
uniform vec2 textureCoordLowerRight;					// テクスチャ座標の右下



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


/* メイン関数 */
void main()
{
	// サイズの半分
	float halfWidth = 0.5 * v_width[0];
	float halfHeight = 0.5 * v_height[0];

	// モデルビュープロジェクション行列を求める
	mat4 modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;

	// 各座標を求める
	vec2 direction = vec2(-halfWidth, halfHeight);
	
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = textureCoordUpperLeft;
	EmitVertex();
	
	direction.xy = vec2(-halfWidth, -halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordUpperLeft.x, textureCoordLowerRight.y);
	EmitVertex();

	direction.xy = vec2(halfWidth, halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = vec2(textureCoordLowerRight.x, textureCoordUpperLeft.y);
	EmitVertex();
	
	direction.xy = vec2(halfWidth, -halfHeight);
	gl_Position = modelViewProjectionMatrix * (gl_in[0].gl_Position + (billboardMatrix * RotationVectorAxisZ(direction, v_angle[0])));
	g_color = v_color[0];
	g_textureCoord = textureCoordLowerRight;
	EmitVertex();
	
	// 処理終了
	EndPrimitive();
}
