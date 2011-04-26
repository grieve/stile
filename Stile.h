#ifndef STILE
#define STILE


#include "core/Initiator.h"
#include "core/Timer.h"
#include "core/Logger.h"
#include "core/Configurator.h"
#include "core/EventManager.h"
#include "core/Types.h"
#include "core/Engine.h"
#include "Math.h"

namespace stile
{
	class Engine;
	struct Control;
	Control& getControl();
}

struct stile::Control
{
	stile::List*	list;
	stile::Timer*	time;
	stile::Logger*	log;
	stile::EventManager*	event;
	stile::Configurator*	config;
	stile::Engine*	engine;

	Control ();
};


#endif //STILE
