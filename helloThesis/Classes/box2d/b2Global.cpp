#include "b2Global.h"

b2Global* b2Global::_b2Global = NULL;

b2Global::b2Global()
{

}

b2Global* b2Global::getInstance()
{
	if (!_b2Global)
	{
		_b2Global = new b2Global();
	}

	return _b2Global;
}