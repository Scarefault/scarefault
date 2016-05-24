#include "analizer/parser/Parser.h"
#include "analizer/helper/CollectorData.hpp"
#include "generator/tester/TesterBase.hpp"
#include "generator/tester/TesterController.hpp"

using namespace Helper;
using namespace Tester;

int main( int argc, char **argv )
{
  Parser parser;
  parser.parse();

  CollectorData * collector_ptr = address_collector;
  TesterBase * tester = TesterBase::get_tester( collector_ptr->get_data() );

  tester->write_data();
}
