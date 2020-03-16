#include"ElectoralMap.h"

class Election{
	public:
		Election(std::vector<Candidate> candidates){
			for(Candidate c : candidates){
				candidates.push_back(c);
			}
		}
	
		std::map<std::string, int> GetResults();
	
		std::vector<Candidate> get_candidates(){return candidates_;};
	private:
		std::vector<Candidate> candidates_;
};

class RepresentativeElection : public Election{
	public:
		std::map<std::string, int> GetResults(){
			return ElectoralMap::Instance(this->get_candidates())->CollectVotesRepresentational();
		}
};

std::map<std::string, int> Election::GetResults(){
	return ElectoralMap::Instance(candidates_)->CollectVotes();
}