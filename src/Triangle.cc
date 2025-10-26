

#include <utility>

#include "Node.h"
#include "Circle.h"
#include "Segment.h"
#include "Triangle.h"

Triangle::Triangle(Node t_p, Node t_q, Node t_r)
    : nodeP(t_p)
    , nodeQ(t_q)
    , nodeR(t_r)
    , circumCircle(t_p, t_q, t_r) {

    std::initializer_list<Segment> segment_list = {
        Segment(t_p, t_q),
        Segment(t_q, t_r),
        Segment(t_r, t_p)
    };

    std::copy(segment_list.begin(), segment_list.end(), segments.begin());
}

Triangle::Triangle(const Segment& segment, const Node& node)
    : Triangle(segment.nodeP, segment.nodeQ, node) {
}

bool Triangle::containsNodesOf(const Triangle& other) const noexcept {
    return (nodeP == other.nodeP) || (nodeP == other.nodeQ) || (nodeP == other.nodeR)
        || (nodeQ == other.nodeP) || (nodeQ == other.nodeQ) || (nodeQ == other.nodeR)
        || (nodeR == other.nodeP) || (nodeR == other.nodeQ) || (nodeR == other.nodeR);
}

// friend operators
bool operator==(const Triangle& lhs, const Triangle& rhs) noexcept {
    return (lhs.nodeP == rhs.nodeP) && (lhs.nodeQ == rhs.nodeQ) && (lhs.nodeR == rhs.nodeR);
}

bool operator!=(const Triangle& lhs, const Triangle& rhs) noexcept {
    return lhs.nodeP != rhs.nodeP || lhs.nodeQ != rhs.nodeQ || lhs.nodeR != rhs.nodeR;
}



