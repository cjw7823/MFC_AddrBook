// CMyFormView.cpp: 구현 파일
//

#include "pch.h"
#include "AddrBook.h"
#include "CMyFormView.h"
#include "CDlgNewAddr.h"

#include "AddrBookDoc.h"
#include "AddrBookView.h"

// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView(IDD_FORMVIEW)
{

}

CMyFormView::~CMyFormView()
{
}

CAddrBookDoc* CMyFormView::GetDocument() const
{

	CAddrBookView* parent = static_cast<CAddrBookView*>(GetParent());
	return parent->GetDocument();
}

void CMyFormView::OnDraw(CDC* pDC)
{

}

BOOL CMyFormView::Create(LPCTSTR a, LPCTSTR b, DWORD c,	const RECT& d, CWnd* e, UINT f, CCreateContext* g)
{
	return __super::Create(a, b, c, d, e, f, g);;
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, listbox);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	//ON_WM_SETFOCUS()
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//저장 명령
	ON_COMMAND(ID_FILE_SAVE, &CMyFormView::OnSaveFile)
	//커스텀
	ON_COMMAND(ID_New_Addr, &CMyFormView::OnNewAddr)
	ON_COMMAND(ID_SEARCH, &CMyFormView::OnSearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ADDR, &CMyFormView::OnNewAddr)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMyFormView::OnSearch)
END_MESSAGE_MAP()


// CMyFormView 진단

#ifdef _DEBUG
void CMyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFormView 메시지 처리기

void CMyFormView::OnNewAddr()
{
	CDlgNewAddr dlg;
	if (dlg.DoModal() == IDOK)
	{
		listbox.AddString(dlg.m_strName + _T(" [") + dlg.m_strPhone + _T("]"));
		GetDocument()->NewAddr(dlg.m_strName, dlg.m_strPhone);
	}
}

void CMyFormView::OnSearch()
{
	CDlgNewAddr dlg;
	if (dlg.DoModal() == IDOK)
	{
		CUserData user = GetDocument()->FindUser(dlg.m_strName);
		if (user.GetName().IsEmpty())
			AfxMessageBox(_T("Not found"));
		else
			AfxMessageBox(user.GetName() + _T(" ") + user.GetPhone());
	}
}

void CMyFormView::OnSaveFile()
{
}


//void CMyFormView::OnSetFocus(CWnd* pOldWnd)
//{
	//CFormView::OnSetFocus(pOldWnd);
//	GetParentFrame()->SendMessage(WM_COMMAND, 1, (LPARAM)GetDlgItem(IDR_AddrBookTYPE));
//}
