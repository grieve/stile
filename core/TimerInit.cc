#include "Initiator.h"
#include "Timer.h"

namespace stile
{

template <>
Init<Timer>::Init ()
{
	setIdentifier	("Timer");
	getInitiator().addInit	(this, 10);
}

template <>
Init<Timer>::~Init ()
{
}

template <>
void Init<Timer>::create	(
		List* stileList
	)
{
	Timer* stileTimer = new Timer(getIdentifier().c_str());
	stileList->insert(List::value_type(getIdentifier(),stileTimer));
}

Init<Timer> stileTimerInit;

}

