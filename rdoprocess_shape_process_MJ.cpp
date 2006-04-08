// rdoprocess_shape_process_MJ.cpp: implementation of the RPShapeProcessMJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <list>
//#include "rdo_process.h"
#include "rdoprocess_shape_process_MJ.h"
#include "rdoprocess_shape_process_dlg1_MJ.h"
#include "rdoprocess_app.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeProcessMJ::RPShapeProcessMJ( RPObject* _parent ):
	RPShape( _parent, _T("Process") )
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

void RPShapeProcessMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeProcessDlg1_MJ dlg(NULL,this);
	dlg.DoModal();
//	rpapp.project().list_name();
}

void RPShapeProcessMJ::list_name()
{
	RPShape::list_name();
	TRACE( "*** Process ***\n" );
}


// // ��������� �������� ��� ���� *.fun
void RPShapeProcessMJ::define_rule()
{
		int cur = gtype;
		CString rule;
		switch(cur) // ���������� �������� ���� ������ �� ������
		{
	case 0: // ��������� 

	rpapp.RDOfiles->pattern<<gexp;

				break;	

	case 1: // ����������
	
	rpapp.RDOfiles->pattern<<"����������_�����_" <<getName().c_str()<<"("<<gexp<<","<<gdisp<<")";
		

	rpapp.RDOfiles->function
	<<endl<<endl<<endl<<"$Sequence ����������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = normal "<<base_gen
	<<endl<<"$End";
						break;
						
	case 2: // ����������� �����
	
		
	rpapp.RDOfiles->pattern
	<<"�����������_�����_" <<getName().c_str()<<"("<<gmin<<","<<gmax<<")";
	
	rpapp.RDOfiles->function
	<<endl<<endl<<endl<<"$Sequence �����������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = uniform "<<base_gen
	<<endl<<"$End";
			break;
	case 3: // ����������������
	rpapp.RDOfiles->pattern
	<<"����������������_�����_" <<getName().c_str()<<"("<<gexp<<")";

	rpapp.RDOfiles->function
	<<endl<<endl<<endl<<"$Sequence ����������������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = exponential "<<base_gen
	<<endl<<"$End";
						break;

		}


}


