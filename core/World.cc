
#include "World.h"

stile::World::World	()
	:mControl(stile::getControl())
{
	strcpy(mIdentifier, "Unknown World");
	mEnabled = true;
	init();
};

stile::World::World	(
		char* id,
		bool enable
	)
	:mControl(stile::getControl())
{
	strcpy(mIdentifier, id);
	mEnabled = enable;
	init();
}

stile::World::~World	()
{
}

void	stile::World::init	()
{

}

void	stile::World::render	()
{
	for(int x=0; x< mChildren.size(); x++)
	{
		mChildren[x]->render();
	} 
}

void	stile::World::update	(unsigned int elapsed)
{
	for(int x=0; x< mChildren.size(); x++)
	{
		mChildren[x]->update(elapsed);
	} 
}

bool	stile::World::add	(
			stile::Entity* child
		)
{
	for(int x=0; x< mChildren.size(); x++)
	{
		if(mChildren[x] == child)
		{
			mControl.log->warning("Child already exists in this world. (%X)", child);
			return false;
		}
	}
	mChildren.push_back(child);
	return true;
}

bool	stile::World::remove	(
			stile::Entity* child
		)
{
	for(int x=0; x< mChildren.size(); x++)
	{
		if(mChildren[x] == child)
		{
			mChildren.erase(mChildren.begin()+x);
			return false;
		}
	}
	mControl.log->warning("Child does not exist in this world. (%X)", child);
	return true;
}
