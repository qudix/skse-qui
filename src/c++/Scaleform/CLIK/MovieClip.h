#pragma once

#include "Scaleform/CLIK/Object.h"

namespace CLIK
{
	class MovieClip :
		public Object
	{
	private:
		using super = Object;

	public:
		MovieClip() = default;
		MovieClip(const MovieClip&) = default;
		MovieClip(MovieClip&&) = default;
		using super::super;

		MovieClip(const super& a_rhs) :
			super(a_rhs)
		{}

		MovieClip(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		~MovieClip() = default;

		MovieClip& operator=(const MovieClip&) = default;
		MovieClip& operator=(MovieClip&&) = default;
		using super::operator=;

		MovieClip& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		MovieClip& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

		// properties
		double Alpha() const { return GetNumber("_alpha"); }
		void Alpha(double a_alpha) { SetNumber("_alpha", a_alpha); }

		Object BlendMode() const { return GetObject("blendMode"); }
		void BlendMode(const Object& a_blendMode) { SetObject("blendMode", a_blendMode); }

		bool CacheAsBitmap() const { return GetBoolean("cacheAsBitmap"); }
		void CacheAsBitmap(bool a_cacheAsBitmap) { SetBoolean("cacheAsBitmap", a_cacheAsBitmap); }

		double Currentframe() const { return GetNumber("_currentframe"); }

		std::string Droptarget() const { return GetString("_droptarget"); }

		bool Enabled() const { return GetBoolean("enabled"); }
		void Enabled(bool a_enabled) { SetBoolean("enabled", a_enabled); }

		//Array Filters() const;
		//void Filters(const Array& a_filters);

		bool FocusEnabled() const { return GetBoolean("focusEnabled"); }
		void FocusEnabled(bool a_focusEnabled) { SetBoolean("focusEnabled", a_focusEnabled); }

		bool Focusrect() const { return GetBoolean("_focusrect"); }
		void Focusrect(bool a_focusrect) { SetBoolean("_focusrect", a_focusrect); }

		double Framesloaded() const { return GetNumber("_framesloaded"); }

		double Height() const { return GetNumber("_height"); }
		void Height(double a_height) { SetNumber("_height", a_height); }

		double HighQuality() const { return GetNumber("_highquality"); }
		void HighQuality(double a_highQuality) { SetNumber("_highquality", a_highQuality); }

		Object HitArea() const { return GetObject("hitArea"); }
		void HitArea(const Object& a_hitArea) { SetObject("hitArea", a_hitArea); }

		double LockRoot() const { return GetNumber("_lockroot"); }
		void LockRoot(double a_lockRoot) { SetNumber("_lockroot", a_lockRoot); }

		//ContextMenu Menu() const;
		//void Menu(const ContextMenu& a_menu);

		std::string Name() const { return GetString("_name"); }
		void Name(std::string_view a_name) { SetString("_name", a_name); }

		double OpaqueBackground() const { return GetNumber("opaqueBackground"); }
		void OpaqueBackground(double a_opaqueBackground) { SetNumber("opaqueBackground", a_opaqueBackground); }

		MovieClip Parent() const { return GetObject("_parent"); }
		void Parent(const MovieClip& a_parent) { SetObject("_parent", a_parent); }

		std::string Quality() const { return GetString("_quality"); }
		void Quality(std::string_view a_quality) { SetString("_quality", a_quality); }

		double Rotation() const { return GetNumber("_rotation"); }
		void Rotation(double a_rotation) { SetNumber("_rotation", a_rotation); }

		//Rectangle Scale9Grid() const;
		//void Scale9Grid(const Rectangle& a_scale9Grid) const;

		Object ScrollRect() const { return GetObject("scrollRect"); }
		void ScrollRect(const Object& a_scrollRect) { SetObject("scrollRect", a_scrollRect); }

		double SoundBufTime() const { return GetNumber("_soundbuftime"); }
		void SoundBufTime(double a_soundBufTime) { SetNumber("_soundbuftime", a_soundBufTime); }

		bool TabChildren() const { return GetBoolean("tabChildren"); }
		void TabChildren(bool a_tabChildren) { SetBoolean("tabChildren", a_tabChildren); }

		bool TabEnabled() const { return GetBoolean("tabEnabled"); }
		void TabEnabled(bool a_tabEnabled) { SetBoolean("tabEnabled", a_tabEnabled); }

		double TabIndex() const { return GetNumber("tabIndex"); }
		void TabIndex(double a_tabIndex) { SetNumber("tabIndex", a_tabIndex); }

		std::string Target() const { return GetString("_target"); }

		double TotalFrames() const { return GetNumber("_totalframes"); }

		bool TrackAsMenu() const { return GetBoolean("trackAsMenu"); }
		void TrackAsMenu(bool a_trackAsMenu) { SetBoolean("trackAsMenu", a_trackAsMenu); }

		//Transform Transform() const;
		//void Transform(const Transform& a_transform);

		std::string URL() const { return GetString("_url"); }

		bool UseHandCursor() const { return GetBoolean("useHandCursor"); }
		void UseHandCursor(bool a_useHandCursor) { SetBoolean("useHandCursor", a_useHandCursor); }

		bool Visible() const { return GetBoolean("_visible"); }
		void Visible(bool a_visible) { SetBoolean("_visible", a_visible); }

		double Width() const { return GetNumber("_width"); }
		void Width(double a_width) { SetNumber("_width", a_width); }

		double X() const { return GetNumber("_x"); }
		void X(double a_x) { SetNumber("_x", a_x); }

		double XMouse() const { return GetNumber("_xmouse"); }

		double XScale() const { return GetNumber("_xscale"); }
		void XScale(double a_xScale) { SetNumber("_xscale", a_xScale); }

		double Y() const { return GetNumber("_y"); }
		void Y(double a_y) { SetNumber("_y", a_y); }

		double YMouse() const { return GetNumber("_ymouse"); }

		double YScale() const { return GetNumber("_yscale"); }
		void YScale(double a_yScale) { SetNumber("_yscale", a_yScale); }
	};
}
