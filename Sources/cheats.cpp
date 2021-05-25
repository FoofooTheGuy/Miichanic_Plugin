#include "cheats.hpp"

namespace CTRPluginFramework
{
	Keyboard *optKb = new Keyboard("Choose option:");
	Keyboard *coloptKb = new Keyboard("Choose option:\n(This clears the birth day because of how confusing that is, deal with it.)");
	Keyboard *deloptKb = new Keyboard("Are you sure you want to delete this Mii?");

bool WriteNibble(u32 address, u8 value, bool right_side) {
  if(!Process::CheckAddress(address)) //checks if address is valid
    return false;
//right side of the byte
  if(right_side) {
    *(u8 *)address &= ~0xF; //Clears 4bit first
    *(u8 *)address |= (value & 0xF); //Write 4bit then
    return true;
  }
//left side of the byte
  *(u8 *)address &= ~(0xF << 4); //Clears 4bit first
  *(u8 *)address |= ((value & 0xF) << 4); //Write 4bit then
  return true;
}

bool ReadNibble(u32 address, u8 &value, bool right_side) {
  if(!Process::CheckAddress(address)) //checks if address is valid
    return false;
//right side of the byte
  if(right_side) {
    value = *(u8 *)(address) & 0xF;
    return true;
  }
//left side of the byte    
  value = (*(u8 *)(address) >> 4) & 0xF;
  return true;
}

