#include "pch.h"
#include "CAdminControl.h"
#include "CShape.h"
#include "CMath.h"
#include <vector>


// �R���X�g���N�^
CAdminControl::CAdminControl()
{
	//vertex_head = NULL;
	shape_head = NULL;
	shape_tail = NULL;
	selected_vertex = NULL;
	shape_selected_vertex_belongs = NULL;
	shape_selected_line_belongs = NULL;
	keep_vertex = new CVertex;
	keep_shape = new CShape;
	selected_line_start = NULL;
	selected_line_end = NULL;
	selected_shape = NULL;
	adding_shape = NULL;
	vectorX = 0.0;
	vectorY = 0.0;
	base_pos = NULL;
	keep_RDown = NULL;
	x_view = 0.0;
	y_view = 0.0;
	x_preview = 0.0;
	y_preview = 0.0;
	changeModeFlag = false;
	screenScaleRate = 1.0;
	preScreenScaleRate = 1.0;
	theta = 0.0;
	pre_theta = 0.0;
	ModeNum = ModeAddVertex;
}

// �f�X�g���N�^
CAdminControl::~CAdminControl()
{
	shape_head->FreeShape();
	keep_vertex->FreeVertex();
}

void CAdminControl::Draw(double x_Mouse, double y_Mouse)
{
	// ���W���̕\��
	if (AxisFlag) {
		DrawAxis();
	}

	DrawDashedLine(x_Mouse, y_Mouse);
	DrawBasePos();

	if (shape_head != NULL) {
		/*  �_���X�g�̓��e��`�悷�� */
		// CShape�N���X�̒���vertex_head���Ƃ��Ă���
		
		for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
			if (ModeNum == ModeDrawSurface) {
				now_s->DrawSurface();
			}
			for (CVertex* vp = now_s->GetVHead(); vp != NULL; vp = vp->GetNext()) {
				//IsCrossLine(tail, vp, vp, vp->GetNext());

				bool vp_selected = false;
				bool line_selected = false;
				bool now_s_selected = false;

				CVertex* s = vp;
				CVertex* e;
				if (vp->GetNext() == NULL) {
					e = now_s->GetVHead();
				}
				else {
					e = vp->GetNext();

				}


				if (vp == selected_vertex ){
					vp_selected = true;
				}
				if (s == selected_line_start && e == selected_line_end) {
					line_selected = true;
				}
				if (now_s == selected_shape) {
					now_s_selected = true;
				}

				if (vp->GetNext() != NULL) {
					DrawLine(vp, vp->GetNext(), now_s_selected || line_selected);

				}
				else if (now_s->GetIsClose()) {
					DrawLine(now_s->GetTail(), now_s->GetVHead(), now_s_selected || line_selected);
				}
				
				DrawPoint(vp, vp_selected || now_s_selected);

			}
		}
	}

}

// �_�̕`��
void CAdminControl ::DrawPoint(CVertex* vertex, bool selected)
{
	glColor3f(1.0, 1.0, 1.0);

	// �I�������_�̐F��ς���
	if (selected) { 
		glColor3f(221.0/256, 160.0/256, 221.0/256);

	}

	glPointSize(POINTSIZE);

	glBegin(GL_POINTS);

	glVertex2f(vertex->GetX(), vertex->GetY());

	glEnd();

}

// ���̕`��
void CAdminControl ::DrawLine(CVertex* start, CVertex* end, bool selected)
{
	glDisable(GL_LINE_STIPPLE);
	glEnable(GL_LINE);

	glColor3f(1.0, 1.0, 1.0);

	// �I���������̐F�ς���
	if (selected) {
		glColor3f(221.0 / 256, 160.0 / 256, 221.0 / 256);

	}

	glLineWidth(LINEWIDTH);

	glBegin(GL_LINES);

	glVertex2f(start->GetX(), start->GetY());
	glVertex2f(end->GetX(), end->GetY());


	glEnd();

}


