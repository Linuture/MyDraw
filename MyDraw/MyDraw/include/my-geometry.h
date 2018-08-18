#pragma once
#ifndef _MYGEOMETRY_
#define _MYGEOMETRY_

#include "../MyDrawView.h"

struct MyPoint{
	int x;
	int y;

	MyPoint (int X = 0, int Y = 0){
		x = X;
		y = Y;
	}
};

class MyDC
{
public:
	MyDC ( )
	{
		CFrameWnd *pFrame = (CFrameWnd *)AfxGetMainWnd ( );
		m_myView = pFrame->GetActiveView ( );

		m_dc = m_myView->GetDC ( );
	}
	~MyDC ( )
	{
		m_myView->ReleaseDC (m_dc);
	}
public:
	void m_MoveTo (const MyPoint & point){
		m_dc->MoveTo (point.x,point.y);
		return;
	}
	void m_LineTo (const MyPoint & point){
		m_dc->LineTo (point.x, point.y);
		return;
	}
	void m_SetPixel (int x, int y){
		m_dc->SetPixel (x, y, RGB (0, 0, 0));
		return;
	}
public:
	int m_SetContrast ( ){
		return m_dc->SetROP2 (10);
	}

private:
	CView * m_myView;
	CDC * m_dc;
};

class MyGeometry
{
public:
	virtual void m_DrawGeometry ( ) = 0;
	virtual void m_SetStartPoint (const CPoint & point) = 0;
	virtual void m_SetEndPoint (const CPoint & point) = 0;
public:
	void m_NewMyDC ( ){
		m_myDC = new MyDC ( );
	}
	void m_DeleteMyDC ( ){
		delete m_myDC;
	}
	int m_SetContrast ( ){
		return m_myDC->m_SetContrast ( );
	}
protected:
	MyDC * m_myDC;
};

class MyLine: public MyGeometry
{
private:
	MyPoint m_P1;
	MyPoint m_P2;
public:
	MyLine (const CPoint & p1 = CPoint (0, 0),
			const CPoint & p2 = CPoint (0, 0))
	{
		m_P1 = MyPoint (p1.x, p1.y);
		m_P2 = MyPoint (p2.x, p2.y);
	}
	~MyLine ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawLine ( );
	}
	virtual void m_SetStartPoint (const CPoint & point){
		this->m_P1 = MyPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point){
		this->m_P2 = MyPoint (point.x, point.y);
	}
public:
	void m_DrawLine ( )
	{
		MyGeometry::m_myDC
			->m_MoveTo (m_P1);
		MyGeometry::m_myDC
			->m_LineTo (m_P2);
		return;
	}

};

class MyRect : public MyGeometry
{
private:
	MyPoint m_P1;//clockwise
	MyPoint m_P2;
	MyPoint m_P3;
	MyPoint m_P4;
public:
	MyRect (const CPoint & p1 = CPoint (0, 0),
			const CPoint & p3 = CPoint (0, 0))
	{
		m_P1 = MyPoint (p1.x, p1.y);
		m_P3 = MyPoint (p3.x, p3.y);
	}
	~MyRect ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawRect ( );
	}
	virtual void m_SetStartPoint (const CPoint & point){
		this->m_P1 = MyPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point){
		this->m_P3 = MyPoint (point.x, point.y);
	}
public:
	void m_DrawRect ( )
	{
		m_P2 = MyPoint (m_P3.x, m_P1.y);
		m_P4 = MyPoint (m_P1.x, m_P3.y);
		m_myDC->m_MoveTo (m_P1);
		m_myDC->m_LineTo (m_P2);
		m_myDC->m_LineTo (m_P3);
		m_myDC->m_LineTo (m_P4);
		m_myDC->m_LineTo (m_P1);
		return;
	}
};

class MyEllipse : public MyGeometry
{
private:
	MyPoint m_P1;
	MyPoint m_P2;
	short m_radius;
public:
	MyEllipse (const CPoint & p1 = CPoint (0, 0),
			   const CPoint & p2 = CPoint (0, 0))
	{
		m_P1 = MyPoint (p1.x, p1.y);
		m_P2 = MyPoint (p2.x, p2.y);
	}
	~MyEllipse ( )
	{

	}
public:
	virtual void m_DrawGeometry ( )
	{
		return this->m_DrawEllipse ( );
	}
	virtual void m_SetStartPoint (const CPoint & point){
		this->m_P1 = MyPoint (point.x, point.y);
	}
	virtual void m_SetEndPoint (const CPoint & point){
		this->m_P2 = MyPoint (point.x, point.y);
	}
public:
	void m_DrawEllipse ( )
	{
		m_radius = abs(m_P2.x - m_P1.x);

		short plusX = 0 - m_radius;
		short plusY = 0;
		for (; plusY <= m_radius*3/4; plusY += 1)
		{
			short distance = sqrt (
				plusX * plusX +
				plusY * plusY);

			if (distance < m_radius){
				plusX = plusX;
			}
			else{
				plusX += 1;
			}

			m_myDC->m_SetPixel (m_P1.x + plusX, m_P1.y + plusY);
			m_myDC->m_SetPixel (m_P1.x + plusX, m_P1.y - plusY);
			m_myDC->m_SetPixel (m_P1.x - plusX, m_P1.y + plusY);
			m_myDC->m_SetPixel (m_P1.x - plusX, m_P1.y - plusY);
			m_myDC->m_SetPixel (m_P1.x + plusY, m_P1.y + plusX);
			m_myDC->m_SetPixel (m_P1.x - plusY, m_P1.y + plusX);
			m_myDC->m_SetPixel (m_P1.x + plusY, m_P1.y - plusX);
			m_myDC->m_SetPixel (m_P1.x - plusY, m_P1.y - plusX);
			
		}
		return;
	}
};
#endif










