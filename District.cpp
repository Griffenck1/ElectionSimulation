#include "District.h"

void PrintVote(std::string vote_name, std::map<std::string, int> vote){
	std::cout << vote_name << ":" << std::endl;
	for(std::pair<std::string, int> p : vote){
		std::cout << p.first << ": " << p.second << std::endl;
	}
	std::cout << std::endl;
}

//converts strings to Party
Party string_to_party(std::string s){
	if(s == "Party1"){
		return Party::Party1;
	}
	else if(s == "Party2"){
		return Party::Party2;
	}
	else{
		return Party::None;
	}
}

//converts Party to strings
std::string party_to_string(Party p){
	if(p == Party::Party1){
		return "Party1";
	}
	else if(p == Party::Party2){
		return "Party2";
	}
	else{
		return "None";
	}
}

std::vector<Party> GetParties(){
	return {Party::Party1, Party::Party2, Party::None};
}

District::District(int id){
	id_ = id;
	//Sets area equalt to a random int between 5 and 29
	area_ = rand() % (30 - 5) + 5;
	
	//Creeates a vector of all parties
	std::vector<Party> parties {Party::Party1, Party::Party2, Party::None};
	
	//Uses the vector of parties in order to start each party with between 0-9 constituents in the district
	for(Party p : parties){
		voters_.insert(std::pair<Party, int>(p, rand() % 10));
	}
}

Party District::MajorityParty(){
	int majority_count = 0;
	Party majority;
	for(std::pair<Party, int> p : voters_){
		if((p.second > majority_count) & (p.first != Party::None)){
			majority = p.first;
			majority_count = p.second;
		}
	}
	return majority;
}

std::map<std::string, int> District::ConductVote(std::vector<Candidate> candidates){
	//Initialized map from candidates to how many votes they have won
	std::map<std::string, int> vote_count;
	//Initializes a map from Party to a vector of candidates in that party
	std::map<Party, std::vector<Candidate>> party_members = {{Party::Party1, std::vector<Candidate>{}}, {Party::Party2, std::vector<Candidate>{}}, {Party::None, std::vector<Candidate>{}}};
	for(Candidate c : candidates){
		vote_count.insert(std::pair<std::string, int>(c.name, 0));
		party_members.at(c.party).push_back(c);
	}
	
	for(std::pair<Party, int> pair : voters_){
		int count = 0;
		while(count < pair.second){
			//this handles Party::None and Parties with no candidates
			if(party_members.at(pair.first).size() == 0){
				if(party_members[this->MajorityParty()].size() != 0){
					vote_count[party_members.at(this->MajorityParty())[rand() % party_members.at(this->MajorityParty()).size()].name] += 1;
				}
				else{
					vote_count[candidates[rand() % candidates.size()].name] += 1;
				}
			}
			else{
				vote_count[party_members.at(pair.first)[rand() % party_members.at(pair.first).size()].name] += 1;
			}
			count++;
		}
	}
	std::cout << "" << std::endl;
	
	return vote_count;
}

int District::CalculateTotalConstituents(){
	int pop;
	for(std::pair<Party, int> pair : voters_){
		pop += pair.second;
	}
	return pop;
}

std::ostream& operator<<(std::ostream& os, const District &d){
	os << "District " << d.id_ << ":" << std::endl;
	os << "square miles: " << d.area_ << std::endl;
	
	for(std::pair<Party, int> pair : d.voters_){
		os << party_to_string(pair.first) << ": " << pair.second << "    " << std::endl;
	}
	
	return os;
}