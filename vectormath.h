#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include <initializer_list>
#include <math.h>

/////////////////////
//  MATRIX CLASS   //
/////////////////////

template<class T>
class Matrix3
{
private:
	T **m_data;
public:
	Matrix3()
	{
		m_data = new T*[3];
		for (int i = 0; i < 3; i++)
			m_data[i] = new T[3];
	}

	Matrix3(const std::initializer_list<std::initializer_list<T>> &list_ext)
	{
		assert(list_ext.size() == 3);

		m_data = new T*[3];
		for (int i = 0; i < 3; i++)
			m_data[i] = new T[3];

		int i = 0, j = 0;
		for (auto &list_int : list_ext)
		{
			assert(list_int.size() == 3);
			j = 0;
			for (auto &element : list_int)
			{
				m_data[i][j] = element;
				j++;
			}
			i++;
		}
	}

	void erase()
	{
		for (int i = 0; i < 3; i++)
			delete[] m_data[i];
		delete[] m_data;

		m_data = nullptr;
	}

	const T* operator[](const int r) const
	{
		assert(r >= 0 && r < 3);
		return m_data[r];
	}

	T* operator[](const int r)
	{
		assert(r >= 0 && r < 3);
		return m_data[r];
	}

	Matrix3<T>& operator=(const std::initializer_list<std::initializer_list<T>> list_ext)
	{
		assert(list_ext.size() == 3);

		this->erase();

		m_data = new T*[3];
		for (int i = 0; i < 3; i++)
			m_data[i] = new T[3];

		int i = 0, j = 0;
		for (auto &list_int : list_ext)
		{
			assert(list_int.size() == 3);
			j = 0;
			for (auto &element : list_int)
			{
				m_data[i][j] = element;
				j++;
			}
			i++;
		}

		return (*this);
	}

	Matrix3<T>& operator=(const Matrix3<T> &m)
	{
		this->erase();

		m_data = new T*[3];
		for (int i = 0; i < 3; i++)
			m_data[i] = new T[3];

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m_data[i][j] = m[i][j];

		return (*this);
	}

	~Matrix3()
	{
		delete[] m_data[0];
		delete[] m_data[1];
		delete[] m_data[2];

		delete[] m_data;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
std::ostream& operator<<(std::ostream &out, Matrix3<T> &m)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
			out << m[r][c] << " ";
		out << "\n";
	}

	return out;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(Matrix3<T> m1, Matrix3<T> m2)
{
	int s = 0;
	for (int r = 0; r < m1.getNumRows(); r++)
		for (int c = 0; c < m1.getNumCols(); c++)
			s += (m1[r][c] == m2[r][c]);

	if (s == m1.getNumRows() * m1.getNumCols())
		return true;
	else return false;
}

template<typename T>
bool operator!=(Matrix3<T> m1, Matrix3<T> m2)
{
	int s = 0;
	for (int r = 0; r < m1.getNumRows(); r++)
		for (int c = 0; c < m1.getNumCols(); c++)
			s += (m1[r][c] == m2[r][c]);

	if (s == m1.getNumRows() * m1.getNumCols())
		return false;
	else return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
Matrix3<T> operator+(const Matrix3<T> &left, const Matrix3<T> &right)
{
	return { {left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2]},
	{left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2]},
	{left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2]} };
}

template<typename T>
Matrix3<T>& operator+=(Matrix3<T> &left, const Matrix3<T> &right)
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			left[r][c] += right[r][c];

	return left;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
Matrix3<T> operator-(const Matrix3<T> &left, const Matrix3<T> &right)
{
	return { {left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2]},
	{left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2]},
	{left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2]} };
}

template<typename T>
Matrix3<T>& operator-=(Matrix3<T> &left, const Matrix3<T> &right)
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			left[r][c] -= right[r][c];

	return left;
}

template<typename T>
Matrix3<T>& operator-(Matrix3<T> &left)
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			left[r][c] = -left[r][c];

	return left;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
Matrix3<T>& operator*=(Matrix3<T> &left, const U &right)
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			left[r][c] *= right;
	return left;
}

template<typename T, typename U>
Matrix3<T> operator*(const Matrix3<T> &left, const U &right)
{
	return { {left[0][0] * right, left[0][1] * right, left[0][2] * right},
		{left[1][0] * right, left[1][1] * right, left[1][2] * right},
		{left[2][0] * right, left[2][1] * right, left[2][2] * right} };
}

template<typename T, typename U>
Matrix3<T> operator*(const U &left, const Matrix3<T> &right)
{
	return { {left * right[0][0], left * right[0][1], left * right[0][2]},
	{left * right[1][0], left * right[1][1], left * right[1][2]},
	{left * right[2][0], left * right[2][1], left * right[2][2]} };
}

template<typename T>
Matrix3<T> operator*(Matrix3<T> &left, Matrix3<T> &right)
{
	T _00 = left[0][0] * right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0];
	T _01 = left[0][0] * right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1];
	T _02 = left[0][0] * right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2];

	T _10 = left[1][0] * right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0];
	T _11 = left[1][0] * right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1];
	T _12 = left[1][0] * right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2];

	T _20 = left[2][0] * right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0];
	T _21 = left[2][0] * right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1];
	T _22 = left[2][0] * right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2];

	return { {_00,_01,_02},{_10,_11,_12},{_20,_21,_22} };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U>
Matrix3<T>& operator/=(Matrix3<T> &left, U right)
{
	for (int r = 0; r < 3; r++)
		for (int c = 0; c < 3; c++)
			left[r][c] /= right;
	return left;
}

template<typename T, typename U>
Matrix3<T> operator/(Matrix3<T> left, U right)
{
	return { {left[0][0] / right, left[0][1] / right, left[0][2] / right},
		{left[1][0] / right, left[1][1] / right, left[1][2] / right},
		{left[2][0] / right, left[2][1] / right, left[2][2] / right} };
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////
// 2D VECTOR MATHS //
/////////////////////

template<typename V2>
float Magnitude(const V2 &v)
{
	return sqrt(static_cast<float>(v.x * v.x + v.y * v.y));
}

template<typename V2>
V2 UnitVector(const V2 &v)
{
	return v / Magnitude(v);
}

template<typename V2>
bool operator>(const V2 &v1,const V2 &v2)
{
	if (Magnitude(v1) > Magnitude(v2))
		return true;
	else return false;
}

template<typename V2>
bool operator<(V2 &v1, V2 &v2)
{
	if (Magnitude(v1) > Magnitude(v2))
		return true;
	else return false;
}

/////////////////////
// 3D VECTOR MATHS //
/////////////////////

template<typename T>
sf::Vector3<T> operator*(const Matrix3<T> &m, const sf::Vector3<T> &v)
{
	return sf::Vector3<T>(
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
		);
}