// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "parenttreeitem.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/

int ParentTreeItem::getChildrenNodesAmount() const
{
	if (!m_IsCollapsedAttribute)
	{
		return m_ChildrenNodes.size();
	}
	else
		return 0;
}

TreeItem & ParentTreeItem::getChildrenNodeAt(int _number) const
{
	if (!m_IsCollapsedAttribute)
	{
		return *m_ChildrenNodes[_number];
	}
	else
		throw std::logic_error(Messages::TreeItemHasNotChildren);
}

bool const ParentTreeItem::getCollapsedAttribute() const
{
	return m_IsCollapsedAttribute;
}

bool const ParentTreeItem::getExpandAttribute() const
{
	return !getCollapsedAttribute();
}

bool const ParentTreeItem::getIsLeaf() const
{
	return false;
}



ParentTreeItem::ParentTreeItem(std::string _name)
	:TreeItem(_name)
{
}

void  ParentTreeItem::PushChildrenNode(std::unique_ptr<TreeItem> _node)
{
	 m_ChildrenNodes.push_back(std::move(_node));
	
}

void ParentTreeItem::setCollapseAttribute(bool _i)
{
	m_IsCollapsedAttribute = _i;
}