	void savetheme(MenuEntry *entry) {
	FwkSettings &settings = FwkSettings::Get();
	if(entry->WasJustActivated()) {
		settings.BackgroundMainColor = Color::White;
		settings.BackgroundSecondaryColor = Color::White;
		settings.BackgroundBorderColor = Color::Silver;
        settings.MainTextColor = Color::Black;
        settings.WindowTitleColor = Color::Black;
        settings.MenuSelectedItemColor = Color::Black;
        settings.MenuUnselectedItemColor = Color::Black; 
        settings.Keyboard.Background = Color::White;
        settings.Keyboard.KeyBackground = Color::DarkGrey;
        settings.Keyboard.KeyBackgroundPressed = Color::DimGrey;
        settings.Keyboard.KeyText = Color::Black;
        settings.Keyboard.KeyTextPressed = Color::Black;
        settings.Keyboard.Cursor = Color::Black;
        settings.Keyboard.Input = Color::Black;
        settings.CustomKeyboard.BackgroundMain = Color::White;
        settings.CustomKeyboard.BackgroundSecondary = Color::White;
        settings.CustomKeyboard.BackgroundBorder = Color::Silver;
        settings.CustomKeyboard.KeyBackground = Color::White;
        settings.CustomKeyboard.KeyBackgroundPressed = Color::Gainsboro;
        settings.CustomKeyboard.KeyText = Color::Black;
        settings.CustomKeyboard.KeyTextPressed = Color::Black;
        settings.CustomKeyboard.ScrollBarBackground = Color::DimGrey;
        settings.CustomKeyboard.ScrollBarThumb = Color::Silver;
	}
	else if (!entry->IsActivated()) {
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
    }
	std::vector<std::string> NameEdit
	{
		"Nickname",
		"Creator",
	};
	void namedit(MenuEntry *entry) {
	u32 val;
	u8 breh;
	std::string textvalue;
	std::string wrote;
    optKb->Populate(NameEdit);
	switch (optKb->Open())
	{
	case 0:
		if (Process::Read32(0x88B2B28, val) && val == 0xFFFFFFFF) { //stupid way of checking if youre in the editor
		Keyboard keyboard("Type a new nickname.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are unsaveable!");
		keyboard.SetMaxLength(10);
		int op = keyboard.Open(textvalue);
		if(op == -1)
		return;
		Process::WriteString(0x8815944, textvalue, StringFormat::Utf16);
		Process::Write16(0x8815958, 0);
		OSD::Notify("Nickname changed!");
		Process::ReadString(0x8815944, wrote, 0x20, StringFormat::Utf16);
        if (strstr(wrote.c_str(), "%")) {
            Process::WriteString(0x8815944, "??????????", StringFormat::Utf16);
			OSD::Notify("Unsavable characters detected (%), fixed.");
		}
		if (strstr(wrote.c_str(), "\\")) {
            Process::WriteString(0x8815944, "??????????", StringFormat::Utf16);
			OSD::Notify("Unsavable characters detected (\\), fixed.");
		}
		}
		else if (Process::Read32(0x88B2B28, val) && val != 0xFFFFFFFF) {
			MessageBox(Color::Red << "You don't seem to be in the editing menu")();
		}
		break;
	case 1:
		if (Process::Read32(0x88B2B28, val) && val == 0xFFFFFFFF) {
		Keyboard keyboard("Type a new creator name.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are unsaveable!");
		keyboard.SetMaxLength(10);
		int op = keyboard.Open(textvalue);
		if(op == -1)
		return;
		Process::WriteString(0x881595A, textvalue, StringFormat::Utf16);
		Process::Write16(0x881596E, 0);
		OSD::Notify("Creator name changed!");
				Process::ReadString(0x881595A, wrote, 0x20, StringFormat::Utf16);
        if (strstr(wrote.c_str(), "%")) {
            Process::WriteString(0x881595A, "??????????", StringFormat::Utf16);
			OSD::Notify("Unsavable characters detected (%), fixed.");
		}
		if (strstr(wrote.c_str(), "\\")) {
            Process::WriteString(0x881595A, "??????????", StringFormat::Utf16);
			OSD::Notify("Unsavable characters detected (\\), fixed.");
		}
		}
		else if (Process::Read32(0x88B2B28, val) && val != 0xFFFFFFFF) {
			MessageBox(Color::Red << "You don't seem to be in the editing menu")();
		}
		break;
	}
	}
	bool IsValidPosition(u32 browpos, u32 browspace, u32 browrot, u32 browsize, u32 browidth, u32 eyepos, u32 eyespace, u32 eyerot, u32 eyesize, u32 eyewidth, u32 nosepos, u32 nosesize, u32 mouthpos, u32 mouthsize, u32 mouthwidth, u32 glasspos, u32 glassize, u32 stachepos, u32 stachesize, u32 molex, u32 moley, u32 molesize, u32 tall, u32 wide, u32 gold, u32 share, u8 nibble, u8 val)
	{
		if((browpos & 0xFF) < 0x3)//all stuff that is invalid
		return false;
		if((browpos & 0xFF) > 0x12)
		return false;
		if((browspace & 0xFF) > 0xC)
		return false;
		if((browrot & 0xFF) > 0xB)
		return false;
		if((browsize & 0xFF) > 0x8)
		return false;
		if((browidth & 0xFF) > 0x6)
		return false;
		if((eyepos & 0xFF) > 0x12)
		return false;
		if((eyespace & 0xFF) > 0xC)
		return false;
		if((eyerot & 0xFF) > 0x7)
		return false;
		if((eyesize & 0xFF) > 0x7)
		return false;
		if((eyewidth & 0xFF) > 0x6)
		return false;
		if((nosepos & 0xFF) > 0x12)
		return false;
		if((nosesize & 0xFF) > 0x8)
		return false;
		if((mouthpos & 0xFF) > 0x12)
		return false;
		if((mouthsize & 0xFF) > 0x8)
		return false;
		if((mouthwidth & 0xFF) > 0x6)
		return false;
		if((glasspos & 0xFF) > 0x14)
		return false;
		if((glassize & 0xFF) > 0x7)
		return false;
		if((stachepos & 0xFF) > 0x10)
		return false;
		if((stachesize & 0xFF) > 0x8)
		return false;
		if((molex & 0xFF) > 0x10)
		return false;
		if((moley & 0xFF) > 0x1E)
		return false;
		if((molesize & 0xFF) > 0x8)
		return false;
		if((tall & 0xFF) > 0x7F)
		return false;
		if((wide & 0xFF) > 0x7F)
		return false;
		if (Process::Read8(share, val) && val == 0 && ReadNibble(gold, nibble, false) && nibble == 1)
		return false;
		
	
	return true;
	}
	bool validOSD(const Screen &screen)
	{
		u32 browpos = 0x88158E4;
		u32 browspace = 0x88158E0;
		u32 browrot = 0x88158DC;
		u32 browsize = 0x88158D4;
		u32 browidth = 0x88158D8;
		u32 eyepos = 0x88158C8;
		u32 eyespace = 0x88158C4;
		u32 eyerot = 0x88158C0;
		u32 eyesize = 0x88158B8;
		u32 eyewidth = 0x88158BC;
		u32 nosepos = 0x88158F0;
		u32 nosesize = 0x88158EC;
		u32 mouthpos = 0x8815904;
		u32 mouthsize = 0x88158FC;
		u32 mouthwidth = 0x8815900;
		u32 glasspos = 0x8815928;
		u32 glassize = 0x8815924;
		u32 stachepos = 0x8815918;
		u32 stachesize = 0x8815914;
		u32 molex = 0x8815934;
		u32 moley = 0x8815938;
		u32 molesize = 0x8815930;
		u32 tall = 0x881593C;
		u32 wide = 0x8815940;
		u32 share = 0x8815983;
		u32 gold = 0x8815998;
		u8 val;
		u8 nibble;
		if (screen.IsTop && (*(u32 *)0x88B2B28 == 0xFFFFFFFF))
		{
			if(!IsValidPosition(*(u8 *)browpos, *(u8 *)browspace, *(u8 *)browrot, *(u8 *)browsize, *(u8 *)browidth, *(u8 *)eyepos, *(u8 *)eyespace, *(u8 *)eyerot, *(u8 *)eyesize, *(u8 *)eyewidth, *(u8 *)nosepos, *(u8 *)nosesize, *(u8 *)mouthpos, *(u8 *)mouthsize, *(u8 *)mouthwidth, *(u8 *)glasspos, *(u8 *)glassize, *(u8 *)stachepos, *(u8 *)stachesize, *(u8 *)molex, *(u8 *)moley, *(u8 *)molesize, *(u8 *)tall, *(u8 *)wide, *(u8 *)gold, *(u8 *)share, val, nibble)) {
			screen.Draw("Unsavable", 0, 0, Color::Red);
			}
			else screen.Draw("Savable", 0, 0, Color::Green);
		}
		return true;
	}
	bool addressOSD(const Screen &screen)
	{
	u8 val;
		if (screen.IsTop && (*(u32 *)0x88B2B28 != 0xFFFFFFFF) && (*(u16 *)0x88014D5 == 0))
		{
			if (Process::Read8(0x88014D4, val)) {
			screen.Draw(Utils::Format("Mii Data Address: %8X", (0x17200 * val) + 0x883A910), 0, 0, Color::Cyan);
			screen.Draw(Utils::Format("Mii Data Address in Save (RAM): %8X", (0x5C * val) + 0x14895A28), 0, 10, Color::Cyan);
			}
		}
		return true;
	}

	void OSD(MenuEntry *entry)
	{
		if (entry->WasJustActivated())
		{
			//OSD::Run(validOSD);
			OSD::Run(addressOSD);
		}
		else if (!entry->IsActivated())
		{
			//OSD::Stop(validOSD);
			OSD::Stop(addressOSD);
		}
	}

	void copymii(MenuEntry *entry) {
	u8 val;
	u8 value;
	u32 dataline;
	u32 numint;
	std::string name1;
	std::string name2;
	if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
		if (*(u32 *)0x88B2B28 != 0xFFFFFFFF && (*(u16 *)0x88014D5 == 0))
		{
			if (Process::Read8(0x88014D4, val)) {
			for (int i = 0; i < 256; i+=4)
			{
				if (Process::Read32((0x17200 * val) + (0x883A910 + i), dataline))
				{
					Process::Write32((0x1E81000 + i), dataline);
				}
			}
				std::string name;
				Process::ReadString((0x17200 * val) + 0x883A9C4, name, 0x20, StringFormat::Utf16);
				OSD::Notify("Copied: " + name);
				Process::Write8(0x01E81108, 0x1);
			}
		}
		else OSD::Notify(Color::Red << "No Mii selected!");
	}
	if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
		if (*(u32 *)0x88B2B28 == 0xFFFFFFFF && (*(u8 *)0x01E81108 == 0x1))
		{
			if (*(u32 *)0x8801164 != 0xFFFFFFFF)
			{
				Sleep(Milliseconds(100));
				MessageBox("Paste this onto the Mii in the Create New Mii editor to avoid the save file from breaking!")();
				return;
			}
				if (*(u32 *)0x8801164 == 0xFFFFFFFF)
				{
					for (int i = 0; i < 256; i+=4)
					{
						if (Process::Read32(0x1E81000 + i, dataline))
						{
							Process::Write32((0x8815890 + i), dataline);
						}
					}
					std::string name;
					Process::ReadString(0x8815944, name, 0x20, StringFormat::Utf16);
					OSD::Notify("Pasted: " + name);
				}
		}
		else OSD::Notify(Color::Red << "No Mii in clipboard and/or you aren't in the editor!");
	}
	}

	void dumpsave(MenuEntry *entry) {
		Directory SaveDir;
		if (Directory::IsExists("/Miichanic") == 0)
			Directory::Create("/Miichanic");

		File SaveFile;
		File::Open(SaveFile,"/Miichanic/CFL_DB.dat", File::RWC);
		SaveFile.Dump(0x14895A20, 0x4BD20);
		SaveFile.Close();
		MessageBox("Dump complete!")();
	}
	void restoresave(MenuEntry *entry) {
		Directory SaveDir;
		File SaveFile;
		Directory::Open(SaveDir,"/Miichanic", true);
		SaveDir.OpenFile(SaveFile,"CFL_DB.dat", File::READ);
		SaveFile.Inject(0x14895A20, 0x4BD20);
		MessageBox("Save restored!")();
	}
	
	#define red 0xD21E14FF
	#define orange 0xFF6E19
	#define yellow 0xFFD820
	#define lime 0x78D220
	#define green 0x007830
	#define blue 0x204898
	#define cyan 0x3CAADE
	#define pink 0xF55A7D
	#define purple 0x7328AD
	#define brown 0x483818
	#define white 0xE0E0E0
	#define black 0x181814
	
	std::vector<std::string> megOpt{
		"Change name...",
		"Change creator...",
		"Toggle gender",
		"Change favorite color",
		//"Change birth day nope nope nope nope",
		"Toggle favorite",
		"Toggle sharing",
		"Toggle copying",
		"Toggle gold pants",
		"Take ownership",
		"Swap with personal Mii",
		"Delete Mii",
	};
	
	std::vector<std::string> ableOpt{
		"Enable",
		"Disable",
	};

	std::vector<std::string> genOpt{
		"Male",
		"Female",
	};
	
	std::vector<std::string> delOpt{
		"No",
		"Yes",
	};
	
	std::vector<std::string> colOpt{
		"\uE017 Red \uE017",
		"\uE017 Orange \uE017",
		"\uE017 Yellow \uE017",
		"\uE017 Lime \uE017",
		"\uE017 Green \uE017",
		"\uE017 Blue \uE017",
		"\uE017 Cyan \uE017",
		"\uE017 Pink \uE017",
		"\uE017 Purple \uE017",
		"\uE017 Brown \uE017",
		"\uE017 White \uE017",
		"\uE017 Black \uE017",
	};
	
	void megamenu(MenuEntry *entry)
	{
		std::vector<std::string> colorOpt;
		static int ColChoice = 0;
		std::string name;
		std::string create;
		std::string finame;
		std::string fifiname;
		u32 pers;
		u32 reg;
		u32 sysID;
		u16 fix;
		u8 check;
		u8 gen;
		u8 val;
		u8 fav;
		u8 share;
		u8 copy;//me questioning why i did it this way
		u8 color;

		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys()))
		{
		if (Process::Read8(0x88014D4, val))
		{
		if (*(u32 *)0x88B2B28 != 0xFFFFFFFF && (*(u16 *)0x88014D5 == 0))
		{
			optKb->Populate(megOpt);
			switch (optKb->Open())
			{
			case 0://name
			Sleep(Milliseconds(100));
			{
				//Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), finame, 0x20, StringFormat::Utf16);
				Keyboard nkeyboard("Type a new nickname.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are invalid!");
				nkeyboard.SetMaxLength(10);
				int naop = nkeyboard.Open(name);
				if(naop == -1)
				return;
				Process::Read16((0x5C * val) + 0x14895A56, fix);
				for(int i = 0; i < 10; i++) {
				   Process::Write8((0x5C * val) + (0x14895A20 + 0x22) + (i * 0x2), 0);
				}
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x22), name, StringFormat::Utf16);
				if (Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), finame, 20, StringFormat::Utf16)) {
				if (strstr(finame.c_str(), "%")) {
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x22), "??????????", StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Invalid characters detected (%), fixed.")();
				}
				if (strstr(finame.c_str(), "\\")) {
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x22), "??????????", StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Invalid characters detected (\\), fixed.")();
				}
				Sleep(Milliseconds(100));
				Process::Write16((0x5C * val) + 0x14895A56, fix);
				if(Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), fifiname, 20, StringFormat::Utf16)) {
				MessageBox("Name changed to \u0022" + fifiname + "\u0022!\n(Reload and save to make changes)")();
				}
				}
			}
				break;
			case 1://creator
			Sleep(Milliseconds(100));
			{
				Keyboard ckeyboard("Type a new creator name.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are invalid!");
				ckeyboard.SetMaxLength(10);
				int crop = ckeyboard.Open(create);
				if(crop == -1)
				return;
				Process::Read16((0x5C * val) + 0x14895A84, fix);
				for(int i = 0; i < 10; i++) {
				   Process::Write8((0x5C * val) + (0x14895A20 + 0x50) + (i * 0x2), 0);
				}
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x50), create, StringFormat::Utf16);
				if (Process::ReadString((0x5C * val) + (0x14895A20 + 0x50), finame, 20, StringFormat::Utf16)) {
				if (strstr(finame.c_str(), "%")) {
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x50), "??????????", StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Invalid characters detected (%), fixed.")();
				}
				if (strstr(finame.c_str(), "\\")) {
				Process::WriteString((0x5C * val) + (0x14895A20 + 0x50), "??????????", StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Invalid characters detected (\\), fixed.")();
				}
				Sleep(Milliseconds(100));
				Process::Write16((0x5C * val) + 0x14895A84, fix);
				if(Process::ReadString((0x5C * val) + (0x14895A20 + 0x50), fifiname, 20, StringFormat::Utf16)) {
				MessageBox("Creator name changed to \u0022" + fifiname + "\u0022!\n(Reload and save to make changes)")();
				}
				}
			}
				break;
			case 2://gender
			Sleep(Milliseconds(100));
					optKb->Populate(genOpt);
					switch (optKb->Open())
					{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x883A9F0), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("Mii is already male!")();
						}
						else if (check == 0x1) {
						Process::Read8((0x5C * val) + (0x14895A40), gen);
						Process::Write8((0x5C * val) + (0x14895A40), (gen - 1));
						Process::Write8((0x17200 * val) + (0x883A9F0), 0);
						Sleep(Milliseconds(100));
						MessageBox("This Mii is now male\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x883A9F0), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("Mii is already female!")();
						}
						else if (check == 0) {
						Process::Read8((0x5C * val) + (0x14895A40), gen);
						Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
						Process::Write8((0x17200 * val) + (0x883A9F0), 1);
						Sleep(Milliseconds(100));
						MessageBox("This Mii is now female\n(Reload and save to make changes)")();
						}
						break;
					}
				break;
			case 3://color (shares space with favorite)
			{
			Sleep(Milliseconds(100));
			colorOpt.push_back(Color(0xD21E14FF) << colOpt[0]);//red
			colorOpt.push_back(Color(0xFF6E19FF) << colOpt[1]);//orange
			colorOpt.push_back(Color(0xFFD820FF) << colOpt[2]);//yellow
			colorOpt.push_back(Color(0x78D220FF) << colOpt[3]);//lime
			colorOpt.push_back(Color(0x007830FF) << colOpt[4]);//green
			colorOpt.push_back(Color(0x204898FF) << colOpt[5]);//blue
			colorOpt.push_back(Color(0x3CAADEFF) << colOpt[6]);//cyan
			colorOpt.push_back(Color(0xF55A7DFF) << colOpt[7]);//pink
			colorOpt.push_back(Color(0x7328ADFF) << colOpt[8]);//purple
			colorOpt.push_back(Color(0x483818FF) << colOpt[9]);//brown
			colorOpt.push_back(Color(0xE0E0E0FF) << colOpt[10]);//white
			colorOpt.push_back(Color(0x181814FF) << colOpt[11]);//black
			
			        Keyboard    keyboard("Pick a new color:", colorOpt);
					ColChoice = keyboard.Open();
					if (ColChoice == 0)//red
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0)//if its already red
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already red!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)//if it is favorite
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);//clear space
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0);//write red value
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));//make it favorite again
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0);//just make it red
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0);//adjust internal
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now red!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 1)//orange
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already orange!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x4);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x4);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x1);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now orange!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 2)//yellow
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x2)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already yellow!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x8);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x8);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x2);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now yellow!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 3)//lime
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x3)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already lime!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0xC);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0xC);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x3);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now lime!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 4)//green
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x4)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already green!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x10);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x10);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x4);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now green!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 5)//blue
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x5)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already blue!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x14);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x14);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x5);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now blue!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 6)//cyan
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x6)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already cyan!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x18);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x18);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x6);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now cyan!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 7)//pink
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x7)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already pink!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x1C);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x1C);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x7);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now pink!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 8)//purple
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x8)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already purple!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x20);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x20);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x8);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now purple!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 9)//brown
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0x9)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already brown!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x24);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x24);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0x9);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now brown!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 10)//white
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0xA)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already white!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x28);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x28);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0xA);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now white!\n(Reload and save to make changes)")();
						}
					}
					if (ColChoice == 11)//black
					{
						if (Process::Read8((0x17200 * val) + (0x883A9FC), check) && check == 0xB)
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already black!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
							{
							Process::Read8((0x17200 * val) + (0x883A9F0), gen);
							Process::Write16((0x5C * val) + (0x14895A40), 0);
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x14895A40), gen);
								Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
								Process::Write8((0x17200 * val) + (0x883A9F0), 1);
							}
							Process::Read8((0x5C * val) + (0x14895A41), color);
							Process::Write8((0x5C * val) + (0x14895A41), color + 0x2C);
							Process::Read8((0x5C * val) + (0x14895A41), fav);
							Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
							}
							else if(check == 0) {
								Process::Read8((0x17200 * val) + (0x883A9F0), gen);
								Process::Write16((0x5C * val) + (0x14895A40), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x14895A40), gen);
									Process::Write8((0x5C * val) + (0x14895A40), (gen + 1));
									Process::Write8((0x17200 * val) + (0x883A9F0), 1);
								}
								Process::Read8((0x5C * val) + (0x14895A41), color);
								Process::Write8((0x5C * val) + (0x14895A41), color + 0x2C);
							}
							Process::Write8((0x17200 * val) + (0x883A9FC), 0xB);
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now black!\n(Reload and save to make changes)")();
						}
					}
				break;
			}
			case 4://favorite
			Sleep(Milliseconds(100));
				optKb->Populate(ableOpt);
				switch (optKb->Open())
				{
				case 0:
					if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0x1)
					{
					Sleep(Milliseconds(100));
					MessageBox("This Mii is already favorited!")();
					}
					else
					{
					Process::Read8((0x5C * val) + (0x14895A41), fav);
					Process::Write8((0x5C * val) + (0x14895A41), (fav + 0x40));
					Process::Write8((0x17200 * val) + (0x883AA00), 1);
					Sleep(Milliseconds(100));
					MessageBox("This Mii is now favorited!\n(Reload and save to make changes)")();
					}
					break;
				case 1:
					if (Process::Read8((0x17200 * val) + (0x883AA00), check) && check == 0)
					{
					Sleep(Milliseconds(100));
					MessageBox("This Mii is already not favorited!")();
					}
					else
					{
					Process::Read8((0x5C * val) + (0x14895A41), fav);
					Process::Write8((0x5C * val) + (0x14895A41), (fav - 0x40));
					Process::Write8((0x17200 * val) + (0x883AA00), 0);
					Sleep(Milliseconds(100));
					MessageBox("This Mii is no longer favorited!\n(Reload and save to make changes)")();
					}
					break;
				};
				break;
			case 5:
				Sleep(Milliseconds(100));
				optKb->Populate(ableOpt);
				switch (optKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x883AA03), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has sharing on!")();
						}
						else if(check == 0x1)
						{
							Process::Read8((0x5C * val) + 0x14895A58, share);
							Process::Write8((0x5C * val) + 0x14895A58, share - 1);
							Process::Write8((0x17200 * val) + 0x883AA03, 0);
							WriteNibble((0x5C * val) + 0x14895A34, 9, false);
							Sleep(Milliseconds(100));
							MessageBox("Sharing has been turned on!\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x883AA03), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has sharing off!")();
						}
						else if(check == 0)
						{
							Process::Read8((0x5C * val) + 0x14895A58, share);
							Process::Write8((0x5C * val) + 0x14895A58, share + 1);
							Process::Write8((0x17200 * val) + 0x883AA03, 0x1);
							Sleep(Milliseconds(100));
							MessageBox("Sharing has been turned off!\n(Reload and save to make changes)")();
						}
					break;
				};
				break;
			case 6:
				Sleep(Milliseconds(100));
				optKb->Populate(ableOpt);
				switch (optKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x883AA01), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has copying on!")();
						}
						else if(check == 0)
						{
							Process::Read8((0x5C * val) + 0x14895A29, copy);
							Process::Write8((0x5C * val) + 0x14895A29, copy + 1);
							Process::Write8((0x17200 * val) + 0x883AA01, 0x1);
							Sleep(Milliseconds(100));
							MessageBox("Copying has been turned on!\n(Reload and save to make changes)")();
						}
					break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x883AA01), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has copying off!")();
						}
						else if(check == 0x1)
						{
							Process::Read8((0x5C * val) + 0x14895A29, copy);
							Process::Write8((0x5C * val) + 0x14895A29, copy - 1);
							Process::Write8((0x17200 * val) + 0x883AA01, 0);
							Sleep(Milliseconds(100));
							MessageBox("Copying has been turned off!\n(Reload and save to make changes)")();
						}
						break;
				};
				break;
			case 7:
				Sleep(Milliseconds(100));
				optKb->Populate(ableOpt);
				switch (optKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x883AA03), check) && check == 0)
						{
							Process::Read8((0x5C * val) + 0x14895A58, share);
							Process::Write8((0x5C * val) + 0x14895A58, share + 1);
							Process::Write8((0x17200 * val) + 0x883AA03, 0x1);
							WriteNibble((0x5C * val) + 0x14895A34, 1, false);
							Sleep(Milliseconds(100));
							MessageBox("Mii has been specialized!\nDon't turn on sharing in the editor or else it won't save.\n(Reload and save to make changes)")();
						}
						else if(check == 1)
						{
							WriteNibble((0x5C * val) + 0x14895A34, 1, false);
							Sleep(Milliseconds(100));
							MessageBox("Mii has been specialized!\nDon't turn on sharing in the editor or else it won't save.\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						WriteNibble((0x5C * val) + 0x14895A34, 9, false);
						Sleep(Milliseconds(100));
						MessageBox("Mii is no longer specialized\n(Reload and save to make changes)")();
						break;
				};
				break;
			case 8:
			{
				for (int i = 0; i < 8; i+=4)
				{
					if (Process::Read32(0x14895A2C + i, sysID))
					{
						Process::Write32((0x5C * val) + (0x14895A2C + i), sysID);
					}
				}
				Sleep(Milliseconds(100));
				if(Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), finame, 20, StringFormat::Utf16)) {
				MessageBox(finame + " is now one of your own Miis!\n(Reload and save to make changes)")();
				}
				break;
			};
			case 9:
			{
				for (int i = 0; i < 92; i+=4)
				{
					if(Process::Read32((0x5C * val) + (0x14895A28 + i), reg))
					{
						Process::Read32((0x14895A28 + i), pers);
						Process::Write32((0x14895A28 + i), reg);
						Process::Write32((0x5C * val) + (0x14895A28 + i), pers);
					}
				}
				Sleep(Milliseconds(100));
				MessageBox("This Mii is now your personal Mii!\n(Reload and save to make changes)")();
				break;
			};
			case 10:
			{
				Sleep(Milliseconds(100));
				deloptKb->Populate(delOpt);
				switch (deloptKb->Open())
				{
					case 0:
						return;
						break;
					case 1:
						if(val == 0)
						{
							Sleep(Milliseconds(100));
							MessageBox("You shoudn't delete your personal Mii.")();
						}
							else
							{
								if(Process::ReadString((0x5C * val) + (0x14895A20 + 0x22), finame, 20, StringFormat::Utf16))
								{
								for (int i = 0; i < 92; i+=4)
								{
								Process::Write32((0x5C * val) + (0x14895A28 + i), 0);
								}
								Sleep(Milliseconds(100));
								MessageBox(finame + " was deleted!\n(Reload and save to make changes)\nP.S. Don't press the Edit button right after or else it will freeze up")();
								}
							}
					break;
				};
				break;
			};
			break;
			};
			}
		}
		}
	}
}
