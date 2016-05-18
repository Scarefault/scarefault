#include "SpreaderData.hpp"

namespace Helper
{
  ADDRESS address_spreader;

  SpreaderData::SpreaderData()
  {
    address_spreader = this;
  }

  void SpreaderData::analiser_methods()
  {
    if( data_ptr->methods[0].name == "create")
    {
      write_test_create();
    }
  }

  void SpreaderData::write_data()
  {
    std::fstream test_stream;

    test_stream.open( TESTFILE, WRITE|APPEND );

    if( test_stream.is_open() )
    {
      test_stream << "package " << data_ptr->package_name << std::endl
        << std::endl
        < "import org.junit.*" << std::endl
        << "import grails.test.mixin.*" << std::endl
        << std::endl
        << "@TestFor(" << data_ptr->class_name << ")" << std::endl
        << "class " << data_ptr->class_name << "Tests {" << std::endl;

      test_stream.close();
    } else
    {
      std::cout << "Unable to open TESTFILE..." << std::endl;
    }
  }

  void SpreaderData::write_test_create()
  {
    std::fstream test_stream;

    test_stream.open( TESTFILE, WRITE|APPEND );

    if( test_stream.is_open() )
    {
      test_stream << "\tvoid testCreate() {" << std::endl
        << "\t\tdef model = controller.create()" << std::endl
        << "\t\tassert model.userInstance != null" << std::endl
        << "\t}\n}" << std::endl;

      test_stream.close();
    } else
    {
      std::cout << "Unable to open TESTFILE..." << std::endl;
    }
  }

  void SpreaderData::set_data( Helper::Data * ptr )
  {
      this->data_ptr = ptr;
  }
}
