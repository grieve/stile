/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/

#include "Timer.h"
#include <iostream>


struct stile::Timer::TimerImpl
{
public:
	struct TriggerObject
	{
	public:
		unsigned int	milliseconds;
		unsigned int	clocks;
		unsigned int	identifier;
		char	strIdentifier[128];
		bool	repeat;
		bool	allowDrift;
		TriggerCallback	triggerCallback;
		stile::TimerHandler*	handler;
	};

	typedef std::multimap<unsigned int, TriggerObject*> TriggerMap;

	Timer&	mParent;
	unsigned long		mClocks;
	float		mSeconds;
	float		mMillis;
	TriggerMap		mTriggerMap;


	TimerImpl	(
			Timer* parent
		)
		: mParent (*parent)
	{};
	~TimerImpl	()
	{};

	void	addTrigger	(TriggerCallback callback, const char* identifier, unsigned int milliseconds, bool repeat, bool allowDrift);
	void	addTrigger	(TriggerCallback callback, unsigned int identifier, unsigned int milliseconds, bool repeat, bool allowDrift);
	void	addTrigger	(stile::TimerHandler* handler, const char* identifier, unsigned int milliseconds, bool repeat, bool allowDrift);
	void	addTrigger	(stile::TimerHandler* handler, unsigned int identifier, unsigned int milliseconds, bool repeat, bool allowDrift);
	void	removeTrigger	(const char* identifier);
	void	removeTrigger	(unsigned int identifier);
	void	removeTrigger	(stile::TimerHandler* handler);
	void	update	();
	void	updateTriggers	();
};

void stile::Timer::TimerImpl::update()
{
	mSeconds = (float)clock() / CLOCKS_PER_SEC;
	updateTriggers();
}

void stile::Timer::TimerImpl::updateTriggers ()
{
	if (mTriggerMap.size() == 0)
	{
		return;
	}
	while (mTriggerMap.begin()->first < clock())
	{
		TriggerObject* trig = mTriggerMap.begin()->second;
		if (trig->milliseconds > 0)
		{
			if (trig->handler)
			{
				trig->handler->trigger(trig->identifier, trig->strIdentifier, trig->milliseconds);
			}
			else
			{
				trig->triggerCallback(trig->identifier, trig->strIdentifier, trig->milliseconds);
			}
			if (trig->repeat)
			{
				unsigned int newClocks;
				if (!trig->allowDrift)
				{
					newClocks = (clock()+trig->clocks)-(clock()-mTriggerMap.begin()->first);
				}
				else
				{
					newClocks = clock()+trig->clocks;
				}
				mTriggerMap.insert(TriggerMap::value_type(newClocks,trig));
			}
		}
		mTriggerMap.erase(mTriggerMap.begin());
	}
}

void stile::Timer::TimerImpl::addTrigger	(
		TriggerCallback callback,
		const char* identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	assert(identifier[0] != '\0');
	TriggerObject* trig = new TriggerObject;
	strcpy(trig->strIdentifier,identifier);
	trig->milliseconds = milliseconds;
	trig->clocks = (unsigned int)floor((CLOCKS_PER_SEC/1000)*milliseconds);
	trig->repeat = repeat;
	trig->allowDrift = allowDrift;
	trig->triggerCallback = callback;
	trig->handler = NULL;
	mTriggerMap.insert (TriggerMap::value_type(clock()+trig->clocks,trig));
}

void stile::Timer::TimerImpl::addTrigger	(
		TriggerCallback callback,
		unsigned int identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	//TODO Reject triggers with the same id

	assert (identifier != 0);
	TriggerObject* trig = new TriggerObject;
	trig->identifier = identifier;
	trig->strIdentifier[0] = '\0';
	trig->milliseconds = milliseconds;
	trig->clocks = (unsigned int)floor((CLOCKS_PER_SEC/1000)*milliseconds);
	trig->repeat = repeat;
	trig->allowDrift	= allowDrift;
	trig->triggerCallback = callback;
	trig->handler = NULL;
	mTriggerMap.insert (TriggerMap::value_type(clock()+trig->clocks,trig));
}

