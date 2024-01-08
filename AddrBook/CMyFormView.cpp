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
	GetDocument()->SetListBoxPtr(&listbox);
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
	ON_COMMAND(ID_FILE_SAVE_AS, &CMyFormView::OnSaveFile)
	//커스텀
	ON_COMMAND(ID_New_Addr, &CMyFormView::OnNewAddr)
	ON_COMMAND(ID_SEARCH, &CMyFormView::OnSearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ADDR, &CMyFormView::OnNewAddr)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CMyFormView::OnSearch)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CMyFormView::OnEdit)
	ON_BN_CLICKED(IDC_BUTTON_SORT, &CMyFormView::OnBnClickedButtonSort)
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
	GetDocument()->DoFileSave();//DoFileSave 에서 OnSaveDocument()호출됨.
}

void CMyFormView::OnEdit()
{
	int itemCount = listbox.GetCount();

	for (int i = 0; i < itemCount; ++i)
	{
		BOOL isSelected = listbox.GetSel(i);

		if (isSelected)
		{
			//편집
			CString name, phone;
			listbox.GetText(i, name);
			listbox.GetText(i, phone);

			int openIndex = name.Find(L"[");
			phone = phone.Mid(openIndex + 1, name.GetLength() - openIndex -2);
			if (openIndex > 1)//이름과 번호 사이 공백을 감안. 1인 경우, 이름 없이 ' []'임.
				name = name.Left(openIndex - 1);
			else//이름이 없는 경우
				name = L"";

			CDlgNewAddr dlg(name, phone);
			if (dlg.DoModal() == IDOK)
			{
				listbox.DeleteString(i);
				listbox.InsertString(i, dlg.m_strName + _T(" [") + dlg.m_strPhone + _T("]"));
				GetDocument()->EditAddr(dlg.m_strName, dlg.m_strPhone, CUserData(name, phone));

				break;
			}
		}
	}
}

int SortAscending(const void* p1, const void* p2);
int SortDescending(const void* p1, const void* p2);

void CMyFormView::OnBnClickedButtonSort()
{
	static bool func_choise = false;//정렬 방식 스왑.

	int itemCount = listbox.GetCount();

	// 배열에 아이템 복사
	CStringArray items;
	for (int i = 0; i < itemCount; ++i)
	{
		CString item;
		listbox.GetText(i, item);
		items.Add(item);
	}

	int (*ptrFunc)(const void*, const void*);
	if (func_choise)
		ptrFunc = SortAscending;
	else
		ptrFunc = SortDescending;

	func_choise = !func_choise;

	// 배열 정렬
	qsort(items.GetData(), items.GetSize(), sizeof(CString), ptrFunc);

	// 리스트 박스 초기화
	listbox.ResetContent();

	// 정렬된 배열의 아이템을 다시 리스트 박스에 설정
	for (int i = 0; i < itemCount; ++i)
	{
		listbox.AddString(items[i]);
	}
}

int SortAscending(const void* p1, const void* p2)
{
	CString* s1 = (CString*)p1;
	CString* s2 = (CString*)p2;

	return _tcscmp(s1->GetBuffer(0), s2->GetBuffer(0));
}

int SortDescending(const void* p1, const void* p2)
{
	CString* s1 = (CString*)p1;
	CString* s2 = (CString*)p2;

	return _tcscmp(s1->GetBuffer(0), s2->GetBuffer(0)) * -1;
}