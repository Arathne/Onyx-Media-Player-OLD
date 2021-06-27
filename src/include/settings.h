#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
	public:
		~Settings (void);
		
		static void set_auto_play (bool state);
		static bool get_auto_play (void);

	private:
		static Settings instance;
		Settings (void);

		bool auto_play_;
};

#endif
