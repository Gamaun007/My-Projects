// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "nodepath.hpp"
#include "treeitem.hpp"
#include "parenttreeitem.hpp"
#include "leaftreeitem.hpp"
#include <string>
#include <ostream>
#include <vector>
#include <unordered_map>
#include <memory>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller ();

/*-----------------------------------------------------------------*/

	void startParentNode ( std::string const & _text );

	void addLeafNode ( std::string const & _text );

	void endParentNode ();

	TreeItem & findNode(NodePath const & _path)const;
/*-----------------------------------------------------------------*/

	std::string getNodeDescription( NodePath const & _path ) const;

	int getNodeChildrenCount( NodePath const & _path ) const;

/*-----------------------------------------------------------------*/

	void makeInvisible ( NodePath const & _path );

	void makeVisible ( NodePath const & _path );

	void expand ( NodePath const & _path );

	void collapse ( NodePath const & _path );

/*-----------------------------------------------------------------*/

	bool isVisible ( NodePath const & _path ) const;

	bool isExpanded ( NodePath const & _path ) const;

	bool isLeaf ( NodePath const & _path ) const;

/*-----------------------------------------------------------------*/

void show ( std::ostream & _o );

//TreeItem * findMainNode(std::string const _text) const;
//TreeItem & resolveMainNode(std::string const _text) const;

//TreeItem * PushChildren(ParentTreeItem *_it, std::string const & _text);
/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::vector <std::unique_ptr<TreeItem>> c_MainNodes;
	std::vector < ParentTreeItem*> c_WayToParentNode;


/*-----------------------------------------------------------------*/ 

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
