#pragma once
struct Function
{
	std::string name;
	std::string(*function)(std::string parameters[]);
};
