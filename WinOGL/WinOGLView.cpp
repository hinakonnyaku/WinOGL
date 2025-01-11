
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_SIZEUP, &CWinOGLView::OnSizeup)
	ON_COMMAND(ID_AXIS, &CWinOGLView::OnAxis)
	ON_UPDATE_COMMAND_UI(ID_AXIS, &CWinOGLView::OnUpdateAxis)
	ON_COMMAND(ID_SIZEDOWN, &CWinOGLView::OnSizedown)
	ON_COMMAND(ID_EDIT_LINE, &CWinOGLView::OnEditLine)
	ON_COMMAND(ID_EDIT_SHAPE, &CWinOGLView::OnEditShape)
	ON_COMMAND(ID_EDIT_VERTEX, &CWinOGLView::OnEditVertex)
	ON_COMMAND(ID_ADD_VERTEX, &CWinOGLView::OnAddVertex)
	ON_UPDATE_COMMAND_UI(ID_ADD_VERTEX, &CWinOGLView::OnUpdateAddVertex)
	ON_UPDATE_COMMAND_UI(ID_EDIT_VERTEX, &CWinOGLView::OnUpdateEditVertex)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LINE, &CWinOGLView::OnUpdateEditLine)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SHAPE, &CWinOGLView::OnUpdateEditShape)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MOVE_VERETEX, &CWinOGLView::OnMoveVeretex)
	ON_UPDATE_COMMAND_UI(ID_MOVE_VERETEX, &CWinOGLView::OnUpdateMoveVeretex)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_DELETE_VERTEX, &CWinOGLView::OnUpdateDeleteVertex)
	ON_COMMAND(ID_DELETE_VERTEX, &CWinOGLView::OnDeleteVertex)
	ON_COMMAND(ID_MOVE_SHAPE, &CWinOGLView::OnMoveShape)
	ON_UPDATE_COMMAND_UI(ID_MOVE_SHAPE, &CWinOGLView::OnUpdateMoveShape)
	ON_COMMAND(ID_SCALE_SHAPE, &CWinOGLView::OnScaleShape)
	ON_UPDATE_COMMAND_UI(ID_SCALE_SHAPE, &CWinOGLView::OnUpdateScaleShape)
	ON_COMMAND(ID_MOVE_SHAPE, &CWinOGLView::OnMoveShape)
	ON_UPDATE_COMMAND_UI(ID_MOVE_SHAPE, &CWinOGLView::OnUpdateMoveShape)
	ON_COMMAND(ID_ROTATE_SHAPE, &CWinOGLView::OnRotateShape)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_SHAPE, &CWinOGLView::OnUpdateRotateShape)
	ON_COMMAND(ID_DRAW_SURFACE, &CWinOGLView::OnDrawSurface)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SURFACE, &CWinOGLView::OnUpdateDrawSurface)
	ON_COMMAND(ID_VIEW_TRANSLATE, &CWinOGLView::OnViewTranslate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRANSLATE, &CWinOGLView::OnUpdateViewTranslate)
	ON_COMMAND(ID_SCALE_SCREEN, &CWinOGLView::OnScaleScreen)
	ON_UPDATE_COMMAND_UI(ID_SCALE_SCREEN, &CWinOGLView::OnUpdateScaleScreen)
	ON_COMMAND(ID_ROTATE_X_AXIS, &CWinOGLView::OnRotateXAxis)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_X_AXIS, &CWinOGLView::OnUpdateRotateXAxis)
	ON_COMMAND(ID_ROTATE_Y_AXIS, &CWinOGLView::OnRotateYAxis)
	ON_UPDATE_COMMAND_UI(ID_ROTATE_Y_AXIS, &CWinOGLView::OnUpdateRotateYAxis)
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	// TODO: 構築コードをここに追加します。
	x_Ldown = 0.0;
	y_Ldown = 0.0;

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT*/);

	// 視点変更
	if (AC.GetChangeModeFlag()) {
		glLoadIdentity(); // 視点を初期化
		AC.SetChangeModeFlag(false);
	}
	switch (AC.GetModeNum())
	{
	case ModeViewTranslate:	// 視点の拡大縮小
		if (AC.LDownFlag) {
			glLoadIdentity(); // 視点を初期化
			AC.ViewTranslation(x_Mouse, y_Mouse);
		}
		break;
	case ModeScaleScreen: // 視点の拡大縮小
		if (AC.LDownFlag) {
			glLoadIdentity(); // 視点を初期化
			AC.ScaleScreen(x_Mouse, y_Mouse);
		}
		break;
	case ModeRotateScreenXaxis: // x軸回転
		if (AC.LDownFlag) {
			glLoadIdentity(); // 視点を初期化
			AC.RotateScreenXaxis(x_Mouse, y_Mouse);
		}
		break;
	case ModeRotateScreenYaxis:
		if (AC.LDownFlag) {
			glLoadIdentity(); // 視点を初期化
			AC.RotateScreenYaxis(x_Mouse, y_Mouse);
		}
		break;
	default:
		break;
	}


	//Draw関数を呼び出す処理
	AC.Draw(x_Mouse, y_Mouse);


	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー


