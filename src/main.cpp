#include <iostream>
#include <exception>

#include <alice/alice.hpp>
#include <alice/alice_simple.hpp>

using namespace dota;

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: example <file>" << std::endl;
		return 1;
	}

	alice_simple alice(argv[1]);

	return 0;
}
