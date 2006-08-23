// rdoprocess_shape_process_MJ.cpp: implementation of the RPShapeProcessMJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
#include "rdoprocess_shape_process_MJ.h"
#include "rdoprocess_shape_process_dlg1_MJ.h"
#include "rdoprocess_method_proc2rdo_MJ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeProcessMJ::RPShapeProcessMJ( RPObject* _parent ):
	RPShape_MJ( _parent, _T("Process") )
{
	
	gname; // ���
	
	gtype = 0;
	base_gen = 1234567;
	
	//�������� �������
	gexp=0;
	gdisp=0;
	gmax=0;
	gmin=0;

	action=0; // ��� �������� �� ��������� � �������
	prior=0;
	queue=0;
	parameter=888; // ���� �� ������ ���� ��������
		
		// ������������� ���� ����� 
	type ="block";
		
	pa_src.push_back( rp::point(-50, -25) );
	pa_src.push_back( rp::point(50, -25) );
	pa_src.push_back( rp::point(50, 25) );
	pa_src.push_back( rp::point(-50, 25) );
	pa_src.push_back( rp::point(-50, -25) );

	docks.push_back( new RPConnectorDock( this, RPConnectorDock::in,  rp::point( -50, 0 ), 180 ) );
	docks.push_back( new RPConnectorDockOne( this, RPConnectorDock::out, rp::point(  50, 0 ), 0 ) );
	docks.push_back( new RPConnectorDock( this, RPConnectorDock::in,  rp::point(  0, 25), 270 ) );
}

RPShapeProcessMJ::~RPShapeProcessMJ()
{
}

RPObject* RPShapeProcessMJ::newObject( RPObject* parent )
{
	return new RPShapeProcessMJ( parent );
}

void RPShapeProcessMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	if ( rpMethod::project->lockResource( proc2rdo ) ) {
		RPShapeProcessDlg1_MJ dlg( CWnd::FromHandle(rpMethod::project->getMainWnd()), this );
		dlg.DoModal();
		rpMethod::project->unlockResource();
	}
//	project->list_name();
}

void RPShapeProcessMJ::list_name()
{
	TRACE( "*** Process ***\n" );
}


// // ��������� �������� ��� ���� *.fun
void RPShapeProcessMJ::define_rule()
{
	RPCreationRDOFilesMJ* RDOfiles = proc2rdo->RDOfiles;
		int cur = gtype;
		CString rule;
		switch(cur) // ���������� �������� ���� ������ �� ������
		{
	case 0: // ��������� 

	RDOfiles->pattern<<gexp;

				break;	

	case 1: // ����������
	
	RDOfiles->pattern<<"����������_�����_" <<getName().c_str()<<"("<<gexp<<","<<gdisp<<")";
		

	RDOfiles->function
	<<std::endl<<std::endl<<std::endl<<"$Sequence ����������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = normal "<<base_gen
	<<std::endl<<"$End";
						break;
						
	case 2: // ����������� �����
	
		
	RDOfiles->pattern
	<<"�����������_�����_" <<getName().c_str()<<"("<<gmin<<","<<gmax<<")";
	
	RDOfiles->function
	<<std::endl<<std::endl<<std::endl<<"$Sequence �����������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = uniform "<<base_gen
	<<std::endl<<"$End";
			break;
	case 3: // ����������������
	RDOfiles->pattern
	<<"����������������_�����_" <<getName().c_str()<<"("<<gexp<<")";

	RDOfiles->function
	<<std::endl<<std::endl<<std::endl<<"$Sequence ����������������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = exponential "<<base_gen
	<<std::endl<<"$End";
						break;

		}


}

