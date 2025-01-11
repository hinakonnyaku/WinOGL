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
	// 点リストのヘッド
	CVertex* vertex_head;
	//点リストの最後
	CVertex* vertex_tail;

	// 次のセルを示すポインタ
	CShape* next_shape;
	// 前のセルを示すポインタ
	CShape* pre_shape;

	// 形状が閉じているか
	bool is_close;
	//頂点の数
	int vertex_cnt;
	// 形状の重心のx座標
	double center_x;
	// 形状の重心のy座標
	double center_y;

public:

	// 次の形状リストを指すポインタを書き込む
	void SetNextS(CShape* new_next);
	// 次の形状リストを指すポインタを読み込む
	CShape* GetNextS();

	// 前の形状リストを指すポインタを書き込む
	void SetPreS(CShape* new_pre);
	// 前の形状リストを指すポインタを読み込む
	CShape* GetPreS();

	// リストを解放する
	void FreeShape();

	// 点リストに点を追加する
	void AddVertex(double x_Ldown, double y_Ldown);

	// vertex_headを読み込む
	CVertex* GetVHead();

	// vertex_tailを読み込む
	CVertex* GetVTail();

	//is_closeを書き込む
	void SetIsClose(bool is_close);
	//is_closeを読み込む
	bool GetIsClose();

	// リストの最後のセルを指すポインタを書き込む
	void SetTail(CVertex* current_vertex);
	// リストの最後のセルを指すポインタを読み込む
	CVertex* GetTail();

	// 頂点の数を数える変数を書き込む
	void SetVCnt(int vertex_cnt);
	// 頂点の数を数える変数を読み込む
	int GetVCnt();

	// 重心のx座標を書き込む
	void SetXCenter(int center_x);
	// 重心のx座標を読み込む
	double GetXCenter();
	// 重心のy座標を書き込む
	void SetYCenter(int center_y);
	// 重心のy座標を読み込む
	double GetYCenter();


	// 距離判定
	bool JudgeDistanceToClose(double x_Ldown, double y_Ldown);

	//形状を閉じる
	void CloseShape();

	// 内包判定 自分にvが内包されているか
	bool IsConnotation(CVertex* v);
	// 自交差しているか（頂点追加のとき）
	bool IsSelfIntersection(CVertex* new_v);
	// start-endの辺と自交差を判定する
	bool IsSelfIntersection(CVertex* start, CVertex* end);

	// 点を挿入する
	void VertexInsertion(CVertex* insert_v, CVertex* start_v, CVertex* end_v);

	// 点を削除
	void DeleteVertex(CVertex* delete_v);

	// 自分自身（形状）コピーする
	CShape* Copy();

	// 重心の座標をcenter_x,yにいれる
	void Center();

	// 面の描画
	void DrawSurface();

	// 自分が時計回りに書かれているか
	bool IsClockwise();
};