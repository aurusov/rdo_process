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
/*
rpapp.RDOfiles->pattern <<endl<<endl<<"��� ���������� ����� - "<<id_next
<<endl<<"��� - "<<getName().c_str()

<<endl<<"����� �������� - "<<gtype
<<endl<<"���� ���������� - "<<base_gen
<<endl<<"�������� ������ - "<<"exp - "<<gexp<<" disp"<<gdisp<<" max - " <<gmax<<" min - "<<gmin
<<endl<<"��������"<<action
<<endl<<"�����"<<queue<<endl

<<"������� :";

std::list<CString>::iterator it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	rpapp.RDOfiles->pattern <<(*it)<<"     ";
	it++;
	}	


*/
// ��������� �������� ��� ���� *.res
	rpapp.RDOfiles->resourse<<endl<<"{-------���� process ------" <<getName().c_str()<<"-------------------}" <<endl

	<<endl<<"Block_process_"<<getName().c_str()<<" : Block_process ��������"
	<<endl<<"Queue_"<<getName().c_str()<<": Queue 0 �������� {���-�� ������� � ������� � ��������� �������� ������� }";


// ��������� ��������� ��� ���� *.pat
rpapp.RDOfiles->pattern <<endl<<endl<<"{---------���������� � ��������--------"<<getName().c_str()<<"-----------------------}"
<<endl

	<<endl<<"$Pattern Block_queue_"<<getName().c_str()<<" : rule {}trace"
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
	<<endl<<"$Pattern Block_queue_release_"<<getName().c_str()<<" : rule {}trace"
	<<endl
	<<endl<<"$Relevant_resources"
	<<endl<<"_transact  : Group_of_transacts_X  Keep"
	<<endl<<"_block     : Queue_<<getName().c_str()"<<" Keep"
	<<endl<<"_block_proc : Block_process_"<<getName().c_str()<<" NoChange"
	<<endl<<"	$Body"
	<<endl<<"_transact"
	<<endl<<"	Choice from   _transact.���������_��������������� = �_������� and" 
	<<endl<<"	_transact.�����_���������� = "<<getName().c_str()<<" and _transact.�����_����������_������� = "<<getName().c_str()
	<<endl<<"		first"
	<<endl<<"	Convert_rule" 
	<<endl<<"		���������_��������������� set �_�������_�����"
	<<endl<<"		�����_����������_�������  set "<<id_next
	<<endl
	<<endl<<"_block"
	<<endl<<"	Choice from _block.�����_������� = ��������"
	<<endl<<"		first"
	<<endl<<"	Convert_rule"
	<<endl<<"		������_������� set _block.������_������� - 1"
	<<endl<<"		�����_������� set �����"
	<<endl
	<<endl<<"_block_proc"
	<<endl<<"	Choice from _block_proc.���������=��������"
	<<endl<<"		first"
	<<endl
	<<endl<<"$End"
	
	//----------------------------------------------------------------------------
		
	<<endl<<"{---------�������-----"<<getName().c_str()<<"----------------}"<<endl



	<<endl<<"$Pattern ����_���������_"<<getName().c_str()<<" : operation  {������������ ������}trace"
	<<endl<<"	$Relevant_resources"
	<<endl<<"	{��������������� ��� ���� ��������}"
	<<endl<<"_block_queue     : Queue_"<<getName().c_str()<<" Keep NoChange"
	<<endl
	<<endl<<"_block : Block_process_"<<getName().c_str()<<" Keep Keep"
	<<endl
	<<endl

	<<endl<<"	{��� ����������� ����������� �������, ������� �������� �������� ����� � "
	<<endl<<"	�����, � ���� ��� ������ ���� �������� �� ������}"
	<<endl
	<<endl;

// ������������ ���������
std::list<CString>::iterator it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl
	<<endl<<"_resource_"<<(*it)<<" : Resource_"<<(*it)<<" Keep Keep";

	it++;
	}



rpapp.RDOfiles->pattern <<endl
	<<endl<<"	{����������� ��� ������ ���������� ������� ��������� - ������� �������������}"
	<<endl<<"_transact_X : Group_of_transacts_X Keep Keep"
	<<endl
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
	<<endl<<"		�����_����������_������� set "<<id_next
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
	<<endl<<"  _block.��������� = ��������"
	<<endl<<"		first"
	<<endl<<"	Convert_begin"
	<<endl<<"		��������� set fun_resource_"<<getName().c_str()<<"_sieze(";


	it = list_resource_procMJ.begin();
	while( it != list_resource_procMJ.end() ) 
	{
	
	rpapp.RDOfiles->pattern <<endl
	<<endl<<"_resource_"<<(*it)<<".���������,";

	it++;
	}

    rpapp.RDOfiles->pattern <<")"<<endl




	<<endl<<"Convert_end  "
    <<endl<<endl<<"		��������� set fun_resource_"<<getName().c_str()<<"_release(";


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
	<<endl<<"$End";


}