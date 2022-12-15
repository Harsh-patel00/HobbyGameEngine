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
	   std::vector<Point3f> _verts{};
	   std::vector<int> _indices{};
	   bool _drawIndexedMesh{};

	   public:
			Mesh() = default;
			explicit Mesh(PRIMITIVE3DTYPE type, bool isIndexed = false)
			{
				_drawIndexedMesh = isIndexed;

				switch (type)
				{
					case PRIMITIVE3DTYPE::Cube:
							for (int & index : Primitives3d::Cube::indices)
							{
								_indices.push_back(index);
							}
							for (auto & vertex : Primitives3d::Cube::vertices)
							{
								_verts.push_back(vertex);
							}
							for (auto &tri: Primitives3d::Cube::tris)
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
			Mesh(Mesh &m, bool isIndexed = false)
			{
				_drawIndexedMesh = isIndexed;

				_tris = m.GetTriangles();
				_verts = *m.GetVertices();
				_indices = m.GetIndices();
			}

			// If a default mesh created, then by calling this function you'll override the mesh
			void SetTriangles(const std::vector<GGraphics::Primitives2d::Triangle> &meshTris)
			{
				_tris = meshTris;
			}

			// This function returns the address of _tris which can't be modified
		   std::vector<GGraphics::Primitives2d::Triangle>& GetTriangles()
		   {
				return _tris;
		   }

		   void SetIndices(const std::vector<int> &indices)
		   {
				_indices = indices;
		   }

		   [[nodiscard]] const std::vector<int>& GetIndices() const
		   {
				return _indices;
		   }

		   void SetVerts(const std::vector<Point3f> &verts)
		   {
				_verts = verts;
		   }

		   std::vector<Point3f>* GetVertices()
		   {
				return &_verts;
		   }

		   // If you use default constructor it'll not render anything
			void Draw(GEngine::EngineWindow *window, Color lineColor)
			{
				if(_drawIndexedMesh)
				{
					DrawIndexed(window, lineColor);
				}
				else
				{
					for (auto tri: _tris)
					{
						tri.Draw(window, lineColor);
					}
				}
			}

	   private:
			void DrawIndexed(GEngine::EngineWindow *window, Color lineColor)
			{
				GGraphics::Primitives2d::Triangle tri{};
				// for each index in indices
				for(int i = 0; i < _indices.size(); i++)
				{
					tri.points[i%3] = _verts[_indices[i]];

					if(i%3 == 2)
					{
						tri.Draw(window, lineColor);
						tri = {};
					}
				}
			}
   };
}
#endif //GAMEENGINE_MESH_H
