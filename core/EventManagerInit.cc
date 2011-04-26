#include "Initiator.h"
#include "Logger.h"
#include "Timer.h"
#include "EventManager.h"

namespace stile
{

template <>
Init<EventManager>::Init ()
{
	setIdentifier	("EventManager");
	getInitiator().addInit	(this, 13);
}

template <>
Init<EventManager>::~Init ()
{
}

template <>
void Init<EventManager>::create	(
		List* stileList
	)
{
	Timer*	stileTimer	=	getBone<Timer>	(stileList, "Timer");
	Logger*	stileLogger	=	getBone<Logger>	(stileList, "Logger");
	Configurator*	stileConfig	=	getBone<Configurator>	(stileList, "Configurator");

	EventManager* stileEventManager = new EventManager(stileTimer, stileLogger, stileConfig);
	stileList->insert(List::value_type(getIdentifier(),stileEventManager));
}

Init<EventManager> stileEventManagerInit;

}
