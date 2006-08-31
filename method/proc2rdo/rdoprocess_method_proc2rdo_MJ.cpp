#include "stdafx.h"
#include "rdoprocess_method_proc2rdo_MJ.h"
#include "rdoprocess_shape_create_MJ.h"
#include "rdoprocess_shape_resource.h"
#include "rdoprocess_shape_process_MJ.h"
#include "rdoprocess_shape_terminate_MJ.h"
#include "rdoprocess_generation_type_MJ.h"
#include "../../resource.h"
#include "res/method_big.xpm"
#include "res/method_small.xpm"
#include "res/generate.xpm"
#include "res/generate_setup.xpm"
#include "res/block_create.xpm"
#include "res/block_terminate.xpm"
#include "res/block_process.xpm"
#include "res/block_resource.xpm"

#include <rdoprocess_object_chart.h>
#include <rdoprocess_shape.h>
#include <rdoprocess_toolbar.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RPMethodProc2RDO_MJ* proc2rdo = NULL;

RPMethodProc2RDO_MJ::RPMethodProc2RDO_MJ( RPObject* _parent ):
	rpMethod::RPMethod( _parent, "���-�������" ),
	RPObject_MJ( get_this() ),
	btn_generate( -1 ),
	btn_generate_setup( -1 ),
	RDOfiles( NULL ) // �������������
{
	proc2rdo = this;
	generate_time_MJ = 100;
	RDOfiles = new RPCreationRDOFilesMJ();
	pixmap_big   = rpMethod::project->createBitmap( method_big_xpm );
	pixmap_small = rpMethod::project->createBitmap( method_small_xpm );
}

RPMethodProc2RDO_MJ::~RPMethodProc2RDO_MJ()
{
	delete RDOfiles;
	proc2rdo = NULL;
}

void RPMethodProc2RDO_MJ::registerObject()
{
	// ������� �����
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPObject_MJ", NULL ) );

	// ������� RPMethod
	RPObjectClassInfo* class_info = new RPObjectClassInfo( "RPMethodProc2RDO_MJ", "RPMethod" );
	class_info->multiParent( "RPObject_MJ" );
	rpMethod::factory->insertFactory( class_info );

	// ������� RPObjectFlowChart
	class_info = new RPObjectClassInfo( "RPObjectFlowChart_MJ", "RPObjectFlowChart", RPObjectFlowChart_MJ::newObject, this, _T("���-�������") );
	class_info->multiParent( "RPObject_MJ" );
	rpMethod::factory->insertFactory( class_info );

	// ������� RPShape
	class_info = new RPObjectClassInfo( "RPShape_MJ", "RPShape" );
	class_info->multiParent( "RPObject_MJ" );
	rpMethod::factory->insertFactory( class_info );

	// ������� RPShape_MJ
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeCreateMJ", "RPShape_MJ", RPShapeCreateMJ::newObject, this, _T("���������"), block_create_xpm, 0 ) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeTerminateMJ", "RPShape_MJ", RPShapeTerminateMJ::newObject, this, _T("����������"), block_terminate_xpm, 1 ) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeProcessMJ", "RPShape_MJ", RPShapeProcessMJ::newObject, this, _T("�������"), block_process_xpm, 2 ) );
	rpMethod::factory->insertFactory( new RPObjectClassInfo( "RPShapeResource_MJ", "RPShape_MJ", RPShapeResource_MJ::newObject, this, _T("������"), block_resource_xpm, 3 ) );

	RPCtrlToolbar* toolbar = rpMethod::project->createToolBar( _T("���-�������") );
	btn_generate       = toolbar->insertButton( this, generate_xpm, _T("������� ������") );
	btn_generate_setup = toolbar->insertButton( this, generate_setup_xpm, _T("���������") );
}

rpMethod::RPMethod* RPMethodProc2RDO_MJ::registerMethod()
{
	new RPMethodProc2RDO_MJ( NULL );
	proc2rdo->registerObject();

	return proc2rdo;
}

RPObjectFlowChart* RPMethodProc2RDO_MJ::makeFlowChart( RPObject* parent )
{
	return new RPObjectFlowChart_MJ( parent );
}

void RPMethodProc2RDO_MJ::buttonCommand( int button_id )
{
	if ( button_id == btn_generate ) {
		generate();
	} else if ( button_id == btn_generate_setup ) {
		RP_GENERATION_TYPE_MJ dlg( AfxGetMainWnd() );
		dlg.DoModal();	
	}
}

void RPMethodProc2RDO_MJ::buttonUpdate( RPCtrlToolbar::ButtonUpdate& button_update )
{
	button_update.enable = true;
}

