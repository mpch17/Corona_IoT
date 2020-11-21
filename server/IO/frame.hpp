#ifndef FRAME_HPP
#define FRAME_HPP

#include "matrix.hpp"
#include "node.hpp"
#include <string>

namespace corona
{
    // Data frame class.
    // Abstract version of Pandas dataframe.
    class frame : public matrix<unsigned short>
    {
    private:
        std::vector<std::vector<unsigned short>> graph;
        std::vector<node> nodes;

        void for_each_row(void (*mod)(std::vector<unsigned short>& row)) noexcept;
        short find_node(const node& n) const noexcept;
        template<typename func>
        node& find(func pred) throw();

    public:
        void add_node(const node& n) throw();
        std::string to_string() const noexcept;
        void create_edge(const node& n1, const node& n2, unsigned short people_count) throw();
        const std::vector<unsigned short>& operator[](unsigned i) const throw() override;
        void add_row(const std::vector<unsigned short>& row) override;
        bool has_edge(const node& n1, const node& n2) const throw();
        const std::vector<node>& get_nodes() const noexcept;
        void remove_node(float longitude, float latitude) noexcept;
    };
}

#endif
