#ifndef NODE_H
#define NODE_H

namespace corona
{
    class node
    {
    private:
        unsigned short people_count;
        float longitude, latitude;

    public:
        node(float longitude, float latitude, unsigned short people_count = 0);
        const float& get_latitude() const noexcept;
        const float& get_longitude() const noexcept;
        const unsigned short& get_people_count() const noexcept;
        void set_people_count(unsigned short count) noexcept;
        void increment_people_count(unsigned short increment) noexcept;
    };
}

#endif
