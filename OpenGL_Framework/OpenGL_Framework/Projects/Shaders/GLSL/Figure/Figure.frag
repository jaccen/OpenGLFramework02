#version 400


// 頂点カラー
in vec4 color;


// 最終的なフラグメントカラー
layout(location = 0) out vec4 fragColor;


void main()
{
	// 頂点カラーを最終的なフラグメントカラーとする
	fragColor = color;
}