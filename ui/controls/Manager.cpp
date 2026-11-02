#include "Manager.h"

namespace Octapedal {

ThemeManager& ThemeManager::instance()
{
    static ThemeManager mgr;
    return mgr;
}

} // namespace OpenDaw
