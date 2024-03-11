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
			Mesh(Mesh &m)
			{
				_vertices = m._vertices;
				_indices = m._indices;
				_tris = m._tris;
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

		   void SetVertices(const std::vector<Point3f> &verts)
		   {
			   _vertices = verts;
			   GenerateTris(); // Update the _tris vector with latest vertices
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

					DrawTriangle(quadSubIndices, window, color);
				}
				else if(_drawMode == MeshDrawMode::Lines)
				{
					// for each index in indices
					for(int i = 0; i < _indices.size() - 1; i += 2)
					{
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
		   void GenerateTris()
		   {
			   _tris.clear();

			   GGraphics::Primitives2d::Triangle tri{};
			   std::vector<int> indicesForTheTriangle{};

			   // for each index in indices
			   for(int i = 0; i < _indices.size(); i++)
			   {
				   tri.points[i % 3] = _vertices[_indices[i]];
				   indicesForTheTriangle.push_back(_indices[i]);

				   if(i%3 == 2)
				   {
					   _tris.push_back(tri);
					   _triIndicesMap.insert({_tris.size(), indicesForTheTriangle});
					   indicesForTheTriangle = {};
					   tri = {};
				   }
			   }

			   //std::cout << "Mesh :: GenerateTris :: Total tris after generation :: " << _tris.size() << '\n';
		   }
		   void DrawTriangle(const std::vector<int>& indexList, GEngine::EngineWindow *window, Color &lineColor)
		   {
			   //if(indexList.size() % 3 != 0) throw std::length_error("Indices for triangle must be multiples of 3.");
			   //
			   //// for each index in indices
			   //for(int i = 0; i < indexList.size() - 2; i+=3)
			   //{
				//   auto tri = Primitives2d::Triangle
				//		   {
				//				   _vertices[indexList[i]],
				//				   _vertices[indexList[i + 1]],
				//				   _vertices[indexList[i + 2]]
				//		   };
			   //
				//   tri.Draw(window, lineColor);
			   //
				//   	std::cout << "Tri :: \n";
				//   	tri.Print();
			   //}
		   }
   };
}
#endif //GAMEENGINE_MESH_H
