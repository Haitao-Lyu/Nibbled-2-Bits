//********************************************************************************************************************************
//				           ___                         ___                   .-.       .-.                          
//				          (   )                       (   )                 /    \    /    \                        
//				   .-..    | |    .---.   ___  ___     | |.-.    ___  ___   | .`. ;   | .`. ;    .--.    ___ .-.    
//				  /    \   | |   / .-, \ (   )(   )    | /   \  (   )(   )  | |(___)  | |(___)  /    \  (   )   \   
//				 ' .-,  ;  | |  (__) ; |  | |  | |     |  .-. |  | |  | |   | |_      | |_     |  .-. ;  | ' .-. ;  
//				 | |  . |  | |    .'`  |  | |  | |     | |  | |  | |  | |  (   __)   (   __)   |  | | |  |  / (___) 
//				 | |  | |  | |   / .'| |  | '  | |     | |  | |  | |  | |   | |       | |      |  |/  |  | |        
//				 | |  | |  | |  | /  | |  '  `-' |     | |  | |  | |  | |   | |       | |      |  ' _.'  | |        
//				 | |  ' |  | |  ; |  ; |   `.__. |     | '  | |  | |  ; '   | |       | |      |  .'.-.  | |        
//				 | `-'  '  | |  ' `-'  |   ___ | |     ' `-' ;   ' `-'  /   | |       | |      '  `-' /  | |        
//				 | \__.'  (___) `.__.'_.  (   )' |      `.__.     '.__.'   (___)     (___)      `.__.'  (___)       
//				 | |                       ; `-' '                                                                  
//				(___)                       .__.'                                                                  
//
//********************************************************************************************************************************
//                       PlayBuffer: An instructional scaffold for learning C++ through 2D game development
// 
//											Copyright 2020 Sumo Digital Limited
//	   C++ code is made available under the Creative Commons Attribution - No Derivatives 4.0 International Public License 
//									https://creativecommons.org/licenses/by-nd/4.0/legalcode
//********************************************************************************************************************************
#ifndef PLAYPCH_H
#define PLAYPCH_H

#define PLAY_VERSION	"1.1.23.02.01"

#include <cstdint>
#include <cstdlib>
#include <cmath> 
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <future>

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used content from the Windows headers
#define NOMINMAX // Stop windows macros defining their own min and max macros

// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

// Includes the GDI plus headers.
// These are only needed by internal parts of the library.

#include "dwmapi.h"
#include <Shlobj.h>
#pragma warning(push)
#pragma warning(disable:4458) // Suppress warning for declaration of 'xyz' hides class member

 // Redirect the GDI to use the standard library for min and max
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <GdiPlus.h>
#pragma warning(pop)

// Macros for Assertion and Tracing
void TracePrintf(const char* file, int line, const char* fmt, ...);
void AssertFailMessage(const char* message, const char* file, long line );
void DebugOutput( const char* s );
void DebugOutput( std::string s );

#ifdef _DEBUG
#define PLAY_TRACE(fmt, ...) TracePrintf(__FILE__, __LINE__, fmt, __VA_ARGS__);
#define PLAY_ASSERT(x) if(!(x)){ PLAY_TRACE(" *** ASSERT FAIL *** !("#x")\n\n"); AssertFailMessage(#x, __FILE__, __LINE__), __debugbreak(); }
#define PLAY_ASSERT_MSG(x,y) if(!(x)){ PLAY_TRACE(" *** ASSERT FAIL *** !("#x")\n\n"); AssertFailMessage(y, __FILE__, __LINE__), __debugbreak(); }
#else
#define PLAY_TRACE(fmt, ...)
#define PLAY_ASSERT(x) if(!(x)){ AssertFailMessage(#x, __FILE__, __LINE__);  }
#define PLAY_ASSERT_MSG(x,y) if(!(x)){ AssertFailMessage(y, __FILE__, __LINE__); }
#endif // _DEBUG

// Global constants such as PI
constexpr float PLAY_PI	= 3.14159265358979323846f;   // pi

#ifndef PLAY_PLAYMEMORY_H
#define PLAY_PLAYMEMORY_H
//********************************************************************************************************************************
// File:		PlayMemory.h
// Platform:	Independent
// Description:	Declaration for a simple memory tracker to prevent leaks
// Notes:		Not part of the Play namespace as this sits outside of the PlayBuffer framework
//********************************************************************************************************************************
#ifdef _DEBUG
	// Prints out all the currently allocated memory to the debug output
	void PrintAllocations( const char* tagText );

	// Allocate some memory with a known origin
	void* operator new(size_t size, const char* file, int line);
	// Allocate some memory with a known origin
	void* operator new[](size_t size, const char* file, int line); 
	// Allocate some memory without a known origin
	void* operator new[](size_t size);

	// Free some memory 
	void operator delete[](void* p);
	// Free some memory (matching allocator for exceptions )
	void operator delete(void* p, const char* file, int line);
	// Free some memory (matching allocator for exceptions )
	void operator delete[](void* p, const char* file, int line); 

	#define new new( __FILE__ , __LINE__ )
#else
	#define PrintAllocations( x )
#endif

#endif // PLAY_PLAYMEMORY_H
#ifndef PLAY_PLAYMATHS_H
#define PLAY_PLAYMATHS_H
//********************************************************************************************************************************
// File:		PlayMaths.h
// Description:	A very simple set of 2D maths structures and operations
// Platform:	Independent
//********************************************************************************************************************************
namespace Play
{
	struct Vector3f;

	// The main 2D structure used in the library
	#pragma warning (push)
	#pragma warning (disable : 4201) // nonstandard extension used: nameless struct/union
	struct Vector2f
	{
		Vector2f() {}
		// We're encouraging implicit type conversions between float and int with the same number of parameters
		// This is really just to help new players who already suffering from cognitive overload! :-)
		Vector2f(float x, float y) : x(x), y(y) {}
		Vector2f(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
		Vector2f(float x, int y) : x(x), y(static_cast<float>(y)) {}
		Vector2f(int x, float y) : x(static_cast<float>(x)), y(y) {}

		// Different ways of accessing member data
		union
		{
			float v[2];
			struct { float x; float y; };
			struct { float width; float height; };
		};

		// Calculates and returns the length of the vector
		float Length() const;
		// Calculates and returns the length of the vector squared (faster)
		float LengthSqr() const;
		// Scales this vector to a unit length (with the same direction)
		void Normalize();
		// Returns a vector at right angles to this one
		Vector2f Perpendicular() const;
		// Returns true if the vector is euivalent to this one within tolerances (read about floating point accuracy!)
		bool AboutEqualTo(const Vector2f& rhs, const float tolerance) const;
		// Returns the dot product between the  vector provided and this one
		float Dot(const Vector2f& rhs) const;
		// Assignment operator with Vector3f
		Vector2f& operator = (const Vector3f& rhs);
		// Copy constructor with Vector3f
		Vector2f(const Vector3f& rhs);
	};

	// A point is conceptually different to a vector, but maps to Vector2f/Vector3f for ease of use
	using Point2f = Vector2f;
	using Point2D = Vector2f;
	using Vector2D = Vector2f;

	// A 2D vector with a w component for use with matrices
	struct Vector3f
	{
		Vector3f() {}
		Vector3f(float x, float y, float w) : x(x), y(y), w(w) {}
		//Vector3f( Vector2f v ) : x( v.x ), y( v.y ), w( 1.0f ) {}

		// Different ways of accessing member data
		union
		{
			float v[3];
			struct { float x; float y; float w; };
			struct { float width; float height; float w; };
		};

		// Returns the 2D part of the 3D vector
		Vector2f As2D() const { return Vector2f(x, y); }
		// Calculates and returns the length of the vector
		float Length() const;
		// Calculates and returns the length of the vector squared (faster)
		float LengthSqr() const;
		// Scales this vector to a unit length (with the same direction)
		void Normalize();
		// Returns a vector at right angles to this one
		Vector3f Perpendicular() const;
		// Returns true if the vector is euivalent to this one within tolerances (read about floating point accuracy!)
		bool AboutEqualTo(const Vector3f& rhs, const float tolerance) const;
		// Returns the dot product between the  vector provided and this one
		float Dot(const Vector3f& rhs) const;
		// Assignment operator with Vector2f
		Vector3f& operator = (const Vector2f& rhs);
		// Copy constructor with Vector3f
		Vector3f(const Vector2f& rhs);
	};
#pragma warning(pop)



	using Point3f = Vector3f;
	using Point3D = Vector3f;
	using Vector3D = Vector3f;

	// Vector assignment and copy operations
	//**************************************************************************************************

	inline Vector2f& Vector2f::operator = (const Vector3f& rhs)
	{
		v[0] = rhs.v[0];
		v[1] = rhs.v[1];
		return *this;
	}

	inline Vector2f::Vector2f(const Vector3f& rhs)
	{
		v[0] = rhs.v[0];
		v[1] = rhs.v[1];
	}

	inline Vector3f& Vector3f::operator = (const Vector2f& rhs)
	{
		v[0] = rhs.v[0];
		v[1] = rhs.v[1];
		v[2] = 0.0f;
		return *this;
	}

	inline Vector3f::Vector3f(const Vector2f& rhs)
	{
		v[0] = rhs.v[0];
		v[1] = rhs.v[1];
		v[2] = 0.0f;
	}

	// Vector component operations
	//**************************************************************************************************

	// Vector component addition
	inline Vector2f operator + (const Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs.v[i] + rhs.v[i];

		return ret;
	}

	inline Vector3f operator + (const Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs.v[i] + rhs.v[i];

		return ret;
	}

	// Vector component assignment addition
	inline Vector2f& operator += (Vector2f& lhs, const Vector2f& rhs)
	{
		for (int i = 0; i < 2; ++i)
			lhs.v[i] += rhs.v[i];

		return lhs;
	}

	inline Vector3f& operator += (Vector3f& lhs, const Vector3f& rhs)
	{
		for (int i = 0; i < 3; ++i)
			lhs.v[i] += rhs.v[i];

		return lhs;
	}

	// Vector component subtraction
	inline Vector2f operator - (const Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs.v[i] - rhs.v[i];

		return ret;
	}

	inline Vector3f operator - (const Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs.v[i] - rhs.v[i];

		return ret;
	}

	// Vector component assignment subtraction
	inline Vector2f& operator -= (Vector2f& lhs, const Vector2f& rhs)
	{
		for (int i = 0; i < 2; ++i)
			lhs.v[i] -= rhs.v[i];

		return lhs;
	}

	inline Vector3f& operator -= (Vector3f& lhs, const Vector3f& rhs)
	{
		for (int i = 0; i < 3; ++i)
			lhs.v[i] -= rhs.v[i];

		return lhs;
	}

	// Vector component unary negation
	inline Vector2f operator - (const Vector2f& op)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = -op.v[i];

		return ret;
	}

	inline Vector3f operator - (const Vector3f& op)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = -op.v[i];

		return ret;
	}

	// Vector component multiplication
	inline Vector2f operator * (const Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs.v[i] * rhs.v[i];

		return ret;
	}

	inline Vector3f operator * (const Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs.v[i] * rhs.v[i];

		return ret;
	}

	// Vector component assignment multiplication
	inline Vector2f operator *= (Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			lhs.v[i] *= rhs.v[i];

		return lhs;
	}

	inline Vector3f operator *= (Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			lhs.v[i] *= rhs.v[i];

		return lhs;
	}

	// Vector component division
	inline Vector2f operator / (const Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs.v[i] / rhs.v[i];

		return ret;
	}

	inline Vector3f operator / (const Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs.v[i] / rhs.v[i];

		return ret;
	}

	// Vector component assignment division
	inline Vector2f operator /= (Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			lhs.v[i] /= rhs.v[i];

		return lhs;
	}

	inline Vector3f operator /= (Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			lhs.v[i] /= rhs.v[i];

		return lhs;
	}

	// Vector scalar operations
	//**************************************************************************************************

	// Vector scalar multiplication
	inline Vector2f operator * (const Vector2f& lhs, const float rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs.v[i] * rhs;

		return ret;
	}

	inline Vector3f operator * (const Vector3f& lhs, const float rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs.v[i] * rhs;

		return ret;
	}

	// Vector scalar multiplication (reverse operands)
	inline Vector2f operator * (const float lhs, const Vector2f& rhs)
	{
		return rhs * lhs;
	}

	inline Vector3f operator * (const float lhs, const Vector3f& rhs)
	{
		return rhs * lhs;
	}

	// Vector scalar assignment multiplication
	inline Vector2f operator *= (Vector2f& lhs, const float& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			lhs.v[i] *= rhs;

		return lhs;
	}

	inline Vector3f operator *= (Vector3f& lhs, const float& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			lhs.v[i] *= rhs;

		return lhs;
	}

	// Vector scalar division
	inline Vector2f operator / (const Vector2f& lhs, const float rhs)
	{
		return lhs * (float(1) / rhs);
	}

	inline Vector3f operator / (const Vector3f& lhs, const float rhs)
	{
		return lhs * (float(1) / rhs);
	}


	// Vector scalar division (reverse operands)
	inline Vector2f operator / (const float lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			ret.v[i] = lhs / rhs.v[i];

		return ret;
	}

	inline Vector3f operator / (const float lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			ret.v[i] = lhs / rhs.v[i];

		return ret;
	}

	// Vector scalar assignment multiplication
	inline Vector2f operator /= (Vector2f& lhs, const float& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
			lhs.v[i] /= rhs;

		return lhs;
	}

	inline Vector3f operator /= (Vector3f& lhs, const float& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
			lhs.v[i] /= rhs;

		return lhs;
	}

	// Vector component comparisons
	//**************************************************************************************************

	// Vector components exactly equal
	inline bool operator == (const Vector2f& lhs, const Vector2f& rhs)
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
		{
			if (lhs.v[i] != rhs.v[i])
				return false;
		}
		return true;
	}

	inline bool operator == (const Vector3f& lhs, const Vector3f& rhs)
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
		{
			if (lhs.v[i] != rhs.v[i])
				return false;
		}
		return true;
	}

	// Vector components not equal
	inline bool operator != (const Vector2f& lhs, const Vector2f& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator != (const Vector3f& lhs, const Vector3f& rhs)
	{
		return !(lhs == rhs);
	}

	// Vector components equal to within specified tolerance.
	inline bool Vector2f::AboutEqualTo(const Vector2f& rhs, const float tolerance) const
	{
		Vector2f ret;
		for (int i = 0; i < 2; ++i)
		{
			if (std::abs(v[i] - rhs.v[i]) > tolerance)
				return false;
		}
		return true;
	}

	inline bool Vector3f::AboutEqualTo(const Vector3f& rhs, const float tolerance) const
	{
		Vector3f ret;
		for (int i = 0; i < 3; ++i)
		{
			if (std::abs(v[i] - rhs.v[i]) > tolerance)
				return false;
		}
		return true;
	}

	// Common maths functions
	//**************************************************************************************************

	// Dot product
	inline float  Vector2f::Dot(const Vector2f& rhs) const
	{
		float ret = 0.f;
		for (int i = 0; i < 2; ++i)
			ret += v[i] * rhs.v[i];

		return ret;
	}

	inline float dot(const Vector2f& lhs, const Vector2f& rhs)
	{
		return lhs.Dot(rhs);
	}


	inline float Vector3f::Dot(const Vector3f& rhs) const
	{
		float ret = 0.f;
		for (int i = 0; i < 3; ++i)
			ret += v[i] * rhs.v[i];

		return ret;
	}

	inline float dot(const Vector3f& lhs, const Vector3f& rhs)
	{
		return lhs.Dot(rhs);
	}

	// Orthogonal vector
	inline Vector2f Vector2f::Perpendicular() const
	{
		Vector2f ret;
		ret.v[0] = -v[1];
		ret.v[1] = v[0];
		return ret;
	}

	// Orthogonal vector
	inline Vector2f perpendicular(const Vector3f& rhs)
	{
		Vector2f ret;
		ret.v[0] = -rhs.v[1];
		ret.v[1] = rhs.v[0];
		return ret;
	}

	// Vector length squared
	inline float Vector2f::LengthSqr() const
	{
		return Dot(*this);
	}

	inline float Vector3f::LengthSqr() const
	{
		return Dot(*this);
	}

	inline float lengthSqr(const Vector2f& v)
	{
		return dot(v, v);
	}

	inline float lengthSqr(const Vector3f& v)
	{
		return dot(v, v);
	}

	// Vector length
	inline float Vector2f::Length() const
	{
		return sqrt(Dot(*this));
	}

	inline float Vector3f::Length() const
	{
		return sqrt(Dot(*this));
	}

	inline float length(const Vector2f& v)
	{
		return sqrt(dot(v, v));
	}

	inline float length(const Vector3f& v)
	{
		return sqrt(dot(v, v));
	}

	// Vector normalize
	inline void Vector2f::Normalize()
	{
		*this /= Length();
	}

	inline Vector2f normalize(const Vector2f& v)
	{
		return v / v.Length();
	}

	inline void Vector3f::Normalize()
	{
		*this /= Length();
	}

	inline Vector3f normalize(const Vector3f& v)
	{
		return v / v.Length();
	}

	// A 3x3 structure for representing 2D matrices
	struct Matrix2D
	{
		Matrix2D() {}
		explicit Matrix2D(const Vector3f& row0, const Vector3f& row1, const Vector3f& row2)
			: row{ row0, row1, row2 }
		{
		}
		union
		{
			float m[3][3];
			Vector3f row[3] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };
		};

		// Transforms a vector by this matrix
		Vector2f Transform(const Vector3f& v) const;
		// Transforms a vector by this matrix
		Vector2f Transform(const Vector2f& v) const;
		// Transposes the matrix (swaps the columns and rows)
		void Transpose();
		// Compares this matrix to another within a tolerance (read about floating point inaccuracies!)
		bool AboutEqualTo(const Matrix2D& rhs, const float tolerance) const;
		// Inverts this matrix (makes it perform the opposite operation)
		void Inverse();
	};

	// Matrix addition
	inline Matrix2D operator + (const Matrix2D& lhs, const Matrix2D& rhs)
	{
		Matrix2D ret;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				ret.m[i][j] = lhs.m[i][j] + rhs.m[i][j];

		return ret;
	}

	// Matrix subtraction
	inline Matrix2D operator - (const Matrix2D& lhs, const Matrix2D& rhs)
	{
		Matrix2D ret;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				ret.m[i][j] = lhs.m[i][j] - rhs.m[i][j];

		return ret;
	}

	// Matrix multiplication
	inline Matrix2D operator * (const Matrix2D& lhs, const Matrix2D& rhs)
	{
		Matrix2D ret;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				float t = 0;
				for (int k = 0; k < 3; ++k)
					t += lhs.m[k][i] * rhs.m[j][k];

				ret.m[j][i] = t;
			}
		}
		return ret;
	}

	// Multipy a vector by a matrix
	inline Vector2f Matrix2D::Transform(const Vector2f& v) const
	{
		Vector3f v3 = v;
		v3.w = 1.0f;
		return Transform(v3);
	}

	// Multipy a vector by a matrix
	inline Vector2f Matrix2D::Transform(const Vector3f& v) const
	{
		Vector3f ret;

		for (int i = 0; i < 3; ++i)
		{
			ret.v[i] = float(0);
			for (int j = 0; j < 3; ++j)
				ret.v[i] += m[j][i] * v.v[j];
		}
		return Vector2f(ret.x, ret.y);
	}

	// Transpose the contents of a matrix
	inline void Matrix2D::Transpose()
	{
		Matrix2D temp;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
				temp.m[j][i] = m[i][j];
		}
		*this = temp;
	}

	// Create an identity matrix
	inline Matrix2D MatrixIdentity()
	{
		Matrix2D mat;
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				mat.m[i][j] = (i == j) ? float(1) : 0;
		return mat;
	}

	// Create a rotation matrix
	inline Matrix2D MatrixRotation(const float theta)
	{
		float c = cos(theta);
		float s = sin(theta);

		return Matrix2D(
			Vector3f(c, -s, 0),
			Vector3f(s, c, 0),
			Vector3f(0, 0, 1)
		);
	}

	// Create a scaling matrix
	inline Matrix2D MatrixScale(const float x, const float y)
	{
		return Matrix2D(
			Vector3f(x, 0, 0),
			Vector3f(0, y, 0),
			Vector3f(0, 0, 1)
		);
	}

	// Create a translation matrix
	inline Matrix2D MatrixTranslation(const float x, const float y)
	{
		return Matrix2D(
			Vector3f(1, 0, 0),
			Vector3f(0, 1, 0),
			Vector3f(x, y, 1)
		);
	}

	// Compare two matrices within a tolerance value
	inline bool Matrix2D::AboutEqualTo(const Matrix2D& rhs, const float tolerance) const
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (std::abs(m[i][j] - rhs.m[i][j]) > tolerance)
					return false;
			}
		}
		return true;
	}

	// Calculate the determinant of a 2x2 matrix
	inline float Determinant(const Matrix2D& m)
	{
		return m.m[0][0] * m.m[1][1] * m.m[2][2]
			+ m.m[1][0] * m.m[2][1] * m.m[0][2]
			+ m.m[2][0] * m.m[0][1] * m.m[1][2]
			- m.m[0][0] * m.m[2][1] * m.m[1][2]
			- m.m[1][0] * m.m[0][1] * m.m[2][2]
			- m.m[2][0] * m.m[1][1] * m.m[0][2];
	}

	inline float det2x2(float a, float b, float c, float d)
	{
		return a * d - b * c;
	}

	// Calculate the inverse of a 2D matrix
	inline void Matrix2D::Inverse()
	{
		float d = Determinant(*this);
		PLAY_ASSERT_MSG(d != 0.f, "Zero determinant");

		float f = float(1) / d;

		float c00 = det2x2(m[1][1], m[2][1], m[1][2], m[2][2]) * f;
		float c10 = det2x2(m[0][1], m[2][1], m[0][2], m[2][2]) * -f;
		float c20 = det2x2(m[0][1], m[1][1], m[0][2], m[1][2]) * f;

		float c01 = det2x2(m[1][0], m[2][0], m[1][2], m[2][2]) * -f;
		float c11 = det2x2(m[0][0], m[2][0], m[0][2], m[2][2]) * f;
		float c21 = det2x2(m[0][0], m[1][0], m[0][2], m[1][2]) * -f;

		float c02 = det2x2(m[1][0], m[2][0], m[1][1], m[2][1]) * f;
		float c12 = det2x2(m[0][0], m[2][0], m[0][1], m[2][1]) * -f;
		float c22 = det2x2(m[0][0], m[1][0], m[0][1], m[1][1]) * f;

		row[0] = Vector3f(c00, c10, c20);
		row[1] = Vector3f(c01, c11, c21);
		row[2] = Vector3f(c02, c12, c22);
	}

}
#endif // PLAY_PLAYMATHS_H
#ifndef PLAY_PLAYPIXEL_H
#define PLAY_PLAYPIXEL_H
//********************************************************************************************************************************
// File:		PlayPixel.h
// Platform:	Independent
// Description:	Pixel types for holding image data
//********************************************************************************************************************************
namespace Play
{
	// A pixel structure to represent an ARBG format pixel
	struct Pixel
	{
		Pixel() {}
		Pixel(uint32_t bits) : bits(bits) {}
		Pixel(float r, float g, float b) :
			a(0xFF), r(static_cast<uint8_t>(r)), g(static_cast<uint8_t>(g)), b(static_cast<uint8_t>(b))
		{
		}
		Pixel(int r, int g, int b) :
			a(0xFF), r(static_cast<uint8_t>(r)), g(static_cast<uint8_t>(g)), b(static_cast<uint8_t>(b))
		{
		}
		Pixel(int a, int r, int g, int b) :
			a(static_cast<uint8_t>(a)), r(static_cast<uint8_t>(r)), g(static_cast<uint8_t>(g)), b(static_cast<uint8_t>(b))
		{
		}

