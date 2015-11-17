// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#include "Resource/Font/TextLayout/TextLayouter.h"
#include "Core/Log/Log.h"
#include "Resource/Model/Mesh/Font/BaseFontMesh.h"
#include "Core/String/StringParser.h"
#include "Resource/Material/IMaterial.h"
#include "Core/Math/Math.h"
#include "Resource/ResourceNames.h"
#include "Node/Control/Label/ILabel.h"

MEDUSA_BEGIN;

TextLayouter::TextLayouter()
{

}

TextLayouter::~TextLayouter()
{
}


bool TextLayouter::LayoutMultipleLineText(List<BaseFontMesh*>& outMeshes, Size2F& outSize,
										  IFont& font,
										  const WStringRef& text,
										  Alignment alignment/*=Alignment::LeftBottom*/,
										  const Size2F& restrictSize/*==Size2F::Zero*/,
										  ILabel* label/*=nullptr*/,
										  bool isStatic/*=false*/)
{
	RETURN_FALSE_IF_EMPTY(text);
	outSize = restrictSize;

	List<WHeapString> outLines;
	List<float> outLineWidths;

	if (restrictSize.Width != 0)
	{
		if (!WordWrapWithWidth(outLines, outLineWidths, outSize.Width, font, text, restrictSize.Width))
		{
			Log::Error("Invalid layout");
			return false;
		}
	}
	else
	{
		if (!WordWrap(outLines, outLineWidths, outSize.Width, font, text))
		{
			Log::Error("Invalid layout");
			return false;
		}
	}
	outSize.Height = static_cast<float>(outLineWidths.Count()*font.LineHeight());
	ReserveMesh(outMeshes, text);

	LayoutMultipleLineMesh(outMeshes, font, outSize, outLineWidths, outLines, alignment, restrictSize, label);

	ShrinkMesh(outMeshes);
	return true;

}


bool TextLayouter::LayoutSingleLineText(List<BaseFontMesh*>& outMeshes,
										Size2F& outSize,
										IFont& font,
										const WStringRef& text,
										Alignment alignment/*=Alignment::LeftBottom*/,
										const Size2F& restrictSize/*=Size2F::Zero*/,
										ILabel* label/*=nullptr*/,
										bool isStatic/*=false*/)
{
	RETURN_FALSE_IF_EMPTY(text);
	outSize = restrictSize;
	WHeapString outString;
	ExpandSingleLine(font, text, outString, outSize.Width);
	outSize.Height = (float)font.LineHeight();

	ReserveMesh(outMeshes, text);

	LayoutSingleLineMesh(outMeshes, font, outSize, outSize.Width, outString, alignment, restrictSize, label);
	ShrinkMesh(outMeshes);
	return true;
}

