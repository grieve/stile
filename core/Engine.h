#ifndef STILE_ENGINE
#define STILE_ENGINE

#include <SFML/Window.hpp>
#include "World.h"
#include "TimerHandler.h"

namespace stile
{
	class   Engine;
	class   World;
	class   Entity;
	struct	Control;
}

class stile::Engine : TimerHandler
{
public:
	stile::Control&	mControl;
	stile::World*	  mWorld;
	sf::Window*	    mWindow;
	unsigned int	  mFrameRate;
	unsigned int	  mUpdateRate;
	bool	          mPaused;
	bool	          mStopped;
	void	          render        ();
	void	          update	      (unsigned int   elapsed);
	void	          setWorld	    (stile::World*  world);
	stile::World*	  getWorld	    ();
	void	          setFrameRate	(unsigned int frameRate);
	void	          setUpdateRate	(unsigned int updateRate);
	void	          stop	        ();
	void	          pause	        ();
	void	          resume	      ();
	void	          trigger	      (
                                  unsigned int  identifier,
                                  const char*   strIdentifier,
                                  unsigned int  millis
                                );
                  Engine	      (
                                  const char*   title,
                                  unsigned int  width       = 640,
                                  unsigned int  height      = 480,
                                  unsigned int  updateRate  = 100,
                                  unsigned int  frameRate   = 60
                                );
                  ~Engine       ();
};

#endif //STILE_ENGINE