// �\�����i�j���j�`��
void CAdminControl::DrawDashedLine(double x_Mouse, double y_Mouse)
{

	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (!sp->GetIsClose()) {
			adding_shape = sp;
			break;
		}
	}

	// �`�󂪈���Ȃ����@|| �_��ǉ����̌`�󂪂Ȃ��Ƃ� || �_��ǉ����̌`�󂪕��Ă���Ƃ� || �ǉ����[�h����Ȃ��Ƃ�
	// �\������`�悵�Ȃ�
	if (shape_head == NULL || adding_shape == NULL || adding_shape->GetIsClose() || GetModeNum() != ModeAddVertex) {
		return;
	}



	CVertex* tail = adding_shape->GetTail();

	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	glColor3f(1.0, 1.0, 1.0);


	glBegin(GL_LINES);
	glVertex2f(tail->GetX(), tail->GetY());
	glVertex2f(x_Mouse, y_Mouse);

	glEnd();



}

// �`�󃊃X�g�Ɍ`���ǉ�����
void CAdminControl::AddShape()
{
	CShape* New_Shape = NULL;


	if (shape_head == NULL) {
		New_Shape = new CShape;
		shape_head = New_Shape;
		shape_tail = New_Shape;
	}
	else if(shape_tail->GetIsClose()){
		New_Shape = new CShape;
		shape_tail->SetNextS(New_Shape);
		New_Shape->SetPreS(shape_tail);
		shape_tail = New_Shape;
	}


}


// �`��Ƃ��邩���Ȃ��� 
// ���Ȃ����ɒ��_�ǉ�
void CAdminControl::CreateShape(double x_Ldown, double y_Ldown)
{
	CVertex* new_v = new CVertex;
	new_v->SetXY(x_Ldown, y_Ldown);



	if (IsOtherIntersection(new_v)) { // ���������� �������́@�����@�ɂЂ��������Ă��邩
		delete new_v;
		return;
	}
	if(IsContained(new_v)){
		delete new_v;
		return;
	}

	AddShape();
	adding_shape = shape_tail;

	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (!sp->GetIsClose()) {
			adding_shape = sp;
			break;
		}
	}


	if (adding_shape->JudgeDistanceToClose(x_Ldown, y_Ldown)) { 
		if (!adding_shape->IsSelfIntersection(adding_shape->GetVHead()) && !IsContainedOtherShape()) {
			adding_shape->CloseShape();

		}
	}
	else {
		if (!adding_shape->IsSelfIntersection(new_v)) { // ����������
			adding_shape->AddVertex(x_Ldown, y_Ldown);
		}
	}
	delete new_v;

}

// ����������
bool CAdminControl::IsOtherIntersection(CVertex* new_v)
{
	if (shape_head == NULL) {
		return false;
	}
	if (adding_shape->GetIsClose()) { // �`�󂪕��Ă�Ƃ����̓_��head�Ȃ̂ŕӂ��Ȃ�����������Ȃ�
		return false;
	}
	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		if (now_s == adding_shape) {
			continue;
		}
		for (CVertex* vp = now_s->GetVHead(); vp != NULL; vp = vp->GetNext()) {
			CVertex* end_point = vp->GetNext();
			if (end_point == NULL) {
				end_point = now_s->GetVHead();
			}
			if (CMath::IsCrossLine(vp, end_point, adding_shape->GetVTail(), new_v)) {
				return true;
			}
		}
	}
	return false;
}


// �����@�`���1�_�ڂ�ł�(�`��̒��ɓ_��ł̂�h��)
bool CAdminControl::IsContained(CVertex* v)
{
	double pi = 3.141592;
	if (shape_head == NULL ) {
		return false;
	}
	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		if (now_s->GetIsClose() && now_s->IsConnotation(v)) {
			return true;
		}
	}
	return false;
}

// �����@�`������Ɣ��f������(�`��̒��Ɍ`�󂪓���̂�h��)
bool CAdminControl::IsContainedOtherShape()
{
	double pi = 3.141592;
	if (shape_head == NULL) {
		return false;
	}
	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		if (now_s == adding_shape) {
			continue;
		}
		if (adding_shape->IsConnotation(now_s->GetVHead())) {
			return true;
		}
	}
	return false;
}



