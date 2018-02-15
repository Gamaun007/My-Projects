// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _LEAFTREEITEM_HPP_
#define _LEAFTREEITEM_HPP_

/*****************************************************************************/

#include "treeitem.hpp"

/*****************************************************************************/

class LeafTreeItem
	:	public TreeItem
{

/*-----------------------------------------------------------------*/
public:
	int getChildrenNodesAmount()const override;
	TreeItem & getChildrenNodeAt(int _number)const override;
	virtual bool const getCollapsedAttribute() const override;
	virtual bool const getIsLeaf() const override;
	virtual bool const getExpandAttribute() const override;

	LeafTreeItem(std::string _name);
	void setCollapseAttribute(bool _i) override;
private:
	
/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _LEAFTREEITEM_HPP_
