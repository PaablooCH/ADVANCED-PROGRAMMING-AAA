#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		LOG_ENGINE("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		LOG_ENGINE("Dummy CleanUp!");
		return true;
	}
};