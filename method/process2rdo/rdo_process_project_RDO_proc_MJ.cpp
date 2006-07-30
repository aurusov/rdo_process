#include "stdafx.h"
#include "rdo_process_project_RDO_proc_MJ.h"
#include "../../rdoprocess_object_chart.h"
#include "../../rdoprocess_shape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPProject_RDO_Proc_MJ::RPProject_RDO_Proc_MJ():
	RPProject(),
	RPObject_MJ( get_this() ),
	RDOfiles( NULL ) // �������������
{
	RDOfiles = new RPCreationRDOFilesMJ();
}

RPProject_RDO_Proc_MJ::~RPProject_RDO_Proc_MJ()
{
}

void RPProject_RDO_Proc_MJ::generate()
{
	RDOfiles->pattern.open("aaa\\RDO_PROCESS.pat");
	RDOfiles->resourse.open("aaa\\RDO_PROCESS.rss");
	RDOfiles->function.open("aaa\\RDO_PROCESS.fun");
	
	RDOfiles->typeres.open("aaa\\RDO_PROCESS.rtp");
	RDOfiles->operations.open("aaa\\RDO_PROCESS.opr");
	RDOfiles->smr.open("aaa\\RDO_PROCESS.smr");
	RDOfiles->statistic.open("aaa\\RDO_PROCESS.pmd");
	
	blank_rdo_MJ();
	list_name();
	
	RDOfiles->pattern.close();
	
	RDOfiles->resourse<<endl<<endl<<"$End";
	RDOfiles->resourse.close();
	
	RDOfiles->function.close();
	RDOfiles->typeres.close();
	
	
	RDOfiles->smr.close();
	
	
	
	RDOfiles->statistic<<
	endl<<"$End";
	RDOfiles->statistic.close();
	
	
	//�������������  �������� *.opr ��� �.�. ������ ���� ��� �������������� ��� �����

		list_pattern_names.push_back("����_��������_�������������_��_�������");

					RDOfiles->operations<<"$Operations";

				std::list<CString>::iterator it = list_pattern_names.begin();
				  int amount = 1;	
				
				  while( it != list_pattern_names.end() ) 
					{
					TRACE( "%s\n", (*it) );
					RDOfiles->operations<<endl
					<<endl<<"operation_"<<amount<<" : "<<(*it);

					it++; amount++;
					}


					RDOfiles->operations
					<<endl<<"$End";
list_pattern_names.clear();

	RDOfiles->operations.close();
}

