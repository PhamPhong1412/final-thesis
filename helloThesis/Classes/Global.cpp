#include "Global.h"

bool Global::instanceFlag = false;
Global* Global::_global = NULL;

Global* Global::getInstance()
{
	if (!instanceFlag)
	{
		instanceFlag = true;
		_global = new Global();
		return _global;
	}
	else
	{
		return _global;
	}
}

Global::Global()
{
	_pause = false;
	_mapWidth = 1;
	_mapHeight = 1;
}