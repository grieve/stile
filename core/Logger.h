/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#ifndef STILE_LOGGER
#define STILE_LOGGER

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <map>
#include <math.h>
#include <string>
#include <cstring>
#include <vector>
#include "Types.h"
#include "Timer.h"
#include "OutputHandler.h"

namespace stile
{
	class Logger;
}

class stile::Logger
{
public:
		Logger	(const char* name, Timer* timer);
		~Logger	();
	void	setDebugLevel	(unsigned int level);
	void	enableStdOut	(bool enable);
	void	addOutputListener	(OutputHandler* listener);
	void	removeOutputListener	(OutputHandler* listener);
	void	addOutputCallback	(OutputCallback cb);
	void	removeOutputCallback	(OutputCallback cb);
	void	error	(const char* format, ...);
	void	warning	(const char* format, ...);
	void	info	(const char* format, ...);
	void	debug	(unsigned int level, const char* format, ...);

private:

	struct	LoggerImpl;
	LoggerImpl&	mImpl;

	Logger	(const Logger& copy);
	Logger operator=	(Logger& rhs);
};

#endif //STILE_LOGGER