void RPProject_RDO_Proc_MJ::blank_rdo_MJ()
{
//������������� ����� ��������� *.rtp
RDOfiles->typeres
<<endl	
<<endl<<"{ res }"
<<endl<<"$Resource_type Resource : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"��������� : (�����,��������)"
<<endl<<"�����������_���������� : integer {������� ������������� ���������� � ������� ������}"
<<endl<<"������_����������� : integer {���� ����������� ������� ����� �������������"
<<endl<<"����� �������� ������� ��������� � ��������� �����}"
<<endl<<"$End"
<<endl
<<endl
<<endl
<<endl
<<endl
<<endl<<"{1}"
<<endl<<"$Resource_type Creates : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"  par_1 : (true, false) {false} {�������� � ��������� ������� ������}"
<<endl<<"  par_amount: integer   {1}     {������� ����������� ���} "
<<endl<<"$End"
<<endl
<<endl
<<endl
<<endl<<"$Resource_type Group_of_transacts_X : temporary    {��������� ������������ ���������}"
<<endl<<"$Parameters"
<<endl<<"   {��������� ��������� �������� �������������"
<<endl<<"    � ������������ �������������}"
<<endl
<<endl<<"{ ��������� ����� ���������� }"
<<endl
<<endl<<"	�����_���������� :(";

list_name_for_type_res(); // �-�� ��������� ������ ���� ������
RDOfiles->typeres<<"������_����_���������)"


<<endl<<"	�����_����������_������� : such_as  Group_of_transacts_X.�����_���������� {ID ������, ���� ����������� ���������� �� ���� ����}"
<<endl
<<endl	
<<endl
<<endl<<"{ C�������� ���������}	"
<<endl<<"	���������_��������� : integer {}"
<<endl
<<endl
<<endl<<"{PRIMARY KEY}"
<<endl<<"    �����������������_�����_��������� : integer"
<<endl<<"    �����������������_�����_������_���������� : such_as  Group_of_transacts_X.�����_����������"
<<endl<<"{-----------}"
<<endl
<<endl<<"	�����_�_������� : integer"
<<endl<<"	���������_��������������� : (�������, ��������, �_�������, �_�������_�����)"
<<endl
<<endl<<"{ �������������� ��������� �������������� �������������}"
<<endl
<<endl<<"{" 
<<endl<<"... : ..."
<<endl<<" }"
<<endl<<"$End "
<<endl 
<<endl<<" {2 �������}"
<<endl<<" $Resource_type Queue : permanent"
<<endl<<"$Parameters"
<<endl<<"  ������_������� : integer"
<<endl<<"	 �����_�������: (��������, �����)"
<<endl<<"$End"
<<endl
<<endl
<<endl<<"{3 �������}"
<<endl<<"$Resource_type Block_process : permanent {��������� ����� Create}"
<<endl<<"$Parameters"
<<endl<<"  ��������� : (�����,��������)"
<<endl<<"$End"
<<endl
<<endl<<"{4del}"
<<endl<<" $Resource_type Block_Del : permanent"
<<endl<<"$Parameters"
<<endl<<"  �����������_��������� : integer"
<<endl
<<endl<<"$End";


//�������������  ��������� *.rtp
RDOfiles->resourse<<"$Resources";


//�������������  ���������� *.pmd
RDOfiles->statistic<<

endl<<"$Results";



//�������������  SMR *.smr
RDOfiles->smr<<
endl<<"Model_name = RDO_PROCESS"
<<endl
<<endl<<"Resource_file  = RDO_PROCESS"
<<endl<<"OprIev_file    = RDO_PROCESS" // OPR
<<endl<<"Trace_file     = RDO_PROCESS"
<<endl<<"Statistic_file = RDO_PROCESS" //PMD
<<endl<<"Results_file   = RDO_PROCESS"
//<<endl<<"Frame_file     = RDO_PROCESS"
//<<endl<<"Frame_number   = 1"
//<<endl<<"Show_mode      = Animation"
//<<endl<<"Show_rate      = 10000000.0"
<<endl
<<endl<<"Terminate_if  Time_now >= "<< generate_time_MJ;



// ������������� ������� � *.pat ��������� ����� �����������
list_pattern_names.push_back("����_�����������");// ��������� ��� ��� *.opr

RDOfiles->pattern
<<"{----------------��������� ����� �����������-------------------------------------------}"
<<endl<<"$Pattern ����_����������� : rule  {������������ ������}trace"
<<endl<<"	$Relevant_resources"
<<endl<<"		_transact_X : Group_of_transacts_X Keep"
<<endl
<<endl<<"	$Body"
<<endl
<<endl<<"	_transact_X"
<<endl<<"		Choice from _transact_X.���������_��������������� = �������  and"
<<endl<<"		_transact_X.�����_����������_�������<>_transact_X.�����_���������� "
<<endl<<"	first"
<<endl
<<endl<<"	Convert_rule"
<<endl<<"		�����_���������� set  _transact_X.�����_����������_�������"
<<endl
<<endl<<"	$End";


RDOfiles->pattern
<<endl<<"{----------------��������� ���� ��������������� �� �������-------------------------------------------}"
<<endl
<<endl<<"$Pattern  ����_��������_�������������_��_������� : irregular_event trace "
<<endl<<"$Relevant_resources"
<<endl<<"_parameter : Group_of_transacts_X  NoChange {����� ��� ����, ��� ��� ���� ������}"
<<endl<<"$Time ="<< generate_time_MJ
<<endl<<"$Body"
<<endl<<"_parameter"
<<endl<<"$End";
}
