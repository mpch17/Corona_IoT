#include "frame.hpp"
#include <stdexcept>
#include "../config.hpp"

namespace corona
{
    // Adds node to graph.
    void frame::add_node(const node& n) throw()
    {
        if (n.is_edge())
        {
            if (n.get_edge1() >= this->graph.size() || n.get_edge2() >= this->graph.size())
                throw std::invalid_argument("Edges do not exist in graph.");

            node n1 = find([&n](node& node_arg){ return n.get_edge1() == node_arg.get_id(); });
            node n2 = find([&n](node& node_arg){ return n.get_edge2() == node_arg.get_id(); });
            this->graph[n1.get_index()][n2.get_index()] = HALLWAY_CAPACITY - n.get_people_count();
        }

        else
        {
            this->nodes.push_back(n);
            for_each_row([](std::vector<unsigned short>& row) {
                row.push_back(0);
            });

            this->graph.push_back(std::vector<unsigned short>(this->nodes.size(), 0));
        }
    }

    // Finds node given predicate.
    template<typename func>
    node& frame::find(func pred) throw()
    {
        for (unsigned i = 0; i < this->nodes.size(); i++)
        {
            if (pred(this->nodes[i]))
                return this->nodes[i];
        }

        throw std::invalid_argument("No node found.");
    }

    // Iterates over all row in graph.
    void frame::for_each_row(void (*mod)(std::vector<unsigned short>& row)) noexcept
    {
        for (unsigned i = 0; i < this->graph.size(); i++)
        {
            mod(this->graph[i]);
        }
    }

    // Converts frame into string representation.
    std::string frame::to_string() const noexcept
    {
        std::string str = "";

        for (unsigned i = 0; i < this->graph.size(); i++)
        {
            for (unsigned j = 0; j < this->graph[i].size(); j++)
            {
                str += (((std::to_string(this->graph[i][j]) += ",")
                    += j) += this->graph[i].size() - 1 ? std::string("\n") : std::string("\t"));
            }
        }

        return str;
    }

    // Creates an edge between two nodes found by their longitude and latitude.
    void frame::create_edge(const node& n1, const node& n2, unsigned short people_count) throw()
    {
        short n1_idx = find_node(n1), n2_idx = find_node(n2);

        if (n1_idx < 0 || n2_idx < 0)
            throw std::invalid_argument("No nodes with longitude and latitude found.");

        this->graph[n1_idx][n2_idx] = people_count;
    }

    // Finds node by longitude and latitude. Returns -1 if not found.
    short frame::find_node(const node& n) const noexcept
    {
        for (unsigned i = 0; i < this->nodes.size(); i++)
        {
            if (this->nodes[i].get_longitude() == n.get_longitude() && this->nodes[i].get_latitude() == n.get_latitude())
                return i;
        }

        return -1;
    }

    // Returns row of graph adjacency matrix.
    bool frame::has_edge(const node& n1, const node& n2) const throw()
    {
        short n1_idx = find_node(n1), n2_idx = find_node(n2);

        if (n1_idx < 0 || n2_idx < 0)
            throw std::invalid_argument("No nodes with longitude and latitude found.");

        return this->graph[n1_idx][n2_idx] > 0;
    }

    // Accesses a row in adjacency matrix (graph).
    const std::vector<unsigned short>& frame::operator[](unsigned i) const throw()
    {
        if (i >= this->graph.size())
            throw std::invalid_argument("Index out of bound for graph.");

        return this->graph[i];
    }

    // Adds row to graph matrix (adjacency matrix).
    void frame::add_row(const std::vector<unsigned short>& row)
    {
        throw std::runtime_error("Operation not supported.");
    }

    // Getter to all nodes.
    const std::vector<node>& frame::get_nodes() const noexcept
    {
        return this->nodes;
    }

    // Removes node from graph.
    // Handled differently if edge.
    void frame::remove_node(float longitude, float latitude) noexcept
    {

    }
}
