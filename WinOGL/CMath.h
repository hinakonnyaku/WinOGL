#pragma once
#include "CVertex.h"
#include "CShape.h"

class CMath
{
public:
	//2�_�Ԃ̋����v�Z
	static double Distance(CVertex* VertexA, CVertex* VertexB);

	//�O�όv�Z
	static double CrossProduct(CVertex a, CVertex b);

	// ���όv�Z
	static double OuterProduct(CVertex a, CVertex b);

	// 2�����̊p�x���߂�
	static double LineAngle(CVertex As, CVertex Ae, CVertex Bs,CVertex Be);

	// �_�Ɛ����̋���(p = �_�Cs = �����̎n�_�Ce = �����̏I�_)
	static double Distance(CVertex* p, CVertex* s, CVertex* e);

	// �������Ă��邩
	static bool IsCrossLine(CVertex* Ae, CVertex* As, CVertex* Be, CVertex* Bs);

	// ����_�Ɛ����̐������������̓_�̍��W�����߂�(p = �_�Cs = �����̎n�_�Ce = �����̏I�_, cx,cy�̃|�C���^�n���̂Œ��g�𒼐ڏ���������)
	static void OnLineVertex(CVertex* p, CVertex* s, CVertex* e, double& cx, double& cy);

	// �g��k���̌v�Z
	static void Scale(double x, double y, double baseX, double baseY, double scale, double& deltaX, double& deltaY);

	// ��]��̍��W�̕ψʗ�
	static void Rotate(double x, double y, double baseX, double baseY, double theta, double& deltaX, double& deltaY);

	// �d�S���v�Z
	static void CalcCenter(CShape* shape, double& x, double& y);

	// �d�S�Ƃ̑��Έʒu���v�Z
	static void CalcRelativePosition(CShape* shape, CVertex* base);
};



