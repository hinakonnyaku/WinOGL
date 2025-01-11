#include "pch.h"
#pragma once
#include "CVertex.h"

class CShape
{
public:
	CShape();
	CShape(CVertex* vertex_head, CShape* next_shape);
	~CShape();

private:
	// �_���X�g�̃w�b�h
	CVertex* vertex_head;
	//�_���X�g�̍Ō�
	CVertex* vertex_tail;

	// ���̃Z���������|�C���^
	CShape* next_shape;
	// �O�̃Z���������|�C���^
	CShape* pre_shape;

	// �`�󂪕��Ă��邩
	bool is_close;
	//���_�̐�
	int vertex_cnt;
	// �`��̏d�S��x���W
	double center_x;
	// �`��̏d�S��y���W
	double center_y;

public:

	// ���̌`�󃊃X�g���w���|�C���^����������
	void SetNextS(CShape* new_next);
	// ���̌`�󃊃X�g���w���|�C���^��ǂݍ���
	CShape* GetNextS();

	// �O�̌`�󃊃X�g���w���|�C���^����������
	void SetPreS(CShape* new_pre);
	// �O�̌`�󃊃X�g���w���|�C���^��ǂݍ���
	CShape* GetPreS();

	// ���X�g���������
	void FreeShape();

	// �_���X�g�ɓ_��ǉ�����
	void AddVertex(double x_Ldown, double y_Ldown);

	// vertex_head��ǂݍ���
	CVertex* GetVHead();

	// vertex_tail��ǂݍ���
	CVertex* GetVTail();

	//is_close����������
	void SetIsClose(bool is_close);
	//is_close��ǂݍ���
	bool GetIsClose();

	// ���X�g�̍Ō�̃Z�����w���|�C���^����������
	void SetTail(CVertex* current_vertex);
	// ���X�g�̍Ō�̃Z�����w���|�C���^��ǂݍ���
	CVertex* GetTail();

	// ���_�̐��𐔂���ϐ�����������
	void SetVCnt(int vertex_cnt);
	// ���_�̐��𐔂���ϐ���ǂݍ���
	int GetVCnt();

	// �d�S��x���W����������
	void SetXCenter(int center_x);
	// �d�S��x���W��ǂݍ���
	double GetXCenter();
	// �d�S��y���W����������
	void SetYCenter(int center_y);
	// �d�S��y���W��ǂݍ���
	double GetYCenter();


	// ��������
	bool JudgeDistanceToClose(double x_Ldown, double y_Ldown);

	//�`������
	void CloseShape();

	// ����� ������v�������Ă��邩
	bool IsConnotation(CVertex* v);
	// ���������Ă��邩�i���_�ǉ��̂Ƃ��j
	bool IsSelfIntersection(CVertex* new_v);
	// start-end�̕ӂƎ������𔻒肷��
	bool IsSelfIntersection(CVertex* start, CVertex* end);

	// �_��}������
	void VertexInsertion(CVertex* insert_v, CVertex* start_v, CVertex* end_v);

	// �_���폜
	void DeleteVertex(CVertex* delete_v);

	// �������g�i�`��j�R�s�[����
	CShape* Copy();

	// �d�S�̍��W��center_x,y�ɂ����
	void Center();

	// �ʂ̕`��
	void DrawSurface();

	// ���������v���ɏ�����Ă��邩
	bool IsClockwise();
};