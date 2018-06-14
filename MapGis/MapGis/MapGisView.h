
// MapGisView.h : CMapGisView ��Ľӿ�
//

#pragma once

#include "CDMap.h"

class CMapGisView : public CView
{
private:
	CDMap m_Map;
	CString m_strFilePath;

protected: // �������л�����
	CMapGisView();
	DECLARE_DYNCREATE(CMapGisView)

// ����
public:
	CMapGisDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMapGisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // MapGisView.cpp �еĵ��԰汾
inline CMapGisDoc* CMapGisView::GetDocument() const
   { return reinterpret_cast<CMapGisDoc*>(m_pDocument); }
#endif

