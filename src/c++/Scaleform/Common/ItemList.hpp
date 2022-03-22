#pragma once

#include "Scaleform/CLIK/GFx/Controls/ScrollingList.hpp"

namespace Scaleform
{
	template <class T>
	class ItemList :
		public CLIK::GFx::Controls::ScrollingList
	{
	private:
		using super = CLIK::GFx::Controls::ScrollingList;
		using super::super;
		using super::operator=;

	public:
		ItemList() = default;
		ItemList(const ItemList&) = default;
		ItemList(ItemList&&) = default;

		ItemList(const super& a_rhs) :
			super(a_rhs)
		{}

		ItemList(super&& a_rhs) :
			super(std::move(a_rhs))
		{}

		~ItemList() = default;

		ItemList& operator=(const ItemList&) = default;
		ItemList& operator=(ItemList&&) = default;

		ItemList& operator=(const super& a_rhs)
		{
			super::operator=(a_rhs);
			return *this;
		}

		ItemList& operator=(super&& a_rhs)
		{
			super::operator=(std::move(a_rhs));
			return *this;
		}

	public:
		void Init(RE::GPtr<RE::GFxMovieView> a_view)
		{
			_view = a_view;
			a_view->CreateArray(std::addressof(_provider));
			DataProvider(CLIK::Array{ _provider });
		}

		T* SelectedItem()
		{
			auto pos = static_cast<ptrdiff_t>(SelectedIndex());
			if (0 <= pos && pos < std::ssize(_impl)) {
				return &_impl[static_cast<size_t>(pos)];
			}

			return nullptr;
		}

		void Refresh()
		{
			_provider.ClearElements();

			for (const auto& elem : _impl) {
				_provider.PushBack(elem.GFxValue(*_view));
			}

			InvalidateData();
		}

		void ModSelectedIndex(double a_mod)
		{
			const auto maxIdx = static_cast<double>(_impl.size()) - 1.0;
			if (maxIdx >= 0.0) {
				const auto idx = std::clamp(SelectedIndex() + a_mod, 0.0, maxIdx);
				SelectedIndex(idx);
			}
		}

		void RestoreIndex(ptrdiff_t a_idx)
		{
			const auto ssize = std::ssize(_impl);
			if (0 <= a_idx && a_idx < ssize) {
				SelectedIndex(static_cast<double>(a_idx));
			} else if (!_impl.empty()) {
				if (a_idx >= ssize) {
					SelectedIndex(static_cast<double>(ssize) - 1.0);
				} else {
					SelectedIndex(0.0);
				}
			} else {
				SelectedIndex(-1.0);
			}
		}

		void RestoreIndex(double a_idx)
		{
			RestoreIndex(static_cast<ptrdiff_t>(a_idx));
		}

	public:
		constexpr void clear() noexcept { _impl.clear(); }
		constexpr void push_back(T& a_item) { _impl.push_back(std::move(a_item)); }

	private:
		RE::GPtr<RE::GFxMovieView> _view;
		RE::GFxValue			   _provider;
		std::vector<T>			   _impl;
	};
}
