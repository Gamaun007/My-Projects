// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BEVERAGE_HPP_
#define _BEVERAGE_HPP_
#include "customer.hpp"
#include <string>
/*****************************************************************************/
class Customer;

class Beverage
{
/*-----------------------------------------------------------------*/

public:
	Beverage(const Beverage &) = delete;
	Beverage & operator = (const Beverage &) = delete;

	virtual ~Beverage()= default;
	virtual std::string getBeverageIngredient();
	virtual bool IsAvailableToSell(Customer &e) = 0;
	std::string const getBeverageName() const;
	int getBeverageAmount() const;
	double getBeveragePrice() const;
protected:
	Beverage(std::string const & _name, int _volumeMl, double _price);

private:
	std::string beverageName;
	int beverageAmount;
	double beveragePrice;

/*-----------------------------------------------------------------*/
};
inline std::string Beverage::getBeverageIngredient()
{
	return "";
}
inline
std::string const Beverage::getBeverageName() const
{
	return beverageName;
}

inline
int Beverage::getBeverageAmount() const
{
	return beverageAmount;
}

inline
double Beverage::getBeveragePrice() const
{
	return beveragePrice;
}
/*****************************************************************************/

#endif // _BEVERAGE_HPP_