void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	// デバイス座標系 -> 正規化座標系
	x_Ldown = (double)point.x / w; // 区間[0,1]に正規化
	y_Ldown = (double)(h - point.y) / h; // 区間[0,1]に正規化, y座標の反転

	// 正規化座標系 -> ワールド座標系
	x_Ldown = x_Ldown * 2.0 - 1.0;
	y_Ldown = y_Ldown * 2.0 - 1.0;

	// 比率合わせた
	double ratio = 0.0;

	if (w > h) {
		ratio = (double)w / h;
		x_Ldown *= ratio;
	}
	else {
		ratio = (double)h / w;
		y_Ldown *= ratio;
	}


	switch (AC.GetModeNum())
	{
	case ModeAddVertex:
		AC.CreateShape(x_Ldown, y_Ldown);
		break;
	case ModeEditVertex:
	case ModeEditLine:
	case ModeEditShape:
		AC.Select(x_Ldown, y_Ldown);
		break;
	case ModeMoveVertex:
		AC.KeepVertex(); // モード変わった時に今選択している点を保存する
		AC.LDownFlag = true;
		break;
	case ModeDeleteVertex:
		AC.DeleteVertex(x_Ldown, y_Ldown);
		break;
	case ModeMoveShape:
		AC.KeepShape(); // モード変わった時に今選択している形状保存
		AC.KeepLDown(x_Ldown, y_Ldown);// モード変わった時左クリックをおした点を保存する
		AC.LDownFlag = true;
		break;
	case ModeScaleShape:
		AC.KeepShape(); // モード変わった時に今選択している形状保存
		AC.KeepLDown(x_Ldown, y_Ldown);// モード変わった時左クリックをおした点を保存する
		AC.LDownFlag = true;
		break;
	case ModeRotateShape:
		AC.KeepShape(); // モード変わった時に今選択している形状保存
		AC.KeepLDown(x_Ldown, y_Ldown);// モード変わった時左クリックをおした点を保存する
		AC.LDownFlag = true;
		break;
	case ModeViewTranslate:
		AC.KeepLDown(x_Ldown, y_Ldown);
		AC.LDownFlag = true;
		break;
	case ModeScaleScreen:
		AC.KeepLDown(x_Ldown, y_Ldown);
		AC.LDownFlag = true;
	case ModeRotateScreenXaxis:
		AC.KeepLDown(x_Ldown, y_Ldown);
		AC.LDownFlag = true;
	case ModeRotateScreenYaxis:
		AC.KeepLDown(x_Ldown, y_Ldown);
		AC.LDownFlag = true;

	default:
		break;
	}


	RedrawWindow(); //更新するやつ

	CView::OnLButtonDown(nFlags, point);
}

void CWinOGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	// デバイス座標系 -> 正規化座標系
	x_Rdown = (double)point.x / w; // 区間[0,1]に正規化
	y_Rdown = (double)(h - point.y) / h; // 区間[0,1]に正規化, y座標の反転

	// 正規化座標系 -> ワールド座標系
	x_Rdown = x_Rdown * 2.0 - 1.0;
	y_Rdown = y_Rdown * 2.0 - 1.0;

	// 比率合わせた
	double ratio = 0.0;

	if (w > h) {
		ratio = (double)w / h;
		x_Rdown *= ratio;
	}
	else {
		ratio = (double)h / w;
		y_Rdown *= ratio;
	}

	switch (AC.GetModeNum())
	{
	case ModeEditLine:
		AC.VertexInsertion(x_Rdown, y_Rdown);
		break;
	case ModeScaleShape:
	case ModeRotateShape:
		AC.SetBasePos(x_Rdown, y_Rdown);// モード変わった時右クリックをおした点を保存する

		break;
	default:
		break;
	}

	

	RedrawWindow();

	CView::OnRButtonDown(nFlags, point);
}



int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		24,
		0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC,
		&pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}


void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	wglDeleteContext(m_hRC);
}


BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	//return CView::OnEraseBkgnd(pDC);
	return true;
}


void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 課題1　ウィンドウのサイズ変えても図形の比率変わらんようにした
	double ratio = 0.0;
	if (cx > cy) { // ウィンドウサイズ横長のとき
		ratio = (double)cx / cy;
		glOrtho(-ratio, ratio, -1.0, 1.0, -100.0, 100.0);

	}
	else { // ウィンドウサイズ縦長の時
		ratio = (double)cy / cx;
		glOrtho(-1.0, 1.0, -ratio, ratio, -100.0, 100.0);
	}

	glMatrixMode(GL_MODELVIEW);
	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}


void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

		// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	// デバイス座標系 -> 正規化座標系
	x_Mouse = (double)point.x / w; // 区間[0,1]に正規化
	y_Mouse = (double)(h - point.y) / h; // 区間[0,1]に正規化, y座標の反転

	// 正規化座標系 -> ワールド座標系
	x_Mouse = x_Mouse * 2.0 - 1.0;
	y_Mouse = y_Mouse * 2.0 - 1.0;

	// 比率合わせた
	double ratio = 0.0;

	if (w > h) {
		ratio = (double)w / h;
		x_Mouse *= ratio;
	}
	else {
		ratio = (double)h / w;
		y_Mouse *= ratio;
	}

	// 点を動かす
	if (AC.GetModeNum() == ModeMoveVertex && AC.LDownFlag) {
		AC.MoveVertex(x_Mouse, y_Mouse);
	}

	// 形状を動かす
	if (AC.GetModeNum() == ModeMoveShape && AC.LDownFlag) {
		AC.MoveShape(x_Mouse, y_Mouse);
	}

	// 形状の拡大縮小
	if (AC.GetModeNum() == ModeScaleShape && AC.LDownFlag) {
		AC.ScaleShape(x_Mouse, y_Mouse);
	}

	// 形状の回転
	if (AC.GetModeNum() == ModeRotateShape && AC.LDownFlag) {
		AC.RotateShape(x_Mouse, y_Mouse);
	}

	RedrawWindow(); //更新するやつ



	CView::OnMouseMove(nFlags, point);
}


void CWinOGLView::OnSizeup()
{
	AC.DrawSizeUp();
	RedrawWindow();
}

void CWinOGLView::OnSizedown()
{
	AC.DrawSizeDown();
	RedrawWindow();
}


void CWinOGLView::OnAxis()
{
	AC.AxisFlag = !AC.AxisFlag;
	RedrawWindow();
}



void CWinOGLView::OnUpdateAxis(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.AxisFlag);
}



void CWinOGLView::OnEditVertex()
{
	AC.ChangeMode(ModeEditVertex);
	RedrawWindow();
}


void CWinOGLView::OnEditLine()
{
	AC.ChangeMode(ModeEditLine);
	RedrawWindow();
}


void CWinOGLView::OnEditShape()
{
	AC.ChangeMode(ModeEditShape);
	RedrawWindow();
}


void CWinOGLView::OnAddVertex()
{
	AC.ChangeMode(ModeAddVertex);
	RedrawWindow();
}


void CWinOGLView::OnUpdateAddVertex(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeAddVertex);
}


