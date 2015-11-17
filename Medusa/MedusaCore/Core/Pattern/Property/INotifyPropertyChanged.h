// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaCorePreDeclares.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Property/PropertyChangedEventArg.h"

MEDUSA_BEGIN;

	template<typename T>
	struct INotifyPropertyChanged
	{
		Event<void (T& sender,PropertyChangedEventArg e)> PropertyChanged;
	};

MEDUSA_END;