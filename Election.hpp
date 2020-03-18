#include"ElectoralMap.h"

class Election{
	public:
		//constructor takes a vector of candidates and uses it to popualte candidates_
		Election(std::vector<Candidate> candidates): candidates_(candidates){}
	
		std::vector<Candidate> get_candidates(){return candidates_;};
		
		//Returns the results of a campaign as a map from string (candidate name) to in (candidate votes)
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(candidates_)->CollectVotes();
		}
		
		//Directs a candidate to a district to campaign in
		void DirectCampaign(unsigned int candidate_id, unsigned int district_id){
			if(candidate_id <= candidates_.size()){
				ElectoralMap::Instance(candidates_)->Campaign(candidates_[candidate_id - 1], district_id);
			}
			else{
				std::cout << "Please enter a valid candidate id" << std::endl;
			}
		}
	
	private:
		std::vector<Candidate> candidates_;
};

class RepresentativeElection : public Election{
	public:
		RepresentativeElection(std::vector<Candidate> candidates): Election(candidates){}
		
		//Overrides the GetResults function to call ElectoralMap::CollectVotesRepresentional rather than 
		//ElectoralMap::CollectVotesDirect
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(this->get_candidates())->CollectVotesRepresentational();
		}
};