#include <iostream>
#include <cstdlib>
#include "stdafx.h"
#include "demo.h"

using namespace SSDF;

int main( int argc, char* argv[] ){

  Demo demo;
  demo.Run();
  cv::waitKey();

  //Mat mat( 400, 400, CV_8UC4, cv::Scalar(0));
  //std::vector<int> ints;
  //cv::imshow( "image", mat );
  //cv::waitKey();
  //std::cout << "Hello World" << std::endl;
  return EXIT_SUCCESS;
}
