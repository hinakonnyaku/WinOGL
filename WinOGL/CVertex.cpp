#include "pch.h"
#include "CVertex.h"

// コンストラクタ
CVertex::CVertex()
{
	x = 0.0;
	y = 0.0;
	rel_x = 0.0;
	rel_y = 0.0;
	next_vertex = NULL;
	pre_vertex = NULL;

}

CVertex::CVertex(double new_x, double new_y, CVertex* new_next)
{
	SetXY(new_x, new_y);
	SetNext(new_next);
}

// デストラクタ
CVertex::~CVertex()
{

}

// 頂点のXY座標を書き込む
void CVertex::SetXY(double new_x, double new_y)
{
	x = new_x;
	y = new_y;
}
// 頂点のX座標を読み込む
double CVertex::GetX()
{
	return x;
}
// 頂点のY座標を読み込む
double CVertex::GetY()
{
	return y;
}

// 重心との相対位置の書き込み，読み込み
void CVertex::SetRelXY(double x, double y)
{
	rel_x = x;
	rel_y = y;
}
double CVertex::GetRelX()
{
	return rel_x;
}
double CVertex::GetRelY()
{
	return rel_y;
}

// 次の頂点リストを指すポインタを書き込む
void CVertex::SetNext(CVertex* new_next)
{
	next_vertex = new_next;
}
// 次の頂点リストを指すポインタを読み込む
CVertex* CVertex::GetNext()
{
	return next_vertex;
}

// 前の頂点リストを指すポインタを書き込む
void CVertex::SetPre(CVertex* new_pre)
{
	pre_vertex = new_pre;

}
// 前の頂点リストを指すポインタを読み込む
CVertex* CVertex::GetPre()
{
	return pre_vertex;
}

// リストを解放する
void CVertex::FreeVertex()
{
	CVertex* nowV = this;
	while (nowV != NULL) {
		CVertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}

// 自分とaの座標が一致するか判定する
bool CVertex::operator==(CVertex a)
{
	return x == a.GetX() && y == a.GetY();
}
