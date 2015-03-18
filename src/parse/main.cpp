#include <iostream>
#include <exception>

#include <alice/alice.hpp>
#include <alice/alice_simple.hpp>
#include <alice/defs.hpp>

#include <boost/filesystem.hpp>

using namespace dota;

int parse(boost::filesystem::path filePath)
{
	std::unordered_map<int, int> lifeTracker;

	std::string filename = filePath.filename().string();

	std::stringstream ss_deaths;
	std::stringstream ss_positions;

	alice_simple alice(filePath.string());

	// Parse until we get a valid game
	while (alice.parse() && alice.getGameinfo() == nullptr);

	auto game = alice.getGameinfo();
	int gameMode = game->getGameMode();
	// Filter for All Pick, Captain's Mode, Random Draft, Single Draft and All Random
	if (gameMode < MODE_AP || gameMode > MODE_AR) {
		std::cout << "Bad gamemode (" << gameMode << ")" << std::endl;
		return 1;
	}

	int tick = 0;
	// Main loop
	while (alice.parse()) {
		game = alice.getGameinfo();
		if (game == nullptr)
			continue;

		if (game->getState() != GAME_GAME)
			continue;

		for (int i = 0; i < alice.countPlayers(); i++) {
			auto player = alice.getPlayer(i);
			if (player == nullptr) {
				std::cout << "Fuck everything #1" << std::endl;
				continue;
			}

			dota:entity_hero* hero = nullptr;
			try {
				hero = player->getHero();
			} catch (dota::entityUnkownProperty& e) {
				continue;
			}
			if (hero == nullptr) {
				continue;
			}

			int cellwidth = 1 << hero->getCellbits();
			int cellX = hero->getCellX();
			int cellY = hero->getCellY();
			auto vecOrigin = hero->getOrigin();
			int x = (cellX * cellwidth - 16384) + vecOrigin[0];
			int y = (cellY * cellwidth - 16384) + vecOrigin[1];

			int lifeState = hero->getLifeState();
			//if (lifeState == STATE_ALIVE && (lifeTracker.find(i) == lifeTracker.end() || lifeTracker[i] != STATE_ALIVE)) {
			if (lifeState == STATE_DEAD && lifeTracker[i] != STATE_DEAD) {
				ss_deaths << x << ";" << y << ";" << player->getTeam() << ";" << game->getTime() - game->getTimeGamestart() << std::endl;
			} else if (tick % 1 == 0) {
				ss_positions << x << ";" << y << ";" << player->getTeam() << ";" << game->getTime() - game->getTimeGamestart() << std::endl;
			}
			lifeTracker[i] = lifeState;
		}

		tick++;
	}
	
	// Filter for games shorter than 10 minutes
	if (game->getTimeEnd() - game->getTimeGamestart() < 10 * 60) {
		std::cout << "Skipping game shorter than 10 minutes (" << (game->getTimeEnd() - game->getTimeGamestart()) / 60 << " min)" << std::endl;
		return 1;
	}

	boost::filesystem::create_directory(filePath.parent_path() / "deaths");
	std::cout << "Writing " << "deaths/" + filename + ".csv" << std::endl;
	std::ofstream f_deaths((filePath.parent_path() / ("deaths/" + filename + ".csv")).string());
	f_deaths.write(ss_deaths.str().c_str(), ss_deaths.str().size());
	f_deaths.close();

	boost::filesystem::create_directory(filePath.parent_path() / "positions");
	std::cout << "Writing " << "positions/" + filename + ".csv" << std::endl;
	std::ofstream f_positions((filePath.parent_path() / ("positions/" + filename + ".csv")).string());
	f_positions.write(ss_positions.str().c_str(), ss_positions.str().size());
	f_positions.close();

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: dota2parse <path>" << std::endl;
		return 1;
	}
	
	boost::filesystem::path dir(argv[1]);

	if (!boost::filesystem::is_directory(dir)) {
		std::cerr << "Path is not a directory" << std::endl;
		return 1;
	}

	for (boost::filesystem::directory_iterator it(dir), end; it != end; it++) {
		auto path = it->path();

		if (path.extension() != ".dem") {
			std::cout << "Skipping " << path << ": Not a demo file" << std::endl;
			continue;
		}

		std::cout << "Parsing demo " << path << std::endl;
		try {
			parse(path);
		} catch (std::exception const&  ex) {
			std::cout << "Failed" << std::endl;
		}
	}

	return 0;
}