void RPShapeProcessMJ::generate_MJ()
{
	RPShape::generate_MJ();

	//��������� ���� ���������� ��������� ��� *.opr
		CString name_value1("����_����������_�_�������_");
		CString name_value2(getName().c_str());
		CString name_value(name_value1 + name_value2);
		rpapp.project().list_pattern_names.push_back(name_value);

		name_value1 = "����_�������_��_�������_�_��������_";
		name_value2 = getName().c_str();
		name_value = name_value1 + name_value2;
		rpapp.project().list_pattern_names.push_back(name_value);

		name_value1 = "����_���������_";
		name_value2 = getName().c_str();
		name_value = name_value1 + name_value2;
		rpapp.project().list_pattern_names.push_back(name_value);



	// ��������� ���������� ��� ���� *.pmd
	rpapp.RDOfiles->statistic

	<<endl<<"���������_�����_" <<getName().c_str()<<
	  ":  watch_state"<<" Block_process_"<<getName().c_str()<<".��������� = �����"

	<<endl<<"�������_�����_" <<getName().c_str()<<
	  ":  watch_par"<<" Queue_"<<getName().c_str()<<".������_�������";



// ��������� �������� ��� ���� *.res
	rpapp.RDOfiles->resourse<<endl<<endl<<"{-------���� process ------" <<getName().c_str()<<"-------------------}" <<endl

	<<"Block_process_"<<getName().c_str()<<" : Block_process ��������"
	<<endl<<"Queue_"<<getName().c_str()<<": Queue 0 �������� {���-�� ������� � ������� � ��������� �������� ������� }";


// ��������� ��������� ��� ���� *.pat
rpapp.RDOfiles->pattern <<endl<<endl<<"{---------���������� � ��������--------"<<getName().c_str()<<"-----------------------}"
<<endl

	<<endl<<"$Pattern ����_����������_�_�������_"<<getName().c_str()<<" : rule {}trace"
	<<endl<<"$Relevant_resources"
	<<endl<<"	 _transact  : Group_of_transacts_X  Keep"
	<<endl<<"	_block     : Queue_"<<getName().c_str()<<" Keep"
	<<endl
	<<endl<<"$Body"
	<<endl<<"_transact"
	<<endl<<"Choice from   _transact.���������_��������������� = ������� and" 
	<<endl<<"	_transact.�����_���������� = "<<getName().c_str()<<" and _transact.�����_����������_������� = "<<getName().c_str()
	<<endl<<"	first"
	<<endl<<"Convert_rule "
	<<endl<<"	���������_��������������� set �_�������"
	<<endl	
	<<endl<<"_block"
	<<endl<<"Choice from 1=1"
	<<endl<<"first"
	<<endl<<"	Convert_rule"
	<<endl<<"	������_������� set _block.������_������� + 1"
	<<endl<<"$End"
	<<endl

	//------------------------------------------------
	
	<<endl<<"{---------������������ �� �������------"<<getName().c_str()<<"---------------}"<<endl
	<<endl<<"$Pattern ����_�������_��_�������_�_��������_"<<getName().c_str()<<" : rule {}trace"
	<<endl
	<<endl<<"$Relevant_resources"
	<<endl<<"	_transact  : Group_of_transacts_X  Keep"
	<<endl<<"	_block     : Queue_"<<getName().c_str()<<" Keep"
	<<endl<<"	_block_proc : Block_process_"<<getName().c_str()<<" NoChange";


	// ������������ ���������
	std::list<CString>::iterator it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl
	<<endl<<"_resource_"<<(*it)<<" : Resource_"<<(*it)<<" NoChange";

	it++;
	}


	rpapp.RDOfiles->pattern <<endl

	<<endl<<"	$Body"
	<<endl<<"_transact"
	<<endl<<"	Choice from   _transact.���������_��������������� = �_������� and" 
	<<endl<<"	_transact.�����_���������� = "<<getName().c_str()<<" and _transact.�����_����������_������� = "<<getName().c_str()
	<<endl<<"		first"
	<<endl<<"	Convert_rule" 
	<<endl<<"		���������_��������������� set �_�������_�����"
	<<endl<<"		�����_����������_�������  set "<<id_next.c_str()
	<<endl
	<<endl<<"_block"
	<<endl<<"	Choice from _block.�����_������� = ��������"
	<<endl<<"		first"
	<<endl<<"	Convert_rule"
	<<endl<<"		������_������� set _block.������_������� - 1"
	<<endl<<"		�����_������� set �����"
	<<endl
	<<endl<<"_block_proc"
	<<endl<<"	Choice from 1=1"
	<<endl<<"		first"
	<<endl;

	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl


	<<endl<<"_resource_"<<(*it) 
    <<endl<<"	Choice from" 
	<<endl<<"	_resource_"<<(*it)<<".���������=��������"
	<<endl<<"		first";

	it++;
	}


rpapp.RDOfiles->pattern
	<<endl<<"$End"
	
	//----------------------------------------------------------------------------
		
	<<endl<<"{---------�������-----"<<getName().c_str()<<"----------------}"<<endl



	<<endl<<"$Pattern ����_���������_"<<getName().c_str()<<" : operation  {������������ ������}trace"
	<<endl<<"	$Relevant_resources"
	<<endl<<"	{��������������� ��� ���� ��������}"
	<<endl<<"_block_queue     : Queue_"<<getName().c_str()<<" Keep NoChange"
	<<endl
	<<endl
	<<endl

	<<endl<<"	{��� ����������� ����������� �������, ������� �������� �������� ����� � "
	<<endl<<"	�����, � ���� ��� ������ ���� �������� �� ������}"
	<<endl
	<<endl;

// ������������ ���������
 it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl
	<<endl<<"_resource_"<<(*it)<<" : Resource_"<<(*it)<<" Keep Keep";

	it++;
	}



rpapp.RDOfiles->pattern <<endl
	<<endl<<"	{����������� ��� ������ ���������� ������� ��������� - ������� �������������}"
	<<endl<<"_transact_X : Group_of_transacts_X Keep Keep"
	<<endl<<"_block : Block_process_"<<getName().c_str()<<" Keep Keep"
	<<endl
	<<"$Time = ";
	define_rule(); // ������� ����� ��������� ����� � ���������� ��� ����� � *.fun
	rpapp.RDOfiles->pattern<<" {����� ������������ ����������������� ��������}"
	<<endl
	<<endl
	<<endl<<"$Body"
	<<endl
	<<endl<<"_block_queue"
	<<endl<<"	Choice from _block_queue.�����_������� = ����� "
	<<endl<<"		first"
	<<endl<<"	Convert_begin"
	<<endl<<"		�����_������� set ��������"
    <<endl
	<<endl
	  
	<<endl<<"_transact_X"	
	<<endl<<"	Choice from _transact_X.���������_��������������� = �_�������_����� and"
	<<endl<<"	_transact_X.�����_���������� = "<<getName().c_str() 
	<<endl<<"		first"
	<<endl<<"	Convert_begin"
	
	
	<<endl<<"		���������_��������������� set ��������"
	<<endl<<"		�����_����������_������� set "<<id_next.c_str()
	<<endl
	<<endl<<"	Convert_end"
	<<endl<<"		���������_��������������� set �������"
	
	
	<<endl<<"{����� ������� ��������� ����� �������� �� ���� ������������ ��������}	"
	<<endl<<endl;




