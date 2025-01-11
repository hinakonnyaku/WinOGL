#include "pch.h"
#pragma once
#include <gl/GL.h>
#include "CVertex.h"
#include "CShape.h"

#define ModeAddVertex 0
#define ModeEditVertex 1
#define ModeEditLine 2
#define ModeEditShape 3
#define ModeMoveVertex 4
#define ModeDeleteVertex 5
#define ModeMoveShape 6
#define ModeScaleShape 7
#define ModeRotateShape 8
#define ModeDrawSurface 9
#define ModeViewTranslate 10
#define ModeScaleScreen 11
#define ModeRotateScreenXaxis 12
#define ModeRotateScreenYaxis 13


class CAdminControl
{
public:
	CAdminControl();
	~CAdminControl();

	// �`�󃊃X�g�̃w�b�h
private:
	CShape* shape_head;
	CShape* shape_tail;
	// �I�����Ă���_
	CVertex* selected_vertex;
	// �I�����Ă���_����������`��
	CShape* shape_selected_vertex_belongs;
	// �_��ۑ�����
	CVertex* keep_vertex;
	// �`���ۑ�����
	CShape* keep_shape;
	// �I�����Ă����������������`��
	CShape* shape_selected_line_belongs;
	// �I�����Ă�������̎n�_
	CVertex* selected_line_start;
	// �I�����Ă�������̏I�_
	CVertex* selected_line_end;
	// �I�����Ă���`��
	CShape* selected_shape;
	// �_��ǉ����Ă���`��
	CShape* adding_shape;
	// �x�N�g��
	double vectorX;
	double vectorY;
	// �g��k���E��]�̊�_
	CVertex* base_pos;

	// �E�N���b�N�̓_��ۑ�
	CVertex* keep_RDown;

	//�@���[�h�̏��
	int ModeNum;

	// ���̎��_�̍��W
	double x_view;
	double y_view;
	// ���_��ۑ�
	double x_preview;
	double y_preview;

	// ���̎��_�̊g�嗦
	double screenScaleRate;
	// ���_�̊g�嗦��ۑ�
	double preScreenScaleRate;

	//�@���̎��_�̉�]�̊p�x
	double theta;
	// ���_�̉�]�̊p�x��ۑ�
	double pre_theta;

	// changeMode�����s������true
	bool changeModeFlag;


private:
	// �`��̈���
	HDC d_hdc;
	// �_�̕`��
	void DrawPoint(CVertex* vertex, bool selected);
	// ���̕`��
	void DrawLine(CVertex* start, CVertex* end, bool selected);




	float POINTSIZE = 10.0;
	float LINEWIDTH = 3.0;



public:
	//�`�揈��
	void Draw(double x_Mouse, double y_Mouse);

	//�j���`��
	void DrawDashedLine(double x_Mouse, double y_Mouse);


	// �`�󃊃X�g�Ɍ`���ǉ�����
	void AddShape();
	void CreateShape(double x_Ldown, double y_Ldown);


	// ���������Ă��邩
	bool IsOtherIntersection(CVertex* new_v);

	// �����@�`���1�_�ڂ�ł�(�`��̒��ɓ_��ł̂�h��)
	bool IsContained(CVertex* v);
	// �����@�`������Ɣ��f������(�`��̒��Ɍ`�󂪓���̂�h��)
	bool IsContainedOtherShape();

	// �_�Ɛ��̃T�C�Y�ύX
	// �傫������
	void DrawSizeUp();
	// ����������
	void DrawSizeDown();

	// ���W���\�����
	bool AxisFlag = false;
	// ���W���̕`��
	void DrawAxis();

	//���[�h��ς���֐�
	void ChangeMode(int mode);

	// �I�����邽�߂̊֐�
	void Select(double x_Ldown, double y_Ldown);


	// �_��I��
	void SelectVertex(CVertex* LDown);
	// �_���I������Ă��邩
	bool IsSelectVertex();
	// ����I��
	void SelectLine(CVertex* LDown);
	// �`���I��
	void SelectShape(CVertex* LDown);
	// �`�󂪑I������Ă��邩
	bool IsSelectShape();

	// ModeNum��private�Ȃ̂ő��̂Ƃ��납�猩���悤��ModeNum�Ԃ�
	int GetModeNum();

	// �_���ړ�����֐�
	void MoveVertex(double x_Mouse, double y_Mouse);

	// �_���ړ����Ă����̂����肷��
	bool IsCrossToMoveVertex();

	// �}�E�X�̍��N���b�N�̏��
	bool LDownFlag = false;

	// selected_vertex��ۑ�����
	void KeepVertex();

	// �ړ��ł��邩���`�F�b�N
	void CheckMovable();

	// shape�����̌`������Ă��邩
	bool IsConnotation(CShape* shape);

	// shape�����̌`��ɓ����Ă��邩
	bool IsConnotationed(CShape* shape);

	// �I�����Ă�������ɓ_��}��
	void VertexInsertion(double x_Rdown, double y_Rdown);

	// �I�����Ă���_���폜
	void DeleteVertex(double x_Ldown, double y_Ldown);

	// �_���폜���Ă������̂�����i�������j
	bool IsCrossToDeleteVertex(CVertex* start_v, CVertex* end_v);

	// �`��̓_�����ׂď������Ƃ��C�`����폜
	void DeleteShape(CShape* delete_s);

	// �`����ړ�����
	void MoveShape(double x_Mouse, double y_Mouse);

	// �`����ړ����Ă��������肷��i�������j
	bool IsCrossToMoveShape(CShape* shape);

	// selected_shape��ۑ�����
	void KeepShape();

	// ���N���b�N���������_��ۑ�����
	void KeepLDown(double x_Ldown, double y_Ldown);
	// �E�N���b�N���������_��ۑ�����
	void KeepRDown(double x_Rdown, double y_Rdown);

	// �`��̊g��k��������
	void ScaleShape(double x_Mouse, double y_Mouse);

	// �`��̉�]������
	void RotateShape(double x_Mouse, double y_Mouse);

	// �g��k���E��]�̊�_��ݒ�E�폜����
	void SetBasePos(double x_Rdown, double y_Rdown);
	// ��_��\������
	void DrawBasePos();
	// ��_���폜����
	void DelBasePos();

	// ���Έʒu�������
	void CalcRelativePosition();

	// �S�Ă̌`�󂪕��Ă���̂�
	bool IsAllShapeClosed();

	// ���_�̕��s�ړ�
	void ViewTranslation(double x_Mouse, double y_Mouse);

	// ���̎��_��ۑ�
	void SaveViewPoint();
	// ���_������
	void ViewpointInitialize();

	//�@changeModeFlag�̐ݒ�
	bool GetChangeModeFlag();
	void SetChangeModeFlag(bool changeMode);

	// ���_�̊g��k��
	void ScaleScreen(double x_Mouse, double y_Mouse);

	// ���̊g��k������ۑ�
	void SaveScreenScaleRate();

	// �g��k�����̏�����
	void ScreenScaleRateInitialize();

	// ���_�@x���̉�]
	void RotateScreenXaxis(double x_Mouse, double y_Mouse);
	// ���_�@y���̉�]
	void RotateScreenYaxis(double x_Mouse, double y_Mouse);

	// ���_�̉�]�̊p�x��ۑ�
	void SaveTheta();
	// ���_�̉�]�̊p�x������
	void ThetaInitialize();
};