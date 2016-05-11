// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Node/Input/Gesture/IGestureRecognizer.h"
#include "Geometry/Point3.h"
#include "Node/INode.h"


MEDUSA_BEGIN;

IGestureRecognizer::IGestureRecognizer( INode* node) 
	:IInputHandler(node)
{

}
IGestureRecognizer::~IGestureRecognizer(void)
{
}


bool IGestureRecognizer::IsValidTouch( const Touch& touch ) const
{
	return mNode->HitTestWorld(touch.Pos);
}

Touch IGestureRecognizer::TransformToNodeSpace( const Touch& touch ) const
{
	Point2F pos=mNode->TransformToLocal(touch.Pos);
	Touch result = touch;
	result.Pos = pos;
	return result;
}

bool IGestureRecognizer::TryTransformToNodeSpace( const Touch& touch,Touch& outTouch ) const
{
	Point2F pos = mNode->TransformToLocal(touch.Pos);
	if (mNode->HitTestLocal(pos))
	{
		outTouch=touch;
		return true;
	}
	return false;
}

bool IGestureRecognizer::HasValidTouch( const List<Touch>& touches ) const
{
	FOR_EACH_COLLECTION(i,touches)
	{
		const Touch& touch=*i;
		if (mNode->HitTestWorld(touch.Pos))
		{
			return true;
		}
	}

	return false;
}


MEDUSA_END;