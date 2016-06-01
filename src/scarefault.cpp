#include "analizer/parser/Parser.h"
#include "analizer/helper/CollectorData.hpp"
#include "generator/tester/TesterBase.hpp"
#include "generator/tester/TesterController.hpp"

using namespace Helper;
using namespace Tester;

int main( int argc, char **argv )
{
  srand( time( NULL ) );

  Parser parser;
  parser.parse();

  CollectorData * collector_ptr = address_collector;
  TesterBase * tester = TesterBase::get_tester( collector_ptr->get_data() );

  // It is commented because some changes need to be made to work properly
  //
  //tester->write_data();
}
