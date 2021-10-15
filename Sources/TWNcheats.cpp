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
			screen.Draw(Utils::Format("Mii Data Address: %X", (0x17200 * val) + 0x8831C84), 0, 0, Color::Cyan);
			screen.Draw(Utils::Format("Mii Data Address In Save (RAM): %X", (0x5C * val) + 0x1488B928), 0, 10, Color::Cyan);
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
		"Change name...",//0
		"Change creator...",//1
		"",//2
		"Change favorite color",//3
		"Change birth day",//4
		"Favorite",//5
		"Sharing",//6
		"Copying",//7
		"Specialized (golden)",//8
		"Take ownership",//9
		"Swap with personal Mii",//10
		"Delete Mii",//11
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

	std::vector<std::string> TWNmonthOpt{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December",
	};

	void TWNmegamenu(MenuEntry *entry)
	{
		const u32 DATA_ADDR = 0x1488B928;
		const int CONSOLE_ID_LENGTH = 0x8;
		const int MII_ID_LENGTH = 0x4;
		const int MAC_ADDR_LENGTH = 0x6;
		const int NAME_LENGTH = 0x14;
		std::vector<std::string> enableColor;
		std::vector<std::string> colorOpt;
		std::vector<int> miiID;
		std::vector<int> creatorMAC;
		static int ColChoice = 0;
		std::string Miiname = "";
		std::string str = "";
		u8 val;
		u8 val8;
		u16 val16;
		u32 val32;
		u32 pers;

		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys()))
		{
		if (Process::Read8(0x88014D4, val))
		{
		if (*(u32 *)0x88B2B28 != 0xFFFFFFFF && (*(u16 *)0x88014D5 == 0))
		{
			std::vector<u8> buf;
			buf.clear();
			miiID.clear();
			creatorMAC.clear();
			for (int i = 0; i <= 92; i++)
			{
				Process::Read8((0x5C * val) + DATA_ADDR + i, val8);
				buf.push_back(val8);
			}

			int allowcopying = (buf[0x1] & 1);///thank Kazuki-4ys for this stuff i guess
			int profanityflag = ((buf[0x1] >> 1) & 1);
			int regionlock = (buf[0x1] >> 2) & 3;
			int characterset = (buf[0x1] >> 4) & 3;
			int pageindex = buf[0x2] & 0xF;
			int slotindex = (buf[0x2] >> 4) & 0xF;
			int version = (buf[0x3] >> 4) & 0x7;
			//stuffs weird
			int isGirl = (buf[0x18] & 1);
			int month = (buf[0x18] >> 1) & 0xF;
			int day = ((buf[0x19] & 3) << 3) + (buf[0x18] >> 5);
			int favColor = (buf[0x19] >> 2) & 0xF;
			int isFavorite = ((buf[0x19] >> 6) & 1);
			int specialMii;
			for (int i = 0; i < MII_ID_LENGTH; i++) {
				miiID.push_back(buf[0xC + i]);
			}
			for (int i = 0; i < MAC_ADDR_LENGTH; i++) {
				creatorMAC.push_back(buf[0x10 + i]);
			}
			Process::ReadString((0x5C * val) + DATA_ADDR + 0x1A, Miiname, NAME_LENGTH, StringFormat::Utf16);
			int notsharing = ~(buf[0x30] & 1);
			if (notsharing == -1)
				notsharing = 0;
			else notsharing = 1;
			int faceShape = (buf[0x30] >> 1) & 0xF;
			int skinColor = buf[0x30] >> 5;
			if (miiID[0] & 0x80) {
				specialMii = 0;
			}
			else {
				specialMii = 1;
			}//the rest of the stuff is useless here
			/*menu stuff*/
			if (isGirl)
				 TWNmegOpt[2].assign("Female");
			else TWNmegOpt[2].assign("Male");
			
			enableColor.clear();
			for (int i = 0; i <= 4; i++)
				enableColor.push_back(TWNmegOpt[i]);
			if(isFavorite)
				enableColor.push_back(Color::Lime << TWNmegOpt[5]);
			else enableColor.push_back(Color::Red << TWNmegOpt[5]);
			if(!notsharing)
				enableColor.push_back(Color::Lime << TWNmegOpt[6]);
			else enableColor.push_back(Color::Red << TWNmegOpt[6]);
			if(allowcopying)
				enableColor.push_back(Color::Lime << TWNmegOpt[7]);
			else enableColor.push_back(Color::Red << TWNmegOpt[7]);
			if(specialMii)
				enableColor.push_back(Color::Lime << TWNmegOpt[8]);
			else enableColor.push_back(Color::Red << TWNmegOpt[8]);
			for (int i = 9; i <= 11; i++)
				enableColor.push_back(TWNmegOpt[i]);

			Sleep(Milliseconds(100));
			Keyboard keyboard("Options for " << Miiname << ":\n\nPick a feature to toggle or change", enableColor);
			int Choiche = keyboard.Open();
			if (Choiche < 0)
				return;
			
			if (Choiche == 0) {//Mii name
			Sleep(Milliseconds(100));
				Keyboard nkeyboard("Type a new nickname.\n(Characters \u0022%\u0022 and \u0022\\\u0022 are invalid!");
				nkeyboard.SetMaxLength(10);
				int naop = nkeyboard.Open(str);
				if(naop == -1)
				return;
				for(int i = 0; i < NAME_LENGTH; i++)//clear old name
				   Process::Write8((0x5C * val) + (DATA_ADDR + 0x1A + i), 0);
				if (strstr(str.c_str(), "%")) {
				std::string toSearch("%");
				std::vector<size_t> IndexVec = GetSubstrIndexList(str, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(str, toSearch, "?", IndexVec.at(i));
					}
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (%), fixed.")();
				}
				}
				if (strstr(str.c_str(), "\\")) {
				std::string toSearch("\\");
				std::vector<size_t> IndexVec = GetSubstrIndexList(str, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(str, toSearch, "?", IndexVec.at(i));
					}
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (\\), fixed.")();
				}
				}
				ConvertString((0x5C * val) + DATA_ADDR + 0x1A, str.c_str(), strlen(str), StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Name changed to \u0022" + str + "\u0022\n(Reload and save to make changes)")();
			}
			if (Choiche == 1) {//creator
			Sleep(Milliseconds(100));
				Keyboard ckeyboard("Type a new creator name.\n(Characters \u0022%\u0022 and \u0022\u005C\u0022 are invalid!");
				ckeyboard.SetMaxLength(10);
				int crop = ckeyboard.Open(str);
				if(crop == -1)
				return;
				for(int i = 0; i < NAME_LENGTH; i++)
				   Process::Write8((0x5C * val) + (DATA_ADDR + 0x48 + i), 0);
				if (strstr(str.c_str(), "%")) {
				std::string toSearch("%");
				std::vector<size_t> IndexVec = GetSubstrIndexList(str, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(str, toSearch, "?", IndexVec.at(i));
					}
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (%), fixed.")();
				}
				}
				if (strstr(str.c_str(), "\\")) {
				std::string toSearch("\\");
				std::vector<size_t> IndexVec = GetSubstrIndexList(str, toSearch);
				if (IndexVec.size())
				{
					for (size_t i = 0; i < IndexVec.size(); i++) {
						ReplaceSTR(str, toSearch, "?", IndexVec.at(i));
					}
					Sleep(Milliseconds(100));
					MessageBox("Invalid characters detected (\\), fixed.")();
				}
				}
				ConvertString((0x5C * val) + DATA_ADDR + 0x48, str.c_str(), strlen(str), StringFormat::Utf16);
				Sleep(Milliseconds(100));
				MessageBox("Creator name changed to \u0022" + str + "\u0022\n(Reload and save to make changes)")();
			}
			if (Choiche == 2) {//gender
				if (isGirl) {//if is girl
					isGirl = false;//make boy
				Sleep(Milliseconds(100));
				MessageBox(Miiname + " is now male!\n(Reload and save to make changes)")();
				}
				else {
				isGirl = true;//if is boy, make girl
				Sleep(Milliseconds(100));
				MessageBox(Miiname + " is now female!\n(Reload and save to make changes)")();
				}
			}
			if (Choiche == 3) {//color
			Sleep(Milliseconds(100));
			colorOpt.push_back(Color(Miired) << TWNcolOpt[0]);
			colorOpt.push_back(Color(Miiorange) << TWNcolOpt[1]);
			colorOpt.push_back(Color(Miiyellow) << TWNcolOpt[2]);
			colorOpt.push_back(Color(Miilime) << TWNcolOpt[3]);
			colorOpt.push_back(Color(Miigreen) << TWNcolOpt[4]);
			colorOpt.push_back(Color(Miiblue) << TWNcolOpt[5]);
			colorOpt.push_back(Color(Miicyan) << TWNcolOpt[6]);
			colorOpt.push_back(Color(Miipink) << TWNcolOpt[7]);
			colorOpt.push_back(Color(Miipurple) << TWNcolOpt[8]);
			colorOpt.push_back(Color(Miibrown) << TWNcolOpt[9]);
			colorOpt.push_back(Color(Miiwhite) << TWNcolOpt[10]);
			colorOpt.push_back(Color(Miiblack) << TWNcolOpt[11]);
			
			        Keyboard    keyboard("Pick a new color:", colorOpt);
					ColChoice = keyboard.Open();
					if (ColChoice != -1)
					{
						favColor = ColChoice;//new shirt stuff here
							Sleep(Milliseconds(100));
							MessageBox("The shirt is now " << colorcolor(ColChoice) << "!\n(Reload and save to make changes)")();
					}
			}
			if (Choiche == 4) {//birth month&day
				Sleep(Milliseconds(100));
				Keyboard keyboard("Pick a month:", TWNmonthOpt);
				month = keyboard.Open();
				if (month < 0)
					return;
				switch (month) {
					case 1://feb
						val8 = 29;
					break;
					case 3://april
					case 5://june
					case 8://sep
					case 10://nov
						val8 = 30;
					break;
					default:
						val8 = 31;
					break;
				}
				std::vector<std::string> dayOpt;
				for (int i = 1; i <= val8; i++)
				dayOpt.push_back(std::to_string(i));

				Sleep(Milliseconds(100));
				Keyboard KB("Pick day:", dayOpt);
				day = KB.Open();
				if (day < 0)
					return;
				month = month+1;
				day = day+1;
				Sleep(Milliseconds(100));
				MessageBox(Utils::Format("The Birthday is now %02i/%02i. (MM/DD :P)\n(Reload and save to make changes)", month, day))();
			}
			if (Choiche == 5) {//favorite
				if (isFavorite) {
					isFavorite = false;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is no longer favorited!\n(Reload and save to make changes)")();
				}
				else {
					isFavorite = true;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now favorited!\n(Reload and save to make changes)")();
				}
			}
			if (Choiche == 6) {//sharing
				if (notsharing) {
					notsharing = false;
					miiID[0] |= 0x80;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now shareable!\n(Reload and save to make changes)")();
				}
				else {
					notsharing = true;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is no longer shareable!\n(Reload and save to make changes)")();
				}
			}
			if (Choiche == 7) {//copying
				if (allowcopying) {
					allowcopying = false;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " no longer has copying on!\n(Reload and save to make changes)")();
				}
				else {
					allowcopying = true;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now copyable!\n(Reload and save to make changes)")();
				}
			}
			if (Choiche == 8) {//golden man, take me by the hand lead me to the land that you understand
				if (miiID[0] & 0x80) {
					miiID[0] &= 0x7f;
					notsharing = true;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now specialized!\n(Reload and save to make changes)")();
				}
				else {
					miiID[0] |= 0x80;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is no longer specialized!\n(Reload and save to make changes)")();
				}
			}
			if (Choiche == 9) {//take ownership
				for (int i = 0; i < 8; i+=4)
				{
					if (Process::Read32(DATA_ADDR + 4 + i, val32))
					{
						Process::Write32((0x5C * val) + (DATA_ADDR + 4 + i), val32);
					}
				}
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now one of your own Miis!\n(Reload and save to make changes)")();
			}
			if (Choiche == 10) {//swap
				for (int i = 0; i < 92; i+=4)
				{
					if(Process::Read32((0x5C * val) + (DATA_ADDR + i), val32))
					{
						Process::Read32((DATA_ADDR + i), pers);
						Process::Write32((DATA_ADDR + i), val32);
						Process::Write32((0x5C * val) + (DATA_ADDR + i), pers);
					}
				}
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now your personal Mii!\n(Reload and save to make changes)")();
			}
			if (Choiche == 11) {//D: elete
				Sleep(Milliseconds(100));
				TWNdeloptKb->Populate(TWNdelOpt);
				switch (TWNdeloptKb->Open())
				{
					case 0:
						break;
					case 1:
						if(val == 0)
						{
							Sleep(Milliseconds(100));
							MessageBox("You shoudn't delete your personal Mii.")();
						}
							else
							{
								for (int i = 0; i <= 92; i+=4)
								{
								Process::Write32((0x5C * val) + (DATA_ADDR + i), 0);
								}
								Sleep(Milliseconds(100));
								MessageBox(Miiname << " was deleted!\n(Reload and save to make changes)\nP.S. Don't press the Edit button right after or else it will freeze up")();
							}
					break;
				break;
				};
			}
		for (int i = 2; i <= 8; i++)
			if (Choiche == i) {
			miiEncode(buf, allowcopying, profanityflag, regionlock, characterset, pageindex, slotindex, version, isGirl, month, day, favColor, isFavorite, notsharing, faceShape, skinColor, miiID, creatorMAC);
			for (int i = 0; i <= 92; i++)
			{
				Process::Write8((0x5C * val) + DATA_ADDR + i, buf.at(i));
			}
			}
		}
		}
	}
	}
	void TWNcallencrypt(MenuEntry *entry) {
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			TWNencrypt();
		}
	}
}