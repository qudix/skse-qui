#pragma once

#include "Scaleform/Object.hpp"

namespace SF
{
	class TextField :
		public Object
	{
	private:
		using super = Object;

	public:
		using super::super;
		using super::operator=;

		TextField() = default;
		TextField(const TextField&) = default;
		TextField(TextField&&) = default;
		TextField(const super& a_rhs);
		TextField(super&& a_rhs);

		~TextField() = default;

		TextField& operator=(const TextField&) = default;
		TextField& operator=(TextField&&) = default;
		TextField& operator=(const super& a_rhs);
		TextField& operator=(super&& a_rhs);

	public:
		// Properties
		double      Alpha() const { return GetNumber("_alpha"); }
		void        Alpha(double a_value) { SetNumber("_alpha", a_value); }
		std::string AntiAliasType() const { return GetString("antiAliasType"); }
		void        AntiAliasType(std::string_view a_value) { SetString("antiAliasType", a_value); }
		Object      AutoSize() const { return GetObject("autoSize"); }
		void        AutoSize(const Object& a_value) { SetObject("autoSize", a_value); }
		bool        Background() const { return GetBoolean("background"); }
		void        Background(bool a_value) { SetBoolean("background", a_value); }
		double      BackgroundColor() const { return GetNumber("backgroundColor"); }
		void        BackgroundColor(double a_value) { SetNumber("backgroundColor", a_value); }
		bool        Border() const { return GetBoolean("border"); }
		void        Border(bool a_value) { SetBoolean("border", a_value); }
		double      BorderColor() const { return GetNumber("borderColor"); }
		void        BorderColor(double a_value) { SetNumber("borderColor", a_value); }
		double      BottomScroll() const { return GetNumber("bottomScroll"); }
		bool        CondenseWhite() const { return GetBoolean("condenseWhite"); }
		void        CondenseWhite(bool a_value) { SetBoolean("condenseWhite", a_value); }
		bool        EmbedFonts() const { return GetBoolean("embedFonts"); }
		void        EmbedFonts(bool a_value) { SetBoolean("embedFonts", a_value); }
		std::string GridFitType() const { return GetString("gridFitType"); }
		void        GridFitType(std::string_view a_value) { SetString("gridFitType", a_value); }
		double      Height() const { return GetNumber("_height"); }
		void        Height(double a_value) { SetNumber("_height", a_value); }
		double      HighQuality() const { return GetNumber("_highquality"); }
		void        HighQuality(double a_value) { SetNumber("_highquality", a_value); }
		double      HScroll() const { return GetNumber("hscroll"); }
		void        HScroll(double a_value) { SetNumber("hscroll", a_value); }
		bool        HTML() const { return GetBoolean("html"); }
		void        HTML(bool a_value) { SetBoolean("html", a_value); }
		std::string HTMLText() const { return GetString("htmlText"); }
		void        HTMLText(std::string_view a_value) { SetString("htmlText", a_value); }
		double      Length() const { return GetNumber("length"); }
		double      MaxChars() const { return GetNumber("maxChars"); }
		void        MaxChars(double a_value) { SetNumber("maxChars", a_value); }
		double      MaxHScroll() const { return GetNumber("maxhscroll"); }
		double      MaxScroll() const { return GetNumber("maxscroll"); }
		bool        MouseWheelEnabled() const { return GetBoolean("mouseWheelEnabled"); }
		void        MouseWheelEnabled(bool a_value) { SetBoolean("mouseWheelEnabled", a_value); }
		bool        Multiline() const { return GetBoolean("multiline"); }
		void        Multiline(bool a_value) { SetBoolean("multiline", a_value); }
		std::string Name() const { return GetString("_name"); }
		void        Name(std::string_view a_value) { SetString("_name", a_value); }
		bool        Password() const { return GetBoolean("password"); }
		void        Password(bool a_value) { SetBoolean("password", a_value); }
		std::string Quality() const { return GetString("_quality"); }
		void        Quality(std::string_view a_value) { SetString("_quality", a_value); }
		std::string Restrict() const { return GetString("restrict"); }
		void        Restrict(std::string_view a_value) { SetString("restrict", a_value); }
		double      Rotation() const { return GetNumber("_rotation"); }
		void        Rotation(double a_value) { SetNumber("_rotation", a_value); }
		double      Scroll() const { return GetNumber("scroll"); }
		void        Scroll(double a_value) { SetNumber("scroll", a_value); }
		bool        Selectable() const { return GetBoolean("selectable"); }
		void        Selectable(bool a_value) { SetBoolean("selectable", a_value); }
		double      Sharpness() const { return GetNumber("sharpness"); }
		void        Sharpness(double a_value) { SetNumber("sharpness", a_value); }
		double      SoundBufTime() const { return GetNumber("_soundbuftime"); }
		void        SoundBufTime(double a_value) { SetNumber("_soundbuftime", a_value); }
		bool        TabEnabled() const { return GetBoolean("tabEnabled"); }
		void        TabEnabled(bool a_value) { SetBoolean("tabEnabled", a_value); }
		double      TabIndex() const { return GetNumber("tabIndex"); }
		void        TabIndex(double a_value) { SetNumber("tabIndex", a_value); }
		std::string Target() const { return GetString("_target"); }
		std::string Text() const { return GetString("text"); }
		void        Text(std::string_view a_value) { SetString("text", a_value); }
		double      TextColor() const { return GetNumber("textColor"); }
		void        TextColor(double a_value) { SetNumber("textColor", a_value); }
		double      TextHeight() const { return GetNumber("textHeight"); }
		void        TextHeight(double a_value) { SetNumber("textHeight", a_value); }
		double      TextWidth() const { return GetNumber("textWidth"); }
		void        TextWidth(double a_value) { SetNumber("textWidth", a_value); }
		double      Thickness() const { return GetNumber("thickness"); }
		void        Thickness(double a_value) { SetNumber("thickness", a_value); }
		std::string Type() const { return GetString("type"); }
		void        Type(std::string_view a_value) { SetString("type", a_value); }
		std::string URL() const { return GetString("_url"); }
		std::string Variable() const { return GetString("variable"); }
		void        Variable(std::string_view a_value) { SetString("variable", a_value); }
		bool        Visible() const { return GetBoolean("_visible"); }
		void        Visible(bool a_value) { SetBoolean("_visible", a_value); }
		double      Width() const { return GetNumber("_width"); }
		void        Width(double a_value) { SetNumber("_width", a_value); }
		bool        WordWrap() const { return GetBoolean("wordWrap"); }
		void        WordWrap(bool a_value) { SetBoolean("wordWrap", a_value); }
		double      X() const { return GetNumber("_x"); }
		void        X(double a_value) { SetNumber("_x", a_value); }
		double      XMouse() const { return GetNumber("_xmouse"); }
		double      XScale() const { return GetNumber("_xscale"); }
		void        XScale(double a_value) { SetNumber("_xscale", a_value); }
		double      Y() const { return GetNumber("_y"); }
		void        Y(double a_value) { SetNumber("_y", a_value); }
		double      YMouse() const { return GetNumber("_ymouse"); }
		double      YScale() const { return GetNumber("_yscale"); }
		void        YScale(double a_value) { SetNumber("_yscale", a_value); }

		// GFx Properties
		bool        AlwaysShowSelection() const { return GetBoolean("alwaysShowSelection"); }
		void        AlwaysShowSelection(bool a_value) { SetBoolean("alwaysShowSelection", a_value); }
		bool        AutoFit() const { return GetBoolean("autoFit"); }
		void        AutoFit(bool a_value) { SetBoolean("autoFit", a_value); }
		double      CaretIndex() const { return GetNumber("caretIndex"); }
		void        CaretIndex(double a_value) { SetNumber("caretIndex", a_value); }
		double      FocusGroup() const { return GetNumber("focusGroup"); }
		void        FocusGroup(double a_value) { SetNumber("focusGroup", a_value); }
		double      FontScaleFactor() const { return GetNumber("fontScaleFactor"); }
		void        FontScaleFactor(double a_value) { SetNumber("fontScaleFactor", a_value); }
		bool        HitTestDisable() const { return GetBoolean("hitTestDisable"); }
		void        HitTestDisable(bool a_value) { SetBoolean("hitTestDisable", a_value); }
		double      InactiveSelectionBkgColor() const { return GetNumber("inactiveSelectionBkgColor"); }
		void        InactiveSelectionBkgColor(double a_value) { SetNumber("inactiveSelectionBkgColor", a_value); }
		double      InactiveSelectionTextColor() const { return GetNumber("inactiveSelectionTextColor"); }
		void        InactiveSelectionTextColor(double a_value) { SetNumber("inactiveSelectionTextColor", a_value); }
		bool        NoAutoSelection() const { return GetBoolean("noAutoSelection"); }
		void        NoAutoSelection(bool a_value) { SetBoolean("noAutoSelection", a_value); }
		bool        NoTranslate() const { return GetBoolean("noTranslate"); }
		void        NoTranslate(bool a_value) { SetBoolean("noTranslate", a_value); }
		double      NumLines() const { return GetNumber("numLines"); }
		void        NumLines(double a_value) { SetNumber("numLines", a_value); }
		double      SelectionBeginIndex() const { return GetNumber("selectionBeginIndex"); }
		void        SelectionBeginIndex(double a_value) { SetNumber("selectionBeginIndex", a_value); }
		double      SelectionEndIndex() const { return GetNumber("selectionEndIndex"); }
		void        SelectionEndIndex(double a_value) { SetNumber("selectionEndIndex", a_value); }
		double      SelectionBkgColor() const { return GetNumber("selectionBkgColor"); }
		void        SelectionBkgColor(double a_value) { SetNumber("selectionBkgColor", a_value); }
		double      SelectionTextColor() const { return GetNumber("selectionTextColor"); }
		void        SelectionTextColor(double a_value) { SetNumber("selectionTextColor", a_value); }
		std::string TextAutoSize() const { return GetString("textAutoSize"); }
		void        TextAutoSize(std::string_view a_value) { SetString("textAutoSize", a_value); }
		bool        TopmostLevel() const { return GetBoolean("topmostLevel"); }
		void        TopmostLevel(bool a_value) { SetBoolean("topmostLevel", a_value); }
		bool        UseRichTextClipboard() const { return GetBoolean("useRichTextClipboard"); }
		void        UseRichTextClipboard(bool a_value) { SetBoolean("useRichTextClipboard", a_value); }
		std::string VerticalAlign() const { return GetString("verticalAlign"); }
		void        VerticalAlign(std::string_view a_value) { SetString("verticalAlign", a_value); }
		std::string VerticalAutoSize() const { return GetString("verticalAutoSize"); }
		void        VerticalAutoSize(std::string_view a_value) { SetString("verticalAutoSize", a_value); }

	public:
		// Methods
		bool   AddListener(Object& a_listener);
		double GetDepth();
		bool   RemoveListener(Object& a_listener);
		void   RemoveTextField();
		void   ReplaceSel(std::string_view a_newText);
		void   ReplaceText(double a_beginIndex, double a_endIndex, std::string_view a_newText);

		// GFx Methods
		void        AppendText(std::string_view a_newText);
		void        AppendHtml(std::string_view a_newHtml);
		double      GetCharIndexAtPoint(double a_x, double a_y);
		double      GetFirstCharInParagraph(double a_charIndex);
		double      GetLineIndexAtPoint(double a_x, double a_y);
		double      GetLineLength(double a_lineIndex);
		Object      GetLineMetrics(double a_lineIndex);
		double      GetLineOffset(double a_lineIndex);
		std::string GetLineText(double a_lineIndex);
		void        CopyToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex);
		void        CutToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex);
		void        PasteFromClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex);
	};
}

#include "TextField.inl"
