#include <iostream>
#include <cstdlib>
#include "stdafx.h"
#include "demo.h"
#include "util.h"
using namespace SSDF;

int main( int argc, char* argv[] ){
  //bool turn = Math::TurnTest( Point(0,0), Point(1,0), Point(0.5,0.5));  //positive
  //turn = Math::TurnTest( Point(1,0), Point(0,0), Point(0.5,0.5));  //negative
  //cout << "turn is " << turn << endl;
  //return EXIT_SUCCESS;

  //float angle;
  //angle = Math::Angle( Vec2f(1,0), Vec2f(0,1) );    //PI/2
  //angle = Math::Angle( Vec2f(0,1), Vec2f(1,0) );    //-PI/2
  //cout << "angle is " << angle << endl;
  //return EXIT_SUCCESS;

  //Point p = Math::ProjectPointToLine( Point(0.25,0.50), Point(0.75,0.5), Point(0.5,0.0) ); 
  //cout << "projected point is " << p << endl;

  Demo demo;
  //demo.RunSimple();
  demo.Run();
  cv::waitKey();

  //Mat mat( 400, 400, CV_8UC4, cv::Scalar(0));
  //std::vector<int> ints;
  //cv::imshow( "image", mat );
  //cv::waitKey();
  //std::cout << "Hello World" << std::endl;
  return EXIT_SUCCESS;
}
