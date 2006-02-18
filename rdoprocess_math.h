#ifndef RDO_PROCESS_MATH_H
#define RDO_PROCESS_MATH_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rdoprocess_point.h"

namespace rp {

class math
{
public:
	static double pi;

	static double getLength( const rp::point& point1, const rp::point& point2 ) {
		try {
			double res = sqrt( (point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y) );
			return res < 1e-10 ? -1 : res;
		} catch (...) {
			return -1;
		}
	}
	static double getDistance( const rp::point& line_point1, const rp::point& line_point2, const rp::point& point, bool* inside = NULL );
	static double getAlpha( const rp::point& p1, const rp::point& p2 );
	static double getAlpha( const rp::point& p1, const rp::point& p2_center, const rp::point& p3 );
	static bool getPlanarData( const rp::point& p1, const rp::point& p2, double& len, double& cos_a, double& sin_a );
	static bool getPlanarData( const rp::point& p1, const rp::point& p2, const rp::point& p3, double& cos_b, double& sin_b, double& koef );
	static rp::point getPerpendicular( const rp::point& line_point1, const rp::point& line_point2, const rp::point& point, bool& null, bool* inside = NULL );
	static rp::point getIntersection( const std::vector< rp::point >& pa, const double x1, const double y1, const double x2, const double y2, const double x3, const double y3, const double x4, const double y4, double& Ka, double& Kb, double& K, double& Ua, double& Ub );
};

}

#endif // RDO_PROCESS_MATH_H