bool TextLayouter::WordWrapWithWidth(List<WHeapString>& outLines, List<float>& outLineWidths, float& outMaxWidth, IFont& font, const WStringRef& text, float restrictWidth)
{
	RETURN_FALSE_IF_EMPTY(text);
	outMaxWidth = 0;

	/*
	items begins with "ok", record the offset can break line according to "Unicode Line Breaking Algorithm". 
	items begins with "fit", record the line width,the max pos that can allow chars
	

	for each char width array, add char width to w
	then compare w to width limit that passed in
	when w < width limit, will update items that begins with "fit"
	after updated,check if it's the fit break line pos according to "Unicode Line Breaking Algorithm"
	if yes,update "ok" items .
	if w> width limit, output current line datas.

	*/

	uint textLength = static_cast<uint>(text.Length());

	uint okBegin = 0;
	float okWidth = 0;

	float fitWidth = 0;

	outLines.Append(WHeapString::Empty);
	WHeapString* line = &outLines.Last();
	float lineWidth = 0;


	for (uint i = 0; i < textLength; ++i)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
			{
				//force to break line
				//add left chars to cur line
				line->Append(text.c_str() + okBegin, i - okBegin);	//ignore '\n'
				okWidth += fitWidth;
				lineWidth += okWidth;
				outLineWidths.Add(lineWidth);
				outMaxWidth = Math::Max(outMaxWidth, lineWidth);

				outLines.Append(WHeapString::Empty);
				line = &outLines.Last();

				lineWidth = 0;
				fitWidth = 0;
				okWidth = 0;
				okBegin = i + 1;
			}
			break;
			case L'\t':
			{
				//add left chars to line
				line->Append(text.c_str() + okBegin, i - okBegin);	//ignore '\t'
				okWidth += fitWidth;
				lineWidth += okWidth;
				okBegin = i + 1;
				fitWidth = 0;
				okWidth = 0;

				//try to expand tab
				float spaceWidth = (float)font.SpaceWidth();
				float copyFitWidth = fitWidth;

				size_t spaceCount = 0;
				size_t planSpaceCount = TabWidth - line->Length() % TabWidth;

				FOR_EACH_SIZE(j, planSpaceCount)
				{
					copyFitWidth += spaceWidth;
					if (copyFitWidth > restrictWidth)
					{
						spaceCount = j;
						break;
					}
				}

				//add left chars
				if (spaceCount == 0)	//can add all spaces
				{
					line->Append(L' ', planSpaceCount);
					lineWidth += planSpaceCount*spaceWidth;
				}
				else
				{
					//add some spaces
					line->Append(L' ', spaceCount);

					lineWidth += spaceCount*spaceWidth;

					//have to break line
					outLineWidths.Add(lineWidth);
					outMaxWidth = Math::Max(outMaxWidth, lineWidth);

					outLines.Append(WHeapString::Empty);
					line = &outLines.Last();

					lineWidth = 0;
				}

			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
			{
				float charWidth = GetCharWidth(font, c);
				fitWidth += charWidth;
				if (fitWidth < restrictWidth)
				{
					if (IsLineBreak(text, i))
					{
						//safe to add current ok chars to line
						line->Append(text.c_str() + okBegin, i - okBegin + 1);
						okWidth += fitWidth;
						lineWidth += okWidth;
						okWidth = 0;
						okBegin = i + 1;
						fitWidth = 0;
					}
					else
					{
						//do nothing
					}
				}
				else
				{
					//have to break line
					//cur line is enough
					okWidth += fitWidth - charWidth;
					lineWidth += okWidth;
					outLineWidths.Add(lineWidth);
					outMaxWidth = Math::Max(outMaxWidth, lineWidth);

					outLines.Append(WHeapString::Empty);
					line = &outLines.Last();


					line->Append(text.c_str() + okBegin, i - okBegin + 1);
					fitWidth = charWidth;
					okWidth = charWidth;

					okBegin = i + 1;
					lineWidth = 0;

					// generate next line

					//add left chars to next line
				}
			}

			break;
		}
	}

	//add left line
	okWidth += fitWidth;
	lineWidth += okWidth;
	outLineWidths.Add(lineWidth);
	outMaxWidth = Math::Max(outMaxWidth, lineWidth);
	//lineWidth = 0;

	if (okBegin < textLength)
	{
		line->Append(text.c_str() + okBegin, textLength - okBegin);
	}

	if (line->IsEmpty())	//if last line is empty
	{
		outLines.RemoveLast();
	}

	Log::Assert(outLines.Count() == outLineWidths.Count(), "Error result");

	return !outLines.IsEmpty();
}

bool TextLayouter::WordWrap(List<WHeapString>& outLines, List<float>& outLineWidths, float& outMaxWidth, IFont& font, const WStringRef& text)
{
	outMaxWidth = 0;
	outLines.Append(WHeapString::Empty);
	WHeapString* line = &outLines.Last();

	uint textLength = static_cast<uint>(text.Length());
	outLineWidths.Add(0);
	float* lineWidth = &outLineWidths.Last();


	FOR_EACH_SIZE(i, textLength)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
				outLines.Append(WHeapString::Empty);
				line = &outLines.Last();
				outLineWidths.Add(0);
				lineWidth = &outLineWidths.Last();
				break;
			case L'\t':
			{
				uint spaceCount = TabWidth - line->Length() % TabWidth;
				line->Append(L' ', spaceCount);
				*lineWidth += spaceCount*font.SpaceWidth();
			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
				line->Append(c);
				*lineWidth += GetCharWidth(font, c);
				break;
		}
	}

	FOR_EACH_COLLECTION(i, outLineWidths)
	{
		outMaxWidth = Math::Max(outMaxWidth, *i);
	}

	return !outLines.IsEmpty();
}

