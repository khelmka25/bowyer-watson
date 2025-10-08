#include "Triangle.h"

#include <utility>

#include "Node.h"
#include "Circle.h"
#include "Segment.h"

Triangle::Triangle(Node t_p, Node t_q, Node t_r)
    : nodeP(t_p)
    , nodeQ(t_q)
    , nodeR(t_r)
    , circumCircle(this->computeCircumCircle(nodeP, nodeQ, nodeR))
{
    std::initializer_list<Node> node_list = {
        t_p,
        t_q,
        t_r
    };

    std::copy(node_list.begin(), node_list.end(), this->nodes.begin());

    std::initializer_list<Segment> segment_list = {
        Segment(t_p, t_q),
        Segment(t_q, t_r),
        Segment(t_r, t_p)
    };

    std::copy(segment_list.begin(), segment_list.end(), this->segments.begin());
}

Triangle::Triangle(const Segment& segment, const Node& node)
    : Triangle(segment.nodeP, segment.nodeQ, node) {
}

Circle Triangle::computeCircumCircle(const Node& n1, const Node& n2, const Node& n3) noexcept
{
    Node circumCenter = Triangle::computeIntersection(n1, n2, n3);
    return Circle(circumCenter, util::distance(circumCenter, n1));
}

// getters, setters, and node checkers ...
bool Triangle::isNodeInCircumCircle(const Node& n) const noexcept
{
    return this->circumCircle.contains(n);
}

// friend operators
bool operator==(const Triangle& lhs, const Triangle& rhs) noexcept
{
    return (lhs.nodeP == rhs.nodeP) && (lhs.nodeQ == rhs.nodeQ) && (lhs.nodeR == rhs.nodeR);
}

bool operator!=(const Triangle& lhs, const Triangle& rhs) noexcept
{
    return lhs.nodeP != rhs.nodeP || lhs.nodeQ != rhs.nodeQ || lhs.nodeR != rhs.nodeR;
}

// circumcircle functions ...
bool Triangle::containsNodesOf(const Triangle& tri) const noexcept
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->nodes.at(i) == tri.nodes.at(j))
                return true;
        }
    }
    return false;
}

// static methods
Node Triangle::computeIntersection(const Node& n1, const Node& n2, const Node& n3) noexcept
{
    float top, bottom;
    // Nodes P and Q ============
    Segment segN1N2 = Segment(n1, n2);
    top = n2.y - n1.y;
    bottom = n2.x - n1.x;

    if (std::abs(bottom) == 0.0f) // ~/0 = infinite slope
        segN1N2.setSlopeType(SlopeType::kInfinite);
    else if (std::abs(top) == 0.0f) // 0/~ = zero slope
        segN1N2.setSlopeType(SlopeType::kZero);
    else                           // ~/~ = normal slope
        segN1N2.setSlopeType(SlopeType::kNormal);

    // Nodes Q and R ============
    Segment segN2N3 = Segment(n2, n3);
    top = n3.y - n2.y;
    bottom = n3.x - n2.x;

    if (std::abs(bottom) == 0.0f) // ~/0 = infinite slope
        segN2N3.setSlopeType(SlopeType::kInfinite);
    else if (std::abs(top) == 0.0f) // 0/~ = zero slope
        segN2N3.setSlopeType(SlopeType::kZero);
    else                           // ~/~ = normal slope
        segN2N3.setSlopeType(SlopeType::kNormal);

    // ==========================
    Node intersection;

    /// ====================================================
    // completely normal triangle
    if (segN1N2.getSlopeType() == SlopeType::kNormal && segN2N3.getSlopeType() == SlopeType::kNormal)
    {
        // setup y = mx + b for segment PQ
        float m1 = util::perpendicularSlope(util::slope(segN1N2));
        float b1 = util::midPoint(segN1N2).y - m1 * util::midPoint(segN1N2).x;

        // setup y = mx + b for segment QR
        float m2 = util::perpendicularSlope(util::slope(segN2N3));
        float b2 = util::midPoint(segN2N3).y - m2 * util::midPoint(segN2N3).x;

        // set them equal to each other
        // m1x + b1 = m2x + b2 -> m1x - m2x = b2 - b1 -> x (m1 - m2) = b2 - b1
        intersection.x = (b2 - b1) / (m1 - m2);
        intersection.y = m2 * intersection.x + b2;
        return intersection;
    }
    // right triangles
    else if (segN1N2.getSlopeType() == SlopeType::kInfinite && segN2N3.getSlopeType() == SlopeType::kZero)
    {
        intersection.y = util::midPoint(segN1N2).y;
        intersection.x = util::midPoint(segN2N3).x;
        return intersection;
    }
    else if (segN1N2.getSlopeType() == SlopeType::kZero && segN2N3.getSlopeType() == SlopeType::kInfinite)
    {
        intersection.y = util::midPoint(segN2N3).y;
        intersection.x = util::midPoint(segN1N2).x;
        return intersection;
    }
    // others ...
    else if (segN1N2.getSlopeType() == SlopeType::kInfinite && segN2N3.getSlopeType() == SlopeType::kNormal)
    {
        intersection.y = util::midPoint(segN1N2).y;
        // for the normal line y = mx + b
        float m = util::perpendicularSlope(util::slope(segN2N3));
        // b = y - mx using util::midPoint of segment QR
        float b = util::midPoint(segN2N3).y - m * util::midPoint(segN2N3).x;
        // y = mx + b -> x = (y - b) / m
        intersection.x = (intersection.y - b) / m;
        return intersection;
    }
    else if (segN1N2.getSlopeType() == SlopeType::kZero && segN2N3.getSlopeType() == SlopeType::kNormal)
    {
        intersection.x = util::midPoint(segN1N2).x;
        // for the nomal line y = mx + b
        float m = util::perpendicularSlope(util::slope(segN2N3));
        // b = y - mx using util::midPoint of segment QR
        float b = util::midPoint(segN2N3).y - m * util::midPoint(segN2N3).x;
        // y = mx + b
        intersection.y = m * intersection.x + b;
        return intersection;
    }
    else if (segN1N2.getSlopeType() == SlopeType::kNormal && segN2N3.getSlopeType() == SlopeType::kInfinite)
    {
        intersection.y = util::midPoint(segN1N2).y;
        // for the normal line y = mx + b
        float m = util::perpendicularSlope(util::slope(segN1N2));
        // b = y - mx using util::midPoint of segment PQ
        float b = util::midPoint(segN1N2).y - m * util::midPoint(segN1N2).x;
        // y = mx + b -> x = (y - b) / m
        intersection.x = (intersection.y - b) / m;
        return intersection;
    }
    else if (segN1N2.getSlopeType() == SlopeType::kNormal && segN2N3.getSlopeType() == SlopeType::kZero)
    {
        intersection.x = util::midPoint(segN1N2).x;
        // for the nomal line y = mx + b
        float m = util::perpendicularSlope(util::slope(segN1N2));
        // b = y - mx using util::midPoint of segment QR
        float b = util::midPoint(segN1N2).y - m * util::midPoint(segN1N2).x;
        // y = mx + b
        intersection.y = m * intersection.x + b;
        return intersection;
    }
    else
    {
        // invlid triangle, set the circum-center to (0, 0)
        // TODO: fix?
        return Node();
    }
}
