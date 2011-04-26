#ifndef STILE_WORLD
#define STILE_WORLD

#include "Entity.h"

namespace stile
{
	class 	World;
	class	Entity;
	struct	Control;
}

class stile::World
{
public:
	stile::Control&	mControl;
	bool	mEnabled;
	char	mIdentifier[128];
	vector<stile::Entity*>	mChildren;

		World	();
		World	(char* id, bool enable=true);
	virtual	~World	();
	virtual void	init	();
	virtual void	render	();
	virtual void	update	(unsigned int elapsed);
	virtual bool	add	(stile::Entity* child);
	virtual bool	remove	(stile::Entity* child);
};



#endif //STILE_WORLD