// �_�Ɛ��̃T�C�Y�ύX
// �傫������
void CAdminControl::DrawSizeUp()
{
	if (LINEWIDTH <= 10.0) {
		POINTSIZE += 0.7;
		LINEWIDTH += 0.4;

	}
}
// ����������
void CAdminControl::DrawSizeDown()
{
	if (LINEWIDTH >= 0.5) {
		POINTSIZE -= 0.7;
		LINEWIDTH -= 0.4;
	}
}

// ���W���̕\��
void CAdminControl::DrawAxis()
{
	glBegin(GL_LINES);
	// x��
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	// y��
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	// z��
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd();
}

void CAdminControl::ChangeMode(int mode)
{
	ModeNum = mode;
	if (mode == ModeAddVertex) { // ���_�ǉ����[�h�ɂȂ�Ƃ��I�u�W�F�N�g�̑I����Ԃ�����
		selected_vertex = NULL;
		shape_selected_vertex_belongs = NULL;
		shape_selected_line_belongs = NULL;
		selected_line_start = NULL;
		selected_line_end = NULL;
		selected_shape = NULL;
		
	}
	DelBasePos();
	ViewpointInitialize();
	ScreenScaleRateInitialize();
	ThetaInitialize();
	changeModeFlag = true;
}


//�I������
void CAdminControl::Select(double x_Ldown, double y_Ldown)
{
	CVertex* LDown = new CVertex(x_Ldown, y_Ldown);

	switch (ModeNum)
	{
	case ModeEditVertex:
		SelectVertex(LDown);
		break;
	case ModeEditLine:
		SelectLine(LDown);
		break;
	case ModeEditShape:
		SelectShape(LDown);
		break;
	default:
		break;
	}
	delete LDown;
}

//�_��I������
void CAdminControl::SelectVertex(CVertex* LDown)
{
	double min = 99999;
	selected_vertex = NULL;
	selected_line_start = NULL;
	selected_line_end = NULL;
	selected_shape = NULL;

	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		for (CVertex* vp = now_s->GetVHead(); vp != NULL; vp = vp->GetNext()) {
			double d = CMath::Distance(vp, LDown);
			if (min > d && d <= 0.05) {
				min = d;
				selected_vertex = vp;
				shape_selected_vertex_belongs = now_s;
			}

		}
	}

}

// �_���I������Ă��邩
bool CAdminControl::IsSelectVertex()
{
	return selected_vertex != NULL;
}


// �ӂ�I������
void CAdminControl::SelectLine(CVertex* LDown)
{
	double min = 99999;
	selected_vertex = NULL;
	selected_line_start = NULL;
	selected_line_end = NULL;
	selected_shape = NULL;

	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		for (CVertex* vp = now_s->GetVHead(); vp != NULL; vp = vp->GetNext()) {

			CVertex* s = vp;
			CVertex* e;
			if (vp->GetNext() == NULL) {
				e = now_s->GetVHead();
			}
			else {
				e = vp->GetNext();

			}
			double d = CMath::Distance(LDown, s, e);
			if (min > d && d <= 0.05) {
				min = d;
				selected_line_start = s;
				selected_line_end = e;
				shape_selected_line_belongs = now_s;
			}

			


		}
	}
}


// �`���I������
void CAdminControl::SelectShape(CVertex* LDown)
{
	selected_vertex = NULL;
	selected_line_start = NULL;
	selected_line_end = NULL;
	selected_shape = NULL;

	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		if (now_s->IsConnotation(LDown)) {
			selected_shape = now_s;
		}
	}


}

// �`�󂪑I������Ă��邩
bool CAdminControl::IsSelectShape()
{
	return selected_shape != NULL;
}

// ModeNum��private�Ȃ̂ő��̂Ƃ��납�猩���悤��ModeNum�Ԃ�
int CAdminControl::GetModeNum()
{
	return ModeNum;
}

