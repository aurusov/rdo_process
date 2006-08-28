#ifndef RDO_PROCESS_CHILDFRM_H
#define RDO_PROCESS_CHILDFRM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ----------------------------------------------------------------------------
// ---------- RPChildFrame
// ----------------------------------------------------------------------------
class RPView;

class RPChildFrame: public CMDIChildWnd
{
DECLARE_DYNCREATE(RPChildFrame)

private:
	RPView* view;

public:
	RPChildFrame();
	virtual ~RPChildFrame();

	void setView( RPView* _view ) { view = _view; }

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(RPChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(RPChildFrame)
	afx_msg void OnFileClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // RDO_PROCESS_CHILDFRM_H
