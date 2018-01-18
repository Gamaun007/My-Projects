// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BEER_HPP_
#define _BEER_HPP_

/*****************************************************************************/

#include "beverage.hpp"

/*****************************************************************************/


class Beer
	:	public Beverage
{
public:
	Beer(std::string const & _name, int _volumeMl, double _price);
/*-----------------------------------------------------------------*/
	bool IsAvailableToSell(Customer &e) override;
	std::string getBeverageIngredient() override;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _BEER_HPP_
