#pragma once

#include <vector>

#include "Node.h"
#include "Vertex.h"
#include "Triangle.h"

class Triangulation {
public:
    explicit Triangulation(std::size_t);
    ~Triangulation() noexcept;

    std::size_t size() const noexcept;

    std::size_t maxTriangles;

    void rebuild();
    void incrementTriangleCount();
    void decrementTriangleCount();
private:

    void clear() noexcept;
    void build() noexcept;
    void bufferData(void);
    
    std::vector<Triangle> triangles;
    std::vector<Node> nodes;

    unsigned int vertexBufferHandle;
    unsigned int vertexArrayHandle;

    void runBowyerWatsonAlgorithm(void);
    void formatData(std::vector<Vertex>* data) const;
};