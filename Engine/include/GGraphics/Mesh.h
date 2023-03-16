//
// Created by Harsh on 26/11/2022.
//

#include "Primitives3d.h"
#include <set>

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

	enum class MeshDrawMode
	{
		Triangle,
		Quad,
		Lines,
		LineStrip
	};

   class Mesh
   {
	   // Store all the triangles of the mesh
	   std::vector<GGraphics::Primitives2d::Triangle> _tris{};
	   std::vector<Point3f> _vertices{};
	   std::vector<int> _indices{};

	   MeshDrawMode _drawMode = MeshDrawMode::Triangle;

	   public:
			Mesh() = default;
			explicit Mesh(PRIMITIVE3DTYPE type)
			{
				switch (type)
				{
					case PRIMITIVE3DTYPE::Cube:
						SetIndices(Primitives3d::Cube::indices, MeshDrawMode::Triangle);
						for (auto & vertex : Primitives3d::Cube::vertices)
							{
								_vertices.push_back(vertex);
							}
						GenerateTris();
						break;
					case PRIMITIVE3DTYPE::Sphere:
					case PRIMITIVE3DTYPE::Cylinder:
						break;
				}
			}
			Mesh(const std::vector<Point3f>& vertices, const std::vector<int>& indices, MeshDrawMode drawMode)
			{
				for (auto &vertex: vertices)
				{
					_vertices.push_back(vertex);
				}
				SetIndices(indices, drawMode);
				GenerateTris();
			}
			Mesh(Mesh &m)
			{
				_vertices = m.GetVertices();
				SetIndices(m.GetIndices(), m.GetDrawMode());

				GenerateTris();
			}

		   std::vector<GGraphics::Primitives2d::Triangle> GetTriangles()
		   {
				return _tris;
		   }

		   void SetIndices(const std::vector<int> &indices, MeshDrawMode drawMode)
		   {
				switch(drawMode)
				{
					case MeshDrawMode::Triangle:
						if(indices.size() % 3 != 0) throw std::length_error("Indices for triangle must be multiples of 3.");
						break;
					case MeshDrawMode::Quad:
						if(indices.size() % 4 != 0) throw std::length_error("Indices for quad must be multiples of 4.");
						break;
					case MeshDrawMode::Lines:
						if(indices.size() % 2 != 0) throw std::length_error("Indices for line must be multiples of 2.");
						break;

					case MeshDrawMode::LineStrip:
					default:
						// Do nothing
						break;
				}

				_drawMode = drawMode;
				_indices = indices;
		   }

		   [[nodiscard]] std::vector<int> GetIndices() const
		   {
				return _indices;
		   }

		   void SetVertices(const std::vector<Point3f> &verts)
		   {
			   _vertices = verts;
		   }

		   [[nodiscard]] std::vector<Point3f> GetVertices() const
		   {
				return _vertices;
		   }

		   [[nodiscard]] MeshDrawMode GetDrawMode() const
		   {
				return _drawMode;
		   }

		   // If you use default constructor it'll not render anything
			void Draw(GEngine::EngineWindow *window, Color lineColor)
			{
				if(_indices.empty()) return;

				if(_drawMode == MeshDrawMode::Triangle)
				{
					DrawTriangle(_indices, window, lineColor);
				}
				else if(_drawMode == MeshDrawMode::Quad)
				{
					std::vector<int> quadSubIndices;

					for (int i = 0; i < _indices.size(); i+=2)
					{
						for (int j = 0; j < 3; ++j)
						{
							int ind = i + j;

							if( (i != 0 && j != 0) && ind % 4 == 0 )
							{
								ind  = ind - 4;
							}
							quadSubIndices.push_back(_indices[ind]);
						}
					}

					DrawTriangle(quadSubIndices, window, lineColor);
				}
				else if(_drawMode == MeshDrawMode::Lines)
				{
					// for each index in indices
					for(int i = 0; i < _indices.size() - 1; i += 2)
					{
						GGraphics::Primitives2d::Line{_vertices[_indices[i]], _vertices[_indices[i+1]], window, lineColor}.Draw();
					}
				}
				else if(_drawMode == MeshDrawMode::LineStrip)
				{
					// for each index in indices
					for(int i = 0; i < _indices.size() - 1; i++)
					{
						GGraphics::Primitives2d::Line{_vertices[_indices[i]], _vertices[_indices[i+1]], window, lineColor}.Draw();
					}
				}
			}
			void DrawPixel(GEngine::EngineWindow *window, Color color)
			{
				for (auto & vertex : _vertices)
				{
					window->DrawPixel((int)vertex.x, (int)vertex.y, color);
				}
			}

	   private:
		   void GenerateTris()
		   {
			   _tris.clear();

			   GGraphics::Primitives2d::Triangle tri{};
			   // for each index in indices
			   for(int i = 0; i < _indices.size(); i++)
			   {
				   tri.points[i % 3] = _vertices[_indices[i]];

				   if(i%3 == 2)
				   {
					   _tris.push_back(tri);
					   tri = {};
				   }
			   }
		   }
		   void DrawTriangle(const std::vector<int>& indexList, GEngine::EngineWindow *window, Color &lineColor)
		   {
			   if(indexList.size() % 3 != 0) throw std::length_error("Indices for triangle must be multiples of 3.");

			   // for each index in indices
			   for(int i = 0; i < indexList.size() - 2; i+=3)
			   {
				   Primitives2d::Triangle
						   {
								   _vertices[indexList[i]],
								   _vertices[indexList[i + 1]],
								   _vertices[indexList[i + 2]]
						   }.Draw(window, lineColor);
			   }
		   }
   };
}
#endif //GAMEENGINE_MESH_H