		union
		{
			uint32_t bits{ 0xFF000000 }; // Alpha set to opaque by default
			struct { uint8_t b, g, r, a; }; // This order corresponds to ( a<<24 | r<<16 | g<<8 | b )
		};
	};

	const Pixel PIX_BLACK{ 0x00, 0x00, 0x00 };
	const Pixel PIX_WHITE{ 0xFF, 0xFF, 0xFF };
	const Pixel PIX_RED{ 0xFF, 0x00, 0x00 };
	const Pixel PIX_GREEN{ 0x00, 0x8F, 0x00 };
	const Pixel PIX_BLUE{ 0x00, 0x00, 0xFF };
	const Pixel PIX_MAGENTA{ 0xFF, 0x00, 0xFF };
	const Pixel PIX_CYAN{ 0x00, 0xFF, 0xFF };
	const Pixel PIX_YELLOW{ 0xFF, 0xFF, 0x00 };
	const Pixel PIX_ORANGE{ 0xFF, 0x8F, 0x00 };
	const Pixel PIX_GREY{ 0x80, 0x80, 0x80 };
	const Pixel PIX_TRANS{ 0x00, 0x00, 0x00, 0x00 };


	struct PixelData
	{
		int width{ 0 };
		int height{ 0 };
		Pixel* pPixels{ nullptr };
		bool preMultiplied = false;
	};

	struct BlendColour
	{
		float alpha{ 1.0f };
		float red{ 1.0f };
		float green{ 1.0f };
		float blue{ 1.0f };
	};
}
#endif // PLAY_PLAYPIXEL_H
#ifndef PLAY_PLAYMOUSE_H
#define PLAY_PLAYMOUSE_H
//********************************************************************************************************************************
// File:		PlayMouse.h
// Platform:	Independent
// Description:	A mouse input data type 
// Notes:		Shared between Play::Input and Play::Window
//********************************************************************************************************************************
namespace Play
{
	// A mouse structure to hold pointer co-ordinates and button states
	struct MouseData
	{
		Vector2f pos{ 0, 0 };
		bool left{ false };
		bool right{ false };
	};
}
#endif // PLAY_PLAYMOUSE_H
#ifndef PLAY_PLAYWINDOW_H
#define PLAY_PLAYWINDOW_H
//********************************************************************************************************************************
// File:		PlayWindow.h
// Description:	Platform specific code to provide a window to draw into
// Platform:	Windows
// Notes:		Uses a 32-bit ARGB display buffer
//********************************************************************************************************************************

// The target frame rate
constexpr int FRAMES_PER_SECOND = 60;

// Some defines to hide the complexity of arguments 
#define PLAY_IGNORE_COMMAND_LINE	int, char*[]

constexpr int PLAY_OK = 0;
constexpr int PLAY_ERROR = -1;

namespace Play::Window
{
	// Create/Destroy functions
	//********************************************************************************************************************************

	// Initialises the Window Manager
	bool CreateManager( PixelData* pDisplayBuffer, int nScale );
	// Destroys the Window Manager
	bool DestroyManager();

	// Windows functions
	//********************************************************************************************************************************

	// Call within WInMain to hand control of Windows functionality over to the PlayWindow class
	int HandleWindows( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow, LPCWSTR windowName );
	// Handles Windows messages for the PlayWindow  
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	// Copies the display buffer pixels to the window
	// > Returns the time taken for the present in seconds
	double Present();
	// Sets the pointer to write mouse input data to
	void RegisterMouse(Play::MouseData* pMouseData);

	// Getter functions
	//********************************************************************************************************************************

	// Gets the width of the display buffer in pixels
	int GetWidth();
	// Gets the height of the display buffer in pixels 
	int GetHeight();
	// Gets the scale of the display buffer in pixels
	int GetScale();

};

// Loading functions
//********************************************************************************************************************************

// Reads the width and height of a png image
int ReadPNGImage( std::string& fileAndPath, int& width, int& height );
// Loads a png image and puts the image data into the destination image provided
int LoadPNGImage( std::string& fileAndPath, Play::PixelData& destImage );

#endif // PLAY_PLAYWINDOW_H
#ifndef PLAY_PLAYBLENDS_H
#define PLAY_PLAYBLENDS_H
//********************************************************************************************************************************
// File:		PlayBlends.h
// Description:	A set of software pixel blending operations
// Platform:	Independent
//********************************************************************************************************************************

namespace Play::Render
{

	inline void Skip(uint32_t*& srcPixels, uint32_t*& destPixels, const uint32_t* destRowEnd)
	{
		// If this is a fully transparent pixel then the low bits store how many there are in a row
		// This means we can skip to the next pixel which isn't fully transparent
		uint32_t skip = static_cast<uint32_t>(destRowEnd - destPixels) - 1;
		uint32_t src = *srcPixels & 0x00FFFFFF;
		if (skip > src) skip = src;
		srcPixels += skip + 1;
		++destPixels += skip;
	}

	class AlphaBlendPolicy
	{
	public:

		static inline void BlendSkip(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply, const uint32_t* destRowEnd)
		{
			if (Blend(srcPixels, destPixels, globalMultiply))
				srcPixels++, destPixels++;
			else
				Skip(srcPixels, destPixels, destRowEnd);
		}

		static inline void BlendFastSkip(uint32_t*& srcPixels, uint32_t*& destPixels, const uint32_t* destRowEnd)
		{
			if (BlendFast(srcPixels, destPixels))
				srcPixels++, destPixels++;
			else
				Skip(srcPixels, destPixels, destRowEnd);
		}

		// *******************************************************************************************************************************************************
		// A basic approach which separates the channels and performs a 'typical' alpha blending operation: (src * srcAlpha)+(dest * (1-srcAlpha))
		// Has the advantage that a global alpha multiplication can be easily added over the top, so we use this method when a global multiply is required
		// Notes: Requires a source buffer which has the source alpha pre-multiplied
		// *******************************************************************************************************************************************************
		static inline bool Blend(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply)
		{
			if (*srcPixels > 0xFF000000) return false; // No pixels to draw( fully transparent )

			uint32_t src = *srcPixels;
			uint32_t dest = *destPixels;

			uint32_t srcAlpha = static_cast<int>((0xFF - (src >> 24)) * globalMultiply.alpha);
			uint32_t constAlpha = static_cast<int>(0xFF * globalMultiply.alpha);

			// Source pixels are already multiplied by srcAlpha so we just apply the constant alpha multiplier
			uint32_t destRed = constAlpha * ((src >> 16) & 0xFF);
			uint32_t destGreen = constAlpha * ((src >> 8) & 0xFF);
			uint32_t destBlue = constAlpha * (src & 0xFF);

			uint32_t invSrcAlpha = 0xFF - srcAlpha;

			// Apply a standard Alpha blend [ src*srcAlpha + dest*(1-SrcAlpha) ]
			destRed += invSrcAlpha * ((dest >> 16) & 0xFF);
			destGreen += invSrcAlpha * ((dest >> 8) & 0xFF);
			destBlue += invSrcAlpha * (dest & 0xFF);

			// Bring back to the range 0-255
			destRed >>= 8;
			destGreen >>= 8;
			destBlue >>= 8;

			// Put ARGB components back together again
			*destPixels = 0xFF000000 | (destRed << 16) | (destGreen << 8) | destBlue;

			return true;
		}

		// *******************************************************************************************************************************************************
		// An optimized approach which uses pre-multiplied alpha, parallel channel multiplication and pixel skipping to achieve the same 'typical' alpha 
		// blending operation (src * srcAlpha)+(dest * (1-srcAlpha)). Not easy to apply a global alpha multiplication over the top, but used everywhere else.
		// Notes: Requires a source buffer which has the source alpha pre-multiplied
		// *******************************************************************************************************************************************************
		static inline bool BlendFast(uint32_t*& srcPixels, uint32_t*& destPixels)
		{
			if (*srcPixels > 0xFF000000) return false; // No pixels to draw( fully transparent )

			// This performs the dest*(1-srcAlpha) calculation for all channels in parallel with minor accuracy loss in dest colour.
			// It does this by shifting all the destination channels down by 4 bits in order to "make room" for the later multiplication.
			// After shifting down, it masks out the bits which have shifted into the adjacent channel data.
			// This causes the RGB data to be rounded down to their nearest 16 producing a reduction in colour accuracy.
			// This is then multiplied by the inverse alpha (inversed in PreMultiplyAlpha), also divided by 16 (hence >> 8+8+8+4).
			// The multiplication brings our RGB values back up to their original bit ranges (albeit rounded to the nearest 16).
			// As the colour accuracy only affects the destination pixels behind semi-transparent source pixels and so isn't very obvious.
			uint32_t dest = (((*destPixels >> 4) & 0x000F0F0F) * (*srcPixels >> 28));
			// Add the (pre-multiplied Alpha) source to the destination and force alpha to opaque
			*destPixels = (*srcPixels + dest) | 0xFF000000;

			return true;
		}
	};




	class AdditiveBlendPolicy
	{
	public:

		static inline void BlendSkip(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply, const uint32_t* destRowEnd)
		{
			if (Blend(srcPixels, destPixels, globalMultiply))
				srcPixels++, destPixels++;
			else
				Skip(srcPixels, destPixels, destRowEnd);
		}

		static inline void BlendFastSkip(uint32_t*& srcPixels, uint32_t*& destPixels, const uint32_t* destRowEnd)
		{
			if (Blend(srcPixels, destPixels, { 1.0f, 1.0f, 1.0f, 1.0f }))
				srcPixels++, destPixels++;
			else
				Skip(srcPixels, destPixels, destRowEnd);
		}

		// *******************************************************************************************************************************************************
		// A basic approach which separates the channels and performs an additive blending operation: (src * srcAlpha)+(dest * destAlpha)
		// Has the advantage that a global alpha multiplication can be easily added over the top, so we use this method when a global multiply is required
		// Notes: Requires a source buffer which has the source alpha pre-multiplied
		// *******************************************************************************************************************************************************
		static inline bool Blend(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply)
		{
			if (*srcPixels > 0xFF000000) return false; // No pixels to draw( fully transparent )

			uint32_t src = *srcPixels;
			uint32_t dest = *destPixels;

			// Keep the blended alpha calculation in the high bits
			uint32_t destAlpha = dest >> 24;
			uint32_t srcAlpha = 0xFF - (src >> 24);
			uint32_t blendedAlpha = srcAlpha + destAlpha;

			// Source pixels are already multiplied by srcAlpha so we just apply the constant alpha multiplier
			uint32_t blendedRed = (uint32_t)( globalMultiply.alpha * globalMultiply.red * ((src >> 8) & 0xFF00));
			uint32_t blendedGreen = (uint32_t)( globalMultiply.alpha * globalMultiply.green * (src & 0xFF00));
			uint32_t blendedBlue = (uint32_t)( globalMultiply.alpha * globalMultiply.blue * ((src << 8) & 0xFF00));

			// Apply an additive blend [ src*srcAlpha + dest*destAlpha ]
			blendedRed += 0xFF * ((dest >> 16) & 0xFF);
			blendedGreen += 0xFF * ((dest >> 8) & 0xFF);
			blendedBlue += 0xFF * (dest & 0xFF);

			// Bring back to the range 0-255
			blendedRed >>= 8;
			blendedGreen >>= 8;
			blendedBlue >>= 8;

			if (blendedAlpha > 0xFF) blendedAlpha = 0xFF;
			if (blendedRed > 0xFF) blendedRed = 0xFF;
			if (blendedGreen > 0xFF) blendedGreen = 0xFF;
			if (blendedBlue > 0xFF) blendedBlue = 0xFF;

			// Put ARGB components back together again
			*destPixels = (blendedAlpha << 24) | (blendedRed << 16) | (blendedGreen << 8) | blendedBlue;

			return true;
		}
	};

	class MultiplyBlendPolicy
	{
	public:

		static inline void BlendSkip(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply, const uint32_t*)
		{
			Blend(srcPixels, destPixels, globalMultiply);
			srcPixels++, destPixels++;
		}

		static inline void BlendFastSkip(uint32_t*& srcPixels, uint32_t*& destPixels, const uint32_t*)
		{
			Blend(srcPixels, destPixels, { 1.0f, 1.0f, 1.0f, 1.0f });
			srcPixels++, destPixels++;
		}

		// *******************************************************************************************************************************************************
		// A basic approach which separates the channels and performs an additive blending operation: (src * srcAlpha)+(dest * destAlpha)
		// Has the advantage that a global alpha multiplication can be easily added over the top, so we use this method when a global multiply is required
		// Notes: Requires a source buffer which has the source alpha unmodified
		// *******************************************************************************************************************************************************
		static inline void Blend(uint32_t*& srcPixels, uint32_t*& destPixels, BlendColour globalMultiply)
		{
			if (*srcPixels < 0x00FFFFFF) return; // No pixels to draw( fully transparent )

			uint32_t src = *srcPixels;
			uint32_t dest = *destPixels;

			// Source pixels
			uint32_t srcAlpha = src >> 24;
			uint32_t srcRed = (src >> 16) & 0xFF;
			uint32_t srcGreen = (src >> 8) & 0xFF;
			uint32_t srcBlue = src & 0xFF;

			// Destination pixels
			uint32_t destAlpha = dest >> 24;
			uint32_t destRed = (dest >> 16) & 0xFF;
			uint32_t destGreen = (dest >> 8) & 0xFF;
			uint32_t destBlue = dest & 0xFF;

			// Apply a multiplicative blend [ dest*invSrcAlpha + (src*dest)*srcAlpha ]
			uint32_t blendAlpha = static_cast<int>(srcAlpha * globalMultiply.alpha);
			uint32_t invBlendAlpha = (0xFF - blendAlpha) * 0xFF;
			uint32_t blendRed = (destRed * invBlendAlpha) + ((srcRed * destRed) * blendAlpha);
			uint32_t blendGreen = (destGreen * invBlendAlpha) + ((srcGreen * destGreen) * blendAlpha);
			uint32_t blendBlue = (destBlue * invBlendAlpha) + ((srcBlue * destBlue) * blendAlpha);

			// Bring back to the range 0-255
			blendRed >>= 16;
			blendGreen >>= 16;
			blendBlue >>= 16;

			// Shouldn't be necessary
			if (blendRed > 0xFF) blendRed = 0xFF;
			if (blendGreen > 0xFF) blendGreen = 0xFF;
			if (blendBlue > 0xFF) blendBlue = 0xFF;

			// Put ARGB components back together again
			*destPixels = (destAlpha << 24) | (blendRed << 16) | (blendGreen << 8) | blendBlue;
		}
	};

}

#endif
#ifndef PLAY_PLAYRENDER_H
#define PLAY_PLAYRENDER_H
//********************************************************************************************************************************
// File:		PlayRender.h
// Description:	A software pixel renderer for drawing 2D primitives into a PixelData buffer
// Platform:	Independent
// Notes:		The only internal state/data stored by the renderer is a pointer to the render target
//********************************************************************************************************************************

namespace Play::Render
{
	// Set the render target for all subsequent drawing operations
	// Returns a pointer to any previous render target
	PixelData* SetRenderTarget( PixelData* pRenderTarget );

	extern PixelData* m_pRenderTarget;

	// Primitive drawing functions
	//********************************************************************************************************************************

	// Sets the colour of an individual pixel on the render target
	template< typename TBlend > void DrawPixel(int posX, int posY, Pixel pix);
	// Sets the colour of an individual pixel on the render target
	template< typename TBlend > void DrawPixelPreMult(int posX, int posY, Pixel pix);

	// Draws a line of pixels into the render target
	void DrawLine( int startX, int startY, int endX, int endY, Pixel pix );
	// Draws pixel data to the render target using a direct copy
	// > Setting alphaMultiply < 1 forces a less optimal rendering approach (~50% slower) 
	template< typename TBlend > void BlitPixels(const PixelData& srcImage, int srcOffset, int blitX, int blitY, int blitWidth, int blitHeight, BlendColour globalMultiply );
	// Draws rotated and scaled pixel data to the render target (much slower than BlitPixels)
	// > Setting alphaMultiply < 1 is not much slower overall (~10% slower) 
	template< typename TBlend > void RotateScalePixels(const PixelData& srcPixelData, int srcFrameOffset, int srcWidth, int srcHeight, const Point2f& origin, const Matrix2D& m, BlendColour globalMultiply);
	// Clears the render target using the given pixel colour
	void ClearRenderTarget( Pixel colour );
	// Copies a background image of the correct size to the render target
	void BlitBackground( PixelData& backgroundImage );


	//********************************************************************************************************************************
	// Function:	BlitPixels - draws image data with and without a global alpha multiply
	// Parameters:	spriteId = the id of the sprite to draw
	//				xpos, ypos = the position you want to draw the sprite
	//				frameIndex = which frame of the animation to draw (wrapped)
	// Notes:		Blend implmentation depends on TBlend class (see PlayBlends.h) - should all end up inlined!
	//********************************************************************************************************************************
	template< typename TBlend > void BlitPixels(const PixelData& srcPixelData, int srcOffset, int blitX, int blitY, int blitWidth, int blitHeight, BlendColour globalMultiply)
	{
		blitY = m_pRenderTarget->height - blitY; // Flip the y-coordinate to be consistant with a Cartesian co-ordinate system

		// Nothing within the display buffer to draw
		if (blitX > m_pRenderTarget->width || blitX + blitWidth < 0 || blitY > m_pRenderTarget->height || blitY + blitHeight < 0)
			return;

		// Work out if we need to clip to the display buffer (and by how much)
		int xClipStart = -blitX;
		if (xClipStart < 0) { xClipStart = 0; }

		int xClipEnd = (blitX + blitWidth) - m_pRenderTarget->width;
		if (xClipEnd < 0) { xClipEnd = 0; }

		int yClipStart = -blitY;
		if (yClipStart < 0) { yClipStart = 0; }

		int yClipEnd = (blitY + blitHeight) - m_pRenderTarget->height;
		if (yClipEnd < 0) { yClipEnd = 0; }

		// Set up the source and destination pointers based on clipping
		int destOffset = (m_pRenderTarget->width * (blitY + yClipStart)) + (blitX + xClipStart);
		uint32_t* destPixels = &m_pRenderTarget->pPixels->bits + destOffset;

		int srcClipOffset = (srcPixelData.width * yClipStart) + xClipStart;
		uint32_t* srcPixels = &srcPixelData.pPixels->bits + srcOffset + srcClipOffset;

		// Work out in advance how much we need to add to src and dest to reach the next row 
		int destInc = m_pRenderTarget->width - blitWidth + xClipEnd + xClipStart;
		int srcInc = srcPixelData.width - blitWidth + xClipEnd + xClipStart;

		//Work out final pixel in destination.
		int destColOffset = (m_pRenderTarget->width * (blitHeight - yClipEnd - yClipStart - 1)) + (blitWidth - xClipEnd - xClipStart);
		uint32_t* destColEnd = destPixels + destColOffset;

		//How many pixels per row in sprite.
		int endRow = blitWidth - xClipEnd - xClipStart;

		if (globalMultiply.alpha < 1.0f)
		{
			// Slightly more optimised to loop through without the additions 
			while (destPixels < destColEnd)
			{
				uint32_t* destRowEnd = destPixels + endRow;

				while (destPixels < destRowEnd)
					TBlend::BlendSkip(srcPixels, destPixels, globalMultiply, destRowEnd);

				// Increase buffers by pre-calculated amounts
				destPixels += destInc;
				srcPixels += srcInc;
			}
		}
		else
		{
			// Slightly more optimised to loop through without the additions 
			while (destPixels < destColEnd)
			{
				uint32_t* destRowEnd = destPixels + endRow;

				while (destPixels < destRowEnd)
					TBlend::BlendFastSkip(srcPixels, destPixels, destRowEnd);

				// Increase buffers by pre-calculated amounts
				destPixels += destInc;
				srcPixels += srcInc;
			}
		}

		return;
	}

