#include "pch.h"
#include "CShape.h"
#include "CMath.h"
#include <math.h>
#include <gl/GL.h>


// コンストラクタ
CShape::CShape()
{
	vertex_head = NULL;
	next_shape = NULL;
	pre_shape = NULL;
	vertex_tail = NULL;
}


// デストラクタ
CShape::~CShape()
{
	vertex_head->FreeVertex();
}

void CShape::SetNextS(CShape* new_next)
{
	next_shape = new_next;

}

CShape* CShape::GetNextS()
{
	return next_shape;
}

void CShape::SetPreS(CShape* new_pre)
{
	pre_shape = new_pre;
}

CShape* CShape::GetPreS()
{
	return pre_shape;
}

// リストを解放する
void CShape::FreeShape()
{
	CShape* nowV = this;
	while (nowV != NULL) {
		CShape* del_cell = nowV;
		nowV = nowV->GetNextS();
		delete del_cell;
	}
}

// 点追加
void CShape::AddVertex(double x_Ldown, double y_Ldown)
{
	//SetX(float click_x);
	CVertex* New_Vertex = new CVertex;

	New_Vertex->SetXY(x_Ldown, y_Ldown);

	if (vertex_head == NULL) {
		vertex_head = New_Vertex;
		vertex_tail = New_Vertex;
	}
	else {
		//CVertex* vp = vertex_head;
		//for (vp = vertex_head; vp->GetNext() != NULL; vp = vp->GetNext()) {
		//}
		////while(vp->GetNext() != NULL){vp = vp -> GetNext();}
		//vp->SetNext(New_Vertex);
		vertex_tail->SetNext(New_Vertex);
		New_Vertex->SetPre(vertex_tail);
		vertex_tail = New_Vertex;

	}
	vertex_cnt++;
}



CVertex* CShape::GetVHead()
{
	return vertex_head;
}

CVertex* CShape::GetVTail()
{
	return vertex_tail;
}

void CShape::SetIsClose(bool is_close)
{
	this->is_close = is_close;
}

bool CShape::GetIsClose()
{
	return is_close;
}


// リストの最後のセルを指すポインタを書き込む
void CShape::SetTail(CVertex* current_vertex)
{
	vertex_tail = current_vertex;
}
// リストの最後のセルを指すポインタを読み込む
CVertex* CShape::GetTail()
{
	return vertex_tail;
}

// 頂点の数の書き込み読み込み
void CShape::SetVCnt(int vertex_cnt)
{
	this->vertex_cnt = vertex_cnt;
}
int CShape::GetVCnt()
{
	return vertex_cnt;
}

// 重心の読み込み書き込み
void CShape::SetXCenter(int center_x)
{
	this->center_x = center_x;
}
double CShape::GetXCenter()
{
	return center_x;
}
void CShape::SetYCenter(int center_y)
{
	this->center_y = center_y;
}
double CShape::GetYCenter()
{
	return center_y;
}


// 距離判定
bool CShape::JudgeDistanceToClose(double x_Ldown, double y_Ldown)
{
	if (vertex_head == NULL && vertex_cnt <= 3) {
		return false;
	}
	else {
		CVertex* NewVertex = new CVertex(x_Ldown, y_Ldown);
		double d = CMath::Distance(vertex_head, NewVertex);
		delete NewVertex;
		return d <= 0.05;
	}
}


void CShape::CloseShape()
{
	SetIsClose(true);
	// 重心を計算
	Center();
	CMath::CalcRelativePosition(this, NULL);

}

//内包判定　自分にvが内包されているか　内包している->true
bool CShape::IsConnotation(CVertex* v)
{
	double angle = 0.0;
	double pi = 3.141592;

	for (CVertex* vp = vertex_head; vp != NULL; vp = vp->GetNext()) {
		CVertex* Be = vp->GetNext();
		if (Be == NULL) {
			Be = vertex_head;
		}
		angle += CMath::LineAngle(*v, *vp, *v, *Be);
	}
	double sub = 2 * pi - fabs(angle);
	if (-0.01 < sub && sub < 0.01) {
		return true;
	}
	return false;

}

// 自交差しているか（頂点追加のとき）
bool CShape::IsSelfIntersection(CVertex* new_v)
{
	int cnt = vertex_cnt;



	// 最新の形状の頂点数2個以下のとき，交差していないと判定し終了
	if (cnt < 2) {
		return false;
	}


	for (CVertex* vp = vertex_head; vp->GetNext()->GetNext() != NULL; vp = vp->GetNext()) {
		// ポインタの中身の座標が同じか判定
		if (*vp == *new_v) {
			continue;
		}
		if (CMath::IsCrossLine(vp, vp->GetNext(), vertex_tail, new_v)) {
			return true;
		}
	}
	return false;
}


// start-endの辺と自交差を判定する
bool CShape::IsSelfIntersection(CVertex* start, CVertex* end)
{
	if (vertex_cnt < 2) {
		return false;
	}

	for (CVertex* vp = vertex_head; vp->GetNext() != NULL; vp = vp->GetNext()) {

		if (vp->GetNext() == start || vp == start || vp == end) {
			continue;
		}
		if (CMath::IsCrossLine(end, start, vp->GetNext(), vp)) {
			return true; // 交差しているときTrue返す
		}
	}

	if (vertex_head == start || vertex_tail == start || vertex_tail == end) {
		return false;
	}
	if (CMath::IsCrossLine(end, start, vertex_head, vertex_tail)) {
		return true; // 交差しているときTrue返す
	}

	return false;
}


