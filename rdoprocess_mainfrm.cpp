#include "stdafx.h"
#include "rdoprocess_mainfrm.h"
#include "rdoprocess_app.h"
#include "rdoprocess_string.h"
#include "ctrl/rdoprocess_pagectrl.h"
#include "resource.h"
#include "rdoprocess_object.h"

#include "rdoprocess_generation_type_MJ.h" // MJ ���������� ���� ������ ���� ������������� �� �������

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------
// ---------- RPMainFrame
// ----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(RPMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(RPMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(RPMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FLOW_CONNECTOR, OnUpdateFlowConnector)
	ON_UPDATE_COMMAND_UI(ID_FLOW_ROTATE, OnUpdateFlowRotate)
	ON_UPDATE_COMMAND_UI(ID_FLOW_SELECT, OnUpdateFlowSelect)
	ON_COMMAND(ID_FLOW_SELECT, OnFlowSelect)
	ON_COMMAND(ID_FLOW_ROTATE, OnFlowRotate)
	ON_COMMAND(ID_FLOW_CONNECTOR, OnFlowConnector)
	ON_COMMAND(ID_GENERATE, OnGenerate)
	ON_COMMAND(ID_GEN_TYPE, OnGenType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

RPMainFrame::RPMainFrame()
{
}

RPMainFrame::~RPMainFrame()
{
}

int RPMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	bool winxp = false;
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	if ( ::GetVersionEx( &osv ) ) {
		winxp = osv.dwMajorVersion >= 5 && osv.dwMinorVersion == 1;
	}
	m_wndToolBar.CreateEx( this, winxp ? 0 : TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLOATING | CBRS_SIZE_DYNAMIC );
	m_wndToolBar.LoadToolBar( IDR_MAINFRAME );

	//MJ start 02.04.06
	m_wndToolBlockBarMJ.CreateEx( this, winxp ? 0 : TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLOATING | CBRS_SIZE_DYNAMIC );
	m_wndToolBlockBarMJ.LoadToolBar(TOOLBARBLOCKMJ);
	//MJstop


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	projectBar.Create( rp::string::format( ID_DOCK_PROJECT_BAR ).c_str(), this, 0 );
	projectBar.EnableDocking( CBRS_ALIGN_ANY );

	CListCtrl* listctrl = new CListCtrl();
	listctrl->Create( LVS_LIST | LVS_SINGLESEL, CRect(0,0,1,1), projectBar.prepareNewPage(), -1 );
	::SetWindowLong( listctrl->m_hWnd, GWL_EXSTYLE, ::GetWindowLong( listctrl->m_hWnd, GWL_EXSTYLE ) | WS_EX_CLIENTEDGE );
	listctrl->InsertItem( 0, "test 1" );
	listctrl->InsertItem( 1, "test 2" );
	listctrl->InsertItem( 2, "test 3" );
	listctrl->InsertItem( 3, "test 4" );
	projectBar.insertPage( listctrl, "Basic Process" );

	CListCtrl* listctrl2 = new CListCtrl();
	listctrl2->Create( LVS_LIST | LVS_SINGLESEL, CRect(0,0,1,1), projectBar.prepareNewPage(), -1 );
	::SetWindowLong( listctrl2->m_hWnd, GWL_EXSTYLE, ::GetWindowLong( listctrl2->m_hWnd, GWL_EXSTYLE ) | WS_EX_CLIENTEDGE );
	listctrl2->InsertItem( 0, "q 1" );
	listctrl2->InsertItem( 1, "qqqqqqqqqqq 2" );
	listctrl2->InsertItem( 2, "q 3" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	listctrl2->InsertItem( 3, "q 4" );
	projectBar.insertPage( listctrl2, "Second Page" );

	CListCtrl* listctrl3 = new CListCtrl();
	listctrl3->Create( LVS_LIST | LVS_SINGLESEL, CRect(0,0,1,1), projectBar.prepareNewPage(), -1 );
	::SetWindowLong( listctrl3->m_hWnd, GWL_EXSTYLE, ::GetWindowLong( listctrl3->m_hWnd, GWL_EXSTYLE ) | WS_EX_CLIENTEDGE );
	listctrl3->InsertItem( 0, "������ 1" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	listctrl3->InsertItem( 1, "������ 2" );
	projectBar.insertPage( listctrl3, "������ ��������" );

	projectBar.selectFirst();

	m_wndToolBar.EnableDocking( CBRS_ALIGN_ANY );

	EnableDocking( CBRS_ALIGN_ANY );

	DockControlBar( &m_wndToolBar );
	DockControlBar( &projectBar, AFX_IDW_DOCKBAR_LEFT );

	return 0;
}

BOOL RPMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

#ifdef _DEBUG
void RPMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void RPMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif

void RPMainFrame::OnUpdateFlowSelect( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( rpapp.project().hasChild() );
	pCmdUI->SetCheck( rpapp.project().getFlowState() == RPProject::flow_select );
}

void RPMainFrame::OnUpdateFlowConnector( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( rpapp.project().hasChild() );
	pCmdUI->SetCheck( rpapp.project().getFlowState() == RPProject::flow_connector );
}

void RPMainFrame::OnUpdateFlowRotate( CCmdUI* pCmdUI )
{
	pCmdUI->Enable( rpapp.project().hasChild() );
	pCmdUI->SetCheck( rpapp.project().getFlowState() == RPProject::flow_rotate );
}

void RPMainFrame::OnFlowSelect()
{
	rpapp.project().setFlowState( RPProject::flow_select );
}

void RPMainFrame::OnFlowConnector()
{
	rpapp.project().setFlowState( RPProject::flow_connector );
}

void RPMainFrame::OnFlowRotate()
{
	rpapp.project().setFlowState( RPProject::flow_rotate );
}

	// MJ start 29.03.06 ���������� ������ �������������
void RPMainFrame::OnGenerate() 
{
	
	rpapp.RDOfiles->pattern.open("aaa\\RDO_PROCESS.pat");
	rpapp.RDOfiles->resourse.open("aaa\\RDO_PROCESS.rss");
	rpapp.RDOfiles->function.open("aaa\\RDO_PROCESS.fun");
	
	rpapp.RDOfiles->typeres.open("aaa\\RDO_PROCESS.rtp");
	rpapp.RDOfiles->operations.open("aaa\\RDO_PROCESS.opr");
	rpapp.RDOfiles->smr.open("aaa\\RDO_PROCESS.smr");
	rpapp.RDOfiles->statistic.open("aaa\\RDO_PROCESS.pmd");
	
	blank_rdo_MJ();
	rpapp.project().list_name();
	
	rpapp.RDOfiles->pattern.close();
	
	rpapp.RDOfiles->resourse<<endl<<endl<<"$End";
	rpapp.RDOfiles->resourse.close();
	
	rpapp.RDOfiles->function.close();
	rpapp.RDOfiles->typeres.close();
	
	
	rpapp.RDOfiles->smr.close();
	
	
	
	rpapp.RDOfiles->statistic<<
	endl<<"$End";
	rpapp.RDOfiles->statistic.close();
	
	
	//�������������  �������� *.opr ��� �.�. ������ ���� ��� �������������� ��� �����

		rpapp.project().list_pattern_names.push_back("����_��������_�������������_��_�������");

					rpapp.RDOfiles->operations<<"$Operations";

				std::list<CString>::iterator it = rpapp.project().list_pattern_names.begin();
				  int amount = 1;	
				
				  while( it != rpapp.project().list_pattern_names.end() ) 
					{
					TRACE( "%s\n", (*it) );
					rpapp.RDOfiles->operations<<endl
					<<endl<<"operation_"<<amount<<" : "<<(*it);

					it++; amount++;
					}


					rpapp.RDOfiles->operations
					<<endl<<"$End";
rpapp.project().list_pattern_names.clear();

	rpapp.RDOfiles->operations.close();
	
	
	
	
	

	
}
	// MJ stop

void RPMainFrame::blank_rdo_MJ()
{
//������������� ����� ��������� *.rtp

rpapp.RDOfiles->typeres
<<endl	
<<endl<<"{ res }"
<<endl<<"$Resource_type Resource : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"��������� : (�����,��������)"
<<endl<<"�����������_���������� : integer {������� ������������� ���������� � ������� ������}"
<<endl<<"������_����������� : integer {���� ����������� ������� ����� �������������"
<<endl<<"����� �������� ������� ��������� � ��������� �����}"
<<endl<<"$End"
<<endl
<<endl
<<endl
<<endl
<<endl
<<endl<<"{1}"
<<endl<<"$Resource_type Creates : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"  par_1 : (true, false) {false} {�������� � ��������� ������� ������}"
<<endl<<"  par_amount: integer   {1}     {������� ����������� ���} "
<<endl<<"$End"
<<endl
<<endl
<<endl
<<endl<<"$Resource_type Group_of_transacts_X : temporary    {��������� ������������ ���������}"
<<endl<<"$Parameters"
<<endl<<"   {��������� ��������� �������� �������������"
<<endl<<"    � ������������ �������������}"
<<endl
<<endl<<"{ ��������� ����� ���������� }"
<<endl
<<endl<<"	�����_���������� :(";

rpapp.project().list_name_for_type_res(); // �-�� ��������� ������ ���� ������
rpapp.RDOfiles->typeres<<"������_����_���������)"


<<endl<<"	�����_����������_������� : such_as  Group_of_transacts_X.�����_���������� {ID ������, ���� ����������� ���������� �� ���� ����}"
<<endl
<<endl	
<<endl
<<endl<<"{ C�������� ���������}	"
<<endl<<"	���������_��������� : integer {}"
<<endl
<<endl
<<endl<<"{PRIMARY KEY}"
<<endl<<"    �����������������_�����_��������� : integer"
<<endl<<"    �����������������_�����_������_���������� : such_as  Group_of_transacts_X.�����_����������"
<<endl<<"{-----------}"
<<endl
<<endl<<"	�����_�_������� : integer"
<<endl<<"	���������_��������������� : (�������, ��������, �_�������, �_�������_�����)"
<<endl
<<endl<<"{ �������������� ��������� �������������� �������������}"
<<endl
<<endl<<"{" 
<<endl<<"... : ..."
<<endl<<" }"
<<endl<<"$End "
<<endl 
<<endl<<" {2 �������}"
<<endl<<" $Resource_type Queue : permanent"
<<endl<<"$Parameters"
<<endl<<"  ������_������� : integer"
<<endl<<"	 �����_�������: (��������, �����)"
<<endl<<"$End"
<<endl
<<endl
<<endl<<"{3 �������}"
<<endl<<"$Resource_type Block_process : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"  ��������� : (�����,��������)"
<<endl<<"$End"
<<endl
<<endl<<"{4del}"
<<endl<<" $Resource_type Block_Del : permanent"
<<endl<<"$Parameters"
<<endl<<"  �����������_��������� : integer"
<<endl
<<endl<<"$End";


//�������������  ��������� *.rtp
rpapp.RDOfiles->resourse<<"$Resources";


//�������������  ���������� *.pmd
rpapp.RDOfiles->statistic<<

endl<<"$Results";



//�������������  SMR *.smr
rpapp.RDOfiles->smr<<
endl<<"Model_name = RDO_PROCESS"
<<endl
<<endl<<"Resource_file  = RDO_PROCESS"
<<endl<<"OprIev_file    = RDO_PROCESS" // OPR
<<endl<<"Trace_file     = RDO_PROCESS"
<<endl<<"Statistic_file = RDO_PROCESS" //PMD
<<endl<<"Results_file   = RDO_PROCESS"
//<<endl<<"Frame_file     = RDO_PROCESS"
//<<endl<<"Frame_number   = 1"
//<<endl<<"Show_mode      = Animation"
//<<endl<<"Show_rate      = 10000000.0"
<<endl
<<endl<<"Terminate_if  Time_now >= "<< rpapp.project().generate_time_MJ;



// ������������� ������� � *.pat ��������� ����� �����������
rpapp.project().list_pattern_names.push_back("����_�����������");// ��������� ��� ��� *.opr

rpapp.RDOfiles->pattern
<<"{----------------��������� ����� �����������-------------------------------------------}"
<<endl<<"$Pattern ����_����������� : rule  {������������ ������}trace"
<<endl<<"	$Relevant_resources"
<<endl<<"		_transact_X : Group_of_transacts_X Keep"
<<endl
<<endl<<"	$Body"
<<endl
<<endl<<"	_transact_X"
<<endl<<"		Choice from _transact_X.���������_��������������� = �������  and"
<<endl<<"		_transact_X.�����_����������_�������<>_transact_X.�����_���������� "
<<endl<<"	first"
<<endl
<<endl<<"	Convert_rule"
<<endl<<"		�����_���������� set  _transact_X.�����_����������_�������"
<<endl
<<endl<<"	$End";


rpapp.RDOfiles->pattern
<<endl<<"{----------------��������� ���� ��������������� �� �������-------------------------------------------}"
<<endl
<<endl<<"$Pattern  ����_��������_�������������_��_������� : irregular_event trace "
<<endl<<"$Relevant_resources"
<<endl<<"_parameter : Group_of_transacts_X  NoChange {����� ��� ����, ��� ��� ���� ������}"
<<endl<<"$Time ="<< rpapp.project().generate_time_MJ
<<endl<<"$Body"
<<endl<<"_parameter"
<<endl<<"$End";



}

void RPMainFrame::OnGenType() 
{
	RP_GENERATION_TYPE_MJ dlg;
	dlg.DoModal();	
}
