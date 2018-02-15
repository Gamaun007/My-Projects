// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "leaftreeitem.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/ 


int LeafTreeItem::getChildrenNodesAmount() const
{
	return 0;
}

TreeItem & LeafTreeItem::getChildrenNodeAt(int _number) const
{
	throw std::logic_error(Messages::TreeItemHasNotChildren);
}

bool const LeafTreeItem::getCollapsedAttribute() const
{
	return true;
}

bool const LeafTreeItem::getIsLeaf() const
{
	return true;
}

bool const LeafTreeItem::getExpandAttribute() const
{
	return !getCollapsedAttribute();
}

LeafTreeItem::LeafTreeItem(std::string _name)
	:TreeItem(_name)
{
}

void LeafTreeItem::setCollapseAttribute(bool _i)
{
	
}
