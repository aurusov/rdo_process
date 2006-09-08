// rdoprocess_shape_create_MJ.cpp: implementation of the RPShapeCreateMJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rdoprocess_shape_create_MJ.h"
#include "rdoprocess_shape_create_dlg1_MJ.h"
#include "rdoprocess_method_proc2rdo_MJ.h"
#include <rdoprocess_shape.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeCreateMJ::RPShapeCreateMJ( RPObject* _parent ):
	RPShape_MJ( _parent, _T("_Create") )
{
	pa_src.push_back( rp::point(-50, -25) );
	pa_src.push_back( rp::point(25, -25) );
	pa_src.push_back( rp::point(50, 0) );
	pa_src.push_back( rp::point(25, 25) );
	pa_src.push_back( rp::point(-50, 25) );
	pa_src.push_back( rp::point(-50, -25) );

	docks.push_back( new RPConnectorDockOne( this, RPConnectorDock::out, rp::point(  50, 0 ), 0, "transact" ) );

	// ������������� ���������� ��� �������������
	gname; // ���
	 gfirst=0; // ����� �������
	gamount=1000000; // ���-�� �����������
	gtype=0; // ����� ��������
	base_gen=1234567890;
	//�������� �������
	gexp=0;
	gdisp=0;
	gmax=0;
	gmin=0;

	//������ ����
	inf=1000000; // ������������
	gID=1; // ID ������
	gpar1=0;
	gpar2=0;
	gpar3=0;

}

RPShapeCreateMJ::~RPShapeCreateMJ()
{
}

rp::RPXMLNode* RPShapeCreateMJ::save( rp::RPXMLNode* parent_node )
{
	rp::RPXMLNode* obj_node = RPShape_MJ::save( parent_node );
	return obj_node;
}

RPObject* RPShapeCreateMJ::newObject( RPObject* parent )
{
	return new RPShapeCreateMJ( parent );
}

void RPShapeCreateMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeCreateDlg1_MJ dlg( AfxGetMainWnd(), this );
	dlg.DoModal();
}

/*void RPShapeCreateMJ::list_name()
{
	RPShape_MJ::list_name();
	TRACE( "*** Create ***\n" );
}
*/


