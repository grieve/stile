#ifndef STILE_VECTOR
#define STILE_VECTOR

#include <iostream>
#include <string>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace stile
{
	namespace math
	{
		class Vector2D;
		class Vector3D;
	}
}

class stile::math::Vector2D
{
public:

		Vector2D	(float x = 0, float y = 0);
		~Vector2D	();
	Vector2D	operator*	(float scalar) const;
	Vector2D	operator+	(const Vector2D &vect) const;
	Vector2D	operator-	(const Vector2D &vect) const;
	void	rotate	(float angle);
	float	crossproduct	(const Vector2D &vect2) const;
	float	magnitude	();
	void	normalise	();
	float	dotproduct	(const Vector2D &vect) const;
	float	getAngle	();

	float	cX;
	float	cY;
};

class stile::math::Vector3D
{
public:

		Vector3D	(float x = 0, float y = 0, float z = 0);
		~Vector3D	();

	float	cX;
	float	cY;
	float	cZ;
};

#endif //STILE_VECTOR
