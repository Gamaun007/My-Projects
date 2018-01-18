// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/

Customer*  Controller::findCustomer(std::string const _name) const
{
	auto it = m_customers.find(_name);
	return (it == m_customers.end()) ? nullptr : it->second.get();
}

Customer & Controller::resolveCustomer(std::string const _name) const
{
	Customer * pCustomer = findCustomer(_name);
	if (pCustomer)
		return *pCustomer;

	throw std::logic_error(Messages::CustomerNameUnknown);
}

Beverage * Controller::findBeverage(std::string const _beverage) const
{
	auto it = m_beverages.find(_beverage);
	return (it == m_beverages.end()) ? nullptr : it->second.get();
}

Beverage & Controller::resolveBeverage(std::string const _beverage) const
{
	Beverage * pBeverage = findBeverage(_beverage);
	if (pBeverage)
		return *pBeverage;

	throw std::logic_error(Messages::BeverageNameUnknown);
}


/*void Controller::duplicateNameChecker(std::string const _name) const
{
	Customer * pCustomer = findCustomer(_name);
	if (pCustomer)
		throw std::logic_error(Messages::CustomerNameNotUnique);
}*/

void Controller::createJuice(std::string const & _name, int _volumeMl, double _price, std::string const & _mainIngredient)
{
	if (findBeverage(_name))
		throw std::logic_error(Messages::BeverageNameNotUnique);
	if (_name == "")
		throw std::logic_error(Messages::EmptyBeverageName);
	if (_volumeMl < 0)
		throw std::logic_error(Messages::NonPositiveAmount);
	if (_price < 0)
		throw std::logic_error(Messages::NonPositivePrice);
	if (_mainIngredient == "")
		throw std::logic_error(Messages::EmptyIngredientName);
	m_beverages[_name] =
		std::make_unique<Juice>(_name, _volumeMl, _price, _mainIngredient);
}

void Controller::createBeer(std::string const & _name, int _volumeMl, double _price)
{
	if (findBeverage(_name))
		throw std::logic_error(Messages::BeverageNameNotUnique);
	if (_name == "")
		throw std::logic_error(Messages::EmptyBeverageName);
	if (_volumeMl < 0)
		throw std::logic_error(Messages::NonPositiveAmount);
	if (_price < 0)
		throw std::logic_error(Messages::NonPositivePrice);
	m_beverages[_name] =
		std::make_unique<Beer>(_name, _volumeMl, _price);
}

void Controller::createPoison(std::string const & _name, int _volumeMl, double _price)
{
	if (findBeverage(_name))
		throw std::logic_error(Messages::BeverageNameNotUnique);
	if (_name == "")
		throw std::logic_error(Messages::EmptyBeverageName);
	if (_volumeMl < 0)
		throw std::logic_error(Messages::NonPositiveAmount);
	if (_price < 0)
		throw std::logic_error(Messages::NonPositivePrice);
	m_beverages[_name] =
		std::make_unique<Poison>(_name, _volumeMl, _price);

}

std::string Controller::getBeverageMainIngredient(std::string const & _beverageName) const
{
	return resolveBeverage(_beverageName).getBeverageIngredient();
}

int Controller::getBeverageVolumeMl(std::string const & _beverageName) const
{
	return resolveBeverage(_beverageName).getBeverageAmount();
}

double Controller::getBeveragePrice(std::string const & _beverageName) const
{
	return resolveBeverage(_beverageName).getBeveragePrice();
}

bool Controller::trySelling(std::string const & _customerName, std::string const & _beverageName)
{
	 return resolveBeverage(_beverageName).IsAvailableToSell(resolveCustomer(_customerName));
}

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::createCustomer(std::string const & _name, int _age, double _money)
	
{
	if (_name == "")
		throw std::logic_error(Messages::EmptyCustomerName);
	if (findCustomer(_name))
		throw std::logic_error(Messages::CustomerNameNotUnique);
	if (_age < 0)
		throw std::logic_error(Messages::NegativeAge);
	if(_money <0)
		throw std::logic_error(Messages::NegativeBalance);
	m_customers[_name] =
		std::make_unique<Customer>(_name, _age, _money);
}

void Controller::makeCustomerAllergicTo(std::string const & _name, std::string const & _ingredient)
{
	
	if (_ingredient == "")
		throw std::logic_error(Messages::EmptyIngredientName);
	resolveCustomer(_name).setCustomerAllergicIngridient(_ingredient);

}

double Controller::getCustomerBalance(std::string const & _customerName) const
{
	return resolveCustomer(_customerName).getCustomerMoney();
}

int Controller::getCustomerAge(std::string const & _customerName) const
{
	return resolveCustomer(_customerName).getCustomerAge();
}

std::string Controller::getCustomerAllergicIngredient(std::string const & _customerName) const
{
	return	resolveCustomer(_customerName).getCustomerAllergicIngridient();
}
