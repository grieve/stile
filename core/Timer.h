/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#ifndef STILE_TIMER
#define STILE_TIMER

#include <time.h>
#include <math.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <assert.h>
#include "TimerHandler.h"

namespace stile
{
	class Timer;
}

class stile::Timer
{
	typedef void (*TriggerCallback)	(
			unsigned int,
			const char*,
			unsigned int
		);

public:
		Timer	(const char* name);
		~Timer	();
	float	getSeconds	();
	void	addTrigger	(
				TriggerCallback	callback,
				const char*	identifier,
				unsigned int	milliseconds,
				bool	repeat = false,
				bool	allowDrift = false
			);
	void	addTrigger	(
				TriggerCallback	callback,
				unsigned int	identifier,
				unsigned int	milliseconds,
				bool	repeat = false,
				bool	allowDrift = false
			);
	void	addTrigger	(
				stile::TimerHandler*	handler,
				const char*	identifier,
				unsigned int	milliseconds,
				bool	repeat = false,
				bool	allowDrift = false
			);
	void	addTrigger	(
				stile::TimerHandler*	handler,
				unsigned int	identifier,
				unsigned int	milliseconds,
				bool	repeat = false,
				bool	allowDrift = false
			);
	void	removeTrigger	(const char* identifier);
	void	removeTrigger	(unsigned int identifier);
	void	removeTrigger	(stile::TimerHandler* handler);
	void	update	();

private:
	struct	TimerImpl;
	TimerImpl&	mImpl;

	Timer	(const Timer& copy);
	Timer operator=	(Timer& rhs);

};

#endif // STILE_TIMER