	//********************************************************************************************************************************
	// Function:	TransformPixels - draws the image data transforming each screen pixel into image space
	// Parameters:	srcPixelData = the pixel data you want to draw
	//				srcFrameOffset = the horizontal pixel offset for the required animation frame within the PixelData
	//				srcDrawWidth, srcDrawHeight = the width and height of the source image frame
	//				srcOrigin = the centre of rotation for the source image
	//				alphaMultiply = additional transparancy applied to the whole sprite
	// Notes:		Much slower than BlitPixels, alphaMultiply is a negligable overhead compared to the rotation
	//********************************************************************************************************************************
	template< typename TBlend > void TransformPixels(const PixelData& srcPixelData, int srcFrameOffset, int srcDrawWidth, int srcDrawHeight, const Point2f& srcOrigin, const Matrix2D& transform, BlendColour globalMultiply)
	{
		// We flip the y screen coordinate and rotate to be consistant with a right-handed Cartesian co-ordinate system 
		Matrix2D right;
		right.row[0] = transform.row[1];
		right.row[1] = -transform.row[0];
		right.row[2] = { transform.row[2].x, m_pRenderTarget->height - transform.row[2].y, 1.0f };

		static float inf = std::numeric_limits<float>::infinity();
		float tgt_minx{ inf }, tgt_miny{ inf }, tgt_maxx{ -inf }, tgt_maxy{ -inf };

		float x[2] = { -srcOrigin.x, srcDrawWidth - srcOrigin.x };
		float y[2] = { -srcOrigin.y, srcDrawHeight - srcOrigin.y };
		Point2f vertices[4] = { { x[0], y[0] }, { x[1], y[0] }, { x[1], y[1] }, { x[0], y[1] } };

		//calculate the extremes of the rotated corners.
		for (int i = 0; i < 4; i++)
		{
			vertices[i] = right.Transform(vertices[i]);
			tgt_minx = floor(tgt_minx < vertices[i].x ? tgt_minx : vertices[i].x);
			tgt_maxx = ceil(tgt_maxx > vertices[i].x ? tgt_maxx : vertices[i].x);
			tgt_miny = floor(tgt_miny < vertices[i].y ? tgt_miny : vertices[i].y);
			tgt_maxy = ceil(tgt_maxy > vertices[i].y ? tgt_maxy : vertices[i].y);
		}

		if (Determinant(right) == 0.0f) return;
		Matrix2D invTransform = right;
		invTransform.Inverse();

		int tgt_draw_width = static_cast<int>(tgt_maxx - tgt_minx);
		int tgt_draw_height = static_cast<int>(tgt_maxy - tgt_miny);
		int tgt_buffer_width = m_pRenderTarget->width;
		int tgt_buffer_height = m_pRenderTarget->height;

		if (tgt_miny < 0) { tgt_draw_height += (int)tgt_miny; tgt_miny = 0; }
		if (tgt_maxy > (float)tgt_buffer_height) { tgt_draw_height -= (int)tgt_maxy - tgt_buffer_height; tgt_maxy = (float)tgt_buffer_height; }
		if (tgt_minx < 0) { tgt_draw_width += (int)tgt_minx; tgt_minx = 0; }
		if (tgt_maxx > (float)tgt_buffer_width) { tgt_draw_width -= (int)tgt_maxx - tgt_buffer_width;  tgt_maxx = (float)tgt_buffer_width; }

		Point2f tgt_pixel_start{ tgt_minx, tgt_miny };
		Point2f src_pixel_start = invTransform.Transform(tgt_pixel_start) + srcOrigin;

		float src_posx = src_pixel_start.x;
		float src_posy = src_pixel_start.y;

		int tgt_posx = static_cast<int>(tgt_pixel_start.x);
		int tgt_posy = static_cast<int>(tgt_pixel_start.y);

		float src_xincx = invTransform.row[0].x;
		float src_xincy = invTransform.row[0].y;
		float src_yincx = invTransform.row[1].x;
		float src_yincy = invTransform.row[1].y;
		float src_xresetx = src_xincx * tgt_draw_width;
		float src_xresety = src_xincy * tgt_draw_width;

		int tgt_start_pixel_index = tgt_posx + (tgt_posy * tgt_buffer_width);
		uint32_t* tgt_pixel = (uint32_t*)m_pRenderTarget->pPixels + tgt_start_pixel_index;
		uint32_t* tgt_column_end = tgt_pixel + (tgt_draw_height * tgt_buffer_width);

		// Iterate through each pixel on the screen in turn
		while (tgt_pixel < tgt_column_end)
		{
			uint32_t* tgt_row_end = tgt_pixel + tgt_draw_width;

			while (tgt_pixel < tgt_row_end)
			{
				int roundX = static_cast<int>(src_posx + 0.5f);
				int roundY = static_cast<int>(src_posy + 0.5f);

				if (roundX >= 0 && roundY >= 0 && roundX < srcDrawWidth && roundY < srcDrawHeight)
				{
					int src_pixel_index = roundX + (roundY * srcPixelData.width);
					uint32_t* src = ((uint32_t*)srcPixelData.pPixels + src_pixel_index + srcFrameOffset);
					TBlend::Blend(src, tgt_pixel, globalMultiply);
				}

				tgt_pixel++;
				src_posx += src_xincx;
				src_posy += src_xincy;
			}

			tgt_pixel += tgt_buffer_width - tgt_draw_width;

			src_posx -= src_xresetx;
			src_posy -= src_xresety;

			src_posx += src_yincx;
			src_posy += src_yincy;
		}

	}

	template< typename TBlend > void DrawPixelPreMult(int posX, int posY, Pixel srcPixel)
	{
		if (srcPixel.a == 0x00 || posX < 0 || posX >= m_pRenderTarget->width || posY < 0 || posY >= m_pRenderTarget->height)
			return;

		// Pre-multiply alpha and invert
		srcPixel.r = (srcPixel.r * srcPixel.a) >> 8;
		srcPixel.g = (srcPixel.g * srcPixel.a) >> 8;
		srcPixel.b = (srcPixel.b * srcPixel.a) >> 8;
		srcPixel.a = 0xFF - srcPixel.a;

		uint32_t* pDest = &m_pRenderTarget->pPixels[(posY * m_pRenderTarget->width) + posX].bits;
		uint32_t* pSrc = &srcPixel.bits;

		TBlend::Blend(pSrc, pDest, { 1.0f, 1.0f, 1.0f, 1.0f });

		return;
	}

	template< typename TBlend > void DrawPixel(int posX, int posY, Pixel srcPixel)
	{
		if (srcPixel.a == 0x00 || posX < 0 || posX >= m_pRenderTarget->width || posY < 0 || posY >= m_pRenderTarget->height)
			return;

		uint32_t* pDest = &m_pRenderTarget->pPixels[(posY * m_pRenderTarget->width) + posX].bits;
		uint32_t* pSrc = &srcPixel.bits;

		TBlend::Blend(pSrc, pDest, { 1.0f, 1.0f, 1.0f, 1.0f });

		return;
	}

};





#endif // PLAY_PLAYRENDER_H
#ifndef PLAY_PLAYGRAPHICS_H
#define PLAY_PLAYGRAPHICS_H
//********************************************************************************************************************************
// File:		PlayGraphics.h
// Description:	Manages 2D graphics operations on a PixelData buffer 
// Platform:	Independent
// Notes:		Uses PNG format. The end of the filename indicates the number of frames e.g. "bat_4.png" or "tiles_10x10.png"
//********************************************************************************************************************************
namespace Play::Graphics
{
	enum BlendMode
	{
		BLEND_NORMAL = 0,
		BLEND_ADD,
		BLEND_MULTIPLY,
		BLEND_SUBTRACT
	};

	extern BlendMode blendMode;

	// Create/Destroy manager functions
	//********************************************************************************************************************************

	// Creates the PlayGraphics manager and generates sprites from all the PNGs in the directory indicated
	bool CreateManager( int bufferWidth, int bufferHeight, const char* path );
	// Destroys the PlayGraphics manager
	bool DestroyManager();

	// Basic drawing functions
	//********************************************************************************************************************************

	// Sets the colour of an individual pixel in the display buffer
	void DrawPixel( Point2f pos, Pixel pix );
	// Draws a line of pixels into the display buffer
	void DrawLine( Point2f startPos, Point2f endPos, Pixel pix );
	// Draws a rectangle into the display buffer
	void DrawRect( Point2f topLeft, Point2f bottomRight, Pixel pix, bool fill = false );
	// Draws a circle into the display buffer
	void DrawCircle( Point2f centrePos, int radius, Pixel pix );
	// Draws raw pixel data to the display buffer
	// > Pre-multiplies the alpha on the image data if this hasn't been done before
	void DrawPixelData( PixelData* pixelData, Point2f pos, float alpha = 1.0f );

	// Debug font functions
	//********************************************************************************************************************************

	// Draws a single character using the in-built debug font
	// > Returns the character width in pixels
	int DrawDebugCharacter( Point2f pos, char c, Pixel pix );
	// Draws text using the in-built debug font
	// > Returns the x position at the end of the text
	int DrawDebugString( Point2f pos, const std::string& s, Pixel pix, bool centred = true );

	// Sprite Loading functions
	//********************************************************************************************************************************

	// Loads a sprite sheet and creates a sprite from it (custom asset pipelines)
	// > All sprites are normally created by the PlayGraphics constructor
	int LoadSpriteSheet( const std::string& path, const std::string& filename );
	// Adds a sprite sheet dynamically from memory (custom asset pipelines)
	// > All sprites are normally created by the PlayGraphics constructor
	int AddSprite( const std::string& name, PixelData& pixelData, int hCount = 1, int vCount = 1 );
	// Updates a sprite sheet dynamically from memory (custom asset pipelines)
	// > Left to caller to release old PixelData
	int UpdateSprite( const std::string& name, PixelData& pixelData, int hCount = 1, int vCount = 1 );
	
	// Loads a background image which is assumed to be the same size as the display buffer
	// > Returns the index of the loaded background
	int LoadBackground( const char* fileAndPath );

	// Sprite Getters and Setters
	//********************************************************************************************************************************

	// Gets the sprite id of the first matching sprite whose filename contains the given text
	// > Returns -1 if not found
	int GetSpriteId( const char* spriteName );
	// Gets the root filename of a specific sprite
	const std::string& GetSpriteName( int spriteId );
	// Gets the size of the sprite with the given id
	Vector2f GetSpriteSize(int spriteId);
	// Gets the number of frames in the sprite with the given id
	int GetSpriteFrames( int spriteId );
	// Gets the origin of the sprite with the given id (offset from top left)
	Vector2f GetSpriteOrigin( int spriteId );
	// Sets the origin of the sprite with the given id (offset from top left)
	void SetSpriteOrigin( int spriteId, Vector2f newOrigin, bool relative = false );
	// Centres the origin of the sprite with the given id
	void CentreSpriteOrigin( int spriteId );
	// Centres the origins of all the sprites
	void CentreAllSpriteOrigins();
	// Sets the origin of all sprites found matching the given name (offset from top left)
	void SetSpriteOrigins( const char* rootName, Vector2f newOrigin, bool relative = false );
	// Gets the number of sprites which have been loaded and created by PlayGraphics
	int GetTotalLoadedSprites();
	// Gets a (read only) pointer to a sprite's canvas buffer data
	const PixelData* GetSpritePixelData( int spriteId ); 

	// Sprite Drawing functions
	//********************************************************************************************************************************

	// Draw the sprite with transparency (slower than without transparency)
	void DrawTransparent(int spriteId, Point2f pos, int frameIndex, BlendColour globalMultiply = { 1.0f, 1.0f, 1.0f, 1.0f } ); // This just to force people to consider when they use an explicit alpha multiply
	// Draw the sprite without rotation or transparency (fastest draw)
	inline void Draw( int spriteId, Point2f pos, int frameIndex ) { DrawTransparent( spriteId, pos, frameIndex ); }
	// Draw the sprite rotated with transparency (slowest draw)
	void DrawRotated( int spriteId, Point2f pos, int frameIndex, float angle, float scale = 1.0f, BlendColour globalMultiply = { 1.0f, 1.0f, 1.0f, 1.0f } );
	// Draw the sprite using a matrix transformation and transparency (slowest draw)
	void DrawTransformed( int spriteId, const Matrix2D& transform, int frameIndex, BlendColour globalMultiply = { 1.0f, 1.0f, 1.0f, 1.0f } );
	// Draws a previously loaded background image
	void DrawBackground( int backgroundIndex = 0 );
	// Multiplies the sprite image buffer by the colour values
	// > Applies to all subseqent drawing calls for this sprite, but can be reset by calling agin with rgb set to white
	void ColourSprite( int spriteId, int r, int g, int b );

	// Draws a string using a sprite-based font exported from PlayFontTool
	int DrawString( int fontId, Point2f pos, std::string text );
	// Draws a centred string using a sprite-based font exported from PlayFontTool
	int DrawStringCentred( int fontId, Point2f pos, std::string text );
	// Draws an individual text character using a sprite-based font 
	int DrawChar( int fontId, Point2f pos, char c );
	// Draws a rotated text character using a sprite-based font 
	int DrawCharRotated( int fontId, Point2f pos, float angle, float scale, char c );
	// Gets the width of an individual text character from a sprite-based font
	int GetFontCharWidth( int fontId, char c );

	// A pixel-based sprite collision test based on drawing
	bool SpriteCollide( int s1Id, Point2f s1Pos, int s1FrameIndex, float s1Angle, int s1PixelColl[4], int s2Id, Point2f s2pos, int s2FrameIndex, float s2Angle, int s2PixelColl[4] );

	// Internal sprite structure for storing individual sprite data
	struct Sprite
	{
		int id{ -1 }; // Fast way of finding the right sprite
		std::string name; // Slow way of finding the right sprite
		int width{ -1 }, height{ -1 }; // The width and height of a single image in the sprite
		//int canvasWidth{ -1 }, canvasHeight{ -1 }; // The width and height of the entire sprite canvas
		int hCount{ -1 }, vCount{ -1 }, totalCount{ -1 };  // The number of sprite images in the canvas horizontally and vertically
		int originX{ 0 }, originY{ 0 }; // The origin and centre of rotation for the sprite (whole pixels only)
		PixelData canvasBuffer; // The sprite image data
		PixelData preMultAlpha; // The sprite data pre-multiplied with its own alpha
		Sprite() = default;
	};

	// Miscellaneous functions
	//********************************************************************************************************************************

	// Gets a pointer to the drawing buffer's pixel data
	PixelData* GetDrawingBuffer(void);
	// Resets the timing bar data and sets the current timing bar segment to a specific colour
	void TimingBarBegin( Pixel pix );
	// Sets the current timing bar segment to a specific colour
	// > Returns the number of timing segments
	int SetTimingBarColour( Pixel pix );
	// Draws the timing bar for the previous frame at the given position and size
	void DrawTimingBar( Point2f pos, Point2f size );
	// Gets the duration (in milliseconds) of a specific timing segment
	float GetTimingSegmentDuration( int id );
	// Clears the display buffer using the given pixel colour
	inline void ClearBuffer( Pixel colour ) { Render::ClearRenderTarget( colour ); }
	// Sets the render target for drawing operations
	inline PixelData* SetRenderTarget(PixelData* renderTarget) { return Render::SetRenderTarget(renderTarget); }
	// Set the blend mode for all subsequent drawing operations that support different blend modes
	inline void SetBlendMode(BlendMode bMode) { blendMode = bMode; }
};
#endif // PLAY_PLAYGRAPHICS_H
#ifndef PLAY_PLAYAUDIO_H
#define PLAY_PLAYAUDIO_H
//********************************************************************************************************************************
// File:		PlayAudio.h
// Description:	Declarations for a simple audio manager 
// Platform:	Independant
//********************************************************************************************************************************
namespace Play::Audio
{
	// Initialises the audio manager, using the directory provided as its root for finding .MP3 files
	bool CreateManager( const char* path );
	// Destroys any memory associated with the audio manager
	bool DestroyManager();
	// Play a sound using part of all of its name
	void StartSound( const char* name, bool bLoop );
	//  Stop the currently playing sound using part of all of its name
	void StopSound( const char* name ); 
};
#endif // PLAY_PLAYAUDIO_H

#ifndef PLAY_PLAYINPUT_H
#define PLAY_PLAYINPUT_H
//********************************************************************************************************************************
// File:		PlayInput.h
// Description:	Manages keyboard and mouse input 
// Platform:	Windows
// Notes:		Obtains mouse data from PlayWindow via MouseData structure
//********************************************************************************************************************************
namespace Play::Input
{
	enum class MouseButton
	{
		BUTTON_LEFT	= 0,
		BUTTON_RIGHT
	};

	// Creates the Input Manager
	MouseData* CreateManager();
	// Destroys the Input Manager
	bool DestroyManager();
	// Returns the status of the supplied mouse button (0=left, 1=right)
	bool GetMouseDown( MouseButton button );
	// Get the screen position of the mouse cursor
	Point2f GetMousePos();
	// Returns true if the key has been pressed since it was last released
	// If you omit the frame number then only the first call in the same frame will ever return true
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyPressed( int vKey, int frame = -1 );
	// Returns true if the key is currently being held down
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyDown( int vKey );
};
#endif // PLAY_PLAYINPUT_H


#ifndef PLAY_PLAYMANAGER_H
#define PLAY_PLAYMANAGER_H
//********************************************************************************************************************************
// File:		PlayManager.h
// Description:	A manager for providing simplified access to the PlayBuffer framework with managed GameObjects
// Platform:	Independent
// Notes:		The GameObject management is "opt in" as many will want to create their own GameObject class
//********************************************************************************************************************************

#define TRANSFORM_SPACE( p )  (drawSpace == DrawingSpace::WORLD ? p - cameraPos : p)
#define TRANSFORM_MATRIX_SPACE( t ) (drawSpace == DrawingSpace::WORLD ? (MatrixTranslation( -cameraPos.x, -cameraPos.y ) * t) : t)
#define TRANSFORM_AXIS_ROT( r ) (axisRotation == AxisRotation::CLOCKWISE_ZERO_UP ? -r+(PLAY_PI/2) : r)
#define TRANSFORM_MATRIX_ROT( t ) (axisRotation == AxisRotation::CLOCKWISE_ZERO_UP ? (t * MatrixRotation( PLAY_PI/2 )) : t)
#define TRANSFORM_Y( pos ) (coordSys == CoordSys::XRIGHT_YDOWN ? Point2D( pos.x, Play::Window::GetHeight()-pos.y ) : pos)
#define TRANSFORM_MATRIX_Y( t ) (coordSys == CoordSys::XRIGHT_YDOWN ? (MatrixTranslation( 0, Play::Window::GetHeight()-(t.row[2].y*2) ) * t) : t)

namespace Play
{
	// Alignment for font drawing operations
	enum Align
	{
		LEFT = 0,
		RIGHT,
		CENTRE,
	};

	enum Direction
	{
		HORIZONTAL = 0,
		VERTICAL,
		ALL,
	};

	enum DrawingSpace
	{
		WORLD = 0,
		SCREEN,
	};

	enum AxisRotation
	{
		CLOCKWISE_ZERO_UP = 0,
		ANTICLOCKWISE_ZERO_RIGHT = 1
	};

	enum CoordSys
	{
		XRIGHT_YDOWN = 0,
		XRIGHT_YUP = 1
	};

	enum BlendMode
	{
		BLEND_NORMAL = 0,
		BLEND_ADD,
		BLEND_MULTIPLY,
		BLEND_SUBTRACT
	};

	// PlayManager uses colour values from 0-100 for red, green, blue and alpha
	struct Colour
	{
		Colour( float r, float g, float b ) : red( r ), green( g ), blue( b ) {}
		Colour( int r, int g, int b ) : red( static_cast<float>( r ) ), green( static_cast<float>( g ) ), blue( static_cast<float>( b ) ) {}
		float red, green, blue;
	};

	extern Colour cBlack, cRed, cGreen, cBlue, cMagenta, cCyan, cYellow, cOrange, cWhite, cGrey;
	extern int frameCount;
	extern Point2f cameraPos;
	extern DrawingSpace drawSpace;
	extern AxisRotation axisRotation;
	extern CoordSys coordSys;

	// Manager creation and deletion
	//**************************************************************************************************

	// Initialises the managers and creates a window of the required dimensions
	void CreateManager( int width, int height, int scale, AxisRotation aRot = AxisRotation::CLOCKWISE_ZERO_UP, CoordSys coSys = CoordSys::XRIGHT_YDOWN );
	// Shuts down the managers and closes the window
	void DestroyManager();

	// PlayWindow functions
	//**************************************************************************************************

	// Copies the contents of the drawing buffer to the window
	void PresentDrawingBuffer();
	// Gets the co-ordinates of the mouse cursor within the display buffer
	Point2D GetMousePos();
	// Gets the status of the left or right mouse buttons
	bool GetMouseButton( Align button );
	// Gets the width of the display buffer
	int GetBufferWidth();
	// Gets the height of the display buffer
	int GetBufferHeight();

	// PlayAudio functions
	//**************************************************************************************************

	// Plays an mp3 audio file from the "Data\Sounds" directory
	void PlayAudio( const char* mp3Filename );
	// Loops an mp3 audio file from the "Data\Sounds" directory
	void StartAudioLoop( const char* mp3Filename );
	// Stops a looping mp3 audio file started with Play::StartSoundLoop()
	void StopAudioLoop( const char* mp3Filename );

	// Camera functions
	//**************************************************************************************************

	// Move the camera to the position specified
	void SetCameraPosition( Point2f pos );
	// Changes the drawing space for all drawing functions ( WORLD = Normal, SCREEN = ignore camera )
	void SetDrawingSpace( DrawingSpace space );
	// Get the current camera position
	Point2f GetCameraPosition( void );
	// Get the current drawing space setting
	DrawingSpace GetDrawingSpace( void );

	// PlayGraphics functions
	//**************************************************************************************************

	// Clears the display buffer using the colour provided
	void ClearDrawingBuffer( Colour col );
	// Loads a PNG file as the background image for the window
	int LoadBackground( const char* pngFilename );
	// Draws the background image previously loaded with Play::LoadBackground() into the drawing buffer
	void DrawBackground( int background = 0 );
	// Draws text to the screen using the built-in debug font
	void DrawDebugText( Point2D pos, const char* text, Colour col = cWhite, bool centred = true );

	// Gets the sprite id of the first matching sprite whose filename contains the given text
	int GetSpriteId( const char* spriteName );
	// Gets the pixel height of a sprite
	int GetSpriteHeight( const char* spriteName );
	// Gets the pixel width of a sprite
	int GetSpriteWidth( const char* spriteName );
	// Gets the pixel height of a sprite
	int GetSpriteHeight( int spriteId );
	// Gets the pixel width of a sprite
	int GetSpriteWidth( int spriteId );
	// Gets the stem filename for the sprite (without path or extension)
	const char* GetSpriteName( int spriteId );
	// Gets the total number of frames in the sprite
	int GetSpriteFrames( int spriteId );
	// Blends the sprite with the given colour (works best on white sprites)
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void ColourSprite( const char* spriteName, Colour col );

