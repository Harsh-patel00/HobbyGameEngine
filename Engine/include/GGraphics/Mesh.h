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
		LineStrip,
		Point
	};

   class Mesh
   {
	   // Store all the triangles of the mesh
	   std::vector<GGraphics::Primitives2d::Triangle> _tris{};
	   std::vector<Point3f> _vertices{};
	   std::vector<int> _indices{};

	   // This maps the index of the triangles in the _tris vector with the indices required to draw that triangle
	   std::map<int, std::vector<int>> _triIndicesMap{};

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

			void SetTriangles(const std::vector<GGraphics::Primitives2d::Triangle> &tris)
			{
				// When we are setting the triangles, we only need to set the indices of the triangle
				// as we already have the vertices.
				_indices.clear();
				//std::cout << "Mesh :: SetTriangles :: Tris size :: " << tris.size() << ", _tris size :: " << _tris.size() << '\n';

				// For every passed tris
				for (auto &passedTri : tris)
				{
					for ( int i = 0; i < _tris.size(); ++i )
					{
						// If the triangle we want to render is already present in the generated triangles
						// that means we already know the indices for that in the map
						if(passedTri == _tris[i])
						{
							for (auto &triIndex : _triIndicesMap[i])
							{
								_indices.push_back(triIndex);
							}
						}
						else
						{
							// Do Nothing
						}
					}
				}

				// To generate the _tris vector
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

		   // Use when only vertex positions change (transforms) — indices and topology unchanged
		   void SetVertices(const std::vector<Point3f> &verts)
		   {
			   _vertices = verts;
			   UpdateTriVertices();
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
			void Draw(GEngine::EngineWindow *window, Color color)
			{
				//std::cout << "Mesh :: Draw :: Starting Drawing...\n";

				if(_indices.empty()) return;

				//std::cout << "Mesh :: Draw :: Did not Returned\n";

				if(_drawMode == MeshDrawMode::Triangle)
				{
					//std::cout << "Mesh :: Draw :: Draw Mode Triangle :: " << _tris.size() << ", Vertices Count :: " << _vertices.size() << '\n';
					for (auto& tri : _tris)
					{
						//std::cout << "Mesh :: Draw :: Tri :: \n";
						//tri.Print();
						tri.Draw(window, color, false);
					}

					//DrawTriangle(_indices, window, color);
				}
				else if(_drawMode == MeshDrawMode::Quad)
				{
					// Each quad (4 indices) is split into 2 triangles: (0,1,2) and (0,2,3)
					for (size_t i = 0; i + 3 < _indices.size(); i += 4)
					{
						auto &v0 = _vertices[_indices[i]];
						auto &v1 = _vertices[_indices[i + 1]];
						auto &v2 = _vertices[_indices[i + 2]];
						auto &v3 = _vertices[_indices[i + 3]];

						Primitives2d::Triangle{v0, v1, v2}.Draw(window, color, false);
						Primitives2d::Triangle{v0, v2, v3}.Draw(window, color, false);
					}
				}
				else if(_drawMode == MeshDrawMode::Lines)
				{
					//std::cout << "DrawMode :: Lines\n";

					// for each index in indices
					for(int i = 0; i < _indices.size() - 1; i += 2)
					{
						//std::cout << "Line :: Start :: " << _indices[i] << ", End :: " << _indices[i+1] << '\n';
						GGraphics::Primitives2d::Line{_vertices[_indices[i]], _vertices[_indices[i+1]], window, color}.Draw();
					}
				}
				else if(_drawMode == MeshDrawMode::LineStrip)
				{
					// for each index in indices
					for(int i = 0; i < _indices.size() - 1; i++)
					{
						GGraphics::Primitives2d::Line{_vertices[_indices[i]], _vertices[_indices[i+1]], window, color}.Draw();
					}
				}
				else if(_drawMode == MeshDrawMode::Point)
				{
					for (auto & vertex : _vertices)
					{
						window->DrawPixel((int)vertex.x, (int)vertex.y, color);
					}
				}

				//std::cout << "Mesh :: Draw :: Draw Complete.\n";
			}


	   private:
		   // Full rebuild — call only when indices/topology change
		   void GenerateTris()
		   {
			   _tris.clear();
			   _triIndicesMap.clear();

			   if (_drawMode != MeshDrawMode::Triangle) return;

			   GGraphics::Primitives2d::Triangle tri{};
			   std::vector<int> indicesForTheTriangle{};

			   for(size_t i = 0; i < _indices.size(); i++)
			   {
				   tri.points[i % 3] = _vertices[_indices[i]];
				   indicesForTheTriangle.push_back(_indices[i]);

				   if(i % 3 == 2)
				   {
					   _tris.push_back(tri);
					   _triIndicesMap.insert({static_cast<int>(_tris.size() - 1), indicesForTheTriangle});
					   indicesForTheTriangle.clear();
					   tri = {};
				   }
			   }
		   }

		   // Fast path — only repositions existing triangle vertices without rebuilding topology
		   void UpdateTriVertices()
		   {
			   if (_drawMode != MeshDrawMode::Triangle) return;

			   // If triangle count doesn't match (first call or topology changed), do a full rebuild
			   if (_tris.size() != _indices.size() / 3)
			   {
				   GenerateTris();
				   return;
			   }

			   // Just update vertex positions in existing triangles
			   for (size_t i = 0; i < _indices.size(); i++)
			   {
				   _tris[i / 3].points[i % 3] = _vertices[_indices[i]];
			   }
		   }
   };
}
#endif //GAMEENGINE_MESH_H
