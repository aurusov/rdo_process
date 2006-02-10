#ifndef RDO_PROCESS_MAINFRM_H
#define RDO_PROCESS_MAINFRM_H

#include "rdoprocess_dockwnd.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ----------------------------------------------------------------------------
// ---------- RDOPROCMainFrame
// ----------------------------------------------------------------------------
class RDOPROCMainFrame: public CMDIFrameWnd
{
DECLARE_DYNAMIC(RDOPROCMainFrame)

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	RDOPROCDockWnd projectBar;

public:
	RDOPROCMainFrame();
	virtual ~RDOPROCMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(RDOPROCMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(RDOPROCMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFlowConnector(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlowRotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFlowSelect(CCmdUI* pCmdUI);
	afx_msg void OnFlowSelect();
	afx_msg void OnFlowRotate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // RDO_PROCESS_MAINFRM_H
