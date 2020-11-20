

#include <iostream>
#include "Filename.h"
#include "Processor.h"
#include <iostream>
#include <regex>
#include "Pathname.h"
#include "Log.h"
void
mainhelper(int argc, char** argv, std::string& in, std::string& out, std::string& local, std::string& system);
int main(int argc, char *argv [])
{
    if (argc < 3) {
        std::cerr << "Usage in_file out_file [-system system_file_path]";
        exit(1);
        }
    std::string in;
    std::string out;
    std::string local = "";
    std::string system = "";
    mainhelper(argc, argv, in, out, local, system);
    local = Filename::get_directory(in); 
    std::cout << "Processing " << in << " to " << out << "\n";
    std::cout << "Local directory is " << local << " system directory is " << system << "\n"; 
    Pathname::set_local_path(local);
    Pathname::set_system_path(system);

    Processor p;
    p.process(Filename(in), Filename(out));
    Log::print(); 
    if (Log::is_terminate())
        exit(1);
    else
        exit(0); 
 
}

void mainhelper(int argc, char** argv, std::string& in, std::string& out, std::string& local, std::string& system)
{
    if (argc >= 3) {
        in = argv[1];
        out = argv[2];
    }
     for (int i = 3; i < argc; i += 2) {
       if (i + 1 >= argc)
            break;
        std::string option = argv[i];
        std::string value = argv[i + 1];
        if (option == "-system")
        {
            system = value;
        }
    }
}
