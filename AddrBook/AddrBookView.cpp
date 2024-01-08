
// AddrBookView.cpp: CAddrBookView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AddrBook.h"
#endif

#include "AddrBookDoc.h"
#include "AddrBookView.h"
#include "CDlgNewAddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddrBookView

IMPLEMENT_DYNCREATE(CAddrBookView, CView)

BEGIN_MESSAGE_MAP(CAddrBookView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_New_Addr, &CAddrBookView::OnNewAddr)
	ON_COMMAND(ID_SEARCH, &CAddrBookView::OnSearch)
END_MESSAGE_MAP()

// CAddrBookView 생성/소멸

CAddrBookView::CAddrBookView() noexcept : m_FormView(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CAddrBookView::~CAddrBookView()
{
	GetDocument()->ReleaseList();
}

BOOL CAddrBookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CAddrBookView 그리기

void CAddrBookView::OnDraw(CDC* /*pDC*/)
{

}


// CAddrBookView 인쇄

BOOL CAddrBookView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CAddrBookView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CAddrBookView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CAddrBookView 진단

#ifdef _DEBUG
void CAddrBookView::AssertValid() const
{
	CView::AssertValid();
}

void CAddrBookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAddrBookDoc* CAddrBookView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAddrBookDoc)));
	return (CAddrBookDoc*)m_pDocument;
}
#endif //_DEBUG


// CAddrBookView 메시지 처리기


int CAddrBookView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CAddrBookView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

}


void CAddrBookView::OnNewAddr()
{
	CDlgNewAddr dlg;
	if (dlg.DoModal() == IDOK) 
	{
		CMyFormView* formView = static_cast<CMyFormView*>(m_FormView);
		formView->listbox.AddString(dlg.m_strName + _T(" [") + dlg.m_strPhone + _T("]"));
		GetDocument()->NewAddr(dlg.m_strName, dlg.m_strPhone);
	}
}


void CAddrBookView::OnSearch()
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

void CAddrBookView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CAddrBookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rc;
	GetClientRect(&rc);
	rc.left -= 10;
	rc.top -= 10;

	CCreateContext cc;

	CView* pView = (CView*)RUNTIME_CLASS(CMyFormView)->CreateObject();
	ZeroMemory(&cc, sizeof(cc));
	pView->Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_HSCROLL, rc, this, IDD_FORMVIEW, &cc);
	pView->OnInitialUpdate();
	m_FormView = pView;
}
