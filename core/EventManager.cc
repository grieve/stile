/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/

#include "EventManager.h"

struct stile::EventManager::EventManagerImpl
{
public:
	EventManager&	                    mParent;
	Timer&	                          mTimer;
	Logger&	                          mLogger;
	Configurator&	                    mConfig;
	GameState	                        mGameState;
	std::vector<StateChangeCallback>	mStateChangeCallbacks;
	std::vector<InputHandler*>	      mKeyboardListeners;
	std::vector<InputHandler*>	      mMouseListeners;
	MouseEvent*	                      mButtonStates	[10];
	sf::Window*                       mWindow;

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
		int key
	)
{
}

void stile::EventManager::handleKeyEvent (
                                                unsigned int key,
                                                int x,
                                                int y,
                                                bool state,
                                                bool alt,
                                                bool ctrl,
                                                bool shift
                                              )
{
	unsigned int intKey = (unsigned int)key;
	for (unsigned int i=0; i<mImpl.mKeyboardListeners.size(); i++)
	{
		mImpl.mKeyboardListeners[i]->handleKeyboardEvent (intKey, x, y, state, alt, ctrl, shift);
	}
}

void stile::EventManager::handleMouseEvent	(
		MouseEventType event,
		int state,
		int x,
		int y,
		bool alt,
		bool ctrl,
		bool shift
	)
{
	mImpl.mButtonStates[event]->secs	= mImpl.mTimer.getSeconds();
	mImpl.mButtonStates[event]->state	= state;
	mImpl.mButtonStates[event]->x	= x;
	mImpl.mButtonStates[event]->y	= y;
	for (unsigned int i=0; i <mImpl.mMouseListeners.size(); i++)
	{
		mImpl.mMouseListeners[i]->handleMouseEvent(event, state, x, y, alt, ctrl, shift);
	}
	mImpl.mLogger.debug(5,"EventManager: Mouse event (%d, %d, %d, %d)", event, state, x, y);
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

void stile::EventManager::processWindowEvents (sf::Window* window)
{
  const sf::Input& input = window->GetInput();
  sf::Event event;
  while(window->GetEvent(event))
  {
    switch(event.Type)
    {
      case sf::Event::Closed :
        setGameState(stile::GAME_STATE_EXIT);
        shutdown(0);
        break;
      case sf::Event::MouseLeft :
        handleMouseEvent(
                          stile::MOUSE_FOCUS,
                          false,
                          input.GetMouseX(),
                          input.GetMouseY(),
                          (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                          (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                          (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                        );
        break;
      case sf::Event::MouseEntered :
        handleMouseEvent(
                          stile::MOUSE_FOCUS,
                          true,
                          input.GetMouseX(),
                          input.GetMouseY(),
                          (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                          (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                          (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                        );
        break;
      case sf::Event::MouseButtonPressed :
        handleMouseEvent(
                          (stile::MouseEventType)event.MouseButton.Button,
                          true,
                          input.GetMouseX(),
                          input.GetMouseY(),
                          (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                          (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                          (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                        );
        break;
      case sf::Event::MouseButtonReleased :
        handleMouseEvent(
                          (stile::MouseEventType)event.MouseButton.Button,
                          false,
                          input.GetMouseX(),
                          input.GetMouseY(),
                          (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                          (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                          (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                        );
        break;
      case sf::Event::KeyPressed :
        handleKeyEvent(
                        event.Key.Code,
                        input.GetMouseX(),
                        input.GetMouseY(),
                        true,
                        (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                        (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                        (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                      );
        break;
      case sf::Event::KeyReleased :
        handleKeyEvent(
                        event.Key.Code,
                        input.GetMouseX(),
                        input.GetMouseY(),
                        false,
                        (input.IsKeyDown(sf::Key::LAlt)     || input.IsKeyDown(sf::Key::RAlt)),
                        (input.IsKeyDown(sf::Key::LShift)   || input.IsKeyDown(sf::Key::RShift)),
                        (input.IsKeyDown(sf::Key::LControl) || input.IsKeyDown(sf::Key::RControl))
                      );
        break;
      case sf::Event::JoyButtonPressed :
        // handle joystick buttons
        break;
      case sf::Event::JoyButtonReleased :
        // handle joystick release
        break;
      case sf::Event::JoyMoved :
        // handle joy movement
        break;
    }
  }
}
