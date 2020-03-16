#include "ElectoralMap.h"

//Helps ensure that only one instance of class can exist at a time
ElectoralMap* ElectoralMap::instance_ = NULL;

ElectoralMap* ElectoralMap::Instance(std::vector<Candidate> candidates){
	if(!instance_){
		instance_ = new ElectoralMap(candidates);
	}
	return instance_;
}

int ElectoralMap::CalculateTotalConstituents(){
	int total;
	for(District d : districts_){
		total += d.CalculateTotalConstituents();
	}
	return total;
}

void ElectoralMap::PopulateDistrictVotes(){
	std::cout << "You need to finish this method" << std::endl;
}

std::map<std::string, int> ElectoralMap::CollectVotes(){
	std::map<std::string, int> total_vote;
	for(Candidate c : candidates_){
		total_vote.insert(std::pair<std::string, int>(c.name, 0));
	}
	for(District d : districts_){
		std::map<std::string, int> district_vote = d.ConductVote(candidates_);
		for(std::pair<std::string, int> pair : district_vote){
			total_vote[pair.first] += pair.second;
		}
	}
	return total_vote;
}

ElectoralMap::ElectoralMap(std::vector<Candidate> candidates){
	candidates_ = candidates;
	
	int count = 0;
	while(count < 2){
		districts_.push_back(District(count + 1));
		count++;
	}
}

std::ostream& operator<<(std::ostream& os, const ElectoralMap &e){
	for(District d : e.districts_){
		os << d << std::endl << std::endl;;
	}
	return os;
}