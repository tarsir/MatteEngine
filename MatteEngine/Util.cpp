#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Graphics.h"
#include "Util.h"
#include "spdlog\spdlog.h"

auto util_logger = spdlog::stdout_color_mt("Util.h");

bool validate_file_extension(std::string filename, std::string valid_extension) {
	std::size_t extension_index = filename.rfind("." + valid_extension);
	if (extension_index != std::string::npos) {
		return true;
	}
	return false;
}

bool validate_file_extension(const char* filename, const char* valid_extension) {
	return validate_file_extension(std::string(filename), std::string(valid_extension));
}

std::vector< std::string > read_file(const char* filename) {
	util_logger->debug("opening file: {}", filename);
	std::vector< std::string > file_lines;
	std::string line;
	std::ifstream file_stream(filename);
	if (file_stream.is_open()) {
		while (getline(file_stream, line)) {
			util_logger->debug("reading line in mapfile: {}", line);
			file_lines.push_back(line);
		}
		file_stream.close();
	}

	return file_lines;
}

void die() {
	util_logger->info("Everything is dying");
	SDL_Delay(5000);
	exit(1);
}

