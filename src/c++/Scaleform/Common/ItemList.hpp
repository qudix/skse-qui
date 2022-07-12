#pragma once

#include "Scaleform/Common/Item.hpp"
#include "Scaleform/CLIK/GFx/Controls/ScrollingList.hpp"

namespace SF
{
	class ItemList :
		public CLIK::GFx::Controls::ScrollingList
	{
		using super = CLIK::GFx::Controls::ScrollingList;

	public:
		using super::super;
		using super::operator=;

		ItemList() = default;
		ItemList(const ItemList&) = default;
		ItemList(ItemList&&) = default;
		ItemList(const super& a_rhs);
		ItemList(super&& a_rhs);

		~ItemList() = default;

		ItemList& operator=(const ItemList&) = default;
		ItemList& operator=(ItemList&&) = default;
		ItemList& operator=(const super& a_rhs);
		ItemList& operator=(super&& a_rhs);

	public:
		void       Init(RE::GPtr<RE::GFxMovieView> a_view);
		void       ModSelectedIndex(double a_mod);
		void       Refresh();
		void       RestoreIndex(double a_idx);
		void       RestoreIndex(ptrdiff_t a_idx);
		IItem::Ptr SelectedItem();

		template <class T>
		std::shared_ptr<T> SelectedItem();

	public:
		void clear() noexcept { _impl.clear(); }
		void push_back(IItem::Ptr a_item) { _impl.push_back(std::move(a_item)); }

	private:
		RE::GPtr<RE::GFxMovieView> _view;
		RE::GFxValue               _provider;
		std::vector<IItem::Ptr>    _impl;
	};
}

#include "ItemList.inl"
