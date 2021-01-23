
// CounterThreadingView.cpp : implementation of the CCounterThreadingView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CounterThreading.h"
#endif

#include "CounterThreadingDoc.h"
#include "CounterThreadingView.h"
#include "CTestThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCounterThreadingView

IMPLEMENT_DYNCREATE(CCounterThreadingView, CView)

BEGIN_MESSAGE_MAP(CCounterThreadingView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREAD_START, &CCounterThreadingView::OnThreadStart)
	ON_COMMAND(ID_THREAD_PAUSE, &CCounterThreadingView::OnThreadPause)
	ON_COMMAND(ID_THREAD_RESUME, &CCounterThreadingView::OnThreadResume)
END_MESSAGE_MAP()

// CCounterThreadingView construction/destruction

CCounterThreadingView::CCounterThreadingView() noexcept
{
	t = 0.0;
	v = 40.0;
	x = 0.0;
	y = 0.0;
	g = 9.8;
	a = 40.0;
	j = 3.14 / 180.0;
}

CCounterThreadingView::~CCounterThreadingView()
{
}

BOOL CCounterThreadingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCounterThreadingView drawing

void CCounterThreadingView::OnDraw(CDC* pDC)
{
	CCounterThreadingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString xCounter;
	xCounter.Format(L"x= %f", x);
	y = v * t * sin(j * a) - 1 / 2 * g * t * t;
	CString yCounter;
	yCounter.Format(L"y= %f", y);
	pDC->MoveTo(200, 400);
	pDC->LineTo(800, 400);
	pDC->MoveTo(200, 400);
	pDC->LineTo(200, 100);
	

	if (t < 850)
	{
		for (int i = 0; i < m_Array.GetSize() - 2; i++)
		{
			pDC->MoveTo(m_Array[i].x, m_Array[i].y);
			pDC->LineTo(m_Array[i + 1].x, m_Array[i + 1].y);
			CBrush brush(RGB(0, 0, 0));
			CBrush* pBrush = pDC->SelectObject(&brush);
			CRect circ(m_Array[i + 1].x-10, m_Array[i + 1].y-10, m_Array[i + 1].x + 10, m_Array[i + 1].y+10);
			pDC->Ellipse(&circ);
			pDC->SelectObject(pBrush);
		}
	}
	
}


// CCounterThreadingView printing

BOOL CCounterThreadingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCounterThreadingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCounterThreadingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCounterThreadingView diagnostics

#ifdef _DEBUG
void CCounterThreadingView::AssertValid() const
{
	CView::AssertValid();
}

void CCounterThreadingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCounterThreadingDoc* CCounterThreadingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCounterThreadingDoc)));
	return (CCounterThreadingDoc*)m_pDocument;
}
#endif //_DEBUG


// CCounterThreadingView message handlers


void CCounterThreadingView::OnThreadStart()
{
	pThread = AfxBeginThread(CCounterThreadingView ::RunThreadFunction, this);
}


void CCounterThreadingView::OnThreadPause()
{
	pThread->SuspendThread();
}


void CCounterThreadingView::OnThreadResume()
{
	pThread->ResumeThread();
}


UINT CCounterThreadingView::RunThreadFunction(LPVOID P)
{
	CCounterThreadingView* pview = (CCounterThreadingView*)P;
	
	CPoint Point(0, 0);

	while (true)
	{
		Point.y = 400 + 200 * sin(pview->t);
		Point.x = 200 + pview->t;

		pview->m_Array.Add(Point);
		pview->t = pview->t + 100;

		pview->Invalidate();
		Sleep(1000);
	}
	// TODO: Add your implementation code here. 
	return 0;
}
