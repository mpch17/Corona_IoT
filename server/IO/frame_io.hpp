#ifndef FRAME_IO_HPP
#define FRAME_IO_HPP

#include "frame.hpp"
#include <ostream>
#include <istream>

namespace corona
{
    // IO of frames.
    class frame_io
    {
    public:
        frame_io();
        virtual ~frame_io() {}
    };

    // Writing of frames.
    class frame_io_write : public frame_io
    {
    private:
        const std::ostream* output;

    public:
        frame_io_write(const std::ostream* outstream);
        ~frame_io_write();
    };

    // Reading of frames.
    class frame_io_read : public frame_io
    {
    private:
        const std::istream* input;

    public:
        frame_io_read(const std::istream* instream);
        ~frame_io_read();
    };
}

#endif
