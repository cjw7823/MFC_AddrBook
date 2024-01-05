// CMyFormView.cpp: 구현 파일
//

#include "pch.h"
#include "AddrBook.h"
#include "CMyFormView.h"


// CMyFormView

IMPLEMENT_DYNCREATE(CMyFormView, CFormView)

CMyFormView::CMyFormView()
	: CFormView(IDD_FORMVIEW)
{

}

CMyFormView::~CMyFormView()
{
}

void CMyFormView::OnDraw(CDC* pDC)
{
	CListBox* pListBox = static_cast<CListBox*>(GetDlgItem(IDC_LIST1));
	if (pListBox != nullptr)
	{
		listbox = pListBox;
	}
}

void CMyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyFormView::OnBnClickedButton2)
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


void CMyFormView::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
