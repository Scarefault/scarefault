#include "Helper.hpp"

namespace Helper
{
    bool is_type( std::string token )
    {
      bool result = true;
      std::vector<std::string> types {
        "short", "Short", "int", "Integer", "long", "Long", "float", "Float",
        "double", "Double", "String", "Date", "List", "boolean" };

      for( int i = 0; i < types.size(); i++ )
      {
        if( !token.compare( types[ i ] ) )
        {
          result = true;
          break;
        } else
        {
          result = false;
        }
      }

      return result;
    }

    char * convert_string_to_cstring( std::string text )
    {
      char * cstring = new char[ text.size() + 1 ];
      std::copy( text.begin(), text.end(), cstring );
      cstring[ text.size() ] = '\0';

      return cstring;
    }

    std::string extract_content_file( std::string domain )
    {
      std::fstream domain_stream;

      std::string domain_file( PATH_DOMAIN );
      domain_file.append( domain );
      domain_file.append( ".groovy" );

      domain_stream.open( domain_file, READ );
      std::string content;

      if( domain_stream.is_open() )
      {
        std::string line;

        while( std::getline( domain_stream, line ) )
        {
          content.append( line );
        }

        domain_stream.close();
      } else
      {
        std::cout << "Unable to open "<< domain_file << "..." << std::endl;
      }

      return content;
    }

    std::vector<std::string>
    extract_words( std::string text, std::string delimiters )
    {
      char * cdelimiters = convert_string_to_cstring( delimiters );
      char * ctext = convert_string_to_cstring( text );

      std::vector<std::string> words;
      char * phrase = strtok( ctext, cdelimiters );

      while( phrase != NULL )
      {
        std::string token( phrase );
        words.push_back( token );
        phrase = strtok( NULL, cdelimiters );
      }

      delete[] cdelimiters;
      delete[] ctext;
      delete[] phrase;

      return words;
    }

  std::string remove_spaces( std::string input )
  {
    input.erase( std::remove( input.begin(), input.end(), ' ' ), input.end() );

    return input;
  }

  std::string convert_to_lower( std::string text )
  {
    std::string lower_text;
    std::locale locale;

    for( int i = 0; i < text.size(); i++ )
    {
      lower_text += std::tolower( text[ i ], locale );
    }

    return lower_text;
  }
}
