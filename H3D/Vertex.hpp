#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif

#include "Vector.hpp"
#include "Color.hpp"

#include "externals.h"
#include STR(GLEW_INCLUDE/gl/glew.h)
/////////////////////////////////////////////////////////////////
//	class Vertex
/////////////////////////////////////////////////////////////////
namespace h3d {
class Vertex
{
public:				 
	h3d::Vec3<GLfloat>  position;
	h3d::Vec2<GLfloat>  texCoord;
	h3d::Vec3<GLfloat>  normal;
};
}
/////////////////////////////////////////////////////////////////