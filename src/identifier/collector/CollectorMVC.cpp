#include "CollectorMVC.hpp"

namespace Collector {
  CollectorMVC::CollectorMVC()
  : Collector::CollectorBase()
  {}

  void CollectorMVC::collect_data( const char * format, ... )
  {
    va_list arguments;
    va_start( arguments, format );

    std::vector<std::string> info_method;

    while( *format != EOL )
    {
      std::string collected_text;

      switch( *format )
      {
        case PACKAGE:
          this->collect_package( va_arg( arguments, char * ) );
          break;
        case CLASS:
          this->collect_class( va_arg( arguments, char * ) );
          break;
        case METHOD:
          collected_text.assign( va_arg( arguments, char * ) );
          info_method.push_back( collected_text );
          break;
        case PARAM:
          collected_text.assign( va_arg( arguments, char * ) );
          info_method.push_back( collected_text );
          break;
      }

      format++;
    }

    this->collect_methods( info_method );
  }

  void CollectorMVC::collect_package( std::string name )
  {
    this->data.set_package( name );
  }

  void CollectorMVC::collect_class( std::string name )
  {
    this->data.set_class( name );

    identify_category( name );
  }

  void CollectorMVC::identify_category( std::string name )
  {
    if( name.find( "Controller" ) != std::string::npos )
    {
      std::size_t found = name.find( "Controller" );
      std::string category = name.substr( found );
      std::string model_base = name.substr( 0, found );

      collect_proprieties( model_base );

      this->data.model_base = model_base;
      this->data.layer = category;
    } else
    {
      this->data.model_base = name;
      this->data.layer = "Domain";
    }
  }

  void CollectorMVC::collect_proprieties( std::string domain )
  {
    std::string content_file = Helper::extract_content_file( domain );

    if( !content_file.empty() )
    {
      std::vector<std::string> content = Helper::extract_words( content_file, " ={" );

      for( int i = 0; i < content.size(); i++ )
      {
        Collector::Propriety new_propriety;

        if( Helper::is_type( content[ i ] ) )
        {
          new_propriety.name = content[ i+1 ];
          new_propriety.type = content[ i ];

          data.proprieties.push_back( new_propriety );
        }

        if( !content[i].compare( "constraints" ) )
        {
          collect_constraints( content_file );
        }
      }
    }
  }

  void CollectorMVC::collect_constraints( std::string text )
  {
    std::size_t found = text.find( "constraints" );
    std::string sub = text.substr( found+11 );
    std::size_t bracket_found = sub.find( "}" );
    std::string substring = sub.substr( 0, bracket_found );

    std::vector<std::string> words = Helper::extract_words( substring, " ={:,(" );
    std::vector<Propriety> proprieties = data.proprieties;

    for( int i = 0; i < proprieties.size(); i++ )
    {
      if( !proprieties[ i ].name.compare( words[ 0 ] ) )
      {
        int k = 1;

        while( words[ k ].compare( ")" ) )
        {
          Collector::Constraint new_constraint;
          new_constraint.name = words[ k ];
          new_constraint.value = words[ k+1 ];

          data.proprieties[ i ].contraints.push_back( new_constraint );
          k += 2;
        }

          words.erase( words.begin(), words.begin()+k+1 );
      }
    }
  }
}