	// Centres the origin of the first sprite found matching the given name
	void CentreSpriteOrigin( const char* spriteName );
	// Centres the origin of all sprites found matching the given name
	void CentreMatchingSpriteOrigins( const char* partName );
	// Centres the origins of all loaded sprites
	void CentreAllSpriteOrigins();
	// Moves the origin of the first sprite found matching the given name
	void MoveSpriteOrigin( const char* spriteName, int xOffset, int yOffset );
	// Moves the origin of all sprites found matching the given name
	void MoveMatchingSpriteOrigins( const char* partName, int xoffset, int yoffset );
	// Moves the origin of all loaded sprites
	void MoveAllSpriteOrigins( int xoffset, int yoffset );
	// Sets the origin of the first sprite found matching the given name
	void SetSpriteOrigin( const char* spriteName, int xOrigin, int yOrigin );
	// Sets the origin of the sprite with a specific ID
	void SetSpriteOrigin( int spriteId, int xOrigin, int yOrigin );
	// Gets the origin of the first sprite found matching the given name
	Point2D GetSpriteOrigin( const char* spriteName );
	// Gets the origin of the sprite with a specific ID
	Point2D GetSpriteOrigin( int spriteId );
	// Gets a (read only) pointer to a sprite's canvas buffer data
	const PixelData* GetSpritePixelData( int spriteId );

	// Set the blend mode for all subsequent drawing operations that support different blend modes
	void SetDrawingBlendMode(BlendMode blendMode);
	// Draws the first matching sprite whose filename contains the given text
	void DrawSprite( const char* spriteName, Point2D pos, int frameIndex );
	// Draws the sprite using its unique sprite ID
	void DrawSprite( int spriteID, Point2D pos, int frame );
	// Draws the sprite with transparency (slower than DrawSprite)
	void DrawSpriteTransparent( const char* spriteName, Point2D pos, int frame, float opacity, Colour colour = cWhite );
	// Draws the sprite with transparency (slower than DrawSprite)
	void DrawSpriteTransparent( int spriteID, Point2D pos, int frame, float opacity, Colour colour = cWhite );
	// Draws the sprite with rotation and transparency (slowest DrawSprite)
	void DrawSpriteRotated( const char* spriteName, Point2D pos, int frame, float angle, float scale = 1.0f, float opacity = 1.0f, Colour colour = cWhite );
	// Draws the sprite with rotation and transparency (slowest DrawSprite)
	void DrawSpriteRotated( int spriteID, Point2D pos, int frame, float angle, float scale, float opacity = 1.0f, Colour colour = cWhite );
	// Draws the sprite using a tranformation matrix. Final rendering approach depends on the contents of the matrix
	void DrawSpriteTransformed( int spriteID, const Matrix2D& transform, int frame, float opacity = 1.0f, Colour colour = cWhite );
	// Draws a single-pixel wide line between two points in the given colour
	void DrawLine( Point2D start, Point2D end, Colour col );
	// Draws a single-pixel wide circle in the given colour
	void DrawCircle( Point2D pos, int radius, Colour col );
	// Draws a rectangle in the given colour
	void DrawRect( Point2D topLeft, Point2D bottomRight, Colour col, bool fill = false );
	// Draws a line between two points using a sprite
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void DrawSpriteLine( Point2D startPos, Point2D endPos, const char* penSprite, Colour c = cWhite );
	// Draws a circle using a sprite
	// > Note that colouring affects subsequent DrawSprite calls using the same sprite!!
	void DrawSpriteCircle( Point2D pos, int radius, const char* penSprite, Colour c = cWhite );
	// Draws text using a sprite-based font exported from PlayFontTool
	void DrawFontText( const char* fontId, std::string text, Point2D pos, Align justify = Align::LEFT );
	// Draws a pixel 
	void DrawPixel( Point2D pos, Colour c );

	// Resets the timing bar data and sets the current timing bar segment to a specific colour
	void BeginTimingBar( Colour colour );
	// Sets the current timing bar segment to a specific colour
	// > Returns the number of timing segments
	int ColourTimingBar( Colour colour );
	// Draws the timing bar for the previous frame at the given position and size
	void DrawTimingBar( Point2f pos, Point2f size );

	// Miscellaneous functions
	//**************************************************************************************************

	// Returns true if the key has been pressed since it was last released
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyPressed( int vKey );
	// Returns true if the key is currently being held down
	// > https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	bool KeyDown( int vKey );
	// Returns a random number as if you rolled a die with this many sides
	int RandomRoll( int sides );
	// Returns a random number from min to max inclusive
	int RandomRollRange( int min, int max );
	// Converts radians to degrees
	constexpr float RadToDeg( float radians ) { return ( radians / PLAY_PI ) * 180.0f; }
	// Converts radians to degrees
	constexpr float DegToRad( float degrees ) { return ( degrees / 180.0f ) * PLAY_PI; }
}
#endif // PLAY_PLAYMANAGER_H
#ifndef PLAY_PLAYOBJECT_H
#define PLAY_PLAYOBJECT_H
//********************************************************************************************************************************
// PlayBuffer provides a managed Play::GameObject structure which can be extended below. Adding additional member variables to
// the struct will cause them to be added to ALL GameObjects regardless of their type, so you may want to consider creating your 
// own GameObject class heirarchy on the longer term.
// Note: Play:GameObject and its associated functionality is only included if you #define PLAY_USING_GAMEOBJECT_MANAGER 
//********************************************************************************************************************************
#ifdef PLAY_USING_GAMEOBJECT_MANAGER
namespace Play
{
	struct GameObject
	{
		GameObject(int type, Point2D pos, int collisionRadius, int spriteId);

		// Default member variables: don't change these!
		int type{ -1 };
		int oldType{ -1 };
		int spriteId{ -1 };
		Point2D pos{ 0.0f, 0.0f };
		Point2D oldPos{ 0.0f, 0.0f };
		Vector2D velocity{ 0.0f, 0.0f };
		Vector2D acceleration{ 0.0f, 0.0f };
		float rotation{ 0.0f };
		float rotSpeed{ 0.0f };
		float oldRot{ 0.0f };
		int frame{ 0 };
		float framePos{ 0.0f };
		float animSpeed{ 0.0f };
		int radius{ 0 };
		float scale{ 1 };
		int lastFrameUpdated{ -1 };

		// Add your own member variables here and every GameObject will have them
		// int something{ 0 };

		int GetId() { return m_id; }

	private:
		// The GameObject's id should never be changed manually so we make it private!
		int m_id{ -1 };

		// Preventing assignment and copying reduces the potential for bugs
		GameObject& operator=(const GameObject&) = delete;
		GameObject(const GameObject&) = delete;
	};

	// GameObject functions
	//**************************************************************************************************

	// Creates a new GameObject and adds it to the managed list.
	// > Returns the new object's unique id
	int CreateGameObject(int type, Point2D pos, int collisionRadius, const char* spriteName);
	// Retrieves a GameObject based on its id
	// > Returns an object with a type of -1 if no object can be found
	GameObject& GetGameObject(int id);
	// Retrieves the first GameObject matching the given type
	// > Returns an object with a type of -1 if no object can be found
	GameObject& GetGameObjectByType(int type);
	// Collects the IDs of all of the GameObjects with the matching type
	std::vector<int> CollectGameObjectIDsByType(int type);
	// Collects the IDs of all of the GameObjects
	std::vector<int> CollectAllGameObjectIDs();
	// Performs a typical update of the object's position and animation
	// > Cam only be called once per object per frame unless allowMultipleUpdatesPerFrame is set to true
	void UpdateGameObject(GameObject& object, bool bWrap = false, int wrapBorderSize = 0, bool allowMultipleUpdatesPerFrame = false);
	// Deletes the GameObject with the corresponding id
	//> Use GameObject.GetId() to find out its unique id
	void DestroyGameObject(int id);
	// Deletes all GameObjects with the corresponding type
	void DestroyGameObjectsByType(int type);
	// Deletes all GameObjects
	void DestroyAllGameObjects();

	// Checks whether the two objects are within each other's collision radii
	bool IsColliding(GameObject& obj1, GameObject& obj2);
	// Checks whether any part of the object is visible within the DisplayBuffer
	bool IsVisible(GameObject& obj);
	// Checks whether the object is overlapping the edge of the screen and moving outwards 
	bool IsLeavingDisplayArea(GameObject& obj, Direction dirn = Direction::ALL);
	// Checks whether the animation has completed playing
	bool IsAnimationComplete(GameObject& obj);

	// Sets the velocity of the object based on a target rotation angle
	void SetGameObjectDirection(GameObject& obj, int speed, float rotation);
	// Set the rotation of the object based on a target point
	void PointGameObject(GameObject& obj,int targetX, int targetY);

	// Changes the object's current spite and resets its animation frame to the start
	void SetSprite(GameObject& obj, const char* spriteName, float animSpeed);
	// Draws the object's sprite without rotation or transparency (fastest)
	void DrawObject(GameObject& obj);
	// Draws the object's sprite with transparency (slower than DrawObject)
	void DrawObjectTransparent(GameObject& obj, float opacity);
	// Draws the object's sprite with rotation and transparency (slower than DrawObject)
	void DrawObjectRotated(GameObject& obj, float opacity = 1.0f);
	//Draws debug info for the the game objects 
	void DrawGameObjectsDebug();
}
#endif
#endif // PLAY_PLAYOBJECT_H

#endif // PLAYPCH_H
//*******************************************************************
//*******************************************************************
#ifdef PLAY_IMPLEMENTATION
//*******************************************************************
//*******************************************************************
//********************************************************************************************************************************
//* File:			PlayMemory.cpp
//* Platform:		Independent
//* Description:	Implementation of a simple memory tracker to prevent leaks. Uses #define new which looks neat and tidy
//*                 (especially for new C++ programmers), but doesn't work for placement new, so you are likely to get compile 
//*                 errors if you start including it in your own header files.  
//*                 Avoids use of STL or anything else which allocates memory as this could create infinite loops!
//* Notes:          This is a simple approach to support your understanding of overriding the new operator.
//*                 See below for more advanced approaches:
//*                 1) The CRT Debug Heap Library (a more advanced version of this approach)
//*                 https://docs.microsoft.com/en-us/visualstudio/debugger/crt-debug-heap-details?view=vs-2019
//*                 2) Heap Profiling in the debugger 
//*                 https://docs.microsoft.com/en-us/visualstudio/profiling/memory-usage?view=vs-2019
//********************************************************************************************************************************


#ifdef _DEBUG

// Undefine 'new' in this compilation unit only.
#pragma push_macro("new")
#undef new

constexpr int MAX_ALLOCATIONS = 8192 * 4;
constexpr int MAX_FILENAME = 1024;

unsigned int g_allocId = 0;

// A structure to store data on each memory allocation
struct ALLOC
{
	void* address = 0;
	char file[MAX_FILENAME] = { 0 };
	int line = 0;
	size_t size = 0;
	int id = 0;

	ALLOC( void* a, const char* fn, int l, size_t s ) { address = a; line = l; size = s; id = g_allocId++; strcpy_s( file, fn ); };
	ALLOC( void ) {};
};

ALLOC g_allocations[MAX_ALLOCATIONS];
unsigned int g_allocCount = 0;


void CreateStaticObject( void );
void PrintAllocation( const char* tagText, ALLOC& a );

//********************************************************************************************************************************
// Overrides for new operator (x4)
//********************************************************************************************************************************

// The file and line are passed through using the macro defined in PlayMemory.h which redefines new. This will only happen if 
// PlayMemory.h has been parsed in advance of the use of new in the relevant code. This approach is problematic for classes 
// the safest approach. The two definitions of new without the file and line pick up any other memory allocations for completeness.
void* operator new( size_t size, const char* file, int line )
{
	PLAY_ASSERT( g_allocCount < MAX_ALLOCATIONS );
	CreateStaticObject();
	void* p = malloc( size );
	g_allocations[g_allocCount++] = ALLOC{ p, file, line, size };
	return p;
}

void* operator new[]( size_t size, const char* file, int line )
{
	PLAY_ASSERT( g_allocCount < MAX_ALLOCATIONS );
	CreateStaticObject();
	void* p = malloc( size );
	g_allocations[g_allocCount++] = ALLOC{ p, file, line, size };
	return p;
}

void* operator new( size_t size )
{
	PLAY_ASSERT( g_allocCount < MAX_ALLOCATIONS );
	CreateStaticObject();
	void* p = malloc( size );
	g_allocations[g_allocCount++] = ALLOC{ p, "Unknown", 0, size };
	return p;
}

void* operator new[]( size_t size )
{
	PLAY_ASSERT( g_allocCount < MAX_ALLOCATIONS );
	CreateStaticObject();
	void* p = malloc( size );
	g_allocations[g_allocCount++] = ALLOC{ p, "Unknown", 0, size };
	return p;
}

//********************************************************************************************************************************
// Overrides for delete operator (x4)
//********************************************************************************************************************************

// The definitions with file and line are only included for exception handling, where it looks for a form of delete that matches 
// the new that was used to allocate it.
void operator delete( void* p, const char* file, int line )
{
	UNREFERENCED_PARAMETER( line );
	UNREFERENCED_PARAMETER( file );
	operator delete( p );
}

int g_id = -1;

void operator delete( void* p )
{
	for( unsigned int a = 0; a < g_allocCount; a++ )
	{
		if( g_allocations[a].address == p )
		{
			if( g_allocations[a].id == g_id )
				g_allocations[a].id = g_id;

			g_allocations[a] = g_allocations[g_allocCount - 1];
			g_allocations[g_allocCount - 1].address = nullptr;
			g_allocCount--;
		}
	}
	free( p );
}

void operator delete[]( void* p, const char* file, int line )
{
	UNREFERENCED_PARAMETER( line );
	UNREFERENCED_PARAMETER( file );
	operator delete[]( p );
}

void operator delete[]( void* p )
{
	for( unsigned int a = 0; a < g_allocCount; a++ )
	{
		if( g_allocations[a].address == p )
		{
			if( g_allocations[a].id == g_id )
				g_allocations[a].id = g_id;

			g_allocations[a] = g_allocations[g_allocCount - 1];
			g_allocations[g_allocCount - 1].address = nullptr;
			g_allocCount--;
		}
	}
	free( p );
}

//********************************************************************************************************************************
// Printing allocations
//********************************************************************************************************************************

// A method for printing out all the memory allocation immediately before program exit (or as close as you can get)
// This is achieved by creating a class as a static object before the first memory allocation, which stays in scope until
// after everything else is destroyed. When it is cleaned up its destructor prints the allocations to show us any leaks!
class DestroyedLast
{
public:
	DestroyedLast()
	{
		PrintAllocations( "<STARTUP>" );
	}
	~DestroyedLast()
	{
		if( g_allocCount > 0 )
		{
			PrintAllocations( "<MEMORY LEAK>" );
		}
		else
		{
			DebugOutput( "**************************************************\n" );
			DebugOutput( "NO MEMORY LEAKS!\n" );
			DebugOutput( "**************************************************\n" );
		}

	}
};

void CreateStaticObject( void )
{
	static DestroyedLast last;
}

void PrintAllocation( const char* tagText, ALLOC& a )
{
	char buffer[MAX_FILENAME * 2] = { 0 };

	if( a.address != nullptr )
	{
		char* lastSlash = strrchr( a.file, '\\' );
		if( lastSlash )
		{
			strcpy_s( buffer, lastSlash + 1 );
			strcpy_s( a.file, buffer );
		}
		// Format in such a way that VS can double click to jump to the allocation.
		sprintf_s( buffer, "%s %s(%d): 0x%02X %d bytes [%d]\n", tagText, a.file, a.line, static_cast<int>( reinterpret_cast<long long>( a.address ) ), static_cast<int>( a.size ), a.id );
		DebugOutput( buffer );
	}
}

void PrintAllocations( const char* tagText )
{
	int bytes = 0;
	char buffer[MAX_FILENAME * 2] = { 0 };
	DebugOutput( "****************************************************\n" );
	DebugOutput( "MEMORY ALLOCATED\n" );
	DebugOutput( "****************************************************\n" );
	for( unsigned int n = 0; n < g_allocCount; n++ )
	{
		ALLOC& a = g_allocations[n];
		PrintAllocation( tagText, a );
		bytes += static_cast<int>(a.size);
	}
	sprintf_s( buffer, "%s Total = %d bytes\n", tagText, bytes );
	DebugOutput( buffer );
	DebugOutput( "**************************************************\n" );

}

#pragma pop_macro("new")

#endif

//********************************************************************************************************************************
// File:		PlayWindow.cpp
// Description:	Platform specific code to provide a window to draw into
// Platform:	Windows
// Notes:		Uses a 32-bit ARGB display buffer
//********************************************************************************************************************************

using namespace Play; // Don't ever do this in header files!

// Instruct Visual Studio to add these to the list of libraries to link
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "dwmapi.lib")

// External functions which must be implemented by the user 
extern void MainGameEntry( int argc, char* argv[] ); 
extern bool MainGameUpdate( float ); // Called every frame
extern int MainGameExit( void ); // Called on quit
	
ULONG_PTR g_pGDIToken = 0;

#define ASSERT_WINDOW PLAY_ASSERT_MSG( Play::Window::m_bCreated, "Window Manager not initialised. Call Window::CreateManager() before using the Play::Window library functions.")

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	// Initialize GDI+
	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR token;
	Gdiplus::Status gdiStatus = Gdiplus::GdiplusStartup(&token, &startupInput, NULL);
	PLAY_ASSERT(Gdiplus::Ok == gdiStatus);
	g_pGDIToken = token;

	MainGameEntry(__argc, __argv);

	return Play::Window::HandleWindows( hInstance, hPrevInstance, lpCmdLine, nShowCmd, L"PlayBuffer" );
}

namespace Play::Window
{
	// Private data
	int m_scale{ 0 };
	PixelData* m_pPlayBuffer{ nullptr };
	MouseData* m_pMouseData{ nullptr };
	HWND m_hWindow{ nullptr };
	bool m_bCreated = false;

	//********************************************************************************************************************************
	// Create / Destroy functions for the Window Manager
	//********************************************************************************************************************************

	bool CreateManager( PixelData* pDisplayBuffer, int nScale )
	{
		PLAY_ASSERT(pDisplayBuffer);
		PLAY_ASSERT(nScale > 0);
		m_pPlayBuffer = pDisplayBuffer;
		m_scale = nScale;
		m_bCreated = true;
		return true;
	}

	bool DestroyManager( void )
	{
		ASSERT_WINDOW;
		m_bCreated = false;
		return true;
	}

	//********************************************************************************************************************************
	// Windows functions
	//********************************************************************************************************************************

	int HandleWindows( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LPCWSTR windowName )
	{
		ASSERT_WINDOW;

		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Play::Window::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = windowName;
		wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

		RegisterClassExW(&wcex);

		int	w = m_pPlayBuffer->width * m_scale;
		int h = m_pPlayBuffer->height * m_scale;

		UINT dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		RECT rect = { 0, 0, w, h };
		AdjustWindowRect(&rect, dwStyle, FALSE);
		HWND hWnd = CreateWindowW(windowName, windowName, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

		if (!hWnd)
			return FALSE;

		m_hWindow = hWnd;

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		HACCEL hAccelTable = LoadAccelerators(hInstance, windowName);

		LARGE_INTEGER frequency;
		double elapsedTime = 0.0;
		static LARGE_INTEGER lastDrawTime;
		LARGE_INTEGER now;

		MSG msg{};
		bool quit = false;

		// Set up counters for timing the frame
		QueryPerformanceCounter(&lastDrawTime);
		QueryPerformanceFrequency(&frequency);

		// Standard windows message loop
		while (!quit)
		{
			// Hangle windows messages
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			do
			{
				QueryPerformanceCounter(&now);
				elapsedTime = (now.QuadPart - lastDrawTime.QuadPart) * 1000.0 / frequency.QuadPart;

			} while (elapsedTime < 1000.0f / FRAMES_PER_SECOND);

			// Call the main game update function (only while we have the input focus in release mode)
#ifndef _DEBUG
			if (GetFocus() == m_hWindow)
#endif
				quit = MainGameUpdate(static_cast<float>(elapsedTime) / 1000.0f);

			lastDrawTime = now;

			DwmFlush(); // Waits for DWM compositor to finish
		}

		// Call the main game cleanup function
		MainGameExit();

		PLAY_ASSERT(g_pGDIToken);
		Gdiplus::GdiplusShutdown(g_pGDIToken);

		return static_cast<int>(msg.wParam);
	}

	LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		ASSERT_WINDOW;

		switch (message)
		{
		case WM_PAINT:
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
			if (m_pMouseData)
				m_pMouseData->left = true;
			break;
		case WM_LBUTTONUP:
			if (m_pMouseData)
				m_pMouseData->left = false;
			break;
		case WM_RBUTTONDOWN:
			if (m_pMouseData)
				m_pMouseData->right = true;
			break;
		case WM_RBUTTONUP:
			if (m_pMouseData)
				m_pMouseData->right = false;
			break;
		case WM_MOUSEMOVE:
			if (m_pMouseData)
			{
				m_pMouseData->pos.x = static_cast<float>(GET_X_LPARAM(lParam) / m_scale);
				m_pMouseData->pos.y = m_pPlayBuffer->height - static_cast<float>(GET_Y_LPARAM(lParam) / m_scale);
			}
			break;
		case WM_MOUSELEAVE:
			m_pMouseData->pos.x = -1;
			m_pMouseData->pos.y = -1;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	double Present( void )
	{
		ASSERT_WINDOW;

		LARGE_INTEGER frequency;
		LARGE_INTEGER before;
		LARGE_INTEGER after;
		QueryPerformanceCounter(&before);
		QueryPerformanceFrequency(&frequency);

		// Set up a BitmapInfo structure to represent the pixel format of the display buffer
		BITMAPINFOHEADER bitmap_info_header
		{
				sizeof(BITMAPINFOHEADER),								// size of its own data,
				m_pPlayBuffer->width, m_pPlayBuffer->height,		// width and height
				1, 32, BI_RGB,				// planes must always be set to 1 (docs), 32-bit pixel data, uncompressed 
				0, 0, 0, 0, 0				// rest can be set to 0 as this is uncompressed and has no palette
		};

		BITMAPINFO bitmap_info{ bitmap_info_header, { 0,0,0,0 } };	// No palette data required for this bitmap

		HDC hDC = GetDC(m_hWindow);

		// Copy the display buffer to the window: GDI only implements up scaling using simple pixel duplication, but that's what we want
		// Note that GDI+ DrawImage would do the same thing, but it's much slower! 
		StretchDIBits(hDC, 0, 0, m_pPlayBuffer->width * m_scale, m_pPlayBuffer->height * m_scale, 0, m_pPlayBuffer->height + 1, m_pPlayBuffer->width, -m_pPlayBuffer->height, m_pPlayBuffer->pPixels, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
		ReleaseDC(m_hWindow, hDC);

		QueryPerformanceCounter(&after);

		double elapsedTime = (after.QuadPart - before.QuadPart) * 1000.0 / frequency.QuadPart;

		return elapsedTime;
	}

	void RegisterMouse( MouseData* pMouseData ) 
	{ 
		ASSERT_WINDOW;
		m_pMouseData = pMouseData; 
	}

	int GetWidth() 
	{ 
		ASSERT_WINDOW;
		return m_pPlayBuffer->width; 
	}

	int GetHeight() 
	{ 
		ASSERT_WINDOW;
		return m_pPlayBuffer->height;
	}

	int GetScale() 
	{ 
		ASSERT_WINDOW;
		return m_scale; 
	}

}

//********************************************************************************************************************************
// Loading functions
//********************************************************************************************************************************

int ReadPNGImage(std::string& fileAndPath, int& width, int& height)
{
	// Convert filename from single to wide string for GDI+ compatibility
	size_t newsize = strlen(fileAndPath.c_str()) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, fileAndPath.c_str(), _TRUNCATE);

	HBITMAP hBitmap = NULL;

	// Use GDI+ to load file into Bitmap structure
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(wcstring, false);
	int status = bitmap->GetLastStatus();

	if (status != Gdiplus::Ok)
		return -status;

	bitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &hBitmap);

	width = bitmap->GetWidth();
	height = bitmap->GetHeight();

	delete bitmap;
	delete[] wcstring;

	return 1;
}

int LoadPNGImage(std::string& fileAndPath, PixelData& destImage)
{
	// Convert filename from single to wide string for GDI+ compatibility
	size_t newsize = strlen(fileAndPath.c_str()) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, fileAndPath.c_str(), _TRUNCATE);

