// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
MEDUSA_BEGIN;



KeyUpEventArg::KeyUpEventArg(uint keyData,uint status)
	:BaseKeyEventArg(keyData,status)
{
	/*
	lParam 
		The repeat count, scan code, extended-key flag, context code, previous key-state flag, and transition-state flag, as shown in the following table. 


		0-15 The repeat count for the current message. The value is the number of times the keystroke is autorepeated as a result of the user holding down the key. The repeat count is always 1 for a WM_KEYUP message. 
		16-23 The scan code. The value depends on the OEM. 
		24 Indicates whether the key is an extended key, such as the right-hand ALT and CTRL keys that appear on an enhanced 101- or 102-key keyboard. The value is 1 if it is an extended key; otherwise, it is 0. 
		25-28 Reserved; do not use. 
		29 The context code. The value is always 0 for a WM_KEYUP message. 
		30 The previous key state. The value is always 1 for a WM_KEYUP message. 
		31 The transition state. The value is always 1 for a WM_KEYUP message. 
	*/
}



MEDUSA_END;