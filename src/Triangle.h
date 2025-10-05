#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>
#include <array>

#include "Util.h"
#include "Circle.h"
#include "node.h"
#include "segment.h"

class Node;
class Circle;

class Triangle
{
public:
    Node p, q, r;

    std::array<Node, 3ull> nodes;
    std::array<Segment, 3ull> segments;

    enum class State : unsigned char {
        kOkay,
        kInvalid,
    } state;

public:
    Triangle() = default;
    /// constructor with 3 nodes
    explicit Triangle(Node nodeP, Node nodeQ, Node nodeR);

    /// constructor with a segment and a node, remove
    Triangle(const Segment& s, const Node& n);

    ~Triangle() noexcept = default;

    // getters, setters, and node checkers ...
    bool isNodeInCircumCircle(const Node& n) const noexcept;

    // operators ...
    friend bool operator==(const Triangle& lhs, const Triangle& rhs) noexcept;
    friend bool operator!=(const Triangle& lhs, const Triangle& rhs) noexcept;

    // circumcircle functions ...
    bool containsNodesOf(const Triangle& tri) const noexcept;

    Circle circumCircle;

public:
    // util
    static Circle computeCircumCircle(
        const Node&,
        const Node&,
        const Node&
    ) noexcept;

    static Node computeIntersection(
        const Node&,
        const Node&,
        const Node&
    ) noexcept;

};

#endif // TRIANGLE_H