// �_�𓮂���
void CAdminControl::MoveVertex(double x_Mouse, double y_Mouse)
{
	double x;
	double y;
	x = keep_vertex->GetX();
	y = keep_vertex->GetY();



	if (LDownFlag) {
		selected_vertex->SetXY(x_Mouse, y_Mouse); 

	}

	// �d�S���v�Z
	shape_selected_vertex_belongs->Center();
	CMath::CalcRelativePosition(shape_selected_vertex_belongs, base_pos);


}

// �_���ړ�����Ƃ��������Ă��邩
bool CAdminControl::IsCrossToMoveVertex()
{

	int cnt = shape_tail->GetVCnt();
	CVertex* pre = NULL;
	CVertex* next = NULL;

	if (selected_vertex->GetPre() == NULL) { // �I�������_�̑O�̓_��NULL�̂Ƃ�
		pre = shape_selected_vertex_belongs->GetVTail(); // pre�ɑI�������_����������`���tail������
	}
	else {
		pre = selected_vertex->GetPre(); 
	}

	if (selected_vertex->GetNext() == NULL) { //�I�������_�̎���NULL�̂Ƃ�
		next = shape_selected_vertex_belongs->GetVHead(); // next�ɑI�����Ă�_����������`���head������
	}
	else {
		next = selected_vertex->GetNext();
	}


	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		bool intersectionPre = sp->IsSelfIntersection(pre, selected_vertex);
		bool intersectionNext = sp->IsSelfIntersection(selected_vertex, next);
		//if (sp->IsSelfIntersection(pre, selected_vertex) || sp->IsSelfIntersection(selected_vertex, next)) {
		if (intersectionPre || intersectionNext) {
			return true;
		}
	}
	return false;


}

// �I�������_setected_vertex��ۑ�����
void CAdminControl::KeepVertex()
{
	double x;
	double y;
	x = selected_vertex->GetX();
	y = selected_vertex->GetY();

	keep_vertex->SetXY(x, y);

}


// �ړ����Ă��������`�F�b�N
void CAdminControl::CheckMovable()
{
	if (GetModeNum() == ModeMoveVertex) {
		if (IsCrossToMoveVertex() || IsConnotation(shape_selected_vertex_belongs)) {
			double x;
			double y;

			x = keep_vertex->GetX();
			y = keep_vertex->GetY();
			selected_vertex->SetXY(x, y);

		}
	}
	if (GetModeNum() == ModeMoveShape || GetModeNum() == ModeScaleShape || GetModeNum() == ModeRotateShape) {
		if (IsConnotation(selected_shape) || IsConnotationed(selected_shape) || IsCrossToMoveShape(selected_shape)) { // �������킩��Ȃ��I�I|| IsCrossToMoveShape(selected_shape)
			// selected_shape->GetVHead()->FreeVertex(); // ���_���X�g��������
			CVertex* selected_vp = selected_shape->GetVHead();
			for (CVertex* keep_vp = keep_shape->GetVHead(); keep_vp != NULL; keep_vp = keep_vp->GetNext()) {
				double x, y;
				x = keep_vp->GetX();
				y = keep_vp->GetY();
				selected_vp->SetXY(x, y);
				selected_vp = selected_vp->GetNext();
			}
			//delete selected_vp;
		}
	}

}

// shape�����̌`������Ă��邩
bool CAdminControl::IsConnotation(CShape* shape)
{
	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (sp == shape) {
			continue;
		}
		if (shape->IsConnotation(sp->GetVHead())) {
			return true;
		}
	}
	return false;
}

// shape�����̌`��ɓ����Ă��邩
bool CAdminControl::IsConnotationed(CShape* shape)
{
	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (sp == shape) {
			continue;
		}
		if (sp->IsConnotation(shape->GetVHead())) {
			return true;
		}
	}
	return false;
}







