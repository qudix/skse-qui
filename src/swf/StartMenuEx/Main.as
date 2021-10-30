class StartMenuEx.Main extends MovieClip
{
	private var _cc: Boolean = true;
	private var _dlc: Boolean = true;
	private var _mods: Boolean = true;
	private var _credits: Boolean = true;
	private var _help: Boolean = true;
	private var _logo: Boolean = true;
	private var _motd: Boolean = true;
	
	private var _limit = 0;
	
	public function Main()
	{
		super();
		var plugin = _global.skse.plugins.QUI
		_cc = plugin.StartGetSetting("CC");
		_dlc = plugin.StartGetSetting("DLC");
		_mods = plugin.StartGetSetting("Mods");
		_credits = plugin.StartGetSetting("Credits");
		_help = plugin.StartGetSetting("Help");
		_logo = plugin.StartGetSetting("Logo");
		_motd = plugin.StartGetSetting("Motd");
	}
	
	function onEnterFrame()
	{
		if (_limit > 5) {
			this.onEnterFrame = null;
			return;
		}
		
		var mc: MovieClip = _root.MenuHolder.Menu_mc;
		if (mc) {
			var list = mc.MainList.__get__entryList();
			var index = 0;
			while (index < list.length - 1) {
				var text = list[index].text;
				if (text == "$CREATION CLUB" && !_cc) {
					list.splice(index, 1);
				} else if (text == "$DOWNLOADABLE CONTENT" && !_dlc) {
					list.splice(index, 1);
				} else if (text == "$MOD MANAGER" && !_mods) {
					list.splice(index, 1);
				} else if (text == "$CREDITS" && !_credits) {
					list.splice(index, 1);
				} else if (text == "$HELP" && !_help) {
					list.splice(index, 1);
				}
				index++;
			}
			
			mc.MainList.InvalidateData();
			
			if (!_logo) {
				mc.Logo_mc._y = 1000;
			}
			
			if (!_motd) {
				mc.MessageOfTheDay_mc._y = 1000;
			}
		}
		
		_limit += 1;
	}
}
