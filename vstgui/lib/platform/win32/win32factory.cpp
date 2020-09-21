// This file is part of VSTGUI. It is subject to the license terms
// in the LICENSE file found in the top-level directory of this
// distribution and at http://github.com/steinbergmedia/vstgui/LICENSE

#include "../iplatformbitmap.h"
#include "../iplatformfont.h"
#include "../iplatformframe.h"
#include "../iplatformframecallback.h"
#include "../iplatformresourceinputstream.h"
#include "../iplatformstring.h"
#include "../iplatformtimer.h"
#include "win32factory.h"
#include <list>
#include <memory>

//-----------------------------------------------------------------------------
namespace VSTGUI {

//-----------------------------------------------------------------------------
uint64_t Win32Factory::getTicks () const noexcept
{
	return IPlatformFrame::getTicks ();
}

//-----------------------------------------------------------------------------
PlatformFramePtr Win32Factory::createFrame (IPlatformFrameCallback* frame, const CRect& size,
                                            void* parent, PlatformType parentType,
                                            IPlatformFrameConfig* config) const noexcept
{
	return owned (IPlatformFrame::createPlatformFrame (frame, size, parent, parentType, config));
}

//-----------------------------------------------------------------------------
PlatformFontPtr Win32Factory::createFont (const UTF8String& name, const CCoord& size,
                                          const int32_t& style) const noexcept
{
	return IPlatformFont::create (name, size, style);
}

//-----------------------------------------------------------------------------
bool Win32Factory::getAllFontFamilies (const FontFamilyCallback& callback) const noexcept
{
	std::list<std::string> names;
	if (IPlatformFont::getAllPlatformFontFamilies (names))
	{
		for (const auto& n : names)
		{
			if (!callback (n))
				break;
		}
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
PlatformBitmapPtr Win32Factory::createBitmap (const CPoint& size) const noexcept
{
	return IPlatformBitmap::create (&const_cast<CPoint&> (size));
}

//-----------------------------------------------------------------------------
PlatformBitmapPtr Win32Factory::createBitmap (const CResourceDescription& desc) const noexcept
{
	if (auto bitmap = IPlatformBitmap::create ())
	{
		if (bitmap->load (desc))
			return bitmap;
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
PlatformBitmapPtr Win32Factory::createBitmapFromPath (UTF8StringPtr absolutePath) const noexcept
{
	return IPlatformBitmap::createFromPath (absolutePath);
}

//-----------------------------------------------------------------------------
PlatformBitmapPtr Win32Factory::createBitmapFromMemory (const void* ptr, uint32_t memSize) const
    noexcept
{
	return IPlatformBitmap::createFromMemory (ptr, memSize);
}

//-----------------------------------------------------------------------------
PNGBitmapBuffer Win32Factory::createBitmapMemoryPNGRepresentation (
    const PlatformBitmapPtr& bitmap) const noexcept
{
	return IPlatformBitmap::createMemoryPNGRepresentation (bitmap);
}

//-----------------------------------------------------------------------------
PlatformResourceInputStreamPtr Win32Factory::createResourceInputStream (
    const CResourceDescription& desc) const noexcept
{
	return IPlatformResourceInputStream::create (desc);
}

//-----------------------------------------------------------------------------
PlatformStringPtr Win32Factory::createString (UTF8StringPtr utf8String) const noexcept
{
	return IPlatformString::createWithUTF8String (utf8String);
}

//-----------------------------------------------------------------------------
PlatformTimerPtr Win32Factory::createTimer (IPlatformTimerCallback* callback) const noexcept
{
	return IPlatformTimer::create (callback);
}

//-----------------------------------------------------------------------------
} // VSTGUI