void RPMethodProc2RDO_MJ::generate()
{
	RDOfiles->pattern.open("aaa\\RDO_PROCESS.pat");
	RDOfiles->resourse.open("aaa\\RDO_PROCESS.rss");
	RDOfiles->function.open("aaa\\RDO_PROCESS.fun");

	RDOfiles->typeres.open("aaa\\RDO_PROCESS.rtp");
	RDOfiles->operations.open("aaa\\RDO_PROCESS.opr");
	RDOfiles->smr.open("aaa\\RDO_PROCESS.smr");
	RDOfiles->statistic.open("aaa\\RDO_PROCESS.pmd");

	blank_rdo_MJ();

	// ��������� ID
	std::list< RPObject* > all_child;
	std::list< rp::string > class_names;
	class_names.push_back( "RPShapeCreateMJ" );
	class_names.push_back( "RPShapeProcessMJ" );
	class_names.push_back( "RPShapeTerminateMJ" );
	rpMethod::project->getAllChildByClasses( all_child, class_names, true );
	std::list< RPObject* >::const_iterator block_it = all_child.begin();
	while ( block_it != all_child.end() ) {
		std::list< RPShape* > list = static_cast<RPShape*>(*block_it)->getNextBlock();
		if ( !list.empty() ) {
			dynamic_cast<RPObject_MJ*>(*block_it)->id_next = list.front()->getName();
			rp::string s = dynamic_cast<RPObject_MJ*>(*block_it)->id_next;
		}
		block_it++;
	}

	// ������� ��������� � ��������
	all_child.clear();
	rpMethod::project->getAllChildByClass( all_child, "RPShape_MJ", true );
	std::list< RPObject* >::iterator shape_it = all_child.begin();
	while ( shape_it != all_child.end() ) {
		dynamic_cast<RPObject_MJ*>(static_cast<RPShape_MJ*>(*shape_it))->generate();
		shape_it++;
	}

	RDOfiles->pattern.close();

	RDOfiles->resourse<<std::endl<<std::endl<<"$End";
	RDOfiles->resourse.close();

	RDOfiles->function.close();
	RDOfiles->typeres.close();

	RDOfiles->smr.close();

	RDOfiles->statistic<<
	std::endl<<"$End";
	RDOfiles->statistic.close();

	//�������������  �������� *.opr ��� �.�. ������ ���� ��� �������������� ��� �����

		list_pattern_names.push_back("����_��������_�������������_��_�������");

					RDOfiles->operations<<"$Operations";

				std::list<CString>::iterator it = list_pattern_names.begin();
				  int amount = 1;	

				  while( it != list_pattern_names.end() ) 
					{
					TRACE( "%s\n", (*it) );
					RDOfiles->operations<<std::endl
					<<std::endl<<"operation_"<<amount<<" : "<<(*it);

					it++; amount++;
					}


					RDOfiles->operations
					<<std::endl<<"$End";
list_pattern_names.clear();

	RDOfiles->operations.close();
}