//�������� ��������
	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl


	<<endl<<"_resource_"<<(*it) 
    <<endl<<"	Choice from" 
	<<endl<<"	_resource_"<<(*it)<<".���������=��������"
	<<endl<<"		first"
    <<endl<<"	Convert_begin"
	<<endl<<"		�����������_���������� set _resource_"<<(*it)<<".�����������_���������� + 1"
	<<endl<<"		���������              set" 
	<<endl<<"		fun_resource_"<<(*it)<<"(_resource_"<<(*it)<<".�����������_����������,_resource_"<<(*it)<<".���������,"
	<<endl<<"		_resource_"<<(*it)<<".������_�����������)"
	<<endl
    <<endl<<"	Convert_end"
	<<endl<<"		�����������_���������� set _resource_"<<(*it)<<".�����������_���������� - 1"
	<<endl<<"		���������              set" 
	<<endl<<"		fun_resource_"<<(*it)<<"(_resource_"<<(*it)<<".�����������_����������,_resource_"<<(*it)<<".���������,"
	<<endl<<"		_resource_"<<(*it)<<".������_�����������)";

	it++;
	}




rpapp.RDOfiles->pattern <<endl<<endl

	<<endl<<"_block"
	<<endl<<"  Choice from"
	<<endl<<"  1=1"
	<<endl<<"		first"
	<<endl<<"	Convert_begin"
	<<endl<<"		��������� set �����" 
	
			/*
	fun_resource_"<<getName().c_str()<<"_seize(";


it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	it++;
	if(it==list_resource_procMJ.end())
	{
	it--;
		rpapp.RDOfiles->pattern <<endl
		<<endl<<"_resource_"<<(*it)<<".���������";
	}
	else
	{
	it--;
		rpapp.RDOfiles->pattern <<endl
		<<endl<<"_resource_"<<(*it)<<".���������,";
	}

	it++;
	}

    rpapp.RDOfiles->pattern <<")"<<endl


*/

	<<endl<<"Convert_end  "
    <<endl<<endl<<"		��������� set �������� "
	/*
	fun_resource_"<<getName().c_str()<<"_seize(";


	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	it++;
	if(it==list_resource_procMJ.end())
	{
	it--;
		rpapp.RDOfiles->pattern <<endl
		<<endl<<"_resource_"<<(*it)<<".���������";
	}
	else
	{
	it--;
		rpapp.RDOfiles->pattern <<endl
		<<endl<<"_resource_"<<(*it)<<".���������,";
	}

	it++;
	}

    rpapp.RDOfiles->pattern <<")"<<endl

  */
	<<endl<<"$End";


// ��������� ������� ��� ���� *.fun ��� �-�� ��������� �������� �� ����, ��� � ����� ��������� ������
rpapp.RDOfiles->function<<endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<endl

	<<endl<<"$Function  fun_resource_"<<getName().c_str()<<"_seize : such_as Block_process.���������"
	<<endl<<"$Type = algorithmic"
	<<endl<<"$Parameters";
	
		it = list_resource_procMJ.begin();
		while( it != list_resource_procMJ.end() ) 
		{
			
	rpapp.RDOfiles->function 
	<<endl<<"		_resource_"<<(*it)<<": such_as Resource.���������";
		it++;
		}
	
	rpapp.RDOfiles->function 
	<<endl<<"	$Body";
	
		it = list_resource_procMJ.begin();
		while( it != list_resource_procMJ.end() ) 
		{
			
	rpapp.RDOfiles->function 
	<<endl<<"	Calculate_if _resource_"<<(*it)<<" = ����� fun_resource_"<<getName().c_str()<<"_seize = �����";
		it++;
		}
	
	rpapp.RDOfiles->function 
	<<endl  
	<<endl<<"  Calculate_if 1=1 fun_resource_"<<getName().c_str()<<"_seize=��������"
	<<endl
	<<endl<<"	$End";	




}