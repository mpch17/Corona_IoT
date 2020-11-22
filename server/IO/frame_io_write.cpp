#include "frame_io.hpp"

namespace corona
{
    // Constructor.
    frame_io_write::frame_io_write(const std::ostream* outstream, const std::string& filename)
        : output(outstream), frame_io(filename)
    {

    }

    // Destructor.
    frame_io_write::~frame_io_write()
    {

    }

    // Opens stream.
    void frame_io_write::open()
    {

    }

    // Closes stream.
    void frame_io_write::close()
    {

    }

    // Writes frame to stream.
    void frame_io_write::write(const frame& f) const
    {

    }
}
