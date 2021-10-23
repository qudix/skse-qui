class PluginExplorerMenu.ScrollingList extends gfx.controls.ScrollingList
{
	/* INITIALIZATION */

	// @override gfx.controls.ScrollingList
	public function ScrollingList()
	{
		super();
	}


	/* PUBLIC FUNCTIONS */

	public function modSelectedPage(a_page: Number): Void
	{
		selectedIndex = clamp(_selectedIndex + totalRenderers * a_page, 0, _dataProvider.length - 1);
	}


	/* PRIVATE FUNCTIONS */

	private function clamp(a_val: Number, a_lo: Number, a_hi: Number): Number
	{
		return Math.min(Math.max(a_lo, a_val), a_hi);
	}
}
