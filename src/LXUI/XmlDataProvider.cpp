#include "stdafx.h"
#include "LXUI2.h"

namespace System
{

signal2<Object*, StringW*>& DataSourceProvider::get_PropertyChanged()
{
	return PropertyChanged;
}

}
