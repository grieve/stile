#ifndef STILE_CONFIGURATOR
#define STILE_CONFIGURATOR

#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include "Logger.h"
#include "Timer.h"
#include "ConfigListener.h"

namespace stile
{
	class Configurator;
}

using namespace std;

class stile::Configurator
{
public:
	Configurator	(
			const char* filename,
			Timer* timer,
			Logger* logger
		);

		~Configurator	();

	bool	getBooleanOption	(const char* option);
	void	setBooleanOption	(const char* option, bool value);
	string&	getStringOption	(const char* option);
	void	setStringOption	(const char* option, string& value);
	int	getIntegerOption	(const char* option);
	void	setIntegerOption	(const char* option, int value);
	float	getFloatOption	(const char* option);
	void	setFloatOption	(const char* option, float value);
	void	loadConfiguration	();
	void	saveConfiguration	();
	bool	fail	();
//	void	addConfigListener	(StileConfigListener* listener);
//	void	removeConfigListener	(StileConfigListener* listener);

//might be better to implement a WIMP style central communication module rather than doing vectors of listeners all the time.

private:
	struct	ConfiguratorImpl;
	ConfiguratorImpl&	mImpl;

	Configurator	(Configurator& copy);
	Configurator operator=	(Configurator& rhs);
};


#endif //STILE_CONFIGURATOR
