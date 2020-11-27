#ifndef FRAME_HPP
#define FRAME_HPP

#include "matrix.hpp"
#include "node.hpp"
#include "../config.hpp"
#include <string>

#if NO_EXCEPT
#define HAS_EXCEPT noexcept
#else
#define HAS_EXCEPT throw()
#endif

namespace corona
{
    // Data frame class.
    // Abstract version of Pandas dataframe.
    class frame : public matrix<unsigned short>
    {
    private:
        std::vector<std::vector<unsigned short>> graph;
        std::vector<node> nodes;

        template<typename modifier>
        void for_each_row(modifier func) noexcept;
        short find_node(const node& n) const noexcept;
        template<typename predicate>
        node& find(predicate pred) HAS_EXCEPT;
        node& findby_id(const unsigned long& id) HAS_EXCEPT;
        void decrement_node_indices(unsigned start_index) noexcept;
        bool check_structure() const HAS_EXCEPT;

    public:
        void add_node(const node& n) HAS_EXCEPT;
        std::string to_string() const noexcept;
        void create_edge(const node& n1, const node& n2, unsigned short people_count) HAS_EXCEPT;
        const std::vector<unsigned short>& operator[](unsigned i) const HAS_EXCEPT override;
        void add_row(const std::vector<unsigned short>& row) override;
        void add_column(const std::vector<unsigned short>& column) override;
        void delete_row(unsigned index) override;
        void delete_column(unsigned index) override;
        bool has_edge(const node& n1, const node& n2) const HAS_EXCEPT;
        const std::vector<node>& get_nodes() const noexcept;
        void remove_node(const node& n) HAS_EXCEPT;
        bool has_node(const node& n) noexcept;
    };
}

#endif
