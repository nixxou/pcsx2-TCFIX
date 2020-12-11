/*  PCSX2 - PS2 Emulator for PCs
 *  Copyright (C) 2002-2020  PCSX2 Dev Team
 *
 *  PCSX2 is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU Lesser General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  PCSX2 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with PCSX2.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "GamePad.h"
#include "keyboard.h"
#include "PAD.h"

extern std::string s_padstrIniPath;

void DefaultKeyboardValues()
{
	set_keyboard_key(0, XK_a, PAD_L2);
	set_keyboard_key(0, XK_semicolon, PAD_R2);
	set_keyboard_key(0, XK_w, PAD_L1);
	set_keyboard_key(0, XK_p, PAD_R1);
	set_keyboard_key(0, XK_i, PAD_TRIANGLE);
	set_keyboard_key(0, XK_l, PAD_CIRCLE);
	set_keyboard_key(0, XK_k, PAD_CROSS);
	set_keyboard_key(0, XK_j, PAD_SQUARE);
	set_keyboard_key(0, XK_v, PAD_SELECT);
	set_keyboard_key(0, XK_n, PAD_START);
	set_keyboard_key(0, XK_e, PAD_UP);
	set_keyboard_key(0, XK_f, PAD_RIGHT);
	set_keyboard_key(0, XK_d, PAD_DOWN);
	set_keyboard_key(0, XK_s, PAD_LEFT);
}

void PADSaveConfig()
{
	FILE* f;

	const std::string iniFile(s_padstrIniPath + "PAD.ini");
	f = fopen(iniFile.c_str(), "w");
	if (f == NULL)
	{
		printf("PAD: failed to save ini %s\n", iniFile.c_str());
		return;
	}

	fprintf(f, "first_time_wizard = %d\n", g_conf.ftw);
	fprintf(f, "log = %d\n", g_conf.log);
	fprintf(f, "options = %d\n", g_conf.packed_options);
	fprintf(f, "mouse_sensibility = %d\n", g_conf.get_sensibility());
	fprintf(f, "ff_intensity = %d\n", g_conf.get_ff_intensity());
	fprintf(f, "uid[0] = %zu\n", g_conf.get_joy_uid(0));
	fprintf(f, "uid[1] = %zu\n", g_conf.get_joy_uid(1));

	for (int pad = 0; pad < GAMEPAD_NUMBER; pad++)
		for (auto const& it : g_conf.keysym_map[pad])
			fprintf(f, "PAD %d:KEYSYM 0x%x = %d\n", pad, it.first, it.second);

	for (auto const& it : g_conf.sdl2_mapping)
		fprintf(f, "SDL2 = %s\n", it.c_str());

	fclose(f);
}

void PADLoadConfig()
{
	FILE* f;
	bool have_user_setting = false;

	g_conf.init();

	const std::string iniFile(s_padstrIniPath + "PAD.ini");
	f = fopen(iniFile.c_str(), "r");
	if (f == NULL)
	{
		printf("OnePAD: failed to load ini %s\n", iniFile.c_str());
		PADSaveConfig(); //save and return
		return;
	}

	u32 value;

	if (fscanf(f, "first_time_wizard = %u\n", &value) == 1)
		g_conf.ftw = value;

	if (fscanf(f, "log = %u\n", &value) == 1)
		g_conf.log = value;

	if (fscanf(f, "options = %u\n", &value) == 1)
		g_conf.packed_options = value;

	if (fscanf(f, "mouse_sensibility = %u\n", &value) == 1)
		g_conf.set_sensibility(value);

	if (fscanf(f, "ff_intensity = %u\n", &value) == 1)
		g_conf.set_ff_intensity(value);

	size_t uid;
	if (fscanf(f, "uid[0] = %zu\n", &uid) == 1)
		g_conf.set_joy_uid(0, uid);
	if (fscanf(f, "uid[1] = %zu\n", &uid) == 1)
		g_conf.set_joy_uid(1, uid);

	u32 pad;
	u32 keysym;
	u32 index;
	while (fscanf(f, "PAD %u:KEYSYM 0x%x = %u\n", &pad, &keysym, &index) == 3)
	{
		set_keyboard_key(pad & 1, keysym, index);
		if (pad == 0)
			have_user_setting = true;
	}

	char sdl2[512];
	while (fscanf(f, "SDL2 = %511[^\n]\n", sdl2) == 1)
		g_conf.sdl2_mapping.push_back(std::string(sdl2));

	if (!have_user_setting)
		DefaultKeyboardValues();

	fclose(f);
}
