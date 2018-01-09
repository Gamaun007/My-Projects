// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "menu.hpp"
#include "messages.hpp"
#include <algorithm>
#include "foodproduct.hpp"
#include "foodcomponents.hpp"

/*****************************************************************************/

// TODO implement your methods here

/*****************************************************************************/

Menu::Menu(std::string _mname)
	:m_mname(_mname)
{
}


void Menu::addProductAndWeight(FoodProduct const & _food, int _weight)
{
	if (_weight <= 0)
		throw std::logic_error(Messages::NonPositiveWeight);
	findSameProduct(_food);
	m_weightmap[&_food] = _weight;
}

void Menu::findSameProduct(FoodProduct const & _name) const
{

	for (auto& x : m_weightmap)
	{
		if (x.first->getProductName() == _name.getProductName())
			throw std::logic_error(Messages::ProductAlreadyIncluded);

	}
	

/*	auto it = std::find_if(
		m_weightmap.begin(), m_weightmap.end(),
		[&](auto const & _product)
	{
		if (_product->getProductName() == _name->getProductName())
			throw std::logic_error(Messages::ProductAlreadyIncluded);
	}
	);
	*/
		
}

void Menu::productNotInMenu(FoodProduct const & _name) const
{
	for (auto& x : m_weightmap)
	{
		if (x.first->getProductName() == _name.getProductName())
			return;
		//if (x == m_weightmap.end())
			
	}
	throw std::logic_error(Messages::ProductNotIncluded);
/*	auto it = std::find_if(
		m_weightmap.begin(), m_weightmap.end(),
		[&](auto const & _product)
	{
		if (it == m_weightmap.end())
			throw std::logic_error(Messages::ProductNotIncluded);
	}
	);*/
}

void Menu::removeProduct(FoodProduct const & _product)
{
	productNotInMenu(_product);
	m_weightmap.erase(&_product);

}

void Menu::updateWeight(FoodProduct const & _product, int _weight)
{
	if (_weight <= 0)
		throw std::logic_error(Messages::NonPositiveWeight);
	productNotInMenu(_product);
	m_weightmap[&_product] = _weight;
}

double const Menu::getWeight(FoodProduct const & _product) const
{
	productNotInMenu(_product);
	return m_weightmap.at(&_product);
}

//FoodComponents  Menu::getComponents(FoodProduct const * _product) const
//{
//	return _product->getFoodComponents();
//}

void Menu::forEachMenuProduct(std::function< void(FoodProduct const &) > _prod) const
{
	for (auto & pProduct : m_weightmap)
	{

		_prod(*pProduct.first);
	}
		
}

void Menu::forEachMenuProductWeight(std::function<void(double const)> _weight) const
{
	for (auto & pWeight : m_weightmap)
	{
		_weight(pWeight.second);
	}
}