void RPShapeCreateMJ::generate()
{
/*
RDOfiles->function <<"��� ���������� ����� - "<<id_next
<<std::endl<<"��� - "<<getName().c_str()
<<std::endl<<"����� ������� - "<<gfirst
<<std::endl<< "���-�� ����������� - "<<gamount
<<std::endl<<"����� �������� - "<<gtype
<<std::endl<<"���� ���������� - "<<base_gen
<<std::endl<<"�������� ������ - "<<"exp - "<<gexp<<" disp"<<gdisp<<" max - " <<gmax<<" min - "<<gmin
<<std::endl<<"������ ����! ������������ - "<<inf
<<std::endl<<"ID ������ - "<<gID
<<std::endl<<"��������� - "<<"1-  "<<gpar1<< " 2 - "<<gpar2<<" 3 - "<<gpar3;
*/

CString name_value1("����_��������_����������_");
CString name_value2(getName().c_str());
CString name_value(name_value1 + name_value2);
proc2rdo->list_pattern_names.push_back(name_value);


// ��������� �������� ��� ���� *.res
	RPCreationRDOFilesMJ* RDOfiles = proc2rdo->RDOfiles;
	RDOfiles->resourse<<std::endl<<std::endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<std::endl

	<<"Create_"<<getName().c_str()<<" : Creates false 1";



// ��������� ��������� ��� ���� *.pat

	RDOfiles->pattern <<std::endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<std::endl


	<<std::endl<<"$Pattern  ����_��������_����������_" <<getName().c_str()<<" : irregular_event trace"
	<<std::endl<<"$Relevant_resources"
	<<std::endl<<"_parameter : Create_"<<getName().c_str()<<" Keep"
	<<std::endl<<" _transact  : Group_of_transacts_X  Create"
    <<std::endl<<"$Time = fun_"<<getName().c_str()<<"(_parameter.par_1, _parameter.par_amount)" 
	<<std::endl<<"$Body"
	<<std::endl<<"_parameter"
	<<std::endl<<" Convert_event"
	<<std::endl<<"par_1      set true {������� � ��� , ��� ��� ��� �� ������}"
	<<std::endl<<"par_amount set _parameter.par_amount + 1" 
	<<std::endl	
	<<std::endl<<"_transact"
	<<std::endl<<"    Convert_event" 
	<<std::endl	 
	<<std::endl	 
	<<std::endl<<"		�����_����������            set "<<getName().c_str()<<" {ID ���������� �����}"
	<<std::endl<<"		�����_����������_�������    set "<<id_next.c_str()          <<" {ID ���� ���� ���������}"
	
	
    //�����_�_������� set 0
	//���������_���������         set 0
	
	<<std::endl<<"		�����������������_�����_��������� set (_parameter.par_amount - 1)"
    <<std::endl<<"		�����������������_�����_������_���������� set "<<getName().c_str()<<" {ID ���������� �����}"
	<<std::endl<<"		���������_��������������� set �������	"
	<<std::endl<<"		���������_��������� set 0"
	<<std::endl<<"		�����_�_�������     set 0"
	<<std::endl<<"$End";







// ��������� ������� ��� ���� *.fun
// ��������� ������



	RDOfiles->function<<std::endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<std::endl;

int cur = gtype;
CString rule;
	switch(cur) // ���������� �������� ���� ������ �� ������
	{
case 0: // ��������� 
			break;	

case 1: // ����������

	RDOfiles->function

	<<std::endl<<"$Sequence ����������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = normal "<<base_gen
	<<std::endl<<"$End";

			break;
case 2: // ����������� �����
	RDOfiles->function
	<<std::endl<<"$Sequence �����������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = uniform "<<base_gen
	<<std::endl<<"$End";
			break;
case 3: // ����������������
	RDOfiles->function
	<<std::endl<<"$Sequence ����������������_�����_" <<getName().c_str()<<" : real "
	<<std::endl<<"$Type = exponential "<<base_gen
	<<std::endl<<"$End";
			break;
	}
// ��������� �-�� ������� ���������� ����� ������������, ����� ����� ����������� ��������
RDOfiles->function<<std::endl
<<std::endl<<"$Function  fun_"<<getName().c_str()<<" : integer"
<<std::endl<<"$Type = algorithmic"
<<std::endl<<"$Parameters"
<<std::endl<<" _par        : such_as Creates.par_1 {��������� ������ ��� ���}"
<<std::endl<<"  _par_amount : integer {�������� �� ������� �� ������}"
<<std::endl<<"$Body"
<<std::endl<<"  Calculate_if _par_amount > "<<gamount<<"{����������� ����������� ���������}  fun_"<<getName().c_str()<<"="<<inf
<<std::endl 
<<std::endl<<"  Calculate_if _par = false and _par_amount <= "<<gamount<<"{����������� ����������� ���������} "
<<std::endl<<"  fun_"<<getName().c_str()<<"="<<gfirst<<"{����� ��������� ������� ���������}"
<<std::endl  
<<std::endl<<"  Calculate_if _par = true and _par_amount <= "<<gamount<<"{����������� ����������� ���������} "
<<std::endl<<"  fun_"<<getName().c_str()<<"=";

// ��������� �����
 cur = gtype;

	switch(cur) // ���������� �������� ���� ������ �� ������
	{
case 0: // ��������� 

	RDOfiles->function<<gexp<<" {����� ��������� ����������}"
	<<std::endl<<"$End";
			break;	

case 1: // ����������

	RDOfiles->function
	<<"����������_�����_" <<getName().c_str()<<"("<<gexp<<","<<gdisp<<") {����� ��������� ����������}"
	<<std::endl
	<<std::endl<<"$End";

			break;
case 2: // ����������� �����
	RDOfiles->function
	<<"�����������_�����_" <<getName().c_str()<<"("<<gmin<<","<<gmax<<") {����� ��������� ����������}"
	<<std::endl
	<<std::endl<<"$End";

			break;
case 3: // ����������������
	RDOfiles->function
	<<"����������������_�����_" <<getName().c_str()<<"("<<gexp<<") {����� ��������� ����������}"
	<<std::endl
	<<std::endl<<"$End";

			break;



	}
}