#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>

#include "Util.h"
#include "node.h"

class Circle
{
public:
    Circle() = default;
    Circle(Node t_center, float t_radius)
        : center(t_center)
        , radius(t_radius) {

    }

    inline bool contains(const Node& n) const noexcept
    {
        return util::distance(this->center, n) <= radius;
    }

public:
    Node center;
    float radius;
};

#endif // CIRCLE_H
