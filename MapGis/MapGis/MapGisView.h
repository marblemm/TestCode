
// MapGisView.h : CMapGisView 类的接口
//

#pragma once

#include "CDMap.h"

class CMapGisView : public CView
{
private:
	CDMap m_Map;
	CString m_strFilePath;

protected: // 仅从序列化创建
	CMapGisView();
	DECLARE_DYNCREATE(CMapGisView)

// 特性
public:
	CMapGisDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMapGisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MapGisView.cpp 中的调试版本
inline CMapGisDoc* CMapGisView::GetDocument() const
   { return reinterpret_cast<CMapGisDoc*>(m_pDocument); }
#endif

