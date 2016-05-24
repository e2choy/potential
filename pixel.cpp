#include "stdafx.h"
#include "pixel.h"

const Pixel Pixel::WHITE(255,255,255,255);
const Pixel Pixel::GRAY(128,128,128,255);
const Pixel Pixel::BLACK(0,0,0,255);
const Pixel Pixel::BLUE(255,0,0,255);
const Pixel Pixel::GREEN(0,255,0,255);
const Pixel Pixel::RED(0,0,255,255);
const Pixel Pixel::VIOLET(255,0,255,255);
const Pixel Pixel::PURPLE(128,0,128,255);
const Pixel Pixel::CYAN(255,255,0,255);
const Pixel Pixel::YELLOW(0,255,255,255);
const Pixel Pixel::ORANGE(0,128,255,255);

cv::Vec4b Pixel::ToVec4b() const{
  return cv::Vec4b( (uchar)(*this)[0], (uchar)(*this)[1], (uchar)(*this)[2], (uchar)(*this)[3] );
}

