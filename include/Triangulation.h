#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include "Node.h"
#include "Vertex.h"
#include "Triangle.h"

class Triangulation {
public:
    explicit Triangulation(std::size_t);
    ~Triangulation() noexcept;

    std::size_t size() const noexcept;

    std::size_t maxTriangleCount;

    void rebuild();
    void incrementTriangleCount();
    void decrementTriangleCount();
private:

    std::vector<Triangle> findInvalidTriangles(const Node* const) noexcept;

    void clear() noexcept;
    void build() noexcept;
    void bufferData(void) const noexcept;
    
    std::vector<Triangle> m_Triangles;

    unsigned int vertexBufferHandle;
    unsigned int vertexArrayHandle;

    void runBowyerWatsonAlgorithm(void);
    void formatData(std::vector<Vertex>* data) const;
};