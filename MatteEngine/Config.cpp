#include "Config.h"
#include "Util.h"
#include <map>
#include <utility>
#include <string>
#include <fstream>
#include <spdlog\spdlog.h>

auto config_logger = spdlog::stdout_color_mt("Config.cpp");

std::vector<std::string> load_config_file(const char* filename) {
	return read_file(filename);
}

std::pair<std::string, int> get_pair_from_entry(std::string config_entry) {
	char *key, *value;
	char *str_copy = new char[config_entry.length() - 1];
	std::strcpy(str_copy, config_entry.c_str());
	char* token_p, *next_token;
	const char *delim = " ";
	rsize_t strmax = sizeof str_copy;

	token_p = strtok_s(str_copy, delim, &next_token);
	for (int i = 0; token_p != NULL; token_p = strtok_s(NULL, delim, &next_token)) {
		switch (i) {
		case 0:
			key = token_p;
			break;
		case 1:
			if (*token_p != '=') {
				config_logger->error("Error parsing a config entry: {}", config_entry);
			}
			break;
		case 2:
			value = token_p;
			break;
		}
		++i;
	}

	config_logger->info("Loading config value: {} = {}", key, value);
	return std::pair<std::string, int>(key, atoi(value));
}

Config::Config() : Config("default.cfg") {}

Config::Config(const char* config_file) {
	std::string loading_file(config_file);
	this->config_name = loading_file.substr(0, loading_file.find_last_of('.'));

	if (!validate_file_extension(loading_file, ".cfg")) {
		config_logger->error("Tried to load an invalid config file: extension should be cfg");
		loading_file = "default.cfg";
	}

	for (auto config_entry : load_config_file(loading_file.c_str())) {
		this->config_values.insert(get_pair_from_entry(config_entry));
	}
}

int Config::get_value(std::string config_key) {
	return this->config_values[config_key];
}

std::string Config::get_config_name() {
	return this->config_name;
}