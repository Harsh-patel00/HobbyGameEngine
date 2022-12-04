//
// Created by Harsh on 25/11/2022.
//

#ifndef GAMEENGINE_MATRIX3X3_H
#define GAMEENGINE_MATRIX3X3_H

template<typename T>
struct Matrix3x3
{
	public:
		T mat[3][3]{0}; // Initialize it with zero

	public:
		Matrix3x3() = default;

		explicit Matrix3x3(T initialValue)
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					mat[i][j] = initialValue;
				}
			}
		}

	public:
		static Matrix3x3 GetIdentityMatrix()
		{
			Matrix3x3 identity{};
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if(i == j)
					{
						identity.mat[i][j] = 1;
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

		Matrix3x3 operator*(Matrix3x3 &mat2)
		{
			Matrix3x3 result{};

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					T interResult = 0;
					for (int k = 0; k < 3; ++k)
					{
						interResult += (*this)[i][k] * mat2[k][j];
					}
					result[i][j] = interResult;
				}
			}

			return result;
		}

		Matrix3x3 operator+(const Matrix3x3 &mat2)
		{
			Matrix3x3 result{};

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					result[i][j] = this[i][j] + mat2[i][j];
				}
			}

			return result;
		}

		Matrix3x3 operator*(const T &scalar)
		{
			Matrix3x3 scaledMatrix3x3{};
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					scaledMatrix3x3[i][j] = this[i][j] * scalar;
				}
			}

			return scaledMatrix3x3;
		}

		Point3<T> operator*(const Point3<T> &p)
		{
			Point3<T> result;

			for (int j = 0; j < 3; ++j)
			{
				T interResult = 0;
				for (int k = 0; k < 3; ++k)
				{
					interResult += (*this)[j][k] * p.point[0][k];
				}
				result.point[0][j] = interResult;
			}

			result.x = result.point[0][0];
			result.y = result.point[0][1];
			result.z = result.point[0][2];

			return result;
		}

		void operator*=(const Matrix3x3 &matrix)
		{
			*this = *this * matrix;
		}

	public:
		// Declaring operators overrides as friend, allows use to take multiple parameters
		// Else operator performs the operation with the instance of this class and other parameter
		friend std::ostream &operator<<(std::ostream &os, Matrix3x3 matrix)
		{
			os << "\nMatrix3x3 :: \n";
			for (int i = 0; i < 3; i++)
			{
				os << "[" << i << "]";
				for (int j = 0; j < 3; j++)
				{
					os << " :: " << matrix[i][j];
				}

				os << "\n";
			}

			return os;
		}

		friend Matrix3x3 operator*(const Matrix3x3 &mat1, const Matrix3x3 &mat2)
		{
			Matrix3x3 result;

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					T interResult = 0;
					for (int k = 0; k < 3; ++k)
					{
						interResult += mat1[i][k] * mat2[k][j];
					}
					result[i][j] = interResult;
				}
			}
			return result;
		}

		friend Matrix3x3 operator*(const T &scalar, const Matrix3x3 &matrix)
		{
			Matrix3x3 scaledMatrix{};
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					scaledMatrix[i][j] = matrix[i][j] * scalar;
				}
			}
			return scaledMatrix;
		}
};

#endif //GAMEENGINE_MATRIX3X3_H
