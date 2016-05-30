#pragma once
#include "stdafx.h"

BEGIN_NAMESPACE_2(SSDF,Math)

//project the point 'p' onto line (p0,p1)
Point ProjectPointToLine( const Point& p0, const Point& p1, const Point& p );

//project the point 'p' onto line (p0,p1) with more infomration
void ProjectPointToLine( const Point& p0, const Point& p1, const Point& p, Point& proj, float& t );

//distance from point to line
float DistancePointToLine( const Point& p0, const Point& p1, const Point& p );

//square distance between to points
float SquareDistance( const Point& p0, const Point& p1 );

//distance between points
float Distance( const Point& p0, const Point& p1 );

//clamp x to the range [a,b]
float Clamp( float x, float a, float b );

//smoothstep function from [low,high] to [0,1]
float Smoothstep( float x, float low = 0.0f, float high = 1.0f );

//check if three points are colinear
bool Colinear( const Point& p0, const Point& p1, const Point& p2 );

//signed angle between two vectors
float Angle( const Vec2f& v0, const Vec2f& v1 ); 

//turn-test clockwise or counter-clockwise
//does point p2 lie clockwise or counter-clockwise of line segment p0p1
//positive in a RHS counter-clockwsie vector p0p1
bool TurnTest( const Point& p0, const Point& p1, const Point& p2 );

//finite differences method to calculate derivatives
//assume delta = 2 * epsilon
float FiniteDifferences( float val0, float val1, float epsilon );

//distance from point to line segment
//not needed for now

END_NAMESPACE_2

