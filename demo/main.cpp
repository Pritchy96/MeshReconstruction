#include <MeshReconstruction.h>
#include <IO.h>
#include <glm/geometric.hpp>

using namespace MeshReconstruction;

int main()
{
	auto sphereSdf = [](glm::vec3 const& pos)
	{
		auto const Radius = 1.0;
		return glm::length(pos) - Radius;
	};

	Rect3 domain;
	domain.min = { -1.1, -1.1, -1.1 };
	domain.size = {2.2, 2.2, 2.2};

	glm::vec3 cubeSize{ 0.5, 0.5, 0.5 };

	auto mesh = MarchCube(sphereSdf, domain, cubeSize);
	WriteObjFile(mesh, "sphere.obj");
}