	HBITMAP hBitmap = NULL;

	// Use GDI+ to load file into Bitmap structure
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(wcstring, false);
	int status = bitmap->GetLastStatus();

	if (status != Gdiplus::Ok)
		return -status;

	bitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &hBitmap);

	// Create BitmapData structure to pull the data into
	Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;

	destImage.width = bitmap->GetWidth();
	destImage.height = bitmap->GetHeight();

	// Lock the bitmap in advance of reading its data
	Gdiplus::Rect rect(0, 0, destImage.width, destImage.height);
	bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData);

	// Get a pointer to the actual bit data
	Pixel* sourcePixels = static_cast<Pixel*>(bitmapData->Scan0);

	destImage.pPixels = new Pixel[destImage.width * destImage.height];
	memset(destImage.pPixels, 0, sizeof(Pixel) * destImage.width * destImage.height);

	Pixel* destPixels = destImage.pPixels;

	// Copy the data across
	for (int b = 0; b < destImage.width * destImage.height; b++)
		*destPixels++ = *sourcePixels++;

	//Unlock the bitmap
	bitmap->UnlockBits(bitmapData);

	delete bitmap;
	delete bitmapData;
	delete[] wcstring;

	return 1;
}

//********************************************************************************************************************************
// Miscellaneous functions
//********************************************************************************************************************************

void AssertFailMessage( const char* message, const char* file, long line )
{
	// file - the file in which the assertion failed ( __FILE__ )
	// line - the line of code where the assertion failed ( __LINE__ )
	std::filesystem::path p = file;
	std::string s = p.filename().string() + " : LINE " + std::to_string(line);
	s += "\n" + std::string(message);
	int wide_count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
	wchar_t* wide = new wchar_t[wide_count];
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wide, wide_count);
	MessageBox(NULL, wide, (LPCWSTR)L"Assertion Failure", MB_ICONWARNING);
	delete[] wide;
}

void DebugOutput( const char* s )
{
	OutputDebugStringA(s);
}

void DebugOutput( std::string s )
{
	OutputDebugStringA(s.c_str());
}

void TracePrintf( const char* file, int line, const char* fmt, ... )
{
	constexpr size_t kMaxBufferSize = 512u;
	char buffer[kMaxBufferSize];

	va_list args;
	va_start(args, fmt);
	// format should be double click-able in VS 
	int len = sprintf_s(buffer, kMaxBufferSize, "%s(%d): ", file, line);
	vsprintf_s(buffer + len, kMaxBufferSize - len, fmt, args);
	DebugOutput(buffer);
	va_end(args);
}

//********************************************************************************************************************************
// File:		PlayRender.cpp
// Description:	A software pixel renderer for drawing 2D primitives into a PixelData buffer
// Platform:	Independent
//********************************************************************************************************************************


#define ASSERT_RENDERTARGET	PLAY_ASSERT_MSG( Play::Render::m_pRenderTarget, "Render Target not initialised. Call Render::SetRenderTarget() before using the Play::Render library functions.")

namespace Play::Render
{
	// Internal (private) namespace variables
	PixelData* m_pRenderTarget{ nullptr };

	PixelData* SetRenderTarget( PixelData* pRenderTarget ) 
	{ 
		PixelData* old = m_pRenderTarget; 
		m_pRenderTarget = pRenderTarget; 
		return old; 
	}

	void DrawLine( int startX, int startY, int endX, int endY, Pixel pix ) 
	{
		ASSERT_RENDERTARGET;

		//Implementation of Bresenham's Line Drawing Algorithm
		int dx = abs(endX - startX);
		int sx = 1;
		if (endX < startX) { sx = -1; }

		int dy = -abs(endY - startY);
		int sy = 1;
		if (endY < startY) { sy = -1; }

		int err = dx + dy;

		if (dx == 0 && dy == 0) return;

		int x = startX;
		int y = startY;

		while (true)
		{
			Graphics::DrawPixel({ x, y }, pix); // Axis flipping is performed within

			if (x == endX && y == endY)
				break;

			int e2 = 2 * err;
			if (e2 >= dy)
			{
				err += dy;
				x += sx;
			}
			if (e2 <= dx)
			{
				err += dx;
				y += sy;
			}
		}
	}

	
	void ClearRenderTarget( Pixel colour ) 
	{
		ASSERT_RENDERTARGET;
		Pixel* pBuffEnd = m_pRenderTarget->pPixels + (m_pRenderTarget->width * m_pRenderTarget->height);
		for (Pixel* pBuff = m_pRenderTarget->pPixels; pBuff < pBuffEnd; *pBuff++ = colour.bits);
		m_pRenderTarget->preMultiplied = false;
	}

	void BlitBackground( PixelData& backgroundImage ) 
	{
		ASSERT_RENDERTARGET;
		PLAY_ASSERT_MSG(backgroundImage.height == m_pRenderTarget->height && backgroundImage.width == m_pRenderTarget->width, "Background size doesn't match render target!");
		// Takes about 1ms for 720p screen on i7-8550U
		memcpy(m_pRenderTarget->pPixels, backgroundImage.pPixels, sizeof(Pixel) * m_pRenderTarget->width * m_pRenderTarget->height);
	}
}
//********************************************************************************************************************************
// File:		PlayGraphics.cpp
// Description:	Manages 2D graphics operations on a PixelData buffer 
// Platform:	Independent
// Notes:		Uses PNG format. The end of the filename indicates the number of frames e.g. "bat_4.png" or "tiles_10x10.png"
//********************************************************************************************************************************


#define ASSERT_GRAPHICS PLAY_ASSERT_MSG( Play::Graphics::m_bCreated, "Graphics Manager not initialised. Call Graphics::CreateManager() before using the Play::Graphics library functions.")

namespace Play::Graphics
{
	// Internal (private) declarations
	// 
	// Count of the total number of sprites loaded
	int m_nTotalSprites{ 0 };
	// Flag to record whether the manager has been created
	bool m_bCreated = false;
	// Buffer pointers
	PixelData m_playBuffer;
	// A buffer for unpacking the debug font into 
	uint8_t* m_pDebugFontBuffer{ nullptr };

	// A vector of all the loaded sprites
	std::vector< Sprite > m_vSpriteData;
	// A vector of all the loaded backgrounds
	std::vector< PixelData > m_vBackgroundData;

	// Multiplies the sprite image by its own alpha transparency values to save repeating this calculation on every draw
	// > A colour multiplication can also be applied at this stage, which affects all subseqent drawing operations on the sprite
	void PreMultiplyAlpha( Pixel* source, Pixel* dest, int width, int height, int maxSkipWidth, float alphaMultiply, Pixel colourMultiply );
	// Allocates a buffer for the debug font and copies the font pixel data to it
	void DecompressDubugFont( void );
	// Returns the pixel width of a string using the debug font
	int GetDebugStringWidth( const std::string& s );
	// Draws the offset points from the origin in all octants
	void DrawCircleOctants( int posX, int posY, int offX, int offY, Pixel pix );
	// Ends the current timing segment and calculates the duration
	LARGE_INTEGER EndTimingSegment();

	struct TimingSegment
	{
		Pixel pix;
		long long begin{ 0 };
		long long end{ 0 };
		float millisecs{ 0 };
	};

	// Vectors of timing data segments
	std::vector<TimingSegment> m_vTimings;
	std::vector<TimingSegment> m_vPrevTimings;

	// The blend mode state
	BlendMode blendMode{ BLEND_NORMAL };

	bool CreateManager( int bufferWidth, int bufferHeight, const char* path )
	{
		PLAY_ASSERT_MSG( !m_bCreated, "Graphics Manager already initialised! Cannot call Graphics::CreateManager() more than once.");

		m_bCreated = true;

		// A working buffer for our display. Each pixel is stored as an unsigned 32-bit integer: alpha<<24 | red<<16 | green<<8 | blue
		m_playBuffer.width = bufferWidth;
		m_playBuffer.height = bufferHeight;
		m_playBuffer.pPixels = new Pixel[static_cast<size_t>( bufferWidth ) * bufferHeight];
		m_playBuffer.preMultiplied = false;
		PLAY_ASSERT( m_playBuffer.pPixels );

		memset( m_playBuffer.pPixels, 0, sizeof( uint32_t ) * bufferWidth * bufferHeight );

		// Make the display buffer the render target for the blitter
		Render::SetRenderTarget( &m_playBuffer );

		// Iterate through the directory
		PLAY_ASSERT_MSG( std::filesystem::exists( path ), "PlayBuffer: Drectory provided does not exist." );

		for( const auto& p : std::filesystem::directory_iterator( path ) )
		{
			// Switch everything to uppercase to avoid need to check case each time
			std::string filename = p.path().string();
			for( char& c : filename ) c = static_cast<char>( toupper( c ) );

			// Only attempt to load PNG files
			if( filename.find( ".PNG" ) != std::string::npos )
			{
				std::ifstream png_infile;
				png_infile.open( filename, std::ios::binary ); // Don't do this as part of the constructor or we lose 16 bytes!

				// If the PNG was opened okay
				if( png_infile )
				{
					int spriteId = LoadSpriteSheet( p.path().parent_path().string() + "\\", p.path().stem().string() );

					// Now we check for .inf file for each sprite and load origins
					int originX = 0, originY = static_cast<int>(GetSpriteSize( spriteId ).y);

					std::string info_filename = filename.replace( filename.find( ".PNG" ), 4, ".INF" );

					if( std::filesystem::exists( info_filename ) )
					{
						std::ifstream info_infile;
						info_infile.open( info_filename, std::ios::in );

						PLAY_ASSERT_MSG( info_infile.is_open(), std::string( "Unable to load existing .inf file: " + info_filename ).c_str() );
						if( info_infile.is_open() )
						{
							std::string type;
							info_infile >> type;
							info_infile >> originX;
							info_infile >> originY;
						}

						info_infile.close();
					}

					SetSpriteOrigin( spriteId, { originX, originY }, false );
				}

				png_infile.close();
			}
		}
		
		return true;
	}

	bool DestroyManager()
	{
		ASSERT_GRAPHICS;

		for( Sprite& s : m_vSpriteData )
		{
			if( s.canvasBuffer.pPixels )
				delete[] s.canvasBuffer.pPixels;

			if( s.preMultAlpha.pPixels )
				delete[] s.preMultAlpha.pPixels;
		}

		for( PixelData& pBgBuffer : m_vBackgroundData )
			delete[] pBgBuffer.pPixels;

		if( m_pDebugFontBuffer )
			delete[] m_pDebugFontBuffer;

		delete[] m_playBuffer.pPixels;

		m_bCreated = false;
		return true;
	}

	//********************************************************************************************************************************
	// Loading functions
	//********************************************************************************************************************************

	int LoadSpriteSheet( const std::string& path, const std::string& filename )
	{
		ASSERT_GRAPHICS;

		PixelData canvasBuffer;
		std::string spriteName = filename;
		int hCount = 1;
		int vCount = 1;

		// Switch everything to uppercase to avoid need to check case each time
		for( char& c : spriteName ) c = static_cast<char>( toupper( c ) );

		// Look for the final number in the filename to pull out the number of frames across the width
		size_t frameWidthEnd = spriteName.find_last_of( "0123456789" );
		size_t frameWidthStart = spriteName.find_last_not_of( "0123456789" );

		if( frameWidthEnd == spriteName.length() - 1 )
		{
			// Grab the number of frames
			std::string widthString = spriteName.substr( frameWidthStart + 1, frameWidthEnd - frameWidthStart );

			// Make sure the number is valid 
			size_t num = widthString.find_first_of( "0123456789" );
			PLAY_ASSERT_MSG( num == 0, std::string( "Incorrectly named sprite: " + filename ).c_str() );

			hCount = stoi( widthString );

			if( spriteName[frameWidthStart] == 'X' )
			{
				//Two dimensional sprite sheet so the width was actually the height: copy it over and work out the real width
				vCount = hCount;

				// Cut off the last number we just found plus an "x", then check for another number indicating a frame height (optional)
				std::string truncated = spriteName.substr( 0, frameWidthStart );
				frameWidthEnd = truncated.find_last_of( "0123456789" );
				frameWidthStart = truncated.find_last_not_of( "0123456789" );

				if( frameWidthEnd == truncated.length() - 1 && frameWidthStart != std::string::npos )
				{
					// Grab the number of images in the height
					widthString = truncated.substr( frameWidthStart + 1, frameWidthEnd - frameWidthStart );

					// Make sure the number is valid
					num = widthString.find_first_of( "0123456789" );
					PLAY_ASSERT_MSG( num == 0, std::string( "Incorrectly named sprite: " + filename ).c_str() );

					hCount = stoi( widthString );
				}
				else
				{
					PLAY_ASSERT_MSG( false, std::string( "Incorrectly named sprite: " + filename ).c_str() );
				}
			}
			else
			{
				vCount = 1;
			}
		}

		std::string fileAndPath( path + spriteName + ".PNG" );
		LoadPNGImage( fileAndPath, canvasBuffer ); // Allocates memory as we don't know the size
	
		return AddSprite( filename, canvasBuffer, hCount, vCount );
	}

	int AddSprite( const std::string& name, PixelData& pixelData, int hCount, int vCount )
	{
		ASSERT_GRAPHICS;

		// Switch everything to uppercase to avoid need to check case each time
		std::string spriteName = name;
		for( char& c : spriteName ) c = static_cast<char>( toupper( c ) );

		Sprite s;
		s.id = m_nTotalSprites++;
		s.name = spriteName;
		s.originX = s.originY = 0;
		s.hCount = hCount;
		s.vCount = vCount;
		s.canvasBuffer = pixelData; // copy including pointer to pixel data

		s.totalCount = s.hCount * s.vCount;
		s.width = s.canvasBuffer.width / s.hCount;
		s.height = s.canvasBuffer.height / s.vCount;

		// Create a separate buffer with the pre-multiplyied alpha
		s.preMultAlpha.pPixels = new Pixel[static_cast<size_t>( s.canvasBuffer.width ) * s.canvasBuffer.height];
		s.preMultAlpha.width = s.canvasBuffer.width;
		s.preMultAlpha.height = s.canvasBuffer.height;
		memset( s.preMultAlpha.pPixels, 0, sizeof( uint32_t ) * s.canvasBuffer.width * s.canvasBuffer.height );
		PreMultiplyAlpha( s.canvasBuffer.pPixels, s.preMultAlpha.pPixels, s.canvasBuffer.width, s.canvasBuffer.height, s.width, 1.0f, 0x00FFFFFF );
		s.canvasBuffer.preMultiplied = true;

		// Add the sprite to our vector
		m_vSpriteData.push_back( s );

		return s.id;
	}

	int UpdateSprite( const std::string& name, PixelData& pixelData, int hCount, int vCount )
	{
		ASSERT_GRAPHICS; 

		// Switch everything to uppercase to avoid need to check case each time
		std::string spriteName = name;
		for( char& c : spriteName ) c = static_cast<char>( toupper( c ) );

		for( Sprite& s : m_vSpriteData )
		{
			if( s.name.find( spriteName ) != std::string::npos )
			{
				// delete the old premultiplied buffer
				delete s.preMultAlpha.pPixels;

				s.hCount = hCount;
				s.vCount = vCount;
				s.canvasBuffer = pixelData; // copy including pointer to pixel data

				s.totalCount = s.hCount * s.vCount;
				s.width = s.canvasBuffer.width / s.hCount;
				s.height = s.canvasBuffer.height / s.vCount;

				// Create a new buffer with the pre-multiplyied alpha
				s.preMultAlpha.pPixels = new Pixel[static_cast<size_t>( s.canvasBuffer.width ) * s.canvasBuffer.height];
				s.preMultAlpha.width = s.canvasBuffer.width;
				s.preMultAlpha.height = s.canvasBuffer.height;
				memset( s.preMultAlpha.pPixels, 0, sizeof( uint32_t ) * s.canvasBuffer.width * s.canvasBuffer.height );
				PreMultiplyAlpha( s.canvasBuffer.pPixels, s.preMultAlpha.pPixels, s.canvasBuffer.width, s.canvasBuffer.height, s.width, 1.0f, 0x00FFFFFF );
				s.canvasBuffer.preMultiplied = true;

				return s.id;
			}
		}

		return -1;
	}


	int LoadBackground( const char* fileAndPath )
	{
		ASSERT_GRAPHICS;

		// The background image may not be the right size for the background so we make sure the buffer is 
		PixelData backgroundImage;
		Pixel* pSrc, * pDest;

		Pixel* correctSizeBuffer = new Pixel[static_cast<size_t>( m_playBuffer.width ) * m_playBuffer.height];
		PLAY_ASSERT( correctSizeBuffer );

		std::string pngFile( fileAndPath );
		PLAY_ASSERT_MSG( std::filesystem::exists( fileAndPath ), "The background png does not exist at the given location." );
		LoadPNGImage( pngFile, backgroundImage ); // Allocates memory in function as we don't know the size

		pSrc = backgroundImage.pPixels;
		pDest = correctSizeBuffer;

		//Copy the image to our background buffer clipping where necessary
		for( int h = 0; h < std::min( backgroundImage.height, m_playBuffer.height ); h++ )
		{
			for( int w = 0; w < std::min( backgroundImage.width, m_playBuffer.width ); w++ )
				*pDest++ = *pSrc++;

			// Skip pixels if we're clipping
			pDest += std::max( m_playBuffer.width - backgroundImage.width, 0 );
			pSrc += std::max( backgroundImage.width - m_playBuffer.width, 0 );
		}

		// Free up the loading buffer
		delete backgroundImage.pPixels;
		backgroundImage.pPixels = correctSizeBuffer;

		m_vBackgroundData.push_back( backgroundImage );

		return static_cast<int>( m_vBackgroundData.size() ) - 1;
	}


	//********************************************************************************************************************************
	// Sprite Getters and Setters
	//********************************************************************************************************************************
	int GetSpriteId( const char* name ) 
	{
		ASSERT_GRAPHICS;

		std::string tofind( name );
		for( char& c : tofind ) c = static_cast<char>( toupper( c ) );

		for( const Sprite& s : m_vSpriteData )
		{
			if( s.name.find( tofind ) != std::string::npos )
				return s.id;
		}
		PLAY_ASSERT_MSG( false, "The sprite name is invalid!" );
		return -1;
	}

