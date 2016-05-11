// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Quad.h"

#include "Geometry/Color4.h"
#include "Geometry/Point2.h"
#include "Geometry/Point3.h"
#include "Geometry/Vertex/TextureVertex.h"
#include "Geometry/Vertex/TextureNormalVertex.h"
#include "Geometry/Vertex/ShapeVertex.h"

MEDUSA_BEGIN;

//[PRE_DECLARE_BEGIN]
typedef Quad<Color4F> QuadColor;
typedef Quad<Point2<float> > QuadTexCoord;
typedef Quad<Point3<float> > QuadVertex3;
typedef Quad<Point2<float> > QuadVertex2;
typedef Quad<TextureVertex> QuadTextureVertex;
typedef Quad<TextureNormalVertex> QuadTextureNormalVertex;

typedef Quad<ShapeVertex> QuadShapeVertex;

//[PRE_DECLARE_END]


MEDUSA_END;
