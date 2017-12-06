#pragma once

void info(const char* infoMsg);
void error(const char* errorMsgFormat, const char* reason);

void sdl_error(const char* errorMsgFormat);
void sdl_image_error(const char* errorMsgFormat);
