#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

namespace corona
{
    // Matrix interface.
    template<typename T>
    class matrix
    {
    public:
        virtual ~matrix() {}
        virtual void add_row(const std::vector<T>& row) = 0;
        virtual void add_column(const std::vector<T>& column) = 0;
        virtual void delete_row(unsigned index) = 0;
        virtual void delete_column(unsigned index) = 0;
        virtual const std::vector<T>& operator[](unsigned index) const throw() = 0;
    };
}

#endif
