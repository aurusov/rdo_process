// rdoprocess_shape_create_MJ.cpp: implementation of the RPShapeCreateMJ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "rdo_process.h"
#include "rdoprocess_shape_create_MJ.h"
#include "rdoprocess_shape_create_dlg1_MJ.h"
#include "rdoprocess_shape.h"
#include "rdoprocess_app.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RPShapeCreateMJ::RPShapeCreateMJ( RPObject* _parent ):
	RPShape( _parent, _T("_Create") )
{

	// ������������� ���� ����� 
	type ="block";	
			
	pa_src.push_back( rp::point(-50, -25) );
	pa_src.push_back( rp::point(25, -25) );
	pa_src.push_back( rp::point(50, 0) );
	pa_src.push_back( rp::point(25, 25) );
	pa_src.push_back( rp::point(-50, 25) );
	pa_src.push_back( rp::point(-50, -25) );

	docks.push_back( new RPConnectorDockOne( this, RPConnectorDock::out, rp::point(  50, 0 ), 0 ) );

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

void RPShapeCreateMJ::onLButtonDblClk( UINT nFlags, CPoint global_chart_pos )
{
	RPShapeCreateDlg1_MJ dlg( NULL, this );
	dlg.DoModal();
}

/*void RPShapeCreateMJ::list_name()
{
	RPShape::list_name();
	TRACE( "*** Create ***\n" );
}
*/


void RPShapeCreateMJ::generate_MJ()
{
/*
rpapp.RDOfiles->function <<"��� ���������� ����� - "<<id_next
<<endl<<"��� - "<<getName().c_str()
<<endl<<"����� ������� - "<<gfirst
<<endl<< "���-�� ����������� - "<<gamount
<<endl<<"����� �������� - "<<gtype
<<endl<<"���� ���������� - "<<base_gen
<<endl<<"�������� ������ - "<<"exp - "<<gexp<<" disp"<<gdisp<<" max - " <<gmax<<" min - "<<gmin
<<endl<<"������ ����! ������������ - "<<inf
<<endl<<"ID ������ - "<<gID
<<endl<<"��������� - "<<"1-  "<<gpar1<< " 2 - "<<gpar2<<" 3 - "<<gpar3;
*/

CString name_value1("����_��������_����������_");
CString name_value2(getName().c_str());
CString name_value(name_value1 + name_value2);
rpapp.project().list_pattern_names.push_back(name_value);


// ��������� �������� ��� ���� *.res
	rpapp.RDOfiles->resourse<<endl<<endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<endl

	<<"Create_"<<getName().c_str()<<" : Creates false 1";



// ��������� ��������� ��� ���� *.pat

rpapp.RDOfiles->pattern <<endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<endl


	<<endl<<"$Pattern  ����_��������_����������_" <<getName().c_str()<<" : irregular_event trace"
	<<endl<<"$Relevant_resources"
	<<endl<<"_parameter : Create_"<<getName().c_str()<<" Keep"
	<<endl<<" _transact  : Group_of_transacts_X  Create"
    <<endl<<"$Time = fun_"<<getName().c_str()<<"(_parameter.par_1, _parameter.par_amount)" 
	<<endl<<"$Body"
	<<endl<<"_parameter"
	<<endl<<" Convert_event"
	<<endl<<"par_1      set true {������� � ��� , ��� ��� ��� �� ������}"
	<<endl<<"par_amount set _parameter.par_amount + 1" 
	<<endl	
	<<endl<<"_transact"
	<<endl<<"    Convert_event" 
	<<endl	 
	<<endl	 
	<<endl<<"		�����_����������            set "<<getName().c_str()<<" {ID ���������� �����}"
	<<endl<<"		�����_����������_�������    set "<<id_next.c_str()          <<" {ID ���� ���� ���������}"
	
	
    //�����_�_������� set 0
	//���������_���������         set 0
	
	<<endl<<"		�����������������_�����_��������� set (_parameter.par_amount - 1)"
    <<endl<<"		�����������������_�����_������_���������� set "<<getName().c_str()<<" {ID ���������� �����}"
	<<endl<<"		���������_��������������� set �������	"
	<<endl<<"		���������_��������� set 0"
	<<endl<<"		�����_�_�������     set 0"
	<<endl<<"$End";







// ��������� ������� ��� ���� *.fun
// ��������� ������



rpapp.RDOfiles->function<<endl<<"{-------���� cretae ------" <<getName().c_str()<<"-------------------}" <<endl;

int cur = gtype;
CString rule;
	switch(cur) // ���������� �������� ���� ������ �� ������
	{
case 0: // ��������� 
			break;	

case 1: // ����������

	rpapp.RDOfiles->function

	<<endl<<"$Sequence ����������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = normal "<<base_gen
	<<endl<<"$End";

			break;
case 2: // ����������� �����
	rpapp.RDOfiles->function
	<<endl<<"$Sequence �����������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = uniform "<<base_gen
	<<endl<<"$End";
			break;
case 3: // ����������������
	rpapp.RDOfiles->function
	<<endl<<"$Sequence ����������������_�����_" <<getName().c_str()<<" : real "
	<<endl<<"$Type = exponential "<<base_gen
	<<endl<<"$End";
			break;
	}
// ��������� �-�� ������� ���������� ����� ������������, ����� ����� ����������� ��������
rpapp.RDOfiles->function<<endl
<<endl<<"$Function  fun_"<<getName().c_str()<<" : integer"
<<endl<<"$Type = algorithmic"
<<endl<<"$Parameters"
<<endl<<" _par        : such_as Creates.par_1 {��������� ������ ��� ���}"
<<endl<<"  _par_amount : integer {�������� �� ������� �� ������}"
<<endl<<"$Body"
<<endl<<"  Calculate_if _par_amount > "<<gamount<<"{����������� ����������� ���������}  fun_"<<getName().c_str()<<"="<<inf
<<endl 
<<endl<<"  Calculate_if _par = false and _par_amount <= "<<gamount<<"{����������� ����������� ���������} "
<<endl<<"  fun_"<<getName().c_str()<<"="<<gfirst<<"{����� ��������� ������� ���������}"
<<endl  
<<endl<<"  Calculate_if _par = true and _par_amount <= "<<gamount<<"{����������� ����������� ���������} "
<<endl<<"  fun_"<<getName().c_str()<<"=";

// ��������� �����
 cur = gtype;

	switch(cur) // ���������� �������� ���� ������ �� ������
	{
case 0: // ��������� 

	rpapp.RDOfiles->function<<gexp<<" {����� ��������� ����������}"
	<<endl<<"$End";
			break;	

case 1: // ����������

	rpapp.RDOfiles->function
	<<"����������_�����_" <<getName().c_str()<<"("<<gexp<<","<<gdisp<<") {����� ��������� ����������}"
	<<endl
	<<endl<<"$End";

			break;
case 2: // ����������� �����
	rpapp.RDOfiles->function
	<<"�����������_�����_" <<getName().c_str()<<"("<<gmin<<","<<gmax<<") {����� ��������� ����������}"
	<<endl
	<<endl<<"$End";

			break;
case 3: // ����������������
	rpapp.RDOfiles->function
	<<"����������������_�����_" <<getName().c_str()<<"("<<gexp<<") {����� ��������� ����������}"
	<<endl
	<<endl<<"$End";

			break;



	}
}