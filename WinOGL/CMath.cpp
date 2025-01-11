#include "pch.h"
#include "CMath.h"
#include <math.h>
#include <vector>

//2点間の距離計算
double CMath::Distance(CVertex* VertexA, CVertex* VertexB)
{
	double d = sqrt(pow(VertexA->GetX() - VertexB->GetX(), 2) + pow(VertexA->GetY() - VertexB->GetY(), 2));
	return d;
}

// 外積の計算
double CMath::CrossProduct(CVertex a, CVertex b)
{
	double a1 = a.GetX();
	double a2 = a.GetY();
	double b1 = b.GetX();
	double b2 = b.GetY();
	double crossProduct = a1 * b2 - a2 * b1;
	return crossProduct;
}

// 内積の計算
double CMath::OuterProduct(CVertex a, CVertex b)
{
	double a1 = a.GetX();
	double a2 = a.GetY();
	double b1 = b.GetX();
	double b2 = b.GetY();
	double outerProduct = a1 * b1 + a2 * b2;
	return outerProduct;
}


double CMath::LineAngle(CVertex As, CVertex Ae, CVertex Bs, CVertex Be)
{
	CVertex a(Ae.GetX() - As.GetX(), Ae.GetY() - As.GetY());
	CVertex b(Be.GetX() - Bs.GetX(), Be.GetY() - Bs.GetY());

	double cross = CrossProduct(a, b);
	double outer = OuterProduct(a, b);
	double angle = atan2(cross, outer);

	return angle;
}

double CMath::Distance(CVertex* p, CVertex* s, CVertex* e)
{
	double ax = s->GetX();
	double ay = s->GetY();
	double bx = e->GetX();
	double by = e->GetY();
	double px = p->GetX();
	double py = p->GetY();

	// ベクトル
	double abx = bx - ax;
	double aby = by - ay;
	double apx = px - ax;
	double apy = py - ay;

	double t = (apx * abx + apy * aby) / (abx * abx + aby * aby);

	double cx, cy;

	if (t <= 0) {
		cx = ax;
		cy = ay;
	}
	else if (1 <= t) {
		cx = bx;
		cy = by;
	}
	else {
		cx = ax + t * abx;
		cy = ay + t * aby;
	}

	return sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy));

}

//交差しているか
bool CMath::IsCrossLine(CVertex* As, CVertex* Ae, CVertex* Bs, CVertex* Be)
{
	CVertex a(Ae->GetX() - As->GetX(), Ae->GetY() - As->GetY());
	CVertex a1(Bs->GetX() - As->GetX(), Bs->GetY() - As->GetY());
	CVertex a2(Be->GetX() - As->GetX(), Be->GetY() - As->GetY());
	CVertex b(Be->GetX() - Bs->GetX(), Be->GetY() - Bs->GetY());
	CVertex b1(As->GetX() - Bs->GetX(), As->GetY() - Bs->GetY());
	CVertex b2(Ae->GetX() - Bs->GetX(), Ae->GetY() - Bs->GetY());

	double ca1 = CMath::CrossProduct(a, a1);
	double ca2 = CMath::CrossProduct(a, a2);
	double cb1 = CMath::CrossProduct(b, b1);
	double cb2 = CMath::CrossProduct(b, b2);

	return ca1 * ca2 <= 0 && cb1 * cb2 <= 0;

}

void CMath::OnLineVertex(CVertex* p, CVertex* s, CVertex* e,  double& cx, double& cy)
{
	double ax = s->GetX();
	double ay = s->GetY();
	double bx = e->GetX();
	double by = e->GetY();
	double px = p->GetX();
	double py = p->GetY();

	// ベクトル
	double abx = bx - ax;
	double aby = by - ay;
	double apx = px - ax;
	double apy = py - ay;

	double t = (apx * abx + apy * aby) / (abx * abx + aby * aby);

	

	if (t <= 0) {
		cx = 10000;
		cy = 10000;
	}
	else if (1 <= t) {
		cx = 10000;
		cy = 10000;
	}
	else {
		cx = ax + t * abx;
		cy = ay + t * aby;

	}

}

void CMath::Scale(double x, double y, double baseX, double baseY, double scale, double& deltaX, double& deltaY)
{
	// 変換後の座標を計算
	double newX = scale * (x - baseX) + baseX;
	double newY = scale * (y - baseY) + baseY;

	// 変位量を計算
	deltaX = newX - x;
	deltaY = newY - y;
}

void CMath::Rotate(double x, double y, double baseX, double baseY, double theta, double& deltaX, double& deltaY)
{

	// 回転後の座標を計算
	double rotatedX = (x - baseX) * cos(theta) - (y - baseY) * sin(theta) + baseX;
	double rotatedY = (x - baseX) * sin(theta) + (y - baseY) * cos(theta) + baseY;

	// 元の座標からの変位量を計算
	deltaX = rotatedX - x;
	deltaY = rotatedY - y;
}

// 重心を計算
void CMath::CalcCenter(CShape* shape, double& x, double& y)
{
	double sumX = 0.0;
	double sumY = 0.0;
	int cnt = 0;
	for (CVertex* now_v = shape->GetVHead(); now_v != NULL; now_v = now_v->GetNext()) {
		sumX = sumX + now_v->GetX();
		sumY = sumY + now_v->GetY();
		cnt++;
	}
	x = sumX / (double)cnt;
	y = sumY / (double)cnt;
}

// 重心との相対位置を計算
void CMath::CalcRelativePosition(CShape* shape, CVertex* base)
{
	double now_x;
	double now_y;
	double base_x = shape->GetXCenter();
	double base_y = shape->GetYCenter();
	if (base != NULL) {
		base_x = base->GetX();
		base_y = base->GetY();
	}

	for (CVertex* now_v = shape->GetVHead(); now_v != NULL; now_v = now_v->GetNext()) {
		now_x = now_v->GetX();
		now_y = now_v->GetY();
		now_v->SetRelXY(base_x - now_x, base_y - now_y);
	}
}
  


