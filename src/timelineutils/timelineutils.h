#ifndef TIMELINEUTILS_H
#define TIMELINEUTILS_H
#include "timelineicon.h"
#include <vector>
namespace TimelineUtils
{
    template<typename T>
    inline T clamp(const T &value, const T &lo, const T &hi)
    {
        return value < lo ? lo : value > hi ? hi : value;
    }

    template<typename T>
    inline T lerp(const T &blend, const T &lhs, const T &rhs)
    {
        static_assert(std::is_floating_point<T>::value,
                      "TimelineUtils::lerp: For floating point types only!");
        return blend * lhs + (1.0 - blend) * rhs;
    }

    template<typename T>
    inline T reverseLerp(const T &val, const T &lhs, const T &rhs)
    {
        static_assert(std::is_floating_point<T>::value,
                      "TimelineUtils::reverseLerp: For floating point types only!");
        return (val - rhs) / (lhs - rhs);
    }
    inline QIcon mergeIcons(const Icon &on, const Icon &off)
    {
        QIcon out;
        out.addPixmap(on.pixmap(), QIcon::Normal, QIcon::On);
        out.addPixmap(off.pixmap(), QIcon::Normal, QIcon::Off);
        return out;
    }
};

#endif // TIMELINEUTILS_H