	const std::string& GetSpriteName( int spriteId )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get name of invalid sprite id" );
		return m_vSpriteData[spriteId].name;
	}

	Vector2f GetSpriteSize( int spriteId )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get width of invalid sprite id" );
		return { m_vSpriteData[spriteId].width, m_vSpriteData[spriteId].height };
	}

	int GetSpriteFrames( int spriteId )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get frames of invalid sprite id" );
		return m_vSpriteData[spriteId].totalCount;
	}

	Vector2f GetSpriteOrigin( int spriteId ) 
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to get origin with invalid sprite id" );
		return { m_vSpriteData[spriteId].originX, m_vSpriteData[spriteId].originY };
	}

	void SetSpriteOrigin( int spriteId, Vector2f newOrigin, bool relative )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to set origin with invalid sprite id" );
		if( relative )
		{
			m_vSpriteData[spriteId].originX += static_cast<int>( newOrigin.x );
			m_vSpriteData[spriteId].originY += static_cast<int>( newOrigin.y );
		}
		else
		{
			m_vSpriteData[spriteId].originX = static_cast<int>( newOrigin.x );
			m_vSpriteData[spriteId].originY = static_cast<int>( newOrigin.y );
		}
	}

	void CentreSpriteOrigin( int spriteId )
	{
		ASSERT_GRAPHICS;
		SetSpriteOrigin( spriteId, GetSpriteSize( spriteId ) / 2, false );
	}

	void CentreAllSpriteOrigins( void )
	{
		ASSERT_GRAPHICS;
		for( Sprite& s : m_vSpriteData )
			CentreSpriteOrigin( s.id );
	}

	void SetSpriteOrigins( const char* rootName, Vector2f newOrigin, bool relative )
	{
		ASSERT_GRAPHICS;
		std::string tofind( rootName );
		for( char& c : tofind ) c = static_cast<char>( toupper( c ) );

		for( Sprite& s : m_vSpriteData )
		{
			if( s.name.find( tofind ) != std::string::npos )
			{
				if( relative )
				{
					s.originX += static_cast<int>( newOrigin.x );
					s.originY += static_cast<int>( newOrigin.y );
				}
				else
				{
					s.originX = static_cast<int>( newOrigin.x );
					s.originY = static_cast<int>( newOrigin.y );
				}
			}
		}
	}

	int GetTotalLoadedSprites() 
	{ 
		ASSERT_GRAPHICS;
		return m_nTotalSprites; 
	}
	
	const PixelData* GetSpritePixelData(int spriteId) 
	{ 
		ASSERT_GRAPHICS;
		return &m_vSpriteData[spriteId].canvasBuffer; 
	}

	//********************************************************************************************************************************
	// Drawing functions
	//********************************************************************************************************************************

	void DrawTransparent( int spriteId, Point2f pos, int frameIndex, BlendColour globalMultiply)
	{
		ASSERT_GRAPHICS;
		const Sprite& spr = m_vSpriteData[spriteId];
		int destx = static_cast<int>( pos.x + 0.5f ) - spr.originX;
		int desty = static_cast<int>( pos.y + 0.5f ) + (spr.height - spr.originY);
		frameIndex = frameIndex % spr.totalCount;
		int frameX = frameIndex % spr.hCount;
		int frameY = frameIndex / spr.hCount;
		int pixelX = frameX * spr.width;
		int pixelY = frameY * spr.height;
		int frameOffset = pixelX + ( spr.canvasBuffer.width * pixelY );

		switch (blendMode)
		{
			case BLEND_NORMAL:
				Render::BlitPixels<Render::AlphaBlendPolicy>(spr.preMultAlpha, frameOffset, destx, desty, spr.width, spr.height, globalMultiply);
				break;
			case BLEND_ADD:
				Render::BlitPixels<Render::AdditiveBlendPolicy>(spr.preMultAlpha, frameOffset, destx, desty, spr.width, spr.height, globalMultiply);
				break;
			case BLEND_MULTIPLY:
				Render::BlitPixels<Render::MultiplyBlendPolicy>(spr.canvasBuffer, frameOffset, destx, desty, spr.width, spr.height, globalMultiply);
				break;
			default:
				PLAY_ASSERT_MSG(false, "Unsupported blend mode in DrawTransparent")
					break;
		}

	};

	void DrawRotated( int spriteId, Point2f pos, int frameIndex, float angle, float scale, BlendColour globalMultiply )
	{
		ASSERT_GRAPHICS;
		Matrix2D trans =  MatrixScale( scale, scale ) * MatrixRotation( angle );
		trans.row[2] = { pos.x, pos.y, 1.0f };
		DrawTransformed( spriteId, trans, frameIndex, globalMultiply);
	}

	void DrawTransformed( int spriteId, const Matrix2D& trans, int frameIndex, BlendColour globalMultiply)
	{
		ASSERT_GRAPHICS;
		const Sprite& spr = m_vSpriteData[spriteId];
		frameIndex = frameIndex % spr.totalCount;
		int frameX = frameIndex % spr.hCount;
		int frameY = frameIndex / spr.hCount;
		int pixelX = frameX * spr.width;
		int pixelY = frameY * spr.height;
		int frameOffset = pixelX + ( spr.canvasBuffer.width * pixelY );

		Vector2f origin = { spr.originX, spr.height - spr.originY };

		switch (blendMode)
		{
		case BLEND_NORMAL:
			Render::TransformPixels<Render::AlphaBlendPolicy>(spr.preMultAlpha, frameOffset, spr.width, spr.height, origin, trans, globalMultiply);
			break;
		case BLEND_ADD:
			Render::TransformPixels<Render::AdditiveBlendPolicy>(spr.preMultAlpha, frameOffset, spr.width, spr.height, origin, trans, globalMultiply);
			break;
		case BLEND_MULTIPLY:
			Render::TransformPixels<Render::MultiplyBlendPolicy>(spr.preMultAlpha, frameOffset, spr.width, spr.height, origin, trans, globalMultiply);
			break;
		default:
			PLAY_ASSERT_MSG(false, "Unsupported blend mode in DrawTransparent")
				break;
		}

	}


	void DrawBackground( int backgroundId )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( m_playBuffer.pPixels, "Trying to draw background without initialising display!" );
		PLAY_ASSERT_MSG( m_vBackgroundData.size() > static_cast<size_t>(backgroundId), "Background image out of range!" );
		Render::BlitBackground( m_vBackgroundData[backgroundId] );
	}

	void ColourSprite( int spriteId, int r, int g, int b )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( spriteId >= 0 && spriteId < m_nTotalSprites, "Trying to colour invalid sprite id" );

		Sprite& s = m_vSpriteData[spriteId];
		uint32_t col = ( ( r & 0xFF ) << 16 ) | ( ( g & 0xFF ) << 8 ) | ( b & 0xFF );

		PreMultiplyAlpha( s.canvasBuffer.pPixels, s.preMultAlpha.pPixels, s.canvasBuffer.width, s.canvasBuffer.height, s.width, 1.0f, col );
		s.canvasBuffer.preMultiplied = true;
	}

	int DrawString( int fontId, Point2f pos, std::string text )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );

		int width = 0;

		for( char c : text )
		{
			Draw( fontId, { pos.x + width, pos.y }, c - 32 );
			width += GetFontCharWidth( fontId, c );
		}
		return width;
	}

	int DrawStringCentred( int fontId, Point2f pos, std::string text )
	{
		ASSERT_GRAPHICS;
		int totalWidth = 0;

		for( char c : text )
			totalWidth += GetFontCharWidth( fontId, c );

		pos.x -= totalWidth / 2;

		DrawString( fontId, pos, text );
		return totalWidth;
	}

	int DrawChar( int fontId, Point2f pos, char c )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
		Draw( fontId, { pos.x, pos.y }, c - 32 );
		return GetFontCharWidth( fontId, c );
	}

	int DrawCharRotated( int fontId, Point2f pos, float angle, float scale, char c )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
		DrawRotated( fontId, { pos.x, pos.y }, c - 32, angle, scale );
		return GetFontCharWidth( fontId, c );
	}

	int GetFontCharWidth( int fontId, char c )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( fontId >= 0 && fontId < m_nTotalSprites, "Trying to use invalid sprite id for font" );
		return (m_vSpriteData[fontId].canvasBuffer.pPixels + ( c - 32 ))->b; // character width hidden in pixel data
	}




	//********************************************************************************************************************************
	// Function:	SpriteCollide: function that checks by pixel if two sprites collide
	// Parameters:	s1Xpos, s1Ypos, s2Xpos, s2Ypos = the origin of rotation for both sprites.
	//				s1Id, s2Id = the ids of both sprites
	//				s1angle, s2angle = the angle of rotation for both sprites, clockwise. 0 = unrotated.
	//				s1Pixelcoll, s2Pixelcoll = the top left and bottom right co-ordinates defining the collision rectangle of both sprites
	//				
	// Returns: true if a single pixel or more overlap between the two sprites and false if not.
	// Notes:	rounding errors may cause it not to be pixel perfect.	
	//********************************************************************************************************************************
	bool SpriteCollide( int id_1, Point2f pos_1, int frame_1, float angle_1, int s1PixelColl[4], int id_2, Point2f pos_2, int frame_2, float angle_2, int s2PixelColl[4] )
	{
		ASSERT_GRAPHICS;
		//transform all co-ordinates of sprite2 into the frame of sprite 1.

		//To do this we'll set up three co-ordinate systems.
		//X,Y are screen, u,v are sprite 1 and a,b are sprite 2.
		//The input is position of centre of rotation in screen and position of centre of rotation in sprite1 and sprite2.

		//We define the origin of the sprite1 as the beginning of its buffer.
		//First I calculate the offset vector for sprite one in the screen.
		//in sprite offsetu = rotOffX, offsetv = rotOffY.
		//When I refer to origin of the sprite I mean the 0,0 pixel.


		//Next define corners of sprite
		const Sprite& s1 = m_vSpriteData[id_1];
		const Sprite& s2 = m_vSpriteData[id_2];

		//Convert collision box locations from relative to sprite origin to relative to sprite top left. Hence TL.
		int s1PixelCollTL[4]{ 0 };
		int s2PixelCollTL[4]{ 0 };

		for( int i{ 0 }; i < 2; i++ )
		{
			s1PixelCollTL[2 * i] = s1PixelColl[2 * i] + s1.originX;
			s1PixelCollTL[2 * i + 1] = s1PixelColl[2 * i + 1] + s1.originY;
			s2PixelCollTL[2 * i] = s2PixelColl[2 * i] + s2.originX;
			s2PixelCollTL[2 * i + 1] = s2PixelColl[2 * i + 1] + s2.originY;
		}

		//in screen
		float cosAngle1 = cos( angle_1 );
		float sinAngle1 = sin( angle_1 );
		float offsetSprite1X = cosAngle1 * s1.originX - sinAngle1 * s1.originY;
		float offsetSprite1Y = cosAngle1 * s1.originY + sinAngle1 * s1.originX;

		//Next I calculate the sprite origin in the screen.
		float originSprite1X = pos_1.x - offsetSprite1X;
		float originSprite1Y = pos_1.y - offsetSprite1Y;

		//Repeat for other sprite.
		float cosAngle2 = cos( angle_2 );
		float sinAngle2 = sin( angle_2 );
		float offsetSprite2X = cosAngle2 * s2.originX - sinAngle2 * s2.originY;
		float offsetSprite2Y = cosAngle2 * s2.originY + sinAngle2 * s2.originX;

		//Next I calculate the sprite origin in the screen.
		float originSprite2X = pos_2.x - offsetSprite2X;
		float originSprite2Y = pos_2.y - offsetSprite2Y;

		//calculate the difference between two sprite origins in screen
		float originDiffX = originSprite2X - originSprite1X;
		float originDiffY = originSprite2Y - originSprite1Y;

		//calculation of the difference between two sprite origins in frame of sprite 1.
		float originDiffu = originDiffX * cosAngle1 + originDiffY * sinAngle1;
		float originDiffv = originDiffY * cosAngle1 - originDiffX * sinAngle1;

		int s2Width = s2.width;
		int s2Height = s2.height;
		int s1Width = s1.width;

		float cosAngleDiff = cos( angle_2 - angle_1 );
		float sinAngleDiff = sin( angle_2 - angle_1 );
		//top left, top right, bottom right, bottom left.
		float s2Cu[4]
		{
			0,
			s2Width * cosAngleDiff,
			s2Width * cosAngleDiff - s2Height * sinAngleDiff,
			-s2Height * sinAngleDiff
		};

		float s2Cv[4]
		{
			0,
			s2Width * sinAngleDiff,
			s2Width * sinAngleDiff + s2Height * cosAngleDiff,
			s2Height * cosAngleDiff
		};


		float minCu{ std::numeric_limits<float>::infinity() };
		float minCv{ std::numeric_limits<float>::infinity() };
		float maxCu{ -std::numeric_limits<float>::infinity() };
		float maxCv{ -std::numeric_limits<float>::infinity() };

		//calculate the extremes of the rotated sprite2.
		for( int i = 0; i < 4; i++ )
		{
			minCu = std::min( s2Cu[i], minCu );
			minCv = std::min( s2Cv[i], minCv );
			maxCu = std::max( s2Cu[i], maxCu );
			maxCv = std::max( s2Cv[i], maxCv );
		}

		//calculate the maximum and minimum positions in the sprite1 frame of the sprite2 corners.
		float maxu = (originDiffu)+( maxCu );
		float maxv = (originDiffv)+( maxCv );
		float minu = (originDiffu)+( minCu );
		float minv = (originDiffv)+( minCv );

		if( minu > s1PixelCollTL[2] || minv > s1PixelCollTL[3] || maxu < s1PixelCollTL[0] || maxv < s1PixelCollTL[1] )
		{
			return false;
		}
		else
		{
			//wrap both frame indexes just in case.
			frame_1 = frame_1 % s1.totalCount;
			frame_2 = frame_2 % s2.totalCount;

			//clip so we loop through sprite 1.
			//Restrict the range we look in for pixel based collisions.
			minv = ( minv < s1PixelCollTL[1] ) ? static_cast<float>( s1PixelCollTL[1] ) : minv;
			maxv = ( maxv > s1PixelCollTL[3] ) ? static_cast<float>( s1PixelCollTL[3] ) : maxv;
			minu = ( minu < s1PixelCollTL[0] ) ? static_cast<float>( s1PixelCollTL[0] ) : minu;
			maxu = ( maxu > s1PixelCollTL[2] ) ? static_cast<float>( s1PixelCollTL[2] ) : maxu;

			//Set up the starting position in sprite 2 frame. We know the box corners in u, v relative to the sprite 2 origin but we need to get them in a,b.
			float minCa = ( minu - originDiffu ) * cosAngleDiff + ( minv - originDiffv ) * sinAngleDiff;
			float minCb = -( minu - originDiffu ) * sinAngleDiff + ( minv - originDiffv ) * cosAngleDiff;

			//rounding at this point
			int iminu = static_cast<int>( minu );
			int iminv = static_cast<int>( minv );
			int imaxu = static_cast<int>( maxu );
			int imaxv = static_cast<int>( maxv );

			float startinga = minCa;
			float startingb = minCb;

			float rowstarta = startinga;
			float rowstartb = startingb;

			//Set up starting and finishing pointers for both the sprite 1 buffer and sprite 2 buffer 
			//starting pointer for the sprite 1 buffer is the minu and minv.
			int sprite1Offset = s1Width * frame_1 + iminu + iminv * s1.canvasBuffer.width;
			Pixel* sprite1Src = s1.canvasBuffer.pPixels + sprite1Offset;

			//The base pointer for the sprite2 will just be start of the correct frame in the canvas buffer.
			int sprite2Offset = s2Width * frame_2;
			Pixel* sprite2Base = s2.canvasBuffer.pPixels + sprite2Offset;
			//Define the number which we need to add to get down a row in sprite1.
			int sprite1ChangeRow = s1.canvasBuffer.width - ( imaxu - iminu );

			//Start of double for loop.
			//Go through the overlapping region (warning may go out of the buffer of sprite 2.)
			for( int v{ iminv }; v < imaxv; v++ )
			{
				//store a and b to be the start of the row.
				float a = rowstarta;
				float b = rowstartb;

				for( int u{ iminu }; u < imaxu; u++ )
				{

					//Edit this part to add a collision box.
					//If we are in sprite 2 then extract the look at the pixels.
					if( a >= s2PixelCollTL[0] && b >= s2PixelCollTL[1] && a < s2PixelCollTL[2] && b < s2PixelCollTL[3] )
					{
						int sprite2Pixel = static_cast<int>( a ) + static_cast<int>( b ) * s2.canvasBuffer.width;
						Pixel sprite2Src = *( sprite2Base + sprite2Pixel );

						//If both pixels at that position are opaque then there is a collision. 
						if( sprite2Src.bits > 0x00FFFFFF && (*sprite1Src).bits > 0x00FFFFFF )
						{
							return true;
						}

					}
					//add change in for going along u. go along a row.
					a += cosAngleDiff;
					b += -sinAngleDiff;

					sprite1Src++;

				}
				//increment for row of sprite 1.
				sprite1Src += sprite1ChangeRow;

				//work out start of next row based on start of previous row. 
				rowstarta += sinAngleDiff;
				rowstartb += cosAngleDiff;
			}
		}
		return false;
	}




	//********************************************************************************************************************************
	// Function:	PreMultiplyAlpha - calculates the (src*srcAlpha) alpha blending calculation in advance as it doesn't change
	// Parameters:	s = the sprite to pre-calculate data for
	// Notes:		Also inverts the alpha ready for the (dest*(1-srcAlpha)) calculation and stores information in the new
	//				buffer which provides the number of fully-transparent pixels in a row (so they can be skipped)
	//********************************************************************************************************************************
	void PreMultiplyAlpha( Pixel* source, Pixel* dest, int width, int height, int maxSkipWidth, float alphaMultiply = 1.0f, Pixel colourMultiply = 0x00FFFFFF )
	{
		ASSERT_GRAPHICS;

		Pixel* pSourcePixels = source;
		Pixel* pDestPixels = dest;

		// Iterate through all the pixels in the entire canvas
		for (int bh = 0; bh < height; bh++)
		{
			for (int bw = 0; bw < width; bw++)
			{
				Pixel src = *pSourcePixels;

				// Separate the channels and calculate src*srcAlpha
				int srcAlpha = static_cast<int>((src.bits >> 24) * alphaMultiply);

				int destRed = (srcAlpha * ((src.bits >> 16) & 0xFF)) >> 8;
				int destGreen = (srcAlpha * ((src.bits >> 8) & 0xFF)) >> 8;
				int destBlue = (srcAlpha * (src.bits & 0xFF)) >> 8;

				destRed = (destRed * ((colourMultiply.bits >> 16) & 0xFF)) >> 8;
				destGreen = (destGreen * ((colourMultiply.bits >> 8) & 0xFF)) >> 8;
				destBlue = (destBlue * (colourMultiply.bits & 0xFF)) >> 8;

				srcAlpha = 0xFF - srcAlpha; // invert the alpha ready to multiply with the destination pixels
				*pDestPixels = (srcAlpha << 24) | (destRed << 16) | (destGreen << 8) | destBlue;

				if (srcAlpha == 0xFF) // Completely transparent pixel
				{
					int repeats = 0;

					// We can only skip to the end of the row because the sprite frames are arranged on a continuous canvas
					int maxSkip = maxSkipWidth - (bw % maxSkipWidth);

					for (int zw = 1; zw < maxSkip; zw++)
					{
						if ((pSourcePixels + zw)->bits >> 24 == 0x00) // Another transparent pixel
							repeats++;
						else
							break;
					}

					*pDestPixels = 0xFF000000 | repeats; // Doesn't matter what the colour was so we use it to store the skip value
				}

				pDestPixels++;
				pSourcePixels++;
			}
		}
	}

	//********************************************************************************************************************************
	// Basic drawing functions
	//********************************************************************************************************************************



	void DrawPixel( Point2f pos, Pixel srcPix )
	{
		ASSERT_GRAPHICS;

		pos.y = Window::GetHeight() - pos.y; //// Flip the y-coordinate to be consistant with a Cartesian co-ordinate system

		// Convert floating point co-ordinates to pixels
		switch (blendMode)
		{
		case BLEND_NORMAL:
			// Convert floating point co-ordinates to pixels
			Render::DrawPixelPreMult<Render::AlphaBlendPolicy>(static_cast<int>(pos.x + 0.5f), static_cast<int>(pos.y + 0.5f), srcPix);
			break;
		case BLEND_ADD:
			// Convert floating point co-ordinates to pixels
			Render::DrawPixelPreMult<Render::AdditiveBlendPolicy>(static_cast<int>(pos.x + 0.5f), static_cast<int>(pos.y + 0.5f), srcPix);
			break;
		case BLEND_MULTIPLY:
			// Convert floating point co-ordinates to pixels
			Render::DrawPixel<Render::MultiplyBlendPolicy>(static_cast<int>(pos.x + 0.5f), static_cast<int>(pos.y + 0.5f), srcPix);
			break;
		default:
			PLAY_ASSERT_MSG(false, "Unsupported blend mode in PlayGraphics::DrawPixel")
				break;
		}
	}

	void DrawLine( Point2f startPos, Point2f endPos, Pixel pix )
	{
		ASSERT_GRAPHICS;
		// Convert floating point co-ordinates to pixels
		int x1 = static_cast<int>( startPos.x + 0.5f );
		int y1 = static_cast<int>( startPos.y + 0.5f );
		int x2 = static_cast<int>( endPos.x + 0.5f );
		int y2 = static_cast<int>( endPos.y + 0.5f );

		Render::DrawLine( x1, y1, x2, y2, pix );
	}




	void DrawRect( Point2f topLeft, Point2f bottomRight, Pixel pix, bool fill )
	{
		ASSERT_GRAPHICS;
		// Convert floating point co-ordinates to pixels
		int x1 = static_cast<int>( topLeft.x + 0.5f );
		int x2 = static_cast<int>( bottomRight.x + 0.5f );
		int y1 = static_cast<int>( topLeft.y + 0.5f );
		int y2 = static_cast<int>( bottomRight.y + 0.5f );

		if( fill )
		{
			for( int x = x1; x < x2; x++ )
			{
				for( int y = y1; y < y2; y++ )
					DrawPixel({ x, y }, pix);
			}
		}
		else
		{
			Render::DrawLine( x1, y1, x2, y1, pix );
			Render::DrawLine( x2, y1, x2, y2, pix );
			Render::DrawLine( x2, y2, x1, y2, pix );
			Render::DrawLine( x1, y2, x1, y1, pix );
		}
	}

	// Private function called by DrawCircle
	void DrawCircleOctants( int posX, int posY, int offX, int offY, Pixel pix )
	{
		ASSERT_GRAPHICS;
		DrawPixel( { posX + offX , posY + offY }, pix );
		DrawPixel( { posX - offX , posY + offY }, pix );
		DrawPixel( { posX + offX , posY - offY }, pix );
		DrawPixel( { posX - offX , posY - offY }, pix );
		DrawPixel( { posX - offY , posY + offX }, pix );
		DrawPixel( { posX + offY , posY - offX }, pix );
		DrawPixel( { posX - offY , posY - offX }, pix );
		DrawPixel( { posX + offY , posY + offX }, pix );
	}

	void DrawCircle( Point2f pos, int radius, Pixel pix )
	{
		ASSERT_GRAPHICS;
		// Convert floating point co-ordinates to pixels
		int x = static_cast<int>( pos.x + 0.5f );
		int y = static_cast<int>( pos.y + 0.5f );

		int dx = 0;
		int dy = radius;

		int d = 3 - 2 * radius;
		DrawCircleOctants( x, y, dx, dy, pix );

		while( dy >= dx )
		{
			dx++;
			if( d > 0 )
			{
				dy--;
				d = static_cast<int>( d + 4 * ( dx - dy ) + 10 );
			}
			else
			{
				d = static_cast<int>( d + 4 * dx + 6 );
			}
			DrawCircleOctants( x, y, dx, dy, pix );
		}
	};

	void DrawPixelData( PixelData* pixelData, Point2f pos, float alpha )
	{
		ASSERT_GRAPHICS;
		if( !pixelData->preMultiplied )
		{
			PreMultiplyAlpha( pixelData->pPixels, pixelData->pPixels, pixelData->width, pixelData->height, pixelData->width );
			pixelData->preMultiplied = true;
		}
		Render::BlitPixels<Render::AlphaBlendPolicy>(*pixelData, 0, static_cast<int>(pos.x), static_cast<int>(pos.y), pixelData->width, pixelData->height, { alpha, 1.0f, 1.0f, 1.0f });
	}


	//********************************************************************************************************************************
	// Debug font functions
	//********************************************************************************************************************************

	// Settings for the embedded debug font
	#define FONT_IMAGE_WIDTH	96
	#define FONT_IMAGE_HEIGHT	36
	#define FONT_CHAR_WIDTH		6
	#define FONT_CHAR_HEIGHT	12

	// A 96x36 font image @ 1bpp containing basic ASCII characters from 0x30 (0) to 0x5F (underscore) at 6x12 pixels each
	static const uint32_t debugFontData[] =
	{
		0x87304178, 0x0800861F, 0xFFFFFFE1, 0x7BBFBE79, 0xF7FE79EF, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EC, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EC, 0xFFFFFFFE, 0x7BBFBE79, 0xF7FE79EF, 0xFFEE3DFE, 0x6BB86080,	0x1078860F, 0xE3DFFEFE, 
		0x5BB7FEFB, 0xE7BE7BEF, 0xFFBFFF41, 0x7BB7FEFB, 0xE7BE7BEC, 0xFFDFFEDF, 0x7BB7FEFB, 0xE7BE7BEC, 0xFFEE3DDF, 0x7BB7FEFB, 0xE7BE7BEF, 0xFFFFFFFF, 0x7BB7BEF9, 0xE7BE7BEF,	0xFFFFFFDF, 0x87B001F8, 0x187E87EF, 0xFFFFFFDF, 
		0x86106104, 0x00007A30, 0x1E7C5061, 0x79E79E79, 0xF7DF7B7F, 0x5E7DA79E, 0x79E79F79, 0xF7DF7B7F, 0x5E7DA79E, 0x79E79F79, 0xF7DF7B7F, 0x5E7DA79E,	0x59E79F79, 0xF7DF7B7F, 0x597DA79E, 0x58005F78, 0x30D0037F, 0x477DA79E, 
		0x59E79F79, 0xF7DE7B7F, 0x597DA79E, 0x59E79F79, 0xF7DE7B7F, 0x5E7DA79E, 0x41E79F79, 0xF7DE7B7F, 0x5E7DA79E, 0x7DE79F79,	0xF7DE7B7F, 0x5E7DA79E, 0x7DE79E79, 0xF7DE7B7F, 0x5E7DA79E, 0x81E06104, 0x07C17A38, 0xDE01A7A1, 
		0x06106101, 0xE79E79E0, 0x337F3FFF, 0x79E79EED, 0xE79E79EF, 0xB77FBFFF, 0x79E79FED, 0xE79E79EF,	0xB7BFBFFF, 0x79E79FED, 0xE79A79EF, 0xB7BFBFFF, 0x79E75FED, 0xE79AB5EF, 0x77DFBFFF, 0x05E0E1ED, 0xE79ACC0E, 0xF7DFBFFF, 
		0x7DE77EED, 0xE79AB7ED, 0xF7EFBFFF, 0x7DE7BEED, 0xE79A7BEB, 0xF7EFBFFF,	0x7DE7BEED, 0xE79A7BE7, 0xF7F7BFFF, 0x7DA7BEED, 0xE79A7BE7, 0xF7F7BCFF, 0x7DD79EED, 0xEB5A7BE7, 0xF7FBBCFF, 0x7C27A1EE, 0x1CE57810, 0x33FB3EC0
	};

	void DecompressDubugFont( void )
	{
		ASSERT_GRAPHICS;

		m_pDebugFontBuffer = new uint8_t[FONT_IMAGE_WIDTH * FONT_IMAGE_HEIGHT];

		for( int y = 0; y < FONT_IMAGE_HEIGHT; y++ )
		{
			for( int x = 0; x < FONT_IMAGE_WIDTH; x++ )
			{
				int bufferIndex = ( y * FONT_IMAGE_WIDTH ) + x;
				int dataIndex = bufferIndex / 32;
				int dataShift = 31 - ( bufferIndex % 32 );

				// Convert 1bpp to an 8-bit array for easy data access
				if( ( debugFontData[dataIndex] >> dataShift ) & 0x01 )
					m_pDebugFontBuffer[( y * FONT_IMAGE_WIDTH ) + x] = 0; // not ARGB just 0 (no pixel)
				else
					m_pDebugFontBuffer[( y * FONT_IMAGE_WIDTH ) + x] = 1; // not ARGB just 1 (a pixel)
			}
		}
	}

	int DrawDebugCharacter( Point2f pos, char c, Pixel pix )
	{
		ASSERT_GRAPHICS;
		// Limited character set in the font (0x30-0x5F) so includes translation of useful chars outside that range
		switch( c )
		{
			case 0x2C: c = 0x5E; break; // Map full stop to comma (nearly the same!)
			case 0x2D: c = 0x3B; break; // Map minus to semi-colon (rarely used)
			case 0x28: c = 0x5B; break; // Map brackets to square brackets
			case 0x29: c = 0x5D; break; // Map brackets to square brackets
			case 0x2E: c = 0x5E; break; // Map full stop to carot (never used)
		}

		if( c < 0x30 || c > 0x5F )
			return FONT_CHAR_WIDTH;

		int sourceX = ( ( c - 0x30 ) % 16 ) * FONT_CHAR_WIDTH;
		int sourceY = ( ( c - 0x30 ) / 16 ) * FONT_CHAR_HEIGHT;

		// Loop over the bounding box of the glyph
		for( int x = 0; x < FONT_CHAR_WIDTH; x++ )
		{
			for( int y = 0; y < FONT_CHAR_HEIGHT; y++ )
			{
				if( m_pDebugFontBuffer[( ( sourceY + y ) * FONT_IMAGE_WIDTH ) + ( sourceX + x )] > 0 )
					DrawPixel( { pos.x + x, pos.y + (FONT_CHAR_HEIGHT - y - 1) }, pix ); 
			}
		}

		return FONT_CHAR_WIDTH;
	}

	int DrawDebugString( Point2f pos, const std::string& s, Pixel pix, bool centred )
	{
		ASSERT_GRAPHICS;

		if( m_pDebugFontBuffer == nullptr )
			DecompressDubugFont();

		if( centred )
			pos.x -= GetDebugStringWidth( s ) / 2;

		pos.y -= 6; // half the height of the debug font

		for( char c : s )
			pos.x += DrawDebugCharacter( pos, static_cast<char>( toupper( c ) ), pix ) + 1;

		// Return horizontal position at the end of the string so strings can be concatenated easily
		return static_cast<int>( pos.x );
	}

	int GetDebugStringWidth( const std::string& s )
	{
		ASSERT_GRAPHICS;
		return static_cast<int>( s.length() ) * ( FONT_CHAR_WIDTH + 1 );
	}

	//********************************************************************************************************************************
	// Miscellaneous functions
	//********************************************************************************************************************************

	PixelData* GetDrawingBuffer(void) 
	{ 
		ASSERT_GRAPHICS;
		return &m_playBuffer; 
	}

	LARGE_INTEGER EndTimingSegment()
	{
		ASSERT_GRAPHICS;

		int size = static_cast<int>( m_vTimings.size() );

		LARGE_INTEGER now, freq;
		QueryPerformanceCounter( &now );
		QueryPerformanceFrequency( &freq );

		if( size > 0 )
		{
			m_vTimings[size - 1].end = now.QuadPart;
			m_vTimings[size - 1].millisecs = static_cast<float>( m_vTimings[size - 1].end - m_vTimings[size - 1].begin );
			m_vTimings[size - 1].millisecs = static_cast<float>( ( m_vTimings[size - 1].millisecs * 1000.0f ) / freq.QuadPart );
		}

		return now;
	}

	int SetTimingBarColour( Pixel pix )
	{
		ASSERT_GRAPHICS;

		TimingSegment newData;
		newData.pix = pix;
		newData.begin = EndTimingSegment().QuadPart;

		m_vTimings.push_back( newData );

		return static_cast<int>( m_vTimings.size() );
	};

	void DrawTimingBar( Point2f pos, Point2f size )
	{
		ASSERT_GRAPHICS;

		EndTimingSegment();

		int startPixel{ 0 };
		int endPixel{ 0 };
		for( const TimingSegment& t : m_vPrevTimings )
		{
			endPixel += static_cast<int>( ( size.width * t.millisecs ) / 16.667f );
			DrawRect( { pos.x + startPixel, pos.y }, { pos.x + endPixel, pos.y + size.height }, t.pix, true );
			startPixel = endPixel;
		}

		DrawRect( { pos.x, pos.y }, { pos.x + size.width, pos.y + size.height }, PIX_BLACK, false );
		DrawRect( { pos.x - 1, pos.y - 1 }, { pos.x + size.width + 1 , pos.y + size.height + 1 }, PIX_WHITE, false );
	}

	float GetTimingSegmentDuration( int id )
	{
		ASSERT_GRAPHICS;
		PLAY_ASSERT_MSG( static_cast<size_t>(id) < m_vTimings.size(), "Invalid id for timing data." );
		return m_vTimings[id].millisecs;
	}

	void TimingBarBegin( Pixel pix )
	{
		ASSERT_GRAPHICS;
		EndTimingSegment();
		m_vPrevTimings = m_vTimings;
		m_vTimings.clear();
		SetTimingBarColour( pix );
	}

}
//********************************************************************************************************************************
// File:		PlaySpeaker.cpp
// Description:	Implementation of a very simple audio manager using the MCI
// Platform:	Windows
// Notes:		Uses MP3 format. The Windows multimedia library is extremely basic, but very quick easy to work with. 
//				Playback isn't always instantaneous and can trigger small frame glitches when StartSound is called. 
//				Consider XAudio2 as a potential next step.
//********************************************************************************************************************************


