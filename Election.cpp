#include "Election.h"

//converts strings to Party
Party string_to_party(std::string s){
	if(s == "Party1"){
		return Party::Party1;
	}
	else if(s == "Party2"){
		return Party::Party2;
	}
	else{
		return Party::None;
	}
}

//converts Party to strigns
std::string party_to_string(Party p){
	if(p == Party::Party1){
		return "Party1";
	}
	else if(p == Party::Party2){
		return "Party2";
	}
	else{
		return "None";
	}
}