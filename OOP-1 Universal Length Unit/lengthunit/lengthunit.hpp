// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LENGTHUNIT_HPP_
#define _LENGTHUNIT_HPP_

/*****************************************************************************/


class LengthUnit
{



	long double m_meters;
	int m_feet, m_inches;

	mutable char* lengthbuffer = new char[50];
	mutable bool m_checker = false;
public:
	LengthUnit();
	LengthUnit(long double _meters);

	LengthUnit(int _feet, int _inches);
	LengthUnit(const char* ch_meter, char _point = '.', char _sep1 = 'm', char _sep2 = '\'', char _sep3 = '\"');
	bool operator == (LengthUnit &d) const;
	bool operator != (LengthUnit &d) const;
	bool operator < (LengthUnit &d) const;
	bool operator <= (LengthUnit &d) const;
	bool operator > (LengthUnit &d) const;
	bool operator >= (LengthUnit &d) const;

	void fetchAsEnglish(int & _feet, int & _inches) const;
	long double getAsMeters() const;
	bool IsValid() const;
	char *toMetricString();
	char *toEnglishString();
	

	static const long double METERS_IN_INCH;
	static const long double METERS_IN_FOOT;

	~LengthUnit();

};


/*****************************************************************************/
LengthUnit operator "" _m(long double meter);
#endif //  _LENGTHUNIT_HPP_

