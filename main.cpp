#include "TextUI.h"

int main(){
	//Set random number seed
	srand(time(NULL));
	std::string choice;
	TextUI ui;
	//while the user does not select q the program runs
	while(choice != "q"){
		choice = ui.MainMenu();
		ui.RouteChoice(choice);
	}
	
	return 0;
}