// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "juice.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/



Juice::Juice(std::string const & _name, int _volumeMl, double _price, std::string const & _mainIngredient)
	:Beverage(_name, _volumeMl,_price)
	,mainIngredient(_mainIngredient)
{
}

std::string Juice::getBeverageIngredient()
{
	return mainIngredient;
}

bool Juice::IsAvailableToSell(Customer &e)
{
	if (getBeverageIngredient() != e.getCustomerAllergicIngridient() && e.getCustomerMoney() >= getBeveragePrice())
	{
		e.setCustomerMoney(getBeveragePrice());
		return true;
	}
	return false;

}