void stile::Timer::TimerImpl::addTrigger	(
		stile::TimerHandler* handler,
		const char* identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	assert(identifier[0] != '\0');
	TriggerObject* trig = new TriggerObject;
	strcpy(trig->strIdentifier,identifier);
	trig->milliseconds = milliseconds;
	trig->clocks = (unsigned int)floor((CLOCKS_PER_SEC/1000)*milliseconds);
	trig->repeat = repeat;
	trig->allowDrift = allowDrift;
	trig->triggerCallback = NULL;
	trig->handler = handler;
	mTriggerMap.insert (TriggerMap::value_type(clock()+trig->clocks,trig));
}

void stile::Timer::TimerImpl::addTrigger	(
		stile::TimerHandler* handler,
		unsigned int identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	//TODO Reject triggers with the same id

	assert (identifier != 0);
	TriggerObject* trig = new TriggerObject;
	trig->identifier = identifier;
	trig->strIdentifier[0] = '\0';
	trig->milliseconds = milliseconds;
	trig->clocks = (unsigned int)floor((CLOCKS_PER_SEC/1000)*milliseconds);
	trig->repeat = repeat;
	trig->allowDrift	= allowDrift;
	trig->triggerCallback = NULL;
	trig->handler = handler;
	mTriggerMap.insert (TriggerMap::value_type(clock()+trig->clocks,trig));
}

void stile::Timer::TimerImpl::removeTrigger	(
		const char* identifier
	)
{
	TriggerMap::iterator i = mTriggerMap.begin();
	while (i != mTriggerMap.end())
	{
		if (strcmp(i->second->strIdentifier, identifier)==0)
		{
			i->second->milliseconds = 0;
		}
		i++;
	}
}

void stile::Timer::TimerImpl::removeTrigger	(
		unsigned int identifier
	)
{
	TriggerMap::iterator i = mTriggerMap.begin();
	while (i != mTriggerMap.end())
	{
		if (i->second->identifier == identifier)
		{
			i->second->milliseconds = 0;
		}
		i++;
	}
}

void stile::Timer::TimerImpl::removeTrigger	(
		stile::TimerHandler* handler
	)
{
	TriggerMap::iterator i = mTriggerMap.begin();
	while (i != mTriggerMap.end())
	{
		if (i->second->handler == handler)
		{
			i->second->milliseconds = 0;
		}
		i++;
	}
}

stile::Timer::Timer	(
		const char* name
	)
	: mImpl(*new stile::Timer::TimerImpl(this))
{
}

float stile::Timer::getSeconds()
{
	return mImpl.mSeconds;
}

void stile::Timer::addTrigger	(
		TriggerCallback callback,
		const char* identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	mImpl.addTrigger(callback, identifier, milliseconds, repeat, allowDrift);
}

void stile::Timer::addTrigger	(
		TriggerCallback callback,
		unsigned int identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	mImpl.addTrigger(callback, identifier, milliseconds, repeat, allowDrift);
}

void stile::Timer::addTrigger	(
		stile::TimerHandler* handler,
		const char* identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	mImpl.addTrigger(handler, identifier, milliseconds, repeat, allowDrift);
}

void stile::Timer::addTrigger	(
		stile::TimerHandler* handler,
		unsigned int identifier,
		unsigned int milliseconds,
		bool repeat,
		bool allowDrift
	)
{
	mImpl.addTrigger(handler, identifier, milliseconds, repeat, allowDrift);
}

void stile::Timer::removeTrigger	(
		unsigned int identifier
	)
{
	mImpl.removeTrigger(identifier);
}

void stile::Timer::removeTrigger	(
		const char* identifier
	)
{
	mImpl.removeTrigger(identifier);
}

void stile::Timer::removeTrigger	(
		stile::TimerHandler* handler
	)
{
	mImpl.removeTrigger(handler);
}

void stile::Timer::update()
{
	mImpl.update();
}
