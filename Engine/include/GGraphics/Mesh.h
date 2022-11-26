//
// Created by Harsh on 26/11/2022.
//

#include "Primitives3d.h"

#ifndef GAMEENGINE_MESH_H
#define GAMEENGINE_MESH_H

namespace GGraphics
{
	enum class PRIMITIVE3DTYPE
	{
			Cube,
			Sphere,
			Cylinder,
	};

   class Mesh
   {
	   // Store all the triangles of the mesh
	   std::vector<GGraphics::Primitives2d::Triangle> _tris{};

	   public:
			Mesh() = default;
			explicit Mesh(PRIMITIVE3DTYPE type)
			{
				switch (type)
				{
					case PRIMITIVE3DTYPE::Cube:
						for (auto & tri : Primitives3d::Cube::tris)
						{
							_tris.push_back(tri);
						}
						break;
					case PRIMITIVE3DTYPE::Sphere:
						break;
					case PRIMITIVE3DTYPE::Cylinder:
						break;
				}
			}

			// If a default mesh created, then by calling this function you'll override the mesh
			void SetTriangles(const std::vector<GGraphics::Primitives2d::Triangle> &meshTris)
			{
				_tris = meshTris;
			}

			// This function returns the address of _tris which can't be modified
		   [[nodiscard]] const std::vector<GGraphics::Primitives2d::Triangle>& GetTriangles() const
		   {
				return _tris;
		   }

		   // If you use default constructor it'll not render anything
			void Draw(GEngine::EngineWindow *window, Color lineColor)
			{
				for(auto tri : _tris)
				{
					tri.Draw(window, lineColor);
				}
			}
   };
}
#endif //GAMEENGINE_MESH_H
