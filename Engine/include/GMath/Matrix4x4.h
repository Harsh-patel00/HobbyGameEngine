//
// Created by Harsh on 25/11/2022.
//

#include "Vector.h"

#ifndef GAMEENGINE_MATRIX4X4_H
#define GAMEENGINE_MATRIX4X4_H

namespace GMath
{
   template<typename T, int size>
   struct Matrix
   {
	   public:
		   T mat[size][size]{0}; // Initialize it with zero

	   public:
		   Matrix() = default;
		   explicit Matrix(T initialValue)
		   {
			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   mat[i][j] = initialValue;
				   }
			   }
		   }

	   public:
		   static Matrix GetIdentityMatrix()
		   {
			   Matrix identity{};
			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   if(i == j)
						   identity.mat[i][j] = 1;
				   }
			   }
			   return identity;
		   }

	   public:
		   Matrix operator*(const Matrix &mat2)
		   {
			   Matrix result{};

			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   int interResult = 0;
					   for (int k = 0; k < size; ++k)
					   {
						   interResult += this->mat[i][k] * mat2.mat[k][j];
					   }
					   result.mat[i][j] = interResult;
				   }
			   }

			   return result;
		   }
		   Matrix operator+(const Matrix &mat2)
		   {
			   Matrix result{};

			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   result.mat[i][j] = mat[i][j] + mat2.mat[i][j];
				   }
			   }

			   return result;
		   }
		   Matrix operator*(const T &scalar)
		   {
			   Matrix scaledMatrix{};
			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   scaledMatrix.mat[i][j] = mat[i][j] * scalar;
				   }
			   }

			   return scaledMatrix;
		   }
		   void operator*=(const Matrix &matrix)
		   {
			   *this = *this * matrix;
		   }

	   public:
		   // Declaring operators overrides as friend, allows use to take multiple parameters
		   // Else operator performs the operation with the instance of this class and other parameter
		   friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
		   {
			   for (int i = 0; i < size; i++)
			   {
				   for (int j = 0; j < size; j++)
				   {
					   os << "\nMatrix[" << i << "][" << j << "] :: " << matrix.mat[i][j];
				   }
			   }

			   return os;
		   }
		   friend Matrix operator*(const Matrix &mat1, const Matrix &mat2)
		   {
			   Matrix result;

			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   int interResult = 0;
					   for (int k = 0; k < size; ++k)
					   {
						   interResult += mat1.mat[i][k] * mat2.mat[k][j];
					   }
					   result.mat[i][j] = interResult;
				   }
			   }
			   return result;
		   }
		   friend Point<T, size> operator*(const Point<T, size> &p, const Matrix &mat1)
		   {
			   Point<T, size> result;

			   for (int j = 0; j < size; ++j)
			   {
				   int interResult = 0;
				   for (int k = 0; k < size; ++k)
				   {
					   interResult += p.point[0][k] * mat1.mat[k][j];
				   }
				   result.point[0][j] = interResult;
			   }

			   if(size == 1)
			   {
				   result.x = result.point[0][0];
			   }
			   else if(size == 2)
			   {
				   result.x = result.point[0][0];
				   result.y = result.point[0][1];
			   }
			   else if(size == 3)
			   {
				   result.x = result.point[0][0];
				   result.y = result.point[0][1];
				   result.z = result.point[0][2];
			   }
			   else if(size == 4)
			   {
				   result.x = result.point[0][0];
				   result.y = result.point[0][1];
				   result.z = result.point[0][2];
				   result.w = result.point[0][3];
			   }

			   return result;
		   }
		   friend Matrix operator*(const T &scalar, const Matrix &matrix)
		   {
			   Matrix scaledMatrix{};
			   for (int i = 0; i < size; ++i)
			   {
				   for (int j = 0; j < size; ++j)
				   {
					   scaledMatrix.mat[i][j] = matrix.mat[i][j] * scalar;
				   }
			   }

			   return scaledMatrix;
		   }
   };

   using Mat2f = Matrix<float, 2>;
   using Mat2d = Matrix<double, 2>;
   using Mat2i = Matrix<int, 2>;

   using Mat3f = Matrix<float, 3>;
   using Mat3d = Matrix<double, 3>;
   using Mat3i = Matrix<int, 3>;

   using Mat4f = Matrix<float, 4>;
   using Mat4d = Matrix<double, 4>;
   using Mat4i = Matrix<int, 4>;
}

#endif //GAMEENGINE_MATRIX4X4_H
