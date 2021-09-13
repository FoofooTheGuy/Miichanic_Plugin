#ifndef REGION_HPP
#define REGION_HPP

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
	enum CurrRegion {
		INVALID,
        JUE,
		CT,
        KOR,
    };

	extern CurrRegion c_Region;

	namespace Region {
		u32	AutoRegion(u32 jue, u32 ct, u32 kor);
	}
}
#endif