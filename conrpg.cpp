#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
using namespace std;
string input;
void clearLine(){
	cout<<"\r                                              \r";
}
void narrator(const string& text, int tickspeed) {
  bool a = false;
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
void narratorclean(const string& textbefore,const string& text, int tickspeed) {
  bool a = false;
  for (char c : text) {
      cout << c;
	      if(_kbhit()){
	      	char key = _getch();
	      	if(key=='\r' or key==' '){
	      		clearLine();
	      		cout << textbefore << text;
	      		break;
					}
				}
      this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
}
void getInput() {
	cout << ">>    ";
	getline(cin, input);
  bool typing = true;
  for(char c : input) {
    if(typing) {
      cout << ">>    ";
      typing = false; 
    }
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(125));
  }
  cout << endl;
}
void flushInput() {
		while(_kbhit()) {
	    _getch(); 
	    Sleep(50);
  }
}
int ambush(){
	bool alpha = true;
	string decision;
  cout << "You are under attack by something. Flee or Fight?" << endl;
	while(true){
	  cin >> decision;
	  for (char &c : decision) {
        c = tolower(c);
    }
	  if(decision=="fight"){
	  	break;
	  	cout << endl;
		}
		else if(decision=="flee")
			cout << "Attempting fleeing...";
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
      alpha = false;
  } else {
      cout << "Error launching program" << endl;
  }

  ofstream outputFile("testsave.txt");

  if (!outputFile.is_open()) {
      cerr << "Error opening file for writing!" << endl;
      return 1; 
  }

  outputFile << (alpha ? "1" : "0") << endl;

  outputFile.close();
  
    while (!alpha) {
      ifstream inputFile("testsave.txt");
      if (!inputFile.is_open()) {
          cerr << "Error opening file for reading!" << endl;
          return 1; 
      }
      string fileContent;
      if (getline(inputFile, fileContent)) {
          alpha = (fileContent == "1");
      }
      inputFile.close();
      Sleep(100);
    }
	cout << "ono to funguje...";
	Sleep(3000);
}
int main(){
	srand(time(0));
	cout << "                                          W E L C O M E    T O" << endl;
 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
	cout << endl << "                                           The C++ Console RPG";
	cout << endl << "                                         Press [ANY KEY] to Begin";
	_getch();
	cout << endl; narrator("Hello Player", 100); cout << endl;
	Sleep(1000);
	narrator("...", 500); cout << endl; Sleep(1000);
	narrator("Your name isn't Player, is it?", 80); cout << endl;
	Sleep(1500);
	narrator("What's your name?", 80); cout << endl << "      [ENTER YOUR NAME NOW]" << endl;
	string playerName;
	flushInput();
	getInput();
	if (!input.empty()) {
		narrator("Nice to meet you, "+input+"!", 100);
	} else {
		narrator("You...", 500); narratorclean("<<    You..."," don't have a name?", 125); Sleep(500); narratorclean("<<    You... don't have a name?"," I will give you one more chance to give me your name.", 80); cout << endl; 
		flushInput();
		getInput();
		if (!input.empty()) {
		narrator("At last, nice to meet you, "+input+"!", 80);
	} else {
		narrator("You sure?", 125); cout << endl; Sleep(1000);
		narrator("That's", 225); narratorclean("<<    That's","...", 500); Sleep(500); narratorclean("<<    That's..."," sad.", 200); cout << endl; Sleep(750);
		narrator("I still need something to call you by, though", 80); cout << endl; Sleep(500);
		narrator("Will Player suffice?", 75); Sleep(500); narratorclean("<<    Will Player suffice?"," I think it will be alright.", 75);
	}
}
	cout << endl << "      [PRESS ANY KEY TO CONTINUE]";
	while(true){
		if(_kbhit()){
			system("cls");
			break;
		}
	}
	cout << "Now let's test multiple console windows..." << endl; Sleep(3000);
	ambush();
	return 0;
}
