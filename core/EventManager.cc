/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/

#include "EventManager.h"

struct stile::EventManager::EventManagerImpl
{
public:
	EventManager&	mParent;
	Timer&	mTimer;
	Logger&	mLogger;
	Configurator&	mConfig;
	GameState	mGameState;
	std::vector<StateChangeCallback>	mStateChangeCallbacks;
	std::vector<InputHandler*>	mKeyboardListeners;
	std::vector<InputHandler*>	mMouseListeners;
	MouseEvent*	mButtonStates	[10];
	bool	mNormalKeyMap	[256];
	bool	mSpecialKeyMap	[256];

	EventManagerImpl	(
			EventManager* parent,
			Timer* timer,
			Logger* logger,
			Configurator* config
		)
		: mParent	(*parent)
		, mTimer	(*timer)
		, mLogger	(*logger)
		, mConfig	(*config)
	{
		memset(mNormalKeyMap, false, sizeof(bool)*256);
		memset(mSpecialKeyMap, false, sizeof(bool)*256);
		for (unsigned int x = 0; x < 10; x++)
		{
			mButtonStates[x]	= new MouseEvent;
			mButtonStates[x]->button	= x;
			mButtonStates[x]->state	= false;
			mButtonStates[x]->x	= 0;
			mButtonStates[x]->y	= 0;
			mButtonStates[x]->secs	= 0;
		}
		mGameState = GAME_STATE_NORMAL;
		mLogger.debug(1, "EventManager started correctly.");
	}
};

stile::EventManager::EventManager	(
		Timer* timer,
		Logger* logger,
		Configurator* config
	)
	: mImpl (*new EventManagerImpl(this, timer, logger, config))
{
}

stile::EventManager::~EventManager()
{
}

void stile::EventManager::addKeyboardListener	(
		InputHandler* listener
	)
{
	for (unsigned int x=0; x<mImpl.mKeyboardListeners.size(); x++)
	{
		if (mImpl.mKeyboardListeners[x] == listener)
		{
			mImpl.mLogger.warning("EventManager: Keyboard listener already added: 0x%x", listener);
			return;
		}
	}
	mImpl.mKeyboardListeners.push_back (listener);
	mImpl.mLogger.debug(3,"EventManager: New keyboard listener added: 0x%x", listener);
}

void stile::EventManager::removeKeyboardListener	(
		InputHandler* listener
	)
{
	for (unsigned int x=0; x<mImpl.mKeyboardListeners.size(); x++)
	{
		if (mImpl.mKeyboardListeners[x] == listener)
		{
			mImpl.mKeyboardListeners.erase(mImpl.mKeyboardListeners.begin()+x);
			mImpl.mLogger.debug(3,"EventManager: Keyboard listener removed: 0x%x", listener);
			return;
		}
	}
	mImpl.mLogger.warning("EventManager: Cannot remove keyboard listener: 0x%x", listener);
}

void stile::EventManager::addMouseListener	(
		InputHandler* listener
	)
{
	for (unsigned int x=0; x<mImpl.mMouseListeners.size(); x++)
	{
		if (mImpl.mMouseListeners[x] == listener)
		{
			mImpl.mLogger.warning("EventManager: Mouse listener already added: 0x%x", listener);
			return;
		}
	}
	mImpl.mMouseListeners.push_back (listener);
	mImpl.mLogger.debug(3, "EventManager: Mouse listener added: 0x%x", listener);
}

void stile::EventManager::removeMouseListener	(
		InputHandler* listener
	)
{
	for (unsigned int x=0; x<mImpl.mMouseListeners.size(); x++)
	{
		if (mImpl.mMouseListeners[x] == listener)
		{
			mImpl.mMouseListeners.erase(mImpl.mMouseListeners.begin()+x);
			mImpl.mLogger.debug(3,"EventManager: Mouse listener removed: 0x%x", listener);
			return;
		}
	}
	mImpl.mLogger.warning("EventManager: Cannot remove mouse listener: 0x%x", listener);
}

void stile::EventManager::addGameStateCallback	(
		StateChangeCallback callback
	)
{
	for(unsigned int x=0; x<mImpl.mStateChangeCallbacks.size(); x++)
	{
		if (mImpl.mStateChangeCallbacks[x] == callback)
		{
			mImpl.mLogger.warning("EventManager: State change callback already added: 0x%x", callback);
			return;
		}
	}
	mImpl.mStateChangeCallbacks.push_back(callback);
	mImpl.mLogger.debug(3,"EventManager: State change callback added: 0x%x", callback);
};