void TextLayouter::LayoutMultipleLineMesh(List<BaseFontMesh*>& outMeshes,
										  IFont& font,
										  const Size2F& imageSize,
										  const List<float>& lineWidths,
										  const List<WHeapString>& lines,
										  Alignment alignment,
										  const Size2F& restrictSize,
										  ILabel* label/*=nullptr*/,
										  bool isStatic/*=false*/)
{

	/**
	* Returns true if the specified character is one of those specified
	* as being Ideographic (class ID) by the Unicode Line Breaking Algorithm
	* (http://www.unicode.org/unicode/reports/tr14/), and is therefore OK
	* to break between a pair of.
	*
	* @param includeNonStarters also return true for category NS
	*                           (non-starters), which can be broken
	*                           after but not before.
	*/

	uint lineCount = static_cast<uint>(lines.Count());
	Point3F origin = Point3F::Zero;

	bool hasKerning = font.HasKerning();
	Size2F validRestrictSize = restrictSize;
	if (validRestrictSize.Height == 0)
	{
		validRestrictSize.Height = (float)(lineCount*font.LineHeight());
	}

	if (hasKerning)
	{
		FOR_EACH_SIZE(i, lineCount)
		{
			const WHeapString& line = lines[i];
			uint lineLength = static_cast<uint>(line.Length());
			float lineWidth = lineWidths[i];
			if (restrictSize.Width == 0)
			{
				validRestrictSize.Width = lineWidth;
			}

			origin = GetPenOrigin((uint)i, lineCount, lineWidth, (float)font.LineHeight(), alignment, validRestrictSize);

			FOR_EACH_SIZE(j, lineLength)
			{
				wchar_t c = line[j];
				const FontChar* fontChar = GetChar(font, c);
				Log::AssertNotNull(fontChar, "fontChar");
				AddCharToMesh(outMeshes, font, *fontChar, origin, label, isStatic);
				if (hasKerning&&j != 0)
				{
					Point3F nextPen = origin;
					const FontKerning* kerning = font.TryLoadKerning(line[j - 1], c);
					if (kerning != nullptr)
					{
						nextPen.X += kerning->Offset;
					}
					nextPen.X += fontChar->HAdvance;

					origin.X = Math::Max(origin.X, nextPen.X);	//avoid the "sliding dot" problem 
				}
				else
				{
					origin.X += fontChar->HAdvance;
				}

			}
		}
	}
	else
	{
		FOR_EACH_SIZE(i, lineCount)
		{
			const WHeapString& line = lines[i];
			uint lineLength = static_cast<uint>(line.Length());
			float lineWidth = lineWidths[i];
			if (restrictSize.Width == 0)
			{
				validRestrictSize.Width = lineWidth;
			}

			origin = GetPenOrigin((uint)i, lineCount, lineWidth, (float)font.LineHeight(), alignment, validRestrictSize);

			FOR_EACH_SIZE(j, lineLength)
			{
				wchar_t c = line[j];
				const FontChar* fontChar = GetChar(font, c);
				Log::AssertNotNull(fontChar, "fontChar");
				AddCharToMesh(outMeshes, font, *fontChar, origin, label, isStatic);
				origin.X += fontChar->HAdvance;
			}
		}
	}
}



