#ifndef CHEATS_H
#define CHEATS_H

#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
	//ELSE
	void savetheme(MenuEntry *entry);
	void namedit(MenuEntry *entry);
	void OSD(MenuEntry *entry);
	void copymii(MenuEntry *entry);
	void dumpsave(MenuEntry *entry);
	void restoresave(MenuEntry *entry);
	void megamenu(MenuEntry *entry);
	//TWN
	void TWNnamedit(MenuEntry *entry);
	void TWNOSD(MenuEntry *entry);
	void TWNcopymii(MenuEntry *entry);
	void TWNdumpsave(MenuEntry *entry);
	void TWNrestoresave(MenuEntry *entry);
	void TWNmegamenu(MenuEntry *entry);
}
#endif