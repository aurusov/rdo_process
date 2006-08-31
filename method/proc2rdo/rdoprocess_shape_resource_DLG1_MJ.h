#if !defined(AFX_RDOPROCESS_SHAPE_RESOURCE_DLG1_MJ_H__08926353_FF43_421C_8D32_681628748E52__INCLUDED_)
#define AFX_RDOPROCESS_SHAPE_RESOURCE_DLG1_MJ_H__08926353_FF43_421C_8D32_681628748E52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rdoprocess_shape_resource_DLG1_MJ.h : header file
//
#include "../../resource.h"
#include "rdoprocess_shape_resource.h"
/////////////////////////////////////////////////////////////////////////////
// RPShapeResourceDLG1_MJ dialog

class RPShapeResourceDLG1_MJ : public CDialog
{
// Construction
public:
	RPShapeResourceDLG1_MJ(CWnd* pParent = NULL, RPShapeResource_MJ* ppParent = NULL); // standard constructor
	virtual BOOL OnInitDialog();


	RPShapeResource_MJ* pParentMJ;
// Dialog Data
	//{{AFX_DATA(RPShapeResourceDLG1_MJ)
	enum { IDD = IDD_DIALOG_RESOURCE_DLG1 };
	CString	m_name;
	int		m_dlgamount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RPShapeResourceDLG1_MJ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(RPShapeResourceDLG1_MJ)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDOPROCESS_SHAPE_RESOURCE_DLG1_MJ_H__08926353_FF43_421C_8D32_681628748E52__INCLUDED_)
