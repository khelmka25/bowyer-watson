#include "Triangulation.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Triangulation::Triangulation(std::size_t t_maxTriangles)
    : maxTriangles(t_maxTriangles)
    , triangles(maxTriangles)
    , nodes(maxTriangles)
{
    glGenVertexArrays(1, &vertexArrayHandle);
    glGenBuffers(1, &vertexBufferHandle);

    rebuild();
}

Triangulation::~Triangulation() noexcept {
    glDeleteVertexArrays(1, &vertexArrayHandle);
    glDeleteBuffers(1, &vertexBufferHandle);
}

void Triangulation::clear() noexcept {
    triangles.clear();
    nodes.clear();
}

void Triangulation::build() noexcept {
    runBowyerWatsonAlgorithm();
}

std::size_t Triangulation::size() const noexcept {
    return triangles.size();
}

void Triangulation::incrementTriangleCount() {
    constexpr std::size_t kIncrement = 5ull;
    maxTriangles = std::min(maxTriangles + kIncrement, 1000ull);
    rebuild();
}

void Triangulation::decrementTriangleCount() {
    constexpr std::size_t kDecrement = 5ull;
    maxTriangles = std::max(maxTriangles - kDecrement, kDecrement);
    rebuild();
}

void Triangulation::rebuild() {
    clear();
    build();
    bufferData();
}

void Triangulation::runBowyerWatsonAlgorithm(void)
{
    for (std::size_t i = 0ull; i < maxTriangles; i++) {
        nodes.emplace_back(util::randomValue(), util::randomValue());
    }

    // superTriangle must contain all nodes in the space ...
    Triangle superTriangle(Node(-5.0f, -2.0f), Node(0.0f, 7.0f), Node(5.0f, -2.0f));
    triangles.push_back(superTriangle); // first triangle must be superTriangle

    // other vars
    std::vector<Triangle> badTriangles = {};
    std::vector<Segment> polygon = {};

    /// Begin Bowyer Watson Algorithm -----------------------------------------
    // for each point in pointList do
    for (auto node = nodes.begin(); node != nodes.end(); node++)
    {
        // badTriangles := empty set
        badTriangles.clear();
        // for each triangle in triangulation do
        for (auto tri = triangles.begin(); tri != triangles.end(); tri++)
        {
            // if point is inside circumcircle of triangle
            if (tri->isNodeInCircumCircle(*node)) {
                tri->state = Triangle::State::kInvalid;
                badTriangles.push_back(*tri);
            }
        }

        // polygon := empty set
        polygon.clear();
        // for each triangle in badTriangles do
        for (auto tri = badTriangles.begin(); tri != badTriangles.end(); tri++)
        {
            // for each edge in triangle do
            for (int i = 0; i < 3; i++)
            {
                bool isSharedSeg = false;
                //  if edge is not shared by any other triangles in badTriangles
                for (auto tri2 = badTriangles.begin(); tri2 != badTriangles.end(); tri2++)
                {
                    // if triangles are the same
                    // skip this loop -> to next triangle
                    if (tri == tri2) continue;

                    for (int j = 0; j < 3; j++)
                    {
                        if (tri->segments.at(i) == tri2->segments.at(j))
                        {
                            isSharedSeg = true;
                        }
                    }
                }
                // add edge to polygon
                if (!isSharedSeg)
                    polygon.push_back(tri->segments.at(i));
            }
        }

        for (auto tri = triangles.begin(); tri != triangles.end(); tri++)
        {
            // if triangle contains a vertex from original super-triangle
            if (tri->state != Triangle::State::kOkay) {
                triangles.erase(tri--);
            }
        }

        // for each edge in polygon do
        for (auto seg = polygon.begin(); seg != polygon.end(); seg++)
        {
            // newTri := form a triangle from edge to point
            // add newTri to triangulation
            triangles.emplace_back(*seg, *node);
        }
    }
    /*
    // for each triangle in triangulation
    for(auto tri = this->triangulation.begin(); tri != this->triangulation.end(); tri++)
    {
        // if triangle contains a vertex from original super-triangle
        if(tri->containsNodesOf(superTriangle) )
            this->triangulation.erase(tri--);
    }*/
}

void Triangulation::bufferData(void)
{
    std::vector<Vertex> data;
    formatData(&data);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    if (data.size() > 0) {
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data.at(0), GL_STATIC_DRAW);
    }
    else {
        std::cout << "Error, triangles were not generated, no data to render.\n";
    }

    glBindVertexArray(vertexArrayHandle);
    // Position attributes of triangulation data
    // Takes up 3 floats: x, y, and z.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attributes of triangulation data
    // Takes up 3 floats: r, g, and b.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Triangulation::formatData(std::vector<Vertex>* data) const
{
    std::array<float, 3>  color;
    const float Z = 0.0f;

    for (std::vector<Triangle>::const_iterator tri = triangles.cbegin(); tri != triangles.cend(); tri++)
    {
        color = { std::abs(util::randomValue()), std::abs(util::randomValue()), std::abs(util::randomValue()) };
        data->emplace_back(tri->nodes.at(0).x, tri->nodes.at(0).y, Z, color.at(0), color.at(1), color.at(2));
        data->emplace_back(tri->nodes.at(1).x, tri->nodes.at(1).y, Z, color.at(0), color.at(1), color.at(2));
        data->emplace_back(tri->nodes.at(2).x, tri->nodes.at(2).y, Z, color.at(0), color.at(1), color.at(2));
    }
}