// rdoprocess_shape_resource.cpp: implementation of the RPShapeResource_MJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "rdo_process.h"
#include "rdoprocess_shape_resource.h"
#include "rdoprocess_shape_resource_DLG1_MJ.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeResource_MJ::RPShapeResource_MJ( RPObject* _parent ):
	RPShape( _parent, _T("Resource") )
{
	
	gamount=1;

	// ������������� ���� ����� 

	type ="resource";

	pa_src.push_back( rp::point(-50, -10) );
	pa_src.push_back( rp::point(-35, -25) );
	pa_src.push_back( rp::point(35, -25) );
	pa_src.push_back( rp::point(50, -10) );
	pa_src.push_back( rp::point(50, 10) );
	pa_src.push_back( rp::point(35, 25) );
	pa_src.push_back( rp::point(-35, 25) );
	pa_src.push_back( rp::point(-50, 10) );
	pa_src.push_back( rp::point(50, 10) );
	pa_src.push_back( rp::point(-50, 10) );
	pa_src.push_back( rp::point(-50, -10) );
	pa_src.push_back( rp::point(50, -10) );
	pa_src.push_back( rp::point(-50, -10) );

/*
	pa_src.push_back( rp::point(-50, -10) );
	pa_src.push_back( rp::point(-35, -25) );
	pa_src.push_back( rp::point(35, -25) );
	pa_src.push_back( rp::point(50, -10) );
	pa_src.push_back( rp::point(50, 10) );

	pa_src.push_back( rp::point(35, 25) );
	pa_src.push_back( rp::point(-35, 25) );
	pa_src.push_back( rp::point(-50, 10) );
	pa_src.push_back( rp::point(-50, -10) );

	pa_src.push_back( rp::point(50, -10) );
	pa_src.push_back( rp::point(50, 10) );
	pa_src.push_back( rp::point(-50, 10) );
*/
	docks.push_back( new RPConnectorDockResource( this, RPConnectorDock::out,  rp::point( 0, -25 ), 90 ) );
}

RPShapeResource_MJ::~RPShapeResource_MJ()
{

}

void RPShapeResource_MJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeResourceDLG1_MJ dlg(NULL,this);
	dlg.DoModal();
}

void RPShapeResource_MJ::generate_MJ()
{
	/*rpapp.RDOfiles->pattern <<endl<<endl<<"��� ���������� ����� - "<<id_next
	<<endl<<"��� - "<<getName().c_str()
	<<endl<<"����� ����� ����������� ������������ - "<<gamount;
*/

	// ��������� ���������� ��� ���� *.pmd
	rpapp.RDOfiles->statistic

	<<endl<<"���������_�������_" <<getName().c_str()<<
	  ":  watch_state "<<"Resource_"<<getName().c_str()<<".��������� = �����";




	
// ��������� ������� ��� ���� *.fun
rpapp.RDOfiles->function<<endl<<"{-------������ ------" <<getName().c_str()<<"-------------------}" <<endl
	
	
	
	
<<endl<<"$Function  fun_resource_" <<getName().c_str()<<" : such_as Resource.��������� {������������ ��� ������� �������}"
<<endl<<"	$Type = algorithmic"
<<endl<<"	$Parameters"
<<endl<<"		 _amount        : integer {������� ���������� ��� �������������}"
<<endl<<"		 _state         : such_as Resource.��������� {�������� �������}"
<<endl<<"		 _max           : integer      { ���� ����������� ������� ����� �������������"
<<endl<<"����� �������� ������� ��������� � ��������� �����}"
<<endl
<<endl<<"$Body"
<<endl<<"	Calculate_if _amount >= _max and _state = ��������"
<<endl<<"		fun_resource_" <<getName().c_str()<<" = �����"
<<endl<<"	{�������� ���� ���-�� ��������� ��������}"
<<endl 
<<endl<<"	Calculate_if _amount < _max and _state = �����"
<<endl<<"		fun_resource_" <<getName().c_str()<<" = ��������"
<<endl    
<<endl<<"	Calculate_if 1=1"
<<endl<<"		fun_resource_" <<getName().c_str()<<" = _state"
<<endl
<<endl<<"$End";



// ��������� �������� ��� ���� *.res
rpapp.RDOfiles->resourse<<endl<<endl<<"{-------������ ------" <<getName().c_str()<<"-------------------}" <<endl

<<"Resource_"<<getName().c_str()<<" : Resource �������� 0 1";








}
