#include "cheats.hpp"
#include <ostream>
#include <string>
#include <vector>

namespace CTRPluginFramework
{
	Keyboard *optKb = new Keyboard("Choose option:");
	Keyboard *deloptKb = new Keyboard("Are you sure you want to delete this Mii?");

bool WriteNibble(u32 address, u8 value, bool right_side) {//ty redshyguy!!!!
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

std::vector<size_t> GetSubstrIndexList(std::string &str, std::string indexOf)//thanks kominost for these two functions!
{
   std::vector<size_t> IndexList;

   for (size_t i = 0; i < str.size(); i++)
   {
      if (str.substr(i, indexOf.size()) == indexOf)
         IndexList.push_back(i);
   }

   return IndexList;
}

void ReplaceSTR(std::string &str, const std::string &oldSTR, const std::string &newSTR, int substrIndex)//kom
{
    str.replace(str.begin() + substrIndex, (str.begin() + substrIndex) + oldSTR.size(), newSTR);
}

bool ConvertString(u32 address, const char* input, size_t size, StringFormat format)
{
    const u8* str8 = reinterpret_cast<const u8*>(input);

    if(format == StringFormat::Utf16)
    {
        u16 *str = new u16[size];
        u16 *addr = (u16*)(address);
        if(utf8_to_utf16(str, str8, size) != -1)
        {
            for(size_t i = 0; i < size; i++)
                *(addr+i) = *(str+i);
            return true;
        }
    }
    else
    {
        u32 *str = new u32[size];
        u32 *addr = (u32*)(address);
        if(utf8_to_utf32(str, str8, size) != -1)
        {
            for(size_t i = 0; i < size; i++)
                *(addr+i) = *(str+i);
            return true;
        }
    }
    return false;
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
		std::string toSearch("%");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x8815944, wrote, StringFormat::Utf16);
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
			Process::WriteString(0x8815944, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (\\), fixed.")();
		}
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
		std::string toSearch("%");
		std::vector<size_t> IndexVec = GetSubstrIndexList(wrote, toSearch);
		if (IndexVec.size())
		{
			for (size_t i = 0; i < IndexVec.size(); i++) {
				ReplaceSTR(wrote, toSearch, "?", IndexVec.at(i));
			}
			Process::WriteString(0x881595A, wrote, StringFormat::Utf16);
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
			Process::WriteString(0x881595A, wrote, StringFormat::Utf16);
			MessageBox("Invalid characters detected (\\), fixed.")();
		}
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
		else if((browpos & 0xFF) > 0x12)
		return false;
		else if((browspace & 0xFF) > 0xC)
		return false;
		else if((browrot & 0xFF) > 0xB)
		return false;
		else if((browsize & 0xFF) > 0x8)
		return false;
		else if((browidth & 0xFF) > 0x6)
		return false;
		else if((eyepos & 0xFF) > 0x12)
		return false;
		else if((eyespace & 0xFF) > 0xC)
		return false;
		else if((eyerot & 0xFF) > 0x7)
		return false;
		else if((eyesize & 0xFF) > 0x7)
		return false;
		else if((eyewidth & 0xFF) > 0x6)
		return false;
		else if((nosepos & 0xFF) > 0x12)
		return false;
		else if((nosesize & 0xFF) > 0x8)
		return false;
		else if((mouthpos & 0xFF) > 0x12)
		return false;
		else if((mouthsize & 0xFF) > 0x8)
		return false;
		else if((mouthwidth & 0xFF) > 0x6)
		return false;
		else if((glasspos & 0xFF) > 0x14)
		return false;
		else if((glassize & 0xFF) > 0x7)
		return false;
		else if((stachepos & 0xFF) > 0x10)
		return false;
		else if((stachesize & 0xFF) > 0x8)
		return false;
		else if((molex & 0xFF) > 0x10)
		return false;
		else if((moley & 0xFF) > 0x1E)
		return false;
		else if((molesize & 0xFF) > 0x8)
		return false;
		else if((tall & 0xFF) > 0x7F)
		return false;
		else if((wide & 0xFF) > 0x7F)
		return false;
		else if (Process::Read8(share, val) && val == 0 && ReadNibble(gold, nibble, false) && nibble == 1)
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
			screen.Draw(Utils::Format("Mii Data Address: %X", (0x17200 * val) + 0x883A910), 0, 0, Color::Cyan);
			screen.Draw(Utils::Format("Mii Data Address in Save (RAM): %X", (0x5C * val) + 0x14895A28), 0, 10, Color::Cyan);
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
			for (int i = 0; i <= 291; i+=4)
			{
				if (Process::Read32((0x17200 * val) + (0x883A910 + i), dataline))
				{
					Process::Write32((0x1E81000 + i), dataline);
				}
			}
				std::string name;
				Process::ReadString((0x17200 * val) + 0x883A9C4, name, 0x20, StringFormat::Utf16);
				OSD::Notify("Copied: " + name);
				Process::Write8(0x01E81124, 0x1);
			}
		}
		else OSD::Notify(Color::Red << "No Mii selected!");
	}
	if(Controller::IsKeysPressed(entry->Hotkeys[1].GetKeys())) {
		if (*(u32 *)0x88B2B28 == 0xFFFFFFFF && (*(u8 *)0x01E81124 == 0x1))
		{
			if (*(u32 *)0x8801164 != 0xFFFFFFFF)
			{
				Sleep(Milliseconds(100));
				MessageBox("Paste this onto the Mii in the Create New Mii editor to avoid the save file from breaking!")();
				return;
			}
				if (*(u32 *)0x8801164 == 0xFFFFFFFF)
				{
					for (int i = 0; i <= 291; i+=4)
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
	
	void exitgame(MenuEntry *entry) {
		if ((MessageBox("Are you sure you want to close the app?\nYou may lose unsaved data.", DialogType::DialogYesNo)).SetClear(ClearScreen::Both)())
		{
			if ((MessageBox("Mii Maker will now close.", DialogType::DialogOkCancel)).SetClear(ClearScreen::Both)())
			{
				Process::ReturnToHomeMenu();
			}
			else return;
		}
		else return;
	}

	void miiEncode(std::vector <u8> &buf, int allowCopying, int profanityFlag, int regionLock, int characterSet, int pageIndex, int slotIndex, int version, int isGirl, int month, int day, int favColor, int isFavorite, int sharing, int faceShape, int skinColor, std::vector<int> miiID, std::vector<int> creatorMAC) {
		buf[1] = allowCopying + (profanityFlag << 1) + (regionLock << 2) + (characterSet << 4);
		buf[2] = pageIndex + (slotIndex << 4);
		buf[3] = version << 4;
		for (int i = 0; i <= 4; i++) {
			buf[0xC + i] = miiID[i];
		}
		for (int i = 0; i <= 6; i++) {
			buf[0x10 + i] = creatorMAC[i];
		}
		buf[0x18] = isGirl + (month << 1) + ((day & 7) << 5);
		buf[0x19] = (day >> 3) + (favColor << 2) + (isFavorite << 6);
		buf[0x30] = !sharing + (faceShape << 1) + (skinColor << 5);
	}

	std::size_t strlen(const std::string& str) {//http://www.cplusplus.com/forum/beginner/192031/#msg925794
		std::size_t length = 0;
		for (char c : str) {
			if ((c & 0xC0) != 0x80) {
				++length;
			}
		}
		return length;
	}

	std::string colorcolor(int pick) {
		if (pick == 0)
			return "red";
		else if (pick == 1)
			return "orange";
		else if (pick == 2)
			return "yellow";
		else if (pick == 3)
			return "lime";
		else if (pick == 4)
			return "green";
		else if (pick == 5)
			return "blue";
		else if (pick == 6)
			return "cyan";
		else if (pick == 7)
			return "pink";
		else if (pick == 8)
			return "purple";
		else if (pick == 9)
			return "brown";
		else if (pick == 10)
			return "white";
		else if (pick == 11)
			return "black";
		else return "";
	}

    std::vector<std::string> megOpt{
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
	
	std::vector<std::string> monthOpt{
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
	
	void megamenu(MenuEntry *entry)
	{
		u32 DATA_ADDR;
		switch (Process::GetTitleID()) {
			case TID_JPN:
			case TID_USA:
			case TID_EUR:
				DATA_ADDR = 0x14895A28;
			case TID_CHN:
			case TID_TWN:
				DATA_ADDR = 0x1488B928;
			case TID_KOR:
				DATA_ADDR = 0x1488B7A8;
			break;
		}
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
			int sharing = !(buf[0x30] & 1);
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
				 megOpt[2].assign("Female");
			else megOpt[2].assign("Male");
			
			enableColor.clear();
			for (int i = 0; i <= 4; i++)
				enableColor.push_back(megOpt[i]);
			if(isFavorite)
				enableColor.push_back(Color::Lime << megOpt[5]);
			else enableColor.push_back(Color::Red << megOpt[5]);
			if(sharing)
				enableColor.push_back(Color::Lime << megOpt[6]);
			else enableColor.push_back(Color::Red << megOpt[6]);
			if(allowcopying)
				enableColor.push_back(Color::Lime << megOpt[7]);
			else enableColor.push_back(Color::Red << megOpt[7]);
			if(specialMii)
				enableColor.push_back(Color::Lime << megOpt[8]);
			else enableColor.push_back(Color::Red << megOpt[8]);
			for (int i = 9; i <= 11; i++)
				enableColor.push_back(megOpt[i]);

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
			colorOpt.push_back(Color(Miired) << colOpt[0]);
			colorOpt.push_back(Color(Miiorange) << colOpt[1]);
			colorOpt.push_back(Color(Miiyellow) << colOpt[2]);
			colorOpt.push_back(Color(Miilime) << colOpt[3]);
			colorOpt.push_back(Color(Miigreen) << colOpt[4]);
			colorOpt.push_back(Color(Miiblue) << colOpt[5]);
			colorOpt.push_back(Color(Miicyan) << colOpt[6]);
			colorOpt.push_back(Color(Miipink) << colOpt[7]);
			colorOpt.push_back(Color(Miipurple) << colOpt[8]);
			colorOpt.push_back(Color(Miibrown) << colOpt[9]);
			colorOpt.push_back(Color(Miiwhite) << colOpt[10]);
			colorOpt.push_back(Color(Miiblack) << colOpt[11]);
			
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
				Keyboard keyboard("Pick a month:", monthOpt);
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
				if (sharing) {
					sharing = false;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is no longer shareable!\n(Reload and save to make changes)")();
				}
				else {
					sharing = true;
					miiID[0] |= 0x80;
				Sleep(Milliseconds(100));
				MessageBox(Miiname << " is now shareable!\n(Reload and save to make changes)")();
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
					sharing = false;
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
				deloptKb->Populate(delOpt);
				switch (deloptKb->Open())
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
			miiEncode(buf, allowcopying, profanityflag, regionlock, characterset, pageindex, slotindex, version, isGirl, month, day, favColor, isFavorite, sharing, faceShape, skinColor, miiID, creatorMAC);
			for (int i = 0; i <= 92; i++)
			{
				Process::Write8((0x5C * val) + DATA_ADDR + i, buf.at(i));
			}
			}
		}
		}
	}
	}

	void callencrypt(MenuEntry *entry) {
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			encrypt();
		}
	}
}