// �I�����Ă�������ɓ_��}������
void CAdminControl::VertexInsertion(double x_Rdown, double y_Rdown)
{
	if (selected_line_start == NULL) { // �������I������ĂȂ����Ȃɂ����Ȃ���return
		return;
	}

	CVertex* RDown = new CVertex(x_Rdown, y_Rdown);
	CVertex* insertionV = new CVertex;
	double x, y;

	CMath::OnLineVertex(RDown, selected_line_start, selected_line_end, x, y); // �I�����Ă�������̏�ŉE�N���b�N�������Ă��邩�@�����̊O�̏ꍇx,y=10000
	double d = CMath::Distance(RDown, selected_line_start, selected_line_end);// d = �I�����Ă����������̋���
	if ((x != 10000 && y != 10000) && d < 0.05) {//�����̏�ŉE�N���b�N�����Ă�@���@�������痣�ꂷ���Ă��Ȃ��Ƃ�
		insertionV->SetXY(x, y);
		shape_selected_line_belongs->VertexInsertion(insertionV, selected_line_start, selected_line_end);
		selected_line_start = NULL; // �_�̑}�����I�����������̑I��������
		selected_line_end = NULL;
		shape_selected_line_belongs = NULL;
		
	}

	delete RDown;
}

// �I�����Ă���_���폜����
void CAdminControl::DeleteVertex(double x_Ldown, double y_Ldown)
{
	CVertex* LDown = new CVertex(x_Ldown, y_Ldown);

	double d = CMath::Distance(LDown, selected_vertex);// d = ���N���b�N�������W�ƑI�����Ă���_�̋���


	if (d > 0.05) {
		delete LDown;
		return;
	}

	CShape* after_delete_vertex = shape_selected_vertex_belongs->Copy();

	CVertex* a_sel_v = NULL; // after_delete_vertex�i�`��j�̒���selected_vertex�Ɠ������W�̓_�����邽�߂̕ϐ�
	CVertex* pre_aselv = NULL;
	CVertex* next_aselv = NULL;
	for (CVertex* vp = after_delete_vertex->GetVHead(); vp != NULL; vp = vp->GetNext()){
		// a_sel_v = after_delete_vertex�i�`��j�̒���selected_vertex�Ɠ������W�̓_
		pre_aselv = vp->GetPre();
		next_aselv = vp->GetNext();
		a_sel_v = vp;
		if (a_sel_v == after_delete_vertex->GetVHead()) {
			pre_aselv = after_delete_vertex->GetVTail();
		}
		if (a_sel_v == after_delete_vertex->GetVTail()) {
			next_aselv = after_delete_vertex->GetVHead();
		}
		if (*a_sel_v == *selected_vertex) {
			break;
		}
	}

	after_delete_vertex->DeleteVertex(a_sel_v);// �R�s�[������̌`�󂩂�_���폜

	if (IsCrossToDeleteVertex(pre_aselv, next_aselv) || IsConnotation(after_delete_vertex) || after_delete_vertex->IsSelfIntersection(pre_aselv, next_aselv)) {// ���������� || ����� || ����������
		delete LDown;
		delete after_delete_vertex;
		return;
	}

	shape_selected_vertex_belongs->DeleteVertex(selected_vertex);
	if (shape_selected_vertex_belongs->GetVCnt() < 3){
		shape_selected_vertex_belongs->SetIsClose(false);
		adding_shape = shape_selected_vertex_belongs;

		if (shape_selected_vertex_belongs->GetVCnt() == 0) {
			DeleteShape(shape_selected_vertex_belongs);
		}

		ChangeMode(ModeAddVertex);
	}
	else {
		ChangeMode(ModeEditVertex);
	}
	delete LDown;
	delete after_delete_vertex;
	selected_vertex = NULL;// �_�̑I����������
	shape_selected_vertex_belongs = NULL; //�I�������_�̌`���������
	return;
}

