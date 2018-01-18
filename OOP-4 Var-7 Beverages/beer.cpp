// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "beer.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/

Beer::Beer(std::string const & _name, int _volumeMl, double _price)
	:Beverage(_name,_volumeMl,_price)
{

}

bool Beer::IsAvailableToSell(Customer &e)
{
	if (getBeverageIngredient() != e.getCustomerAllergicIngridient() && e.getCustomerAge() >= 18 && e.getCustomerMoney() >= getBeveragePrice())
	{
		e.setCustomerMoney(getBeveragePrice());
		return true;
	}
	return false;
	
}

std::string Beer::getBeverageIngredient()
{
	return "Corn";
}
