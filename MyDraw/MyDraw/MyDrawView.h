
// MyDrawView.h: CMyDrawView 类的接口
//

#pragma once
//----------------------------------------
#include "include/my-tool.h"
//----------------------------------------


class CMyDrawView : public CView
{
private:
	MyTool * m_myTool;
	/////////////////////////Above is mine////////////////////////////////
protected: // 仅从序列化创建
	CMyDrawView();
	DECLARE_DYNCREATE(CMyDrawView)

// 特性
public:
	CMyDrawDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
	afx_msg void OnMouseMove (UINT nFlags, CPoint point);
	afx_msg void OnDrawLine ( );
	afx_msg void OnDrawRect ( );
	afx_msg void OnDrawEllipse ( );
};

#ifndef _DEBUG  // MyDrawView.cpp 中的调试版本
inline CMyDrawDoc* CMyDrawView::GetDocument() const
   { return reinterpret_cast<CMyDrawDoc*>(m_pDocument); }
#endif

