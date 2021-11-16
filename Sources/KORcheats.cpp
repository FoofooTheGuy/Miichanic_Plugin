#include "cheats.hpp"

namespace CTRPluginFramework
{
	Keyboard *KORoptKb = new Keyboard("Choose option:");
	Keyboard *KORcoloptKb = new Keyboard("Choose option:\n(This clears the birth day because of how confusing that is, deal with it.)");
	Keyboard *KORdeloptKb = new Keyboard("Are you sure you want to delete this Mii?");

	std::vector<std::string> KORNameEdit
	{
		"Nickname",
		"Creator",
	};
	void KORnamedit(MenuEntry *entry) {
	u32 val;
	u8 breh;
	std::string textvalue;
	std::string wrote;
    KORoptKb->Populate(KORNameEdit);
	switch (KORoptKb->Open())
	{
	case 0:
		if (Process::Read32(0x8032218, val) && val == 0xFFFFFFFF) { //stupid way of checking if youre in the editor
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
		if (Process::Read32(0x8032218, val) && val == 0xFFFFFFFF) {
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

	bool KORvalidOSD(const Screen &screen)
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
		if (screen.IsTop && (*(u32 *)0x8032218 == 0xFFFFFFFF))
		{
			if(!IsValidPosition(*(u8 *)browpos, *(u8 *)browspace, *(u8 *)browrot, *(u8 *)browsize, *(u8 *)browidth, *(u8 *)eyepos, *(u8 *)eyespace, *(u8 *)eyerot, *(u8 *)eyesize, *(u8 *)eyewidth, *(u8 *)nosepos, *(u8 *)nosesize, *(u8 *)mouthpos, *(u8 *)mouthsize, *(u8 *)mouthwidth, *(u8 *)glasspos, *(u8 *)glassize, *(u8 *)stachepos, *(u8 *)stachesize, *(u8 *)molex, *(u8 *)moley, *(u8 *)molesize, *(u8 *)tall, *(u8 *)wide, *(u8 *)gold, *(u8 *)share, val, nibble)) {
			screen.Draw("Unsavable", 0, 0, Color::Red);
			}
			else screen.Draw("Savable", 0, 0, Color::Green);
		}
		return true;
	}
	bool KORaddressOSD(const Screen &screen)
	{
	u8 val;
		if (screen.IsTop && (*(u32 *)0x8AF73A4 == 0xB88C50) && (*(u16 *)0x88014D5 == 0))
		{
			if (Process::Read8(0x88014D4, val)) {
			screen.Draw(Utils::Format("Mii Data Address: %X", (0x17200 * val) + 0x8831C84), 0, 0, Color::Cyan);
			screen.Draw(Utils::Format("Mii Data Address In Save (RAM): %X", (0x5C * val) + 0x1488B7A8), 0, 10, Color::Cyan);
			}
		}
		return true;
	}

	void KOROSD(MenuEntry *entry)
	{
		if (entry->WasJustActivated())
		{
			//OSD::Run(KORvalidOSD);
			OSD::Run(KORaddressOSD);
		}
		else if (!entry->IsActivated())
		{
			//OSD::Stop(KORvalidOSD);
			OSD::Stop(KORaddressOSD);
		}
	}

	void KORcopymii(MenuEntry *entry) {
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
		if (*(u32 *)0x8032218 == 0xFFFFFFFF && (*(u8 *)0x01E81108 == 0x1))
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

	void KORdumpsave(MenuEntry *entry) {
		Directory SaveDir;
		if (Directory::IsExists("/Miichanic") == 0)
			Directory::Create("/Miichanic");

		File SaveFile;
		File::Open(SaveFile,"/Miichanic/CFL_DB.dat", File::RWC);
		SaveFile.Dump(0x1488B7A0, 0x4BD20);
		SaveFile.Close();
		MessageBox("Dump complete!")();
	}
	void KORrestoresave(MenuEntry *entry) {
		Directory SaveDir;
		File SaveFile;
		Directory::Open(SaveDir,"/Miichanic", true);
		SaveDir.OpenFile(SaveFile,"CFL_DB.dat", File::READ);
		SaveFile.Inject(0x1488B7A0, 0x4BD20);
		MessageBox("Save restored!")();
	}

	void KORcallencrypt(MenuEntry *entry) {
		if(Controller::IsKeysPressed(entry->Hotkeys[0].GetKeys())) {
			KORencrypt();
		}
	}
}