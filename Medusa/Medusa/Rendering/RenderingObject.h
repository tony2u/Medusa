// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma  once
#include "MedusaPreDeclares.h"
#include "Core/Pattern/Delegate.h"
#include "Rendering/RenderingTypes.h"
#include "Resource/Model/Mesh/IMesh.h"
#include "Resource/Material/IMaterial.h"

MEDUSA_BEGIN;


class RenderingObject
{
public:
	const static RenderingObject Empty;
	RenderingObject(const Share<IMesh>& mesh = nullptr, const Share<IMaterial>& material = nullptr);
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
	const Share<IMesh>& Mesh()const { return mMesh; }
	void SetMesh(const Share<IMesh>& val);

	const Share<IMaterial>& Material() const { return mMaterial; }
	void SetMaterial(const Share<IMaterial>& val);

	bool IsValid() const;
	bool IsBlend()const;

	void UnregisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val);
	void UnregisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val);

	void RegisterMeshChanged(const Delegate<void(RenderableChangedFlags)>& val);
	void RegisterMaterialChanged(const Delegate<void(RenderableChangedFlags)>& val);
private:
	Share<IMesh> mMesh = nullptr;
	Share<IMaterial> mMaterial = nullptr;
};


MEDUSA_END;