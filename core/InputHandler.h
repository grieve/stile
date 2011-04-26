/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#ifndef STILE_INPUT_HANDLER
#define STILE_INPUT_HANDLER

namespace stile
{
	struct	MouseEvent;
	class	InputHandler;
}

struct stile::MouseEvent
{
	unsigned int	button;
	bool	state;
	unsigned int	x;
	unsigned int	y;
	float	secs;
};

class stile::InputHandler
{
public:
	virtual void handleKeyboardEvent	(
			int key,
			int x,
			int y,
			bool state, 
			bool special
		) = 0;
	virtual void handleMouseEvent	(
			int button,
			bool state,
			int x,
			int y
		) = 0;
	virtual void handleMouseMovement	(
			int x,
			int y,
			MouseEvent** buttons
		) {};
};

#endif //STILE_INPUT_HANDLER
