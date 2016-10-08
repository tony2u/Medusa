// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"
#ifdef MEDUSA_FREETYPE

#include "TTFFont.h"
#include "Core/IO/FileSystem.h"
#include "Core/Memory/MemoryData.h"
#include "Core/Log/Log.h"
#include "Resource/Font/FontFactory.h"
#include "Resource/TextureAtlas/TextureAtlasRegion.h"
#include "Resource/Material/MaterialFactory.h"
#include "Resource/ResourceNames.h"
#include "Resource/Image/PVRImage.h"
#include "Resource/Image/DynamicAtlasRGBAImage.h"
#include "Resource/Material/IMaterial.h"
#include "Resource/Texture/ImageTexture.h"
#include "Resource/Texture/TextureFactory.h"
#include "Resource/TextureAtlas/TextureAtlas.h"
#include "Resource/TextureAtlas/TextureAtlasPage.h"
#include "Geometry/GeometryFactory.h"

MEDUSA_BEGIN;

bool TTFFont::InitializeLibrary()
{
	if (mLibrary == nullptr)
	{
		FT_Error err = FT_Init_FreeType(&mLibrary);
		if (err)
		{
			Log::Error("Error init freetype");
			return false;
		}
	}
	return true;
}

bool TTFFont::UninitializeLibrary()
{
	if (mLibrary != nullptr)
	{
		FT_Done_FreeType(mLibrary);
		mLibrary = nullptr;
	}
	return true;
}

Share<TTFFont> TTFFont::CreateFromFile(const FontId& fontId)
{
	auto data = FileSystem::Instance().ReadAllData(fontId);
	return CreateFromData(fontId, data);
}


Share<TTFFont> TTFFont::CreateFromData(const FontId& fontId, const MemoryData& data)
{
	Share<TTFFont> font = new TTFFont(fontId);
	if (!font->Initialize(data))
	{
		font = nullptr;
	}

	return font;
}

TTFFont::TTFFont(const FontId& fontId) :IFont(fontId)
{
	mFace = nullptr;
	mInitialImageSize = 1024;
	mMaxImageSize = Render::Instance().GetInteger(GraphicsIntegerName::MaxTextureSize);
}



TTFFont::~TTFFont(void)
{
	if (mStroker != nullptr)
	{
		FT_Stroker_Done(mStroker);
		mStroker = nullptr;
	}

	if (mFace != nullptr)
	{
		FT_Done_Face(mFace);
		mFace = nullptr;
	}
}


bool TTFFont::Initialize(const MemoryData& data)
{
	RETURN_FALSE_IF_FALSE(InitializeLibrary());
	mFontData = data;
	FT_Error err;
	if (!data.IsNull())
	{
		err = FT_New_Memory_Face(mLibrary, data.Data(), (FT_Long)data.ByteSize(), 0, &mFace);
		if (err)
		{
			Log::Error("Error face");
			return false;
		}
	}
	else
	{
		Log::Error("Error face");
		return false;
	}


	//init some face metrics
	mFamilyName = mFace->family_name;
	mStyleName = mFace->style_name;

	mTotalCharCount = (uint)mFace->num_glyphs;
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::HasHorizontal, FT_HAS_HORIZONTAL(mFace) != 0);
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::HasVertical, FT_HAS_VERTICAL(mFace) != 0);
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::HasKerning, FT_HAS_KERNING(mFace) != 0);
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::IsScalable, FT_IS_SCALABLE(mFace) != 0);
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::IsItalic, (mFace->style_flags&FT_STYLE_FLAG_ITALIC) != 0);
	MEDUSA_FLAG_ENABLE(mFlags,FontFlags::IsBold, (mFace->style_flags&FT_STYLE_FLAG_BOLD) != 0);

	err = FT_Select_Charmap(mFace, mEncoding);
	if (err)
	{
		bool isSuccess = false;
		//try to find other encoding
		FOR_EACH_INT32(i, mFace->num_charmaps)
		{
			if (mFace->charmaps[i]->encoding != FT_ENCODING_NONE)
			{
				mEncoding = mFace->charmaps[i]->encoding;
				err = FT_Select_Charmap(mFace, mEncoding);
				isSuccess = (err == 0);
				break;
			}
		}

		if (!isSuccess)
		{
			Log::Error("Cannot select unicode charmap");
			return false;
		}
	}

	OnUpdateFontId();

	return true;
}

