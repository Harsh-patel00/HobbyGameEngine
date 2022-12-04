//
// Created by Harsh on 25/11/2022.
//

#ifndef GAMEENGINE_MATRIX4X4_H
#define GAMEENGINE_MATRIX4X4_H

template<typename T>
struct Matrix4x4
{
	public:
		T mat[4][4]{0}; // Initialize it with zero

	public:
		Matrix4x4() = default;

		explicit Matrix4x4(T initialValue)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					(*this)[i][j] = initialValue;
				}
			}
		}

	public:
		static Matrix4x4 GetIdentityMatrix()
		{
			Matrix4x4 identity{};
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if(i == j)
					{
						identity[i][j] = 1;
					}
				}
			}
			return identity;
		}

	public:
		T *operator[](int index)
		{
			return mat[index];
		}

		Matrix4x4 operator*(Matrix4x4 mat2)
		{
			Matrix4x4 result{};

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					T interResult = 0;
					for (int k = 0; k < 4; ++k)
					{
						interResult += (*this)[i][k] * mat2[k][j];
					}
					result[i][j] = interResult;
				}
			}

			return result;
		}

		Matrix4x4 operator+(const Matrix4x4 &mat2)
		{
			Matrix4x4 result{};

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					result[i][j] = (*this)[i][j] + mat2[i][j];
				}
			}

			return result;
		}

		Matrix4x4 operator*(const T &scalar)
		{
			Matrix4x4 scaledMatrix{};
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					scaledMatrix[i][j] = (*this)[i][j] * scalar;
				}
			}

			return scaledMatrix;
		}

		Point4<T> operator*(const Point4<T> &p)
		{
			Point4<T> result;

			for (int j = 0; j < 4; ++j)
			{
				T interResult = 0;
				for (int k = 0; k < 4; ++k)
				{
					interResult += (*this)[j][k] * p.point[0][k];
				}
				result.point[0][j] = interResult;
			}

			result.x = result.point[0][0];
			result.y = result.point[0][1];
			result.z = result.point[0][2];
			result.w = result.point[0][3];

			return result;
		}

		Point3<T> operator*(const Point3<T> &p)
		{
			Point4<T> p3ToP4(p);
			Point4<T>intermediateResult = (*this) * p3ToP4;
			Point3<T> finalRes;

			if(intermediateResult.w != 0 && intermediateResult.w != 1)
			{
				finalRes = {
								intermediateResult.x / intermediateResult.w,
							    intermediateResult.y / intermediateResult.w,
				                intermediateResult.z / intermediateResult.w
							 };
			}
			else
			{
				finalRes = { intermediateResult.x, intermediateResult.y, intermediateResult.z };
			}


			return finalRes;
		}

		void operator*=(const Matrix4x4 &matrix)
		{
			*this = *this * matrix;
		}

	public:
		// Declaring operators overrides as friend, allows use to take multiple parameters
		// Else operator performs the operation with the instance of this class and other parameter
		friend std::ostream &operator<<(std::ostream &os, Matrix4x4 matrix)
		{
			os << "\nMatrix :: \n";
			for (int i = 0; i < 4; i++)
			{
				os << "[" << i << "]";
				for (int j = 0; j < 4; j++)
				{
					os << " :: " << matrix[i][j];
				}

				os << "\n";
			}

			return os;
		}

		friend Matrix4x4 operator*(const Matrix4x4 &mat1, const Matrix4x4 &mat2)
		{
			Matrix4x4 result;

			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					T interResult = 0;
					for (int k = 0; k < 4; ++k)
					{
						interResult += mat1[i][k] * mat2[k][j];
					}
					result[i][j] = interResult;
				}
			}
			return result;
		}

		friend Matrix4x4 operator*(const T &scalar, const Matrix4x4 &matrix)
		{
			Matrix4x4 scaledMatrix{};
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					scaledMatrix[i][j] = matrix[i][j] * scalar;
				}
			}

			return scaledMatrix;
		}
};

#endif //GAMEENGINE_MATRIX4X4_H
