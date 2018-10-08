#pragma once
#include "SDL.h"
#include <vector>
#include <string>

bool validate_file_extension(std::string filename, std::string valid_extension);
bool validate_file_extension(const char* filename, const char* valid_extension);
std::vector< std::string > read_file(const char* filename);
void die();