void RPMethodProc2RDO_MJ::blank_rdo_MJ()
{
//������������� ����� ��������� *.rtp
RDOfiles->typeres
<<std::endl	
<<std::endl<<"{ res }"
<<std::endl<<"$Resource_type Resource : permanent {��������� ����� Create}"
<<std::endl<<"$Parameters"
<<std::endl<<"��������� : (�����,��������)"
<<std::endl<<"�����������_���������� : integer {������� ������������� ���������� � ������� ������}"
<<std::endl<<"������_����������� : integer {���� ����������� ������� ����� �������������"
<<std::endl<<"����� �������� ������� ��������� � ��������� �����}"
<<std::endl<<"$End"
<<std::endl
<<std::endl
<<std::endl
<<std::endl
<<std::endl
<<std::endl<<"{1}"
<<std::endl<<"$Resource_type Creates : permanent {��������� ����� Create}"
<<std::endl<<"$Parameters"
<<std::endl<<"  par_1 : (true, false) {false} {�������� � ��������� ������� ������}"
<<std::endl<<"  par_amount: integer   {1}     {������� ����������� ���} "
<<std::endl<<"$End"
<<std::endl
<<std::endl
<<std::endl
<<std::endl<<"$Resource_type Group_of_transacts_X : temporary    {��������� ������������ ���������}"
<<std::endl<<"$Parameters"
<<std::endl<<"   {��������� ��������� �������� �������������"
<<std::endl<<"    � ������������ �������������}"
<<std::endl
<<std::endl<<"{ ��������� ����� ���������� }"
<<std::endl
<<std::endl<<"	�����_���������� :(";

	std::list< RPObject* > blocks;
	rpMethod::project->getAllChildByClass( blocks, "RPShape_MJ", true );
	std::list< RPObject* >::const_iterator it = blocks.begin();
	while ( it != blocks.end() ) {
		RDOfiles->typeres << (*it)->getName() << ", ";
		it++;
	}

RDOfiles->typeres<<"������_����_���������)"


<<std::endl<<"	�����_����������_������� : such_as  Group_of_transacts_X.�����_���������� {ID ������, ���� ����������� ���������� �� ���� ����}"
<<std::endl
<<std::endl	
<<std::endl
<<std::endl<<"{ C�������� ���������}	"
<<std::endl<<"	���������_��������� : integer {}"
<<std::endl
<<std::endl
<<std::endl<<"{PRIMARY KEY}"
<<std::endl<<"    �����������������_�����_��������� : integer"
<<std::endl<<"    �����������������_�����_������_���������� : such_as  Group_of_transacts_X.�����_����������"
<<std::endl<<"{-----------}"
<<std::endl
<<std::endl<<"	�����_�_������� : integer"
<<std::endl<<"	���������_��������������� : (�������, ��������, �_�������, �_�������_�����)"
<<std::endl
<<std::endl<<"{ �������������� ��������� �������������� �������������}"
<<std::endl
<<std::endl<<"{" 
<<std::endl<<"... : ..."
<<std::endl<<" }"
<<std::endl<<"$End "
<<std::endl 
<<std::endl<<" {2 �������}"
<<std::endl<<" $Resource_type Queue : permanent"
<<std::endl<<"$Parameters"
<<std::endl<<"  ������_������� : integer"
<<std::endl<<"	 �����_�������: (��������, �����)"
<<std::endl<<"$End"
<<std::endl
<<std::endl
<<std::endl<<"{3 �������}"
<<std::endl<<"$Resource_type Block_process : permanent {��������� ����� Create}"
<<std::endl<<"$Parameters"
<<std::endl<<"  ��������� : (�����,��������)"
<<std::endl<<"$End"
<<std::endl
<<std::endl<<"{4del}"
<<std::endl<<" $Resource_type Block_Del : permanent"
<<std::endl<<"$Parameters"
<<std::endl<<"  �����������_��������� : integer"
<<std::endl
<<std::endl<<"$End";


//�������������  ��������� *.rtp
RDOfiles->resourse<<"$Resources";


//�������������  ���������� *.pmd
RDOfiles->statistic<<

std::endl<<"$Results";



//�������������  SMR *.smr
RDOfiles->smr<<
std::endl<<"Model_name = RDO_PROCESS"
<<std::endl
<<std::endl<<"Resource_file  = RDO_PROCESS"
<<std::endl<<"OprIev_file    = RDO_PROCESS" // OPR
<<std::endl<<"Trace_file     = RDO_PROCESS"
<<std::endl<<"Statistic_file = RDO_PROCESS" //PMD
<<std::endl<<"Results_file   = RDO_PROCESS"
//<<std::endl<<"Frame_file     = RDO_PROCESS"
//<<std::endl<<"Frame_number   = 1"
//<<std::endl<<"Show_mode      = Animation"
//<<std::endl<<"Show_rate      = 10000000.0"
<<std::endl
<<std::endl<<"Terminate_if  Time_now >= "<< generate_time_MJ;



// ������������� ������� � *.pat ��������� ����� �����������
list_pattern_names.push_back("����_�����������");// ��������� ��� ��� *.opr

RDOfiles->pattern
<<"{----------------��������� ����� �����������-------------------------------------------}"
<<std::endl<<"$Pattern ����_����������� : rule  {������������ ������}trace"
<<std::endl<<"	$Relevant_resources"
<<std::endl<<"		_transact_X : Group_of_transacts_X Keep"
<<std::endl
<<std::endl<<"	$Body"
<<std::endl
<<std::endl<<"	_transact_X"
<<std::endl<<"		Choice from _transact_X.���������_��������������� = �������  and"
<<std::endl<<"		_transact_X.�����_����������_�������<>_transact_X.�����_���������� "
<<std::endl<<"	first"
<<std::endl
<<std::endl<<"	Convert_rule"
<<std::endl<<"		�����_���������� set  _transact_X.�����_����������_�������"
<<std::endl
<<std::endl<<"	$End";


RDOfiles->pattern
<<std::endl<<"{----------------��������� ���� ��������������� �� �������-------------------------------------------}"
<<std::endl
<<std::endl<<"$Pattern  ����_��������_�������������_��_������� : irregular_event trace "
<<std::endl<<"$Relevant_resources"
<<std::endl<<"_parameter : Group_of_transacts_X  NoChange {����� ��� ����, ��� ��� ���� ������}"
<<std::endl<<"$Time ="<< generate_time_MJ
<<std::endl<<"$Body"
<<std::endl<<"_parameter"
<<std::endl<<"$End";
}
