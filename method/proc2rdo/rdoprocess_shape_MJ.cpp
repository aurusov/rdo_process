#include "stdafx.h"
#include "rdoprocess_shape_MJ.h"
#include "rdoprocess_method_proc2rdo_MJ.h"
#include "rdoprocess_shape_process_MJ.h" 
#include "rdoprocess_shape_create_MJ.h"
#include "rdoprocess_shape_terminate_MJ.h"
#include "rdoprocess_shape_resource.h"

// ----------------------------------------------------------------------------
// ---------- RPObjectFlowChart_MJ
// ----------------------------------------------------------------------------
RPObjectFlowChart_MJ::RPObjectFlowChart_MJ( RPObject* parent ):
	RPObjectFlowChart( parent ),
	RPObject_MJ( get_this() )
{
/*
	RPShapeCreateMJ* shape_create = new RPShapeCreateMJ( this );
	shape_create->setPosition( 100, 100 );
	shape_create->gamount = 1000;
	shape_create->gname   = "�������_�����";
	shape_create->setName( std::string("�������_�����") );
	shape_create->gtype = 2;
	shape_create->gmin  = 10;
	shape_create->gmax  = 30;
	
	RPShapeProcessMJ* shape_process = new RPShapeProcessMJ( this );
	shape_process->setPosition( 100, 150 );
	shape_process->setName( std::string("���������_������") );
	shape_process->gtype = 3;
	shape_process->gexp  = 7;

	shape_process = new RPShapeProcessMJ( this );
	shape_process->setPosition( 100, 200 );
	shape_process->gtype = 1;
	shape_process->gdisp = 2;
	shape_process->gexp  = 15;

	shape_process = new RPShapeProcessMJ( this );
	shape_process->setPosition( 100, 250 );
	shape_process->setName( std::string("���������_�����") );
	shape_process->gtype = 3;
	shape_process->gexp  = 5;

	RPShapeTerminateMJ* shape_terminate = new RPShapeTerminateMJ( this );
	shape_terminate->setPosition( 100, 200 );
	shape_terminate->setName( std::string("�����") );

	RPShapeResource_MJ* shape_resource = new RPShapeResource_MJ( this );
	shape_resource->setPosition( 100, 250 );

	shape_resource = new RPShapeResource_MJ( this );
	shape_resource->setPosition( 100, 300 );
*/
}

RPObject* RPObjectFlowChart_MJ::newObject( RPObject* _parent )
{
	return new RPObjectFlowChart_MJ( _parent );
}
