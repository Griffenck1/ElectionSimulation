#ifndef TEXTUI_H
#define TEXTUI_H

#include "Election.hpp"

class TextUI{
	public:
	std::string MainMenu();
	
	void RouteChoice(std::string);
	
	void DirectElection();
	
	void RepresentationalElection();
	
	std::vector<Candidate> GetCandidatesToRegister();
	
	private:
};

#endif  // TEXTUI_H