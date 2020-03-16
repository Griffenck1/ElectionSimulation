#include "Election.hpp"

int main(){
	//Set random number seed
	srand(time(NULL));
	std::vector<Candidate> candidates = {Candidate("Bob", Party::Party1, 0), Candidate("Jill", Party::Party2, 1)};
	std::cout << *ElectoralMap::Instance(candidates) << std::endl;
	PrintVote("Full Results", ElectoralMap::Instance(candidates)->CollectVotes());
	return 0;
}