namespace SF
{
	inline TextField::TextField(const super& a_rhs) :
		super(a_rhs)
	{}

	inline TextField::TextField(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline TextField& TextField::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline TextField& TextField::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}

namespace SF
{
	inline bool TextField::AddListener(Object& a_listener)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("addListener", std::addressof(boolean), a_listener));
		return boolean.GetBool();
	}

	inline double TextField::GetDepth()
	{
		RE::GFxValue number;
		Assert((Invoke("getDepth", std::addressof(number))));
		return number.GetNumber();
	}

	inline bool TextField::RemoveListener(Object& a_listener)
	{
		RE::GFxValue boolean;
		Assert(InvokeA("removeListener", std::addressof(boolean), a_listener));
		return boolean.GetBool();
	}

	inline void TextField::RemoveTextField()
	{
		Assert(Invoke("removeTextField"));
	}

	inline void TextField::ReplaceSel(std::string_view a_newText)
	{
		Assert(InvokeA("replaceSel", nullptr, a_newText));
	}

	inline void TextField::ReplaceText(double a_beginIndex, double a_endIndex, std::string_view a_newText)
	{
		Assert(InvokeA("replaceText", nullptr, a_beginIndex, a_endIndex, a_newText));
	}
}

namespace SF
{
	inline void TextField::AppendText(std::string_view a_newText)
	{
		Assert(InvokeA("appendText", nullptr, a_newText));
	}

	inline void TextField::AppendHtml(std::string_view a_newHtml)
	{
		Assert(InvokeA("appendHtml", nullptr, a_newHtml));
	}

	inline double TextField::GetCharIndexAtPoint(double a_x, double a_y)
	{
		RE::GFxValue number;
		Assert(InvokeA("getCharIndexAtPoint", std::addressof(number), a_x, a_y));
		return number.GetNumber();
	}

	inline double TextField::GetFirstCharInParagraph(double a_charIndex)
	{
		RE::GFxValue number;
		Assert(InvokeA("getFirstCharInParagraph", std::addressof(number), a_charIndex));
		return number.GetNumber();
	}

	inline double TextField::GetLineIndexAtPoint(double a_x, double a_y)
	{
		RE::GFxValue number;
		Assert(InvokeA("getLineIndexAtPoint", std::addressof(number), a_x, a_y));
		return number.GetNumber();
	}

	inline double TextField::GetLineLength(double a_lineIndex)
	{
		RE::GFxValue number;
		Assert(InvokeA("getLineLength", std::addressof(number), a_lineIndex));
		return number.GetNumber();
	}

	inline Object TextField::GetLineMetrics(double a_lineIndex)
	{
		RE::GFxValue object;
		Assert(InvokeA("getLineMetrics", std::addressof(object), a_lineIndex));
		return Object(object);
	}

	inline double TextField::GetLineOffset(double a_lineIndex)
	{
		RE::GFxValue number;
		Assert(InvokeA("getLineOffset", std::addressof(number), a_lineIndex));
		return number.GetNumber();
	}

	inline std::string TextField::GetLineText(double a_lineIndex)
	{
		RE::GFxValue str;
		Assert(InvokeA("getLineText", std::addressof(str), a_lineIndex));
		return str.GetString();
	}

	inline void TextField::CopyToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
	{
		Assert(InvokeA("copyToClipboard", nullptr, a_richClipboard, a_startIndex, a_endIndex));
	}

	inline void TextField::CutToClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
	{
		Assert(InvokeA("cutToClipboard", nullptr, a_richClipboard, a_startIndex, a_endIndex));
	}

	inline void TextField::PasteFromClipboard(bool a_richClipboard, double a_startIndex, double a_endIndex)
	{
		Assert(InvokeA("pasteFromClipboard", nullptr, a_richClipboard, a_startIndex, a_endIndex));
	}
}
