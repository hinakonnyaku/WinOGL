#include "pch.h"
#include "CVertex.h"

// �R���X�g���N�^
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

// �f�X�g���N�^
CVertex::~CVertex()
{

}

// ���_��XY���W����������
void CVertex::SetXY(double new_x, double new_y)
{
	x = new_x;
	y = new_y;
}
// ���_��X���W��ǂݍ���
double CVertex::GetX()
{
	return x;
}
// ���_��Y���W��ǂݍ���
double CVertex::GetY()
{
	return y;
}

// �d�S�Ƃ̑��Έʒu�̏������݁C�ǂݍ���
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

// ���̒��_���X�g���w���|�C���^����������
void CVertex::SetNext(CVertex* new_next)
{
	next_vertex = new_next;
}
// ���̒��_���X�g���w���|�C���^��ǂݍ���
CVertex* CVertex::GetNext()
{
	return next_vertex;
}

// �O�̒��_���X�g���w���|�C���^����������
void CVertex::SetPre(CVertex* new_pre)
{
	pre_vertex = new_pre;

}
// �O�̒��_���X�g���w���|�C���^��ǂݍ���
CVertex* CVertex::GetPre()
{
	return pre_vertex;
}

// ���X�g���������
void CVertex::FreeVertex()
{
	CVertex* nowV = this;
	while (nowV != NULL) {
		CVertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}

// ������a�̍��W����v���邩���肷��
bool CVertex::operator==(CVertex a)
{
	return x == a.GetX() && y == a.GetY();
}
