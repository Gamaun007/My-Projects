// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#include <string>
#ifndef _CUSTOMER_HPP_
#define _CUSTOMER_HPP_

/*****************************************************************************/

class Beverage;

class Customer
{


/*-----------------------------------------------------------------*/

public:
	Customer(std::string const & _name,	int _age,	double _money);
	std::string const & getCustomerName() const; 
	std::string const & getCustomerAllergicIngridient() const;
	int  getCustomerAge() const;
	double  getCustomerMoney() const;
	void setCustomerAllergicIngridient(std::string _alergicname);
	void setCustomerMoney(double _money);
	//bool TryToSell(Beverage &e) const;

private:
	std::string customerName;
	std::string customerAllergicIngridient;
	int customerAge;
	double customerMoney;

/*-----------------------------------------------------------------*/

};

inline
std::string const & Customer::getCustomerName() const
{
	return customerName;
}

inline 
std::string const & Customer::getCustomerAllergicIngridient() const
{
	return customerAllergicIngridient;
}

inline 
int Customer::getCustomerAge() const
{
	return customerAge;
}

inline
double  Customer::getCustomerMoney() const
{
	return customerMoney;
}

/*****************************************************************************/

#endif // _CUSTOMER_HPP_
