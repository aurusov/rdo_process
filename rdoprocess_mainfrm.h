#ifndef RDO_PROCESS_MAINFRM_H
#define RDO_PROCESS_MAINFRM_H

#include "ctrl/rdoprocess_projectbar.h"
#include "ctrl/rdoprocess_toolbar.h"
#include "rdoprocess_object.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ----------------------------------------------------------------------------
// ---------- RPMainFrameMsg
// ----------------------------------------------------------------------------
class RPMainFrameMsg: public RPObject
{
friend class RPMainFrame;
protected:
	RPMainFrameMsg();
	virtual rp::string getType() { return "RPMainFrameMsg"; }
	virtual void notify( RPObject* from, UINT message, WPARAM wParam, LPARAM lParam );
};

// ----------------------------------------------------------------------------
// ---------- RPMainFrame
// ----------------------------------------------------------------------------
class RPMainFrame: public CMDIFrameWnd
{
DECLARE_DYNAMIC(RPMainFrame)

friend class RPMainFrameMsg;

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_wndToolBlockBarMJ; // MJ 2.04.06 ������ ��� ������
	CComboBox   m_wndCombo;
	RPToolBar   m_wndStyleAndColorToolBar;
	RPMainFrameMsg* m_msg;

	void dockControlBarBesideOf( CControlBar& bar, CControlBar& baseBar );

public:
	RPMainFrame();
	virtual ~RPMainFrame();

	RPProjectBar projectBar;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(RPMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(RPMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFlowSelect(CCmdUI* pCmdUI);
	afx_msg void OnFlowSelect();
	afx_msg void OnFlowRotate();
	afx_msg void OnFlowConnector();
	afx_msg void OnGenerate();
	afx_msg void OnGenType();
	afx_msg void OnUpdateBtnFillBrush(CCmdUI* pCmdUI);
	afx_msg void OnBtnFillBrush();
	afx_msg void OnBtnFillPen();
	afx_msg void OnBtnFillText();
	//}}AFX_MSG
	afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
	afx_msg LONG OnSelEndDefault(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // RDO_PROCESS_MAINFRM_H
