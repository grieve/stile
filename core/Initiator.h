#ifndef STILE_INITIATOR
#define STILE_INITIATOR

#include <string>
#include "Types.h"
#include "Init.h"
#include "Configurator.h"

namespace stile
{
	class	Initiator;
	class	InitiatorImpl;
	Initiator&	getInitiator();
}


template<class T>
T* getBone	(
		stile::List* list,
		const char* boneName
	)
{
	T* tPtr = (T*)list->find(boneName)->second;
	if (!tPtr)
	{
		std::cout
			<< "ERROR: "
			<< boneName
			<< " not found! Bail!"
			<< std::endl;
		exit(1);
	}
	else
	{
		return tPtr;
	}
};

class stile::Initiator
{
protected:
	friend Initiator& initiator();

public:
	Initiator	();
	virtual ~Initiator ();

		void	addInit	(InitX* init, int weight);
		void	initialize	(List* list);

private:
	InitiatorImpl*	mImpl;
};

#endif // STILE_INITIATOR