// 点を挿入する
void CShape::VertexInsertion(CVertex* insert_v, CVertex* start_v, CVertex* end_v )
{

	bool IsSelectLastLine = end_v == GetVHead();


	if (IsSelectLastLine == true) {
		insert_v->SetPre(start_v);
		start_v->SetNext(insert_v);
	}
	else {
		insert_v->SetNext(end_v);
		insert_v->SetPre(start_v);
		start_v->SetNext(insert_v);
		end_v->SetPre(insert_v);

	}

	if (IsSelectLastLine == true) {
		SetTail(insert_v);
	}


}

// 点を削除する
void CShape::DeleteVertex(CVertex* delete_v)
{
	if (delete_v->GetPre() != NULL) {
		delete_v->GetPre()->SetNext(delete_v->GetNext());
	}
	else {
		vertex_head = delete_v->GetNext();

	}

	if (delete_v->GetNext() != NULL) {
		delete_v->GetNext()->SetPre(delete_v->GetPre());

	}
	else {
		vertex_tail = delete_v->GetPre();
	}

	vertex_cnt--;
	
	delete delete_v;
}



// 自分自身（形状）コピーする
CShape* CShape::Copy()
{
	CShape* copy_s = new CShape();
	for (CVertex* now_v = vertex_head; now_v != NULL; now_v = now_v->GetNext()) {
		copy_s->AddVertex(now_v->GetX(), now_v->GetY());
	}
	copy_s->CloseShape();
	return copy_s;
}

// 重心の座標をcenter_x,yにいれる
void CShape::Center()
{
	CMath::CalcCenter(this, center_x, center_y);
}

// 面を描画
void CShape::DrawSurface()
{
	CShape* triangle = new CShape; //注目する三角形
	triangle->AddVertex(0, 0);
	triangle->AddVertex(0, 0);
	triangle->AddVertex(0, 0);
	CVertex* tv1 = triangle->GetVHead();
	CVertex* tv2 = tv1->GetNext();
	CVertex* tv3 = tv2->GetNext();
	CShape* copy = Copy(); // 形状コピー
	bool copyIsClockwise = copy->IsClockwise();
	while (copy->GetVCnt() >= 3) {
		for (CVertex* now_v = copy->GetVHead(); now_v != NULL; now_v = now_v->GetNext()) {
			CVertex* nv1 = now_v;
			CVertex* nv2 = nv1->GetNext();
			CVertex* nv3 = nv2->GetNext();

			double center_x;
			double center_y;

			tv1->SetXY(nv1->GetX(), nv1->GetY());
			tv2->SetXY(nv2->GetX(), nv2->GetY());
			tv3->SetXY(nv3->GetX(), nv3->GetY());

			CMath::CalcCenter(triangle, center_x, center_y);
			CVertex* center = new CVertex(center_x, center_y);

			bool noOtherVertex = true;
			for (CVertex* other_v = copy->GetVHead(); other_v != NULL; other_v = other_v->GetNext()) {
				if (*tv1 == *other_v || *tv2 == *other_v || *tv3 == *other_v) {
					continue;
				}
				if (triangle->IsConnotation(other_v)) {
					noOtherVertex = false;
					break;
				}

			}

			if ((copy->IsConnotation(center) || (copyIsClockwise == triangle->IsClockwise())) && noOtherVertex) { // コピーした形状に今見てる三角形の重心が内包されているか

				// 面の描画
				glBegin(GL_POLYGON);
				glVertex2f(nv1->GetX(), nv1->GetY());// 形状の点をglVertex2f()で指定する
				glVertex2f(nv2->GetX(), nv2->GetY());
				glVertex2f(nv3->GetX(), nv3->GetY());
				glEnd();

				copy->DeleteVertex(nv2);
				delete center;
				break;
			}

		}
	}
	delete triangle;
	delete copy;
}

bool CShape::IsClockwise()
{
	CShape* triangle = new CShape; //注目する三角形
	triangle->AddVertex(0, 0);
	triangle->AddVertex(0, 0);
	triangle->AddVertex(0, 0);
	CVertex* tv1 = triangle->GetVHead();
	CVertex* tv2 = tv1->GetNext();
	CVertex* tv3 = tv2->GetNext();

	for (CVertex* now_v = GetVHead(); now_v != NULL; now_v = now_v->GetNext()) {
		CVertex* nv1 = now_v;
		CVertex* nv2 = nv1->GetNext();
		CVertex* nv3 = nv2->GetNext();

		double center_x;
		double center_y;
		double angle = 0.0;

		tv1->SetXY(nv1->GetX(), nv1->GetY());
		tv2->SetXY(nv2->GetX(), nv2->GetY());
		tv3->SetXY(nv3->GetX(), nv3->GetY());

		CMath::CalcCenter(triangle, center_x, center_y);
		CVertex* center = new CVertex(center_x, center_y);

		if(IsConnotation(center)) {
			for (CVertex* vp = vertex_head; vp != NULL; vp = vp->GetNext()) {
				CVertex* Be = vp->GetNext();
				if (Be == NULL) {
					Be = vertex_head;
				}
				
				angle += CMath::LineAngle(*center, *vp, *center, *Be);
			}
			delete center;
			delete triangle;
			return angle > 0;
		}
	}
	delete triangle;

	return false;
}



