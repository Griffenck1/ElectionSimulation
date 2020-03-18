#include "District.h"

/**
Helps make printing votes easier
*/
void PrintVote(std::string vote_name, std::map<std::string, int> vote){
	std::cout << std::endl;
	std::cout << vote_name << ":" << std::endl;
	for(std::pair<std::string, int> p : vote){
		std::cout << p.first << ": " << p.second << std::endl;
	}
	std::cout << std::endl;
	//prints a winner if this is the full results
	if(vote_name == "Full Results"){
		//Calculate the winner of the vote
		std::string winner = "NULL";
		int winner_votes = 0;
		for(std::pair<std::string, int> p : vote){
			if(p.second > winner_votes){
				winner = p.first;
				winner_votes = p.second;
			}
		}
		std::cout << "Congragulations, " << winner << " you've won!" << std::endl << std::endl; 
	}
}

/**
Converts strings to Party
*/
Party StringToParty(std::string s){
	if(s == "Party1"){
		return Party::Party1;
	}
	else if(s == "Party2"){
		return Party::Party2;
	}
	else if(s == "Party3"){
		return Party::Party3;
	}
	else{
		return Party::None;
	}
}

/**
Converts Party to strings to help with printing
*/
std::string PartyToString(Party p){
	if(p == Party::Party1){
		return "Party1";
	}
	else if(p == Party::Party2){
		return "Party2";
	}
	else if(p == Party::Party3){
		return "Party3";
	}
	else{
		return "None";
	}
}

/**
Returns a vector of all parties in the enum class
*/
std::vector<Party> GetParties(){
	return {Party::Party1, Party::Party2, Party::Party3, Party::None};
}

/**
Takes an integer as an argument and constructs a District
*/
District::District(int id){
	id_ = id;
	//Sets area equalt to a random int between 5 and 29
	area_ = rand() % (30 - 5) + 5;
	
	//Creates a vector of all parties
	std::vector<Party> parties = GetParties();
	
	//Uses the vector of parties in order to start each party with between 0-9 constituents in the district
	for(Party p : parties){
		voters_.insert(std::pair<Party, int>(p, rand() % 10));
	}
}

/**
Calculates and returns the total # of constituents in a district
*/
int District::CalculateTotalConstituents(){
	int pop = 0;
	for(std::pair<Party, int> pair : voters_){
		pop += pair.second;
	}
	return pop;
}

/**
Calcualtes which party has the most voters in a district and returns that 
Party
*/
Party District::MajorityParty(){
	int majority_count = -1;
	Party majority;
	for(std::pair<Party, int> p : voters_){
		if((p.second > majority_count) & (p.first != Party::None)){
			majority = p.first;
			majority_count = p.second;
		}
	}
	return majority;
}

/**
Returns the majority party in the district ignoring the party that is passed 
as a parameter
*/
Party District::MajorityParty(Party not_this_party){
	int majority_count = -1;
	Party majority;
	for(std::pair<Party, int> p : voters_){
		if((p.second > majority_count) & (p.first != Party::None) & (p.first != not_this_party)){
			majority = p.first;
			majority_count = p.second;
		}
	}
	return majority;
}

/**
Converts one contituent from their old party to their new partu
*/
void District::ConvertConstituent(Party old_party, Party new_party){
	if(voters_[old_party] > 0){
		voters_[old_party] -= 1;
		voters_[new_party] += 1;
	}
}

/**
Handles conducting votes in a district, then returns the vote as a map from
string (holds candidate's name) to int (holds how many votes were cast for them)
*/
std::map<std::string, int> District::ConductVote(std::vector<Candidate> candidates){
	//Initialized map from candidates to how many votes they have won
	std::map<std::string, int> vote_count;
	//Initializes a map from Party to a vector of candidates in that party
	std::map<Party, std::vector<Candidate>> party_members;
	for(Party p : GetParties()){
		party_members.insert(std::pair<Party,  std::vector<Candidate>>(p , std::vector<Candidate>{}));
	}
	for(Candidate c : candidates){
		vote_count.insert(std::pair<std::string, int>(c.name, 0));
		party_members.at(c.party).push_back(c);
	}
	
	for(std::pair<Party, int> pair : voters_){
		int count = 0;
		//for all voters in party
		while(count < pair.second){
			//this handles Party::None and Parties with no candidates
			if(party_members.at(pair.first).size() == 0){
				//If there is a majority party with constituents
				if(party_members[this->MajorityParty()].size() != 0){
					//Vote for a random member of the majority party
					vote_count[party_members.at(this->MajorityParty())[rand() % party_members.at(this->MajorityParty()).size()].name] += 1;
				}
				else{
					//If all parties except None have no candidates, vote for a random candidate
					vote_count[candidates[rand() % candidates.size()].name] += 1;
				}
			}
			else{
				//Cosntituents with a party other than None and candidates will vote for a random candiddate in their party
				vote_count[party_members.at(pair.first)[rand() % party_members.at(pair.first).size()].name] += 1;
			}
			count++;
		}
	}
	std::cout << "" << std::endl;
	
	return vote_count;
}

/**
Overloads << so that printing districts is easier
*/
std::ostream& operator<<(std::ostream& os, const District &d){
	os << "District " << d.id_ << ":" << std::endl;
	os << "square miles: " << d.area_ << std::endl;
	
	for(std::pair<Party, int> pair : d.voters_){
		os << PartyToString(pair.first) << ": " << pair.second << std::endl;
	}
	
	os << std::endl;
	
	return os;
}