void TextLayouter::LayoutSingleLineMesh(List<BaseFontMesh*>& outMeshes,
										IFont& font,
										const Size2F& imageSize,
										float lineWidth,
										const WStringRef& line,
										Alignment alignment,
										const Size2F& restrictSize,
										ILabel* label/*=nullptr*/,
										bool isStatic/*=false*/)
{
	Point3F origin = Point3F::Zero;
	bool hasKerning = font.HasKerning();
	Size2F validRestrictSize = restrictSize;
	if (validRestrictSize.Height == 0)
	{
		validRestrictSize.Height = (float)font.LineHeight();
	}
	if (validRestrictSize.Width == 0)
	{
		validRestrictSize.Width = lineWidth;
	}

	if (hasKerning)
	{

		uint lineLength = static_cast<uint>(line.Length());
		origin = GetPenOrigin(0, 1, lineWidth, (float)font.LineHeight(), alignment, validRestrictSize);

		FOR_EACH_SIZE(j, lineLength)
		{
			wchar_t c = line[j];
			const FontChar* fontChar = GetChar(font, c);
			Log::AssertNotNull(fontChar, "fontChar");
			AddCharToMesh(outMeshes, font, *fontChar, origin, label, isStatic);
			if (hasKerning&&j != 0)
			{
				Point3F nextPen = origin;
				const FontKerning* kerning = font.TryLoadKerning(line[j - 1], c);
				if (kerning != nullptr)
				{
					nextPen.X += kerning->Offset;
				}
				nextPen.X += fontChar->HAdvance;

				origin.X = Math::Max(origin.X, nextPen.X);	//avoid the "sliding dot" problem 
			}
			else
			{
				origin.X += fontChar->HAdvance;
			}

		}
	}
	else
	{
		uint lineLength = static_cast<uint>(line.Length());
		origin = GetPenOrigin(0, 1, lineWidth, (float)font.LineHeight(), alignment, validRestrictSize);

		FOR_EACH_SIZE(j, lineLength)
		{
			wchar_t c = line[j];

			const FontChar* fontChar = GetChar(font, c);
			Log::AssertNotNull(fontChar, "fontChar");
			AddCharToMesh(outMeshes, font, *fontChar, origin, label, isStatic);
			origin.X += fontChar->HAdvance;
		}
	}
}


void TextLayouter::AddCharToMesh(List<BaseFontMesh*>& outMeshes, IFont& font, const FontChar& fontChar, const Point3F& origin, ILabel* label/*=nullptr*/, bool isStatic/*=false*/)
{
	RETURN_IF_NULL(fontChar.Material());

	if (StdString::ConstValues<wchar_t>::IsEmptyChar(fontChar.Id))
	{
		return;
	}

	BaseFontMesh* mesh = nullptr;
	if (outMeshes.Count() == 1 && outMeshes.First()->Material() == fontChar.Material())
	{
		mesh = outMeshes.First();
	}
	else
	{
		//Because one font won't contains many material, so it's ok here.
		FOR_EACH_COLLECTION(i, outMeshes)
		{
			BaseFontMesh* item = *i;
			if (item->Material() == fontChar.Material())
			{
				mesh = item;
				break;
			}
		}
	}

	if (mesh == nullptr)
	{
		//still cannot find the mesh, try create a new mesh in label
		mesh = label->CreateFontMesh(fontChar.Material(), isStatic);
	}

	Log::AssertNotNull(mesh, "Mesh");
	mesh->AddFontChar(font, fontChar, origin);
}


