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
	/*HeatmapManager hmm;
	hmm.ReadData("../src/test.csv");
	hmm.CreateHeatmap();
	hmm.CreateImage();*/
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

			int lifeState = player->getHero()->getLifeState();
			if (lifeState == STATE_DEAD && lifeTracker[i] != STATE_DEAD) {
				std::cout << player->getName() << " died! Oh noes! " << std::endl;
				deaths++;
			}
			lifeTracker[i] = lifeState;
		}
	}

	std::cout << "Total deaths: " << deaths << std::endl;

	return 0;

	std::cout << "Waiting for players..." << std::endl;
	while (alice.parse()) {
		int playerCount = alice.countPlayers();
		std::cout << "Player count: " << playerCount << std::endl;

		if (playerCount > 0) {
			for (int i = 0; i < playerCount; i++) {
				auto player = alice.getPlayer(i);
				std::cout << player->getName() << std::endl;
			}
			std::cin.get();
		}
	}

	

	//std::cout << "Connected players: " << game->getConnectedPlayers() << std::endl;

	return 0;
}
