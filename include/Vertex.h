#ifndef VERTEX_H
#define VERTEX_H

/** a substitute to using an array of 6 floats*/
struct Vertex
{
    Vertex() = default;
    Vertex(float t_x, float t_y, float t_z, float t_r, float t_g, float t_b)
        : x(t_x)
        , y(t_y)
        , z(t_z)
        , r(t_r)
        , g(t_g)
        , b(t_b) {

    }

    float x, y, z, r, g, b;
};

#endif // VERTEX_H
