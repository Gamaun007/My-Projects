// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "foodcomponents.hpp"
#include "menu.hpp"
#include "foodproduct.hpp"
#include <vector>
#include<unordered_map>
#include <string>
#include <memory>
#include <functional>
//#include <math.h>

/*****************************************************************************/
class Menu;

class FoodProduct;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller () = default;

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller () ;

/*-----------------------------------------------------------------*/

	void createFoodProduct (
		std::string const & _productName, 
		FoodComponents _components,
		double _energeticValue
	);
	
	FoodComponents getFoodProductComponents ( std::string const & _productName ) const;

	double getFoodProductEnergeticValue ( std::string const & _productName ) const;

/*-----------------------------------------------------------------*/

	void createMenu ( std::string const & _menuName );

	void addProductToMenu (
		std::string const & _menuName,
		std::string const & _productName,
		int _weight
	);

	void removeProductFromMenu (
		std::string const & _menuName,
		std::string const & _productName
	);

	void updateProductWeightInMenu (
		std::string const & _menuName,
		std::string const & _productName,
		int _newWeight
	);

	double getProductWeightInMenu (
		std::string const & _menuName,
		std::string const & _productName
	);

	std::vector< std::string > getProductsInMenu ( std::string const & _menuName ) const;

/*-----------------------------------------------------------------*/

	FoodComponents getTotalComponentsInMenu ( std::string const & _menuName ) const;

	double getMenuDailyEnergeticPercentage ( 
		std::string const & _menuName, 
		double _dailyNorm = 2500.00
	) const;

	std::string findProductWithMinimalFatWithEnergyOver ( double _energeticValue ) const;

	std::string findMenuWithBiggestWeight () const;

	void forEachProduct(std::function< void(FoodProduct const &) > _prod) const;
	void forEachMenu(std::function< void(Menu const &) > _menu) const;
	FoodComponents getComponents(FoodProduct const * _product) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	FoodProduct* findProduct(std::string const & _name) const;
	FoodProduct & resolveProduct(std::string const & _name) const;

	Menu* findMenu(std::string const & _name) const;
	Menu & resolveMenu(std::string const & _name) const;

/*-----------------------------------------------------------------*/

	//std::vector< Menu const * > m_menus;
	std::unordered_map<std::string, std::unique_ptr< FoodProduct > > m_products;
	std::unordered_map<std::string, std::unique_ptr< Menu > > m_menus;


/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
