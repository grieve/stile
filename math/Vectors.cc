#include "Vectors.h"

namespace stile
{
	namespace math
	{
		Vector2D::Vector2D	(
				float x,
				float y
			)
		{
			cX = x;
			cY = y;
		}

		Vector2D::~Vector2D ()
		{
		}

		Vector2D Vector2D::operator*	(
				float scalar
			) const
		{
			return Vector2D(cX * scalar, cY * scalar);
		}

		Vector2D Vector2D::operator+	(
				const Vector2D &vect
			) const
		{
			return Vector2D(cX + vect.cX, cY + vect.cY);
		}

		Vector2D Vector2D::operator-	(
				const Vector2D &vect
			) const
		{
			return Vector2D(cX - vect.cX, cY - vect.cY);
		}

		void Vector2D::rotate	(
				float angle
			)
		{
			float xt = (cX * cosf(angle)) - (cY * sinf(angle));
			float yt = (cY * cosf(angle)) + (cX * sinf(angle));
			cX = xt;
			cY = yt;
		}

		float Vector2D::crossproduct	(
				const Vector2D &vect2
			) const
		{
			return (this->cX * vect2.cY) - (this->cY * vect2.cX);
		}

		float Vector2D::magnitude()
		{
			return sqrtf(cX * cX +cY * cY);
		}

		void Vector2D::normalise()
		{
			float mag = sqrtf(cX* cX + cY * cY);
			this->cX = cX / mag;
			this->cY = cY / mag;
		}

		float Vector2D::dotproduct	(
				const Vector2D &vect
			) const
		{
			return (cX * vect.cX) + (cY * vect.cY);
		}

		float Vector2D::getAngle()
		{
			if ( cY == 0)
				if (cX > 0)
					return (0.5*M_PI);
				if (cX < 0)
					return (1.5*M_PI);
				else
					return 0;

			float ang = atan(cX/cY);
			if (cX > 0)
				if (cY > 0)
					return ang;
				else
					return M_PI-ang;
			else
				if (cY > 0)
					return (2*M_PI)-ang;
				else
					return M_PI+ang;
		}
	}
}
