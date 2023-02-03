#pragma once
#include <glm/ext/vector_float3.hpp>
#include <math.h>
#include <vector>
#include <array>
#include <functional>

namespace MeshReconstruction
{
	// struct Vec3
	// {
	// 	double x, y, z;

	// 	Vec3 operator+(Vec3 const& o) const
	// 	{
	// 		return { x + o.x, y + o.y, z + o.z };
	// 	}

	// 	Vec3 operator-(Vec3 const& o) const
	// 	{
	// 		return { x - o.x, y - o.y, z - o.z };
	// 	}

	// 	Vec3 operator*(double c) const
	// 	{
	// 		return { c*x, c*y, c*z };
	// 	}

	// 	double Norm() const
	// 	{
	// 		return sqrt(x*x + y*y + z*z);
	// 	}

	// 	Vec3 Normalized() const
	// 	{
	// 		auto n = Norm();
	// 		return { x / n, y / n, z / n };
	// 	}
	// };

	struct Rect3
	{
		glm::vec3 min;
		glm::vec3 size;
	};

	using Triangle = std::array<int, 3>;

	struct Mesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> indexes;
		std::vector<glm::vec3> vertexNormals;
	};

	using Fun3s = std::function<double(glm::vec3 const&)>;
	using Fun3v = std::function<glm::vec3(glm::vec3 const&)>;
}