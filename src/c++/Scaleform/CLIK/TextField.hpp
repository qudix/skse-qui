#pragma once

#include "Scaleform/CLIK/Object.hpp"

namespace CLIK
{
	class TextField :
		public Object
	{
	private:
		using super = Object;

	public:
		TextField() = default;
		TextField(const TextField&) = default;
		TextField(TextField&&) = default;
		using super::super;

		TextField(const super& a_rhs) :
			super(a_rhs)
		{}

		TextField(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		~TextField() = default;

		TextField& operator=(const TextField&) = default;
		TextField& operator=(TextField&&) = default;
		using super::operator=;

		TextField& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		TextField& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

		// properties
		double Alpha() const { return GetNumber("_alpha"); }
		void Alpha(double a_alpha) { SetNumber("_alpha", a_alpha); }

		std::string AntiAliasType() const { return GetString("antiAliasType"); }
		void AntiAliasType(std::string_view a_antiAliasType) { SetString("antiAliasType", a_antiAliasType); }

		Object AutoSize() const { return GetObject("autoSize"); }
		void AutoSize(const Object& a_autoSize) { SetObject("autoSize", a_autoSize); }

		bool Background() const { return GetBoolean("background"); }
		void Background(bool a_background) { SetBoolean("background", a_background); }

		double BackgroundColor() const { return GetNumber("backgroundColor"); }
		void BackgroundColor(double a_backgroundColor) { SetNumber("backgroundColor", a_backgroundColor); }

		bool Border() const { return GetBoolean("border"); }
		void Border(bool a_border) { SetBoolean("border", a_border); }

		double BorderColor() const { return GetNumber("borderColor"); }
		void BorderColor(double a_borderColor) { SetNumber("borderColor", a_borderColor); }

		double BottomScroll() const { return GetNumber("bottomScroll"); }

		bool CondenseWhite() const { return GetBoolean("condenseWhite"); }
		void CondenseWhite(bool a_condenseWhite) { SetBoolean("condenseWhite", a_condenseWhite); }

		bool EmbedFonts() const { return GetBoolean("embedFonts"); }
		void EmbedFonts(bool a_embedFonts) { SetBoolean("embedFonts", a_embedFonts); }

		//Array Filters() const;
		//void Filters(Array& a_filters);

		std::string GridFitType() const { return GetString("gridFitType"); }
		void GridFitType(std::string_view a_gridFitType) { SetString("gridFitType", a_gridFitType); }

		double Height() const { return GetNumber("_height"); }
		void Height(double a_height) { SetNumber("_height", a_height); }

		double HighQuality() const { return GetNumber("_highquality"); }
		void HighQuality(double a_highQuality) { SetNumber("_highquality", a_highQuality); }

		double HScroll() const { return GetNumber("hscroll"); }
		void HScroll(double a_hscroll) { SetNumber("hscroll", a_hscroll); }

		bool HTML() const { return GetBoolean("html"); }
		void HTML(bool a_html) { SetBoolean("html", a_html); }

		std::string HTMLText() const { return GetString("htmlText"); }
		void HTMLText(std::string_view a_htmlText) { SetString("htmlText", a_htmlText); }

		double Length() const { return GetNumber("length"); }

		double MaxChars() const { return GetNumber("maxChars"); }
		void MaxChars(double a_maxChars) { SetNumber("maxChars", a_maxChars); }

		double MaxHScroll() const { return GetNumber("maxhscroll"); }

		double MaxScroll() const { return GetNumber("maxscroll"); }

		//ContextMenu Menu() const;

		bool MouseWheelEnabled() const { return GetBoolean("mouseWheelEnabled"); }
		void MouseWheelEnabled(bool a_mouseWheelEnabled) { SetBoolean("mouseWheelEnabled", a_mouseWheelEnabled); }

		bool Multiline() const { return GetBoolean("multiline"); }
		void Multiline(bool a_multiline) { SetBoolean("multiline", a_multiline); }

		std::string Name() const { return GetString("_name"); }
		void Name(std::string_view a_name) { SetString("_name", a_name); }

		//MovieClip Parent() const;
		//void Parent(const MovieClip& a_parent);

		bool Password() const { return GetBoolean("password"); }
		void Password(bool a_password) { SetBoolean("password", a_password); }

		std::string Quality() const { return GetString("_quality"); }
		void Quality(std::string_view a_quality) { SetString("_quality", a_quality); }

		std::string Restrict() const { return GetString("restrict"); }
		void Restrict(std::string_view a_restrict) { SetString("restrict", a_restrict); }

		double Rotation() const { return GetNumber("_rotation"); }
		void Rotation(double a_rotation) { SetNumber("_rotation", a_rotation); }

		double Scroll() const { return GetNumber("scroll"); }
		void Scroll(double a_scroll) { SetNumber("scroll", a_scroll); }

		bool Selectable() const { return GetBoolean("selectable"); }
		void Selectable(bool a_selectable) { SetBoolean("selectable", a_selectable); }

		double Sharpness() const { return GetNumber("sharpness"); }
		void Sharpness(double a_sharpness) { SetNumber("sharpness", a_sharpness); }

		double SoundBufTime() const { return GetNumber("_soundbuftime"); }
		void SoundBufTime(double a_soundBufTime) { SetNumber("_soundbuftime", a_soundBufTime); }

		//StyleSheet StyleSheet() const;
		//void StyleSheet(const StyleSheet& a_styleSheet);

		bool TabEnabled() const { return GetBoolean("tabEnabled"); }
		void TabEnabled(bool a_tabEnabled) { SetBoolean("tabEnabled", a_tabEnabled); }

		double TabIndex() const { return GetNumber("tabIndex"); }
		void TabIndex(double a_tabIndex) { SetNumber("tabIndex", a_tabIndex); }

		std::string Target() const { return GetString("_target"); }

		std::string Text() const { return GetString("text"); }
		void Text(std::string_view a_text) { SetString("text", a_text); }

		double TextColor() const { return GetNumber("textColor"); }
		void TextColor(double a_textColor) { SetNumber("textColor", a_textColor); }

		double TextHeight() const { return GetNumber("textHeight"); }
		void TextHeight(double a_textHeight) { SetNumber("textHeight", a_textHeight); }

		double TextWidth() const { return GetNumber("textWidth"); }
		void TextWidth(double a_textWidth) { SetNumber("textWidth", a_textWidth); }

		double Thickness() const { return GetNumber("thickness"); }
		void Thickness(double a_thickness) { SetNumber("thickness", a_thickness); }

		std::string Type() const { return GetString("type"); }
		void Type(std::string_view a_type) { SetString("type", a_type); }

		std::string URL() const { return GetString("_url"); }

		std::string Variable() const { return GetString("variable"); }
		void Variable(std::string_view a_variable) { SetString("variable", a_variable); }

		bool Visible() const { return GetBoolean("_visible"); }
		void Visible(bool a_visible) { SetBoolean("_visible", a_visible); }

		double Width() const { return GetNumber("_width"); }
		void Width(double a_width) { SetNumber("_width", a_width); }

		bool WordWrap() const { return GetBoolean("wordWrap"); }
		void WordWrap(bool a_wordWrap) { SetBoolean("wordWrap", a_wordWrap); }

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

		// methods
		bool AddListener(Object& a_listener)
		{
			enum
			{
				kListener,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kListener] = a_listener.GetInstance();
			assert(args[kListener].IsObject());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("addListener", std::addressof(boolean), args.data(), kNumArgs);
			assert(success);

			return boolean.GetBool();
		}

		double GetDepth()
		{
			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getDepth", std::addressof(number));
			assert(success);

			return number.GetNumber();
		}

		//TextFormat GetNewTextFormat();
		//TextFormat GetTextFormat(std::optional<double> a_beginIndex, std::optional<double> a_endIndex);

		bool RemoveListener(Object& a_listener)
		{
			enum
			{
				kListener,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kListener] = a_listener.GetInstance();
			assert(args[kListener].IsObject());

			RE::GFxValue boolean;
			[[maybe_unused]] const auto success =
				Invoke("removeListener", std::addressof(boolean), args.data(), args.size());
			assert(success);

			return boolean.GetBool();
		}

		void RemoveTextField()
		{
			[[maybe_unused]] const auto success =
				Invoke("removeTextField");
			assert(success);
		}

		void ReplaceSel(std::string_view a_newText)
		{
			enum
			{
				kNewText,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kNewText] = a_newText;
			assert(args[kNewText].IsString());

			[[maybe_unused]] const auto success =
				Invoke("replaceSel", nullptr, args.data(), args.size());
			assert(success);
		}

		void ReplaceText(double a_beginIndex, double a_endIndex, std::string_view a_newText)
		{
			enum
			{
				kBeginIndex,
				kEndIndex,
				kNewText,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kBeginIndex] = a_beginIndex;
			assert(args[kBeginIndex].IsNumber());

			args[kEndIndex] = a_endIndex;
			assert(args[kEndIndex].IsNumber());

			args[kNewText] = a_newText;
			assert(args[kNewText].IsString());

			[[maybe_unused]] const auto success =
				Invoke("replaceText", nullptr, args.data(), args.size());
			assert(success);
		}

		//void SetNewTextFormat(TextFormat& a_tf);

		//void SetTextFormat(std::optional<double> a_beginIndex, std::optional<double> a_endIndex, TextFormat& a_textFormat);;

		// gfx properties
		bool AutoFit() const { return GetBoolean("autoFit"); }
		void AutoFit(bool a_autoFit) { SetBoolean("autoFit", a_autoFit); }

		double CaretIndex() const { return GetNumber("caretIndex"); }
		void CaretIndex(double a_caretIndex) { SetNumber("caretIndex", a_caretIndex); }

		double FocusGroup() const { return GetNumber("focusGroup"); }
		void FocusGroup(double a_focusGroup) { SetNumber("focusGroup", a_focusGroup); }

		bool HitTestDisable() const { return GetBoolean("hitTestDisable"); }
		void HitTestDisable(bool a_hitTestDisable) { SetBoolean("hitTestDisable", a_hitTestDisable); }

		bool NoTranslate() const { return GetBoolean("noTranslate"); }
		void NoTranslate(bool a_noTranslate) { SetBoolean("noTranslate", a_noTranslate); }

		double NumLines() const { return GetNumber("numLines"); }
		void NumLines(double a_numLines) { SetNumber("numLines", a_numLines); }

		bool TopmostLevel() const { return GetBoolean("topmostLevel"); }
		void TopmostLevel(bool a_topmostLevel) { SetBoolean("topmostLevel", a_topmostLevel); }

		double InactiveSelectionBkgColor() const { return GetNumber("inactiveSelectionBkgColor"); }
		void InactiveSelectionBkgColor(double a_inactiveSelectionBkgColor) { SetNumber("inactiveSelectionBkgColor", a_inactiveSelectionBkgColor); }

		bool AlwaysShowSelection() const { return GetBoolean("alwaysShowSelection"); }
		void AlwaysShowSelection(bool a_alwaysShowSelection) { SetBoolean("alwaysShowSelection", a_alwaysShowSelection); }

		bool NoAutoSelection() const { return GetBoolean("noAutoSelection"); }
		void NoAutoSelection(bool a_noAutoSelection) { SetBoolean("noAutoSelection", a_noAutoSelection); }

		double SelectionBeginIndex() const { return GetNumber("selectionBeginIndex"); }
		void SelectionBeginIndex(double a_selectionBeginIndex) { SetNumber("selectionBeginIndex", a_selectionBeginIndex); }

		double SelectionEndIndex() const { return GetNumber("selectionEndIndex"); }
		void SelectionEndIndex(double a_selectionEndIndex) { SetNumber("selectionEndIndex", a_selectionEndIndex); }

		double SelectionBkgColor() const { return GetNumber("selectionBkgColor"); }
		void SelectionBkgColor(double a_selectionBkgColor) { SetNumber("selectionBkgColor", a_selectionBkgColor); }

		double SelectionTextColor() const { return GetNumber("selectionTextColor"); }
		void SelectionTextColor(double a_selectionTextColor) { SetNumber("selectionTextColor", a_selectionTextColor); }

		bool UseRichTextClipboard() const { return GetBoolean("useRichTextClipboard"); }
		void UseRichTextClipboard(bool a_useRichTextClipboard) { SetBoolean("useRichTextClipboard", a_useRichTextClipboard); }

		double InactiveSelectionTextColor() const { return GetNumber("inactiveSelectionTextColor"); }
		void InactiveSelectionTextColor(double a_inactiveSelectionTextColor) { SetNumber("inactiveSelectionTextColor", a_inactiveSelectionTextColor); }

		double FontScaleFactor() const { return GetNumber("fontScaleFactor"); }
		void FontScaleFactor(double a_fontScaleFactor) { SetNumber("fontScaleFactor", a_fontScaleFactor); }

		std::string TextAutoSize() const { return GetString("textAutoSize"); }
		void TextAutoSize(std::string_view a_textAutoSize) { SetString("textAutoSize", a_textAutoSize); }

		std::string VerticalAlign() const { return GetString("verticalAlign"); }
		void VerticalAlign(std::string_view a_verticalAlign) { SetString("verticalAlign", a_verticalAlign); }

		std::string VerticalAutoSize() const { return GetString("verticalAutoSize"); }
		void VerticalAutoSize(std::string_view a_verticalAutoSize) { SetString("verticalAutoSize", a_verticalAutoSize); }

		// gfx methods
		void AppendText(std::string_view a_newText)
		{
			enum
			{
				kNewText,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kNewText] = a_newText;
			assert(args[kNewText].IsString());

			[[maybe_unused]] const auto success =
				Invoke("appendText", nullptr, args.data(), args.size());
			assert(success);
		}

		void AppendHtml(std::string_view a_newHtml)
		{
			enum
			{
				kNewHtml,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kNewHtml] = a_newHtml;
			assert(args[kNewHtml].IsString());

			[[maybe_unused]] const auto success =
				Invoke("appendHtml", nullptr, args.data(), args.size());
			assert(success);
		}

		//Rectangle GetCharBoundaries(double a_charIndex);
		//Rectangle GetExactCharBoundaries(double a_charIndex);

		double GetCharIndexAtPoint(double a_x, double a_y)
		{
			enum
			{
				kX,
				kY,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kX] = a_x;
			assert(args[kX].IsNumber());

			args[kY] = a_y;
			assert(args[kY].IsNumber());

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getCharIndexAtPoint", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		double GetFirstCharInParagraph(double a_charIndex)
		{
			enum
			{
				kCharIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kCharIndex] = a_charIndex;
			assert(args[kCharIndex].IsNumber());

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getFirstCharInParagraph", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		double GetLineIndexAtPoint(double a_x, double a_y)
		{
			enum
			{
				kX,
				kY,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kX] = a_x;
			assert(args[kX].IsNumber());

			args[kY] = a_y;
			assert(args[kY].IsNumber());

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getLineIndexAtPoint", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		double GetLineLength(double a_lineIndex)
		{
			enum
			{
				kLineIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kLineIndex] = a_lineIndex;
			assert(args[kLineIndex].IsNumber());

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getLineLength", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		Object GetLineMetrics(double a_lineIndex)
		{
			enum
			{
				kLineIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kLineIndex] = a_lineIndex;
			assert(args[kLineIndex].IsNumber());

			RE::GFxValue object;
			[[maybe_unused]] const auto success =
				Invoke("getLineMetrics", std::addressof(object), args.data(), args.size());
			assert(success);

			return Object(object);
		}

		double GetLineOffset(double a_lineIndex)
		{
			enum
			{
				kLineIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kLineIndex] = a_lineIndex;
			assert(args[kLineIndex].IsNumber());

			RE::GFxValue number;
			[[maybe_unused]] const auto success =
				Invoke("getLineOffset", std::addressof(number), args.data(), args.size());
			assert(success);

			return number.GetNumber();
		}

		std::string GetLineText(double a_lineIndex)
		{
			enum
			{
				kLineIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kLineIndex] = a_lineIndex;
			assert(args[kLineIndex].IsNumber());

			RE::GFxValue str;
			[[maybe_unused]] const auto success =
				Invoke("getLineText", std::addressof(str), args.data(), args.size());
			assert(success);

			return str.GetString();
		}

		void CopyToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
		{
			enum
			{
				kRichClipboard,
				kStartIndex,
				kEndIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kRichClipboard] = a_richClipboard;
			assert(args[kRichClipboard].IsBool());

			args[kStartIndex] = a_startIndex;
			assert(args[kStartIndex].IsNumber());

			args[kEndIndex] = a_endIndex;
			assert(args[kEndIndex].IsNumber());

			[[maybe_unused]] const auto success =
				Invoke("copyToClipboard", nullptr, args.data(), args.size());
			assert(success);
		}

		void CutToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
		{
			enum
			{
				kRichClipboard,
				kStartIndex,
				kEndIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kRichClipboard] = a_richClipboard;
			assert(args[kRichClipboard].IsBool());

			args[kStartIndex] = a_startIndex;
			assert(args[kStartIndex].IsNumber());

			args[kEndIndex] = a_endIndex;
			assert(args[kEndIndex].IsNumber());

			[[maybe_unused]] const auto success =
				Invoke("cutToClipboard", nullptr, args.data(), args.size());
			assert(success);
		}

		void PasteFromClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
		{
			enum
			{
				kRichClipboard,
				kStartIndex,
				kEndIndex,
				kNumArgs
			};

			std::array<RE::GFxValue, kNumArgs> args;

			args[kRichClipboard] = a_richClipboard;
			assert(args[kRichClipboard].IsBool());

			args[kStartIndex] = a_startIndex;
			assert(args[kStartIndex].IsNumber());

			args[kEndIndex] = a_endIndex;
			assert(args[kEndIndex].IsNumber());

			[[maybe_unused]] const auto success =
				Invoke("pasteFromClipboard", nullptr, args.data(), args.size());
			assert(success);
		}
	};
}
