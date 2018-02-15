// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"

/*****************************************************************************/


// TODO


/*****************************************************************************/  

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::startParentNode(std::string const & _text)
{
	if (_text == "")
		throw std::logic_error(Messages::EmptyDescriptionText);
	auto it = std::make_unique<ParentTreeItem>(_text);
	ParentTreeItem * pNode = it.get();

	if (c_WayToParentNode.empty())
		c_MainNodes.push_back(std::move(it) );
	else
		c_WayToParentNode.back()->PushChildrenNode(std::move(it));
	
	c_WayToParentNode.push_back(pNode);
}

void Controller::addLeafNode(std::string const & _text)
{
	if (_text == "")
		throw std::logic_error(Messages::EmptyDescriptionText);
	auto it = std::make_unique<LeafTreeItem>(_text);
	LeafTreeItem * pNode = it.get();
	if (c_WayToParentNode.empty())
	{
		
		c_MainNodes.push_back(std::move (it));
	}
	else
	{
		
		c_WayToParentNode.back()->PushChildrenNode(std::move (it));
	}
}

void Controller::endParentNode()
{
	if (c_WayToParentNode.empty())
		throw std::logic_error(Messages::DidNotOpenParentPreviously);
	c_WayToParentNode.pop_back();
}

TreeItem & Controller::findNode(NodePath const & _path) const
{
	
	if (_path.getIndexAtLevel(0)<1 || _path.getIndexAtLevel(0)>c_MainNodes.size())
		throw std::logic_error(Messages::NodePathUnresolved);
	TreeItem * it = c_MainNodes.at(_path.getIndexAtLevel(0) - 1).get();
	for (int i = 1; i < _path.getLevelsCount(); i++)
	{
		if (_path.getIndexAtLevel(i)<1 || _path.getIndexAtLevel(i)>it->getChildrenNodesAmount())
			throw std::logic_error(Messages::NodePathUnresolved);
		if (i < _path.getLevelsCount() && _path.getLevelsCount() > 0 && it->getChildrenNodesAmount() == 0)
			throw std::logic_error(Messages::TreeItemHasNotChildren);
		
		it = &it->getChildrenNodeAt(_path.getIndexAtLevel(i)-1);
	}

	return *it;

}

std::string Controller::getNodeDescription(NodePath const & _path) const
{
	return findNode(_path).getNodeDataInfo();
	
}

int Controller::getNodeChildrenCount(NodePath const & _path) const
{
	return findNode(_path).getChildrenNodesAmount();
}

void Controller::makeInvisible(NodePath const & _path)
{
	findNode(_path).setVisibilityAttribute(false);
}

void Controller::makeVisible(NodePath const & _path)
{
	findNode(_path).setVisibilityAttribute(true);
}

void Controller::expand(NodePath const & _path)
{
	findNode(_path).setCollapseAttribute(false);
}

void Controller::collapse(NodePath const & _path)
{
	findNode(_path).setCollapseAttribute(true);
}

bool Controller::isVisible(NodePath const & _path) const
{
	return findNode(_path).getVisibilityAttribute();
}

bool Controller::isExpanded(NodePath const & _path) const
{
	return findNode(_path).getExpandAttribute();
}

bool Controller::isLeaf(NodePath const & _path) const
{
	return findNode(_path).getIsLeaf();
}

void Controller::show(std::ostream & _o)
{
	for (auto const & node : c_MainNodes)
		node->OutputNodeInfo(_o, 0);
}