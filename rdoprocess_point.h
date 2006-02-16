#ifndef RDO_PROCESS_POINT_H
#define RDO_PROCESS_POINT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace rp {

// ----------------------------------------------------------------------------
// ---------- point
// ----------------------------------------------------------------------------
class point {
public:
	double x;
	double y;

	point()                        : x( 0 )      , y( 0 )       {};
	point( const rp::point& point ): x( point.x ), y( point.y ) {};
	point( const CPoint& point )   : x( point.x ), y( point.y ) {};
	point( double _x, double _y )  : x( _x )     , y( _y )      {};

	rp::point& operator= ( const rp::point& point ) {
		x = point.x;
		y = point.y;
		return *this;
	}
	operator CPoint() { return CPoint( x, y ); }
};

}

#endif // RDO_PROCESS_POINT_H