Point2F TextLayouter::GetPenOrigin(uint lineIndex, uint lineCount, float lineWidth, float lineHeight, Alignment alignment, const Size2F& restrictSize)
{
	if (restrictSize.Height < lineCount*lineHeight)
	{
		return Point2F::Zero;
	}

	Point2F origin;
	switch (alignment)
	{
		case Alignment::LeftBottom:
			origin.Y = (lineCount - lineIndex - 1)*lineHeight;
			origin.X = 0.f;
			break;
		case Alignment::LeftCenter:
			origin.Y = (restrictSize.Height - lineCount*lineHeight) / 2.f + (lineCount - lineIndex - 1)*lineHeight;
			origin.X = 0.f;
			break;
		case Alignment::LeftTop:
			origin.Y = restrictSize.Height - lineHeight*(lineIndex + 1);
			origin.X = 0.f;
			break;
		case Alignment::MiddleBottom:
			origin.Y = (lineCount - lineIndex - 1)*lineHeight;
			origin.X = (restrictSize.Width - lineWidth) / 2.f;
			break;
		case Alignment::MiddleCenter:
			origin.Y = (restrictSize.Height - lineCount*lineHeight) / 2.f + (lineCount - lineIndex - 1)*lineHeight;
			origin.X = (restrictSize.Width - lineWidth) / 2.f;
			break;
		case Alignment::MiddleTop:
			origin.Y = restrictSize.Height - lineHeight*(lineIndex + 1);
			origin.X = (restrictSize.Width - lineWidth) / 2.f;
			break;
		case Alignment::RightBottom:
			origin.Y = (lineCount - lineIndex - 1)*lineHeight;
			origin.X = restrictSize.Width - lineWidth;
			break;
		case Alignment::RightCenter:
			origin.Y = (restrictSize.Height - lineCount*lineHeight) / 2.f + (lineCount - lineIndex - 1)*lineHeight;
			origin.X = restrictSize.Width - lineWidth;
			break;
		case Alignment::RightTop:
			origin.Y = restrictSize.Height - lineHeight*(lineIndex + 1);
			origin.X = restrictSize.Width - lineWidth;
			break;
		default:
			break;
	}

	return origin;

}



bool TextLayouter::ExpandSingleLine(IFont& font, const WStringRef& text, WHeapString& outString, float& outLineWidth)
{
	outString.Clear();
	outLineWidth = 0;
	uint charCount = 0;

	uint textLength = static_cast<uint>(text.Length());

	FOR_EACH_SIZE(i, textLength)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
				break;
			case L'\t':
			{
				uint spaceCount = TabWidth - charCount%TabWidth;
				outLineWidth += spaceCount*font.SpaceWidth();
				charCount += spaceCount;
				outString.Append(L' ', spaceCount);
			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
				++charCount;
				outLineWidth += GetCharWidth(font, c);
				outString.Append(c);
				break;
		}
	}
	return true;
}

