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
		void Move(vec2<int> pos);

		/*
		 * Get Methods
		 */
		int x() const;
		int y() const;

		vec2<int> position() const;
		vec2<int> dimensions() const;

		/*
		 * Set Methods
		 */
		void SetX(int x);
		void SetY(int y);

		void SetPosition(int x, int y);
		void SetPosition(vec2<int> pos);

		void SetDimensions(int w, int h);
		void SetDimensions(vec2<int> dim);

		/*
		 * Public Attributes
		 */
		Align origin;
		int w;
		int h;

	private:

		/*
		 * Private Attributes
		 */
		int _x;
		int _y;
		
		bool _moveToTarget;
		Entity* _targetObj;
		vec2<int> _targetPos;
};
