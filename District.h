#ifndef DISTRCIT_H
#define DISTRICT_H

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

//This enum class represents the available political parties, as well as None
enum class Party {Party1, Party2, None};

Party string_to_party(std::string s);

std::string party_to_string(Party p);

//Helper fucntion helps to print votes from map format
void PrintVote(std::string vote_name, std::map<std::string, int> vote);

//This struct represents a Candidate, this holds their data, and Election will tell them when and where to campaign
struct Candidate{
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

class District{
	public:
		District(int id);
	
		int get_id(){return id_;};
		int get_area(){return area_;};
		std::map<Party, int> get_voters(){return voters_;};
	
		int CalculateTotalConstituents();
	
		friend std::ostream& operator<<(std::ostream& os, const District &d);
		
		Party MajorityParty();
	
		std::map<std::string, int> ConductVote(std::vector<Candidate>);
	
	private:
		std::map<Party, int> voters_;
		int area_;
		int id_;
};

#endif  // DISTRICT_H