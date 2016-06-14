#ifndef FILEBASE_HPP_
#define FILEBASE_HPP_

#include <vector>
#include <string>


#include "Method.hpp"


namespace Collector
{
  class FileBase
  {
    public:
      std::string class_name;
      std::vector<Method> methods;

      void insert_method( Collector::Method );
      void set_class( std::string );
  };
}

#endif // FILEBASE_HPP_