bool TextLayouter::IsIdeographic(wchar_t c, bool includeNonStarters)
{
	RETURN_TRUE_IF(c >= L'\u2E80' && c <= L'\u2FFF'); // CJK, KANGXI RADICALS, DESCRIPTION SYMBOLS
	RETURN_TRUE_IF(c == L'\u3000');// IDEOGRAPHIC SPACE

	if (c >= L'\u3040' && c <= L'\u309F')
	{
		if (!includeNonStarters)
		{
			switch (c)
			{
				case L'\u3041': //  # HIRAGANA LETTER SMALL A
				case L'\u3043': //  # HIRAGANA LETTER SMALL I
				case L'\u3045': //  # HIRAGANA LETTER SMALL U
				case L'\u3047': //  # HIRAGANA LETTER SMALL E
				case L'\u3049': //  # HIRAGANA LETTER SMALL O
				case L'\u3063': //  # HIRAGANA LETTER SMALL TU
				case L'\u3083': //  # HIRAGANA LETTER SMALL YA
				case L'\u3085': //  # HIRAGANA LETTER SMALL YU
				case L'\u3087': //  # HIRAGANA LETTER SMALL YO
				case L'\u308E': //  # HIRAGANA LETTER SMALL WA
				case L'\u3095': //  # HIRAGANA LETTER SMALL KA
				case L'\u3096': //  # HIRAGANA LETTER SMALL KE
				case L'\u309B': //  # KATAKANA-HIRAGANA VOICED SOUND MARK
				case L'\u309C': //  # KATAKANA-HIRAGANA SEMI-VOICED SOUND MARK
				case L'\u309D': //  # HIRAGANA ITERATION MARK
				case L'\u309E': //  # HIRAGANA VOICED ITERATION MARK
					return false;
			}
		}
		return true; // Hiragana (except small characters)
	}

	if (c >= L'\u30A0' && c <= L'\u30FF')
	{
		if (!includeNonStarters)
		{
			switch (c)
			{
				case L'\u30A0': //  # KATAKANA-HIRAGANA DOUBLE HYPHEN
				case L'\u30A1': //  # KATAKANA LETTER SMALL A
				case L'\u30A3': //  # KATAKANA LETTER SMALL I
				case L'\u30A5': //  # KATAKANA LETTER SMALL U
				case L'\u30A7': //  # KATAKANA LETTER SMALL E
				case L'\u30A9': //  # KATAKANA LETTER SMALL O
				case L'\u30C3': //  # KATAKANA LETTER SMALL TU
				case L'\u30E3': //  # KATAKANA LETTER SMALL YA
				case L'\u30E5': //  # KATAKANA LETTER SMALL YU
				case L'\u30E7': //  # KATAKANA LETTER SMALL YO
				case L'\u30EE': //  # KATAKANA LETTER SMALL WA
				case L'\u30F5': //  # KATAKANA LETTER SMALL KA
				case L'\u30F6': //  # KATAKANA LETTER SMALL KE
				case L'\u30FB': //  # KATAKANA MIDDLE DOT
				case L'\u30FC': //  # KATAKANA-HIRAGANA PROLONGED SOUND MARK
				case L'\u30FD': //  # KATAKANA ITERATION MARK
				case L'\u30FE': //  # KATAKANA VOICED ITERATION MARK
					return false;
			}
		}
		return true; // Katakana (except small characters)
	}

	RETURN_TRUE_IF(c >= L'\u3400' && c <= L'\u4DB5');	// CJK UNIFIED IDEOGRAPHS EXTENSION A
	RETURN_TRUE_IF(c >= L'\u4E00' && c <= L'\u9FBB');	// CJK UNIFIED IDEOGRAPHS
	RETURN_TRUE_IF(c >= L'\uF900' && c <= L'\uFAD9');	// CJK COMPATIBILITY IDEOGRAPHS
	RETURN_TRUE_IF(c >= L'\uA000' && c <= L'\uA48F');	// YI SYLLABLES
	RETURN_TRUE_IF(c >= L'\uA490' && c <= L'\uA4CF');	// YI RADICALS
	RETURN_TRUE_IF(c >= L'\uFE62' && c <= L'\uFE66');	// SMALL PLUS SIGN to SMALL EQUALS SIGN
	RETURN_TRUE_IF(c >= L'\uFF10' && c <= L'\uFF19');	// WIDE DIGITS

	return false;
}

bool TextLayouter::ExpandTab(const WStringRef& text, WHeapString& outString)
{
	RETURN_FALSE_IF_EMPTY(text);
	if (!text.Contains(StdString::ConstValues<wchar_t>::Tab) || text.Contains(StdString::ConstValues<wchar_t>::LineSeparator))
	{
		Log::AssertFailedFormat(L"Invalid text when ExpandTab.{}", text.c_str());
		return false;
	}

	uint length = static_cast<uint>(text.Length());
	outString.ReserveLength(length);
	FOR_EACH_SIZE(i, length)
	{
		wchar_t c = text[i];
		if (c == StdString::ConstValues<wchar_t>::Tab)
		{
			uint spaceCount = TabWidth - i%TabWidth;
			FOR_EACH_SIZE(j, spaceCount)
			{
				outString.Append(StdString::ConstValues<wchar_t>::Space);
			}
		}
		else
		{
			outString.Append(c);
		}
	}

	return true;
}

float TextLayouter::GetCharWidth(IFont& font, wchar_t c)
{
	const FontChar* fontChar = GetChar(font, c);
	RETURN_ZERO_IF_NULL(fontChar);

	return (float)fontChar->HAdvance;
}

