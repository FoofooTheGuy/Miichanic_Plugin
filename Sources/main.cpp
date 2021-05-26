#include "cheats.hpp"
#include "CTRPluginFramework.hpp"

void    abort(void);

namespace CTRPluginFramework
{
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;


        svcUnmapProcessMemory(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
	    settings.AllowSearchEngine = true;
        settings.AllowActionReplay = true;
        settings.WaitTimeToBoot = Time(Seconds(5));
		settings.BackgroundMainColor = Color::Black;
		settings.BackgroundSecondaryColor = Color::Black;
		settings.BackgroundBorderColor = Color::Silver;
        settings.MainTextColor = Color::White;
        settings.WindowTitleColor = Color::White;
        settings.MenuSelectedItemColor = Color::White;
        settings.MenuUnselectedItemColor = Color::White;
        settings.Keyboard.Background = Color::Black;
        settings.Keyboard.KeyBackground = Color::Black;
        settings.Keyboard.KeyBackgroundPressed = Color::Silver;
        settings.Keyboard.KeyText = Color::White;
        settings.Keyboard.KeyTextPressed = Color::White;
        settings.Keyboard.Cursor = Color::White;
        settings.Keyboard.Input = Color::White;
        settings.CustomKeyboard.BackgroundMain = Color::Black;
        settings.CustomKeyboard.BackgroundSecondary = Color::Black;
        settings.CustomKeyboard.BackgroundBorder = Color::Silver;
        settings.CustomKeyboard.KeyBackground = Color::Black;
        settings.CustomKeyboard.KeyBackgroundPressed = Color::Gainsboro;
        settings.CustomKeyboard.KeyText = Color::White;
        settings.CustomKeyboard.KeyTextPressed = Color::Black;
        settings.CustomKeyboard.ScrollBarBackground = Color::Silver;
        settings.CustomKeyboard.ScrollBarThumb = Color::DimGrey;
	}

	static MenuEntry *AddArg(void *arg, MenuEntry *entry)
    {
        if(entry != nullptr)
            entry->SetArg(arg);
        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey)
    {
        if (entry != nullptr)
        {
            entry->Hotkeys += hotkey;
            entry->SetArg(new std::string(entry->Name()));
            entry->Name() += " " + hotkey.ToString();
            entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index)
            {
                std::string *name = reinterpret_cast<std::string *>(entry->GetArg());

                entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
            });
        }

        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys)
    {
        if (entry != nullptr)
        {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }

    int	main()
	{
		if (Process::GetTitleID() == 0x0004001000020700 || Process::GetTitleID() == 0x0004001000021700 || Process::GetTitleID() == 0x0004001000022700)
		{
			PluginMenu *menu = new PluginMenu("Miichanic's Tool Box (JP/US/EU)", 0, 4, 6, "A set of cheats for 3DS Mii Maker made by Foofoo\n\nyoutube.com/c/foofooanimations");
			menu->SynchronizeWithFrame(true);
			
			const std::vector<MenuEntry *> JPUSEUeditorEntries{
			new MenuEntry("Nickname / Creator Modifier", nullptr, namedit, "Be free from the restrictions!\n(But the length is still capped at 10 because that doesn't actually save.)"),
			EntryWithHotkey(new MenuEntry("Copy and paste Mii data", copymii, "Copy any Mii!\nTap on a Mii in the View Mii Characters menu and press the hotkey to copy.\nThen go to the editor and use the paste hotkey.\nYou may have to edit something manually to make the preview update, but it's all there ready for saving."), { Hotkey(Key::DPadUp, "Copy Mii data"), Hotkey(Key::DPadDown, "Paste the Mii into editor")}),
			};
			
			const std::vector<MenuEntry *> JPUSEUsaveEntries{
			new MenuEntry("Dump save file", nullptr, dumpsave, "Backup your save file!\nDumps are stored in: SD:Miichanic/CFL_DB.dat"),
			new MenuEntry("Restore save file", nullptr, restoresave),
			EntryWithHotkey(new MenuEntry("Mega menu", megamenu, "Tap on a mii and press the hotkeys, it can't do everything, but it's useful."), { Hotkey(Key::A | Key::DPadRight, "Open menu")}),
			};
			
			// ítems
			menu->Append(new MenuFolder("Editor codes", JPUSEUeditorEntries));
			menu->Append(new MenuFolder("Save file options", JPUSEUsaveEntries));
			menu->Append(new MenuEntry("Useless OSD", OSD, "Some useful OSD, just says the address of your current mii selection.\nThis might freeze the game, so only turn it on when you need it."));
			menu->Append(new MenuEntry("Toggle theme", savetheme, "On is Light theme, and off is dark theme.\n(Close the menu for it to change)"));
			
			menu->Run();
			delete menu;
		}
		if (Process::GetTitleID() == 0x0004001000028700 || Process::GetTitleID() == 0x0004001000026700 || Process::GetTitleID() == 0x0004001000027700)
		{
			PluginMenu *menu = new PluginMenu("Miichanic's Tool Box (TWN/CHN/KOR?)", 0, 4, 6, "A set of cheats for 3DS Mii Studio made by Foofoo\n\nyoutube.com/c/foofooanimations");
			menu->SynchronizeWithFrame(true);
			
			const std::vector<MenuEntry *> TWNeditorEntries{
			new MenuEntry("Nickname / Creator Modifier", nullptr, TWNnamedit, "Be free from the restrictions!\n(But the length is still capped at 10 because that doesn't actually save.)"),
			EntryWithHotkey(new MenuEntry("Copy and paste Mii data", TWNcopymii, "Copy any Mii!\nTap on a Mii in the View Mii Characters menu and press the hotkey to copy.\nThen go to the editor and use the paste hotkey.\nYou may have to edit something manually to make the preview update, but it's all there ready for saving."), { Hotkey(Key::DPadUp, "Copy Mii data"), Hotkey(Key::DPadDown, "Paste the Mii into editor")}),
			};
			
			const std::vector<MenuEntry *> TWNsaveEntries{
			new MenuEntry("Dump save file", nullptr, TWNdumpsave, "Backup your save file!\nDumps are stored in: SD:Miichanic/CFL_DB.dat"),
			new MenuEntry("Restore save file", nullptr, TWNrestoresave),
			EntryWithHotkey(new MenuEntry("mega menu", TWNmegamenu, "tap on a mii and press the hotkeys, it can't do everything, but it's useful."), { Hotkey(Key::A | Key::DPadRight, "Open menu")}),
			};
			
			// ítems
			menu->Append(new MenuFolder("Editor codes", TWNeditorEntries));
			menu->Append(new MenuFolder("Save file options", TWNsaveEntries));
			menu->Append(new MenuEntry("Useless OSD", TWNOSD, "Some useful OSD, just says the address of your current mii selection.\nThis might freeze the game, so only turn it on when you need it."));
			menu->Append(new MenuEntry("Toggle Theme", savetheme, "On is Light theme, and off is dark theme.\n(Close the menu for it to change)"));
			
			menu->Run();
			delete menu;
		}
		else
			MessageBox("Hey, this isn't Mii Maker!")();
			PluginMenu *menu = new PluginMenu("Miichanic's Tool Box (N/A)", 0, 0, 0, "Empty.");
			menu->SynchronizeWithFrame(true);
			menu->Run();
			delete menu;
		return 0;
	}

}
