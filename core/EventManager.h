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

namespace stile
{
	enum GameState
	{
		GAME_STATE_NORMAL,
		GAME_STATE_PAUSED,
		GAME_STATE_SUSPENDED,
		GAME_STATE_OVER
	};
	class EventManager;
}

class stile::EventManager
{
	typedef void (*StateChangeCallback) (GameState);

public:
		EventManager	(Timer* timer, Logger* logger, Configurator* config);
		~EventManager	();
	void	addKeyboardListener	(InputHandler* listener);
	void	removeKeyboardListener	(InputHandler* listener);
	void	addMouseListener	(InputHandler* listener);
	void	removeMouseListener	(InputHandler* listener);
	void	addGameStateCallback	(StateChangeCallback callback);
	void	removeGameStateCallback	(StateChangeCallback callback);
	void	setGameState	(GameState gameState);
	GameState	getGameState	();
	bool	keyPressed	(int key, bool special = false);
	void	handleNormalKeyDown	(unsigned char key, int x, int y);
	void	handleNormalKeyUp	(unsigned char key, int x, int y);
	void	handleSpecialKeyDown	(int key, int x, int y);
	void	handleSpecialKeyUp	(int key, int x, int y);
	void	handleMouseEvent	(int button, int state, int x, int y);
	void	handleMouseMovement	(int x, int y);
	void	shutdown	(int exitCode);

private:
	struct	EventManagerImpl;
	EventManagerImpl&	mImpl;

	EventManager	(EventManager& copy);
	EventManager operator=	(EventManager& rhs);
};
#endif //STILE_EVENT_MANAGER
