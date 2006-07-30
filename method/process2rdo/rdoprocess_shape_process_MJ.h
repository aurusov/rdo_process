// rdoprocess_shape_process_MJ.h: interface for the RPShapeProcessMJ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RDOPROCESS_SHAPE_PROCESS_MJ_H__A5AEB64C_2CE8_46D3_9E6B_86368CB68269__INCLUDED_)
#define AFX_RDOPROCESS_SHAPE_PROCESS_MJ_H__A5AEB64C_2CE8_46D3_9E6B_86368CB68269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_shape_MJ.h"
#include <list>

class RPShapeProcessMJ : public RPShape_MJ
{
public:
	RPShapeProcessMJ( RPObject* parent );
	virtual ~RPShapeProcessMJ();

	virtual rp::string getType() { return "RPShapeProcessMJ"; }

	virtual void onLButtonDblClk( UINT nFlags, CPoint global_chart_pos );
	virtual void list_name();
	virtual void generate();
	void define_rule();

		//���������� ��� ���������
	CString gname; // ���
	
	int gtype; // ����� ��������
	int base_gen;
	
	//�������� �������
	double gexp;
	double gdisp;
	double gmax;
	double gmin;

	int action; // ��� �������� �� ��������� � �������
	int prior;
	int queue;
	int parameter;

	std::list< CString> list_resource_procMJ;
};

#endif // !defined(AFX_RDOPROCESS_SHAPE_PROCESS_MJ_H__A5AEB64C_2CE8_46D3_9E6B_86368CB68269__INCLUDED_)
