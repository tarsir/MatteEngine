#pragma once

#include <string>
#include <map>

class Config {
private:
	std::map<std::string, int> config_values;
	std::string config_name;
public:
	Config();
	Config(const char* config_file);
	int get_value(std::string config_key);
	std::string get_config_name();
};
