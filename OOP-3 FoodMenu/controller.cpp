// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include <algorithm>

#include "foodproduct.hpp"
/*****************************************************************************/

// TODO implement controller methods here

/*****************************************************************************/

//Controller::Controller()
//{
//}

Controller::~Controller()
{
}

void Controller::createFoodProduct(std::string const & _productName, FoodComponents _components, double _energeticValue)
{
	if (findProduct(_productName))
		throw std::logic_error(Messages::ProductAlreadyExists);
	if (_productName == "")
		throw std::logic_error(Messages::EmptyProductName);
	if (_energeticValue < 0)
		throw std::logic_error(Messages::NegativeEnergeticValue);
	m_products[_productName] =
		std::make_unique< FoodProduct >(_productName, _components, _energeticValue);
}



FoodProduct * Controller::findProduct(std::string const & _name) const
{
	auto it = m_products.find(_name);
	return (it == m_products.end()) ? nullptr : it->second.get();
}

FoodProduct & Controller::resolveProduct(std::string const & _name) const
{
	FoodProduct * pProduct = findProduct(_name);
	if (pProduct)
		return *pProduct;

	throw std::logic_error(Messages::ProductNotFound);
}

Menu * Controller::findMenu(std::string const & _name) const
{
	auto it = m_menus.find(_name);
	return (it == m_menus.end()) ? nullptr : it->second.get();
}

Menu & Controller::resolveMenu(std::string const & _name) const
{
	Menu * pMenu = findMenu(_name);
	if (pMenu)
		return *pMenu;

	throw std::logic_error(Messages::MenuNotFound);
}

FoodComponents  Controller::getFoodProductComponents(std::string const & _productName) const
{
	return resolveProduct(_productName).getFoodComponents();
}

double  Controller::getFoodProductEnergeticValue(std::string const & _productName) const
{
	return resolveProduct(_productName).getCalories();
}

void Controller::createMenu(std::string const & _menuName)
{
	if (findMenu(_menuName))
		throw std::logic_error(Messages::MenuAlreadyExists);
	if (_menuName == "")
		throw std::logic_error(Messages::EmptyMenuTitle);
	m_menus[_menuName] =
		std::make_unique< Menu >(_menuName);
}

void Controller::addProductToMenu(std::string const & _menuName, std::string const & _productName, int _weight)
{
		resolveMenu(_menuName).addProductAndWeight(resolveProduct(_productName), _weight);
}

void Controller::removeProductFromMenu(std::string const & _menuName, std::string const & _productName)
{
	resolveMenu(_menuName).removeProduct(resolveProduct(_productName));
}

void Controller::updateProductWeightInMenu(std::string const & _menuName, std::string const & _productName, int _newWeight)
{
	resolveMenu(_menuName).updateWeight(resolveProduct(_productName),_newWeight);
}

double Controller::getProductWeightInMenu(std::string const & _menuName, std::string const & _productName)
{
	return resolveMenu(_menuName).getWeight(resolveProduct(_productName)) ;
}

std::vector<std::string> Controller::getProductsInMenu(std::string const & _menuName) const
{
	std::vector<std::string> result;
	const Menu & e = resolveMenu(_menuName);

	
	e.forEachMenuProduct(
		[&](const FoodProduct & _prod)
	{
		result.push_back(_prod.getProductName());
	}
	);
	std::sort(result.begin(),result.end());
	return  result;
}

FoodComponents Controller::getTotalComponentsInMenu(std::string const & _menuName) const
{
	
	const Menu & e = resolveMenu(_menuName);

	float _prot = 0;
	double _fat = 0;
	double _carbo = 0;

	e.forEachMenuProduct(
		[&](const FoodProduct & _prod)
	{
	
	_prot += e.getWeight(_prod) / 100 * getComponents(&_prod).getProteins() ;
	_fat += e.getWeight(_prod) /100 * getComponents(&_prod).getFat();
	_carbo += e.getWeight(_prod) /  100 * getComponents(&_prod).getCarbo();
	}
					);

	FoodComponents result((double)_prot, _fat, _carbo);
	return result;
}

double Controller::getMenuDailyEnergeticPercentage(std::string const & _menuName, double _dailyNorm) const
{
	if (_dailyNorm < 0)
		throw std::logic_error(Messages::NegativeEnergeticValue);

	const Menu & e = resolveMenu(_menuName);

	double _calori = 0;

	e.forEachMenuProduct(
		[&](const FoodProduct & _prod)
	{

		_calori += e.getWeight(_prod) / 100 * _prod.getCalories();
		
	}
	);
	double result = (_calori / _dailyNorm) * 100;
	return result;
}

std::string Controller::findProductWithMinimalFatWithEnergyOver(double _energeticValue) const
{
	double _fatbuffer = 0;
	std::string _name = "";
	if (_energeticValue < 0)
		throw std::logic_error(Messages::NegativeEnergeticValue);
	forEachProduct(
		[&](const FoodProduct & _prod)
	{
		double _calories = _prod.getCalories();
		if (_calories >= _energeticValue)
		{
			double _buffer = getComponents(&_prod).getFat();
			if (_fatbuffer == 0 || _buffer < _fatbuffer)
			{
				_fatbuffer = _buffer;
				_name = _prod.getProductName();
			}
				
		}

	}
	);
	return _name;
}

std::string Controller::findMenuWithBiggestWeight() const
{
	double _champion = 0;
	std::string mostpowerfullmenu = "";
	forEachMenu(
		[&](const Menu & _menu)
	{
		double _menuweight = 0;

		_menu.forEachMenuProductWeight(
			[&](const double _weight)
		{
			_menuweight += _weight;
		}
										);
		if (_champion == 0 || _champion < _menuweight)
		{
			_champion = _menuweight;
			mostpowerfullmenu = _menu.getMname();

		}
	}
				);
	return mostpowerfullmenu;
	
}

void Controller::forEachProduct(std::function<void(FoodProduct const&)> _prod) const
{
	for (auto & pProduct : m_products)
	{

		_prod(*pProduct.second);
	}
}

void Controller::forEachMenu(std::function<void(Menu const&)> _menu) const
{
	
	for (auto & pMenu : m_menus)
	{

		_menu(*pMenu.second);
	}
}


FoodComponents  Controller::getComponents(FoodProduct const * _product) const
{
	return _product->getFoodComponents();
}

