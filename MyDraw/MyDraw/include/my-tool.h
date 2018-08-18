#pragma once
#ifndef _MYTOOL_
#define _MYTOOL_

#include "stdafx.h"
#include "my-geometry.h"

enum draw_Type
{ Type_draw_Line, Type_draw_Ellipse,Type_draw_Rect, Type_draw_nothing };

class MyTool
{
public:
	MyTool ( )
	{
		this->m_drawType = Type_draw_nothing;
		m_myGeom = nullptr;
		//m_myLine = nullptr;
		//m_myRect = nullptr;
		m_flag = 0;
	}
public:
	bool m_ProcMouse (UINT msg, CPoint point, UINT nFlags);
public:
	void m_SetType (draw_Type drawType)
	{
		this->m_drawType = drawType;
	}
private:
	bool m_IsDrawSomething ()
	{
		return (this->m_drawType != Type_draw_nothing);
	}
	draw_Type m_GetType ( )
	{
		return this->m_drawType;
	}
private:
	void m_InitialDraw (CPoint point);
	void m_ShowDrawing (CPoint point);
	void m_EndDraw (CPoint point);
private:
	void m_NewGeometry (draw_Type type);
	void m_DeleteGeometry ( );
private:
	MyGeometry * m_myGeom;
	short m_flag;
	draw_Type m_drawType;
};

inline bool 
MyTool::m_ProcMouse (UINT msg, CPoint point, UINT nFlags)
{
	bool isDraw = this->m_IsDrawSomething ();

	if (isDraw){
		switch (msg)
		{
		case WM_LBUTTONDOWN:
			this->m_InitialDraw (point);
			return true;
		case WM_LBUTTONUP:
			this->m_EndDraw (point);
			return true;
		case WM_MOUSEMOVE:
			this->m_ShowDrawing (point);
			return true;
		default:
			return true;
		}
	}
	else{
		return false;
	}
}

inline void 
MyTool::m_InitialDraw (CPoint point)
{
	draw_Type type = this->m_GetType ( );
	this->m_NewGeometry (type);

	m_myGeom->m_SetStartPoint (point);
	m_myGeom->m_SetEndPoint (point);

	this->m_flag = 1;

	return;
}

inline void
MyTool::m_ShowDrawing (CPoint point)
{
	if (this->m_flag == 1)
	{
		m_myGeom->m_NewMyDC ( );
		m_myGeom->m_SetContrast ( );

		m_myGeom->m_DrawGeometry ( );
		m_myGeom->m_SetEndPoint (point);
		m_myGeom->m_DrawGeometry ( );

		m_myGeom->m_DeleteMyDC ( );

		return;
	}
	else
	{
		return;
	}
}

inline void
MyTool::m_EndDraw (CPoint point)
{
	if (this->m_flag == 1)
	{
		this->m_flag = 0;

		m_myGeom->m_NewMyDC ( );

		m_myGeom->m_DrawGeometry ( );

		m_myGeom->m_DeleteMyDC ( );

		return (this->m_DeleteGeometry ( ));
	}
	else
	{
		return;
	}
}

inline void
MyTool::m_NewGeometry (draw_Type type)
{
	switch (type)
	{
	case Type_draw_Line:
		this->m_myGeom = new MyLine ( );
		return;
	case Type_draw_Rect:
		this->m_myGeom = new MyRect ( );
		return;
	case Type_draw_Ellipse:
		this->m_myGeom = new MyEllipse ( );
		return;
	default:
		return;
	}
}

inline void
MyTool::m_DeleteGeometry ()
{
	delete this->m_myGeom;
	this->m_myGeom = nullptr;

	return;
}

#endif
