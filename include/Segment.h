#ifndef SEGMENT_H
#define SEGMENT_H

#include "Node.h"

enum SlopeType
{
    kNormal,
    kZero,
    kInfinite
};

class Segment
{
public:
    Segment() = default;
    Segment(Node t_p, Node t_q)
        : nodeP(t_p)
        , nodeQ(t_q)
        , m_SlopeType(SlopeType::kNormal) {
        const float dy = nodeP.y - nodeQ.y;
        const float dx = nodeP.x - nodeQ.x;

        /* ~/0 = infinite slope */
        if (std::fabs(dx) < std::numeric_limits<float>::epsilon()) {
            m_SlopeType = SlopeType::kInfinite;
        }
        /* 0/~ = zero slope*/
        else if (std::fabs(dy) < std::numeric_limits<float>::epsilon()) {
            m_SlopeType = SlopeType::kZero;
        }
        /* ~/~ = normal slope */
        // else {
        //     m_SlopeType = SlopeType::kNormal;
        // }
    }

    inline friend bool operator==(const Segment& s1, const Segment& s2) noexcept {
        return (s1.nodeP == s2.nodeP && s1.nodeQ == s2.nodeQ) || (s1.nodeP == s2.nodeQ && s1.nodeQ == s2.nodeP);
    }

    inline friend bool operator!=(const Segment& s1, const Segment& s2) noexcept {
        return !(s1 == s2);
    }

    inline void setSlopeType(const SlopeType& value) noexcept {
        m_SlopeType = value;
    }

    inline SlopeType slopeType() const noexcept {
        return m_SlopeType;
    }

    float slope() const noexcept {
        const float dy = nodeP.y - nodeQ.y;
        const float dx = nodeP.x - nodeQ.x;

        return dy / dx;
    }

    float perpSlope() const noexcept {
        return -1.f / slope();
    }

    Node midpoint() const noexcept {
        return Node((nodeP.x + nodeQ.x) / 2.0f, (nodeP.y + nodeQ.y) / 2.0f);
    }

public:
    Node nodeP, nodeQ;

private:
    SlopeType m_SlopeType = SlopeType::kNormal;
};

#endif // SEGMENT_H
