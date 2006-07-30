// rdoprocess_shape_create_dlg2_MJ.cpp : implementation file
//

#include "stdafx.h"
//#include "rdo_process.h"
#include "rdoprocess_shape_create_dlg2_MJ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RPShapeCreateDlg2_MJ dialog


RPShapeCreateDlg2_MJ::RPShapeCreateDlg2_MJ(CWnd* pParent,RPShapeCreateMJ* ppParent)
	: CDialog(RPShapeCreateDlg2_MJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(RPShapeCreateDlg2_MJ)
	m_dlginf = 0;
	m_dlgid = 0;
	m_dlgpar1 = 0.0;
	m_dlgpar2 = 0.0;
	m_dlgpar3 = 0.0;
	//}}AFX_DATA_INIT
	pParentMJ = ppParent;

}


void RPShapeCreateDlg2_MJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RPShapeCreateDlg2_MJ)
	DDX_Text(pDX, IDC_EDIT1, m_dlginf);
	DDX_Text(pDX, IDC_EDIT2, m_dlgid);
	DDX_Text(pDX, IDC_EDIT3, m_dlgpar1);
	DDX_Text(pDX, IDC_EDIT4, m_dlgpar2);
	DDX_Text(pDX, IDC_EDIT5, m_dlgpar3);
	//}}AFX_DATA_MAP
}


BOOL RPShapeCreateDlg2_MJ::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ������������� ���� ���������� �������
    
	m_dlginf= pParentMJ->inf; // ������������
	m_dlgid=  pParentMJ->gID; // ID ������
	m_dlgpar1=pParentMJ->gpar1;
	m_dlgpar2=pParentMJ->gpar2;
	m_dlgpar3=pParentMJ->gpar3;

UpdateData(FALSE);
	return TRUE;
}



BEGIN_MESSAGE_MAP(RPShapeCreateDlg2_MJ, CDialog)
	//{{AFX_MSG_MAP(RPShapeCreateDlg2_MJ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RPShapeCreateDlg2_MJ message handlers

void RPShapeCreateDlg2_MJ::OnOK() 
{
	// ������������� ������� ���������� ����

    UpdateData(TRUE);
	
	pParentMJ->inf   = m_dlginf; // ������������
	pParentMJ->gID   = m_dlgid; // ID ������
	pParentMJ->gpar1 = m_dlgpar1;
	pParentMJ->gpar2 = m_dlgpar2;
	pParentMJ->gpar3 = m_dlgpar3;
  
		
	CDialog::OnOK();
}
