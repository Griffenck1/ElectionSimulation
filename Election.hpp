#include"ElectoralMap.h"

class Election{
	public:
		Election(std::vector<Candidate> candidates): candidates_(candidates){}
	
		std::vector<Candidate> get_candidates(){return candidates_;};
		
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(candidates_)->CollectVotes();
		}
	
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
		
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(this->get_candidates())->CollectVotesRepresentational();
		}
};