// �_���폜���Ă������̂�����i�������j
bool CAdminControl::IsCrossToDeleteVertex(CVertex* start_v, CVertex* end_v)
{
	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (sp == shape_selected_vertex_belongs) {
			continue;
		}
		bool intersection = sp->IsSelfIntersection(start_v, end_v);
		if (intersection) {
			return true;
		}
	}


	return false;
}

// �`��폜
void CAdminControl::DeleteShape(CShape* delete_s)
{
	if (delete_s->GetPreS() != NULL) {
		delete_s->GetPreS()->SetNextS(delete_s->GetNextS());
	}
	else {
		shape_head = delete_s->GetNextS();

	}

	if (delete_s->GetNextS() != NULL) {
		delete_s->GetNextS()->SetPreS(delete_s->GetPreS());

	}
	else {
		shape_tail = delete_s->GetPreS();
	}

	delete delete_s;
}


// �`�󓮂���
void CAdminControl::MoveShape(double x_Mouse, double y_Mouse)
{
	
	vectorX = x_Mouse - keep_vertex->GetX();
	vectorY = y_Mouse - keep_vertex->GetY();
	double x = 0.0;
	double y = 0.0;
	if (LDownFlag) {
		for (CVertex* vp = selected_shape->GetVHead(); vp != NULL; vp = vp->GetNext()) {
			x = vp->GetX();
			y = vp->GetY();
			vp->SetXY(x + vectorX, y + vectorY);
		}
	}
	keep_vertex->SetXY(keep_vertex->GetX() + vectorX, keep_vertex->GetY() + vectorY); // �N�_���X�V
}

// �`����ړ����Ă��������肷��i�������j
bool CAdminControl::IsCrossToMoveShape(CShape* shape)
{
	for (CShape* sp = shape_head; sp != NULL; sp = sp->GetNextS()) {
		if (sp == shape) {
			continue;
		}
		for (CVertex* vp = selected_shape->GetVHead(); vp != NULL; vp = vp->GetNext()) {
			CVertex* start = vp;
			CVertex* end = vp->GetNext();
			if (end == NULL) {
				end = selected_shape->GetVHead();
			}
			bool intersection = sp->IsSelfIntersection(start, end);
			if (intersection) {
				return true;
			}
		}
	}
	return false;
}


// selected_shape��ۑ�����
void CAdminControl::KeepShape()
{
	keep_shape = selected_shape->Copy();
	// keep_shape = selected_shape;

}

// ���N���b�N���������_�i�ړ�����Ƃ��̋N�_�ɂȂ�j��ۑ�����
void CAdminControl::KeepLDown(double x_Ldown, double y_Ldown)
{
	keep_vertex->SetXY(x_Ldown, y_Ldown);
}

// �E�N���b�N���������_��ۑ�����
void CAdminControl::KeepRDown(double x_Rdown, double y_Rdown)
{
	if (keep_RDown == NULL) {
		keep_RDown = new CVertex(x_Rdown, y_Rdown);
	}
	else {
		CVertex* new_RDown = new CVertex(x_Rdown, y_Rdown);
		double d = CMath::Distance(keep_RDown, new_RDown);
		if (d <= 0.05) {
			delete keep_RDown;
			keep_RDown = NULL;
		}
		else {
			keep_RDown->SetXY(x_Rdown, y_Rdown);
		}
	}
}

// �`����g��k������
void CAdminControl::ScaleShape(double x_Mouse, double y_Mouse)
{
	double base_x = selected_shape->GetXCenter();
	double base_y = selected_shape->GetYCenter();

	if (base_pos != NULL) {
		base_x = base_pos->GetX();
		base_y = base_pos->GetY();
	}

	CVertex* now_mouse = new CVertex(x_Mouse, y_Mouse);
	CVertex* base = new CVertex(base_x, base_y);

	double scale = 1.0;             // �g��k����
	double d_BasetoNow = CMath::Distance(base, now_mouse); // ��_�ƍ��̃}�E�X����_�̋���
	double d_BasetoKeep = CMath::Distance(base, keep_vertex); // ��_�ƍ��N���b�N�������W�̋���
	scale = d_BasetoNow / d_BasetoKeep; // d_base to keep ���P�Ƃ����Ƃ�d_base to now�̔䗦���v�Z

	if (scale < 0.2) scale = 0.2; // �k����������h�~

	double x = 0.0, y = 0.0;
	CVertex* keep_vp = keep_shape->GetVHead();
	for (CVertex* vp = selected_shape->GetVHead(); vp != NULL; vp = vp->GetNext()) {
		x = keep_vp->GetX();
		y = keep_vp->GetY();

		vp->SetXY(scale * (x - base_x) + base_x, scale * (y - base_y) + base_y); 
		keep_vp = keep_vp->GetNext();
	}




}

