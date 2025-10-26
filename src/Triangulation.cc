#include "Triangulation.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Triangulation::Triangulation(std::size_t t_maxTriangles)
    : maxTriangleCount(t_maxTriangles)
    , m_Triangles(maxTriangleCount) {
    glGenVertexArrays(1, &vertexArrayHandle);
    glGenBuffers(1, &vertexBufferHandle);

    rebuild();
}

Triangulation::~Triangulation() noexcept {
    glDeleteVertexArrays(1, &vertexArrayHandle);
    glDeleteBuffers(1, &vertexBufferHandle);
}

std::vector<Triangle> Triangulation::findInvalidTriangles(const Node* const node) noexcept {
    std::vector<Triangle> invalidTriangles{};
    // for each triangle in triangulation do
    for (auto i = 0ull; i < m_Triangles.size(); i++) {
        Triangle* const triangle = &m_Triangles[i];
        // if point is inside circumcircle of triangle
        if (triangle->circumCircle.contains(*node)) {
            triangle->state = Triangle::State::kInvalid;
            invalidTriangles.push_back(*triangle);
        }
    }

    return invalidTriangles;
}

void Triangulation::clear() noexcept {
    m_Triangles.clear();
}

void Triangulation::build() noexcept {
    runBowyerWatsonAlgorithm();
}

std::size_t Triangulation::size() const noexcept {
    return m_Triangles.size();
}

void Triangulation::incrementTriangleCount() {
    constexpr std::size_t kIncrement = 5ull;
    maxTriangleCount = std::min(maxTriangleCount + kIncrement, 1000ull);
    std::cout << "Triangle Count Increased to " << maxTriangleCount << std::endl;
    rebuild();
}

void Triangulation::decrementTriangleCount() {
    constexpr std::size_t kDecrement = 5ull;
    maxTriangleCount = std::max(maxTriangleCount - kDecrement, kDecrement);
    std::cout << "Triangle Count Decreased to " << maxTriangleCount << std::endl;
    rebuild();
}

void Triangulation::rebuild() {
    clear();
    build();

    if (m_Triangles.empty()) {
        std::cerr << "Error: no triangles were generated!" << std::endl;
        return;
    }

    bufferData();
}

void Triangulation::runBowyerWatsonAlgorithm(void) {
    m_Triangles.clear();
    std::vector<Node> nodes{};
    nodes.reserve(maxTriangleCount);

    for (std::size_t i = 0ull; i < maxTriangleCount; i++) {
        const Node node(util::randomValue(), util::randomValue());
        nodes.push_back(node);
    }

    // superTriangle must contain all nodes in the space ...
    // the screen space is +/- 1 unit, a circle with radius = sqrt(2) at the origin covers this space
    // create a triangle whose base is horizontal below the screen that encloses this circle:
    //    /|
    //   / |
    //  / H|
    // /---|
    // Triangle super(Node(-5.0f, -2.0f), Node(0.0f, 7.0f), Node(5.0f, -2.0f));
    Triangle super(Node(-4.f, -1.5f), Node(1.5f, -1.5f), Node(1.5f, 4.f));
    m_Triangles.push_back(super); // first triangle must be superTriangle

    /// Begin Bowyer Watson Algorithm -----------------------------------------
    // for each point in pointList do
    for (auto nodeIdx = 0ull; nodeIdx < nodes.size(); nodeIdx++) {
        const Node* const node = &nodes[nodeIdx];
        // badTriangles := empty set
        std::vector<Triangle> invalidTriangles = findInvalidTriangles(node);

        // polygon := empty set
        std::vector<Segment> freeSegments{};
        // for each triangle in badTriangles do
        for (auto j = 0ull; j < invalidTriangles.size(); j++) {
            const Triangle* const triangleJ = &invalidTriangles[j];

            // for each edge in triangle do
            for (auto k = 0ull; k < 3ull; k++) {
                bool sharesSegment = false;
                // if edge is not shared by any other triangles in badTriangles
                for (auto l = 0ull; l < invalidTriangles.size(); l++) {
                    const Triangle* const triangleL = &invalidTriangles[l];
                    // if triangles are the same
                    // skip this loop -> to next triangle
                    if (j == l) {
                        continue;
                    }

                    for (auto m = 0ull; m < 3ull; m++) {
                        if (triangleJ->segments[k] == triangleL->segments[m]) {
                            sharesSegment = true;
                        }
                    }
                }

                // add edge to polygon
                if (!sharesSegment) {
                    freeSegments.push_back(triangleJ->segments.at(k));
                }
            }
        }

        for (auto tri = m_Triangles.begin(); tri != m_Triangles.end(); tri++) {
            // if triangle contains a vertex from original super-triangle
            if (tri->state != Triangle::State::kValid) {
                m_Triangles.erase(tri--);
            }
        }

        // for each edge in polygon do
        for (auto segmentIdx = 0ull; segmentIdx < freeSegments.size(); segmentIdx++) {
            const Segment* const segment = &freeSegments[segmentIdx];
            // newTri := form a triangle from edge to point
            // add newTri to triangulation
            const Triangle triangle(*segment, *node);
            m_Triangles.push_back(triangle);
        }
    }

    // for each triangle in triangulation
    for (auto i = 0ull; i < m_Triangles.size(); i++) {
        Triangle* const triangle = &m_Triangles[i];
        if (triangle->containsNodesOf(super)) {
            triangle->state = Triangle::State::kInvalid;
        }
    }

    auto end = std::remove_if(m_Triangles.begin(), m_Triangles.end(), [](auto& triangle){
        return triangle.state != Triangle::State::kValid;
    });

    m_Triangles.erase(end, m_Triangles.end());
}

void Triangulation::bufferData(void) const noexcept {

    std::vector<Vertex> vertexBuffer{};
    formatData(&vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

    glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(Vertex), &vertexBuffer.at(0), GL_STATIC_DRAW);

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

void Triangulation::formatData(std::vector<Vertex>* vertexBuffer) const {
    vertexBuffer->reserve(3ull * m_Triangles.size());

    for (auto i = 0ull; i < m_Triangles.size(); i++) {
        const Triangle* const tri = &m_Triangles[i];

        std::array<float, 3> color{
            std::abs(util::randomValue()),
            std::abs(util::randomValue()),
            std::abs(util::randomValue())
        };

        vertexBuffer->emplace_back(tri->nodeP.x, tri->nodeP.y, 0.f, color[0], color[1], color[2]);
        vertexBuffer->emplace_back(tri->nodeQ.x, tri->nodeQ.y, 0.f, color[0], color[1], color[2]);
        vertexBuffer->emplace_back(tri->nodeR.x, tri->nodeR.y, 0.f, color[0], color[1], color[2]);
    }
}