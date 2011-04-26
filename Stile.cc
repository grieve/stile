#include "Stile.h"

stile::Control::Control()
{
	list	= new stile::List;
	stile::Initiator& init 	=	getInitiator();

	init.initialize (list);

	time	= (stile::Timer*)list->find	("Timer")->second;
	log	= (stile::Logger*)list->find	("Logger")->second;
	config	= (stile::Configurator*)list->find	("Configurator")->second;
	event	= (stile::EventManager*)list->find	("EventManager")->second;
}

stile::Control& stile::getControl()
{
	static Control control;
	return control;
}
