#ifndef READER_HPP_
#define READER_HPP_

#include <string>

namespace psr {

    class Reader
    {
    private:
        bool is_open;

    public:
        Reader();
        Reader(const std::string& output_filename, const std::string& output_map_filename);
        void Open(const std::string& output_filename, const std::string& output_map_filename);
        void Close();
        inline bool IsOpen() { return is_open; };
        ~Reader();
    };

}

#endif