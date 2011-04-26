#ifndef STILE_ENTITY
#define STILE_ENTITY

#include "../../stile/Stile.h"

namespace stile
{
	class	Entity;
	struct	Control;
}

class stile::Entity
{
public:
	stile::Control&	mControl;
	bool	mEnabled;
	char	mIdentifier[128];

			Entity	();
	virtual		~Entity	();
	virtual	void	init	();
	virtual	void	render	();
	virtual	void	update	(unsigned int elapsed);
};

#endif //STILE_ENTITY
