#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace corona
{
    // Graph interface.
    template<typename N, typename W>
    class graph
    {
    public:
        virtual ~graph() {}
        virtual std::vector<std::vector<W>> get_matrix() const noexcept = 0;
        virtual std::vector<N> get_nodes() const noexcept = 0;
        virtual W get_value(const unsigned long& v1, const unsigned long& v2) const noexcept = 0;
    };
}

#endif
