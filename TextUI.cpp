#include "TextUI.h"

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

void TextUI::RouteChoice(std::string choice){
	if(choice == "d"){
		this->DirectElection();
	}
	else if(choice == "r"){
		this->RepresentationalElection();
	}
}

void TextUI::DirectElection(){
	Election e(this->GetCandidatesToRegister());
	std::cout << std::endl << *ElectoralMap::Instance(e.get_candidates());
	
	unsigned int choice1;
	unsigned int choice2;
	while(choice1 != 0){
		if(choice1 != 0){
			std::cout << "Which candidate is campaigning (0 to stop)?";
			std::cin >> choice1;
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
	std::cout << std::endl;
	PrintVote("Full Results", e.GetResults());
	ElectoralMap::Instance(e.get_candidates())->ReleaseInstance();
}

void TextUI::RepresentationalElection(){
	RepresentativeElection e(this->GetCandidatesToRegister());
	std::cout << std::endl << *ElectoralMap::Instance(e.get_candidates());
	
	unsigned int choice1;
	unsigned int choice2;
	while(choice1 != 0){
		if(choice1 != 0){
			std::cout << "Which candidate is campaigning (0 to stop)?";
			std::cin >> choice1;
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
	std::cout << std::endl;
	PrintVote("Full Results", e.GetResults());
	ElectoralMap::Instance(e.get_candidates())->ReleaseInstance();
}

std::vector<Candidate> TextUI::GetCandidatesToRegister(){
	std::vector<Candidate> candidates;
	int count = 1;
	for(Party p : GetParties()){
		if(p != Party::None){
			std::string choice;
			while(choice != "n"){
				std::cout << "Do you want to register a candidate for " << party_to_string(p) << " (y or n)?";
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