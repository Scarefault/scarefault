#include "identifier/parser/Parser.h"
#include "identifier/collector/CollectorBase.hpp"
#include "identifier/collector/Language.hpp"
#include "generator/tester/TesterBase.hpp"
#include "generator/tester/TesterController.hpp"

using namespace Collector;
using namespace Tester;

int main( int argc, char **argv )
{
  srand( time( NULL ) );

  Parser parser( GRAILS );
  parser.parse();

  CollectorBase * collector_ptr = address_collector;
  TesterBase * tester = TesterBase::get_tester( collector_ptr->get_data() );

  tester->write_data();
}
