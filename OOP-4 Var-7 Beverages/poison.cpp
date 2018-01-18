// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "poison.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/

Poison::Poison(std::string const & _name, int _volumeMl, double _price)
	: Beverage(_name,_volumeMl,_price)
{

}

std::string Poison::getBeverageIngredient()
{
	return "Technical alcohol";
}

bool Poison::IsAvailableToSell(Customer & e)
{
	return false;
}
