
// WinOGLView.h : CWinOGLView クラスのインターフェイス
//

#pragma once
#include <gl/GL.h>
#include "CAdminControl.h"


class CWinOGLView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLView() noexcept;
	DECLARE_DYNCREATE(CWinOGLView)

// 属性
public:
	CWinOGLDoc* GetDocument() const;

// 操作
public:

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 実装
public:
	virtual ~CWinOGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	HGLRC m_hRC;
	CAdminControl AC;


private:
	double x_Ldown; // 左クリックしたx座標を格納
	double y_Ldown; // 左クリックしたy座標を格納

	double x_Rdown; // 右クリックしたx座標を格納
	double y_Rdown; // 右クリックしたy座標を格納


	double x_Mouse; // マウスがいる座標
	double y_Mouse;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSizeup();
	afx_msg void OnAxis();
	afx_msg void OnUpdateAxis(CCmdUI* pCmdUI);
	afx_msg void OnSizedown();
	afx_msg void OnEditLine();
	afx_msg void OnEditShape();
	afx_msg void OnEditVertex();
	afx_msg void OnAddVertex();
	afx_msg void OnUpdateAddVertex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditVertex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditShape(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMoveVeretex();
	afx_msg void OnUpdateMoveVeretex(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateDeleteVertex(CCmdUI* pCmdUI);
	afx_msg void OnDeleteVertex();
	afx_msg void OnScaleShape();
	afx_msg void OnUpdateScaleShape(CCmdUI* pCmdUI);
	afx_msg void OnMoveShape();
	afx_msg void OnUpdateMoveShape(CCmdUI* pCmdUI);
	afx_msg void OnRotateShape();
	afx_msg void OnUpdateRotateShape(CCmdUI* pCmdUI);
	afx_msg void OnDrawSurface();
	afx_msg void OnUpdateDrawSurface(CCmdUI* pCmdUI);
	afx_msg void OnViewTranslate();
	afx_msg void OnUpdateViewTranslate(CCmdUI* pCmdUI);
	afx_msg void OnScaleScreen();
	afx_msg void OnUpdateScaleScreen(CCmdUI* pCmdUI);
	afx_msg void OnRotateXAxis();
	afx_msg void OnUpdateRotateXAxis(CCmdUI* pCmdUI);
	afx_msg void OnRotateYAxis();
	afx_msg void OnUpdateRotateYAxis(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // WinOGLView.cpp のデバッグ バージョン
inline CWinOGLDoc* CWinOGLView::GetDocument() const
   { return reinterpret_cast<CWinOGLDoc*>(m_pDocument); }
#endif

