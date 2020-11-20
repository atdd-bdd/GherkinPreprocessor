// Integer calculate 
#pragma warning( push )
#pragma warning( disable : 4244 )
#include "Calculate.h"
#include "atmsp.h"
std::string Calculate::calculate_double(std::string& expression){
ATMSP<double> parser;
ATMSB<double> byteCode;
parser.parse(byteCode, expression, "");
double result = byteCode.run();
std::string out = std::to_string(result);
return out;
}
#pragma warning( pop )
