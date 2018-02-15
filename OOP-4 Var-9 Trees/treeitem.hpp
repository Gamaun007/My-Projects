// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TREEITEM_HPP_
#define _TREEITEM_HPP_
#include <string>
#include "messages.hpp"
#include <vector>
#include<memory>
/*****************************************************************************/
class ParentTreeItem;
class TreeItem
{

/*-----------------------------------------------------------------*/
public:
	virtual ~TreeItem() = default;

	//TreeItem(const TreeItem &) = delete;
	//TreeItem & operator = (const TreeItem &) = delete;

	virtual int getChildrenNodesAmount() const = 0;
	virtual TreeItem & getChildrenNodeAt(int _number)const = 0 ;
	std::string const getNodeDataInfo() const;
	bool const getVisibilityAttribute() const;
	virtual bool const getIsLeaf() const = 0;
	virtual bool const getCollapsedAttribute() const = 0;
	virtual bool const getExpandAttribute() const = 0;
	void setVisibilityAttribute(bool _i);
	virtual void setCollapseAttribute(bool _i) = 0;

	void OutputNodeInfo(std::ostream & _o, int _lvl) const;

protected:
	TreeItem(std::string _name);
	
private:
	std::string m_nodeDataInfo;
	bool m_visibilityAttribute = true;


/*-----------------------------------------------------------------*/
};

inline
std::string const TreeItem::getNodeDataInfo() const
{
	return m_nodeDataInfo;
}
inline bool const TreeItem::getVisibilityAttribute() const
{
	return m_visibilityAttribute;
}
inline void TreeItem::setVisibilityAttribute(bool _i)
{
	m_visibilityAttribute = _i;
}



/*****************************************************************************/

#endif // _TREEITEM_HPP_
