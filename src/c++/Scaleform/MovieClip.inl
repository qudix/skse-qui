namespace SF
{
	inline MovieClip::MovieClip(const super& a_rhs) :
		super(a_rhs)
	{}

	inline MovieClip::MovieClip(super&& a_rhs) :
		super(std::move(a_rhs))
	{}

	inline MovieClip& MovieClip::operator=(const super& a_rhs)
	{
		super::operator=(a_rhs);
		return *this;
	}

	inline MovieClip& MovieClip::operator=(super&& a_rhs)
	{
		super::operator=(std::move(a_rhs));
		return *this;
	}
}
