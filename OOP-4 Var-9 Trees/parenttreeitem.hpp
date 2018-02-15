// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PARENTTREEITEM_HPP_
#define _PARENTTREEITEM_HPP_

/*****************************************************************************/

#include "treeitem.hpp"

/*****************************************************************************/

class ParentTreeItem
	:	public TreeItem
{

/*-----------------------------------------------------------------*/
public:

	int getChildrenNodesAmount()const override;
	TreeItem & getChildrenNodeAt(int _number)const  override;
	virtual bool const getCollapsedAttribute() const override;
	virtual bool const getExpandAttribute() const override;
	virtual bool const getIsLeaf() const override;

	ParentTreeItem(std::string _name);
	void  PushChildrenNode(std::unique_ptr<TreeItem> _node);
	void setCollapseAttribute(bool _i) override;

	
private:
	std::vector <std::unique_ptr <TreeItem>> m_ChildrenNodes;
	bool m_IsCollapsedAttribute = false;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _PARENTTREEITEM_HPP_