const FontChar* TextLayouter::GetChar(IFont& font, wchar_t c)
{
	if (c == L' ')
	{ 
		return &font.SpaceFontChar();
	}

	const FontChar* fontChar = font.TryLoadChar(c);
	if (fontChar == nullptr || fontChar->Material() == nullptr)
	{
		Log::FormatError(L"Cannot find char:{}", c);
		return nullptr;
	}

	return fontChar;
}

bool TextLayouter::IsLineBreak(const WStringRef& text, uint index)
{
	wchar_t c = text[index];

	bool isSpaceOrTab = StdString::IsSpaceOrTab(c);
	// From the Unicode Line Breaking Algorithm (at least approximately)
	bool isLineBreak = isSpaceOrTab
		// / is class SY and - is class HY, except when followed by a digit
		|| ((c == StdString::ConstValues<wchar_t>::Slash || c == StdString::ConstValues<wchar_t>::Backslash || c == StdString::ConstValues<wchar_t>::Hyphen) && (index >= text.Length() || StdString::IsDigit(text[index + 1])))
		// Ideographs are class ID: breakpoints when adjacent, except for NS
		// (non-starters), which can be broken after but not before
		|| (c >= FirstCJKChar && IsIdeographic(c, true) && index < text.Length() && IsIdeographic(text[index + 1], false));



	return isLineBreak;
}

bool TextLayouter::ReserveMesh(List<BaseFontMesh*>& outMeshes, const WStringRef& text)
{
	if (outMeshes.Count() == 1)
	{
		outMeshes.First()->ReserveMesh((uint)text.Length());
		return true;
	}

	FOR_EACH_COLLECTION(i, outMeshes)
	{
		BaseFontMesh* mesh = *i;
		mesh->ReserveMesh((uint)text.Length());
	}


	return true;
}

bool TextLayouter::ShrinkMesh(List<BaseFontMesh*>& outMeshes)
{
	if (outMeshes.Count() == 1)
	{
		outMeshes.First()->ShrinkMesh();
		return true;
	}

	FOR_EACH_COLLECTION(i, outMeshes)
	{
		BaseFontMesh* mesh = *i;
		mesh->ShrinkMesh();
	}

	return true;
}

Size2F TextLayouter::GetSingleLineSize(IFont& font, const WStringRef& text)
{
	float outLineWidth = 0;
	uint charCount = 0;

	uint textLength = static_cast<uint>(text.Length());

	FOR_EACH_SIZE(i, textLength)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
				break;
			case L'\t':
			{
				uint spaceCount = TabWidth - charCount%TabWidth;
				outLineWidth += spaceCount*font.SpaceWidth();
				charCount += spaceCount;
			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
				++charCount;
				outLineWidth += GetCharWidth(font, c);
				break;
		}
	}
	return Size2F(outLineWidth, (float)font.LineHeight());
}

Size2F TextLayouter::GetMultipleLineSize(IFont& font, const WStringRef& text, const Size2F& restrictSize/*=Size2F::Zero*/)
{
	if (restrictSize.Width != 0)
	{
		return GetMultipleLineSizeHelperWithWidth(font, text, restrictSize.Width);
	}
	else
	{
		return GetMultipleLineSizeHelper(font, text);
	}

}

Size2F TextLayouter::GetMultipleLineSizeHelper(IFont& font, const WStringRef& text)
{
	Size2F resultSize = Size2F::Zero;
	if (text.IsEmpty())
	{
		return resultSize;
	}

	uint charCount = 0;
	uint lineCount = 1;

	uint textLength = static_cast<uint>(text.Length());
	float lineWidth = 0;


	FOR_EACH_SIZE(i, textLength)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
				resultSize.Width = Math::Max(resultSize.Width, lineWidth);
				lineWidth = 0;
				++lineCount;
				charCount = 0;
				break;
			case L'\t':
			{
				uint spaceCount = TabWidth - charCount%TabWidth;
				lineWidth += spaceCount*font.SpaceWidth();
			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
				++charCount;
				lineWidth += GetCharWidth(font, c);
				break;
		}
	}
	if (charCount == 0)
	{
		--lineCount;	//remove empty line
	}

	resultSize.Width = Math::Max(resultSize.Width, lineWidth);
	resultSize.Height = (float)(lineCount*font.LineHeight());
	return resultSize;
}

