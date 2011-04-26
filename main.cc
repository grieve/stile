/*
	* File:	main.cpp
	* Author: TheGrieve
	*
	* Created on 28 May 2010, 20:08
	*/

/*
	*
	*/

#include <iostream>
#include "../stile/Stile.h"

#include <time.h>

stile::Control*	gControl;
stile::Engine* gEngine;
unsigned int	gNumDriftCalls	=	0;
unsigned int	gNumCalls	=	0;
unsigned int	gLastCall	=	0;
unsigned int	gLastDriftCall	=	0;
unsigned int	gLastMeasure	=	0;
unsigned int	gLastDriftMeasure	=	0;
unsigned int	gTotalDriftCalls	=	0;
unsigned int	gTotalCalls	=	0;
unsigned int	gStartClocks	=	0;

void init
(
	int argc,
	char** argv
)
{
}

void timerTrigger	(
		unsigned int indentifier, 
		const char* strIdentifier,
		unsigned int millis
	)
{
	if(strcmp(strIdentifier, "EngineTest") == 0)
	{
		gControl->log->warning("Starting engine test...");
		stile::World* world = new stile::World("Test World");
		world->add(new stile::Entity());
		world->add(new stile::Entity());
		gEngine = new stile::Engine("",800,600,1,1);
		gEngine->setWorld(world);
	}
	
	if(strcmp(strIdentifier, "EngineFast") == 0)
	{
		gControl->log->warning("Increasing engine rates...");
		gEngine->setFrameRate(60);
		gEngine->setUpdateRate(100);
	}
	
	if(strcmp(strIdentifier, "EngineEnd") == 0)
	{
		gEngine->stop();
		gControl->log->warning("All tests over. Exiting in 5 seconds.");
		gControl->time->addTrigger(timerTrigger, "Exit", 5000);
	}

	if(strcmp(strIdentifier, "Exit") == 0)
	{
		gControl->event->setGameState(stile::GAME_STATE_OVER);
	}
}

void handleGameStateChange	(
		stile::GameState gameState
	)
{
	if(gameState == stile::GAME_STATE_OVER)
	{
		gControl->log->info("Game state has changed to GAME_STATE_OVER. Quitting.");
		gControl->event->shutdown(0);
	}
}

int main	(
		int argc,
		char** argv
	)
{
	gControl = &stile::getControl();
	init(argc, argv);
	gControl->event->addGameStateCallback	(handleGameStateChange);
	gControl->log->warning("\n\
In 10 seconds we will begin the protype Engine, World \
and Entity tests. A world will be created and added to the engine. 2 entities \
will be created an added to the world. This simiulation will then run for ten \
seconds at a very slow render and updare rate. We will then increase these \
rates to something more realistic for 5 seconds.");
	gControl->time->addTrigger(timerTrigger, "EngineTest", 10000);
	gControl->time->addTrigger(timerTrigger, "EngineFast", 20000);
	gControl->time->addTrigger(timerTrigger, "EngineEnd", 25000);
	while(true)
	{
		gControl->time->update();
	}
}
