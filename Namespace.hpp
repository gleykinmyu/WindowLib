#ifndef WL_NAMESPACE_HPP
#define WL_NAMESPACE_HPP

namespace wl
{
#ifdef WL_ALLOCATION_HPP
using namespace Allocation;
#endif

#ifdef WL_CONTROLS_HPP
using namespace Controls;
#endif

#ifdef WL_GRAPHICS_HPP
using namespace Graphics;
#endif

#ifdef WL_SYSTEM_HPP
using namespace System;
#endif

#ifdef WL_UTILITY_HPP
using namespace Utility;
#endif

#ifdef WL_WINDOW_HPP
using namespace Window;
#endif
}
#endif //!WL_NAMESPACE_HPP