#include "frame.hpp"
#include <stdexcept>

namespace corona
{
    // Adds node to graph.
    void frame::add_node(const node& n) noexcept
    {
        this->nodes.push_back(n);
        for_each_row([](std::vector<unsigned short>& row) {
            row.push_back(0);
        });

        this->graph.push_back(std::vector<unsigned short>(this->nodes.size(), 0));
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
    void frame::create_edge(const node& n1, const node& n2) throw()
    {
        short n1_idx = find_node(n1), n2_idx = find_node(n2);

        if (n1_idx < 0 || n2_idx < 0)
            throw std::invalid_argument("No nodes with longitude and latitude found.");

        this->graph[n1_idx][n2_idx] = 1;
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
    const std::vector<unsigned short>& frame::operator[](unsigned i) const throw()
    {
        if (i >= this->graph.size())
            throw std::invalid_argument("Index out of bounds on graph.");

        return this->graph[i];
    }
}
