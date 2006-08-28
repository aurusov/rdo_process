#include "stdafx.h"

#define RP_METHOD_EXPORTS
#include "rdoprocess_method_algorithm.h"

#include "rdoprocess_shape_action.h"
#include "rdoprocess_shape_if.h"
#include "res/block_action.xpm"
#include "res/block_if.xpm"
#include <rdoprocess_factory.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RPMethodAlgorithm* algorithm = NULL;

// ----------------------------------------------------------------------------
// ---------- RPMethodAlgorithm
// ----------------------------------------------------------------------------
RPMethodAlgorithm::RPMethodAlgorithm( RPObject* _parent ):
	RPMethod( _parent, "��������" )
{
	algorithm = this;
}

RPMethodAlgorithm::~RPMethodAlgorithm()
{
	algorithm = NULL;
}

void RPMethodAlgorithm::registerObject()
{
	rpMethod::factory->insertFactory( new RPObjectClassInfo( getClassName(), "RPMethod" ) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPAlgorithmFlowChart", "RPObjectFlowChart", RPAlgorithmFlowChart::newObject, this, _T("��������")  ) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeAction", "RPShape", RPShapeAction::newObject, this, _T("��������"), block_action_xpm , 0) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeIf", "RPShape", RPShapeIf::newObject, this, _T("�������"), block_if_xpm, 1 ) );
}

RP_METHOD_DLL rpMethod::RPMethod* registerMethod( RPObjectFactory* _factory, RPProject* _project )
{
	rpMethod::factory = _factory;
	rpMethod::project = _project;

	RPMethodAlgorithm* method = new RPMethodAlgorithm( NULL );
	method->registerObject();

	return method;
}

RPObjectFlowChart* RPMethodAlgorithm::makeFlowChart( RPObject* parent )
{
	return new RPAlgorithmFlowChart( parent );
}

// ----------------------------------------------------------------------------
// ---------- RPAlgorithmFlowChart
// ----------------------------------------------------------------------------
RPAlgorithmFlowChart::RPAlgorithmFlowChart( RPObject* _parent ):
	RPObjectFlowChart( _parent )
{
	RPShape* shape_action = static_cast<RPShape*>(rpMethod::factory->getNewObject( "RPShapeAction", this ));
	shape_action->setPosition( 100, 45 );
	shape_action = static_cast<RPShape*>(rpMethod::factory->getNewObject( "RPShapeAction", this ));
	shape_action->setPosition( 250, 145 );
	RPShape* shape_if = static_cast<RPShape*>(rpMethod::factory->getNewObject( "RPShapeIf", this ));
	shape_if->setPosition( 300, 100 );

	after_constructor();
}

RPAlgorithmFlowChart::~RPAlgorithmFlowChart()
{
}

RPObject* RPAlgorithmFlowChart::newObject( RPObject* parent )
{
	return new RPAlgorithmFlowChart( parent );
}

rpMethod::RPMethod* RPAlgorithmFlowChart::getMethod()
{
	return algorithm;
}
