﻿
// AddrBookDoc.h: CAddrBookDoc 클래스의 인터페이스
//


#pragma once

#include "CMyFormView.h"

class CAddrBookDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CAddrBookDoc() noexcept;
	DECLARE_DYNCREATE(CAddrBookDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CAddrBookDoc();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName) override;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName) override;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//protected:
	CPtrList m_ptrList;
private:
	CListBox* m_listBox;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int NewAddr(CString name, CString phone);
	int EditAddr(CString name, CString phone, CUserData editData);
	void ReleaseList();
	CUserData FindUser(CString name);
	void SetListBoxPtr(CListBox* listBox) { m_listBox = listBox; };
};