void CWinOGLView::OnUpdateEditVertex(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeEditVertex);
}


void CWinOGLView::OnUpdateEditLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeEditLine);
}


void CWinOGLView::OnUpdateEditShape(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeEditShape);
}


// 左クリックはなしたときに行う処理
void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (AC.GetModeNum() == ModeMoveVertex) {
		AC.CheckMovable();
	}
	if (AC.GetModeNum() == ModeMoveShape) {
		AC.CheckMovable();
	}
	if (AC.GetModeNum() == ModeScaleShape) {
		AC.CheckMovable();
	}
	if (AC.GetModeNum() == ModeRotateShape) {
		AC.CheckMovable();
	}
	if (AC.GetModeNum() == ModeViewTranslate) {
		AC.SaveViewPoint();
	}
	if (AC.GetModeNum() == ModeScaleScreen) {
		AC.SaveScreenScaleRate();
	}
	if (AC.GetModeNum() == ModeRotateScreenXaxis) {
		AC.SaveTheta();
	}
	if (AC.GetModeNum() == ModeRotateScreenYaxis) {
		AC.SaveTheta();
	}



	AC.LDownFlag = false;
	RedrawWindow();
}


void CWinOGLView::OnMoveVeretex()
{
	AC.ChangeMode(ModeMoveVertex);
	RedrawWindow();

}


void CWinOGLView::OnUpdateMoveVeretex(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsSelectVertex()); // 点を選択しているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeMoveVertex);
}




void CWinOGLView::OnUpdateDeleteVertex(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsSelectVertex()); // 点を選択しているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeDeleteVertex);
}


void CWinOGLView::OnDeleteVertex()
{
	AC.ChangeMode(ModeDeleteVertex);
	RedrawWindow();
}

void CWinOGLView::OnMoveShape()
{
	AC.ChangeMode(ModeMoveShape);
	RedrawWindow();
}


void CWinOGLView::OnUpdateMoveShape(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsSelectShape()); // 形状を選択しているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeMoveShape);
}



void CWinOGLView::OnScaleShape()
{
	AC.ChangeMode(ModeScaleShape);
	AC.CalcRelativePosition();
	RedrawWindow();
}


void CWinOGLView::OnUpdateScaleShape(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsSelectShape()); // 形状を選択しているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeScaleShape);
}




void CWinOGLView::OnRotateShape()
{
	AC.ChangeMode(ModeRotateShape);
	RedrawWindow();
}


void CWinOGLView::OnUpdateRotateShape(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsSelectShape()); // 形状を選択しているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeRotateShape);
}


void CWinOGLView::OnDrawSurface()
{

	AC.ChangeMode(ModeDrawSurface);
	RedrawWindow();
}


void CWinOGLView::OnUpdateDrawSurface(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(AC.IsAllShapeClosed()); // 全ての形状が閉じているときしかこのモード選択できなくする
	pCmdUI->SetCheck(AC.GetModeNum() == ModeDrawSurface); // ボタン押してるよってやつ

}


void CWinOGLView::OnViewTranslate()
{
	AC.ChangeMode(ModeViewTranslate);
	RedrawWindow();
}


void CWinOGLView::OnUpdateViewTranslate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeViewTranslate); // ボタン押してるよってやつ
}



void CWinOGLView::OnScaleScreen()
{
	AC.ChangeMode(ModeScaleScreen);
	RedrawWindow();
}


void CWinOGLView::OnUpdateScaleScreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeScaleScreen); // ボタン押してるよってやつ
}


void CWinOGLView::OnRotateXAxis()
{
	AC.ChangeMode(ModeRotateScreenXaxis);
	RedrawWindow();
}


void CWinOGLView::OnUpdateRotateXAxis(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeRotateScreenXaxis); // ボタン押してるよってやつ
}


void CWinOGLView::OnRotateYAxis()
{
	AC.ChangeMode(ModeRotateScreenYaxis);
	RedrawWindow();
}


void CWinOGLView::OnUpdateRotateYAxis(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(AC.GetModeNum() == ModeRotateScreenYaxis); // ボタン押してるよってやつ
}
