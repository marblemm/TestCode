
// MapGisView.cpp : CMapGisView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MapGis.h"
#endif

#include "MapGisDoc.h"
#include "MapGisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapGisView

IMPLEMENT_DYNCREATE(CMapGisView, CView)

	BEGIN_MESSAGE_MAP(CMapGisView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMapGisView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_COMMAND(ID_FILE_OPEN, &CMapGisView::OnFileOpen)
	END_MESSAGE_MAP()

	// CMapGisView 构造/析构

	CMapGisView::CMapGisView()
	{
		// TODO: 在此处添加构造代码

	}

	CMapGisView::~CMapGisView()
	{
	}

	BOOL CMapGisView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式

		return CView::PreCreateWindow(cs);
	}

	// CMapGisView 绘制

	void CMapGisView::OnDraw(CDC* /*pDC*/)
	{
		CMapGisDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码
	}


	// CMapGisView 打印


	void CMapGisView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMapGisView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CMapGisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CMapGisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CMapGisView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CMapGisView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CMapGisView 诊断

#ifdef _DEBUG
	void CMapGisView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMapGisView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMapGisDoc* CMapGisView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapGisDoc)));
		return (CMapGisDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMapGisView 消息处理程序

	//动态创建地图窗口
	int CMapGisView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  在此添加您专用的创建代码
		CRect rcmap;
		GetClientRect(rcmap);
		m_Map.Create(NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rcmap,this,IDC_MAP);

		return 0;
	}


	void CMapGisView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		// TODO: 在此处添加消息处理程序代码
		if(m_Map.m_hWnd == NULL)
			return;   
		if(IsWindow(m_Map.m_hWnd)) //判断给定的窗口句柄是否标识一个已存在的窗口
		{
			CRect rc;
			this->GetClientRect(&rc);
			m_Map.MoveWindow(&rc,FALSE);      
			m_Map.ZoomToPrev(); 
		}
	}


	void CMapGisView::OnFileOpen()
	{
		// TODO: 在此添加命令处理程序代码

		TCHAR szFilters[]= _T("SHP Files (*.shp)|*.shp||");

		CFileDialog fileDlg (TRUE,_T("shp"),_T("*.shp"),
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

		if( fileDlg.DoModal() == IDOK )
		{
			m_strFilePath = fileDlg.GetPathName();

			if (_T("")!=m_strFilePath)
			{

				// 先删除所有图层
				m_Map.RemoveAllLayers();


				// 创建shp接口打开shp文件加入地图
				mapWindow::IShapefilePtr pShapefilebound;
				pShapefilebound.CreateInstance(__uuidof(mapWindow::Shapefile));
				pShapefilebound->Open(_bstr_t(m_strFilePath),false);

				m_Map.AddLayer(pShapefilebound,true);
				//}

			}
			// 发送视图重绘消息
			Invalidate();
		}
	}
