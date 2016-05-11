// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Rendering/RenderingTypes.h"

MEDUSA_BEGIN;


class RenderingObject
{
public:
	const static RenderingObject Empty;
	RenderingObject(IMesh* mesh=nullptr,IMaterial* material=nullptr);
	RenderingObject(::std::nullptr_t const) noexcept { }

	~RenderingObject();
	RenderingObject(const RenderingObject& val);
	RenderingObject& operator=(const RenderingObject& val);
	RenderingObject(RenderingObject&& val);
	RenderingObject& operator=(RenderingObject&& val);

	bool operator==(const RenderingObject& val)const { return mMesh == val.mMesh&&mMaterial == val.mMaterial; }

	bool operator==(::std::nullptr_t const) const noexcept { return !IsValid(); }
	bool operator!=(::std::nullptr_t const) const noexcept { return IsValid(); }

	friend bool operator==(::std::nullptr_t, const RenderingObject& other) noexcept { return other.IsValid(); }
	friend bool operator!=(::std::nullptr_t, const RenderingObject& other) noexcept { return !other.IsValid(); }

	explicit operator bool() const noexcept { return IsValid(); }
public:
	IMesh* Mesh()const { return mMesh; }
	void SetMesh(IMesh* val);

	IMaterial* Material() const { return mMaterial; }
	void SetMaterial(IMaterial* val);

	bool IsValid() const;
	bool IsBlend()const;

	void UnregisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val);
	void UnregisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val);

	void RegisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val);
	void RegisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val);
private:
	IMesh* mMesh = nullptr;
	IMaterial* mMaterial = nullptr;
};


MEDUSA_END;