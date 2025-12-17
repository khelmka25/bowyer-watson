#pragma once

#include <iostream>
#include <cmath>
#include <array>

#include "Util.h"
#include "Circle.h"
#include "Node.h"
#include "Segment.h"

class Node;
class Circle;

class Triangle
{
public:
    Triangle() = default;
    /// constructor with 3 nodes
    explicit Triangle(Node nodeP, Node nodeQ, Node nodeR);
    explicit Triangle(const Segment& s, const Node& n);

    // operators ...
    friend bool operator==(const Triangle& lhs, const Triangle& rhs) noexcept;
    friend bool operator!=(const Triangle& lhs, const Triangle& rhs) noexcept;

    bool containsNodesOf(const Triangle& other) const noexcept;

public:
    Node nodeP, nodeQ, nodeR;

    // std::array<Node, 3ull> nodes;
    std::array<Segment, 3ull> segments;

    enum class State : unsigned char {
        kValid,
        kInvalid,
    } state = State::kValid;

    Circle circumCircle;
};
