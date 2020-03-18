#include "TextUI.h"

/** 
Brings the user to the program main menu and returns the users choice as a string
*/
std::string TextUI::MainMenu(){
	std::string choice;
	bool valid_choice = false;
	while(!valid_choice){
		std::cout << "What kind of election would you like (d for direct, r for representational, q to quit)?";
		std::cin >> choice;
		if(choice == "d" | choice == "r" | choice == "q"){
			valid_choice = true;
		}
		else{
			std::cout << "Please enter a valid choice" << std::endl;
		}
	}
	return choice;
}

/** 
Routes a users choice to the appropriate handler function
*/
void TextUI::RouteChoice(std::string choice){
	if(choice == "d"){
		this->DirectElection();
	}
	else if(choice == "r"){
		this->RepresentationalElection();
	}
}

/** 
Runs a direct election
*/
void TextUI::DirectElection(){
	Election e(this->GetCandidatesToRegister());
	std::cout << *ElectoralMap::Instance(e.get_candidates());
	
	unsigned int choice1;
	while(choice1 != 0){
		if(choice1 != 0){
			std::cout << "Which candidate is campaigning (0 to stop)?";
			std::cin >> choice1;
			if(choice1 != 0){
				unsigned int choice2 = 1;
				while(choice2 != 0){
					std::cout << "Where is the candidate campaigning (0 to stop)?";
					std::cin >> choice2;
					if(choice2 != 0){
						e.DirectCampaign(choice1, choice2);
						std::cout << *ElectoralMap::Instance(e.get_candidates());
					}
				}
			}
		}
	}
	PrintVote("Full Results", e.GetResults());
	ElectoralMap::Instance(e.get_candidates())->ReleaseInstance();
}

/** 
Runs a representational election
*/
void TextUI::RepresentationalElection(){
	RepresentativeElection e(this->GetCandidatesToRegister());
	std::cout << *ElectoralMap::Instance(e.get_candidates());
	
	unsigned int choice1;
	while(choice1 != 0){
		if(choice1 != 0){
			std::cout << "Which candidate is campaigning (0 to stop)?";
			std::cin >> choice1;
			if(choice1 != 0){
				unsigned int choice2 = 1;
					while(choice2 != 0){
						std::cout << "Where is the candidate campaigning (0 to stop)?";
						std::cin >> choice2;
						if(choice2 != 0){
							e.DirectCampaign(choice1, choice2);
							std::cout << *ElectoralMap::Instance(e.get_candidates());
						}
					}
			}
		}
	}
	PrintVote("Full Results", e.GetResults());
	ElectoralMap::Instance(e.get_candidates())->ReleaseInstance();
}

/** 
Prompts the user to register candidates, and stores user input as a
vector of candidates
*/
std::vector<Candidate> TextUI::GetCandidatesToRegister(){
	std::vector<Candidate> candidates;
	int count = 1;
	//for every party
	for(Party p : GetParties()){
		//except Party::None
		if(p != Party::None){
			std::string choice;
			//either register a candidate or do not
			while(choice != "n"){
				std::cout << "Do you want to register a candidate for " << PartyToString(p) << " (y or n)?";
				std::cin >> choice;
				if(choice == "y"){
					//created a second choice so if user names a candidate "n" it will not break out of the loop
					std::string choice2;
					std::cout << "What is their name?";
					std::cin >> choice2;
					candidates.push_back(Candidate(choice2, p, count));
					count++;
				}
				else if(choice != "n"){
					std::cout << "Please enter a valid choice" << std::endl;
				}
			}
		}
	}
	return candidates;
}