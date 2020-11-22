#include "frame.hpp"
#include <stdexcept>
#include "../config.hpp"

namespace corona
{
    // Adds node to graph.
    void frame::add_node(const node& n) throw()
    {
        check_structure();

        if (has_node(n))
            return;

        else if (n.is_edge())
        {
            if (n.get_edge1() >= this->graph.size() || n.get_edge2() >= this->graph.size())
                throw std::invalid_argument("Edges do not exist in graph.");

            node n1 = findby_id(n.get_edge1());
            node n2 = findby_id(n.get_edge2());
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
    template<typename predicate>
    node& frame::find(predicate pred) throw()
    {
        for (node& n : this->nodes)
        {
            if (pred(n))
                return n;
        }

        throw std::invalid_argument("No node found.");
    }

    // Iterates over all row in graph.
    template<typename modifier>
    void frame::for_each_row(modifier func) noexcept
    {
        for (unsigned i = 0; i < this->graph.size(); i++)
        {
            func(this->graph[i]);
        }
    }

    // Converts frame into string representation.
    std::string frame::to_string() const noexcept
    {
        check_structure();

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
        check_structure();

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

    // Returns true if flow between the two nodes is greater than 0.
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

    // Adds column to graph matrix (adjacency matrix).
    void frame::add_column(const std::vector<unsigned short>& column)
    {
        throw std::runtime_error("Operation not supported.");
    }

    // Removes row from graph (adjacency matrix).
    void frame::delete_row(unsigned index)
    {
        this->graph.erase(this->graph.begin() + index);
    }

    // Removes column from graph (adjacency matrix).
    void frame::delete_column(unsigned index)
    {
        for_each_row([&index](std::vector<unsigned short>& row){
            row.erase(row.begin() + index);
        });
    }

    // Getter to all nodes.
    const std::vector<node>& frame::get_nodes() const noexcept
    {
        return this->nodes;
    }

    // Removes node from graph.
    // Handled differently if edge.
    void frame::remove_node(const node& n)
    {
        check_structure();

        if (n.is_edge())
        {
            node n1 = find([&n](const node& n_arg){ return n.get_edge1() == n.get_id(); });
            node n2 = find([&n](const node& n_arg){ return n.get_edge2() == n.get_id(); });
            this->graph[n1.get_index()][n2.get_index()] = 0;
        }

        else
        {
            if (n.get_index() >= this->nodes.size())
                throw std::invalid_argument("Cannot remove node: Index out of bounds.");

            delete_row(n.get_index());
            delete_column(n.get_index());
            this->nodes.erase(this->nodes.begin() + n.get_index());
            decrement_node_indices(n.get_index());
        }
    }

    // Decrements all node indices by one from given index position.
    void frame::decrement_node_indices(unsigned start_index) noexcept
    {
        for (unsigned i = start_index; i < this->nodes.size(); i++)
        {
            this->nodes[i].set_index(this->nodes[i].get_index() - 1);
        }
    }

    // Makes sure graph is square and has the same number of rows/columns as entries in nodes.
    // If something is wrong, an std::runtime_error is thrown.
    void frame::check_structure() const throw()
    {
        if (this->graph.size() > 0 && this->graph.size() != this->graph[0].size())
            throw std::runtime_error("Graph matrix is not square: Maybe the number of calls to delete_row and delete_column does not match.");

        else if (this->graph.size() != this->nodes.size())
            throw std::runtime_error("The number of stored nodes does not match the number of nodes in graph.");
    }

    // Checks whether node (vertex or edge) exists.
    bool frame::has_node(const node& n) const noexcept
    {
        try
        {
            if (n.is_edge())
            {
                node n1 = findby_id(n.get_edge1());
                node n2 = findby_id(n.get_edge2());

                return this->graph[n1.get_index()][n2.get_index()] > 0;
            }

            else
            {
                node found = findby_id(n.get_id());
                return true;
            }
        }

        catch (const std::invalid_argument& exc)
        {
                return false;
        }
    }

    // Finds node by ID.
    inline node& frame::findby_id(const unsigned long& id) throw()
    {
        return find([&id](const node& n){ return n.get_id() == id; });
    }
}

