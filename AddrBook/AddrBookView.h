﻿
// AddrBookView.h: CAddrBookView 클래스의 인터페이스
//

#pragma once

#include "CMyFormView.h"

class CAddrBookView : public CView
{
protected: // serialization에서만 만들어집니다.
	CAddrBookView() noexcept;
	DECLARE_DYNCREATE(CAddrBookView)

// 특성입니다.
public:
	CAddrBookDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CAddrBookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	CView* m_FormView;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNewAddr();
	afx_msg void OnSearch();
	virtual void OnInitialUpdate() override;
};

#ifndef _DEBUG  // AddrBookView.cpp의 디버그 버전
inline CAddrBookDoc* CAddrBookView::GetDocument() const
   { return reinterpret_cast<CAddrBookDoc*>(m_pDocument); }
#endif

