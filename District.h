#ifndef DISTRCIT_H
#define DISTRICT_H

#include <iostream>
#include <vector>
#include <map>
#include <math.h> 
#include <stdio.h> //Random # generation
#include <stdlib.h> //Random # generation
#include <time.h> //Random # generation

//This enum class represents the available political parties, as well as None
enum class Party {Party1, Party2, None};

Party string_to_party(std::string s);

std::string party_to_string(Party p);

std::vector<Party> GetParties(); 

void PrintVote(std::string vote_name, std::map<std::string, int> vote);

//This struct represents a Candidate, this holds their data, and Election will tell them when and where to campaign
struct Candidate{
	std::string name;
	Party party;
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
		
		Party MajorityParty();
	
		Party MajorityParty(Party not_this_party);
	
		void ConvertConstituent(Party old_party, Party new_party);
	
		std::map<std::string, int> ConductVote(std::vector<Candidate>);
	
		friend std::ostream& operator<<(std::ostream& os, const District &d);
	
	private:
		std::map<Party, int> voters_;
		int area_;
		int id_;
};

#endif  // DISTRICT_H