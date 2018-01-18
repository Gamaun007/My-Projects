// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#include "controller.hpp"
#include "customer.hpp"
#include "messages.hpp"
/*****************************************************************************/


// TODO


/*****************************************************************************/

Customer::Customer(std::string const & _name, int _age, double _money)
	: customerName(_name)
	,customerAge(_age)
	,customerMoney(_money)
{
	
}

void Customer::setCustomerAllergicIngridient(std::string _alergicname)
{
	customerAllergicIngridient = _alergicname;
}

void Customer::setCustomerMoney(double _money)
{
	customerMoney = customerMoney - _money;
}


