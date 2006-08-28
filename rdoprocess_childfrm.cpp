#include "stdafx.h"
#include "rdoprocess_childfrm.h"
#include "rdoprocess_docview.h"
#include <rdoprocess_object_flowchart.h>
#include <rdoprocess_flowchart.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPChildFrame
// ----------------------------------------------------------------------------
IMPLEMENT_DYNCREATE(RPChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(RPChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(RPChildFrame)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

RPChildFrame::RPChildFrame():
	CMDIChildWnd(),
	view( NULL )
{
}

RPChildFrame::~RPChildFrame()
{
}

BOOL RPChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) ) return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

int RPChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if ( CMDIChildWnd::OnCreate(lpCreateStruct) == -1 ) return -1;
	return 0;
}

void RPChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus( pOldWnd );
//	if ( flowchart ) flowchart->SetFocus();
}

BOOL RPChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
//	if ( view && view->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo) ) return TRUE;
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

#ifdef _DEBUG
void RPChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void RPChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void RPChildFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

void RPChildFrame::OnMDIActivate( BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd )
{
	if ( view ) view->getFlowchart()->flowobj->setActive( bActivate ? true : false );
	CMDIChildWnd::OnMDIActivate( bActivate, pActivateWnd, pDeactivateWnd );
}
