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
	// 頂点のX座標
	double x;
	// 頂点のY座標
	double y;
	// 重心との相対位置(relativr_position)
	double rel_x;
	double rel_y;
	// 次の頂点リストを指すポインタ
	CVertex* next_vertex;
	// 一個前の点を指すポインタ
	CVertex* pre_vertex;

public:
	// 頂点のXY座標を書き込む
	void SetXY(double new_x, double new_y);
	// 頂点のX座標を読み込む
	double GetX();
	// 頂点のY座標を読み込む
	double GetY();

	// 重心との相対位置の
	// 頂点のXY座標を書き込む
	void SetRelXY(double x, double y);
	// 頂点のX座標を読み込む
	double GetRelX();
	// 頂点のY座標を読み込む
	double GetRelY();


	// 次の頂点リストを指すポインタを書き込む
	void SetNext(CVertex* new_next);
	// 次の頂点リストを指すポインタを読み込む
	CVertex* GetNext();

	// 一個前の頂点リストを指すポインタを書き込む
	void SetPre(CVertex* new_next);
	// 一個前の頂点リストを指すポインタを読み込む
	CVertex* GetPre();

	// リストを解放する
	void FreeVertex();

	// 自分とaの座標が一致するか判定する
	bool operator==(CVertex a);

};

