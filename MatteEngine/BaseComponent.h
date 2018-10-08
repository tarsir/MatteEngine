#pragma once
#include "ComponentList.h"
#include <string>

class Component {
public:
	virtual ComponentTypes component_type() = 0;
};