void RPShapeProcessMJ::generate()
{
	RPShape_MJ::generate();

	RPCreationRDOFilesMJ* RDOfiles = proc2rdo->RDOfiles;

	//��������� ���� ���������� ��������� ��� *.opr
		CString name_value1("����_����������_�_�������_");
		CString name_value2(getName().c_str());
		CString name_value(name_value1 + name_value2);
		proc2rdo->list_pattern_names.push_back(name_value);

		name_value1 = "����_�������_��_�������_�_��������_";
		name_value2 = getName().c_str();
		name_value = name_value1 + name_value2;
		proc2rdo->list_pattern_names.push_back(name_value);

		name_value1 = "����_���������_";
		name_value2 = getName().c_str();
		name_value = name_value1 + name_value2;
		proc2rdo->list_pattern_names.push_back(name_value);



	// ��������� ���������� ��� ���� *.pmd
	RDOfiles->statistic

	<<std::endl<<"���������_�����_" <<getName().c_str()<<
	  ":  watch_state"<<" Block_process_"<<getName().c_str()<<".��������� = �����"

	<<std::endl<<"�������_�����_" <<getName().c_str()<<
	  ":  watch_par"<<" Queue_"<<getName().c_str()<<".������_�������";



// ��������� �������� ��� ���� *.res
	RDOfiles->resourse<<std::endl<<std::endl<<"{-------���� process ------" <<getName().c_str()<<"-------------------}" <<std::endl

	<<"Block_process_"<<getName().c_str()<<" : Block_process ��������"
	<<std::endl<<"Queue_"<<getName().c_str()<<": Queue trace 0 �������� {���-�� ������� � ������� � ��������� �������� ������� }";


// ��������� ��������� ��� ���� *.pat
RDOfiles->pattern <<std::endl<<std::endl<<"{---------���������� � ��������--------"<<getName().c_str()<<"-----------------------}"
<<std::endl

	<<std::endl<<"$Pattern ����_����������_�_�������_"<<getName().c_str()<<" : rule {}trace"
	<<std::endl<<"$Relevant_resources"
	<<std::endl<<"	 _transact  : Group_of_transacts_X  Keep"
	<<std::endl<<"	_block     : Queue_"<<getName().c_str()<<" Keep"
	<<std::endl
	<<std::endl<<"$Body"
	<<std::endl<<"_transact"
	<<std::endl<<"Choice from   _transact.���������_��������������� = ������� and" 
	<<std::endl<<"	_transact.�����_���������� = "<<getName().c_str()<<" and _transact.�����_����������_������� = "<<getName().c_str()
	<<std::endl<<"	first"
	<<std::endl<<"Convert_rule "
	<<std::endl<<"	���������_��������������� set �_�������"
	<<std::endl	
	<<std::endl<<"_block"
	<<std::endl<<"Choice from 1=1"
	<<std::endl<<"first"
	<<std::endl<<"	Convert_rule"
	<<std::endl<<"	������_������� set _block.������_������� + 1"
	<<std::endl<<"$End"
	<<std::endl

	//------------------------------------------------
	
	<<std::endl<<"{---------������������ �� �������------"<<getName().c_str()<<"---------------}"<<std::endl
	<<std::endl<<"$Pattern ����_�������_��_�������_�_��������_"<<getName().c_str()<<" : rule {}trace"
	<<std::endl
	<<std::endl<<"$Relevant_resources"
	<<std::endl<<"	_transact  : Group_of_transacts_X  Keep"
	<<std::endl<<"	_block     : Queue_"<<getName().c_str()<<" Keep"
	<<std::endl<<"	_block_proc : Block_process_"<<getName().c_str()<<" NoChange";


	// ������������ ���������
	std::list<CString>::iterator it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	RDOfiles->pattern <<std::endl
	<<std::endl<<"_resource_"<<(*it)<<" : Resource_"<<(*it)<<" NoChange";

	it++;
	}


	RDOfiles->pattern <<std::endl

	<<std::endl<<"	$Body"
	<<std::endl<<"_transact"
	<<std::endl<<"	Choice from   _transact.���������_��������������� = �_������� and" 
	<<std::endl<<"	_transact.�����_���������� = "<<getName().c_str()<<" and _transact.�����_����������_������� = "<<getName().c_str()
	<<std::endl<<"		first"
	<<std::endl<<"	Convert_rule" 
	<<std::endl<<"		���������_��������������� set �_�������_�����"
	<<std::endl<<"		�����_����������_������� set "<<id_next.c_str()
	<<std::endl
	<<std::endl<<"_block"
	<<std::endl<<"	Choice from _block.�����_������� = ��������"
	<<std::endl<<"		first"
	<<std::endl<<"	Convert_rule"
	<<std::endl<<"		������_������� set _block.������_������� - 1"
	<<std::endl<<"		�����_������� set �����"
	<<std::endl
	<<std::endl<<"_block_proc"
	<<std::endl<<"	Choice from 1=1"
	<<std::endl<<"		first"
	<<std::endl;

	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	RDOfiles->pattern <<std::endl


	<<std::endl<<"_resource_"<<(*it) 
    <<std::endl<<"	Choice from" 
	<<std::endl<<"	_resource_"<<(*it)<<".���������=��������"
	<<std::endl<<"		first";

	it++;
	}


