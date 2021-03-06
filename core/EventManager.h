/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#ifndef STILE_EVENT_MANAGER
#define STILE_EVENT_MANAGER

#include <vector>
#include "InputHandler.h"
#include "Timer.h"
#include "Logger.h"
#include "Configurator.h"
#include "SFML/Window.hpp"

namespace stile
{
	enum GameState
	{
		GAME_STATE_NORMAL,
		GAME_STATE_PAUSED,
		GAME_STATE_SUSPENDED,
		GAME_STATE_OVER,
		GAME_STATE_EXIT,
		WINDOW_STATE_FOCUS,
		WINDOW_STATE_BLUR
	};
	enum MouseEventType
	{
	  MOUSE_LEFT,
	  MOUSE_RIGHT,
	  MOUSE_MIDDLE,
	  MOUSE_X1,
	  MOUSE_X2,
	  MOUSE_FOCUS
	};
	class EventManager;
}

class stile::EventManager
{
	typedef void (*StateChangeCallback) (GameState);

public:
            EventManager	          (Timer* timer, Logger* logger, Configurator* config);
            ~EventManager	          ();
	void      addKeyboardListener	    (InputHandler* listener);
	void      removeKeyboardListener	(InputHandler* listener);
	void      addMouseListener	      (InputHandler* listener);
	void      removeMouseListener	    (InputHandler* listener);
	void      addGameStateCallback	  (StateChangeCallback callback);
	void      removeGameStateCallback	(StateChangeCallback callback);
	void      setGameState            (GameState gameState);
	GameState	getGameState            ();
	bool      keyPressed              (int key);
	void      handleKeyEvent          (unsigned int key, int x, int y, bool state, bool alt, bool ctrl, bool shift);
	void      handleMouseEvent        (MouseEventType event, int state, int x, int y, bool alt, bool ctrl, bool shift);
	void      handleMouseMovement     (int x, int y);
	void      shutdown                (int exitCode);
	void      processWindowEvents     (sf::Window* window);

private:
	struct            EventManagerImpl;
	EventManagerImpl& mImpl;

	EventManager            (EventManager& copy);
	EventManager operator=  (EventManager& rhs);
};
#endif //STILE_EVENT_MANAGER