void stile::EventManager::removeGameStateCallback	(
		StateChangeCallback callback
	)
{
	for(unsigned int x=0; x<mImpl.mStateChangeCallbacks.size(); x++)
	{
		if (mImpl.mStateChangeCallbacks[x] == callback)
		{
			mImpl.mStateChangeCallbacks.erase(mImpl.mStateChangeCallbacks.begin()+x);
			mImpl.mLogger.debug(3,"EventManager: State change callback removed: 0x%x", callback);
			return;
		}
	}
	mImpl.mLogger.warning("EventManager: Cannot remove state change callback: 0x%x", callback);
};

void stile::EventManager::setGameState	(
		GameState gameState
	)
{
	if (gameState == mImpl.mGameState)
		return;

	mImpl.mGameState = gameState;
	for (unsigned int x=0; x<mImpl.mStateChangeCallbacks.size(); x++)
	{
		(*mImpl.mStateChangeCallbacks[x])(gameState);
	}
};

stile::GameState stile::EventManager::getGameState ()
{
	return mImpl.mGameState;
};

bool stile::EventManager::keyPressed	(
		int key,
		bool special
	)
{
	if (special)
	{
		return mImpl.mSpecialKeyMap[key];
	}
	else
	{
		return mImpl.mNormalKeyMap[key];
	}
}

void stile::EventManager::handleNormalKeyDown	(
		unsigned char key,
		int x,
		int y
	)
{
	unsigned int intKey = (unsigned int)key;
	mImpl.mNormalKeyMap[intKey] = true;
	for (unsigned int i=0; i<mImpl.mKeyboardListeners.size(); i++)
	{
		mImpl.mKeyboardListeners[i]->handleKeyboardEvent (intKey, x, y, true, false);
	}
}

void stile::EventManager::handleNormalKeyUp	(
		unsigned char key,
		int x,
		int y
	)
{
	unsigned int intKey = (unsigned int)key;
	mImpl.mNormalKeyMap[intKey] = false;
	for (unsigned int i=0; i<mImpl.mKeyboardListeners.size(); i++)
	{
		mImpl.mKeyboardListeners[i]->handleKeyboardEvent (intKey, x, y, false, false);
	}
}

void stile::EventManager::handleSpecialKeyDown	(
		int key,
		int x,
		int y
	)
{
	mImpl.mSpecialKeyMap[key] = true;
	for (unsigned int i=0; i<mImpl.mKeyboardListeners.size(); i++)
	{
		mImpl.mKeyboardListeners[i]->handleKeyboardEvent (key, x, y, true, true);
	}
}

void stile::EventManager::handleSpecialKeyUp	(
		int key,
		int x,
		int y
	)
{
	mImpl.mSpecialKeyMap[key] = false;
	for (unsigned int i=0; i<mImpl.mKeyboardListeners.size(); i++)
	{
		mImpl.mKeyboardListeners[i]->handleKeyboardEvent (key, x, y, false, true);
	}
}

void stile::EventManager::handleMouseEvent	(
		int button,
		int state,
		int x,
		int y
	)
{
	mImpl.mButtonStates[button]->secs	= mImpl.mTimer.getSeconds();
	mImpl.mButtonStates[button]->state	= state;
	mImpl.mButtonStates[button]->x	= x;
	mImpl.mButtonStates[button]->y	= y;
	for (unsigned int i=0; i <mImpl.mMouseListeners.size(); i++)
	{
		mImpl.mMouseListeners[i]->handleMouseEvent(button, state, x, y);
	}
	mImpl.mLogger.debug(5,"EventManager: Mouse event (%d, %d, %d, %d)", button, state, x, y);
}

void stile::EventManager::handleMouseMovement	(
		int x,
		int y
	)
{
	for (unsigned int i=0; i <mImpl.mMouseListeners.size(); i++)
	{
		mImpl.mMouseListeners[i]->handleMouseMovement(x, y, mImpl.mButtonStates);
	}
	std::cout << x << y << std::endl;
	mImpl.mLogger.debug(5,"EventManager: Mouse movement (%d, %d)", x, y);
}

void stile::EventManager::shutdown	(
		int exitCode
	)
{
	//TODO add shutdown callbacks
	mImpl.mLogger.debug(3, "NOTE: Shutdown callbacks not yet implemented.\nShutting down...");
	exit(exitCode);
}
