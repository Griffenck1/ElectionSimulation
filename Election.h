#ifndef ELECTION_H
#define ELECTION_H

#include<iostream>
#include<vector>

//This enum class represents the available political parties, as well as None
enum class Party {Party1, Party2, None};

Party string_to_party(std::string s);

std::string party_to_string(Party p);

//This struct represents a Candidate, this holds their data, and Election will tell them when and where to campaign
struct Candidate {
	std::string name;
	Party party;
	//id starts at 0 and ascends by 1 for each newly registered candidate
	int id;
	
	/**
	This constructor takes parameters and constructs a candidate, there is no default contructor as a defualt
	constructor should never be used in this program
	*/
	Candidate(std::string n, Party p, int i){
		name = n;
		party = p;
		id = i;
	}
	
};

class Election {
	public:
		Election(){
			//keeps track of how many time the while loop has run through
			int counter = 0;
			
			//registers candidates for each party
			while(counter < 2){
				std::string name;
				std::string party;
				std::cout << "Register candidate for party " << counter + 1 << ":" << std::endl;
				std::cin >> name;
				std::cin >> party;
				candidates_.push_back(Candidate(name, string_to_party(party), counter));
				counter++;
			}
		}
	
		std::vector<Candidate> get_candidates() { return candidates_; };
	
	private:
		std::vector<Candidate> candidates_;
};

#endif  // ELECTION_H