#ifndef FRAME_IO_HPP
#define FRAME_IO_HPP

#include "frame.hpp"
#include <ostream>
#include <istream>
#include <string>

namespace corona
{
    // IO of frames.
    class frame_io
    {
    private:
        std::string filename;

    public:
        frame_io(const std::string& filename = "");
        virtual ~frame_io() {}
        virtual void open() = 0;
        virtual void close() = 0;
    };

    // Writing of frames.
    class frame_io_write : public frame_io
    {
    private:
        const std::ostream* output;

    public:
        frame_io_write(const std::ostream* outstream, const std::string& filename = "");
        ~frame_io_write();
        void open() override;
        void close() override;
        void write(const frame& f) const;
    };

    // Reading of frames.
    class frame_io_read : public frame_io
    {
    private:
        const std::istream* input;

    public:
        frame_io_read(const std::istream* instream, const std::string& filename = "");
        ~frame_io_read();
        void open() override;
        void close() override;
        frame read() const;
    };
}

#endif