// �`��̉�]
void CAdminControl::RotateShape(double x_Mouse, double y_Mouse)
{
	double base_x = selected_shape->GetXCenter();
	double base_y = selected_shape->GetYCenter();
	
	if (base_pos != NULL) {
		base_x = base_pos->GetX();
		base_y = base_pos->GetY();
	}

	double vec_horizon_x; // �d�S�����ʂƐ����ȃx�N�g��
	double vec_horizon_y;
	vec_horizon_x = 1.0;
	vec_horizon_y = base_y;

	double vec_Ldown_x; // �d�S�ƍ��N���b�N���������W�Ƃ̃x�N�g��
	double vec_Ldown_y;
	vec_Ldown_x = keep_vertex->GetX() - base_x;
	vec_Ldown_y = keep_vertex->GetY() - base_y;

	double thetaA = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), *keep_vertex); //  �d�S�����ʂƐ����ȃx�N�g���Əd�S�ƍ��N���b�N���������W�Ƃ̃x�N�g���̊p�x

	double vec_now_x; // �d�S�ƃ}�E�X������W�Ƃ̃x�N�g��
	double vec_now_y;
	vec_now_x = x_Mouse - base_x;
	vec_now_y = y_Mouse - base_y;

	double thetaB = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), CVertex(x_Mouse, y_Mouse));

	double thetaC = thetaB - thetaA; // �p�x�̍�

	CVertex* keep_vp = keep_shape->GetVHead();
	// �e���_����]
	for (CVertex* vp = selected_shape->GetVHead(); vp != NULL; vp = vp->GetNext()) {
		double deltaX = 0.0, deltaY = 0.0;
		CMath::Rotate(keep_vp->GetX(), keep_vp->GetY(), base_x, base_y, thetaC, deltaX, deltaY);
		vp->SetXY(keep_vp->GetX() + deltaX, keep_vp->GetY() + deltaY);
		keep_vp = keep_vp->GetNext();
	}

}

// �g��k���E��]�̊�_��ݒ�E�폜����
void CAdminControl::SetBasePos(double x_Rdown, double y_Rdown)
{
	CVertex* Rdown = new CVertex(x_Rdown, y_Rdown);
	if (base_pos == NULL) {
		base_pos = new CVertex(x_Rdown, y_Rdown);
	}
	else {
		double d = CMath::Distance(base_pos, Rdown);
		if (d <= 0.05) {
			DelBasePos();//��_�폜
			selected_shape->Center();
		}
		else {
			base_pos->SetXY(x_Rdown, y_Rdown);
		}
	}
	delete Rdown;
}

// ��_��`��
void CAdminControl::DrawBasePos()
{
	if (base_pos == NULL) {
		return;
	}

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(POINTSIZE * 2);
	glBegin(GL_POINTS);
	glVertex2f(base_pos->GetX(), base_pos->GetY());
	glEnd();

}

// ��_�폜
void CAdminControl::DelBasePos()
{
	if (base_pos == NULL) {
		return;
	}
	delete base_pos;
	base_pos = NULL;
}

// ���Έʒu�������
void CAdminControl::CalcRelativePosition()
{
	CMath::CalcRelativePosition(selected_shape, base_pos);
}

