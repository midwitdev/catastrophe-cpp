#include "html.hxx"

Element* Element::fromVector(const std::vector<Element*>& v)
{
    for (int i = 1; i < v.size(); i++) {
        v[i-1]->next = v[i];
    }

    return v[0];
}