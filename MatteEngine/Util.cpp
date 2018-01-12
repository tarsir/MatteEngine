#include "Graphics.h"
#include "Util.h"
#include "spdlog\spdlog.h"

auto util_logger = spdlog::stdout_color_mt("Util.h");

void die() {
	util_logger->info("Everything is dying");
	SDL_Delay(5000);
	exit(1);
}

