#include "Lines.h"
 std::list<std::string>& Lines::get_data() {
	return data;
}
 Lines::Lines() {

}
 void Lines::print_lines(std::ostream& out) {

	for (std::string& it : data) {
		out << it << "*" << "\n";
	}

}

 Lines::Lines(const std::string array[], const int size) {
	for (int i = 0; i < size; i++)
	{
		data.push_back(array[i]);
	}
}

 bool Lines::write_lines(Filename name) {
	std::ofstream myfile;
	myfile.open(name.get_value());
	if (!myfile.good())
		Log::write(LogType::SEVERE, "Unable to open for writing " + name.get_value());
	for (auto& it : data) {
		myfile << it << "\n";
	}
	myfile.close();
	if (!myfile.good())
		Log::write(LogType::SEVERE, "Error writing " + name.get_value());
	return myfile.good();
}

 bool Lines::read_lines(Filename name) {
	std::ifstream myfile;
	myfile.open(name.get_value());
	if (!myfile.good()) {
		Log::write(LogType::SEVERE, "Unable to open for reading " + name.get_value());
	}
	if (!name.isCSV())
	{
		std::string line;
		while (std::getline(myfile, line)) {
			data.push_back(line);
		}
	}
	else
	{
		std::string line;
		while (std::getline(myfile, line)) {
			std::vector<std::string> tokens = CSVParser::readCSVRow(line);
			std::string line_updated = "|";
			for (std::string t : tokens)
			{
				line_updated += t + "|";
			}
			data.push_back(line_updated);
		}
	}

	myfile.close();
	return myfile.good();
}

