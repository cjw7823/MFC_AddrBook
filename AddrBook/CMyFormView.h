#pragma once

class CAddrBookDoc;

// CMyFormView 폼 보기

class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

//protected:
	CMyFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyFormView();

public:
	CAddrBookDoc* GetDocument() const;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	void OnDraw(CDC* pDC) override;
	BOOL Create(LPCTSTR a, LPCTSTR b, DWORD c,
		const RECT& d, CWnd* e, UINT f, CCreateContext* g) override;
	CListBox listbox;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNewAddr();
	afx_msg void OnSearch();
	afx_msg void OnSaveFile();
	afx_msg void OnEdit();
	afx_msg void OnBnClickedButtonSort();
	afx_msg void OnBnClickedDelete();
};


