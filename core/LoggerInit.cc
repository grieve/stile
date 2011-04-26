#include "Initiator.h"
#include "Logger.h"
#include "Timer.h"

namespace stile
{

template <>
Init<Logger>::Init ()
{
	setIdentifier	("Logger");
	getInitiator().addInit	(this, 11);
}

template <>
Init<Logger>::~Init ()
{
}

template <>
void Init<Logger>::create	(
		List* stileList
	)
{
	Timer* stileTimer = getBone<Timer>(stileList, "Timer");
	Logger* stileLogger = new Logger(getIdentifier().c_str(), stileTimer);
	stileLogger->enableStdOut(true);
	stileList->insert(List::value_type(getIdentifier(),stileLogger));
}

Init<Logger> stileLoggerInit;

}

