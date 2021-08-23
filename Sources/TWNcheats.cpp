#include "cheats.hpp"

namespace CTRPluginFramework
{
	Keyboard *TWNoptKb = new Keyboard("Choose option:");
	Keyboard *TWNcoloptKb = new Keyboard("Choose option:\n(This clears the birth day because of how confusing that is, deal with it.)");
	Keyboard *TWNdeloptKb = new Keyboard("Are you sure you want to delete this Mii?");

	std::vector<std::string> TWNNameEdit
	{
		"Nickname",
		"Creator",
	};
	void TWNnamedit(MenuEntry *entry) {
	u32 val;
	u8 breh;
	std::string textvalue;
	std::string wrote;
    TWNoptKb->Populate(TWNNameEdit);
	switch (TWNoptKb->Open())
	{
	case 0:
		if (Process::Read32(0x803CAEC, val) && val == 0xFFFFFFFF) { //stupid way of checking if youre in the editor
		Keyboard keyboard("Type a new nickname.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are unsaveable!");
		keyboard.SetMaxLength(10);
		int op = keyboard.Open(textvalue);
		if(op == -1)
		return;
		Process::WriteString(0x880CCB8, textvalue, StringFormat::Utf16);
		Process::Write16(0x880CCCC, 0);
		OSD::Notify("Nickname changed!");
		Process::ReadString(0x880CCB8, wrote, 0x20, StringFormat::Utf16);
		if (strstr(wrote.c_str(), "%")) {
		std::string toSearch("%");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x880CCB8, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (%), fixed.")();
		}
		}
		if (strstr(wrote.c_str(), "\\")) {
		std::string toSearch("\\");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x880CCB8, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (\\), fixed.")();
		}
		}
		}
		else MessageBox(Color::Red << "You don't seem to be in the editing menu")();
		break;
	case 1:
		if (Process::Read32(0x803CAEC, val) && val == 0xFFFFFFFF) {
		Keyboard keyboard("Type a new creator name.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are unsaveable!");
		keyboard.SetMaxLength(10);
		int op = keyboard.Open(textvalue);
		if(op == -1)
		return;
		Process::WriteString(0x880CCCE, textvalue, StringFormat::Utf16);
		Process::Write16(0x880CCE2, 0);
		OSD::Notify("Creator name changed!");
				Process::ReadString(0x880CCCE, wrote, 0x20, StringFormat::Utf16);
		if (strstr(wrote.c_str(), "%")) {
		std::string toSearch("%");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x880CCCE, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (%), fixed.")();
		}
		}
		if (strstr(wrote.c_str(), "\\")) {
		std::string toSearch("\\");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x880CCCE, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (\\), fixed.")();
		}
		}
		}
		else MessageBox(Color::Red << "You don't seem to be in the editing menu")();
		break;
	}
	}

	bool TWNvalidOSD(const Screen &screen)
	{
		u32 browpos = 0x880CC58; //0x8C8C difference from regular
		u32 browspace = 0x880CC54;///
		u32 browrot = 0x880CC50;///
		u32 browsize = 0x880CC48;///
		u32 browidth = 0x880CC4C;///
		u32 eyepos = 0x880CC3C;///
		u32 eyespace = 0x880CC38;///
		u32 eyerot = 0x880CC34;///
		u32 eyesize = 0x880CC2C;///
		u32 eyewidth = 0x880CC30;///
		u32 nosepos = 0x880CC64;///
		u32 nosesize = 0x880CC60;///
		u32 mouthpos = 0x880CC78;///
		u32 mouthsize = 0x880CC70;///
		u32 mouthwidth = 0x880CC74;///
		u32 glasspos = 0x880CC9C;///
		u32 glassize = 0x880CC98;///
		u32 stachepos = 0x880CC8C;///
		u32 stachesize = 0x880CC88;///
		u32 molex = 0x880CCA8;///
		u32 moley = 0x880CCAC;///
		u32 molesize = 0x880CCA4;///
		u32 tall = 0x880CCB0;///
		u32 wide = 0x880CCB4;///
		u32 share = 0x880CCF7;///
		u32 gold = 0x880CD0C;///
		u8 val;
		u8 nibble;
		if (screen.IsTop && (*(u32 *)0x803CAEC == 0xFFFFFFFF))
		{
			if(!IsValidPosition(*(u8 *)browpos, *(u8 *)browspace, *(u8 *)browrot, *(u8 *)browsize, *(u8 *)browidth, *(u8 *)eyepos, *(u8 *)eyespace, *(u8 *)eyerot, *(u8 *)eyesize, *(u8 *)eyewidth, *(u8 *)nosepos, *(u8 *)nosesize, *(u8 *)mouthpos, *(u8 *)mouthsize, *(u8 *)mouthwidth, *(u8 *)glasspos, *(u8 *)glassize, *(u8 *)stachepos, *(u8 *)stachesize, *(u8 *)molex, *(u8 *)moley, *(u8 *)molesize, *(u8 *)tall, *(u8 *)wide, *(u8 *)gold, *(u8 *)share, val, nibble)) {
			screen.Draw("Unsavable", 0, 0, Color::Red);
			}
			else screen.Draw("Savable", 0, 0, Color::Green);
		}
		return true;
	}
	bool TWNaddressOSD(const Screen &screen)
	{
	u8 val;
		if (screen.IsTop && (*(u32 *)0x8AF73A4 == 0xB88C50) && (*(u16 *)0x88014D5 == 0))
		{
			if (Process::Read8(0x88014D4, val)) {
			screen.Draw(Utils::Format("Mii Data Address: %8X", (0x17200 * val) + 0x8831C84), 0, 0, Color::Cyan);
			screen.Draw(Utils::Format("Mii Data Address In Save (RAM): %8X", (0x5C * val) + 0x1488B928), 0, 10, Color::Cyan);
			}
		}
		return true;
	}

	void TWNOSD(MenuEntry *entry)
	{
		if (entry->WasJustActivated())
		{
			//OSD::Run(TWNvalidOSD);
			OSD::Run(TWNaddressOSD);
		}
		else if (!entry->IsActivated())
		{
			//OSD::Stop(TWNvalidOSD);
			OSD::Stop(TWNaddressOSD);
		}
	}

	void TWNcopymii(MenuEntry *entry) {
	u8 val;
	u32 dataline;
	u32 numint;
	if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
		if (*(u32 *)0x8AF73A4 == 0xB88C50 && (*(u16 *)0x88014D5 == 0))
		{
			if (Process::Read8(0x88014D4, val)) {
			for (int i = 0; i < 256; i+=4)
			{
				if (Process::Read32((0x17200 * val) + (0x8831C84 + i), dataline))
				{
					Process::Write32((0x1E81000 + i), dataline);
				}
			}
				std::string name;
				Process::ReadString((0x17200 * val) + 0x8831D38, name, 0x20, StringFormat::Utf16);
				OSD::Notify("Copied: " + name);
				Process::Write8(0x01E81108, 0x1);
			}
		}
		else OSD::Notify(Color::Red << "No Mii selected!");
	}
	if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
		if (*(u32 *)0x803CAEC == 0xFFFFFFFF && (*(u8 *)0x01E81108 == 0x1))
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
							Process::Write32((0x880CC04 + i), dataline);
						}
					}
					std::string name;
					Process::ReadString(0x880CCB8, name, 0x20, StringFormat::Utf16);
					OSD::Notify("Pasted: " + name);
				}
		}
		else OSD::Notify(Color::Red << "No Mii in clipboard and/or you aren't in the editor!");
	}
	}
	
	void TWNdumpsave(MenuEntry *entry) {
		Directory SaveDir;
		if (Directory::IsExists("/Miichanic") == 0)
			Directory::Create("/Miichanic");

		File SaveFile;
		File::Open(SaveFile,"/Miichanic/CFL_DB.dat", File::RWC);
		SaveFile.Dump(0x1488B920, 0x4BD20);
		SaveFile.Close();
		MessageBox("Dump complete!")();
	}
	void TWNrestoresave(MenuEntry *entry) {
		Directory SaveDir;
		File SaveFile;
		Directory::Open(SaveDir,"/Miichanic", true);
		SaveDir.OpenFile(SaveFile,"CFL_DB.dat", File::READ);
		SaveFile.Inject(0x1488B920, 0x4BD20);
		MessageBox("Save restored!")();
	}
	
	std::vector<std::string> TWNmegOpt{
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
	
	std::vector<std::string> TWNableOpt{
		"Enable",
		"Disable",
	};

	std::vector<std::string> TWNgenOpt{
		"Male",
		"Female",
	};
	
	std::vector<std::string> TWNdelOpt{
		"No",
		"Yes",
	};
	
	std::vector<std::string> TWNcolOpt{
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
	
	void TWNmegamenu(MenuEntry *entry)
	{
		std::vector<std::string> TWNcolorOpt;
		static int TWNColChoice = 0;
		std::string name;
		std::string create;
		std::string finame;
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
		if (*(u32 *)0x8AF73A4 == 0xB88C50 && (*(u16 *)0x88014D5 == 0))
		{
			TWNoptKb->Populate(TWNmegOpt);
			switch (TWNoptKb->Open())
			{
			case 0://name done
			Sleep(Milliseconds(100));
			{
				//Process::ReadString((0x5C * val) + (0x1488B920 + 0x22), finame, 0x20, StringFormat::Utf16);
				Keyboard nkeyboard("Type a new nickname.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are invalid!");
				nkeyboard.SetMaxLength(10);
				int naop = nkeyboard.Open(name);
				if(naop == -1)
				return;
				Process::Read16((0x5C * val) + 0x1488B956, fix);
				for(int i = 0; i < 10; i++) {
				   Process::Write8((0x5C * val) + (0x1488B920 + 0x22) + (i * 0x2), 0);
				}
				Process::WriteString((0x5C * val) + (0x1488B920 + 0x22), name, StringFormat::Utf16);
				if (Process::ReadString((0x5C * val) + (0x1488B920 + 0x22), finame, 20, StringFormat::Utf16)) {
				if (strstr(finame.c_str(), "%")) {
				std::string toSearch("%");
				std::vector<size_t> IndexVec = GetSubstrIndexList(finame, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(finame, toSearch, "?", IndexVec.at(i));
					}
					Process::WriteString((0x5C * val) + (0x1488B920 + 0x22), finame, StringFormat::Utf16);
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (%), fixed.")();
				}
				}
				if (strstr(finame.c_str(), "\\")) {
				std::string toSearch("\\");
				std::vector<size_t> IndexVec = GetSubstrIndexList(finame, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(finame, toSearch, "?", IndexVec.at(i));
					}
					Process::WriteString((0x5C * val) + (0x1488B920 + 0x22), finame, StringFormat::Utf16);
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (\\), fixed.")();
				}
				}
				Sleep(Milliseconds(100));
				Process::Write16((0x5C * val) + 0x1488B956, fix);
				//if(Process::ReadString((0x5C * val) + (0x1488B920 + 0x22), fifiname, 20, StringFormat::Utf16)) {
				MessageBox("Name changed to \u0022" + finame + "\u0022!\n(Reload and save to make changes)")();
				}
			}
				break;
			case 1://creator done
			Sleep(Milliseconds(100));
			{
				Keyboard ckeyboard("Type a new creator name.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are invalid!");
				ckeyboard.SetMaxLength(10);
				int crop = ckeyboard.Open(create);
				if(crop == -1)
				return;
				Process::Read16((0x5C * val) + 0x1488B984, fix);
				for(int i = 0; i < 10; i++) {
				   Process::Write8((0x5C * val) + (0x1488B920 + 0x50) + (i * 0x2), 0);
				}
				Process::WriteString((0x5C * val) + (0x1488B920 + 0x50), create, StringFormat::Utf16);
				if (Process::ReadString((0x5C * val) + (0x1488B920 + 0x50), finame, 20, StringFormat::Utf16)) {
				if (strstr(finame.c_str(), "%")) {
				std::string toSearch("%");
				std::vector<size_t> IndexVec = GetSubstrIndexList(finame, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(finame, toSearch, "?", IndexVec.at(i));
					}
					Process::WriteString((0x5C * val) + (0x1488B920 + 0x50), finame, StringFormat::Utf16);
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (%), fixed.")();
				}
				}
				if (strstr(finame.c_str(), "\\")) {
				std::string toSearch("\\");
				std::vector<size_t> IndexVec = GetSubstrIndexList(finame, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(finame, toSearch, "?", IndexVec.at(i));
					}
					Process::WriteString((0x5C * val) + (0x1488B920 + 0x50), finame, StringFormat::Utf16);
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (\\), fixed.")();
				}
				}
				Sleep(Milliseconds(100));
				Process::Write16((0x5C * val) + 0x1488B984, fix);
				//if(Process::ReadString((0x5C * val) + (0x1488B920 + 0x50), fifiname, 20, StringFormat::Utf16)) {
				MessageBox("Creator name changed to \u0022" + finame + "\u0022!\n(Reload and save to make changes)")();
				}
			}
				break;
			case 2://gender done
			Sleep(Milliseconds(100));
					TWNoptKb->Populate(TWNgenOpt);
					switch (TWNoptKb->Open())
					{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x8831D64), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("Mii is already male!")();
						}
						else if (check == 0x1) {
						Process::Read8((0x5C * val) + (0x1488B940), gen);
						Process::Write8((0x5C * val) + (0x1488B940), (gen - 1));
						Process::Write8((0x17200 * val) + (0x8831D64), 0);
						Sleep(Milliseconds(100));
						MessageBox("This Mii is now male\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x8831D64), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("Mii is already female!")();
						}
						else if (check == 0) {
						Process::Read8((0x5C * val) + (0x1488B940), gen);
						Process::Write8((0x5C * val) + (0x1488B940), (gen + 1));
						Process::Write8((0x17200 * val) + (0x8831D64), 1);
						Sleep(Milliseconds(100));
						MessageBox("This Mii is now female\n(Reload and save to make changes)")();
						}
						break;
					}
				break;
			case 3://color (shares space with favorite) done
			{
			Sleep(Milliseconds(100));
			TWNcolorOpt.push_back(Color(red) << TWNcolOpt[0]);
			TWNcolorOpt.push_back(Color(orange) << TWNcolOpt[1]);
			TWNcolorOpt.push_back(Color(yellow) << TWNcolOpt[2]);
			TWNcolorOpt.push_back(Color(lime) << TWNcolOpt[3]);
			TWNcolorOpt.push_back(Color(green) << TWNcolOpt[4]);
			TWNcolorOpt.push_back(Color(blue) << TWNcolOpt[5]);
			TWNcolorOpt.push_back(Color(cyan) << TWNcolOpt[6]);
			TWNcolorOpt.push_back(Color(pink) << TWNcolOpt[7]);
			TWNcolorOpt.push_back(Color(purple) << TWNcolOpt[8]);
			TWNcolorOpt.push_back(Color(brown) << TWNcolOpt[9]);
			TWNcolorOpt.push_back(Color(white) << TWNcolOpt[10]);
			TWNcolorOpt.push_back(Color(black) << TWNcolOpt[11]);
			
			        Keyboard    keyboard("Pick a new color:", TWNcolorOpt);
					TWNColChoice = keyboard.Open();
					if (TWNColChoice != -1)
					{
						std::string picked = colorcolor(TWNColChoice);
						if (Process::Read8((0x17200 * val) + (0x8831D70), check) && check == TWNColChoice)//if its already the color you pick
						{
						Sleep(Milliseconds(100));
						MessageBox("The shirt is already " << picked << "!")();
						}
						else
						{
							if (Process::Read8((0x17200 * val) + (0x8831D74), check) && check == 0x1)//if it is favorite
							{
							Process::Read8((0x17200 * val) + (0x8831D64), gen);
							Process::Write16((0x5C * val) + (0x1488B940), 0);//clear space
							if(gen == 0x1) {
								Process::Read8((0x5C * val) + (0x1488B940), gen);
								Process::Write8((0x5C * val) + (0x1488B940), (gen + 1));
								Process::Write8((0x17200 * val) + (0x8831D64), 1);
							}
							Process::Read8((0x5C * val) + (0x1488B941), color);
							Process::Write8((0x5C * val) + (0x1488B941), color + (4 * TWNColChoice));//write color value
							Process::Read8((0x5C * val) + (0x1488B941), fav);
							Process::Write8((0x5C * val) + (0x1488B941), (fav + 0x40));//make it favorite again
							}
							else if(check == 0) {//if its not favorite
								Process::Read8((0x17200 * val) + (0x8831D64), gen);
								Process::Write16((0x5C * val) + (0x1488B940), 0);
								if(gen == 0x1) {
									Process::Read8((0x5C * val) + (0x1488B940), gen);
									Process::Write8((0x5C * val) + (0x1488B940), (gen + 1));
									Process::Write8((0x17200 * val) + (0x8831D64), 1);
								}
								Process::Read8((0x5C * val) + (0x1488B941), color);
								Process::Write8((0x5C * val) + (0x1488B941), color + (4 * TWNColChoice));//just make it the color
							}
							Process::Write8((0x17200 * val) + (0x8831D70), TWNColChoice);//adjust internal
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now " << picked << "!\n(Reload and save to make changes)")();
						}
					}
				break;
			}
			case 4://favorite done
			Sleep(Milliseconds(100));
				TWNoptKb->Populate(TWNableOpt);
				switch (TWNoptKb->Open())
				{
				case 0:
					if (Process::Read8((0x17200 * val) + (0x8831D74), check) && check == 0x1)
					{
					Sleep(Milliseconds(100));
					MessageBox("This Mii is already favorited!")();
					}
					else
					{
					Process::Read8((0x5C * val) + (0x1488B941), fav);
					Process::Write8((0x5C * val) + (0x1488B941), (fav + 0x40));
					Process::Write8((0x17200 * val) + (0x8831D74), 1);
					Sleep(Milliseconds(100));
					MessageBox("This Mii is now favorited!\n(Reload and save to make changes)")();
					}
					break;
				case 1:
					if (Process::Read8((0x17200 * val) + (0x8831D74), check) && check == 0)
					{
					Sleep(Milliseconds(100));
					MessageBox("This Mii is already not favorited!")();
					}
					else
					{
					Process::Read8((0x5C * val) + (0x1488B941), fav);
					Process::Write8((0x5C * val) + (0x1488B941), (fav - 0x40));
					Process::Write8((0x17200 * val) + (0x8831D74), 0);
					Sleep(Milliseconds(100));
					MessageBox("This Mii is no longer favorited!\n(Reload and save to make changes)")();
					}
					break;
				};
				break;
			case 5://share done
				Sleep(Milliseconds(100));
				TWNoptKb->Populate(TWNableOpt);
				switch (TWNoptKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x8831D77), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has sharing on!")();
						}
						else if(check == 0x1)
						{
							Process::Read8((0x5C * val) + 0x1488B958, share);
							Process::Write8((0x5C * val) + 0x1488B958, share - 1);
							Process::Write8((0x17200 * val) + 0x8831D77, 0);
							WriteNibble((0x5C * val) + 0x1488B934, 9, false);
							Sleep(Milliseconds(100));
							MessageBox("Sharing has been turned on!\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x8831D77), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has sharing off!")();
						}
						else if(check == 0)
						{
							Process::Read8((0x5C * val) + 0x1488B958, share);
							Process::Write8((0x5C * val) + 0x1488B958, share + 1);
							Process::Write8((0x17200 * val) + 0x8831D77, 0x1);
							Sleep(Milliseconds(100));
							MessageBox("Sharing has been turned off!\n(Reload and save to make changes)")();
						}
					break;
				};
				break;
			case 6://copy done
				Sleep(Milliseconds(100));
				TWNoptKb->Populate(TWNableOpt);
				switch (TWNoptKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x8831D75), check) && check == 0x1)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has copying on!")();
						}
						else if(check == 0)
						{
							Process::Read8((0x5C * val) + 0x1488B929, copy);
							Process::Write8((0x5C * val) + 0x1488B929, copy + 1);
							Process::Write8((0x17200 * val) + 0x8831D75, 0x1);
							Sleep(Milliseconds(100));
							MessageBox("Copying has been turned on!\n(Reload and save to make changes)")();
						}
					break;
					case 1:
						if (Process::Read8((0x17200 * val) + (0x8831D75), check) && check == 0)
						{
						Sleep(Milliseconds(100));
						MessageBox("This Mii is already has copying off!")();
						}
						else if(check == 0x1)
						{
							Process::Read8((0x5C * val) + 0x1488B929, copy);
							Process::Write8((0x5C * val) + 0x1488B929, copy - 1);
							Process::Write8((0x17200 * val) + 0x8831D75, 0);
							Sleep(Milliseconds(100));
							MessageBox("Copying has been turned off!\n(Reload and save to make changes)")();
						}
						break;
				};
				break;
			case 7://gold pants done
				Sleep(Milliseconds(100));
				TWNoptKb->Populate(TWNableOpt);
				switch (TWNoptKb->Open())
				{
					case 0:
						if (Process::Read8((0x17200 * val) + (0x8831D77), check) && check == 0)
						{
							Process::Read8((0x5C * val) + 0x1488B958, share);
							Process::Write8((0x5C * val) + 0x1488B958, share + 1);
							Process::Write8((0x17200 * val) + 0x8831D77, 0x1);
							WriteNibble((0x5C * val) + 0x1488B934, 1, false);
							Sleep(Milliseconds(100));
							MessageBox("Mii has been specialized!\nDon't turn on sharing in the editor or else it won't save.\n(Reload and save to make changes)")();
						}
						else if(check == 1)
						{
							WriteNibble((0x5C * val) + 0x1488B934, 1, false);
							Sleep(Milliseconds(100));
							MessageBox("Mii has been specialized!\nDon't turn on sharing in the editor or else it won't save.\n(Reload and save to make changes)")();
						}
						break;
					case 1:
						WriteNibble((0x5C * val) + 0x1488B934, 9, false);
						Sleep(Milliseconds(100));
						MessageBox("Mii is no longer special\n(Reload and save to make changes)")();
						break;
				};
				break;
			case 8://own done
			{
				for (int i = 0; i < 8; i+=4)
				{
					if (Process::Read32(0x1488B92C + i, sysID))
					{
						Process::Write32((0x5C * val) + (0x1488B92C + i), sysID);
					}
				}
				Sleep(Milliseconds(100));
				if(Process::ReadString((0x5C * val) + (0x1488B920 + 0x22), finame, 20, StringFormat::Utf16)) {
				MessageBox(finame + " is now one of your own Miis!\n(Reload and save to make changes)")();
				}
				break;
			};
			case 9:
			{
				for (int i = 0; i < 92; i+=4)
				{
					if(Process::Read32((0x5C * val) + (0x1488B928 + i), reg))
					{
						Process::Read32((0x1488B928 + i), pers);
						Process::Write32((0x1488B928 + i), reg);
						Process::Write32((0x5C * val) + (0x1488B928 + i), pers);
					}
				}
				Sleep(Milliseconds(100));
				MessageBox("This Mii is now your personal Mii!\n(Reload and save to make changes)")();
				break;
			};
			case 10://delete done
			{
				Sleep(Milliseconds(100));
				TWNdeloptKb->Populate(TWNdelOpt);
				switch (TWNdeloptKb->Open())
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
								Process::Write32((0x5C * val) + (0x1488B928 + i), 0);
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
