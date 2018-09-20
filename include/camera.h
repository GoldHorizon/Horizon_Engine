#pragma once

#include "types.h"
#include "enumerations.h"

class Camera
{
	public:
		/*
		 * Constructors/Destructors
		 */
		Camera();
		~Camera();

		/*
		 * Class Methods
		 */
		void Move(int x, int y);
		void Move(Vec2<int> pos);

		/*
		 * Get Methods
		 */
		int x() const;
		int y() const;
		int w() const;
		int h() const;

		Vec2<int> position() const;
		Vec2<int> dimensions() const;

		Align origin() const;

		/*
		 * Set Methods
		 */
		void SetX(int x);
		void SetY(int y);
		void SetW(int w);
		void SetH(int h);

		void SetPosition(int x, int y);
		void SetPosition(Vec2<int> pos);
		void SetDimensions(int w, int h);
		void SetDimensions(Vec2<int> dim);

		void SetOrigin(Align origin);

	private:

		Align _origin;
		int _x;
		int _y;
		int _w;
		int _h;

};
