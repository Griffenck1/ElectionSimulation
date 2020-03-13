#include "Election.h"

int main(){
	Election e1;
	std::vector<Candidate> temp;
	temp = e1.get_candidates();
	for(Candidate c : temp){
		std::cout << c.name << " " << c.id << std::endl;
	}
	return 0;
}