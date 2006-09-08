// rdoprocess_shape_terminate_MJ.cpp: implementation of the RPShapeTerminate_MJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rdoprocess_shape_terminate_MJ.h"
#include "rdoprocess_shape_terminate_dlg1_MJ.h"
#include "rdoprocess_method_proc2rdo_MJ.h"

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

	docks.push_back( new RPConnectorDock( this, RPConnectorDock::in,  rp::point( -50, 0 ), 180, "transact" ) );
}

RPShapeTerminateMJ::~RPShapeTerminateMJ()
{
}

RPObject* RPShapeTerminateMJ::newObject( RPObject* parent )
{
	return new RPShapeTerminateMJ( parent );
}

void RPShapeTerminateMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeTerminateDlg1_MJ dlg( AfxGetMainWnd(), this );
	dlg.DoModal();
}

void RPShapeTerminateMJ::generate()
{

	//��������� ���� ���������� ��������� ��� *.opr
		CString name_value1("����_��������_");
		CString name_value2(getName().c_str());
		CString name_value(name_value1 + name_value2);
		proc2rdo->list_pattern_names.push_back(name_value);



	/*
	RDOfiles->pattern <<std::endl<<std::endl<<"��� ���������� ����� - "<<id_next
	<<std::endl<<"��� - "<<getName().c_str();
*/

// ��������� �������� ��� ���� *.res

	RPCreationRDOFilesMJ* RDOfiles = proc2rdo->RDOfiles;
	RDOfiles->resourse<<std::endl<<std::endl<<"{-------���� process ------" <<getName().c_str()<<"-------------------}" <<std::endl

	<<"Block_Del_"<<getName().c_str()<<" : Block_Del 0";






// ��������� ��������� ��� ���� *.pat


RDOfiles->pattern <<std::endl
<<std::endl<<"{-------���� ��������------------"<<getName().c_str()<<"---------------------------------}"
<<std::endl
<<std::endl
<<std::endl<<"$Pattern ����_��������_"<<getName().c_str()<<" : rule  {������������ ������}trace"
<<std::endl<<"	$Relevant_resources"
<<std::endl
<<std::endl<<"		_transact_X : Group_of_transacts_X Erase"
<<std::endl<<"		_block : Block_Del_"<<getName().c_str()<<" Keep"
<<std::endl<<"			{����������� ��� ������ ���������� ������� ��������� - ������� �������������}"
<<std::endl
<<std::endl
<<std::endl
<<std::endl<<"$Body"
<<std::endl 
<<std::endl<<"  _transact_X"
<<std::endl<<"		 Choice from _transact_X.���������_��������������� = ������� and"
<<std::endl<<"		_transact_X.�����_���������� = "<<getName().c_str()
<<std::endl<<"			first"
<<std::endl	 
<<std::endl
<<std::endl<<"	_block"
<<std::endl<<"		  Choice from 1=1"
<<std::endl<<"			first"
<<std::endl<<"		Convert_rule	"
<<std::endl<<"		 �����������_��������� set _block.�����������_��������� + 1"
<<std::endl	 
<<std::endl<<"$End";

}
