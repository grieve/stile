/*
&&LICENSE
COPYRIGHT (C)2010 - RYAN GRIEVE
LICENSE&&
*/


#ifndef STILE_OUTPUT_HANDLER
#define STILE_OUTPUT_HANDLER

#include <sstream>

namespace stile
{
	typedef	void(*OutputCallback)(std::ostringstream&);
	class	OutputHandler;
}

class stile::OutputHandler
{
public:
	virtual void write (std::ostringstream& strOutput)	= 0;
};

#endif //STILE_OUTPUT_HANDLER
