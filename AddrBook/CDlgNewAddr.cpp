// CDlgNewAddr.cpp: 구현 파일
//

#include "pch.h"
#include "AddrBook.h"
#include "afxdialogex.h"
#include "CDlgNewAddr.h"


// CDlgNewAddr 대화 상자

IMPLEMENT_DYNAMIC(CDlgNewAddr, CDialogEx)

CDlgNewAddr::CDlgNewAddr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NEW_ADDR, pParent)
	, m_strName(_T(""))
	, m_strPhone(_T(""))
{

}

CDlgNewAddr::~CDlgNewAddr()
{
}

void CDlgNewAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
}


BEGIN_MESSAGE_MAP(CDlgNewAddr, CDialogEx)
END_MESSAGE_MAP()


// CDlgNewAddr 메시지 처리기
