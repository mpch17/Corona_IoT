#include "node.hpp"

namespace corona
{
    // Constructor.
    node::node(const invalid_node_t& in)
    {
        this->invalid = true;
    }

    // Constructor.
    node::node(bool edge, float longitude, float latitude, unsigned long id,
                int node_index, unsigned long edge1_id, unsigned long edge2_id,
                unsigned short people_count)
        : id(id), node_index(node_index), edge1(edge1_id), edge2(edge2_id), edge(edge),
            people_count(people_count), longitude(longitude), latitude(latitude)
    {}

    // Getters.
    int node::get_index() const noexcept
    {
        return this->node_index;
    }

    unsigned long node::get_id() const noexcept
    {
        return this->id;
    }

    bool node::is_edge() const noexcept
    {
        return this->edge;
    }

    unsigned long node::get_edge1() const noexcept
    {
        return this->edge1;
    }

    unsigned long node::get_edge2() const noexcept
    {
        return this->edge2;
    }

    const float& node::get_latitude() const noexcept
    {
        return this->latitude;
    }

    const float& node::get_longitude() const noexcept
    {
        return this->longitude;
    }

    const unsigned short& node::get_people_count() const noexcept
    {
        return this->people_count;
    }

    // Setters.
    void node::set_index(int index) noexcept
    {
        this->node_index = index;
    }

    void node::set_people_count(unsigned short count) noexcept
    {
        this->people_count = count;
    }

    void node::increment_people_count(unsigned short increment) noexcept
    {
        this->people_count += increment;
    }

    // Equality operator.
    bool node::operator==(const node& n) const noexcept
    {
        if (this->invalid && n.invalid)
            return true;

        else if (this->invalid != n.invalid)
            return false;

        return n.people_count == this->people_count &&
            n.longitude == this->longitude &&
            n.latitude == this->latitude &&
            n.edge == this->edge &&
            n.id == this->id &&
            n.edge1 == this->edge1 &&
            n.edge2 == this->edge2 &&
            n.node_index == this->node_index &&
            n.value == this->value;
    }
}
