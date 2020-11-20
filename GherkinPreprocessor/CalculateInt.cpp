// Integer calculate 
#include "Calculate.h"
#include "atmsp.h"
std::string Calculate::calculate_int(std::string& expression){
ATMSP<double> parser;
ATMSB<double> byteCode;
parser.parse(byteCode, expression, "");
int result =(int) byteCode.run();
std::string out = std::to_string(result);
return out;
}
