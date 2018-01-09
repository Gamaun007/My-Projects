// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PASSPORT_HPP_
#define _PASSPORT_HPP_

/*****************************************************************************/

#include "date.hpp"
#include <vector>
#include <functional>
#include <string>
#include <regex>


/*****************************************************************************/


class Passport
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	struct RegistrationRecord
	{
		const std::string m_address;
		const Date m_date;
		const bool m_isRegistration;

		RegistrationRecord ( std::string const & _address, Date _date, bool _isRegistration );

		
		bool operator == ( RegistrationRecord  const & _r ) const;

		bool operator != ( RegistrationRecord const & _r ) const;
	};

/*-----------------------------------------------------------------*/

	Passport( std::string id, Date v, std::string name);
	~Passport();
	bool isValidName() const;
	bool isValidDate() const;
	bool isValidID() const;
	std::string getPassportId() const;
	std::string getOwnerFullName() const;
	int getTotalRegistrationRecordsCount() const;
	bool isCurrentlyRegistered() const;
	RegistrationRecord getCurrentRegistration() const;
	Date getIssued() const;
	Passport(const Passport &) = delete;
	Passport & operator = (const Passport &) = delete;
	RegistrationRecord & getRegistrationRecord(int _i) const;
	void trackRegistration(std::string _address, Date _d);
	void trackUnregistration(Date _d);
	bool wasEverRegisteredAt(std::string _address) const;
	bool isCohabitantWith(Passport &_p);
	std::string getAddressAt(Date _d) const;
	void forEachRegistration(std::function<void(Date , Date , std::string const , bool  )> _lambda );
	
	


/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	std::vector<RegistrationRecord*> reglist;

	std::string passport_id;
	std::string passport_name;
	Date current_date;
	

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

// TODO: inline methods implementation

/*****************************************************************************/

#endif // _PASSPORT_HPP_