bool CAdminControl::IsAllShapeClosed()
{
	for (CShape* now_s = shape_head; now_s != NULL; now_s = now_s->GetNextS()) {
		if (!now_s->GetIsClose()) {
			return false;
		}
	}
	return true;
}

// ���_�̕��s�ړ�
void CAdminControl::ViewTranslation(double x_Mouse, double y_Mouse)
{
	double keep_x =keep_vertex->GetX();
	double keep_y = keep_vertex->GetY();
	x_view = x_Mouse - keep_x + x_preview;
	y_view = y_Mouse - keep_y + y_preview;
	glTranslatef(x_view, y_view, 0.0);
}

// ���_�̕ۑ�
void CAdminControl::SaveViewPoint()
{
	x_preview = x_view;
	y_preview = y_view;
}

// ���_�̏�����
void CAdminControl::ViewpointInitialize()
{
	x_view = 0.0;
	y_view = 0.0;
	x_preview = 0.0;
	y_preview = 0.0;
}

// changeModeFlag�̐ݒ�
bool CAdminControl::GetChangeModeFlag()
{
	return changeModeFlag;
}
void CAdminControl::SetChangeModeFlag(bool changeMode)
{
	changeModeFlag = changeMode;
}

// ���_�̊g��k��
void CAdminControl::ScaleScreen(double x_Mouse, double y_Mouse)
{
	CVertex* now_mouse = new CVertex(x_Mouse, y_Mouse);
	CVertex* base = new CVertex(0.0, 0.0);

	double d_BasetoNow = CMath::Distance(base, now_mouse); // ��_�ƍ��̃}�E�X����_�̋���
	double d_BasetoKeep = CMath::Distance(base, keep_vertex); // ��_�ƍ��N���b�N�������W�̋���
	screenScaleRate = (d_BasetoNow / d_BasetoKeep) + preScreenScaleRate - 1; // d_base to keep ���P�Ƃ����Ƃ�d_base to now�̔䗦���v�Z

	if (screenScaleRate < 0.2) screenScaleRate = 0.2; // �k����������h�~

	glScalef(screenScaleRate, screenScaleRate, screenScaleRate);
}

// ���_�̊g��k������ۑ�
void CAdminControl::SaveScreenScaleRate()
{
	preScreenScaleRate = screenScaleRate;
}

// �g��k�����̏�����
void CAdminControl::ScreenScaleRateInitialize()
{
	screenScaleRate = 1.0;
	preScreenScaleRate = 1.0;
}

// ���_�@x���̉�]
void CAdminControl::RotateScreenXaxis(double x_Mouse, double y_Mouse)
{
	double base_x = 0.0;
	double base_y = 0.0;

	double thetaA = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), *keep_vertex); //  �d�S�����ʂƐ����ȃx�N�g���Əd�S�ƍ��N���b�N���������W�Ƃ̃x�N�g���̊p�x


	double thetaB = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), CVertex(x_Mouse, y_Mouse));

	double thetaC = thetaB - thetaA; // �p�x�̍�
	thetaC = thetaC * 20;
	glRotatef(thetaC, 1.0, 0.0, 0.0);
}

// ���_�@y���̉�]
void CAdminControl::RotateScreenYaxis(double x_Mouse, double y_Mouse)
{
	double base_x = 0.0;
	double base_y = 0.0;

	double thetaA = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), *keep_vertex); //  �d�S�����ʂƐ����ȃx�N�g���Əd�S�ƍ��N���b�N���������W�Ƃ̃x�N�g���̊p�x


	double thetaB = CMath::LineAngle(CVertex(base_x, base_y), CVertex(base_x + 1, base_y), CVertex(base_x, base_y), CVertex(x_Mouse, y_Mouse));

	theta = thetaB - thetaA; // �p�x�̍�
	theta = theta * 20 + pre_theta;
	glRotatef(theta, 0.0, 1.0, 0.0);

}

void CAdminControl::SaveTheta()
{
	pre_theta = theta;
}

void CAdminControl::ThetaInitialize()
{
	theta = 0.0;
	pre_theta = 0.0;
}








