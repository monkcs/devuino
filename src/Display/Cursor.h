#ifndef CURSOR_H
#define CURSOR_H

#include "Vector2D.h"

namespace devuino
{
	template<typename TPointer, typename TPosition>
	class Cursor : public Vector2D<TPosition>
	{
	  public:
		constexpr Cursor(const TPointer pointer, const bool active, const Vector2D<TPosition> position) : Vector2D<TPosition>(position), active(active), pointer(pointer)
		{
		}

		bool active;
		TPointer pointer;
	};
}

#endif
