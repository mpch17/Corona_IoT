#include "flow_graph.hpp"
#include <flow_path.hpp>

namespace corona
{
    // Initialises values to flow_graph object.
    void init_flow_graph(flow_graph& fg, const frame& f) noexcept
    {
        fg.nodes = f.get_nodes();

        for (unsigned i = 0; i < f.get_nodes().size(); i++)
        {
            fg.adj_matrix.push_back(std::vector<int>(f[i].size(), 0));

            for (unsigned j = 0; j < f[i].size(); j++)
            {
                fg.adj_matrix[i][j] = f[i][j];
            }
        }
    }

    // Creates instance of flow_graph given frame.
    flow_graph parse_frame(const frame& f) noexcept
    {
        flow_graph fg;
        init_flow_graph(fg, f);

        return fg;
    }

    // Returns matrix.
    std::vector<std::vector<int>> flow_graph::get_matrix() const noexcept
    {
        return this->adj_matrix;
    }

    // Getter to all nodes in flow graph.
    std::vector<node> flow_graph::get_nodes() const noexcept
    {
        return this->nodes;
    }

    // Returns edge flow. Both ares must be indices in adjacency matrix.
    int flow_graph::get_value(const unsigned long& v1, const unsigned long& v2) const noexcept
    {
        return this->adj_matrix[v1][v2];
    }

    // Computes path with maximum flow.
    void flow_graph::compute_path(const int& source, const int& sink) noexcept
    {
        this->flow = FordFulkerson(this->adj_matrix, source, sink);
    }

    // Returns path and flow in pair. Ket is path and value is flow.
    const std::pair<std::vector<int>, int>& flow_graph::get_flow() const noexcept
    {
        return this->flow;
    }
}