RDOfiles->pattern
	<<std::endl<<"$End"
	
	//----------------------------------------------------------------------------
		
	<<std::endl<<"{---------�������-----"<<getName().c_str()<<"----------------}"<<std::endl



	<<std::endl<<"$Pattern ����_���������_"<<getName().c_str()<<" : operation  {������������ ������}trace"
	<<std::endl<<"	$Relevant_resources"
	<<std::endl<<"	{��������������� ��� ���� ��������}"
	<<std::endl<<"_block_queue     : Queue_"<<getName().c_str()<<" Keep NoChange"
	<<std::endl
	<<std::endl
	<<std::endl

	<<std::endl<<"	{��� ����������� ����������� �������, ������� �������� �������� ����� � "
	<<std::endl<<"	�����, � ���� ��� ������ ���� �������� �� ������}"
	<<std::endl
	<<std::endl;

// ������������ ���������
 it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	RDOfiles->pattern <<std::endl
	<<std::endl<<"_resource_"<<(*it)<<" : Resource_"<<(*it)<<" Keep Keep";

	it++;
	}



RDOfiles->pattern <<std::endl
	<<std::endl<<"	{����������� ��� ������ ���������� ������� ��������� - ������� �������������}"
	<<std::endl<<"_transact_X : Group_of_transacts_X Keep Keep"
	<<std::endl<<"_block : Block_process_"<<getName().c_str()<<" Keep Keep"
	<<std::endl
	<<"$Time = ";
	define_rule(); // ������� ����� ��������� ����� � ���������� ��� ����� � *.fun
	RDOfiles->pattern<<" {����� ������������ ����������������� ��������}"
	<<std::endl
	<<std::endl
	<<std::endl<<"$Body"
	<<std::endl
	<<std::endl<<"_block_queue"
	<<std::endl<<"	Choice from _block_queue.�����_������� = ����� "
	<<std::endl<<"		first"
	<<std::endl<<"	Convert_begin"
	<<std::endl<<"		�����_������� set ��������"
    <<std::endl
	<<std::endl
	  
	<<std::endl<<"_transact_X"	
	<<std::endl<<"	Choice from _transact_X.���������_��������������� = �_�������_����� and"
	<<std::endl<<"	_transact_X.�����_���������� = "<<getName().c_str() 
	<<std::endl<<"		first"
	<<std::endl<<"	Convert_begin"
	
	
	<<std::endl<<"		���������_��������������� set ��������"
	<<std::endl<<"		�����_����������_������� set "<<id_next.c_str()
	<<std::endl
	<<std::endl<<"	Convert_end"
	<<std::endl<<"		���������_��������������� set �������"
	
	
	<<std::endl<<"{����� ������� ��������� ����� �������� �� ���� ������������ ��������}	"
	<<std::endl<<std::endl;




