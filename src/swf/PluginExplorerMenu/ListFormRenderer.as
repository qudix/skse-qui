class PluginExplorerMenu.ListFormRenderer extends gfx.controls.ListItemRenderer
{
	public var textContainer: MovieClip;
	public var countContainer: MovieClip;

	private static var RED: Number = 0xEF9A9A;
	private static var WHITE: Number = 0xFFFFFF;

	public function ListItemRenderer(a_data: Object) { super(); }

	private function updateInfo(): Void
	{
		if (data != null) {
			var dataName: String = data.name != null ? data.name : "<Unknown>";
			var dataCount: Number = data.count != null ? data.count : 0;

			textContainer.textField.text = dataName;
			textContainer.textField.textColor = WHITE;
			countContainer.textField.text = dataCount;
			countContainer.textField.textColor = WHITE;
		} else {
			textContainer.textField.text = "";
			textContainer.textField.textColor = WHITE;
			countContainer.textField.text = "";
			countContainer.textField.textColor = WHITE;
		}
	}

	private function updateAfterStateChange(): Void
	{
		updateInfo();
    }

	public function setData(a_data: Object): Void
	{
		super.setData(a_data);
		updateInfo();
	}
}
