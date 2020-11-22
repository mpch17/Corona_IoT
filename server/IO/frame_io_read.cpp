#include "frame_io.hpp"

namespace corona
{
    // Constructor.
    frame_io_read::frame_io_read(const std::istream* instream, const std::string& filename)
        : input(instream), frame_io(filename)
    {

    }

    // Destructor.
    frame_io_read::~frame_io_read()
    {

    }

    // Open file.
    void frame_io_read::open()
    {

    }

    // Closes file.
    void frame_io_read::close()
    {

    }

    // Reads and parses frame.
//    frame frame_io_read::read() const
//    {

//    }
}
