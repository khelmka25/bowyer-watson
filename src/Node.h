#pragma once

struct Node
{
    Node() = default;
    explicit Node(float t_x, float t_y)
        : x(t_x), y(t_y)
    {
    }

    float x, y;

    inline friend bool operator==(const Node &lhs, const Node &rhs) noexcept
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }

    inline friend bool operator!=(const Node &lhs, const Node &rhs) noexcept
    {
        return (lhs.x != rhs.x) || (lhs.y != rhs.y);
    }
};
