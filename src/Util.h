#pragma once

#include <cstdlib>
#include <cmath>

#include "segment.h"
#include "node.h"

namespace util {
    /**==============================================
    *@return distance between two nodes */
    static inline float distance(const Node& n1, const Node& n2) noexcept
    {
        return std::sqrt(std::powf(n2.x - n1.x, 2) + std::powf(n2.y - n1.y, 2));
    }

    /**==============================================
    *@return the midPoint of two nodes */
    static inline Node midPoint(const Node& n1, const Node& n2) noexcept
    {
        return Node((n1.x + n2.x) / 2.0f, (n1.y + n2.y) / 2.0f);
    }

    /**==============================================
    *@return the midPoint of a segment */
    static inline Node midPoint(const Segment& s) noexcept
    {
        return Node((s.p.x + s.q.x) / 2.0f, (s.p.y + s.q.y) / 2.0f);
    }

    static inline float slope(const Node& n1, const Node& n2) noexcept
    {
        float top = n2.y - n1.y;
        float bottom = n2.x - n1.x;
        return top / bottom;
    }

    static inline float slope(const Segment& s) noexcept
    {
        float top = s.q.y - s.p.y; // dy
        float bottom = s.q.x - s.p.x; // dx
        return top / bottom;
    }

    static inline float perpendicularSlope(const float& slope)
    {
        return -1.0f / slope; // negative reciprocal
    }

    /**==============================================
    * @return a random value between 1.0f and -1.0f */
    static inline float randomValue(void) noexcept
    {
        const float value = static_cast<float>(std::rand() % 2000);
        const float unit = value / 1000.0f;
        return unit - 1.f;
    }
}

