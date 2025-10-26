#include "Circle.h"

Circle::Circle(Node t_center, float t_radius)
    : m_Center(t_center)
    , m_Radius(t_radius) {
}

Circle::Circle(Node nodeP, Node nodeQ, Node nodeR) {
    m_Center = locateCenter(nodeP, nodeQ, nodeR);
    m_Radius = m_Center.distanceTo(nodeP);
}

Node Circle::locateCenter(const Node& nodeP, const Node& nodeQ, const Node& nodeR) noexcept {
    // Nodes P and Q ============
    Segment segmentPQ = Segment(nodeP, nodeQ);

    // Nodes Q and R ============
    Segment segmentQR = Segment(nodeQ, nodeR);

    // ==========================
    Node intersection;

    /// ====================================================
    // completely normal triangle
    if ((segmentPQ.slopeType() == SlopeType::kNormal) && (segmentQR.slopeType() == SlopeType::kNormal)) {
        // setup y = mx + b for segment PQ
        float m1 = segmentPQ.perpSlope();
        float b1 = segmentPQ.midpoint().y - m1 * segmentPQ.midpoint().x;

        // setup y = mx + b for segment QR
        float m2 = segmentQR.perpSlope();
        float b2 = segmentQR.midpoint().y - m2 * segmentQR.midpoint().x;

        // set them equal to each other
        // m1x + b1 = m2x + b2 -> m1x - m2x = b2 - b1 -> x (m1 - m2) = b2 - b1
        intersection.x = (b2 - b1) / (m1 - m2);
        intersection.y = m2 * intersection.x + b2;
        return (intersection);
    }
    // right triangles
    else if ((segmentPQ.slopeType() == SlopeType::kInfinite) && (segmentQR.slopeType() == SlopeType::kZero)) {
        intersection.y = segmentPQ.midpoint().y;
        intersection.x = segmentQR.midpoint().x;
        return intersection;
    }
    else if ((segmentPQ.slopeType() == SlopeType::kZero) && (segmentQR.slopeType() == SlopeType::kInfinite)) {
        intersection.y = segmentQR.midpoint().y;
        intersection.x = segmentPQ.midpoint().x;
        return (intersection);
    }
    // others ...
    else if ((segmentPQ.slopeType() == SlopeType::kInfinite) && (segmentQR.slopeType() == SlopeType::kNormal)) {
        intersection.y = segmentPQ.midpoint().y;
        // for the normal line y = mx + b
        float m = segmentQR.perpSlope();
        // b = y - mx using util::midPoint of segment QR
        float b = segmentQR.midpoint().y - m * segmentQR.midpoint().x;
        // y = mx + b -> x = (y - b) / m
        intersection.x = (intersection.y - b) / m;
        return (intersection);
    }
    else if ((segmentPQ.slopeType() == SlopeType::kZero) && (segmentQR.slopeType() == SlopeType::kNormal)) {
        intersection.x = segmentPQ.midpoint().x;
        // for the nomal line y = mx + b
        float m = segmentQR.perpSlope();
        // b = y - mx using util::midPoint of segment QR
        float b = segmentQR.midpoint().y - m * segmentQR.midpoint().x;
        // y = mx + b
        intersection.y = m * intersection.x + b;
        return (intersection);
    }
    else if ((segmentPQ.slopeType() == SlopeType::kNormal) && (segmentQR.slopeType() == SlopeType::kInfinite)) {
        intersection.y = segmentPQ.midpoint().y;
        // for the normal line y = mx + b
        float m = segmentPQ.perpSlope();
        // b = y - mx using util::midPoint of segment PQ
        float b = segmentPQ.midpoint().y - m * segmentPQ.midpoint().x;
        // y = mx + b -> x = (y - b) / m
        intersection.x = (intersection.y - b) / m;
        return (intersection);
    }
    else if (segmentPQ.slopeType() == SlopeType::kNormal && segmentQR.slopeType() == SlopeType::kZero) {
        intersection.x = segmentPQ.midpoint().x;
        // for the nomal line y = mx + b
        float m = segmentPQ.perpSlope();
        // b = y - mx using util::midPoint of segment QR
        float b = segmentPQ.midpoint().y - m * segmentPQ.midpoint().x;
        // y = mx + b
        intersection.y = m * intersection.x + b;
        return (intersection);
    }
    else {
        // invlid triangle, set the circum-center to (0, 0)
        // TODO: fix?
        std::cout << "Invalid Triangle, circumcenter of something..." << std::endl;
        return Node();
    }
}