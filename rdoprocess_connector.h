#ifndef RDO_PROCESS_CONNECTOR_H
#define RDO_PROCESS_CONNECTOR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_object_chart.h"
#include "rdoprocess_object_matrix.h"

#include <list>

// ----------------------------------------------------------------------------
// ---------- RPConnector
// ----------------------------------------------------------------------------
class RPConnectorDock;
class RPShape;

#define CON_DEBUG 1
#undef CON_DEBUG

class RPConnector: public RPObjectChart
{
friend class RPObjectFlowChart;

protected:
	RPConnectorDock* dock_begin;
	RPConnectorDock* dock_end;

	rp::polyline borders;
	int recursive;

#ifdef CON_DEBUG
	void makeConnector( CDC& dc, const rp::point& p1, const rp::point& p2, double norm1, double norm2, rp::polyline& pa );
	bool getShortLine( CDC& dc, const rp::polyline& pa, const rp::point& from, const rp::point& to, double& lengthA2, rp::point& B1, rp::point& B2, rp::point& interborder );
	bool isVectoreIntersect( CDC& dc, RPShape* shape, const rp::point& vect_begin, const rp::point& vect_end ) const;
#else if
	void makeConnector( const rp::point& p1, const rp::point& p2, double norm1, double norm2, rp::polyline& pa );
	bool getShortLine( const rp::polyline& pa, const rp::point& from, const rp::point& to, double& lengthA2, rp::point& B1, rp::point& B2, rp::point& interborder );
	bool isVectoreIntersect( RPShape* shape, const rp::point& vect_begin, const rp::point& vect_end ) const;
#endif

	// ������� ���� ��������� ������ � ���������� ����������
	virtual void transformToGlobal() {};

	// ��������� �� ����� ������ ������
	virtual bool pointInPolygon( const rp::point& global_chart_pos ) {
		return false;
	};
	// ��������� �� ����� � ��������� (������������) ����� ������ (������������� ���������, � �������)
	virtual bool pointInNCArea( const rp::point& global_chart_pos ) {
		return false;
	};

	// �������� ������
	virtual rp::rect getBoundingRect( bool global = true ) const {
		return rp::rect();
	};

	// ��������� ������
	virtual void draw( CDC& dc );

	virtual bool isConnector() const   { return true; }

public:
	RPConnector( RPObject* parent, const rp::string& name = "connector" );
	virtual ~RPConnector();

	RPConnectorDock* getConnectedDock( const RPConnectorDock& dock ) const;
};

// ----------------------------------------------------------------------------
// ---------- RPConnectorDock
// ----------------------------------------------------------------------------
class RPConnectorDock
{
public:
	enum Type {
		in    = 0x01,
		out   = 0x02,
		inout = 0x03,
		fly   = 0x04,
		all   = 0x07
	};
	static const int delta;

protected:
	RPObjectChart*  parent;
	rp::point       point;
	Type            type;
	double          norm;

public:
	RPConnectorDock( RPObjectChart* _parent, Type _type, const rp::point& _point, double _norm ): parent( _parent ), type( _type ), point( _point ), norm( _norm ) {};
	virtual ~RPConnectorDock() {};

	std::list< RPConnector* > connectors;

	virtual bool can_connect() const { return true;                  }
	virtual COLORREF color() const   { return RGB(0xF0, 0xFF, 0x00); }
	Type getType() const             { return type;                  }
	bool isType( Type _type ) const {
		switch ( _type ) {
			case fly  : return type & fly ? true : false;
			case in   : return type & in  ? true : false;
			case out  : return type & out ? true : false;
			case inout: return (type & inout) == inout ? true : false;
			case all  : return (type & all  ) == all   ? true : false;
		}
		return false;
	}
	const RPObjectChart& object() const {
		return *parent;
	}
	rp::point getPosition( bool global = true ) const {
		return global && parent->isMatrix() ? static_cast<RPObjectMatrix*>(parent)->globalMatrix() * point : point;
	}
	double getNorm( bool global = true ) const {
		double res = global && parent->isMatrix() ? static_cast<RPObjectMatrix*>(parent)->getRotationGlobal() + norm : norm;
		while ( res >= 360 ) res -= 360;
		while ( res <    0 ) res += 360;
		return res;
	}
	rp::point getDeltaPosition( bool global = true ) const {
		rp::point pos    = getPosition( global );
		double    rotate = getNorm( global );
		rp::point res;
		res.x = pos.x + cos( rotate * rp::math::pi / 180.0 ) * RPConnectorDock::delta;
		res.y = pos.y - sin( rotate * rp::math::pi / 180.0 ) * RPConnectorDock::delta;
		return res;
	}
	// ��� ��� ������� ��������
	virtual RPConnector* make_connector( RPObject* _parent ) { return new RPConnector( _parent ); }
};

// ----------------------------------------------------------------------------
// ---------- RPConnectorDockOne
// ----------------------------------------------------------------------------
class RPConnectorDockOne: public RPConnectorDock
{
public:
	RPConnectorDockOne( RPObjectMatrix* _parent, Type _type, const rp::point& _point, double _norm ): RPConnectorDock( _parent, _type, _point, _norm ) {};
	virtual ~RPConnectorDockOne() {};

	virtual bool can_connect() const { return connectors.empty(); }
};

// ----------------------------------------------------------------------------
// ---------- RPConnectorResource
// ----------------------------------------------------------------------------
class RPConnectorResource: public RPConnector
{
public:
	RPConnectorResource( RPObject* parent, const rp::string& name = "connector" );
	virtual ~RPConnectorResource();
};

// ----------------------------------------------------------------------------
// ---------- RPConnectorResource
// ----------------------------------------------------------------------------
class RPConnectorDockResource: public RPConnectorDock
{
public:
	RPConnectorDockResource( RPObjectMatrix* _parent, Type _type, const rp::point& _point, double _norm ): RPConnectorDock( _parent, _type, _point, _norm ) {};
	virtual ~RPConnectorDockResource() {};

	// ��� ��� ������� ��������
	virtual RPConnector* make_connector( RPObject* _parent ) { return new RPConnectorResource( _parent ); }
};

#endif // RDO_PROCESS_CONNECTOR_H
