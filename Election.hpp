#include"ElectoralMap.h"

class Election{
	public:
		Election(std::vector<Candidate> candidates){
			for(Candidate c : candidates){
				candidates_.push_back(c);
			}
		}
	
		std::vector<Candidate> get_candidates(){return candidates_;};
		
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(candidates_)->CollectVotes();
		}
	
	private:
		std::vector<Candidate> candidates_;
};

class RepresentativeElection : public Election{
	public:
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(this->get_candidates())->CollectVotesRepresentational();
		}
};