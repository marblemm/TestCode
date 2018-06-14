
// MapGisView.cpp : CMapGisView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
		// ��׼��ӡ����
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMapGisView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_COMMAND(ID_FILE_OPEN, &CMapGisView::OnFileOpen)
	END_MESSAGE_MAP()

	// CMapGisView ����/����

	CMapGisView::CMapGisView()
	{
		// TODO: �ڴ˴���ӹ������

	}

	CMapGisView::~CMapGisView()
	{
	}

	BOOL CMapGisView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: �ڴ˴�ͨ���޸�
		//  CREATESTRUCT cs ���޸Ĵ��������ʽ

		return CView::PreCreateWindow(cs);
	}

	// CMapGisView ����

	void CMapGisView::OnDraw(CDC* /*pDC*/)
	{
		CMapGisDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	}


	// CMapGisView ��ӡ


	void CMapGisView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CMapGisView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// Ĭ��׼��
		return DoPreparePrinting(pInfo);
	}

	void CMapGisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	}

	void CMapGisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: ��Ӵ�ӡ����е��������
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


	// CMapGisView ���

#ifdef _DEBUG
	void CMapGisView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMapGisView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMapGisDoc* CMapGisView::GetDocument() const // �ǵ��԰汾��������
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapGisDoc)));
		return (CMapGisDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CMapGisView ��Ϣ�������

	//��̬������ͼ����
	int CMapGisView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  �ڴ������ר�õĴ�������
		CRect rcmap;
		GetClientRect(rcmap);
		m_Map.Create(NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rcmap,this,IDC_MAP);

		return 0;
	}


	void CMapGisView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		// TODO: �ڴ˴������Ϣ����������
		if(m_Map.m_hWnd == NULL)
			return;   
		if(IsWindow(m_Map.m_hWnd)) //�жϸ����Ĵ��ھ���Ƿ��ʶһ���Ѵ��ڵĴ���
		{
			CRect rc;
			this->GetClientRect(&rc);
			m_Map.MoveWindow(&rc,FALSE);      
			m_Map.ZoomToPrev(); 
		}
	}


	void CMapGisView::OnFileOpen()
	{
		// TODO: �ڴ���������������

		TCHAR szFilters[]= _T("SHP Files (*.shp)|*.shp||");

		CFileDialog fileDlg (TRUE,_T("shp"),_T("*.shp"),
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

		if( fileDlg.DoModal() == IDOK )
		{
			m_strFilePath = fileDlg.GetPathName();

			if (_T("")!=m_strFilePath)
			{

				// ��ɾ������ͼ��
				m_Map.RemoveAllLayers();


				// ����shp�ӿڴ�shp�ļ������ͼ
				mapWindow::IShapefilePtr pShapefilebound;
				pShapefilebound.CreateInstance(__uuidof(mapWindow::Shapefile));
				pShapefilebound->Open(_bstr_t(m_strFilePath),false);

				m_Map.AddLayer(pShapefilebound,true);
				//}

			}
			// ������ͼ�ػ���Ϣ
			Invalidate();
		}
	}
