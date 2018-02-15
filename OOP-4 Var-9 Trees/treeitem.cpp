// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "treeitem.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/ 

TreeItem::TreeItem(std::string _name)
	: m_nodeDataInfo(_name)
{

}

void TreeItem::OutputNodeInfo(std::ostream & _s, int _level) const
{
	if (m_visibilityAttribute)
	{
		for (int i = 0; i < _level; i++)
			_s << "\t";

		_s << getNodeDataInfo() << std::endl;

		for (int i = 0; i < getChildrenNodesAmount(); i++)
			getChildrenNodeAt(i).OutputNodeInfo(_s, _level + 1);
	}
}