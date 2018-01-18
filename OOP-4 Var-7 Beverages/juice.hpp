// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _JUICE_HPP_
#define _JUICE_HPP_

/*****************************************************************************/

#include "beverage.hpp"

/*****************************************************************************/

class Juice
	:	public Beverage
{

/*-----------------------------------------------------------------*/
public:
	Juice(std::string const & _name, int _volumeMl, double _price, std::string const & _mainIngredient);
	std::string getBeverageIngredient() override;
	bool IsAvailableToSell(Customer &e) override;

private:
	std::string mainIngredient;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _JUICE_HPP_
