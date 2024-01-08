
// AddrBookDoc.cpp: CAddrBookDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "AddrBook.h"
#endif

#include "AddrBookDoc.h"

#include <locale.h>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAddrBookDoc

IMPLEMENT_DYNCREATE(CAddrBookDoc, CDocument)

BEGIN_MESSAGE_MAP(CAddrBookDoc, CDocument)
END_MESSAGE_MAP()


// CAddrBookDoc 생성/소멸

CAddrBookDoc::CAddrBookDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CAddrBookDoc::~CAddrBookDoc()
{
}

BOOL CAddrBookDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CStdioFile file;
	if (file.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
	{
		CString dataToSave;
		POSITION pos = m_ptrList.GetHeadPosition();
		while (pos != NULL)
		{
			CUserData* data = static_cast<CUserData*>(m_ptrList.GetNext(pos));
			dataToSave += data->GetName() + L"," + data->GetPhone() + L"\r\n";
		}
		CStringA utf8Data(dataToSave);
		file.Write(utf8Data, utf8Data.GetLength());
		file.Close();

		return 1;
	}

	return 0;
}

BOOL CAddrBookDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	CStdioFile file;
	setlocale(LC_ALL, "korean");
	if (file.Open(lpszPathName, CFile::modeRead | CFile::typeText))
	{
		CString line;
		while (file.ReadString(line))
		{
			//TRACE(_T("%s\n"), line);

		}

		file.Close();

		return 1;
	}

	return 0;
}

BOOL CAddrBookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}


// CAddrBookDoc serialization

void CAddrBookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CAddrBookDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CAddrBookDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAddrBookDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAddrBookDoc 진단

#ifdef _DEBUG
void CAddrBookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAddrBookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAddrBookDoc 명령


int CAddrBookDoc::NewAddr(CString name, CString phone)
{
	CUserData *pNew = new CUserData(name, phone);

	m_ptrList.AddTail(pNew);

	return 0;
}

int CAddrBookDoc::EditAddr(CString name, CString phone, CUserData editData)
{
	CUserData* pNew = new CUserData(name, phone);

	POSITION position = m_ptrList.Find(&editData);
	m_ptrList.RemoveAt(position);

	POSITION pos = m_ptrList.GetHeadPosition();
	while (pos != NULL)
	{
		CUserData* pNode = (CUserData*)m_ptrList.GetNext(pos);
		TRACE(_T("%s , %s"), pNode->GetName(), pNode->GetPhone());
	}

	//m_ptrList.InsertBefore(editPos, pNew);

	return 0;
}


void CAddrBookDoc::ReleaseList()
{
	POSITION pos = m_ptrList.GetHeadPosition();
	while (pos != NULL)
	{
		CUserData* pNode = (CUserData*)m_ptrList.GetNext(pos);

		//OutputDebugString(pNode->GetName() + _T("----------------------------\n"));
		delete pNode;
	}
}


CUserData CAddrBookDoc::FindUser(CString name)
{
	POSITION pos = m_ptrList.GetHeadPosition();
	while (pos != NULL)
	{
		CUserData* pNode = (CUserData*)m_ptrList.GetNext(pos);
		if (pNode->GetName() == name)
			return *pNode;
	}

	return CUserData(_T(""),_T(""));
}
