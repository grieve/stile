#ifndef STILE_TIMER_HANDLER
#define STILE_TIMER_HANDLER

namespace stile
{
	class TimerHandler;
}

class stile::TimerHandler
{
public:
	virtual void	trigger	(
				unsigned int identifier,
				const char* strIdentifier,
				unsigned int millis
			) = 0;
};

#endif //STILE_TIMER_HANDLER
