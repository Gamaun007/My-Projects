// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "passport.hpp"
#include "messages.hpp"

/*****************************************************************************/


Passport::Passport( std::string id, Date v, std::string name)
	: passport_id(id) , current_date (v), passport_name (name)
{
	if (!isValidID())
		throw std::logic_error(Messages::BadPassportId);
	if(!isValidDate())
		throw std::logic_error(Messages::PassportIssuedInFuture);
	if (!isValidName())
		throw std::logic_error(Messages::OwnerEmptyName);
}

Passport::~Passport()
{
	while (!reglist.empty())
		reglist.pop_back();
	reglist.clear();
}
Passport::RegistrationRecord::RegistrationRecord(std::string const & _address, Date _date, bool _isRegistration)
	:m_address (_address), m_date ( _date) , m_isRegistration ( _isRegistration)
{

}
bool Passport::RegistrationRecord::operator == (RegistrationRecord  const & _r) const
{
	return (m_address == _r.m_address && m_date == _r.m_date);
}

bool Passport::RegistrationRecord::operator != (RegistrationRecord  const & _r) const
{
	return !(*this == _r);
}

bool Passport::isValidName() const
{
	return !(passport_name[0] == NULL);
}

bool Passport::isValidID() const
{
	
	std::regex regular("[A-Z]{2}[0-9]{6}");
	return (std::regex_match(passport_id, regular));
	
	
}

bool Passport::isValidDate() const
{
	return (current_date <= Date());
}

std::string Passport::getPassportId() const
{
	return passport_id;
}

std::string Passport::getOwnerFullName() const
{
	return passport_name;
}
Date Passport::getIssued() const
{
	return current_date;
}

int Passport::getTotalRegistrationRecordsCount() const
{
	return reglist.size();
}

bool Passport::isCurrentlyRegistered() const
{
	
	return (!reglist.empty() && reglist.back()->m_isRegistration == true);
	
}

Passport::RegistrationRecord Passport::getCurrentRegistration() const
{
	if (reglist.empty() || reglist.back()->m_isRegistration == false)
		throw std::logic_error(Messages::NoCurrentRegistration);
	else
		return *reglist.back();
	
}

Passport::RegistrationRecord &Passport::getRegistrationRecord(int _i) const
{
	return *reglist[_i];
}

void Passport::trackRegistration( std::string _address, Date _d)
{
	if (_d < current_date)
		throw std::logic_error(Messages::RegistrationDateBeforePassportIssue);
	else
	if (_d > Date())
		throw std::logic_error (Messages::RegistrationDateInFuture);
	else
	if (!reglist.empty() && reglist.back()->m_isRegistration == true)
		throw std::logic_error(Messages::CurrentRegistrationStillActive);
	else
		if(!reglist.empty() && _d < reglist.back()->m_date)
			throw std::logic_error(Messages::PreviousRegistrationLaterThanCurrent);
	else
		reglist.push_back(new Passport::RegistrationRecord(_address, _d, true));
	
	
}

void Passport::trackUnregistration(Date _d)
{
	if (reglist.empty())
		throw std::logic_error(Messages::NoCurrentRegistration);
	else
		if (reglist.back()->m_isRegistration == true)
		{
			if (_d < reglist.back()->m_date )
				throw std::logic_error(Messages::UnregisteringEarlierThanRegistered);
			if (_d > Date())
				throw std::logic_error(Messages::UnregistrationDateInFuture);
			else
			reglist.push_back(new Passport::RegistrationRecord(reglist.back()->m_address, _d, false));
			
		}
	else
	if (reglist.back()->m_isRegistration == false)
		throw std::logic_error(Messages::NoCurrentRegistration);
		
}

bool Passport::wasEverRegisteredAt(std::string _address) const //щрнцн лерндю мер б passport_test.cpp
{
	for (auto i : reglist)
	{
		if (i->m_address == _address)
		return true;
	}
	return false;
		
}

bool Passport::isCohabitantWith(Passport &_p)
{
	if (_p.reglist.empty() || this->reglist.empty())
		return false;
	return (_p.reglist.back()->m_address == this->reglist.back()->m_address);
	
}

std::string Passport::getAddressAt(Date _d) const
{
	if (!reglist.empty() && _d >= reglist.back()->m_date  && reglist.back()->m_isRegistration == true)
		return reglist.back()->m_address;
	else
	
		for (int  i =0; i < reglist.size(); i++)
		{
			if (reglist[i]->m_isRegistration == true && reglist[i]->m_date <= _d && reglist[i+1] ->m_date > _d)
				return reglist[i+1]->m_address;
		}	
	return "";

}

void Passport::forEachRegistration(std::function<void(Date, Date, std::string const, bool)> _lambda)
{
	if (reglist.empty()) 
		return;
	else
	for (int i=0;i< reglist.size();i++)
	{
		if (reglist[i]->m_isRegistration == true)
		{
			if (reglist[i] != reglist.back())
				_lambda(reglist[i]->m_date, reglist[i+1]->m_date, reglist[i]->m_address, false);
			else 
				_lambda(reglist[i]->m_date, Date(), reglist[i]->m_address, true);
		}
	}
}



// TODO ...


/*****************************************************************************/
