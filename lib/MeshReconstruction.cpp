#include "MeshReconstruction.h"
#include "Cube.h"
#include "Triangulation.h"
#include <glm/geometric.hpp>

using namespace MeshReconstruction;
using namespace std;

// Adapted from here: http://paulbourke.net/geometry/polygonise/

namespace
{
	glm::vec3 NumGrad(Fun3s const& f, glm::vec3 const& p)
	{
		auto const Eps = 1e-6;
		glm::vec3 epsX{ Eps, 0, 0 }, epsY{ 0, Eps, 0 }, epsZ{ 0, 0, Eps };
		auto gx = (f(p + epsX) - f(p - epsX)) / 2;
		auto gy = (f(p + epsY) - f(p - epsY)) / 2;
		auto gz = (f(p + epsZ) - f(p - epsZ)) / 2;
		return { gx, gy, gz };
	}
}

Mesh MeshReconstruction::MarchCube(Fun3s const& sdf, Rect3 const& domain)
{
	float NumCubes = 50.0f;
	glm::vec3 cubeSize = domain.size * (1.0f / NumCubes);

	return MarchCube(sdf, domain, cubeSize);
}

Mesh MeshReconstruction::MarchCube(
	Fun3s const& sdf,
	Rect3 const& domain,
	glm::vec3 const& cubeSize,
	double isoLevel,
	Fun3v sdfGrad)
{
	// Default value.
	sdfGrad = sdfGrad == nullptr
		? [&sdf](glm::vec3 const& p) { return NumGrad(sdf, p); }
		: sdfGrad;

	auto const NumX = static_cast<int>(ceil(domain.size.x / cubeSize.x));
	auto const NumY = static_cast<int>(ceil(domain.size.y / cubeSize.y));
	auto const NumZ = static_cast<int>(ceil(domain.size.z / cubeSize.z));

	float const HalfCubeDiag = glm::length(cubeSize) / 2.0f;
	auto const HalfCubeSize = cubeSize * 0.5f;

	Mesh mesh;

	for (auto ix = 0; ix < NumX; ++ix)
	{
		auto x = domain.min.x + ix * cubeSize.x;
			
		for (auto iy = 0; iy < NumY; ++iy)
		{
			auto y = domain.min.y + iy * cubeSize.y;
			
			for (auto iz = 0; iz < NumZ; ++iz)
			{
				auto z = domain.min.z + iz * cubeSize.z;
				glm::vec3 min{ x, y, z };

				// Process only if cube lies within narrow band around surface.
				auto cubeCenter = min + HalfCubeSize;
				auto dist = abs(sdf(cubeCenter) - isoLevel);
				if (dist > HalfCubeDiag) continue;

				Cube cube({ min, cubeSize }, sdf);
				auto intersect = cube.Intersect(isoLevel);
				Triangulate(intersect, sdfGrad, mesh);
			}
		}
	}

	return mesh;
}
