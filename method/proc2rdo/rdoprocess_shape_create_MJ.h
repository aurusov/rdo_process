// rdoprocess_shape_create_MJ.h: interface for the RPShapeCreateMJ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RDOPROCESS_SHAPE_CREATE_MJ_H__B043A584_EC30_4198_83AE_4C54E356FDAF__INCLUDED_)
#define AFX_RDOPROCESS_SHAPE_CREATE_MJ_H__B043A584_EC30_4198_83AE_4C54E356FDAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_shape_MJ.h"

class RPShapeCreateMJ : public RPShape_MJ  
{
friend class RPMethodProc2RDO_MJ;

private:
	static RPObject* newObject( RPObject* parent );

public:
	RPShapeCreateMJ( RPObject* parent );
	virtual ~RPShapeCreateMJ();

	virtual rp::string getClassName() const { return "RPShapeCreateMJ"; }
	virtual rp::RPXMLNode* save( rp::RPXMLNode* parent_node );

	void define_rule();
	virtual void onLButtonDblClk( UINT nFlags, CPoint global_chart_pos );
	//virtual void list_name();
	virtual void generate();

	//���������� ��� ���������
	CString gname; // ���
	double gfirst; // ����� �������
	double gamount; // ���-�� �����������
	int gtype; // ����� ��������
	int base_gen;
	
	//�������� �������
	double gexp;
	double gdisp;
	double gmax;
	double gmin;

	//������ ����
	int inf; // ������������
	int gID; // ID ������
	double gpar1, gpar2, gpar3;


};

#endif // !defined(AFX_RDOPROCESS_SHAPE_CREATE_MJ_H__B043A584_EC30_4198_83AE_4C54E356FDAF__INCLUDED_)
