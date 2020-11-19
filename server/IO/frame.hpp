#ifndef FRAME_HPP
#define FRAME_HPP

#include "matrix.hpp"

namespace corona
{
    // Data frame class.
    // Abstract version of Pandas dataframe.
    class frame : public matrix
    {
    public:
        frame();
    };
}

#endif
