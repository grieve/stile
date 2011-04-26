#ifndef STILE_INIT
#define STILE_INIT

#include <string>
#include <cstring>
#include "Types.h"

namespace stile
{
	class InitX;
	template <class T> class Init;
}

using namespace std;

class stile::InitX
{
public:
		InitX	();
	virtual	~InitX	();
	virtual void	setIdentifier	(const string& name);
	virtual string	getIdentifier	() const;
	virtual void	create	(stile::List* stileList) = 0;

protected:
	string	mIdentifier;
};

template <class T>
class stile::Init : public stile::InitX
{
public:
		Init	();
	virtual	~Init	();
	virtual	void create	(stile::List* stileList);
};

inline
stile::InitX::InitX ()
	: mIdentifier	("unknown")
{}

inline
stile::InitX::~InitX ()
{}

inline
void stile::InitX::setIdentifier	(
		const string& identifier
	)
{
	mIdentifier = identifier;
}

inline
string stile::InitX::getIdentifier() const
{
	return mIdentifier;
}

#endif //STILE_INIT
