// rdoprocess_shape_process_dlg2_MJ.cpp : implementation file
//

#include "stdafx.h"
//#include "rdo_process.h"
#include "rdoprocess_shape_process_dlg2_MJ.h"
#include "rdoprocess_app.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RPShapeProcessDlg2_MJ dialog


RPShapeProcessDlg2_MJ::RPShapeProcessDlg2_MJ(CWnd* pParent,RPShapeProcessMJ* ppParent,RPShapeProcessDlg1_MJ* pParentDlg)
	: CDialog(RPShapeProcessDlg2_MJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(RPShapeProcessDlg2_MJ)
	m_combo_res_value = _T("");
	//}}AFX_DATA_INIT
	pParentMJ = ppParent;
	pParentDlgMJ = pParentDlg;
	list_resource_dlg2 = &list_resource_MJ;
	
}


BOOL RPShapeProcessDlg2_MJ::OnInitDialog()
{
	CDialog::OnInitDialog();
	rpapp.project().list_name_for_resource_MJ(list_resource_dlg2);
	list_name_resource();

	return true;
}


void RPShapeProcessDlg2_MJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RPShapeProcessDlg2_MJ)
	DDX_Control(pDX, IDC_COMBO1, m_combo_res_control);
	DDX_CBString(pDX, IDC_COMBO1, m_combo_res_value);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RPShapeProcessDlg2_MJ, CDialog)
	//{{AFX_MSG_MAP(RPShapeProcessDlg2_MJ)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RPShapeProcessDlg2_MJ message handlers

void RPShapeProcessDlg2_MJ::OnCloseupCombo1() 
{
//pParentMJ->list_name_for_resource_MJ();	
}


void RPShapeProcessDlg2_MJ::list_name_resource()
{

	std::list< RPObject* >::const_iterator it = list_resource_MJ.begin();
	while( it != list_resource_MJ.end() ) {
	
		
	    TRACE( "%s\n", (*it)->getName().c_str() );
      	m_combo_res_control.AddString((*it)->getName().c_str());
		it++;
	}
}


void RPShapeProcessDlg2_MJ::OnOK() 
{
	// TODO: Add extra validation here
	CString data_combo;
	if(	m_combo_res_control.GetCurSel() != -1)
	{
		m_combo_res_control.GetLBText(m_combo_res_control.GetCurSel(),data_combo);
		pParentDlgMJ->m_ResList.AddString(data_combo);
        pParentMJ->list_resource_procMJ.push_back(data_combo);
	}
	CDialog::OnOK();
}
