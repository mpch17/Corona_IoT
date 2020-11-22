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

        template<typename modifier>
        void for_each_row(modifier func) noexcept;
        short find_node(const node& n) const noexcept;
        template<typename predicate>
        node& find(predicate pred) throw();
        node& findby_id(const unsigned long& id) throw();
        void decrement_node_indices(unsigned start_index) noexcept;
        void check_structure() const throw();

    public:
        void add_node(const node& n) throw();
        std::string to_string() const noexcept;
        void create_edge(const node& n1, const node& n2, unsigned short people_count) throw();
        const std::vector<unsigned short>& operator[](unsigned i) const throw() override;
        void add_row(const std::vector<unsigned short>& row) override;
        void add_column(const std::vector<unsigned short>& column) override;
        void delete_row(unsigned index) override;
        void delete_column(unsigned index) override;
        bool has_edge(const node& n1, const node& n2) const throw();
        const std::vector<node>& get_nodes() const noexcept;
        void remove_node(const node& n);
        bool has_node(const node& n) noexcept;
    };
}

#endif
