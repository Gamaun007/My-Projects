// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "lengthunit.hpp"
#include <stdexcept>
#include <cstring>
#include<string>

/*****************************************************************************/
LengthUnit::LengthUnit()
{
	m_meters = 0;
	m_feet = 0;
	m_inches = 0;
}

LengthUnit::LengthUnit(const char* ch_meter,char dot, char _sep, char _sepf, char _sepi)
{
	// Пытаемся распознать строковое представление  по шаблону.
	// Функция sscanf возвращает число успешно обнаруженных частей шаблона.
	char sep1, sep2;
	int  temp1, temp2;
	
	int nMatched = sscanf(ch_meter, "%d%c%d%c%d",
		&temp1, &sep1, &temp2, &sep2);
	if (nMatched == 2 && sep1 == _sep)
	{
		char *symbol = "m";
		m_meters = strtold(ch_meter, &symbol);
		m_feet = 0;
		m_inches = 0;
	}
	else
		if (nMatched == 4 && sep1 == dot && sep2 == _sep)
		{
			char *symbol = "m";
			m_meters = strtold(ch_meter, &symbol);
			m_feet = 0;
			m_inches = 0;
		}
		else if (nMatched == 4 && sep1 == _sepf && sep2 == _sepi)
		{
			m_feet = temp1;
				m_inches = temp2;
				
				
				if (!IsValid())
					throw std::logic_error("Error: is not valid!");
				
		}
		else throw std::logic_error("Bad format");

		
}

LengthUnit::LengthUnit(long double _meters)

{
	m_meters = _meters;
	m_feet = 0;
	m_inches = 0;
}

LengthUnit::LengthUnit(int _feet, int _inches)
{
	m_feet = _feet;
	m_inches = _inches;
	m_meters = _feet*METERS_IN_FOOT + _inches*METERS_IN_INCH;
	
	
	if (!IsValid())
		throw std::logic_error("Inches out of range");

}

bool LengthUnit::IsValid() const
{
	
	if (m_inches<0 || m_inches>11)
		return 0;
	else return 1;
}

long double LengthUnit::getAsMeters() const
{
	
		return m_meters;
}

void LengthUnit::fetchAsEnglish(int & _feet, int & _inches) const

{
	if (m_meters / METERS_IN_FOOT == 0)
	{
		_feet = 0;
		_inches = m_meters / METERS_IN_INCH;
	}
	else if (m_meters / METERS_IN_FOOT >0)
	{
		double full_feet = (m_meters / METERS_IN_FOOT);
		_feet = full_feet;
		_inches = ((full_feet - _feet)*METERS_IN_FOOT) / METERS_IN_INCH;
	}
	else
	if (m_meters == 0 || (m_feet == 0 && m_inches == 0))
	{
			_feet = 0; 
			_inches = 0;
		
	}
	else
	if (m_feet != 0 || m_inches != 0)
	{
		_feet = m_feet;
		_inches = m_inches;
	}
	
	
		

	

}
char* LengthUnit::toMetricString()
{
	
	
	sprintf(lengthbuffer, "%.2f%c", m_meters, 'm');
	m_checker = true;
	return lengthbuffer;
	
}

char *LengthUnit::toEnglishString()
{


	sprintf(lengthbuffer, "%i%c%i%c", m_feet, '\'', m_inches,  '"');
	m_checker = true;
	return lengthbuffer;
	
}

bool LengthUnit::operator == (LengthUnit &d) const
{
	
	return m_meters == d.getAsMeters() ;
} 
bool LengthUnit::operator != (LengthUnit &d) const
{
	
	return m_meters != d.getAsMeters();
}

bool LengthUnit::operator < (LengthUnit &d) const
{

	if (m_meters < d.getAsMeters())
		return true;
	
	else
		return false;
}

bool LengthUnit::operator >(LengthUnit &d) const
{
	if (m_meters > d.getAsMeters())
		return true;

	else
		return false;
}

bool LengthUnit::operator <= (LengthUnit &d) const
{
	
	return (m_meters < d.getAsMeters()) || (*this == d);
}

bool LengthUnit::operator >= (LengthUnit &d) const
{
	return (m_meters > d.getAsMeters()) || (*this == d);
}


LengthUnit operator "" _m(long double meter)
{
	
	return LengthUnit(meter);
}

LengthUnit::~LengthUnit()
{
	
	delete[] this->lengthbuffer;
}
const long double LengthUnit::METERS_IN_INCH = 0.0254;
const long double LengthUnit::METERS_IN_FOOT = 0.3048;

/*****************************************************************************/

// TODO ...

/*****************************************************************************/