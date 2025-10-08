#pragma once

#include <cstdlib>
#include <cmath>

#include "segment.h"
#include "node.h"

namespace util {
    /**==============================================
    *@return distance between two nodes */
    static inline float distance(const Node& node0, const Node& node1) noexcept
    {
        return std::sqrt(std::powf(node1.x - node0.x, 2) + std::powf(node1.y - node0.y, 2));
    }

    /**==============================================
    *@return the midPoint of two nodes */
    static inline Node midPoint(const Node& node0, const Node& node1) noexcept
    {
        return Node((node0.x + node1.x) / 2.0f, (node0.y + node1.y) / 2.0f);
    }

    /**==============================================
    *@return the midPoint of a segment */
    static inline Node midPoint(const Segment& s) noexcept
    {
        return Node((s.nodeP.x + s.nodeQ.x) / 2.0f, (s.nodeP.y + s.nodeQ.y) / 2.0f);
    }

    static inline float slope(const Node& node0, const Node& node1) noexcept
    {
        float top = node1.y - node0.y;
        float bottom = node1.x - node0.x;
        return top / bottom;
    }

    static inline float slope(const Segment& s) noexcept
    {
        float top = s.nodeQ.y - s.nodeP.y; // dy
        float bottom = s.nodeQ.x - s.nodeP.x; // dx
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