// Instruct Visual Studio to link the multimedia library  
#pragma comment(lib, "winmm.lib")

#define ASSERT_AUDIO PLAY_ASSERT_MSG( Play::Audio::m_bCreated, "Audio Manager not initialised. Call Audio::CreateManager() before using the Play::Audio library functions.")

namespace Play::Audio
{
	// Internal (private) namespace variables
	bool m_bCreated = false;
	std::vector< std::string > m_vSoundStrings;


	//********************************************************************************************************************************
	// Create and Destroy functions
	//********************************************************************************************************************************
	bool CreateManager( const char* path )
	{
		PLAY_ASSERT_MSG( !m_bCreated, "Audio manager has already been created!" );
		PLAY_ASSERT_MSG( std::filesystem::is_directory(path), "Audio directory does not exist!" );
		m_bCreated = true;

		// Iterate through the directory
		for (auto& p : std::filesystem::directory_iterator(path))
		{
			// Switch everything to uppercase to avoid need to check case each time
			std::string filename = p.path().string();
			for (char& c : filename) c = static_cast<char>(toupper(c));

			// Only load .mp3 files
			if (filename.find(".MP3") != std::string::npos)
			{
				m_vSoundStrings.push_back(filename);
				std::string command = "open \"" + filename + "\" type mpegvideo alias " + filename;
				mciSendStringA(command.c_str(), NULL, 0, 0);
			}
		}

		return true;
	}

	bool DestroyManager( void )
	{
		ASSERT_AUDIO;
		for (std::string& s : m_vSoundStrings)
		{
			std::string command = "close " + s;
			mciSendStringA(command.c_str(), NULL, 0, 0);
		}

		m_bCreated = false;
		return true;
	}

	//********************************************************************************************************************************
	// Sound playing functions
	//********************************************************************************************************************************
	void StartSound(const char* name, bool bLoop)
	{
		ASSERT_AUDIO;

		std::string filename(name);
		for (char& c : filename) c = static_cast<char>(toupper(c));

		// Iterate through the sound data 
		for (std::string& s : m_vSoundStrings)
		{
			if (s.find(filename) != std::string::npos)
			{
				std::string command = "play " + s + " from 0";
				if ( bLoop ) command += " repeat";
				mciSendStringA(command.c_str(), NULL, 0, 0);
				return;
			}
		}
		PLAY_ASSERT_MSG(false, std::string("Trying to play unknown sound effect: " + std::string(name)).c_str());
	}

	void StopSound( const char* name )
	{
		ASSERT_AUDIO;

		std::string filename( name );
		for (char& c : filename) c = static_cast<char>(toupper(c));

		// Iterate through the sound data 
		for (std::string& s : m_vSoundStrings)
		{
			if (s.find( filename ) != std::string::npos)
			{
				std::string command = "stop " + s;
				mciSendStringA(command.c_str(), NULL, 0, 0);
				return;
			}
		}
		PLAY_ASSERT_MSG(false, std::string( "Trying to stop unknown sound effect: " + std::string(name)).c_str() );
	}

}
//********************************************************************************************************************************
// File:		PlayInput.cpp
// Description:	Manages keyboard and mouse input 
// Platform:	Windows
// Notes:		Obtains mouse data from PlayWindow via MouseData structure
//********************************************************************************************************************************


#define ASSERT_INPUT PLAY_ASSERT_MSG( Play::Input::m_bCreated, "Input Manager not initialised. Call Input::CreateManager() before using the Play::Input library functions.")

namespace Play::Input
{
	// Flag to record whether the manager has been created
	bool m_bCreated = false;
	// The state of the mouse
	MouseData m_mouseData;

	//********************************************************************************************************************************
	// Create and Destroy functions
	//********************************************************************************************************************************
	MouseData* Play::Input::CreateManager(void)
	{
		PLAY_ASSERT_MSG(!m_bCreated, "Input manager has already been created!");
		m_bCreated = true;
		return &m_mouseData;
	}

	bool Play::Input::DestroyManager(void)
	{
		ASSERT_INPUT;
		m_bCreated = false;
		return true;
	}

	//********************************************************************************************************************************
	// Mouse functions
	//********************************************************************************************************************************

	bool GetMouseDown(MouseButton button)
	{
		ASSERT_INPUT;
		PLAY_ASSERT_MSG(button == MouseButton::BUTTON_LEFT || button == MouseButton::BUTTON_RIGHT, "Invalid mouse button selected.");

		if (button == MouseButton::BUTTON_LEFT)
			return m_mouseData.left;
		else
			return m_mouseData.right;
	};

	bool Play::Input::KeyPressed(int vKey, int frame)
	{
		ASSERT_INPUT;
		static std::map< int, int > keyMap;

		int& previous_frame = keyMap[vKey];

		// Returns true if key wasn't pressed the last time we checked or if this is the same frame as the last check
		if (KeyDown(vKey) && (previous_frame == 0 || (previous_frame == frame && frame != -1)))
		{
			previous_frame = frame;
			return true;
		}

		if (!KeyDown(vKey))
			previous_frame = 0;

		return false;
	}

	bool KeyDown(int vKey)
	{
		ASSERT_INPUT;
		return GetAsyncKeyState(vKey) & 0x8000; // Don't want multiple calls to KeyState
	}

	Point2f GetMousePos() 
	{ 
		ASSERT_INPUT;
		return m_mouseData.pos; 
	}
}
//********************************************************************************************************************************
// File:		PlayManager.cpp
// Description:	A manager for providing simplified access to the PlayBuffer framework
// Platform:	Independent
// Notes:		The GameObject management is "opt in" as many will want to create their own GameObject class
//********************************************************************************************************************************

namespace Play
{
	// A set of default colour definitions
	Colour cBlack{ 0.0f, 0.0f, 0.0f };
	Colour cRed{ 100.0f, 0.0f, 0.0f };
	Colour cGreen{ 0.0f, 100.0f, 0.0f };
	Colour cBlue{ 0.0f, 0.0f, 100.0f };
	Colour cMagenta{ 100.0f, 0.0f, 100.0f };
	Colour cCyan{ 0.0f, 100.0f, 100.0f };
	Colour cYellow{ 100.0f, 100.0f, 0.0f };
	Colour cOrange{ 100.0f, 50.0f, 0.0f };
	Colour cWhite{ 100.0f, 100.0f, 100.0f };
	Colour cGrey{ 50.0f, 50.0f, 50.0f };

	int frameCount = 0; // Updated in Play::Present

	// The camera
	Point2f cameraPos{ 0.0f, 0.0f };
	// Spaces and co-ordinate systems
	DrawingSpace drawSpace = DrawingSpace::WORLD;
	AxisRotation axisRotation = AxisRotation::CLOCKWISE_ZERO_UP;
	CoordSys coordSys = CoordSys::XRIGHT_YDOWN;

	//**************************************************************************************************
	// Manager creation and deletion
	//**************************************************************************************************

	void CreateManager( int displayWidth, int displayHeight, int displayScale, AxisRotation aRot, CoordSys coSys )
	{
		Play::Graphics::CreateManager( displayWidth, displayHeight, "Data\\Sprites\\" );
		Play::Window::CreateManager( Play::Graphics::GetDrawingBuffer(), displayScale );
		Play::Window::RegisterMouse( Play::Input::CreateManager() );
		Play::Audio::CreateManager( "Data\\Audio\\" );
		axisRotation = aRot;
		coordSys = coSys;
		// Seed the game's random number generator based on the time
		srand( (int)time( NULL ) );
	}

	void DestroyManager()
	{
		Play::Audio::DestroyManager();
		Play::Graphics::DestroyManager();
		Play::Window::DestroyManager();
		Play::Input::DestroyManager();
#ifdef PLAY_USING_GAMEOBJECT_MANAGER
		Play::DestroyAllGameObjects();
#endif

	}

	int GetBufferWidth()
	{
		return Play::Window::GetWidth();
	}

	int GetBufferHeight()
	{
		return Play::Window::GetHeight();
	}

	//**************************************************************************************************
	// PlayGraphics functions
	//**************************************************************************************************

	void ClearDrawingBuffer( Colour c )
	{
		int r = static_cast<int>( c.red * 2.55f );
		int g = static_cast<int>( c.green * 2.55f );
		int b = static_cast<int>( c.blue * 2.55f );
		Play::Graphics::ClearBuffer( { r, g, b } );
	}

	int LoadBackground( const char* pngFilename )
	{
		return Play::Graphics::LoadBackground( pngFilename );
	}

	void DrawBackground( int background )
	{
		Play::Graphics::DrawBackground( background );
	}

