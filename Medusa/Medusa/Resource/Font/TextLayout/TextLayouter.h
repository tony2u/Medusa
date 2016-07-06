// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Resource/Font/IFont.h"
#include "Graphics/GraphicsTypes.h"
#include "Geometry/Point3.h"
#include "Geometry/Scale2.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Resource/Model/Mesh/Font/BaseFontMesh.h"

MEDUSA_BEGIN;


class TextLayouter
{

public:
	TextLayouter();
	~TextLayouter();
	const static uint TabWidth = 4;	//4 space
	const static uint FirstCJKChar = L'\u2E80';
public:
	static Size2F GetSingleLineSize(IFont& font, const WStringRef& text);
	static Size2F GetMultipleLineSize(IFont& font, const WStringRef& text, const Size2F& restrictSize = Size2F::Zero);

	static bool LayoutMultipleLineText(List<Share<BaseFontMesh>>& outMeshes, List<TextureAtlasPage*>& outPages, Size2F& outSize,
									   IFont& font, const WStringRef& text, Alignment alignment = Alignment::LeftBottom, const Size2F& restrictSize = Size2F::Zero, ILabel* label = nullptr, bool isStatic = false);
	static bool LayoutSingleLineText(List<Share<BaseFontMesh>>& outMeshes, List<TextureAtlasPage*>& outPages, Size2F& outSize,
									 IFont& font, const WStringRef& text, Alignment alignment = Alignment::LeftBottom, const Size2F& restrictSize = Size2F::Zero, ILabel* label = nullptr, bool isStatic = false);
private:
	static Size2F GetMultipleLineSizeHelper(IFont& font, const WStringRef& text);
	static Size2F GetMultipleLineSizeHelperWithWidth(IFont& font, const WStringRef& text, float restrictWidth);

	static bool WordWrapWithWidth(List<WHeapString>& outLines, List<float>& outLineWidths, float& outMaxWidth, IFont& font, const WStringRef& text, float restrictWidth);
	static bool WordWrap(List<WHeapString>& outLines, List<float>& outLineWidths, float& outMaxWidth, IFont& font, const WStringRef& text);

	static bool ExpandSingleLine(IFont& font, const WStringRef& text, WHeapString& outString, float& outLineWidth);

	static bool ExpandTab(const WStringRef& text, WHeapString& outString);
	static bool IsLineBreak(const WStringRef& text, uint index);
	static bool IsIdeographic(wchar_t c, bool includeNonStarters);

	static float GetCharWidth(IFont& font, wchar_t c);
	static const FontChar* GetChar(IFont& font, wchar_t c);


	static void AddCharToMesh(List<Share<BaseFontMesh>>& outMeshes, List<TextureAtlasPage*>& outPages,IFont& font, const FontChar& fontChar, const Point3F& origin, ILabel* label = nullptr, bool isStatic = false);

	static void LayoutMultipleLineMesh(List<Share<BaseFontMesh>>& outMeshes, List<TextureAtlasPage*>& outPages,
									   IFont& font, const Size2F& imageSize, const List<float>& lineWidths, const List<WHeapString>& lines, Alignment alignment, const Size2F& restrictSize, ILabel* label = nullptr, bool isStatic = false);

	static void LayoutSingleLineMesh(List<Share<BaseFontMesh>>& outMeshes, List<TextureAtlasPage*>& outPages,
									 IFont& font, const Size2F& imageSize, float lineWidth, const WStringRef& line, Alignment alignment, const Size2F& restrictSize, ILabel* label = nullptr, bool isStatic = false);

	static Point2F GetPenOrigin(uint lineIndex, uint lineCount, float lineWidth, float lineHeight, Alignment alignment, const Size2F& restrictSize);

	static bool ReserveMesh(List<Share<BaseFontMesh>>& outMeshes, const WStringRef& text);
	static bool ShrinkMesh(List<Share<BaseFontMesh>>& outMeshes);


};

MEDUSA_END;