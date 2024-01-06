// CDlgNewAddr.cpp: 구현 파일
//

#include "pch.h"
#include "AddrBook.h"
#include "afxdialogex.h"
#include "CDlgNewAddr.h"

#include <cwctype>

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

	DDX_Control(pDX, IDC_EDIT_PHONE, m_EditCtrl);
}


BEGIN_MESSAGE_MAP(CDlgNewAddr, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PHONE, &CDlgNewAddr::OnEnChangeEditPhone)
END_MESSAGE_MAP()


// CDlgNewAddr 메시지 처리기


void CDlgNewAddr::OnEnChangeEditPhone()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString text;
	m_EditCtrl.GetWindowTextW(text);

	if (!IsNumeric(text))//입력된 문자가 숫자가 아니라면.
	{
		TRACE(_T("m_EditCtrl: %s\n"), text);

		text.Delete(text.GetLength() - 1);
		m_EditCtrl.SetWindowTextW(text);
	}
}

bool CDlgNewAddr::IsNumeric(const CString& str)
{
	// CString을 wchar_t 배열로 변환
	const wchar_t* charArray = str.GetString();

	// 각 문자가 숫자인지 확인
	for (int i = 0; i < str.GetLength(); ++i)
	{
		if (!std::iswdigit(charArray[i]))
		{
			return false; // 숫자가 아닌 문자가 있으면 false 반환
		}
	}

	return true; // 모든 문자가 숫자이면 true 반환
}
