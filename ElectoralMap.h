#ifndef ELECTORALMAP_H
#define ELECTORALMAP_H

#include"District.h"

class ElectoralMap{
	public:
		static ElectoralMap* Instance(std::vector<Candidate> candidates);
	
		void ReleaseInstance();
	
		friend std::ostream& operator<<(std::ostream& os, const ElectoralMap &e);
		
		//returns the total # of constituants
		int CalculateTotalConstituents();
		
		//calcualtes how many votes a district has in a representational election and populates district_votes_
		void PopulateDistrictVotes();
	
		//collects votes from all districts
		std::map<std::string, int> CollectVotes();
	
		//collects votes from all districts for representational elections
		std::map<std::string, int> CollectVotesRepresentational();
	
		void Campaign(Candidate c, unsigned int district_id);
	private:
		ElectoralMap(std::vector<Candidate> candidates);
		std::vector<District> districts_;
		std::vector<Candidate> candidates_;
		static ElectoralMap* instance_;
		std::map<int, int> district_votes_;
};

#endif  // ELECTORALMAP_H