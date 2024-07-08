#pragma once
#include "stdint.h"


namespace WLD
{
	enum class WLD_API ShaderDataType : uint8_t
	{
		None,
		Bool,
		Int,
		Int1 = Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Vec2 = Float2, Vec3, Vec4,
		Mat2, Mat3, Mat4,
		Mat2x2 = Mat2, Mat3x3, Mat4x4,
		Mat2x3, Mat2x4, Mat3x2, Mat3x4, Mat4x2, Mat4x3,
		Mat2X2 = Mat2, Mat3X3, Mat4X4,
		Mat2X3, Mat2X4, Mat3X2, Mat3X4, Mat4X2, Mat4X3
	};
}