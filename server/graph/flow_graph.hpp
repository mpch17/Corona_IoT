#ifndef FLOW_GRAPH_HPP
#define FLOW_GRAPH_HPP

#include "graph.hpp"
#include "../IO/frame.hpp"
#include "../IO/node.hpp"
#include <utility>

namespace corona
{
    class flow_graph : public graph<node, int>
    {
    private:
        std::vector<std::vector<int>> adj_matrix;
        std::vector<node> nodes;
        std::pair<std::vector<int>, int> flow;

        friend void init_flow_graph(flow_graph& fg, const frame& f) noexcept;

    public:
        std::vector<std::vector<int>> get_matrix() const noexcept override;
        std::vector<node> get_nodes() const noexcept override;
        int get_value(const unsigned long& v1, const unsigned long& v2) const noexcept override;
        void compute_path(const int& source, const int& sink) noexcept;
        const std::pair<std::vector<int>, int>& get_flow() const noexcept;
    };

    flow_graph parse_frame(const frame& f) noexcept;
}

#endif
