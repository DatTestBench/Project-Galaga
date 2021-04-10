#include "structs.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window(const std::string& title, const float width, const float height, const bool isVSyncOn)
	: title{ title }
	, width{ width }
	, height{ height }
	, isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f()
	: Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f(const float x, const float y)
	: x{ x }
	, y{ y }
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf()
	: Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf(const float left, const float bottom, const float width, const float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f()
	: Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f(const float r, const float g, const float b, const float a)
	: r{ r }
	, g{ g }
	, b{ b }
	, a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef()
	: Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef(const float centerX, const float centerY, const float radius)
	: Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef(const Point2f& center, const float radius)
	: center{ center }
	, radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef()
	: Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}


Ellipsef::Ellipsef(const Point2f& center, const float radiusX, const float radiusY)
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

Ellipsef::Ellipsef(const float centerX, const float centerY, const float radiusX, const float radiusY)
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}