intp TTFFont::FontUnitToPixelSize(intp fontUnitSize) const
{
	return (int)mFontId.Size()*fontUnitSize / (int)mFace->units_per_EM;
}

Rect2I TTFFont::BBoxToRect(const FT_BBox& val)
{
	Rect2I result;
	result.Origin.X = FixedPointToPixelSize(val.xMin);
	result.Origin.Y = FixedPointToPixelSize(val.yMin);
	result.Size.Width = FixedPointToPixelSize(val.xMax - val.xMin);
	result.Size.Height = FixedPointToPixelSize(val.yMax - val.yMin);
	return result;
}

bool TTFFont::OnUpdateFontId()
{
	FT_Error err;
	if (mFontId.HasOutline())
	{
		if (mStroker == nullptr)
		{
			err = FT_Stroker_New(mLibrary, &mStroker);
			if (err)
			{
				Log::Error("Error FT_Stroker_New");
				FT_Stroker_Done(mStroker);
				return false;
			}
		}

		FT_Stroker_Set(mStroker, (int)(mFontId.OutlineThickness() * 64), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	}
	else
	{
		if (mStroker != nullptr)
		{
			FT_Stroker_Done(mStroker);
			mStroker = nullptr;
		}
	}



	/*The character widths and heights are specified in 1/64th of points. A point is a physical distance,
	equaling 1/72th of an inch. Normally, it is not equivalent to a pixel.*/
	/*character size is set to 16pt for a 300 * 300dpi*/

	/*err=FT_Set_Char_Size(mFace,0,16*64,300,300);
	if (err)
	{
	Log::LogError("Error char size");
	}*/

	err = FT_Set_Pixel_Sizes(mFace, mFontId.Size(), mFontId.Size());
	if (err)
	{
		Log::Error("Error pixel size");
		return false;
	}

	//int maxPixelsX = ::FT_MulFix((mFace->bbox.xMax - mFace->bbox.xMin), mFace->size->metrics.x_scale);
	//int maxPixelsY = ::FT_MulFix((mFace->bbox.yMax - mFace->bbox.yMin), mFace->size->metrics.y_scale);


	const Matrix2& matrix = mFontId.Matrix();
	//Coefficients of the matrix are otherwise in 16.16 fixed-point units.
	if (matrix != Matrix2::Identity)
	{
		FT_Matrix    ftMatrix;
		ftMatrix.xx = (FT_Fixed)(matrix.A * 0x10000L);
		ftMatrix.xy = (FT_Fixed)(matrix.B * 0x10000L);
		ftMatrix.yx = (FT_Fixed)(matrix.C * 0x10000L);
		ftMatrix.yy = (FT_Fixed)(matrix.D * 0x10000L);
		/* the ftTranslate position in 26.6 cartesian space coordinates */
		FT_Vector ftTranslate;
		ftTranslate.x = (FT_Pos)matrix.X * 64;
		ftTranslate.y = (FT_Pos)matrix.Y * 64;
		FT_Set_Transform(mFace, &ftMatrix, &ftTranslate);
	}

	mAscender = FontUnitToPixelSize(mFace->ascender);
	mDescender = FontUnitToPixelSize(mFace->descender);
	mLineHeight = FontUnitToPixelSize(mFace->height);
	mMaxAdvance.Width = (uint)FontUnitToPixelSize(mFace->max_advance_width);
	mMaxAdvance.Height = (uint)FontUnitToPixelSize(mFace->max_advance_height);
	mUnderlinePosition = FontUnitToPixelSize(mFace->underline_position);
	if (mUnderlinePosition > -2)
	{
		mUnderlinePosition = -2;
	}

	mUnderlineTickness = FontUnitToPixelSize(mFace->underline_thickness);
	if (mUnderlineTickness < 1)
	{
		mUnderlineTickness = 1;
	}


	//update load flags

	if (mFontId.HasLCDFiltering())
	{
		if (mFontId.LCDFilterType() == FontLCDFilterType::Light)
		{
			FT_Library_SetLcdFilter(mLibrary, FT_LCD_FILTER_LIGHT);
			FT_Library_SetLcdFilterWeights(mLibrary, (byte*)FontId::LightLCDFilter);
		}
		else
		{
			FT_Library_SetLcdFilter(mLibrary, FT_LCD_FILTER_DEFAULT);
			FT_Library_SetLcdFilterWeights(mLibrary, (byte*)FontId::DefaultLCDFilter);
		}

	}
	else
	{
		//FT_Library_SetLcdFilter(mLibrary, FT_LCD_FILTER_NONE);
	}

	mSpaceFontChar = OnLoadChar(' ');

	return true;

}


FT_UInt32 TTFFont::GetGlyphLoadFlags(bool outline/*=false*/, bool hinting/*=false*/, bool lcdFiltering/*=false*/) const
{
	FT_UInt32 glyphLoadFlags = 0;

	if (outline)
	{
		glyphLoadFlags |= FT_LOAD_NO_BITMAP;
	}
	else
	{
		glyphLoadFlags |= FT_LOAD_RENDER;
	}

	if (hinting)
	{
		glyphLoadFlags |= FT_LOAD_FORCE_AUTOHINT;
	}
	else
	{
		glyphLoadFlags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT;
	}

	if (lcdFiltering)
	{
		glyphLoadFlags |= FT_LOAD_TARGET_LCD;
	}

	return glyphLoadFlags;
}

const FontChar* TTFFont::OnLoadChar(wchar_t c)
{
	auto glyphLoadFlags = GetGlyphLoadFlags();

	FT_UInt glyphIndex = FT_Get_Char_Index(mFace, c);
	FT_Error err = FT_Load_Glyph(mFace, glyphIndex, glyphLoadFlags);

	if (err)
	{
		Log::Error("Error FT_Load_Glyph");
		return nullptr;
	}



	std::unique_ptr<FontChar> fontChar(new FontChar(c));
	/*    metrics           :: The metrics of the last loaded glyph in the   */
	/*                         slot.  The returned values depend on the last */
	/*                         load flags (see the @FT_Load_Glyph API        */
	/*                         function) and can be expressed either in 26.6 */
	/*                         fractional pixels or font units.              */
	/*                                                                       */
	/*                         Note that even when the glyph image is        */
	/*                         transformed, the metrics are not.             */

	FT_GlyphSlot slot = mFace->glyph;
	fontChar->HAdvance = (ushort)FixedPointToPixelSize(slot->advance.x);
	fontChar->VAdvance = (ushort)FixedPointToPixelSize(slot->advance.y);
	fontChar->HBearing.X = slot->bitmap_left;
	fontChar->HBearing.Y = slot->bitmap_top;

	if (slot->bitmap.width == 0 || slot->bitmap.rows == 0)
	{
		//empty char
		fontChar->HBearing.X = slot->bitmap_left;
		fontChar->HBearing.Y = slot->bitmap_top;
	}
	else
	{
		if (!mFontId.HasOutline())
		{
			fontChar->HBearing.X = slot->bitmap_left;
			fontChar->HBearing.Y = slot->bitmap_top;

			// We want each glyph to be separated by at least one black pixel,but font factory already has spacing 1

			Size2U gylphSize(slot->bitmap.width + 1, slot->bitmap.rows + 1);
			auto* region = AddGlyphImage(c, PixelType::A8, gylphSize, slot->bitmap.pitch, MemoryData::FromStatic(slot->bitmap.buffer, 0), PixelType::A8);
			if (region == nullptr)
			{
				return nullptr;
			}
			fontChar->SetRegion(region);
		}
		else
		{
			FT_BitmapGlyph originalBitmapGlyph = nullptr;
			FT_Glyph outlineGlyph = nullptr;

			do
			{
				//copy original bitmap
				err = FT_Get_Glyph(slot, (FT_Glyph*)&originalBitmapGlyph);
				if (err)
				{
					Log::Error("Error FT_Get_Glyph");
					return nullptr;
				}

				FT_BBox originalBox;
				FT_Glyph_Get_CBox(*(FT_Glyph*)&originalBitmapGlyph, FT_GLYPH_BBOX_GRIDFIT, &originalBox);

				//load new outline char
				glyphLoadFlags = GetGlyphLoadFlags(true);
				err = FT_Load_Glyph(mFace, glyphIndex, glyphLoadFlags);
				if (err)
				{
					Log::Error("Error FT_Load_Glyph");
					break;
				}
				slot = mFace->glyph;
				if (slot->format != FT_GLYPH_FORMAT_OUTLINE)
				{
					Log::Error("Error FT_Load_Glyph outline");
					break;
				}

				err = FT_Get_Glyph(slot, (FT_Glyph*)&outlineGlyph);
				if (err)
				{
					Log::Error("Error FT_Get_Glyph");
					break;
				}

				if (mFontId.OutlineType() == FontOutlineType::Line)
				{
					err = FT_Glyph_Stroke((FT_Glyph*)&outlineGlyph, mStroker, 1);
				}
				else if (mFontId.OutlineType() == FontOutlineType::Inner)
				{
					err = FT_Glyph_StrokeBorder((FT_Glyph*)&outlineGlyph, mStroker, 1, 1);
				}
				else if (mFontId.OutlineType() == FontOutlineType::Outer)
				{
					err = FT_Glyph_StrokeBorder((FT_Glyph*)&outlineGlyph, mStroker, 0, 1);
				}

				if (err)
				{
					Log::Error("Error FT_Glyph_Stroke");
					break;
				}
				if (outlineGlyph->format != FT_GLYPH_FORMAT_OUTLINE)
				{
					Log::Error("Error FT_Load_Glyph outline");
					break;
				}
				FT_Outline *outline = &reinterpret_cast<FT_OutlineGlyph>(outlineGlyph)->outline;
				FT_BBox outlineBox;
				FT_Glyph_Get_CBox(outlineGlyph, FT_GLYPH_BBOX_GRIDFIT, &outlineBox);
				auto width = FixedPointToPixelSize(outlineBox.xMax - outlineBox.xMin);
				auto rows = FixedPointToPixelSize(outlineBox.yMax - outlineBox.yMin);

				FT_Bitmap bmp;
				bmp.buffer = new byte[width * rows];
				memset(bmp.buffer, 0, width * rows);
				bmp.width = (int)width;
				bmp.rows = (int)rows;
				bmp.pitch = (int)width;
				bmp.pixel_mode = FT_PIXEL_MODE_GRAY;
				bmp.num_grays = 256;

				FT_Raster_Params params;
				memset(&params, 0, sizeof(params));
				params.source = outline;
				params.target = &bmp;
				params.flags = FT_RASTER_FLAG_AA;
				FT_Outline_Translate(outline, -outlineBox.xMin, -outlineBox.yMin);
				FT_Outline_Render(mLibrary, outline, &params);

				//blend 2 bitmaps
				originalBitmapGlyph->bitmap.rows;
				Rect2I originalRect = BBoxToRect(originalBox);
				Rect2I outlineRect = BBoxToRect(outlineBox);
				Rect2I blendRect = Rect2I::Union(originalRect, outlineRect);
				MemoryData blendImageData = MemoryData::AllocZero(blendRect.Area() * 2);//IA
				byte* blendImage = (byte*)blendImageData.MutableData();

				//expand original image to blend
				//align images at left-bottom
				auto blendDeltaX = originalRect.Left() - blendRect.Left();
				auto blendDeltaY = blendRect.Top() - originalRect.Top();

				FOR_EACH_INT32(x, originalRect.Width())
				{
					FOR_EACH_INT32(y, originalRect.Height())
					{
						auto blendIndex = (blendDeltaX + x) + (blendDeltaY + y)*blendRect.Width();
						auto originalIndex = x + y*originalRect.Width();
						auto alpha = originalBitmapGlyph->bitmap.buffer[originalIndex];
						blendImage[2 * blendIndex+1] = alpha;	//text alpha at a
					}
				}

				blendDeltaX = outlineRect.Left() - blendRect.Left();
				blendDeltaY = blendRect.Top() - outlineRect.Top();
				FOR_EACH_INT32(x, outlineRect.Width())
				{
					FOR_EACH_INT32(y, outlineRect.Height())
					{
						auto blendIndex = (blendDeltaX + x) + (blendDeltaY + y)*blendRect.Width();
						auto originalIndex = x + y*outlineRect.Width();
						auto alpha = bmp.buffer[originalIndex];
						blendImage[2 * blendIndex] = alpha;	//text alpha at i(r)
					}
				}

				fontChar->HBearing.X -=2*(originalRect.Left()- blendRect.Left());
				fontChar->HBearing.Y +=(blendRect.Top()-originalRect.Top());

				// We want each glyph to be separated by at least one black pixel,but font factory already has spacing 1
				Size2U gylphSize(blendRect.Width() + 1, blendRect.Height() + 1);
				
				auto* region = AddGlyphImage(c, PixelType::IA88, gylphSize, blendRect.Width() * 2, blendImageData, PixelType::IA88);
				if (region == nullptr)
				{
					break;
				}
				fontChar->SetRegion(region);

				SAFE_FREE(bmp.buffer);
			} while (0);

			if (originalBitmapGlyph != nullptr)
			{
				FT_Done_Glyph((FT_Glyph)originalBitmapGlyph);
			}

			if (outlineGlyph != nullptr)
			{
				FT_Done_Glyph((FT_Glyph)outlineGlyph);
			}

		}
	}


	mChars.Add(fontChar->Id, fontChar.get());

	return fontChar.release();
}

const FontKerning* TTFFont::OnLoadKerning(int prev, int next)
{
	FT_UInt leftGlyph = FT_Get_Char_Index(mFace, prev);
	FT_UInt rightGlyph = FT_Get_Char_Index(mFace, next);
	FT_Vector outKerning;
	FT_Get_Kerning(mFace, leftGlyph, rightGlyph, FT_KERNING_DEFAULT, &outKerning);
	if (outKerning.x != 0)
	{
		outKerning.x = (FT_Pos)FixedPointToPixelSize(outKerning.x);
		FontKerning* kerning = new FontKerning(prev, next, (int)outKerning.x);
		uint64 id = ((uint64)prev << 32) | ((uint64)next);
		mKernings.Add(id, kerning);
		return kerning;
	}

	return nullptr;
}

uint TTFFont::Preload(const WStringRef& str)
{
	RETURN_ZERO_IF_EMPTY(str);
	uint count = 0;
	size_t length = str.Length();
	FOR_EACH_SIZE(i, length)
	{
		wchar_t c = str[i];
		if (OnLoadChar(c) != nullptr)
		{
			++count;
		}
	}

	return count;
}


TextureAtlasRegion* TTFFont::AddGlyphImage(wchar_t c, PixelType destPixelType, const Size2U& size, int pitch, const MemoryData& imageData, PixelType srcPixelType)
{
	RETURN_NULL_IF(size > mMaxImageSize);

	Rect2U outRect = Rect2U::Zero;

	auto& pages = mAtlas->Pages();
	for (auto* page : pages)
	{
		auto image = page->GetTexture()->Image().CastPtr<DynamicAtlasRGBAImage>();
		if (image->AddImageRect(size, pitch, imageData, srcPixelType, outRect, true, GraphicsPixelConvertMode::Normal))
		{
			page->SetPageSize(image->Size());

			TextureAtlasRegion* region = new TextureAtlasRegion();
			region->SetId(c);
			region->SetTextureRect(outRect);
			page->AddRegion(region);
			page->GetTexture()->SetLoaded(false);	//re upload texture
			return region;
		}
	}

	FileId imageFileId = mAtlas->GetFileId();
	imageFileId.Name.AppendFormat("@{}", mAtlas->PageCount());

	//at this time all current material is full, add a new image
	Share<DynamicAtlasRGBAImage> image = new DynamicAtlasRGBAImage(imageFileId, mInitialImageSize, mMaxImageSize, destPixelType, false);
	Share<ImageTexture> texture = new ImageTexture(imageFileId, image, ShaderSamplerNames::Texture, GraphicsTextureUnits::Texture0);
	texture->ResetDefaultParameters();

	TextureAtlasPage* page = new TextureAtlasPage(mAtlas->PageCount());
	page->SetTexture(texture);
	mAtlas->AddPage(page);

	if (image->AddImageRect(size, pitch, imageData, srcPixelType, outRect, true, GraphicsPixelConvertMode::Normal))
	{
		page->SetPageSize(image->Size());

		TextureAtlasRegion* region = new TextureAtlasRegion();
		region->SetId(c);
		region->SetTextureRect(outRect);
		page->AddRegion(region);
		texture->SetLoaded(false);	//re upload texture

		return region;
	}
	return nullptr;
}



FT_Library TTFFont::mLibrary = nullptr;


MEDUSA_END;

#endif
