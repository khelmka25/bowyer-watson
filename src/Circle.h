#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>

#include "Util.h"
#include "node.h"

class Circle
{
public:
    Circle() = default;
    Circle(Node center_, float radius_) : center(center_), radius(radius_) {}

    inline bool contains(const Node& n) const noexcept
    {
        return util::distance(this->center, n) < radius;
    }

public:
    Node center;
    float radius;
};

#endif // CIRCLE_H
