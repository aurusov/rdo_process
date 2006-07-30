// rdoprocess_shape_terminate_MJ.cpp: implementation of the RPShapeTerminate_MJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "rdo_process.h"
#include "rdoprocess_shape_terminate_MJ.h"
#include "rdoprocess_shape_terminate_dlg1_MJ.h"
#include "rdo_process_project_RDO_proc_MJ.h"
#include "../../rdoprocess_app.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeTerminateMJ::RPShapeTerminateMJ( RPObject* _parent ):
	RPShape_MJ( _parent, _T("Terminate") )
{
	// ������������� ���� ����� 
	type ="block";
		
	pa_src.push_back( rp::point(-50, 0) );
	pa_src.push_back( rp::point(-25, -25) );
	pa_src.push_back( rp::point(50, -25) );
	pa_src.push_back( rp::point(50, 25) );
	pa_src.push_back( rp::point(-25, 25) );
	pa_src.push_back( rp::point(-50, 0) );

	docks.push_back( new RPConnectorDock( this, RPConnectorDock::in,  rp::point( -50, 0 ), 180 ) );
}

void RPShapeTerminateMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
RPShapeTerminateDlg1_MJ dlg(NULL,this);
dlg.DoModal();

}


RPShapeTerminateMJ::~RPShapeTerminateMJ()
{

}

void RPShapeTerminateMJ::generate()
{

	//��������� ���� ���������� ��������� ��� *.opr
		CString name_value1("����_��������_");
		CString name_value2(getName().c_str());
		CString name_value(name_value1 + name_value2);
		static_cast<RPProject_RDO_Proc_MJ*>(rpapp.project())->list_pattern_names.push_back(name_value);



	/*
	RDOfiles->pattern <<endl<<endl<<"��� ���������� ����� - "<<id_next
	<<endl<<"��� - "<<getName().c_str();
*/

// ��������� �������� ��� ���� *.res

	RPCreationRDOFilesMJ* RDOfiles = static_cast<RPProject_RDO_Proc_MJ*>(rpapp.project())->RDOfiles;
	RDOfiles->resourse<<endl<<endl<<"{-------���� process ------" <<getName().c_str()<<"-------------------}" <<endl

	<<"Block_Del_"<<getName().c_str()<<" : Block_Del 0";






// ��������� ��������� ��� ���� *.pat


RDOfiles->pattern <<endl
<<endl<<"{-------���� ��������------------"<<getName().c_str()<<"---------------------------------}"
<<endl
<<endl
<<endl<<"$Pattern ����_��������_"<<getName().c_str()<<" : rule  {������������ ������}trace"
<<endl<<"	$Relevant_resources"
<<endl
<<endl<<"		_transact_X : Group_of_transacts_X Erase"
<<endl<<"		_block : Block_Del_"<<getName().c_str()<<" Keep"
<<endl<<"			{����������� ��� ������ ���������� ������� ��������� - ������� �������������}"
<<endl
<<endl
<<endl
<<endl<<"$Body"
<<endl 
<<endl<<"  _transact_X"
<<endl<<"		 Choice from _transact_X.���������_��������������� = ������� and"
<<endl<<"		_transact_X.�����_���������� = "<<getName().c_str()
<<endl<<"			first"
<<endl	 
<<endl
<<endl<<"	_block"
<<endl<<"		  Choice from 1=1"
<<endl<<"			first"
<<endl<<"		Convert_rule	"
<<endl<<"		 �����������_��������� set _block.�����������_��������� + 1"
<<endl	 
<<endl<<"$End";

}
