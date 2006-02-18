#include "stdafx.h"
#include "rdoprocess_rect.h"
#include "rdoprocess_math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace rp {

// ----------------------------------------------------------------------------
// ---------- rect
// ----------------------------------------------------------------------------
bool rect::pointInRect( const rp::point& point ) const
{
	unsigned int i;
	unsigned int j;
	int k0 = 0;
	bool flag = true;
	for ( i = 0, j = 1; i < 4; i++, j++ ) {
		if ( j == 4 ) j = 0;
		const rp::point& p1 = pa[i];
		const rp::point& p2 = pa[j];
		int k = (point.y - p1.y)*(p2.x - p1.x) - (point.x - p1.x)*(p2.y - p1.y);
		if ( k == 0 ) {
			break;
		} else {
			if ( k0 == 0 ) {
				k0 = k;
			} else {
				if ( k0 * k < 0 ) {
					flag = false;
					break;
				}
			}
		}
	}
	return flag;
}

/*
void rect::extendFromCenter( double delta )
{
	double len, cos_a, sin_a;
	rp::point center = getCenter();
	if ( rp::math::getPlanarData( center, pa[0], len, cos_a, sin_a ) ) {
		len += delta;
		pa[0].x = cos_a * len + center.x;
		pa[0].y = center.y - sin_a * len;
	}
	if ( rp::math::getPlanarData( center, pa[1], len, cos_a, sin_a ) ) {
		len += delta;
		pa[1].x = cos_a * len + center.x;
		pa[1].y = center.y - sin_a * len;
	}
	if ( rp::math::getPlanarData( center, pa[2], len, cos_a, sin_a ) ) {
		len += delta;
		pa[2].x = cos_a * len + center.x;
		pa[2].y = center.y - sin_a * len;
	}
	if ( rp::math::getPlanarData( center, pa[3], len, cos_a, sin_a ) ) {
		len += delta;
		pa[3].x = cos_a * len + center.x;
		pa[3].y = center.y - sin_a * len;
	}
}
*/

rect& rect::extendByPerimetr( double delta )
{
	double cos_b, sin_b, koef;
	if ( rp::math::getPlanarData( pa[3], pa[0], pa[1], cos_b, sin_b, koef ) ) {
		pa[0].x += cos_b * delta;
		pa[0].y -= sin_b * delta;
	}
	if ( rp::math::getPlanarData( pa[0], pa[1], pa[2], cos_b, sin_b, koef ) ) {
		pa[1].x += cos_b * delta;
		pa[1].y -= sin_b * delta;
	}
	if ( rp::math::getPlanarData( pa[1], pa[2], pa[3], cos_b, sin_b, koef ) ) {
		pa[2].x += cos_b * delta;
		pa[2].y -= sin_b * delta;
	}
	if ( rp::math::getPlanarData( pa[2], pa[3], pa[0], cos_b, sin_b, koef ) ) {
		pa[3].x += cos_b * delta;
		pa[3].y -= sin_b * delta;
	}
	return *this;
}

}