	void DrawDebugText( Point2D pos, const char* text, Colour c, bool centred )
	{
		Play::Graphics::DrawDebugString( TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), text, { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f }, centred );
	}

	void PresentDrawingBuffer()
	{
		static bool debugInfo = false;
		DrawingSpace originalDrawSpace = drawSpace;

		if( KeyPressed( VK_F1 ) )
			debugInfo = !debugInfo;

		if( debugInfo )
		{
			drawSpace = DrawingSpace::SCREEN;

			int textX = 10;
			int textY = 10;
			std::string s = "PlayBuffer Version:" + std::string( PLAY_VERSION );
			Play::Graphics::DrawDebugString( { textX - 1, textY - 1 }, s, PIX_BLACK, false );
			Play::Graphics::DrawDebugString( { textX + 1, textY + 1 }, s, PIX_BLACK, false );
			Play::Graphics::DrawDebugString( { textX + 1, textY - 1 }, s, PIX_BLACK, false );
			Play::Graphics::DrawDebugString( { textX - 1, textY + 1 }, s, PIX_BLACK, false );
			Play::Graphics::DrawDebugString( { textX, textY }, s, PIX_YELLOW, false );

			drawSpace = DrawingSpace::WORLD;

#ifdef PLAY_USING_GAMEOBJECT_MANAGER	
			DrawGameObjectsDebug();
#endif
		}

		Play::Window::Present();
		frameCount++;

		drawSpace = originalDrawSpace;
	}

	Point2D GetMousePos()
	{
		return TRANSFORM_Y( Play::Input::GetMousePos() );
	}

	bool GetMouseButton( Align button )
	{
		return Play::Input::GetMouseDown( static_cast<Play::Input::MouseButton>(button));
	}

	//**************************************************************************************************
	// PlaySpeaker functions
	//**************************************************************************************************

	void PlayAudio( const char* fileName )
	{
		Play::Audio::StartSound( fileName, false );
	}

	void StartAudioLoop( const char* fileName )
	{
		Play::Audio::StartSound( fileName, true );
	}

	void StopAudioLoop( const char* fileName )
	{
		Play::Audio::StopSound( fileName );
	}

	//**************************************************************************************************
	// Camera functions
	//**************************************************************************************************

	void SetCameraPosition( Point2f pos ) { cameraPos = TRANSFORM_Y( pos ); }

	Point2f GetCameraPosition( void ) { return TRANSFORM_Y( cameraPos ); }

	void SetDrawingSpace( DrawingSpace space ) { drawSpace = space;	}

	DrawingSpace GetDrawingSpace( void ) { return drawSpace; }

	//**************************************************************************************************
	// PlayGraphics functions
	//**************************************************************************************************

	int GetSpriteId( const char* spriteName )
	{
		return Play::Graphics::GetSpriteId( spriteName );
	}

	int GetSpriteHeight( const char* spriteName )
	{
		return static_cast<int>(Play::Graphics::GetSpriteSize( GetSpriteId( spriteName ) ).height);
	}

	int GetSpriteWidth( const char* spriteName )
	{
		return static_cast<int>(Play::Graphics::GetSpriteSize( GetSpriteId( spriteName ) ).width );
	}

	int GetSpriteHeight( int spriteId )
	{
		return static_cast<int>( Play::Graphics::GetSpriteSize( spriteId ).height );
	}

	int GetSpriteWidth( int spriteId )
	{
		return static_cast<int>(Play::Graphics::GetSpriteSize( spriteId ).width );
	}

	Point2D GetSpriteOrigin( const char* spriteName )
	{
		return Play::Graphics::GetSpriteOrigin( GetSpriteId( spriteName ) );
	}

	Point2D GetSpriteOrigin( int spriteId )
	{
		return Play::Graphics::GetSpriteOrigin( spriteId );
	}

	const char* GetSpriteName( int spriteId )
	{
		return Play::Graphics::GetSpriteName( spriteId ).c_str();
	}

	const PixelData* GetSpritePixelData( int spriteId )
	{
		return Play::Graphics::GetSpritePixelData( spriteId );
	}

	int GetSpriteFrames( int spriteId )
	{
		return static_cast<int>(Play::Graphics::GetSpriteFrames( spriteId ) );
	}

	void ColourSprite( const char* spriteName, Colour c )
	{
		int spriteId = Play::Graphics::GetSpriteId( spriteName );
		Play::Graphics::ColourSprite( spriteId, static_cast<int>( c.red * 2.55f ), static_cast<int>( c.green * 2.55f), static_cast<int>( c.blue * 2.55f ) );
	}

	void CentreSpriteOrigin( const char* spriteName )
	{
		int spriteId = Play::Graphics::GetSpriteId( spriteName );
		Play::Graphics::SetSpriteOrigin( spriteId, Play::Graphics::GetSpriteSize( spriteId ) / 2, false );
	}

	void CentreMatchingSpriteOrigins( const char* rootName )
	{
		int spriteId = Play::Graphics::GetSpriteId( rootName ); // Finds the first matching sprite and assumes same dimensions
		Play::Graphics::SetSpriteOrigins( rootName, Play::Graphics::GetSpriteSize( spriteId ) / 2, false );
	}

	void CentreAllSpriteOrigins()
	{
		for( int i = 0; i < Play::Graphics::GetTotalLoadedSprites(); i++ )
			Play::Graphics::SetSpriteOrigin( i, Play::Graphics::GetSpriteSize( i ) / 2, false );
	}

	void MoveSpriteOrigin( const char* spriteName, int xOffset, int yOffset )
	{
		int spriteId = Play::Graphics::GetSpriteId( spriteName );
		Play::Graphics::SetSpriteOrigin( spriteId, { xOffset, yOffset }, true ); // relative option set
	}

	void MoveMatchingSpriteOrigins( const char* rootName, int xoffset, int yoffset )
	{
		Play::Graphics::SetSpriteOrigins( rootName, { xoffset, yoffset }, true ); // relative option set
	}

	void MoveAllSpriteOrigins(int xoffset, int yoffset)
	{
		for (int i = 0; i < Play::Graphics::GetTotalLoadedSprites(); i++)
			Play::Graphics::SetSpriteOrigin(i, { xoffset, yoffset }, true ); // relative option set
	}

	void SetSpriteOrigin( int spriteId, int xOrigin, int yOrigin )
	{
		Play::Graphics::SetSpriteOrigin( spriteId, { xOrigin, yOrigin } );
	}

	void SetSpriteOrigin( const char* spriteName, int xOrigin, int yOrigin )
	{
		int spriteId = Play::Graphics::GetSpriteId( spriteName );
		Play::Graphics::SetSpriteOrigin( spriteId, { xOrigin, yOrigin } ); 
	}

	void SetDrawingBlendMode(BlendMode blendMode)
	{
		Graphics::SetBlendMode(static_cast<Graphics::BlendMode>(blendMode));
	}

	void DrawSprite( const char* spriteName, Point2D pos, int frameIndex )
	{
		Play::Graphics::Draw( Play::Graphics::GetSpriteId( spriteName ), TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), frameIndex );
	}

	void DrawSprite(int spriteID, Point2D pos, int frameIndex)
	{
		Play::Graphics::Draw( spriteID, TRANSFORM_SPACE(TRANSFORM_Y( pos ) ), frameIndex );
	}

	void DrawSpriteTransparent(const char* spriteName, Point2D pos, int frameIndex, float opacity, Colour colour)
	{
		Graphics::DrawTransparent(Graphics::GetSpriteId(spriteName), TRANSFORM_SPACE(pos), frameIndex, { opacity, colour.red / 100.0f, colour.green / 100.0f, colour.blue / 100.0f });
	}

	void DrawSpriteTransparent(int spriteID, Point2D pos, int frameIndex, float opacity, Colour colour)
	{
		Graphics::DrawTransparent(spriteID, TRANSFORM_SPACE(pos), frameIndex, { opacity, colour.red / 100.0f, colour.green / 100.0f, colour.blue / 100.0f } );
	}

	void DrawSpriteRotated( const char* spriteName, Point2D pos, int frameIndex, float angle, float scale, float opacity, Colour colour)
	{
		Play::Graphics::DrawRotated( Play::Graphics::GetSpriteId( spriteName ), TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), frameIndex, TRANSFORM_AXIS_ROT( angle ), scale, { opacity, colour.red / 100.0f, colour.green / 100.0f, colour.blue / 100.0f });
	}

	void DrawSpriteRotated( int spriteID, Point2D pos, int frameIndex, float angle, float scale, float opacity, Colour colour )
	{
		Play::Graphics::DrawRotated( spriteID, TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), frameIndex, TRANSFORM_AXIS_ROT( angle ), scale, { opacity, colour.red / 100.0f, colour.green / 100.0f, colour.blue / 100.0f });
	}

	void DrawSpriteTransformed( int spriteID, const Matrix2D& transform, int frameIndex, float opacity, Colour colour )
	{
		Play::Graphics::DrawTransformed( spriteID, TRANSFORM_MATRIX_SPACE( TRANSFORM_MATRIX_ROT(TRANSFORM_MATRIX_Y( transform ) ) ), frameIndex, { opacity, colour.red / 100.0f, colour.green / 100.0f, colour.blue / 100.0f });
	}

	void DrawLine( Point2f start, Point2f end, Colour c )
	{
		return Play::Graphics::DrawLine( TRANSFORM_SPACE( TRANSFORM_Y( start ) ), TRANSFORM_SPACE( TRANSFORM_Y( end ) ), { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f }  );
	}

	void DrawCircle( Point2D pos, int radius, Colour c )
	{
		Play::Graphics::DrawCircle( TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), radius, { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f } );
	}

	void DrawRect( Point2D topLeft, Point2D bottomRight, Colour c, bool fill )
	{
		Play::Graphics::DrawRect( TRANSFORM_SPACE( TRANSFORM_Y( topLeft ) ), TRANSFORM_SPACE( TRANSFORM_Y( bottomRight ) ), { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f }, fill );
	}

	void DrawSpriteLine( Point2f startPos, Point2f endPos, const char* penSprite, Colour c )
	{
		int spriteId = Play::Graphics::GetSpriteId( penSprite );
		ColourSprite( penSprite, c );

		//Draws a line in any angle
		int x1 = static_cast<int>( startPos.x );
		int y1 = static_cast<int>( startPos.y );
		int x2 = static_cast<int>( endPos.x );
		int y2 = static_cast<int>( endPos.y );

		//Implementation of Bresenham's Line Drawing Algorithm
		int dx = abs( x2 - x1 );
		int sx = 1;
		if( x2 < x1 ) { sx = -1; }

		int dy = -abs( y2 - y1 );
		int sy = 1;
		if( y2 < y1 ) { sy = -1; }
		
		int err = dx + dy;

		if( dx == 0 && dy == 0 ) return;

		while( true )
		{
			Play::DrawSprite( spriteId, { x1, y1 }, 0 );
			
			if( x1 == x2 && y1 == y2 )
				break;

			int e2 = 2 * err;
			if( e2 >= dy )
			{
				err += dy;
				x1 += sx;
			}
			if( e2 <= dx )
			{
				err += dx;
				y1 += sy;
			}
		}
	}

	// Not exposed externally
	void DrawCircleOctants( int spriteId, int x, int y, int ox, int oy )
	{
		//displaying all 8 coordinates of(x,y) residing in 8-octants
		Play::DrawSprite( spriteId, { x + ox, y + oy }, 0 );
		Play::DrawSprite( spriteId, { x - ox, y + oy }, 0 );
		Play::DrawSprite( spriteId, { x + ox, y - oy }, 0 );
		Play::DrawSprite( spriteId, { x - ox, y - oy }, 0 );
		Play::DrawSprite( spriteId, { x + oy, y + ox }, 0 );
		Play::DrawSprite( spriteId, { x - oy, y + ox }, 0 );
		Play::DrawSprite( spriteId, { x + oy, y - ox }, 0 );
		Play::DrawSprite( spriteId, { x - oy, y - ox }, 0 );
	}

	void DrawSpriteCircle( Point2D pos, int radius, const char* penSprite, Colour c )
	{
		int spriteId = Play::Graphics::GetSpriteId( penSprite );
		ColourSprite( penSprite, c );

		pos = TRANSFORM_SPACE( TRANSFORM_Y( pos ) );

		int ox = 0, oy = radius;
		int d = 3 - 2 * radius;
		DrawCircleOctants( spriteId, static_cast<int>(pos.x), static_cast<int>(pos.y), ox, oy );

		while( oy >= ox )
		{
			ox++;
			if( d > 0 )
			{
				oy--;
				d = d + 4 * ( ox - oy ) + 10;
			}
			else
			{
				d = d + 4 * ox + 6;
			}
			DrawCircleOctants( spriteId, static_cast<int>(pos.x), static_cast<int>(pos.y), ox, oy );
		}
	};

	void DrawFontText( const char* fontId, std::string text, Point2D pos, Align justify )
	{
		int font = Play::Graphics::GetSpriteId( fontId );

		int totalWidth{ 0 };

		for( char c : text )
			totalWidth += Play::Graphics::GetFontCharWidth( font, c );

		switch( justify )
		{
			case Align::CENTRE:
				pos.x -= totalWidth / 2;
				break;
			case Align::RIGHT:
				pos.x -= totalWidth;
				break;
			default:
				break;
		}

		pos.x += Play::Graphics::GetSpriteOrigin( font ).x;
		Play::Graphics::DrawString( font, TRANSFORM_SPACE( TRANSFORM_Y( pos ) ), text );
	}

	void DrawPixel(Point2D pos, Colour c)
	{
		return Play::Graphics::DrawPixel(TRANSFORM_SPACE(TRANSFORM_Y(pos)), { c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f });
	}

	void BeginTimingBar( Colour c )
	{
		Play::Graphics::TimingBarBegin( Pixel( c.red*2.55f, c.green*2.55f, c.blue*2.55f ) );
	}

	int ColourTimingBar( Colour c )
	{
		return Play::Graphics::SetTimingBarColour( Pixel( c.red * 2.55f, c.green * 2.55f, c.blue * 2.55f ) );
	}

	void DrawTimingBar( Point2f pos, Point2f size )
	{
		Play::Graphics::DrawTimingBar( pos, size );
	}


	//**************************************************************************************************
	// Miscellaneous functions
	//**************************************************************************************************

	bool KeyPressed( int vKey )
	{
		return Play::Input::KeyPressed( vKey, frameCount );
	}

	bool KeyDown( int vKey )
	{
		return Play::Input::KeyDown( vKey );
	}

	int RandomRoll( int sides )
	{
		return ( rand() % sides ) + 1;
	}

	int RandomRollRange( int begin, int end )
	{
		int range = abs( end - begin );
		int rnd = ( rand() % ( range + 1 ) );
		if( end > begin )
			return begin + rnd;
		else
			return end + rnd;
	}
}
//********************************************************************************************************************************
// File:		PlayManager.cpp
// Description:	A manager for providing simplified access to the PlayBuffer framework
// Platform:	Independent
// Notes:		The GameObject management is "opt in" as many will want to create their own GameObject class
//********************************************************************************************************************************

// Define this to opt in to the PlayManager
#ifdef PLAY_USING_GAMEOBJECT_MANAGER
namespace Play
{
	// Constructor for the GameObject struct - kept as simple as possible
	GameObject::GameObject(int type, Point2f newPos, int collisionRadius, int spriteId = 0)
		: type(type), pos(newPos), radius(collisionRadius), spriteId(spriteId)
	{
		// Member variables are assigned default values in the class header
		static int uniqueId = 0;
		m_id = uniqueId++;
	}

	// A map is used internally to store all the GameObjects and their unique ids
	static std::map<int, GameObject&> objectMap;

	// Used instead of Null return values, PlayMangager operations performed on this GameObject should fail transparently
	static GameObject noObject{ -1,{ 0, 0 }, 0, -1 };


	//**************************************************************************************************
	// GameObject functions
	//**************************************************************************************************
	int CreateGameObject(int type, Point2f newPos, int collisionRadius, const char* spriteName)
	{
		int spriteId = Play::Graphics::GetSpriteId(spriteName);
		// Deletion is handled in DestroyGameObject()
		GameObject* pObj = new GameObject(type, newPos, collisionRadius, spriteId);
		int id = pObj->GetId();
		objectMap.insert(std::map<int, GameObject&>::value_type(id, *pObj));
		return id;
	}

	GameObject& GetGameObject(int ID)
	{
		std::map<int, GameObject&>::iterator i = objectMap.find(ID);

		if (i == objectMap.end())
			return noObject;

		return i->second;
	}

	GameObject& GetGameObjectByType(int type)
	{
		int count = 0;

		for (std::pair<const int, GameObject&>& i : objectMap)
			if (i.second.type == type) { count++; }

		PLAY_ASSERT_MSG(count <= 1, "Multiple objects of type found, use CollectGameObjectIDsByType instead");

		for (std::pair<const int, GameObject&>& i : objectMap)
		{
			if (i.second.type == type)
				return i.second;
		}

		return noObject;
	}

	std::vector<int> CollectGameObjectIDsByType(int type)
	{
		std::vector<int> vec;
		for (std::pair<const int, GameObject&>& i : objectMap)
		{
			if (i.second.type == type)
				vec.push_back(i.first);
		}
		return vec; // Returning a copy of the vector
	}

	std::vector<int> CollectAllGameObjectIDs()
	{
		std::vector<int> vec;

		for (std::pair<const int, GameObject&>& i : objectMap)
			vec.push_back(i.first);

		return vec; // Returning a copy of the vector
	}

	void UpdateGameObject(GameObject& obj, bool bWrap, int wrapBorderSize, bool allowMultipleUpdatesPerFrame)
	{
		if (obj.type == -1) return; // Don't update noObject

		// We allow multiple updates if the object type has changed
		PLAY_ASSERT_MSG(obj.lastFrameUpdated != frameCount || obj.type != obj.oldType || allowMultipleUpdatesPerFrame, "Trying to update the same GameObject more than once in the same frame!");
		obj.lastFrameUpdated = frameCount;

		// Save the current position in case we need to go back
		obj.oldPos = obj.pos;
		obj.oldRot = obj.rotation;

		// Move the object according to a very simple physical model
		obj.velocity += obj.acceleration;
		obj.pos += obj.velocity;
		obj.rotation += obj.rotSpeed;

		// Handle the animation frame update
		obj.framePos += obj.animSpeed;
		if (obj.framePos > 1.0f)
		{
			obj.frame++;
			obj.framePos -= 1.0f;
		}

		// Wrap objects around the screen
		if (bWrap)
		{
			int dWidth = Play::Window::GetWidth();
			int dHeight = Play::Window::GetHeight();
			Vector2f origin = Play::Graphics::GetSpriteOrigin(obj.spriteId);

			if (obj.pos.x - origin.x - wrapBorderSize > dWidth)
				obj.pos.x = 0.0f - wrapBorderSize + origin.x;
			else if (obj.pos.x + origin.x + wrapBorderSize < 0)
				obj.pos.x = dWidth + wrapBorderSize - origin.x;

			if (obj.pos.y - origin.y - wrapBorderSize > dHeight)
				obj.pos.y = 0.0f - wrapBorderSize + origin.y;
			else if (obj.pos.y + origin.y + wrapBorderSize < 0)
				obj.pos.y = dHeight + wrapBorderSize - origin.y;
		}

	}

	void DestroyGameObject(int ID)
	{
		if (objectMap.find(ID) == objectMap.end())
		{
			PLAY_ASSERT_MSG(false, "Unable to find object with given ID");
		}
		else
		{
			GameObject* go = &objectMap.find(ID)->second;
			delete go;
			objectMap.erase(ID);
		}
	}

	void DestroyAllGameObjects(void)
	{
		for (std::pair<const int, GameObject&>& p : objectMap)
			delete& p.second;
		objectMap.clear();
	}

	void DestroyGameObjectsByType(int objType)
	{
		std::vector<int> typeVec = CollectGameObjectIDsByType(objType);
		for (size_t i = 0; i < typeVec.size(); i++)
			DestroyGameObject(typeVec[i]);
	}

	bool IsColliding(GameObject& object1, GameObject& object2)
	{
		//Don't collide with noObject
		if (object1.type == -1 || object2.type == -1)
			return false;

		int xDiff = int(object1.pos.x) - int(object2.pos.x);
		int yDiff = int(object1.pos.y) - int(object2.pos.y);
		int radii = object2.radius + object1.radius;

		// Game progammers don't do square root!
		return((xDiff * xDiff) + (yDiff * yDiff) < radii * radii);
	}

	bool IsVisible(GameObject& obj)
	{
		if (obj.type == -1) return false; // Not for noObject

		int spriteID = obj.spriteId;
		Vector2f spriteSize = Play::Graphics::GetSpriteSize(obj.spriteId);
		Vector2f spriteOrigin = Play::Graphics::GetSpriteOrigin(spriteID);

		Point2f pos = TRANSFORM_SPACE( obj.pos );

		return(pos.x + spriteSize.width - spriteOrigin.x > 0 && pos.x - spriteOrigin.x < Window::GetWidth() &&
			pos.y + spriteSize.height - spriteOrigin.y > 0 && pos.y - spriteOrigin.y < Window::GetHeight());
	}

	bool IsLeavingDisplayArea(GameObject& obj, Direction dirn)
	{
		if (obj.type == -1) return false; // Not for noObject

		int spriteID = obj.spriteId;
		Vector2f spriteSize = Play::Graphics::GetSpriteSize(obj.spriteId);
		Vector2f spriteOrigin = Play::Graphics::GetSpriteOrigin(spriteID);

		Point2f pos = TRANSFORM_SPACE( obj.pos );

		if (dirn != Direction::VERTICAL)
		{
			if (pos.x - spriteOrigin.x < 0 && obj.velocity.x < 0)
				return true;

			if (pos.x + spriteSize.width - spriteOrigin.x > Window::GetWidth() && obj.velocity.x > 0)
				return true;
		}

		if (dirn != Direction::HORIZONTAL)
		{
			if (pos.y - spriteOrigin.y < 0 && obj.velocity.y < 0)
				return true;

			if (pos.y + spriteSize.height - spriteOrigin.y > Window::GetHeight() && obj.velocity.y > 0)
				return true;
		}

		return false;
	}

	bool IsAnimationComplete(GameObject& obj)
	{
		if (obj.type == -1) return false; // Not for noObject
		return obj.frame >= Play::Graphics::GetSpriteFrames(obj.spriteId) - 1;
	}

	void SetGameObjectDirection(GameObject& obj, int speed, float angle)
	{
		if (obj.type == -1) return; // Not for noObject

		obj.rotation = angle;

		switch (axisRotation)
		{
		case CLOCKWISE_ZERO_UP:
			obj.velocity.x = speed * sin(obj.rotation);
			obj.velocity.y = speed * cos(obj.rotation);
			break;
		case ANTICLOCKWISE_ZERO_RIGHT:
			obj.velocity.x = speed * cos(obj.rotation);
			obj.velocity.y = speed * sin(obj.rotation);
			break;
		}

		if (coordSys == XRIGHT_YDOWN)
			obj.velocity.y = -obj.velocity.y;
	}

	void PointGameObject(GameObject& obj, int targetX, int targetY)
	{
		if (obj.type == -1) return; // Not for noObject

		float xdiff = targetX - obj.pos.x;
		float ydiff = targetY - obj.pos.y;

		if (coordSys == XRIGHT_YDOWN)
			ydiff = -ydiff;

		switch (axisRotation)
		{
			case CLOCKWISE_ZERO_UP:
				obj.rotation = atan2( xdiff, ydiff );
				break;
			case ANTICLOCKWISE_ZERO_RIGHT:
				obj.rotation = atan2( ydiff, xdiff );
				break;
		}
	}

	void SetSprite(GameObject& obj, const char* spriteName, float animSpeed)
	{
		int newSprite = Play::Graphics::GetSpriteId(spriteName);
		// Only reset the animation back to the start when it is new
		if (newSprite != obj.spriteId)
			obj.frame = 0;
		obj.spriteId = newSprite;
		obj.animSpeed = animSpeed;
	}

	void DrawObject(GameObject& obj)
	{
		if (obj.type == -1) return; // Don't draw noObject
		Play::Graphics::Draw(obj.spriteId, TRANSFORM_SPACE( TRANSFORM_Y( obj.pos ) ), obj.frame);
	}

	void DrawObjectTransparent(GameObject& obj, float opacity)
	{
		if (obj.type == -1) return; // Don't draw noObject
		Play::Graphics::DrawTransparent(obj.spriteId, TRANSFORM_SPACE( TRANSFORM_Y( obj.pos )), obj.frame, { opacity, 1.0f, 1.0f, 1.0f });
	}

	void DrawObjectRotated(GameObject& obj, float opacity)
	{
		if (obj.type == -1) return; // Don't draw noObject
		Play::Graphics::DrawRotated(obj.spriteId, TRANSFORM_SPACE( TRANSFORM_Y( obj.pos ) ), obj.frame, TRANSFORM_AXIS_ROT( obj.rotation ), obj.scale, { opacity, 1.0f, 1.0f, 1.0f });
	}

	void DrawGameObjectsDebug()
	{
		for (std::pair<const int, GameObject&>& i : objectMap)
		{
			GameObject& obj = i.second;
			int id = obj.spriteId;
			Vector2D size = Play::Graphics::GetSpriteSize(obj.spriteId);
			Vector2D origin = Play::Graphics::GetSpriteOrigin(id);

			// Corners of sprite drawing area
			Point2D p0 = obj.pos - origin;
			Point2D p2 = { obj.pos.x + size.width - origin.x, obj.pos.y + size.height - origin.y };
			Point2D p1 = { p2.x, p0.y };
			Point2D p3 = { p0.x, p2.y };

			DrawLine(p0, p1, cRed);
			DrawLine(p1, p2, cRed);
			DrawLine(p2, p3, cRed);
			DrawLine(p3, p0, cRed);

			DrawCircle(obj.pos, obj.radius, cBlue);

			DrawLine({ obj.pos.x - 20,  obj.pos.y - 20 }, { obj.pos.x + 20, obj.pos.y + 20 }, cWhite);
			DrawLine({ obj.pos.x + 20, obj.pos.y - 20 }, { obj.pos.x - 20, obj.pos.y + 20 }, cWhite);

			std::string s = Play::Graphics::GetSpriteName(obj.spriteId) + " f[" + std::to_string(obj.frame % Play::Graphics::GetSpriteFrames(obj.spriteId)) + "]";
			DrawDebugText({ (p0.x + p1.x) / 2.0f, p0.y - 20 }, s.c_str());
		}
	}
}


#endif
#endif // PLAY_IMPLEMENTATION

#ifdef PLAY_IMPLEMENTATION
#undef PLAY_IMPLEMENTATION // try to prevent multiple implementations
#endif
