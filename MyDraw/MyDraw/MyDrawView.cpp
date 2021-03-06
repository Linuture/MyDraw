

// MyDrawView.cpp: CMyDrawView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyDraw.h"
#endif

#include "MyDrawDoc.h"
#include "MyDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDrawView

IMPLEMENT_DYNCREATE(CMyDrawView, CView)

BEGIN_MESSAGE_MAP(CMyDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN ( )
	ON_WM_LBUTTONUP ( )
	ON_WM_MOUSEMOVE ( )
	ON_COMMAND (ID_DRAW_LINE, &CMyDrawView::OnDrawLine)
	ON_COMMAND (ID_DRAW_RECT, &CMyDrawView::OnDrawRect)
	ON_COMMAND (ID_DRAW_ELLIPSE, &CMyDrawView::OnDrawEllipse)
END_MESSAGE_MAP()

// CMyDrawView 构造/析构

CMyDrawView::CMyDrawView()
{
	// TODO: 在此处添加构造代码
	m_myTool = new MyTool ( );
}

CMyDrawView::~CMyDrawView()
{
	delete m_myTool;
}

BOOL CMyDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyDrawView 绘图

void CMyDrawView::OnDraw(CDC* /*pDC*/)
{
	CMyDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyDrawView 打印

BOOL CMyDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyDrawView 诊断

#ifdef _DEBUG
void CMyDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDrawDoc* CMyDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDrawDoc)));
	return (CMyDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyDrawView 消息处理程序


void CMyDrawView::OnLButtonDown (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_myTool->m_ProcMouse (WM_LBUTTONDOWN, point, nFlags);

	return CView::OnLButtonDown (nFlags, point);
}


void CMyDrawView::OnLButtonUp (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_myTool->m_ProcMouse (WM_LBUTTONUP, point, nFlags);

	return CView::OnLButtonUp (nFlags, point);
}


void CMyDrawView::OnMouseMove (UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_myTool->m_ProcMouse (WM_MOUSEMOVE, point, nFlags);

	return CView::OnMouseMove (nFlags, point);
}


void CMyDrawView::OnDrawLine ( )
{
	// TODO: 在此添加命令处理程序代码
	m_myTool->m_SetType (Type_draw_Line);
}


void CMyDrawView::OnDrawRect ( )
{
	// TODO: 在此添加命令处理程序代码
	m_myTool->m_SetType (Type_draw_Rect);
}


void CMyDrawView::OnDrawEllipse ( )
{
	// TODO: 在此添加命令处理程序代码
	m_myTool->m_SetType (Type_draw_Ellipse);
}
