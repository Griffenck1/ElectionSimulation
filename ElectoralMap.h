#ifndef ELECTORALMAP_H
#define ELECTORALMAP_H

#include"District.h"

class ElectoralMap{
	public:
		static ElectoralMap* Instance(std::vector<Candidate> candidates);
	
		void ReleaseInstance();
		
		int CalculateTotalConstituents();
		
		void PopulateDistrictVotes();
	
		void Campaign(Candidate c, unsigned int district_id);
	
		std::map<std::string, int> CollectVotes();
	
		std::map<std::string, int> CollectVotesRepresentational();
	
		friend std::ostream& operator<<(std::ostream& os, const ElectoralMap &e);
	private:
		ElectoralMap(std::vector<Candidate> candidates);
		std::vector<District> districts_;
		std::vector<Candidate> candidates_;
		static ElectoralMap* instance_;
		std::map<int, int> district_votes_;
};

#endif  // ELECTORALMAP_H