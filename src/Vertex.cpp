#include "Vertex.h"

Vertex::Vertex(float x, float y)
{
    this->x = x;
    this->y = y;
    this->isMinorRoad = false;
    this->isSeed = false;
}

bool Vertex::operator<(const Vertex other)
{
    return this->x < other.x || this->y < other.y;
}

bool Vertex::operator>(const Vertex other)
{
    return this->x > other.x || this->y > other.y;
}

bool Vertex::operator==(const Vertex other)
{
    return this->x == other.x && this->y == other.y;
}

void Vertex::connection(Vertex *other)
{
    bool alreadyIn = false;
    for (Vertex *n : this->neighbors)
    {
        if (n->operator==(*other))
        {
            alreadyIn = true;
            break;
        }
    }
    if (!alreadyIn)
    {
        this->neighbors.push_back(other);
    }

    alreadyIn = false;
    for (Vertex *n : other->neighbors)
    {
        if (n->operator==(*this))
        {
            alreadyIn = true;
            break;
        }
    }
    if (!alreadyIn)
    {
        other->neighbors.push_back(this);
    }
}
