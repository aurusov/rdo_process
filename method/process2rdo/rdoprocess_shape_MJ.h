#ifndef RDO_PROCESS_SHAPE_MJ_H
#define RDO_PROCESS_SHAPE_MJ_H

#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../rdoprocess_shape.h"
#include "../../rdoprocess_object_flowchart.h"

// ----------------------------------------------------------------------------
// ---------- RPObject_MJ
// ----------------------------------------------------------------------------
class RPObject_MJ
{
private:
	RPObject* obj;

public:
	RPObject_MJ( RPObject* _obj ): obj( _obj ), id_next( "" ), type( "block" ) {}

	rp::string id_next; // MJ 30.03.06 id ���������� �����, �������� ����� ��� �������, ������� ��������� �������
	rp::string type; // MJ 1.04.06 ��� ����������� ���� ������

	void list_name();				// MJ ������ �� ����� ����� ��������, ���������� ��� �������������
	void list_name_for_type_res();  // MJ ������������ ��� ������������� ����� ���������, ������ ���������� ����� ���� ������ ������� ���� �� ������, ����� ��������� ��� ���� �����
	void list_name_for_resource_MJ( std::list< RPObject* >* list_resource ); // MJ ���������� �� ������ �� ������ ��� ��� �������, ������������ � �������� ��� ������ ��������
};

// ----------------------------------------------------------------------------
// ---------- RPShape_MJ
// ----------------------------------------------------------------------------
class RPShape_MJ: public RPShape, public RPObject_MJ
{
public:
	RPShape_MJ( RPObject* parent, const rp::string& name = "object" ): RPShape( parent, name ), RPObject_MJ( get_this() ) {}

	virtual rp::string getType() { return "RPShape_MJ"; }
};

// ----------------------------------------------------------------------------
// ---------- RPObjectFlowChart_MJ
// ----------------------------------------------------------------------------
class RPObjectFlowChart_MJ: public RPObjectFlowChart, public RPObject_MJ
{
public:
	RPObjectFlowChart_MJ( RPObject* parent, RPFlowChart* flowchart ): RPObjectFlowChart( parent, flowchart ), RPObject_MJ( get_this() ) {}

	virtual rp::string getType() { return "RPObjectFlowChart_MJ"; }
};

#endif // RDO_PROCESS_SHAPE_MJ_H