//�������� ��������
	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	RDOfiles->pattern <<std::endl


	<<std::endl<<"_resource_"<<(*it) 
    <<std::endl<<"	Choice from" 
	<<std::endl<<"	_resource_"<<(*it)<<".���������=��������"
	<<std::endl<<"		first"
    <<std::endl<<"	Convert_begin"
	<<std::endl<<"		�����������_���������� set _resource_"<<(*it)<<".�����������_���������� + 1"
	<<std::endl<<"		���������              set" 
	<<std::endl<<"		fun_resource_"<<(*it)<<"(_resource_"<<(*it)<<".�����������_����������,_resource_"<<(*it)<<".���������,"
	<<std::endl<<"		_resource_"<<(*it)<<".������_�����������)"
	<<std::endl
    <<std::endl<<"	Convert_end"
	<<std::endl<<"		�����������_���������� set _resource_"<<(*it)<<".�����������_���������� - 1"
	<<std::endl<<"		���������              set" 
	<<std::endl<<"		fun_resource_"<<(*it)<<"(_resource_"<<(*it)<<".�����������_����������,_resource_"<<(*it)<<".���������,"
	<<std::endl<<"		_resource_"<<(*it)<<".������_�����������)";

	it++;
	}




RDOfiles->pattern <<std::endl<<std::endl

	<<std::endl<<"_block"
	<<std::endl<<"  Choice from"
	<<std::endl<<"  1=1"
	<<std::endl<<"		first"
	<<std::endl<<"	Convert_begin"
	<<std::endl<<"		��������� set �����" 
	
			/*
	fun_resource_"<<getName().c_str()<<"_seize(";


it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	it++;
	if(it==list_resource_procMJ.end())
	{
	it--;
		RDOfiles->pattern <<std::endl
		<<std::endl<<"_resource_"<<(*it)<<".���������";
	}
	else
	{
	it--;
		RDOfiles->pattern <<std::endl
		<<std::endl<<"_resource_"<<(*it)<<".���������,";
	}

	it++;
	}

    RDOfiles->pattern <<")"<<std::endl


*/

	<<std::endl<<"Convert_end  "
    <<std::endl<<std::endl<<"		��������� set �������� "
	/*
	fun_resource_"<<getName().c_str()<<"_seize(";


	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	it++;
	if(it==list_resource_procMJ.end())
	{
	it--;
		RDOfiles->pattern <<std::endl
		<<std::endl<<"_resource_"<<(*it)<<".���������";
	}
	else
	{
	it--;
		RDOfiles->pattern <<std::endl
		<<std::endl<<"_resource_"<<(*it)<<".���������,";
	}

	it++;
	}

    RDOfiles->pattern <<")"<<std::endl

  */
	<<std::endl<<"$End";


// ��������� ������� ��� ���� *.fun ��� �-�� ��������� �������� �� ����, ��� � ����� ��������� ������
RDOfiles->function<<std::endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<std::endl

	<<std::endl<<"$Function  fun_resource_"<<getName().c_str()<<"_seize : such_as Block_process.���������"
	<<std::endl<<"$Type = algorithmic"
	<<std::endl<<"$Parameters";
	
		it = list_resource_procMJ.begin();
		while( it != list_resource_procMJ.end() ) 
		{
			
	RDOfiles->function 
	<<std::endl<<"		_resource_"<<(*it)<<": such_as Resource.���������";
		it++;
		}
	
	RDOfiles->function 
	<<std::endl<<"	$Body";
	
		it = list_resource_procMJ.begin();
		while( it != list_resource_procMJ.end() ) 
		{
			
	RDOfiles->function 
	<<std::endl<<"	Calculate_if _resource_"<<(*it)<<" = ����� fun_resource_"<<getName().c_str()<<"_seize = �����";
		it++;
		}
	
	RDOfiles->function 
	<<std::endl  
	<<std::endl<<"  Calculate_if 1=1 fun_resource_"<<getName().c_str()<<"_seize=��������"
	<<std::endl
	<<std::endl<<"	$End";	




}