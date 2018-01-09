// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MENU_HPP_
#define _MENU_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>
/*****************************************************************************/

class FoodProduct;


/*****************************************************************************/


class Menu
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Menu(std::string _mname);
	std::string getMname() const;
	void addProductAndWeight(FoodProduct const & _food, int _weight);
	void findSameProduct(FoodProduct const & _name) const;
	void productNotInMenu(FoodProduct const & _name) const;
	void removeProduct(FoodProduct const & _product);
	void updateWeight(FoodProduct const & _product, int _weight);
	double const getWeight(FoodProduct const & _product) const;
	//FoodComponents getComponents(FoodProduct const * _product) const;
	void forEachMenuProduct(std::function< void(FoodProduct const &) > _prod) const;
	void forEachMenuProductWeight(std::function< void(double const) > _weight) const;

	

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	const std::string m_mname;
	std::unordered_map< FoodProduct const *, double > m_weightmap;
/*-----------------------------------------------------------------*/

};
inline
std::string Menu::getMname() const
{
	return m_mname;
}
/*****************************************************************************/

#endif //  _MENU_HPP_
