#ifndef FRAME_HPP
#define FRAME_HPP

#include "matrix.hpp"
#include "node.hpp"
#include <vector>
#include <string>

namespace corona
{
    // Data frame class.
    // Abstract version of Pandas dataframe.
    class frame : public matrix
    {
    private:
        std::vector<std::vector<unsigned short>> graph;
        std::vector<node> nodes;

        void for_each_row(void (*mod)(std::vector<unsigned short>& row)) noexcept;
        short find_node(const node& n) const noexcept;

    public:
        void add_node(const node& n) noexcept;
        std::string to_string() const noexcept;
        void create_edge(const node& n1, const node& n2) throw();
        const std::vector<unsigned short>& operator[](unsigned i) const throw();
    };
}

#endif
