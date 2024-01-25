#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
using namespace std;

class Game{
public:
	string sequence, playerName, input, tb, decision1, decision1sub1, level, hp;
	int a, b=0;
	bool isAlive = true;
	void clearLine(){
		cout<<"\r                                              \r";
	}
	bool CheckSave() {
		const wstring folderPath = L"save";
		DWORD folderAttributes = GetFileAttributesW(folderPath.c_str());

		if (folderAttributes == INVALID_FILE_ATTRIBUTES || !(folderAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (CreateDirectoryW(folderPath.c_str(), nullptr) == 0 && GetLastError() != ERROR_ALREADY_EXISTS) {
				cerr << "[!] Neda sa vytvorit zlozka" << endl;
				return false;
			}

			return false;
		}

		return true;
	}

	void SaveInfo(const string& data, const string& fileName) {
		const string folderPath = "save";
		const string filePath = folderPath + "\\" + fileName;

		ofstream file(filePath);

		if (file.is_open()) {
			file << data;  

			file.close();
		}
		else {
			cout << "[!] vyskytol sa nejaky problem";
		}
	}
	string ReadInfo(const string& fileName) {
		const string folderPath = "save";
		const string filePath = folderPath + "\\" + fileName;

		ifstream file(filePath);

		if (file.is_open()) {
			string data;
			getline(file, data);  

			file.close();

			return data;
		}
		else {
			cout << "[!] vyskytol sa nejaky problem" << endl;
			return ""; 
		}
	}
	void ReadSave() {
		level = ReadInfo("PlayerLevel.txt");
		hp = ReadInfo("PlayerHealth.txt");
		playerName = ReadInfo("PlayerName.txt");
		sequence = ReadInfo("Sequence.txt");
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
		skip(1000);
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
	
	// Space saving
	
		void d1n(){
			if(a==0) truenarrator("\t  Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
			if(a==1) truenarrator("\t  For real? You visit the trees again, and... you don't find anything.", 50);
			if(a==2) truenarrator("\t  There is something weird about those trees. They're... trees.", 50);
			if(a>2){
				truenarrator("\t  You visit the trees once more. Once again, you find nothin-", 50); cout << endl;
				truenarrator("\t  w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << endl; skip(300);
				truenarrator("\t  Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << endl;
				truenarrator("\t  before the fight even has a chance to begin.", 50); skip(400); cout << endl; skip(400); system("cls"); cout << "\n\n\n\n";
				truenarrator("\t  \033[1;31mYou get the tree picker ending.\033[0m", 50); cout << endl; skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
				cout << "\t  [Press F to load the latest save]"; isAlive = false;
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		break;
						}
					}
				}
				
			}
		}
	
	// Decisions
	
	void d1(){
		truenarrator("\t  You look around you. You see the following:", 50);
		cout << endl;
		truenarrator("\t  1) Trees",50); cout << endl; truenarrator("\t  2) Trees", 50); cout << endl; truenarrator("\t  3) Trees", 50); cout << endl; truenarrator("\t  4) A path", 50); cout << endl; truenarrator("\t  5) A strange place between the trees, where abandoned stuff can be seen.", 50); skip(500); cout << endl << endl; truenarrator("\t  What do you choose?", 50);
		cout << endl;
	}
	
	// Sequences
	void SaveSequence(){
		ReadSave();
		truenarrator("\tWelcome back, ", 50); truenarrator(playerName, 50); skip(250); cout << endl;
		truenarrator("\tDo you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		while(true){
			if(_kbhit()){
				char keypressed = _getch();
				if(keypressed=='f'){
					if(sequence=="1" || sequence=="0") sequence1();
				} 
				else if(keypressed=='l') introsequence();
			}
		}
	}
	void introsequence(){
		sequence = "0"; hp = "20"; level = "0";
		SaveInfo(sequence, "Sequence.txt"); SaveInfo(hp, "PlayerHealth.txt"); SaveInfo(level, "PlayerLevel.txt");
		cout << "                                          W E L C O M E    T O" << endl;
	 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
		cout << endl << "                                           The C++ Console RPG";
		cout << endl << "                                         Press [ANY KEY] to Begin";
		_getch();
		cout << endl; narrator("Hello Player", 100); skip(1000); cout << endl;
		narrator("...", 500); skip(1000); cout << endl;
		narrator("Your name isn't Player, is it?", 80); skip(1500); cout << endl;
		narrator("What's your name?", 80); skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << endl;
		flushInput();
		getInput(); playerName = input; SaveInfo(playerName, "PlayerName.txt");
		if (!playerName.empty()) {
			narrator("Nice to meet you, "+playerName+"!", 100);
		} else {
			narrator("You...", 500); narratorclean(" don't have a name?", 125); skip(500); narratorclean(" I will give you one more chance to give me your name.", 80); cout << endl; 
			flushInput();
			getInput(); playerName = input; SaveInfo(playerName, "PlayerName.txt");
			if (!playerName.empty()) {
			narrator("At last, nice to meet you, "+playerName+"!", 80);
		} else {
			narrator("You sure?", 125); cout << endl; skip(1000);
			narrator("That's", 225); narratorclean("...", 500); skip(500); narratorclean(" sad.", 200); cout << endl; skip(750);
			narrator("I still need something to call you by, though", 80); cout << endl; skip(500);
			narrator("Will Player suffice?", 75); skip(500); narratorclean(" I think it will be alright.", 75); playerName = "Player"; SaveInfo(playerName, "PlayerName.txt");
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
	}
	void sequence1(){
		system("cls");
		Sleep(3500);
		sequence = "1";
		SaveInfo(sequence, "Sequence.txt");
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
		d1();
		while(true){
			if(a>0 || b>0) d1();
			cout << endl << endl;
			flushInput();
			cout << ">>    ";
			getline(cin, decision1);
			cout << endl << endl;
			if(decision1=="1"){
				MCS("I want to see the trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="2"){
				MCS("I want to see those trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="3"){
				MCS("I must see these trees.", 80);
				cout << endl << endl;
				d1n();
				if(!isAlive){
					system("cls");
					sequence1();
					break;
				}
				skip(500);
				cout << endl << endl;
				a++;
				continue;		
			}
			else if(decision1=="4"){
				MCS("I would like to see where this path leads.", 80);
				cout << endl << endl;
				truenarrator("\t  Okay, you decide you want to see the destination of this path. Are you sure you don't want to check\n\t  the abandoned place where your stuff might lay out first?", 50);
				cout << endl << endl;
				skip(250);
				truenarrator("\t  1) Go through with your initial decision\n\t  2) Abort", 50);
				cout << endl << endl << endl << ">>    ";
				flushInput();
				getline(cin, decision1sub1);
				if(decision1sub1=="1"){
					MCS("I really want to know where it leads.", 80);
					cout << endl << endl << endl;
					truenarrator("\t  Very well, you decide to embark on an adventurous journe- nevermind, you die. Reason: UNKN0WN", 50);
					skip(400);
					cout << endl << endl << endl;
					truenarrator("\n\t  [Press F to pay respects(load the last save)]", 50);
					while(true){
						if(_kbhit()){
					  	char key = _getch();
					  	if(key=='f'){
					  		break;
							}
						}
					}
					system("CLS");
					sequence1();
					break;
				}
				else if(decision1sub1=="2"){
					MCS("I think we should check that strange abandoned place first.", 80);
					cout << endl << endl;
					truenarrator("\t  At last, you decide to check the strange place with abandoned stuff out. You see the following:",50); truenarrator("\n\t  - Tea",50); truenarrator("\n\t  - An iron sword",50); truenarrator("\n\t  - Golden armor with a low durability",50); truenarrator("\n\t  - A shield",50); truenarrator("\n\t  - Elixir of Love",50); truenarrator("\n\t  - A stick",50); truenarrator("\n\t  - Bandage x3",50); truenarrator("\n\t  - A small backpack", 50);
					break;
				}
			}
			else if(decision1=="5"){
				MCS("I would like to check the strange abandoned place out first.", 80);
				cout << endl << endl;
					truenarrator("\t  Great choice, better than \"trees\" atleast, you near the abandoned things and find the following:",50); truenarrator("\n\t  - Tea",50); truenarrator("\n\t  - An iron sword",50); truenarrator("\n\t  - Golden armor with a low durability",50); truenarrator("\n\t  - A shield",50); truenarrator("\n\t  - Elixir of Love",50); truenarrator("\n\t  - A stick",50); truenarrator("\n\t  - Bandage x3",50); truenarrator("\n\t  - A small backpack", 50);			break;
			}
			else{
				truenarrator("\t  Invalid choice. Choose again.", 50);
				cout << endl << endl;
				b++;
				continue;
			}
		}
		cout << endl << endl;
		narrator("Great.", 100); skip(250); narratorclean(" These things will come in handy. Grab them and let's get out of here.", 80); skip(1000);
		cout << endl << endl;
		cout << "      "; truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); skip(500);
		cout << endl << endl;
		MCS("Good idea, let's follow that path we saw earlier, it looks like it leads to a meadow.", 80); skip(1000);
		cout << endl << endl;
		cout << "      "; truenarrator("You are approached by a pack of wolves ready to attack you. You have to defend yourself.", 50); cout << endl << "      "; truenarrator("In a quick manner, you have to decide which weapon to use. Your weapons: ", 50); cout << endl << "      "; truenarrator("1) A stick",50); skip(200); cout << endl << "      "; truenarrator("2) An iron sword", 50); cout << endl << endl;
	}
	};

int main(){
	Game game;
	srand(time(0));
	bool ExistujeSave = game.CheckSave();
		if (ExistujeSave) {
			game.SaveSequence();
		}
		else{
			game.introsequence();
			game.sequence1();
		}

//	cout << "Now let's test multiple console windows..." << endl; Sleep(3000);
//	ambush(); 
	return 0;
}
