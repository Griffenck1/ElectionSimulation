#include "TextUI.h"

int main(){
	//Set random number seed
	srand(time(NULL));
	std::string choice;
	TextUI ui;
	while(choice != "q"){
		choice = ui.MainMenu();
		ui.RouteChoice(choice);
	}
	
	return 0;
}