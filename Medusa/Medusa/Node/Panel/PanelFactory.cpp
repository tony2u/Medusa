// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "PanelFactory.h"
#include "StackPanel.h"
#include "RelativePanel.h"
#include "CanvasPanel.h"
#include "DockPanel.h"
#include "GridPanel.h"
#include "UniformGridPanel.h"
#include "WrapPanel.h"
#include "ViewPanel.h"
#include "ScrollPanel.h"



MEDUSA_BEGIN;

PanelFactory::PanelFactory()
{
	Register<StackPanel>(PanelType::Stack);
	Register<RelativePanel>(PanelType::Relative);
	Register<CanvasPanel>(PanelType::Canvas);
	Register<DockPanel>(PanelType::Dock);
	Register<GridPanel>(PanelType::Grid);
	Register<UniformGridPanel>(PanelType::UniformGrid);
	Register<WrapPanel>(PanelType::Wrap);
	Register<ViewPanel>(PanelType::View);
	Register<ScrollPanel>(PanelType::Scroll);


}

MEDUSA_END;
