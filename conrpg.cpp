#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
using namespace std;
string input, tb;
void clearLine(){
	cout<<"\r                                              \r";
}
void narrator(const string& text, int tickspeed) {
  bool a = false;
  tb="<<    ";
  tb+=text;
  for (char c : text) {
      if (!a) {
          cout << "<<    ";
          a = true;
      }
      if(_kbhit()){
      	char key = _getch();
      	if(key=='\r' or key==' '){
      		clearLine();
      		cout << "<<    " << text;
      		break;
				}
			}
      cout << c;
      this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
}
void MCS(const string& text, int tickspeed){
	bool a = false;
	tb=">>    ";
	tb+=text;
  for (char c : text) {
      if (!a) {
          cout << ">>    ";
          a = true;
      }
      if(_kbhit()){
      	char key = _getch();
      	if(key=='\r' or key==' '){
      		clearLine();
      		cout << ">>    " << text;
      		break;
				}
			}
      cout << c;
      this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
}
void narratorclean(const string& text, int tickspeed) {
  bool a = false;
  tb+=text;
  for (char c : text) {
      cout << c;
	      if(_kbhit()){
	      	char key = _getch();
	      	if(key=='\r' or key==' '){
	      		clearLine();
	      		cout << tb;
	      		break;
					}
				}
      this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
}
void truenarrator(const string& text, int tickspeed) {
  bool a = false;
  for (char c : text) {
      cout << c;
	      if(_kbhit()){
	      	char key = _getch();
	      	if(key=='\r' or key==' '){
	      		clearLine();
	      		cout << text;
	      		break;
					}
				}
      this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
}
void skip(int time){
	for(time; time>0; time-=50){
	  if(_kbhit()){
	  	char key = _getch();
	  	if(key=='\r' or key==' '){
	  		break;
			}
		}
		Sleep(50);
	}
}
void getInput() {
	cout << ">>    ";
	getline(cin, input);
	Sleep(1000);
}
void flushInput() {
		while(_kbhit()) {
	    _getch(); 
	    Sleep(50);
  }
}
int ambush(){
	string decision;
  cout << "You are under attack by something. Flee or Fight?" << endl;
	while(true){
		flushInput();
	  cin >> decision;
	  for (char &c : decision) {
        c = tolower(c);
    }
	  if(decision=="fight"){
	  	break;
	  	cout << endl;
		}
		else if(decision=="flee"){
			cout << "Attempting fleeing...";
			Sleep(500);
			cout << " Fleeing unsuccessful" << endl;
			continue;
		}

		else{
			cout << "Invalid choice. Try again." << endl;
		}
	}
  Sleep(2000);

  const char *programName = "combatmoreeffective.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Start the child process in a new console window.
  if (CreateProcess(NULL, const_cast<char*>(programName), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
      cout << "Launching combat program in a new console window..." << endl;
      WaitForSingleObject(pi.hProcess, INFINITE); 
  } else {
      cout << "Error launching program" << endl;
  }
  ifstream inputFile("testsave.txt");
  if (!inputFile.is_open()) {
    cerr << "Error opening file for reading!" << endl;
    return 1;
  }
  string filecontent;
  if (getline(inputFile, filecontent)) {
    if (filecontent == "1") {
        cout << "You aborted the fight. You automatically die." << endl;
    }
		else{
      cout << "You finished the fight." << endl;
    }
  }
	cout << "ono to funguje...";
	Sleep(3000);
}
// Sequences
void sequence1(){
	Sleep(3500);
	MCS("Where am I?", 80); narratorclean(" How did I get here?",80); skip(1000);
	cout << endl;
	MCS("There is a thick forest all around me.", 80); skip(1000);
	cout << endl;
	MCS("I, ", 100); narratorclean("...", 200); skip(500); narratorclean(" can't remember anything.", 80); skip(1500);
	cout << endl;
	narrator("What's happening! ", 80); skip(600); narratorclean("Why can't I control my body? ", 100); skip(500); narratorclean("This... ", 175); skip(300); narratorclean("This is not my body!", 80);
	cout << endl;
	MCS("Who said that? ", 40); skip(750);
	cout << endl;
	MCS("Where are you? Show yourself!", 75); skip(1000);
	cout << endl;
	narrator("I can't show myself.", 80); skip(1000);
	cout << endl;
	MCS("What do you mean?", 80); skip(1000);
	cout << endl;
	narrator("I myself have no idea.", 80); skip(500); narratorclean(" It seems like...", 120); skip(400); narratorclean(" I am in you.", 100); skip(750);
	cout << endl;
	MCS("Why are you in me?", 80); skip(1000);
	cout << endl;
	narrator("Good question.", 80); skip(500); narratorclean(" All I can remember is my death,", 80); skip(250); narratorclean(" and now,", 125); narratorclean(" I find myself here,", 100); skip(500); narratorclean(" in your body.", 100); skip(1000);
	cout << endl;
	MCS("What do you mean your death?", 80); skip(1500);
	cout << endl;
	narrator("This has to be a nightmare.", 80); skip(1000);
	cout << endl;
	narrator("Well,", 125); skip(400); narratorclean(" we don't really have a choice,",80); skip(300); narratorclean(" stand up and look around.", 80 ); skip(250);
	cout << endl;
	narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
	cout << endl;
	narrator("and why you don't remember anything.", 80); skip(400); narratorclean(" Stand up before someone,", 100);skip(200); narratorclean(" or worse,", 125); skip(200); narratorclean(" something finds us.", 100); skip(1000);
	cout << endl;
	MCS("Why should I listen to you?", 80); skip(1000);
	cout << endl;
	narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
	cout << endl;
	cout << endl;
	truenarrator("      You look around you. You see the following:", 50);
	cout << endl;
	truenarrator("      1) Trees",50); cout << endl; truenarrator("      2) Trees", 50); cout << endl; truenarrator("      3) Trees", 50); cout << endl; truenarrator("      4) A path", 50); cout << endl; truenarrator("      5) A strange place between the trees, where abandoned stuff can be seen.", 50); skip(500); cout << endl << endl; truenarrator("      What do you choose?", 50);
	cout << endl;	
}
int main(){
	srand(time(0));
	cout << "                                          W E L C O M E    T O" << endl;
 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
	cout << endl << "                                           The C++ Console RPG";
	cout << endl << "                                         Press [ANY KEY] to Begin";
	_getch();
	cout << endl; narrator("Hello Player", 100); skip(1000); cout << endl;
	narrator("...", 500); skip(1000); cout << endl;
	narrator("Your name isn't Player, is it?", 80); skip(1500); cout << endl;
	narrator("What's your name?", 80); skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << endl;
	string playerName;
	flushInput();
	getInput();
	if (!input.empty()) {
		narrator("Nice to meet you, "+input+"!", 100);
	} else {
		narrator("You...", 500); narratorclean(" don't have a name?", 125); skip(500); narratorclean(" I will give you one more chance to give me your name.", 80); cout << endl; 
		flushInput();
		getInput();
		if (!input.empty()) {
		narrator("At last, nice to meet you, "+input+"!", 80);
	} else {
		narrator("You sure?", 125); cout << endl; skip(1000);
		narrator("That's", 225); narratorclean("...", 500); skip(500); narratorclean(" sad.", 200); cout << endl; skip(750);
		narrator("I still need something to call you by, though", 80); cout << endl; skip(500);
		narrator("Will Player suffice?", 75); skip(500); narratorclean(" I think it will be alright.", 75);
	}
}
	skip(1000);
	cout << endl << "      [PRESS ANY KEY TO START THE GAME]";
	while(true){
		if(_kbhit()){
			system("cls");
			break;
		}
	}
	sequence1();
//	cout << "Now let's test multiple console windows..." << endl; Sleep(3000);
//	ambush(); 
	return 0;
}
