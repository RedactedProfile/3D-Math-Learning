#include <iostream>


typedef struct vec4
{
	float x, y, z, w;

	vec4() {}

	vec4(float _x, float _y, float _z, float _w)
	{
		x = _x; 
		y = _y;
		z = _z;
		w = _w;
	}

	static float DotProduct(vec4 a, vec4 b)
	{
		std::cout << "Dot Product of (" << a.x << " * " << b.x << ") + (" << a.y << " * " << b.y << ") + (" << a.z << " * " << b.z << ") + (" << a.w << " * " << b.w << ") = ";
		std::cout << "(" << (a.x * b.x) << ") + (" << (a.y * b.y) << ") + (" << (a.z * b.z) << ") + (" << (a.w * b.w) << ") = ";

		float res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);

		std::cout << res << "\n\r";

		return res;
	}
} vec4;

typedef struct mat4x4
{
	static const int size = 4;
	union 
	{
		vec4 r[size];
		struct
		{
			float
				_11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;
		};
		float m[size][size];
	};

	mat4x4() {
		memset(this, 0, sizeof(*this));
	}

	void echo()
	{
		std::cout << "      | " << _11 << " " << _12 << " " << _13 << " " << _14 << " | \n\r";
		std::cout << " M =  | " << _21 << " " << _22 << " " << _23 << " " << _24 << " | \n\r";
		std::cout << "      | " << _31 << " " << _32 << " " << _33 << " " << _34 << " | \n\r";
		std::cout << "      | " << _41 << " " << _42 << " " << _43 << " " << _44 << " | \n\r\n\r";
	}
	
	static mat4x4 Zero()
	{
		return mat4x4();
	}

	static mat4x4 Identity()
	{
		mat4x4 m = mat4x4::Zero();
		m._11 = 1; m._22 = 1; m._33 = 1; m._44 = 1;
		return m;
	}

	/// <summary>
	/// Addition works by simply adding each corresponding element together
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	mat4x4 operator+(mat4x4 b)
	{
		mat4x4 a = *this;

		for (int x = 0; x < size; x++)
		{
			for (int y = 0; y < size; y++)
			{
				a.m[x][y] += b.m[x][y];
			}
		}

		return a;
	}

	/// <summary>
	/// Multiplication works by getting the dot product of each row of a against each column of b 
	/// </summary>
	/// <returns></returns>
	mat4x4 operator*(mat4x4 b)
	{
		mat4x4 a = *this;
		
		mat4x4 tmp = mat4x4::Zero();

		for (int row = 0; row < size; row++)
		{
			vec4 aRow( a.m[row][0], a.m[row][1], a.m[row][2], a.m[row][3] );
			for (int column = 0; column < size; column++)
			{
				vec4 bColumn(b.m[0][column], b.m[1][column], b.m[2][column], b.m[3][column]);
				tmp.m[row][column] = vec4::DotProduct(aRow, bColumn);
			}
		}

		return tmp;
	}

	uint16_t det()
	{
		return 0;
	}
	
} mat;


int main()
{
	mat4x4 
		a = mat4x4::Identity(), 
		b = mat4x4::Identity();

	a.r[0] = vec4(-1, 5, -4, 0);
	a.r[1] = vec4(3, 2, 1, 0);

	b.r[0] = vec4(2, 1, 0, 0);
	b.r[1] = vec4(0, -2, 1, 0);
	b.r[2] = vec4(-1, 2, 3, 0);

	a.echo();
	std::cout << "    X    \n\t\n\r";
	b.echo();
	std::cout << "---------------------------\n\t\n\r";

	//a = a + b;
	a = a * b; // should equate to the same identity

	a.echo();

	std::cout << "Test";
	return 0;
}