#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
	//HELPERS
	#define TID_JPN 0x0004001000020700
	#define TID_USA 0x0004001000021700
	#define TID_EUR 0x0004001000022700
	#define TID_CHN 0x0004001000026700
	#define TID_KOR 0x0004001000027700
	#define TID_TWN 0x0004001000028700
	#define red 0xD21E14FF//0
	#define orange 0xFF6E19FF//1
	#define yellow 0xFFD820FF//2
	#define lime 0x78D220FF//3
	#define green 0x007830FF//4
	#define blue 0x204898FF//5
	#define cyan 0x3CAADEFF//6
	#define pink 0xF55A7DFF//7
	#define purple 0x7328ADFF//8
	#define brown 0x483818FF//9
	#define white 0xE0E0E0FF//10
	#define black 0x181814FF//11
	bool WriteNibble(u32 address, u8 value, bool right_side);
	bool ReadNibble(u32 address, u8 &value, bool right_side);
	bool IsValidPosition(u32 browpos, u32 browspace, u32 browrot, u32 browsize, u32 browidth, u32 eyepos, u32 eyespace, u32 eyerot, u32 eyesize, u32 eyewidth, u32 nosepos, u32 nosesize, u32 mouthpos, u32 mouthsize, u32 mouthwidth, u32 glasspos, u32 glassize, u32 stachepos, u32 stachesize, u32 molex, u32 moley, u32 molesize, u32 tall, u32 wide, u32 gold, u32 share, u8 nibble, u8 val);
	std::vector<size_t> GetSubstrIndexList(std::string &str, std::string indexOf);
	void ReplaceSTR(std::string &str, const std::string &oldSTR, const std::string &newSTR, int substrIndex);
	std::string colorcolor(int pick);
	//STUFF
	void savetheme(MenuEntry *entry);
	void namedit(MenuEntry *entry);
	void OSD(MenuEntry *entry);
	void copymii(MenuEntry *entry);
	void dumpsave(MenuEntry *entry);
	void restoresave(MenuEntry *entry);
	void megamenu(MenuEntry *entry);
	void exitgame(MenuEntry *entry);
	//CHN/TWN
	void TWNnamedit(MenuEntry *entry);
	void TWNOSD(MenuEntry *entry);
	void TWNcopymii(MenuEntry *entry);
	void TWNdumpsave(MenuEntry *entry);
	void TWNrestoresave(MenuEntry *entry);
	void TWNmegamenu(MenuEntry *entry);
	//KOR
	void KORnamedit(MenuEntry *entry);
	void KOROSD(MenuEntry *entry);
	void KORcopymii(MenuEntry *entry);
	void KORdumpsave(MenuEntry *entry);
	void KORrestoresave(MenuEntry *entry);
	void KORmegamenu(MenuEntry *entry);
}
#endif
