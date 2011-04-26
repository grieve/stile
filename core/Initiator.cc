#include <iostream>
#include <map>
#include "Initiator.h"

using std::multimap;

namespace stile
{
	typedef multimap<unsigned int, InitX*>	InitList;
}

class stile::InitiatorImpl
{
public:
	InitiatorImpl	(){}
	~InitiatorImpl	(){}
	InitList	stileInitList;
};


stile::Initiator::Initiator ()
{
	mImpl = new InitiatorImpl();
}

stile::Initiator::~Initiator ()
{
	if (mImpl) delete mImpl;
	mImpl = 0;
}

void stile::Initiator::addInit	(
		stile::InitX* stileInit,
		int weight
	)
{
	mImpl->stileInitList.insert(InitList::value_type(weight,stileInit));
}

void stile::Initiator::initialize	(
		stile::List* stileList
	)
{
	for (InitList::iterator i = mImpl->stileInitList.begin(); i != mImpl->stileInitList.end(); ++i)
	{
		InitX* bone = i->second;
		bone->create (stileList);
	}
}

stile::Initiator& stile::getInitiator()
{
	static stile::Initiator stileInit;
	return stileInit;
}
