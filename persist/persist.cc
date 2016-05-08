/* demo */


#include<iostream>
#include<vector>
#include<fstream>

#include<string>
#include<iterator>
#include<cstdlib>
#include"persist.hpp"
#include"scores.hpp"
#include"ioadd.hpp"

//encapsulated to this
void SendHighScore(ScoreBoard &score) {
	SendObject sendobj(&score); // function object
	sendobj(); // call function object
}



int main(int argc, char **argv) {

    try {
    	ScoreBoard score_board; // Score Board encapsulation of high scores.
    	std::string userName;
    	std::cout << "Enter the Person Name: ";
    	userName = getString(std::cin);
    	int score = 0;
    	// loop until score is valid.
    	do {
    		std::cout << "Enter the Score: ";
    		score = getInteger(std::cin);
    	} while (score == 0);

        if(score_board.enterUser(userName.c_str(), score) == true) { // Attempt to add user to list
        	std::cout << "added user: " << userName << ":" << score << "\n";
        } else {
        	std::cout << "Score not High enough sorry\n";
        }
        score_board.DisplayScores();// output
        Score &s = score_board.highestScore();
        std::cout << "Highest Score: " << s.username << " with a score of: " << s.score << "\n";
        SendHighScore(score_board); // send score over TCP/IP.
        std::cout << "Transmitted score data...\n";
    }
    catch(ScoreException &s) {
    	std::cerr << "error: " << s.what() << "\n";
    }
    catch(std::exception &e) { 
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unknown error\n";
    }
    return 0;
}
