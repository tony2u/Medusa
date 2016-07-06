class Point2F[Suppress,Dir=Geometry/Point2.h]
{
  float X;
  float Y;
};

class Point2U[Suppress,Dir=Geometry/Point2.h]
{
  uint X;
  uint Y;
};

class Size2F[Suppress,Dir=Geometry/Size2.h]
{
  float Width;
  float Height;
};

class Size2U[Suppress,Dir=Geometry/Size2.h]
{
  uint Width;
  uint Height;
};

class Scale2F[Suppress,Dir=Geometry/Scale2.h]
{
  float X;
  float Y;
};

class Scale2U[Suppress,Dir=Geometry/Scale2.h]
{
  uint X;
  uint Y;
};

class Range2F[Suppress,Dir=Geometry/Range2.h]
{
  float X;
  float Y;
};

class Range2U[Suppress,Dir=Geometry/Range2.h]
{
  uint X;
  uint Y;
};


class Rect2F[Suppress,Dir=Geometry/Rect2.h]
{
  Point2F Origin;
  Size2F Size;
};

class Rect2U[Suppress,Dir=Geometry/Rect2.h]
{
	Point2U Origin;
	Size2U Size;
};

class Padding4F[Suppress,Dir=Geometry/Padding4.h]
{
  float Left;
  float Right;
  float Up;
  float Down;
};

class Padding4U[Suppress,Dir=Geometry/Padding4.h]
{
  uint Left;
  uint Right;
  uint Up;
  uint Down;
};


class Color4B[Suppress,Dir=Geometry/Color4.h]
{
  byte R;
  byte G;
  byte B;
  byte A;
};

class Color4F[Suppress,Dir=Geometry/Color4.h]
{
  float R;
  float G;
  float B;
  float A;
};


class PointPath2F[Suppress,Dir=Geometry/PointPath2.h]
{
  List<Point2F> Points;
};