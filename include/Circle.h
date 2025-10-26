#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include <array>
#include <iostream>

#include "Util.h"
#include "node.h"

class Circle
{
public:
    Circle() = default;
    Circle(Node t_center, float t_radius);

    // create a circle that intersects all three nodes
    Circle(Node, Node, Node);

    inline const Node& center() const noexcept {
        return m_Center;
    }

    inline const float& radius() const noexcept {
        return m_Radius;
    }

    inline bool contains(const Node& n) const noexcept {
        const float distance = m_Center.distanceTo(n);
        return distance <= m_Radius;
    }

private:
    static Node locateCenter(const Node&, const Node&, const Node&) noexcept;

private:
    Node m_Center;
    float m_Radius;
};

#endif // CIRCLE_H
