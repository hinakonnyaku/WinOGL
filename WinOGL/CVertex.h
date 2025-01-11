#include "pch.h"
#pragma once
#include <stdio.h> 


class CVertex
{

public:
	CVertex();
	CVertex(double new_x, double new_y, CVertex* new_next = NULL);
	~CVertex();

private:
	// ���_��X���W
	double x;
	// ���_��Y���W
	double y;
	// �d�S�Ƃ̑��Έʒu(relativr_position)
	double rel_x;
	double rel_y;
	// ���̒��_���X�g���w���|�C���^
	CVertex* next_vertex;
	// ��O�̓_���w���|�C���^
	CVertex* pre_vertex;

public:
	// ���_��XY���W����������
	void SetXY(double new_x, double new_y);
	// ���_��X���W��ǂݍ���
	double GetX();
	// ���_��Y���W��ǂݍ���
	double GetY();

	// �d�S�Ƃ̑��Έʒu��
	// ���_��XY���W����������
	void SetRelXY(double x, double y);
	// ���_��X���W��ǂݍ���
	double GetRelX();
	// ���_��Y���W��ǂݍ���
	double GetRelY();


	// ���̒��_���X�g���w���|�C���^����������
	void SetNext(CVertex* new_next);
	// ���̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetNext();

	// ��O�̒��_���X�g���w���|�C���^����������
	void SetPre(CVertex* new_next);
	// ��O�̒��_���X�g���w���|�C���^��ǂݍ���
	CVertex* GetPre();

	// ���X�g���������
	void FreeVertex();

	// ������a�̍��W����v���邩���肷��
	bool operator==(CVertex a);

};

