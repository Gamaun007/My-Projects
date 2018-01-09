// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _FOODPRODUCT_HPP_
#define _FOODPRODUCT_HPP_

/*****************************************************************************/

#include "foodcomponents.hpp"

#include <string>
#include <memory>

/*****************************************************************************/


class FoodProduct
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	FoodProduct(std::string const & _productname, FoodComponents &_components,double _calories);
	FoodComponents const & getFoodComponents() const;
	std::string const & getProductName() const;
	double getCalories() const;
	//bool operator == (FoodProduct _c) const;
	//bool operator != (FoodProduct _c) const;


/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	double m_calories;
	const std::string m_productname;
	FoodComponents  m_components;

/*-----------------------------------------------------------------*/

};
inline double
FoodProduct::getCalories() const
{
	return m_calories;
}

/*inline bool FoodProduct::operator==(FoodProduct _c) const
{
	return _c.getProductName == this->getProductName;
}

inline bool FoodProduct::operator!=(FoodProduct _c) const
{
	return !(*this == _c);
}
*/
inline FoodComponents const &
FoodProduct::getFoodComponents() const
{
	return  m_components;
}

inline
std::string const & FoodProduct::getProductName() const
{
	return m_productname;
}
/*****************************************************************************/

#endif //  _FOODPRODUCT_HPP_
