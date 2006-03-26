#if !defined(AFX_RDOPROCESS_SHAPE_PROCESS_DLG1_MJ_H__0DF5DDB9_3E18_409E_A23C_A0A0F476FFFB__INCLUDED_)
#define AFX_RDOPROCESS_SHAPE_PROCESS_DLG1_MJ_H__0DF5DDB9_3E18_409E_A23C_A0A0F476FFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rdoprocess_shape_process_dlg1_MJ.h : header file
//
#include"resource.h"
#include "rdoprocess_shape_process_MJ.h"
/////////////////////////////////////////////////////////////////////////////
// RPShapeProcessDlg1_MJ dialog

class RPShapeProcessDlg1_MJ : public CDialog
{
// Construction
public:
	RPShapeProcessDlg1_MJ(CWnd* pParent = NULL,RPShapeProcessMJ* ppParent=NULL);   // standard constructor
    virtual BOOL OnInitDialog();

	RPShapeProcessMJ* pParentMJ; // ������ �� ��������
// Dialog Data
	//{{AFX_DATA(RPShapeProcessDlg1_MJ)
	enum { IDD = IDD_DIALOG_PROCESS_1_MJ };
	CListBox	m_ResList;
	CButton	m_DelRes;
	CButton	m_AddRes;
	CEdit	m_proc_dlg1_max_control_MJ;
	CEdit	m_proc_dlg1_min_control_MJ;
	CEdit	m_proc_dlg1_disp_control_MJ;
	CEdit	m_proc_dlg1_exp_control_MJ;
	CComboBox	m_parameter;
	CComboBox	m_combo;
	CComboBox	m_type;
	CComboBox	m_action;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RPShapeProcessDlg1_MJ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RPShapeProcessDlg1_MJ)
	afx_msg void OnCloseupCombo1();
	afx_msg void OnCloseupCombo3();
	afx_msg void OnButton1();
	virtual void OnOK();
	afx_msg void OnCloseupCombo2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDOPROCESS_SHAPE_PROCESS_DLG1_MJ_H__0DF5DDB9_3E18_409E_A23C_A0A0F476FFFB__INCLUDED_)
