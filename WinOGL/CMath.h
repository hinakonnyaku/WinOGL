#pragma once
#include "CVertex.h"
#include "CShape.h"

class CMath
{
public:
	//2点間の距離計算
	static double Distance(CVertex* VertexA, CVertex* VertexB);

	//外積計算
	static double CrossProduct(CVertex a, CVertex b);

	// 内積計算
	static double OuterProduct(CVertex a, CVertex b);

	// 2線分の角度求める
	static double LineAngle(CVertex As, CVertex Ae, CVertex Bs,CVertex Be);

	// 点と線分の距離(p = 点，s = 線分の始点，e = 線分の終点)
	static double Distance(CVertex* p, CVertex* s, CVertex* e);

	// 交差しているか
	static bool IsCrossLine(CVertex* Ae, CVertex* As, CVertex* Be, CVertex* Bs);

	// ある点と線分の垂線から線分上の点の座標を求める(p = 点，s = 線分の始点，e = 線分の終点, cx,cyのポインタ渡すので中身を直接書き換える)
	static void OnLineVertex(CVertex* p, CVertex* s, CVertex* e, double& cx, double& cy);

	// 拡大縮小の計算
	static void Scale(double x, double y, double baseX, double baseY, double scale, double& deltaX, double& deltaY);

	// 回転後の座標の変位量
	static void Rotate(double x, double y, double baseX, double baseY, double theta, double& deltaX, double& deltaY);

	// 重心を計算
	static void CalcCenter(CShape* shape, double& x, double& y);

	// 重心との相対位置を計算
	static void CalcRelativePosition(CShape* shape, CVertex* base);
};



