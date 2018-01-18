// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/
#include "customer.hpp"
#include "beverage.hpp"
#include "juice.hpp"
#include "beer.hpp"
#include "poison.hpp"
#include <string>
#include <unordered_map>
#include<memory>
/*****************************************************************************/
class Customer;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller ();

/*-----------------------------------------------------------------*/

	void createCustomer ( 
			std::string const & _name
		,	int _age
		,	double _money
	);

	void makeCustomerAllergicTo (
			std::string const & _name
		,	std::string const & _ingredient 
	);
	
	double getCustomerBalance ( std::string const & _customerName ) const;

	int getCustomerAge ( std::string const & _customerName ) const;

	std::string getCustomerAllergicIngredient ( std::string const & _customerName ) const;

/*-----------------------------------------------------------------*/
	Customer* findCustomer(std::string const _name) const;
	Customer & resolveCustomer(std::string const _name) const;

	Beverage * findBeverage(std::string const _beverage) const;
	Beverage & resolveBeverage(std::string const _beverage) const;

	// void duplicateNameChecker(std::string const _name) const;

	void createJuice (
			std::string const & _name
		,	int _volumeMl
		,	double _price
		,	std::string const & _mainIngredient
	);

	void createBeer (
			std::string const & _name
		,	int _volumeMl
		,	double _price
	);

	void createPoison (
			std::string const & _name
		,	int _volumeMl
		,	double _price
	);

	std::string getBeverageMainIngredient ( std::string const & _beverageName ) const;

	int getBeverageVolumeMl( std::string const & _beverageName ) const;

	double getBeveragePrice( std::string const & _beverageName ) const;

/*-----------------------------------------------------------------*/

	bool trySelling (
			std::string const & _customerName
		,	std::string const & _beverageName
	);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::unordered_map<std::string,std::unique_ptr<Customer> > m_customers;
	std::unordered_map<std::string, std::unique_ptr<Beverage> > m_beverages;

/*-----------------------------------------------------------------*/


};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
