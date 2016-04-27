#pragma once
#include <cfloat>
#include <cmath>
#include <cassert>

#define PI 3.14159265359

	struct vec2
	{
		union
		{
			struct { float x, y; };
			float v[2];
			
		};

		vec2() {}
		vec2(float a_x, float a_y)
			: x(a_x), y(a_y) {}


		//static construction functions
		float magnitude() const; //pythagorean theorm
		static vec2 fromAngle(float angle);
		//unary oerations	
		float angle() const; //atan2f
		//vec2 normal() const;
		vec2 normalize();
		static vec2 random();
		static vec2 fromXZ(float *vec3) { return vec2{ vec3[0],vec3[2] }; }
		float &operator[](unsigned idx) { return v[idx]; }
		float  operator[](unsigned idx) const { return v[idx]; }

	};
	
	inline vec2 operator*(const vec2 &a, const vec2 &b) { return vec2{ a.x * b.x, a.y * b.y }; }
	
	//binary operators
	float dot(const vec2 &lhs, const vec2 &rhs);
	vec2 operator+(const vec2 &lhs, const vec2 &rhs);
	vec2 operator+=(const vec2 &lhs, const vec2 &rhs);
	vec2 operator-(const vec2 &lhs, const vec2 &rhs);
	vec2 operator-=(const vec2 &lhs, const vec2 &rhs);
	
	vec2 operator*(const vec2 &lhs, float rhs);
	vec2 operator*(float lhs, const vec2 & rhs);
	vec2 operator*=(const vec2 &lhs, float rhs);
	vec2 operator/(const vec2 &lhs, float rhs);
	vec2 operator/=(const vec2 &lhs, float rhs);
	
	bool operator==(const vec2 &lhs, const vec2 &rhs);
	bool operator!=(const vec2 &lhs, const vec2 &rhs);
	bool operator<(const vec2 &lhs, const vec2 &rhs);
	bool operator<=(const vec2 &lhs, const vec2 &rhs);
	bool operator>(const vec2 &lhs, const vec2 &rhs);
	bool operator>=(const vec2 &lhs, const vec2 &rhs);

	vec2 min(const vec2 &a, const vec2 &b);
	vec2 max(const vec2 &a, const vec2 &b);
	vec2 clamp(const vec2 &a, const vec2 &min, const vec2 &max);
	vec2 mix(const vec2 &start, const vec2 &end, float t);
	vec2 lerp(const vec2 &start, const vec2 &end, float t);
	inline float distance(const vec2 &a, const vec2 &b) { vec2 temp = a - b; return temp.magnitude(); }
	inline vec2 normal(const vec2 &a) { return a / a.magnitude(); }


	vec2 reflect(const vec2 &incident, const vec2 &normal
		);
	vec2 project(const vec2 &a, const vec2 &b);
	vec2 perp(vec2 &a);
	vec2 snap(const vec2 &val, const vec2 &lower, const vec2 &upper);

	//vec2 fromAngle(cont)
	//Intersections

	//float Circle(float x1, float y1, float r1, float x2, float y2, float r2);
	//float AABB(float x1, float y1, float hw1, float hh1, float x2, float y2, float hw2, float hh2);





