#ifndef RDO_PROCESS_POLYLINE_H
#define RDO_PROCESS_POLYLINE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_point.h"
#include <vector>
#include <algorithm>

namespace rp {

// ----------------------------------------------------------------------------
// ---------- polyline
// ----------------------------------------------------------------------------
class rect;

class polyline: public std::vector< rp::point > {
protected:
	struct trans {
		trans() {};
		CPoint operator()( const rp::point point ) {
			return CPoint( static_cast<int>(point.x), static_cast<int>(point.y) );
		}
	};
public:
	int getMinX() const {
		if ( empty() ) return 0;
		std::vector< rp::point >::const_iterator it = begin();
		int value = static_cast<int>(it->x);
		it++;
		while ( it != end() ) {
			if ( value > it->x ) value = static_cast<int>(it->x);
			it++;
		}
		return value;
	}
	int getMinY() const {
		if ( empty() ) return 0;
		std::vector< rp::point >::const_iterator it = begin();
		int value = static_cast<int>(it->y);
		it++;
		while ( it != end() ) {
			if ( value > it->y ) value = static_cast<int>(it->y);
			it++;
		}
		return value;
	}
	int getMaxX() const {
		if ( empty() ) return 0;
		std::vector< rp::point >::const_iterator it = begin();
		int value = static_cast<int>(it->x);
		it++;
		while ( it != end() ) {
			if ( value < it->x ) value = static_cast<int>(it->x);
			it++;
		}
		return value;
	}
	int getMaxY() const {
		if ( empty() ) return 0;
		std::vector< rp::point >::const_iterator it = begin();
		int value = static_cast<int>(it->y);
		it++;
		while ( it != end() ) {
			if ( value < it->y ) value = static_cast<int>(it->y);
			it++;
		}
		return value;
	}
	rp::rect getBoundingRect() const;
	rp::point getCenter() const {
		return rp::point( (getMaxX() + getMinX()) / 2, (getMaxY() + getMinY()) / 2 );
	}
	bool isPolygon() const {
		if ( size() < 3 ) return false;
		return (*begin() == *(end()-1)) ? true : false;
	}
	bool pointInPolygon( const rp::point& point ) const;
//	void extendFromCenter( double delta );
	polyline& extendByPerimetr( double delta );

	std::vector< CPoint > getWinPolyline() const {
		std::vector< CPoint > pa( size() );
		trans tr;
		std::transform( begin(), end(), pa.begin(), tr );
		return pa;
	}
};

} // namespace rp

#endif // RDO_PROCESS_POLYLINE_H
