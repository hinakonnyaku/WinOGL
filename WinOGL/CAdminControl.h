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

	// 形状リストのヘッド
private:
	CShape* shape_head;
	CShape* shape_tail;
	// 選択している点
	CVertex* selected_vertex;
	// 選択している点が所属する形状
	CShape* shape_selected_vertex_belongs;
	// 点を保存する
	CVertex* keep_vertex;
	// 形状を保存する
	CShape* keep_shape;
	// 選択している線分が所属する形状
	CShape* shape_selected_line_belongs;
	// 選択している線分の始点
	CVertex* selected_line_start;
	// 選択している線分の終点
	CVertex* selected_line_end;
	// 選択している形状
	CShape* selected_shape;
	// 点を追加している形状
	CShape* adding_shape;
	// ベクトル
	double vectorX;
	double vectorY;
	// 拡大縮小・回転の基点
	CVertex* base_pos;

	// 右クリックの点を保存
	CVertex* keep_RDown;

	//　モードの状態
	int ModeNum;

	// 今の視点の座標
	double x_view;
	double y_view;
	// 視点を保存
	double x_preview;
	double y_preview;

	// 今の視点の拡大率
	double screenScaleRate;
	// 視点の拡大率を保存
	double preScreenScaleRate;

	//　今の視点の回転の角度
	double theta;
	// 視点の回転の角度を保存
	double pre_theta;

	// changeModeを実行したらtrue
	bool changeModeFlag;


private:
	// 描画領域情報
	HDC d_hdc;
	// 点の描画
	void DrawPoint(CVertex* vertex, bool selected);
	// 線の描画
	void DrawLine(CVertex* start, CVertex* end, bool selected);




	float POINTSIZE = 10.0;
	float LINEWIDTH = 3.0;



public:
	//描画処理
	void Draw(double x_Mouse, double y_Mouse);

	//破線描画
	void DrawDashedLine(double x_Mouse, double y_Mouse);


	// 形状リストに形状を追加する
	void AddShape();
	void CreateShape(double x_Ldown, double y_Ldown);


	// 他交差しているか
	bool IsOtherIntersection(CVertex* new_v);

	// 内包判定　形状の1点目を打つ時(形状の中に点を打つのを防ぐ)
	bool IsContained(CVertex* v);
	// 内包判定　形状を閉じると判断した時(形状の中に形状が入るのを防ぐ)
	bool IsContainedOtherShape();

	// 点と線のサイズ変更
	// 大きくする
	void DrawSizeUp();
	// 小さくする
	void DrawSizeDown();

	// 座標軸表示状態
	bool AxisFlag = false;
	// 座標軸の描画
	void DrawAxis();

	//モードを変える関数
	void ChangeMode(int mode);

	// 選択するための関数
	void Select(double x_Ldown, double y_Ldown);


	// 点を選択
	void SelectVertex(CVertex* LDown);
	// 点が選択されているか
	bool IsSelectVertex();
	// 線を選択
	void SelectLine(CVertex* LDown);
	// 形状を選択
	void SelectShape(CVertex* LDown);
	// 形状が選択されているか
	bool IsSelectShape();

	// ModeNumがprivateなので他のところから見れるようにModeNum返す
	int GetModeNum();

	// 点を移動する関数
	void MoveVertex(double x_Mouse, double y_Mouse);

	// 点を移動していいのか判定する
	bool IsCrossToMoveVertex();

	// マウスの左クリックの状態
	bool LDownFlag = false;

	// selected_vertexを保存する
	void KeepVertex();

	// 移動できるかをチェック
	void CheckMovable();

	// shapeが他の形状を内包しているか
	bool IsConnotation(CShape* shape);

	// shapeが他の形状に内包されているか
	bool IsConnotationed(CShape* shape);

	// 選択している線分に点を挿入
	void VertexInsertion(double x_Rdown, double y_Rdown);

	// 選択している点を削除
	void DeleteVertex(double x_Ldown, double y_Ldown);

	// 点を削除してもいいのか判定（他交差）
	bool IsCrossToDeleteVertex(CVertex* start_v, CVertex* end_v);

	// 形状の点がすべて消えたとき，形状を削除
	void DeleteShape(CShape* delete_s);

	// 形状を移動する
	void MoveShape(double x_Mouse, double y_Mouse);

	// 形状を移動していいか判定する（他交差）
	bool IsCrossToMoveShape(CShape* shape);

	// selected_shapeを保存する
	void KeepShape();

	// 左クリックをおした点を保存する
	void KeepLDown(double x_Ldown, double y_Ldown);
	// 右クリックを押した点を保存する
	void KeepRDown(double x_Rdown, double y_Rdown);

	// 形状の拡大縮小をする
	void ScaleShape(double x_Mouse, double y_Mouse);

	// 形状の回転をする
	void RotateShape(double x_Mouse, double y_Mouse);

	// 拡大縮小・回転の基点を設定・削除する
	void SetBasePos(double x_Rdown, double y_Rdown);
	// 基点を表示する
	void DrawBasePos();
	// 基点を削除する
	void DelBasePos();

	// 相対位置をいれる
	void CalcRelativePosition();

	// 全ての形状が閉じているのか
	bool IsAllShapeClosed();

	// 視点の平行移動
	void ViewTranslation(double x_Mouse, double y_Mouse);

	// 今の視点を保存
	void SaveViewPoint();
	// 視点初期化
	void ViewpointInitialize();

	//　changeModeFlagの設定
	bool GetChangeModeFlag();
	void SetChangeModeFlag(bool changeMode);

	// 視点の拡大縮小
	void ScaleScreen(double x_Mouse, double y_Mouse);

	// 今の拡大縮小率を保存
	void SaveScreenScaleRate();

	// 拡大縮小率の初期化
	void ScreenScaleRateInitialize();

	// 視点　x軸の回転
	void RotateScreenXaxis(double x_Mouse, double y_Mouse);
	// 視点　y軸の回転
	void RotateScreenYaxis(double x_Mouse, double y_Mouse);

	// 視点の回転の角度を保存
	void SaveTheta();
	// 視点の回転の角度初期化
	void ThetaInitialize();
};