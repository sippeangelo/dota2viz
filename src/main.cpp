#include <iostream>
#include <exception>

#include <alice/alice.hpp>
#include <alice/alice_simple.hpp>
#include <alice/defs.hpp>

#include "HeatmapManager.h"

using namespace dota;

std::unordered_map<int, int> lifeTracker;

int main(int argc, char **argv) {
	
	////////////////////////////////////////////////////////////
	// Heatmap stuff 
	////////////////////////////////////////////////////////////
	HeatmapManager hmm;
	//hmm.ReadData();
	hmm.CreateHeatmap("../../replays/");
	//hmm.CreateImage();
	////////////////////////////////////////////////////////////
	// Heatmap not stuff
	////////////////////////////////////////////////////////////
	
	if (argc != 2) {
		std::cerr << "Usage: example <file>" << std::endl;
		return 1;
	}

	alice_simple alice(argv[1]);

	// Parse until we get a valid game
	while (alice.parse() && alice.getGameinfo() == nullptr);

	auto game = alice.getGameinfo();
	int gameMode = game->getGameMode();
	// Filter for All Pick, Captain's Mode, Random Draft, Single Draft and All Random
	if (gameMode < MODE_AP || gameMode > MODE_AR) {
		std::cout << "Bad gamemode (" << gameMode << ")" << std::endl;
		return 1;
	}

	int deaths = 0;
	// Main loop
	while (alice.parse()) {
		auto game = alice.getGameinfo();
		if (game == nullptr)
			continue;

		if (game->getState() != GAME_GAME)
			continue;

		for (int i = 0; i < alice.countPlayers(); i++) {
			auto player = alice.getPlayer(i);
			auto hero = player->getHero();

			int lifeState = hero->getLifeState();
			//if (lifeState == STATE_ALIVE && (lifeTracker.find(i) == lifeTracker.end() || lifeTracker[i] != STATE_ALIVE)) {
			if (lifeState == STATE_DEAD && lifeTracker[i] != STATE_DEAD) {
				int cellwidth = 1 << hero->getCellbits();
				int cellX = hero->getCellX();
				int cellY = hero->getCellY();
				auto vecOrigin = hero->getOrigin();
				int x = (cellX * cellwidth - 16384) + vecOrigin[0];
				int y = (cellY * cellwidth - 16384) + vecOrigin[1];

				std::cout << x << ";" << y << ";" << player->getTeam() << ";" << game->getTime() - game->getTimeGamestart() << std::endl;
			}
			lifeTracker[i] = lifeState;
		}
	}

	return 0;
}
