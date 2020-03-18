#include "ElectoralMap.h"

//Helps ensure that only one instance of class can exist at a time
ElectoralMap* ElectoralMap::instance_ = NULL;

/**
Constructs an electoral map
*/
ElectoralMap::ElectoralMap(std::vector<Candidate> candidates){
	candidates_ = candidates;
	
	int count = 0;
	while(count < 3){
		districts_.push_back(District(count + 1));
		count++;
	}
}

/**
Returns a poitner to the instance of ElectoralMap
*/
ElectoralMap* ElectoralMap::Instance(std::vector<Candidate> candidates){
	//if there is no instance, make one
	if(!instance_){
		instance_ = new ElectoralMap(candidates);
	}
	return instance_;
}

/**
Sets the instance to NULL, thus deleting it
*/
void ElectoralMap::ReleaseInstance(){
	ElectoralMap::instance_ = NULL;
}

/**
Calculates the total number of constituents in the ElectoralMap from all districts
*/
int ElectoralMap::CalculateTotalConstituents(){
	int total = 0;
	for(District d : districts_){
		total += d.CalculateTotalConstituents();
	}
	return total;
}

/**
Assigns every district a representational vote based on total population
*/
void ElectoralMap::PopulateDistrictVotes(){
	int total_votes = districts_.size() * 5;
	for(District d : districts_){
		float total_constituents = this->CalculateTotalConstituents();
		float district_constituents = d.CalculateTotalConstituents();
		int votes = floor(((district_constituents * 1.0)/total_constituents) * total_votes);
		district_votes_.insert(std::pair<int, int>(d.get_id() - 1, votes));
	}
}

/**
Allows a candidate to campaign in a district, handles the logic of whether the 
candidate has failed or succeeded.
*/
void ElectoralMap::Campaign(Candidate c, unsigned int district_id){
	if((district_id) <= districts_.size()){
		std::map<Party, int> district_voters = districts_[district_id - 1].get_voters();
		
		float chance_success = 0;
		float chance_extra_success = 0;
		
		float voters_from_party = district_voters[c.party];
		float voters_not_from_party = districts_[district_id - 1].CalculateTotalConstituents() - voters_from_party - district_voters[Party::None];
		//This check to see if voters_not_from party == 0, and sets it to 1 if it is to avoid dividing by 0
		if(voters_not_from_party == 0){
			voters_not_from_party = 1;
		}
		chance_success = 100 * (((voters_from_party + 1) * 2) / voters_not_from_party) * (((voters_from_party + 1) * 2) / districts_[district_id - 1].get_area());
		
		//cap chance of success at %100
		if(chance_success > 100){
			chance_success = 100;
		}
			
		chance_extra_success = chance_success * 0.1;
		
		std::cout << "chance to convert: " << chance_success << std::endl;
		std::cout << "chance to convert from another party: " << chance_extra_success << std::endl << std::endl;
		
		//generates a random number between 1 and 100
		int random = rand() % 100 + 1;
	
		if(random <= chance_success){
			districts_[district_id - 1].ConvertConstituent(Party::None, c.party);
			std::cout << "Congrats, you have converted someone from None to " << PartyToString(c.party) << std::endl << std::endl;
		}
		if(random <= chance_extra_success){
			districts_[district_id - 1].ConvertConstituent(districts_[district_id - 1].MajorityParty(c.party), c.party);
			std::cout << "Congrats, you have converted someone from " << PartyToString(districts_[district_id - 1].MajorityParty(c.party));
			 std::cout << " to " << PartyToString(c.party) << std::endl << std::endl;
		}
	}
	else{
		std::cout << "Please enter a valid district id" << std::endl;
	}
	
}

/**
Collects votes from each district for a direct election, adds them together,
and returns the total vote as map from string (candidate name) to int (candidate votes)
*/
std::map<std::string, int> ElectoralMap::CollectVotes(){
	std::map<std::string, int> total_vote;
	for(Candidate c : candidates_){
		total_vote.insert(std::pair<std::string, int>(c.name, 0));
	}
	for(District d : districts_){
		std::map<std::string, int> district_vote = d.ConductVote(candidates_);
		std::cout << "District " << d.get_id() << ": " << std::endl;
		for(std::pair<std::string, int> pair : district_vote){
			total_vote[pair.first] += pair.second;
			std::cout << pair.first << ": " << pair.second << std::endl;
		};
	}
	return total_vote;
}

/**
Collects votes from each district for a Representational election, adds them together,
and returns the total vote as map from string (candidate name) to int (candidate votes)
*/
std::map<std::string, int> ElectoralMap::CollectVotesRepresentational(){
	//populate district votes only if the election is representational
	this->PopulateDistrictVotes();
	
	std::map<std::string, int> total_vote;
	for(Candidate c : candidates_){
		total_vote.insert(std::pair<std::string, int>(c.name, 0));
	}
	for(District d : districts_){
		std::map<std::string, int> district_vote = d.ConductVote(candidates_);
		std::string winner;
		int winner_votes = 0;
		for(std::pair<std::string, int> pair : district_vote){
			if(pair.second > winner_votes){
				winner = pair.first;
				winner_votes = pair.second;
			}
		}
		total_vote[winner] += district_votes_[d.get_id() - 1];
		std::cout << "District " << d.get_id() << ": " << std::endl;
		std::cout << winner << ": " << district_votes_[d.get_id() - 1] << std::endl;
	}
	return total_vote;
}

/**
Overload << to make printing electoral maps easier
*/
std::ostream& operator<<(std::ostream& os, const ElectoralMap &e){
	for(District d : e.districts_){
		os << d;
	}
	return os;
}