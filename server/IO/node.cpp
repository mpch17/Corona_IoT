#include "node.hpp"

namespace corona
{
    // Constructor.
    node::node(bool edge, float longitude, float latitude, unsigned short people_count)
        : edge(edge), people_count(people_count), longitude(longitude), latitude(latitude)
    {}

    // Getters.
    bool node::is_edge() const noexcept
    {
        return this->edge;
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
    void node::set_people_count(unsigned short count) noexcept
    {
        this->people_count = count;
    }

    void node::increment_people_count(unsigned short increment) noexcept
    {
        this->people_count += increment;
    }
}
