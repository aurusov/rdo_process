// rdoprocess_shape_resource.cpp: implementation of the RPShapeResource_MJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rdoprocess_shape_resource.h"
#include "rdoprocess_shape_resource_DLG1_MJ.h"
#include "rdoprocess_method_proc2rdo_MJ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// ---------- RPConnectorDockResourceOut
// ----------------------------------------------------------------------------
class RPConnectorDockResourceOut: public RPConnectorDock
{
public:
	RPConnectorDockResourceOut( RPShape* _parent, Type _type, const rp::point& _point, double _norm, const rp::string& type = "" ): RPConnectorDock( _parent, _type, _point, _norm, type ) {};
	virtual ~RPConnectorDockResourceOut() {};

	virtual RPConnector* make_connector( RPObject* _parent ) {
		RPConnector* conn = RPConnectorDock::make_connector( _parent );
		conn->setPen( CPen(PS_DOT, 1, RGB(0x00, 0x00, 0x80)) );
		return conn;
	}
};

// ----------------------------------------------------------------------------
// ---------- RPShapeResource_MJ
// ----------------------------------------------------------------------------
RPShapeResource_MJ::RPShapeResource_MJ( RPObject* _parent ):
	RPShape_MJ( _parent, _T("Resource") )
{
	
	gamount=1;

	// ������������� ���� ����� 

	type ="resource";

	main_pen_default.DeleteObject();
	main_pen_default.CreatePen( PS_SOLID, main_pen_width, RGB( 0x00, 0x00, 0x00 ) );
	setPen( main_pen_default );
	bg_brush.DeleteObject();
	bg_brush.CreateSolidBrush( RGB(0xF0, 0xF0, 0xF0) );

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
	docks.push_back( new RPConnectorDockResourceOut( this, RPConnectorDock::out,  rp::point( 0, -25 ), 90, "resource" ) );
}

RPShapeResource_MJ::~RPShapeResource_MJ()
{
}

RPObject* RPShapeResource_MJ::newObject( RPObject* parent )
{
	return new RPShapeResource_MJ( parent );
}

void RPShapeResource_MJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeResourceDLG1_MJ dlg( AfxGetMainWnd(), this );
	dlg.DoModal();
}

void RPShapeResource_MJ::generate()
{
	/*RDOfiles->pattern <<std::endl<<std::endl<<"��� ���������� ����� - "<<id_next
	<<std::endl<<"��� - "<<getName().c_str()
	<<std::endl<<"����� ����� ����������� ������������ - "<<gamount;
*/

	RPCreationRDOFilesMJ* RDOfiles = proc2rdo->RDOfiles;

	// ��������� ���������� ��� ���� *.pmd
	RDOfiles->statistic

	<<std::endl<<"���������_�������_" <<getName().c_str()<<
	  ":  watch_state "<<"Resource_"<<getName().c_str()<<".��������� = �����";




	
// ��������� ������� ��� ���� *.fun
RDOfiles->function<<std::endl<<"{-------������ ------" <<getName().c_str()<<"-------------------}" <<std::endl
	
	
	
	
<<std::endl<<"$Function  fun_resource_" <<getName().c_str()<<" : such_as Resource.��������� {������������ ��� ������� �������}"
<<std::endl<<"	$Type = algorithmic"
<<std::endl<<"	$Parameters"
<<std::endl<<"		 _amount        : integer {������� ���������� ��� �������������}"
<<std::endl<<"		 _state         : such_as Resource.��������� {�������� �������}"
<<std::endl<<"		 _max           : integer      { ���� ����������� ������� ����� �������������"
<<std::endl<<"����� �������� ������� ��������� � ��������� �����}"
<<std::endl
<<std::endl<<"$Body"
<<std::endl<<"	Calculate_if _amount >= _max and _state = ��������"
<<std::endl<<"		fun_resource_" <<getName().c_str()<<" = �����"
<<std::endl<<"	{�������� ���� ���-�� ��������� ��������}"
<<std::endl 
<<std::endl<<"	Calculate_if _amount < _max and _state = �����"
<<std::endl<<"		fun_resource_" <<getName().c_str()<<" = ��������"
<<std::endl    
<<std::endl<<"	Calculate_if 1=1"
<<std::endl<<"		fun_resource_" <<getName().c_str()<<" = _state"
<<std::endl
<<std::endl<<"$End";



// ��������� �������� ��� ���� *.res
RDOfiles->resourse<<std::endl<<std::endl<<"{-------������ ------" <<getName().c_str()<<"-------------------}" <<std::endl

<<"Resource_"<<getName().c_str()<<" : Resource �������� 0 1";








}
