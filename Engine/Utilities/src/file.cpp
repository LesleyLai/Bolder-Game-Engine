#include "file.hpp"
#include "exception.hpp"

#include <fstream>

using namespace bolder;

std::string utility::load_file(const char* filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
      std::string contents;
      in.seekg(0, std::ios::end);
      contents.resize(static_cast<std::string::size_type>(in.tellg()));
      in.seekg(0, std::ios::beg);
      in.read(&contents[0], static_cast<std::streamsize>(contents.size()));
      in.close();
      return(contents);
    }
    auto message = std::string("cannot open file " ) + filename;
    throw Exception {message.c_str()};
}
