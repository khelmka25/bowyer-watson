#ifndef SEGMENT_H
#define SEGMENT_H

#include "node.h"

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
        , slopeType(SlopeType::kNormal) {
    }

    inline friend bool operator == (const Segment& s1, const Segment& s2) noexcept
    {
        return (s1.nodeP == s2.nodeP && s1.nodeQ == s2.nodeQ) || (s1.nodeP == s2.nodeQ && s1.nodeQ == s2.nodeP);
    }

    inline friend bool operator != (const Segment& s1, const Segment& s2) noexcept
    {
        return (s1.nodeP != s2.nodeP) || (s1.nodeQ != s2.nodeQ);
    }

    inline void setSlopeType(const SlopeType& value) noexcept
    {
        this->slopeType = value;
    }

    inline SlopeType getSlopeType(void) const noexcept
    {
        return this->slopeType;
    }

public:
    Node nodeP, nodeQ;

private:
    SlopeType slopeType;
};

#endif // SEGMENT_H
