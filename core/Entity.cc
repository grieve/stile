
#include "Entity.h"

stile::Entity::Entity	()
	:mControl(stile::getControl())
{
	strcpy(mIdentifier, "Unknown Entity");
	mEnabled = true;
	init();
};

/*stile::Entity::Entity	(
		char* id,
		bool enable
	)
	:mControl(stile::getControl())
{
	strcpy(mIdentifier, id);
	mEnabled = enable;
	init();
}*/

stile::Entity::~Entity	()
{
}


void	stile::Entity::init	()
{

}

void	stile::Entity::render	()
{
}

void	stile::Entity::update	(unsigned int elapsed)
{
}
