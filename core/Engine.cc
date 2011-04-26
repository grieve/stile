
#include "Engine.h"

stile::Engine::Engine	(
		const char*	title,
		unsigned int	width,
		unsigned int	height,
		unsigned int	updateRate,
		unsigned int	frameRate 
	)
	:mControl(stile::getControl())
{
	mWindow = new sf::Window(sf::VideoMode(width, height, 32), title);
	setUpdateRate(updateRate);
	setFrameRate(frameRate);
	mPaused = false;
	mStopped = false;
};

stile::Engine::~Engine	()
{
}
void	stile::Engine::render	()
{
	if(mWorld && !mStopped)
	{
		mWorld->render();
		mWindow->Display();	
	}
}

void	stile::Engine::update	(unsigned int elapsed)
{
	sf::Event event;
	while(mWindow.GetEvent(event))
	{
		
	}
	if(mWorld && !mPaused)
		mWorld->update(elapsed);
}

void stile::Engine::setWorld	(
		stile::World* world
	)
{
	mWorld = world;
}

stile::World* stile::Engine::getWorld	()
{
	return mWorld;
}

void stile::Engine::stop	()
{
	mStopped = true;
	mPaused = true;
}

void stile::Engine::pause	()
{
	mPaused = true;
}

void stile::Engine::resume	()
{
	mStopped = false;
	mPaused = false;
}

void stile::Engine::setFrameRate	(
		unsigned int frameRate
	)
{
	mFrameRate = frameRate;
	mControl.time->removeTrigger(2);
	mControl.time->addTrigger(this, 2, 1000/mFrameRate, true);
}

void stile::Engine::setUpdateRate	(
		unsigned int updateRate
	)
{
	mUpdateRate = updateRate;
	mControl.time->removeTrigger(1);
	mControl.time->addTrigger(this, 1, 1000/mUpdateRate, true);
}

void stile::Engine::trigger	(
		unsigned int	id,
		const char*	strId,
		unsigned int	millis
	)
{
	switch(id)
	{
		case 1:
			update(millis);
			break;
		case 2:
			render();
			break;
	}
}
