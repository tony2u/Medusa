// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "MedusaPreDeclares.h"

MEDUSA_BEGIN;

struct MeshComponentVersions
{	
	uint VertexMesion; 
	uint NormalVersion; 
	uint ColorVersion; 
	uint TexCoordVersion; 
	uint IndexVersion; 
	MeshComponentVersions():VertexMesion(0),NormalVersion(0),ColorVersion(0),TexCoordVersion(0),IndexVersion(0){}	
	MeshComponentVersions(uint p1,uint p2,uint p3,uint p4,uint p5):VertexMesion(p1),NormalVersion(p2),ColorVersion(p3),TexCoordVersion(p4),IndexVersion(p5){}  
	MeshComponentVersions& operator=(const MeshComponentVersions& val){VertexMesion=val.VertexMesion;NormalVersion=val.NormalVersion;ColorVersion=val.ColorVersion;TexCoordVersion=val.TexCoordVersion;IndexVersion=val.IndexVersion;return *this;}	
	bool operator==(const MeshComponentVersions& val)const{return VertexMesion==val.VertexMesion&&NormalVersion==val.NormalVersion&&ColorVersion==val.ColorVersion&&TexCoordVersion==val.TexCoordVersion&&IndexVersion==val.IndexVersion;}	
	bool operator<(const MeshComponentVersions& val)const{return VertexMesion<val.VertexMesion&&NormalVersion<val.NormalVersion&&ColorVersion<val.ColorVersion&&TexCoordVersion<val.TexCoordVersion&&IndexVersion<val.IndexVersion;}	
	intp HashCode()const{return (VertexMesion)^(NormalVersion)^(ColorVersion)^(TexCoordVersion)^(IndexVersion);}	
	void Reset()
	{
		VertexMesion=0;
		NormalVersion=0;
		ColorVersion=0;
		TexCoordVersion=0;
		IndexVersion=0;
	}
	void IncreaseAll()
	{
		++VertexMesion;
		++NormalVersion;
		++ColorVersion;
		++TexCoordVersion;
		++IndexVersion;
	}
};


MEDUSA_END;