#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

class Vertex
{
    public:
        Vertex(float x, float y);
        bool operator<(const Vertex other);
        bool operator>(const Vertex other);
        bool operator==(const Vertex other);

        void connection(Vertex *other);

        std::vector<Vertex*> neighbors;
        float x;
        float y;
        bool isMinorRoad;
        bool isSeed;

    private:
};

#endif // VERTEX_H
