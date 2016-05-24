#pragma once
#include "stdafx.h"

BEGIN_NAMESPACE_2(SSDF,Math)

//project the point 'p' onto line (p0,p1)
Point ProjectPointToLine( const Point& p0, const Point& p1, const Point& p );

//distance from point to line
float DistancePointToLine( const Point& p0, const Point& p1, const Point& p );

//square distance between to points
float SquareDistance( const Point& p0, const Point& p1 );

//distance between points
float Distance( const Point& p0, const Point& p1 );

END_NAMESPACE_2

