// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _POISON_HPP_
#define _POISON_HPP_

/*****************************************************************************/

#include "beverage.hpp"

/*****************************************************************************/

class Poison
	:	public Beverage
{

public:
	Poison(std::string const & _name, int _volumeMl, double _price);
	std::string getBeverageIngredient() override;
/*-----------------------------------------------------------------*/
	bool IsAvailableToSell(Customer &e) override;
	// TODO


/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _POISON_HPP_
