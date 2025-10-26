#pragma once

#include <limits>
#include <cmath>

class Node
{
public:
    Node() = default;
    explicit Node(float t_x, float t_y)
        : x(t_x), y(t_y) {

        static unsigned int idSequence = 0;
        id = idSequence++;
    }

    // copy ctor: inherit other id
    Node(const Node& other) = default;
    Node(Node&& other) = default;
    Node& operator=(const Node& other) = default;
    Node& operator=(Node&& other) = default;

    float distanceTo(const Node& other) const noexcept {
        const float dx = other.x - x;
        const float dy = other.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    inline friend bool operator==(const Node& lhs, const Node& rhs) noexcept {
        // const float dx = lhs.x - rhs.x;
        // const float dy = lhs.y - rhs.y;
        // constexpr auto eps = std::numeric_limits<float>::epsilon();
        // return (std::fabs(dx) < eps) && (std::fabs(dy) < eps);
        return lhs.id == rhs.id;
    }

    inline friend bool operator!=(const Node& lhs, const Node& rhs) noexcept {
        return !(lhs == rhs);
    }

    float x, y;
    unsigned int id;
};