Size2F TextLayouter::GetMultipleLineSizeHelperWithWidth(IFont& font, const WStringRef& text, float restrictWidth)
{
	if (text.IsEmpty())
	{
		return Size2F::Zero;
	}
	float outMaxWidth = 0;
	size_t textLength = text.Length();

	size_t okBegin = 0;
	float okWidth = 0;

	float fitWidth = 0;

	float lineWidth = 0;
	size_t lineCount = 1;
	size_t charCount = 0;

	for (uint i = 0; i < textLength; ++i)
	{
		wchar c = text[i];
		switch (c)
		{
			case L'\n':
			{
				//force to break line
				//add left chars to cur line
				okWidth += fitWidth;
				lineWidth += okWidth;
				outMaxWidth = Math::Max(outMaxWidth, lineWidth);

				charCount = 0;

				lineWidth = 0;
				fitWidth = 0;
				okWidth = 0;
				okBegin = i + 1;
				++lineCount;
			}
			break;
			case L'\t':
			{
				//add left chars to line
				charCount += i - okBegin;//ignore '\t'

				okWidth += fitWidth;
				lineWidth += okWidth;
				okBegin = i + 1;
				fitWidth = 0;
				okWidth = 0;

				//try to expand tab
				float spaceWidth =(float) font.SpaceWidth();
				float copyFitWidth = fitWidth;

				size_t spaceCount = 0;
				size_t planSpaceCount = TabWidth - charCount%TabWidth;

				FOR_EACH_SIZE(j, planSpaceCount)
				{
					copyFitWidth += spaceWidth;
					if (copyFitWidth > restrictWidth)
					{
						spaceCount = j;
						break;
					}
				}

				//add left chars
				if (spaceCount == 0)	//can add all spaces
				{
					charCount += planSpaceCount;
					lineWidth += planSpaceCount*spaceWidth;
				}
				else
				{
					lineWidth += spaceCount*spaceWidth;

					//have to break line
					outMaxWidth = Math::Max(outMaxWidth, lineWidth);

					charCount = 0;
					lineWidth = 0;
					fitWidth = 0;
					++lineCount;
				}

			}
			break;
			case L'\r':
			case L'\f':
			case L'\v':
				//ignore
				break;
			default:
			{
				float charWidth = GetCharWidth(font, c);
				fitWidth += charWidth;
				if (fitWidth < restrictWidth)
				{
					if (IsLineBreak(text, i))
					{
						//safe to add current ok chars to line
						charCount += i - okBegin + 1;
						okWidth += fitWidth;
						lineWidth += okWidth;
						okWidth = 0;
						okBegin = i + 1;
						fitWidth = 0;
					}
					else
					{
						//do nothing
					}
				}
				else
				{
					//have to break line
					//cur line is enough
					okWidth += fitWidth - charWidth;
					lineWidth += okWidth;
					outMaxWidth = Math::Max(outMaxWidth, lineWidth);

					charCount = i - okBegin + 1;
					okWidth = charWidth;
					fitWidth = charWidth;
					okBegin = i + 1;
					lineWidth = 0;
					++lineCount;

					// generate next line

					//add left chars to next line
				}
			}

			break;
		}
	}

	//add left line
	okWidth += fitWidth;
	lineWidth += okWidth;
	outMaxWidth = Math::Max(outMaxWidth, lineWidth);
	//lineWidth = 0;

	if (okBegin < textLength)
	{
		charCount += textLength - okBegin + 1;
	}

	if (charCount == 0)	//if last line is empty
	{
		--lineCount;
	}

	return Size2F(outMaxWidth, (float)(lineCount*font.LineHeight()));
}

MEDUSA_END;
