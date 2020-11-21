#ifndef NODE_H
#define NODE_H

namespace corona
{
    class node
    {
    private:
        unsigned short people_count;
        float longitude, latitude;
        bool edge;
        unsigned long id, edge1, edge2;
        int node_index, value;

    public:
        node(bool edge, float longitude, float latitude, unsigned long id,
            int node_index = -1, unsigned long edge1_id = 0, unsigned long edge2_id = 0,
            unsigned short people_count = 0);
        bool is_edge() const noexcept;
        int get_index() const noexcept;
        unsigned long get_id() const noexcept;
        unsigned long get_edge1() const noexcept;
        unsigned long get_edge2() const noexcept;
        const float& get_latitude() const noexcept;
        const float& get_longitude() const noexcept;
        const unsigned short& get_people_count() const noexcept;
        void set_index(int index) noexcept;
        void set_people_count(unsigned short count) noexcept;
        void increment_people_count(unsigned short increment) noexcept;
    };
}

#endif
