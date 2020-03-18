#ifndef TEXTUI_H
#define TEXTUI_H

#include "Election.hpp"

class TextUI{
	public:
	std::string MainMenu();
	
	void RouteChoice(std::string);
	
	private:
	void DirectElection();
	void RepresentationalElection();
	
	std::vector<Candidate> GetCandidatesToRegister();
};

#endif  // TEXTUI_H