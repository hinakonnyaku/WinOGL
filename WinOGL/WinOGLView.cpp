
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

	//三角形描画　（第１回）
	//glColor3f(1.0, 1.0, 1.0); // 色を設定
	//glBegin(GL_LINE_STRIP); // 描画の開始
	//glVertex2f(-1.0, 0.5); // 1点目の座標
	//glVertex2f(0.0, -0.5); // 2点目の座標
	//glVertex2f(1.0, 0.5); // 3点目の座標
	//glVertex2f(-1.0, 0.5); // 4点目の座標(始点に戻る)
	//glEnd(); // 描画の終了

	//左クリックした座標を表示
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x_Ldown, y_Ldown);
	glEnd();


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
		ratio = (double)w /h ;
		x_Ldown *= ratio;
	}
	else {
		ratio = (double)h / w;
		y_Ldown *= ratio;
	}


	RedrawWindow(); //更新するやつ

	CView::OnLButtonDown(nFlags, point);
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
