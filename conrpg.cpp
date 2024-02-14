#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
class Game{
public:
	string playerName, fightstatus, input, tb, decision1, decision1sub1, decision2="";
	string diadec1, diadec2, diadec3, diadec4, diadec5;
	const string mc = "\033[33m", vc = "\033[36m";
	int a=0, b=0, sequence, level, xp, requiredxp, xpgained, initiallvl, plvlbonusdmg;
	double perlevel, hp, currenthp, maxdmg;
	bool isAlive = true;
  void save() {
    ofstream file("savegame.txt");
    file << sequence << "\n";
    file << playerName << "\n";
    file << level << "\n";
    file << xp << "\n";
    file << hp << "\n"; 
    file << currenthp << "\n";
    file << maxdmg << "\n";
    file.close();
  }

  void load() {
    ifstream file("savegame.txt");
    file >> sequence;
    file >> playerName;
    file >> level;
    file >> xp;
    file >> hp;
    file >> currenthp;
    file >> maxdmg;
    requiredxp=10*pow(1.2, level);
    perlevel = (requiredxp-xp)/requiredxp*100;
  }
  bool CheckSave(){
  	ifstream file("savegame.txt");
  	return file.good();
	}
	void checkLevelUp(){
		if(xp>=requiredxp){
			initiallvl = level;
			hp = currenthp;
			while(xp>=requiredxp){
				hp += hp/10;
				level += 1;
				xp -= requiredxp;
				requiredxp += requiredxp/5;
			} 
		cout << "\n      Leveled up! Went from lvl " << initiallvl << " to lvl " << level << ". HP: " << currenthp << " -> " << hp << endl;
		cout << "      Current xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << endl;
		}
		save();
	}
	void clearLine(){
		cout<<"\r                                              \r";
	}
void narrator(const string& text, int tickspeed) {
  bool a = false;
  tb="<<    ";
  tb+=text;
  for (char c : text) {
    if (!a) {
      cout << vc << "<<    "; 
      a = true;
    }
    if(_kbhit()){
      char key = _getch();
      if(key=='\r' or key==' '){
        clearLine(); 
        cout << vc << "<<    " << text;
        break;
      }
    }
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m";
}
void MCS(const string& text, int tickspeed){
  bool a = false;
  tb=">>    ";
  tb+=text;
  for (char c : text) {
    if (!a) {
      cout << mc << ">>    ";  
      a = true;
    }
    if(_kbhit()){
      char key = _getch();
      if(key=='\r' or key==' '){
        clearLine();
        cout << mc << ">>    " << text;
        break;  
      }
    }
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m"; 
}
void narratorclean(string currentColor, const string& text, int tickspeed) {
  bool a = false;
  tb += text;
  for(char c : text) {
    if(currentColor != "") {
      cout << currentColor; 
    }
    cout << c;  
    if(_kbhit()) {
      char key = _getch();
      if(key=='\r' or key==' ') {
        clearLine();
        if(currentColor != "") {
          cout << currentColor;
        }
        cout << tb;
        break;
      }
    }
    
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m"; 
}
void MCSC(string currentColor, const string& text, int tickspeed) {
	tb=">>    ";
	tb+=text;
  bool a = false;
  for(char c : text) {
    if(currentColor != "") {
      cout << currentColor; 
    }
    cout << c;  
    if(_kbhit()) {
      char key = _getch();
      if(key=='\r' or key==' ') {
        clearLine();
        if(currentColor != "") {
          cout << currentColor;
        }
        cout << tb;
        break;
      }
    }
    this_thread::sleep_for(chrono::milliseconds(tickspeed));
  }
  cout << "\033[0m"; 
}
	void truenarrator(const string& text, int tickspeed) {
		tb="      ";
		tb+=text; cout << "      ";
	  bool a = false;
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
	void TNC(const string& text, int tickspeed){
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
	string GVI(int min, int max) {
		string dinput;
	  while (true) {
      char input = _getch();  
      if (input >= min+'0' && input <= max+'0') {
          dinput = string(1, input);  
          cout << dinput;  
          break;
      }
    }
    return dinput;
	}
	string GVIclean(int min, int max) {
		string dinput;
	  while (true) {
      char input = _getch();  
      if (input >= min+'0' && input <= max+'0') {
          dinput = string(1, input);   
          break;
      }
    }
    return dinput;
	}
	void flushInput() {
			while(_kbhit()) {
		    _getch(); 
		    Sleep(50);
	  }
	}
	int ambush(string attacker, int enemyhp, int enemydmg, int enemyskill, int enemyrage){
		ofstream file("savegame.txt");
    file << sequence << "\n";
    file << playerName << "\n";
    file << level << "\n";
    file << xp << "\n";
    file << hp << "\n"; 
    file << currenthp << "\n";
    file << maxdmg << "\n";
    file << enemyhp << "\n";
    file << enemydmg << "\n";
    file << enemyskill << "\n";
    file << enemyrage << "\n";
    file << attacker << "\n";
    file.close();
	  Sleep(2000);
	  cout << endl << "      "; truenarrator("Prepare to fight...", 50); Sleep(500);
	  const char *programName = "combatmoreeffective.exe";
	  STARTUPINFO si;
	  PROCESS_INFORMATION pi;
	  ZeroMemory(&si, sizeof(si));
	  si.cb = sizeof(si);
	  ZeroMemory(&pi, sizeof(pi));
	  if (CreateProcess(NULL, const_cast<char*>(programName), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
	      WaitForSingleObject(pi.hProcess, INFINITE); 
	  } else {
	      cout << "Error launching program" << endl;
	  }
	  ifstream inputFile("testsave.txt");
	  if (!inputFile.is_open()) {
	    cerr << "Error opening file for reading!" << endl;
	    return 1;
	  }
	  inputFile >> fightstatus;
	  inputFile >> xpgained;
	  if(fightstatus=="1"){
	  	truenarrator("You aborted the fight... You automatically die.", 50); cout << endl; skip(250); truenarrator("[Press F to load the latest save/L to start over]",50);
			while(true){
      	if(_kbhit()){
      		char c = _getch();
      		if(c=='f') sequence1();
					else if(c=='f') introsequence();
				}
			}
		}
		else{
      truenarrator("You finished the fight.", 50); cout << endl;
    }
		Sleep(3000);
		xp+=xpgained;
		checkLevelUp();
		Sleep(2000);
	}
	void d1n(){
		if(a==0) truenarrator("Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
		if(a==1) truenarrator("For real? You visit the trees again, and... you don't find anything.", 50);
		if(a==2) truenarrator("There is something weird about those trees. They're... trees.", 50);
		if(a>2){
			truenarrator("You visit the trees once more. Once again, you find nothin-", 50); cout << endl;
			truenarrator("w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << endl; skip(300);
			truenarrator("Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << endl;
			truenarrator("before the fight even has a chance to begin.", 50); skip(400); cout << endl; skip(400); system("cls"); cout << "\n\n\n\n";
			truenarrator("\033[1;31mYou get the tree picker ending.\033[0m", 50); cout << endl; skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
			cout << "      [Press F to load the latest save]"; isAlive = false;
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
		truenarrator("You look around you. You see the following:", 50);
		cout << endl;
		truenarrator("1) Trees",50); cout << endl; truenarrator("2) Trees", 50); cout << endl; truenarrator("3) Trees", 50); cout << endl; truenarrator("4) A path", 50); cout << endl; truenarrator("5) A strange place between the trees, where abandoned stuff can be seen.", 50); skip(500); cout << endl << endl; truenarrator("What do you choose?", 50);
	}
	
	// Sequences
	void savesequence(){
		load();
		truenarrator("Welcome back, "+playerName, 50); skip(250); cout << endl;
		truenarrator("Do you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		while(true){
			if(_kbhit()){
				char keypressed = _getch();
				if(keypressed=='f'){
					if(sequence==1) sequence1();
					else if(sequence==2) sequence2();
				} 
				else if(keypressed=='l'){
					introsequence(); sequence1();
				} 
			}
		}
	}
	void introsequence(){
		system("cls");
		level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
		cout << "                                          W E L C O M E    T O" << endl;
	 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
		cout << endl << "                                           The C++ Console RPG";
		cout << endl << "                                         Press [ANY KEY] to Begin";
		_getch();
		cout << endl; truenarrator("Hello Player", 100); skip(1000); cout << endl;
		truenarrator("...", 500); skip(1000); cout << endl;
		truenarrator("Your name isn't Player, is it?", 80); skip(1500); cout << endl;
		truenarrator("What's your name?", 80); skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << endl;
		flushInput();
		getInput(); playerName = input; save();
		if (!playerName.empty()) {
			truenarrator("Nice to meet you, "+playerName+"!", 100);
		} else {
			truenarrator("You...", 500); TNC(" don't have a name?", 125); skip(500); TNC(" I will give you one more chance to give me your name.", 80); cout << endl; 
			flushInput();
			getInput(); playerName = input; save();
			if (!playerName.empty()) {
			truenarrator("At last, nice to meet you, "+playerName+"!", 80);
		} else {
			truenarrator("You sure?", 125); cout << endl; skip(1000);
			truenarrator("That's", 225); TNC("...", 500); skip(500); TNC(" sad.", 200); cout << endl; skip(750);
			truenarrator("I still need something to call you by, though", 80); cout << endl; skip(500);
			truenarrator("Will Player suffice?", 75); skip(500); TNC(" I think it will be alright.", 75); playerName = "Player"; save();
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
		sequence=0;
		sequence1();
	}
	void sequence1(){
		system("cls");
		if(sequence==0) sequence++;
		save();
		Sleep(500);
		cout << "\n\n\n\n\n\n\t\t{[()]} Sequence 1 {[()]}\n\n\n"; Sleep(500);
		truenarrator("\t\tThe game saves every sequence. Good luck on your journey.", 50);
		Sleep(2000); system("cls");
		Sleep(2500);
		MCS("Where am I?", 80); narratorclean(mc," How did I get here?",80); skip(1000);
		cout << endl;
		MCS("There is a thick forest all around me.", 80); skip(1000);
		cout << endl;
		MCS("I, ", 100); narratorclean(mc,"...", 200); skip(500); narratorclean(mc," can't remember anything.", 80); skip(1500);
		cout << endl;
		narrator("What's happening! ", 80); skip(600); narratorclean(vc,"Why can't I control my body? ", 100); skip(500); narratorclean(vc,"This... ", 175); skip(300); narratorclean(vc,"This is not my body!", 80);
		cout << endl;
		MCS("Who said that? ", 40); skip(750);
		cout << endl;
		MCS("Where are you? Show yourself!", 75); skip(1000);
		cout << endl;
		narrator("I can't show myself.", 80); skip(1000); cout << endl;
		MCS("What do you mean?", 80); skip(1000);
		cout << endl;
		narrator("I myself have no idea.", 80); skip(500); narratorclean(vc," It seems like...", 120); skip(400); narratorclean(vc," I am in you.", 100); skip(750);
		cout << endl << endl; truenarrator("1) Why are you in me?", 50); cout << "\n"; truenarrator("2) How is that possible?",50); cout << "\n"; truenarrator("3) What happened to my memories?",50); cout << "\n"; truenarrator("4) You're lying. You're hiding behind those trees aren't you?",50); 
		cout << "\n\n\033[33m>>    ";
		diadec2 = GVIclean(1,4);
		cout << "\033[0m";
		if(diadec2=="1"){
			MCSC(mc, "Why are you in me?", 80); skip(1000);
			cout << endl;
			narrator("Good question.", 80); skip(500); narratorclean(vc," All I can remember is my death,", 80); skip(250); narratorclean(vc," and now,", 125); narratorclean(vc," I find myself here,", 100); skip(500); narratorclean(vc," in your body.", 100); skip(1000);
			cout << endl << endl; truenarrator("1) What do you mean your death?", 50); cout << "\n"; truenarrator("2) Hold on, you're dead?",50); cout << "\n"; truenarrator("3) Is this a dream?",50); cout << "\n"; truenarrator("4) Huh?",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				MCSC(mc,"What do you mean your death?", 80); skip(1000);
				cout << endl;
				narrator("This has to be a nightmare.", 80); skip(1000);
				cout << endl;
				narrator("Well,", 125); skip(400); narratorclean(vc," we don't really have a choice,",80); skip(300); narratorclean(vc," stand up and look around.", 80 ); skip(250);
				cout << endl;
				narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
				cout << endl;
				narrator("and why you don't remember anything.", 80); skip(400); narratorclean(vc," Stand up before someone,", 100);skip(200); narratorclean(vc," or worse,", 125); skip(200); narratorclean(vc," something finds us.", 100); skip(1000);
				cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) Is this a nightmare?",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc,"Why should I listen to you?", 80); skip(1000);
					cout << endl;
					narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
				}
				if(diadec4=="2"){
					MCSC(mc,"I don't trust you.", 80); skip(1000);
					cout << endl;
					narrator("You don't have to trust", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
					cout << endl;
					MCS("Fine.", 100); skip(1500);
				}
				if(diadec4=="3"){
					MCSC(mc,"Is this a nigthmare?", 80); skip(1000);
					cout << endl;
					narrator("Oh, come on.", 80); skip(400); narratorclean(vc," No, this is not a nightmare.", 80); skip(400); narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); skip(200); cout << endl;
					narrator("Dying in a dream sucks as well.", 80);  skip(400); narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); skip(1000);
					MCS("Okay, I'll comply.", 80); skip(1500);
				}
				if(diadec4=="4"){
					MCSC(mc,"Okay, we should get going.", 80); skip(1000);
					cout << endl;
					narrator("Great, let's go that way.", 80);  skip(500); narratorclean(vc," It looks like there might be something there.", 75); skip(1500);
				}
			}
			else if(diadec3=="2"){
				MCSC(mc,"Hold on, you're dead?", 70); skip(1000);
				cout << endl;
				narrator("Affirmative, it does seem that way.", 80); skip(1000);
				cout << endl;
				narrator("Well,", 125); skip(400); narratorclean(vc," we don't really have time and a choice,",80); skip(300); narratorclean(vc," stand up and look around.", 80 ); skip(250);
				cout << endl;
				narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
				cout << endl;
				narrator("and why you don't remember anything.", 80); skip(400); narratorclean(vc," Stand up before someone,", 100);skip(200); narratorclean(vc," or worse,", 125); skip(200); narratorclean(vc," something finds us.", 100); skip(1000);
				cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) Is this a nightmare?",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc,"Why should I listen to you?", 80); skip(1000);
					cout << endl;
					narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
				}
				if(diadec4=="2"){
					MCSC(mc,"I don't trust you.", 80); skip(1000);
					cout << endl;
					narrator("You don't have to trust me.", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
					cout << endl;
					MCS("Fine.", 100); skip(1500);
				}
				if(diadec4=="3"){
					MCSC(mc,"Is this a nightmare?", 80); skip(1000);
					cout << endl;
					narrator("Oh, come on.", 80); skip(400); narratorclean(vc," No, this is not a nightmare.", 80); skip(400); narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); skip(200); cout << endl;
					narrator("Dying in a dream sucks as well.", 80);  skip(400); narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); skip(1000);
					MCS("Okay, I'll comply.", 80); skip(1500);
				}
				if(diadec4=="4"){
					MCSC(mc,"Okay, we should get going.", 80); skip(1000);
					cout << endl;
					narrator("Great, let's go that way.", 80);  skip(500); narratorclean(vc," It looks like there might be something there.", 75); skip(1500);
				}
			}
			else if(diadec3=="3"){
				MCSC(mc,"That's not possible!", 70); narratorclean(mc," Am I dreaming?", 100); skip(1000);
				cout << endl;
				narrator("I understand the difficulty of comprehending a situation like this,", 80); skip(400); narratorclean(vc," however,", 100); skip(250); narratorclean(mc," dream or not,", 100); skip(250);
				cout << endl;
				narrator("we have to move. So, I would advise you to get up before someone,", 125); skip(400); narratorclean(vc," or worse,",80); skip(300); narratorclean(vc," something,", 80 ); skip(250); narratorclean(vc," finds us.", 80 );
				cout << endl;
				narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
				cout << endl;
				narrator("and why you don't remember anything.", 80);
				cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) This is insane.",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc,"Why should I listen to you?", 80); skip(1000);
					cout << endl;
					narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
				}
				if(diadec4=="2"){
					MCSC(mc,"I don't trust you.", 80); skip(1000);
					cout << endl;
					narrator("You don't have to trust me.", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
					cout << endl;
					MCS("Fine.", 100); skip(1500);
				}
				if(diadec4=="3"){
					MCSC(mc,"This is insane.", 80); skip(400); narratorclean(mc," I don't understand.", 80 ); skip(250); narratorclean(vc," But I'll comply.", 80 ); skip(1000);
					cout << endl;
					narrator("I'll explain what I know once we get out of here.", 80); skip(1500);
				}
				if(diadec4=="4"){
					MCSC(mc,"Okay, we should get going.", 80); skip(1000);
					cout << endl;
					narrator("Great, let's go that way.", 80);  skip(500); narratorclean(vc," It looks like there might be something there.", 75); skip(1500);
				}
			}
			else if(diadec3=="4"){
				MCSC(mc,"Huh?", 70); skip(1000);
				cout << endl;
				narrator("I understand if comprehending it is beyond your current capabilities,", 80); skip(400); narratorclean(vc," however,", 100); skip(250); 
				cout << endl;
				narrator("we have to move. So, I would advise you to get up before someone,", 125); skip(400); narratorclean(vc," or worse,",80); skip(300); narratorclean(vc," something,", 80 ); skip(250); narratorclean(vc," finds us.", 80 );
				cout << endl;
				narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
				cout << endl;
				narrator("and why you don't remember anything.", 80);
				cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) Is this a nightmare?",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc,"Why should I listen to you?", 80); skip(1000);
					cout << endl;
					narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
				}
				if(diadec4=="2"){
					MCSC(mc,"I don't trust you.", 80); skip(1000);
					cout << endl;
					narrator("You don't have to trust me.", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
					cout << endl;
					MCS("Fine.", 100); skip(1500);
				}
				if(diadec4=="3"){
					MCSC(mc,"Is this a nightmare?", 80); skip(1000);
					cout << endl;
					narrator("Oh, come on.", 80); skip(400); narratorclean(vc," No, this is not a nightmare.", 80); skip(400); narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); skip(200); cout << endl;
					narrator("Dying in a dream sucks as well.", 80);  skip(400); narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); skip(1000);
					MCS("Okay, I'll comply.", 80); skip(1500);
				}
				if(diadec4=="4"){
					MCSC(mc,"Okay, we should get going.", 80); skip(1000);
					cout << endl;
					narrator("Great, let's go that way.", 80);  skip(500); narratorclean(vc," It looks like there might be something there.", 75); skip(1500);
				}
			}
		}
		else if(diadec2=="2"){
			MCSC(mc, "How is that possible?", 80); skip(1000);
			cout << endl;
			narrator("I don't know.", 80); skip(500); narratorclean(vc," But what I do know,", 80); skip(250); narratorclean(vc," is,", 125); narratorclean(vc," that we should get out of here,", 100); skip(500); cout << endl; narrator("we don't want anyone or anything to find us, do we now?", 80); skip(1000); narratorclean(vc," I'll tell you the answers on the way out of here,", 80); skip(250); cout << endl; narrator("just get up and move,", 80); skip(200); narratorclean(vc, " please.", 100); skip(1000);
			cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) Is this a nightmare?",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				MCSC(mc,"Why should I listen to you?", 80); skip(1000);
				cout << endl;
				narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
			}
			if(diadec3=="2"){
				MCSC(mc,"I don't trust you.", 80); skip(1000);
				cout << endl;
				narrator("You don't have to trust me.", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
				cout << endl;
				MCS("Fine.", 100); skip(1500);
			}
			if(diadec3=="3"){
				MCSC(mc,"Is this a nigthmare?", 80); skip(1000);
				cout << endl;
				narrator("Oh, come on.", 80); skip(400); narratorclean(vc," No, this is not a nightmare.", 80); skip(400); narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); skip(200); cout << endl;
				narrator("Dying in a dream sucks as well.", 80);  skip(400); narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); skip(1000); cout << endl;
				MCS("Okay, I'll comply.", 80); skip(1500);
			}
			if(diadec3=="4"){
				MCSC(mc,"Okay, we should get going.", 80); skip(1000);
				cout << endl;
				narrator("Great, let's go that way.", 80);  skip(500); narratorclean(vc," It looks like there might be something there.", 75); skip(1500);
			}
		}
		if(diadec2=="3"){
			MCSC(mc, "But where are my memories?", 80); skip(400); narratorclean(mc," You just came here into my mind, and all of them are gone.", 80); skip(400);narratorclean(mc, " What have you done to them?", 80); skip(1000);
			cout << endl;
			narrator("I haven't done anything to your memories.", 80); skip(500); narratorclean(vc," I know nothing,", 80); skip(250); narratorclean(vc," same as you.", 125); skip(400); narratorclean(vc," Do you think I want to be here?", 100); skip(500); cout << endl; narrator("I somehow died and now I am here,", 80); skip(250); narratorclean(vc, " in your body,", 100); narratorclean(vc, " which I can't control.", 100); skip(250); cout << endl; narrator("But,", 80); skip(250); narratorclean(vc," here we are,", 80); skip(250); narratorclean(vc," so move your ass and get up.", 80); skip(1000);
			cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) I don't trust you.",50); cout << "\n"; truenarrator("3) This has to be a nightmare.",50); cout << "\n"; truenarrator("4) Okay, we should get going.",50); 	
			cout << "\n\n\033[33m>>    ";
			diadec3 = GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				MCSC(mc,"Why should I listen to you?", 80); skip(1000);
				cout << endl;
				narrator("Does it look like you have a choice? What else do you want to do?", 75); skip(1500);
			}
			if(diadec3=="2"){
				MCSC(mc,"I don't trust you.", 80); skip(1000);
				cout << endl;
				narrator("You don't have to trust me.", 75); skip(250); narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); skip(1000);
				cout << endl;
				MCS("Fine.", 100); skip(1500);
			}
			if(diadec3=="3"){
				MCSC(mc,"This has to be a nightmare!...", 80); narratorclean(mc, "URGHHHH!", 80); skip(1000);
				cout << endl;
				narrator("We have no choice,", 80); skip(400); narratorclean(vc," we must cooperate,", 80); skip(400); narratorclean(vc," unless you want to die.", 80); skip(1000); 
				cout << endl << endl; truenarrator("1) Okay, let's go.", 50); cout << "\n"; truenarrator("2) Wait, why would I die?",50); cout << "\n"; truenarrator("3) No! I want to go my own way.",50); cout << "\n"; truenarrator("4) I'm not moving unless you tell me who you are.",50); 	
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,4); 
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc,"Okay, let's go.", 80); skip(1000);
					cout << endl;
					narrator("Great.", 75); narratorclean(vc," Time to move this way.", 75); skip(1500);
				}
				if(diadec4=="2"){
					MCSC(mc,"Wait, why would I die?", 80); skip(1000);
					cout << endl;
					narrator("Because you will be alone in this world,", 75); skip(250); narratorclean(vc, " without memories,", 75); skip(250); narratorclean(vc, " forgotten to everyone,", 75); skip(250); narratorclean(vc, " and an easy target for enemies.", 75); skip(250); cout << endl; narrator("We're not alone in this forest.", 80); skip(250); narratorclean(vc, " I can help you get out of here safely.", 75); skip(1000); 
					cout << endl;
					MCS("Why is this happening to me?", 75); skip(1000);
					cout << endl;
					narrator("I know you're scared and frustrated.", 80); skip(250); narratorclean(vc," But trust me,", 100); skip(400); narratorclean(vc," the only way for both of us to survive is to get up and move.", 80); skip(1000);
					cout << endl;
					MCS("I guess I have no choice...", 80); skip(250); narratorclean(mc," Fine,", 100); skip(250); narratorclean(mc," I'll cooperate.", 80); skip(1000);
					cout << endl;
					narrator("Okay, great. Let's go that way.", 80); skip(1500);
				}
				if(diadec4=="3"){
					MCSC(mc,"No! I want to go my own way.", 80); skip(1000);
					cout << endl;
					narrator("You know what, fine, go your own way, we'll see how that goes.", 75); skip(1500);
					// endingplaceholder1();
				}
				if(diadec4=="4"){
					MCSC(mc,"I'm not moving unless you tell me who you are.", 80); skip(1000);
					cout << endl;
					narrator("Fine, fine.", 80);  skip(500); narratorclean(vc," I'll tell you...", 75); skip(250); narratorclean(vc," My name is Void.", 75); skip(250); narratorclean(vc," I was the general of a faction", 75); cout << endl; narrator("called Terragnis.", 75); skip(250); narratorclean(vc," We were in a war against another faction called Slofridi.", 75); skip(250); narratorclean(vc," When I was in a battle,", 80); skip(250); cout << endl; narrator("an arrow hit me.", 75); skip(250); narratorclean(vc," But,", 100); skip(400); narratorclean(vc," somehow,", 100); skip(250); narratorclean(vc," I didn't die.", 100); skip(250); narratorclean(vc," Suddenly,", 100); skip(250); cout << endl; narrator(" a bright light flashed before it was followed by darkness.", 75); skip(250); narratorclean(vc," When I came to my senses, I found myself in someone else's body...", 75); skip(250); cout << endl; narrator("in your body.", 75); skip(400); narratorclean(vc," And now,", 100); skip(250); narratorclean(vc," we're here.", 100); skip(1500);
					cout << endl;
					MCS("So, you died and woke up in my head.", 80); skip(1000);
					cout << endl;
					narrator("To put it shortly, yes.", 80); skip(1000);
					cout << endl;
					MCS("But, how is that possible?", 80); skip(1000); 
					cout << endl;
					narrator("I told you everything I know.", 80);  skip(500); narratorclean(vc," I would like to know more too,", 75); skip(250); narratorclean(vc, " but we will find out nothing if we just sit here.", 80); skip(1000);
					cout << endl;
					MCS("You have a point,", 80); skip(250); narratorclean(mc," let's get out of here.", 75); skip(1500);		
				}
			}
		}
		else if(diadec2=="4"){
			MCSC(mc, "You're lying.", 80); skip(250); narratorclean(mc, " You're hiding behind those trees, aren't you?", 80); skip(1000);
			cout << endl;
			narrator("I am not one lie to lie.", 80); skip(250); narratorclean(vc, " Only when it is an utter necessity.", 80); skip(250); cout << endl; narrator("You should get up and move your ass before you get us both killed by someone or something.", 80); skip(1000);
			cout << endl << endl; truenarrator("1) Alright, let's get going.", 50); cout << "\n"; truenarrator("2) I will need a further explanation in order to comply.",50); cout << "\n"; truenarrator("3) I don't understand, how is this possible?",50); cout << "\n"; truenarrator("4) I'm not buying that. You are trying to lure me out.",50);
			cout << "\n\n\033[33m>>    ";
			diadec3 = GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				MCSC(mc, "Alright,", 80); skip(250); narratorclean(mc, " let's get going.", 75); skip(1000);
				cout << endl;
				narrator("Okay, great.", 80); skip(250); narratorclean(vc, "Let's go that way,", 80); skip(250); narratorclean(vc, " it seems like there might be something there.", 80); skip(1500);
			}
			else if(diadec3=="2"){
				MCSC(mc, "I will need a further explanation in order to comply.", 80); skip(1000);
				cout << endl;
				narrator("I told you,", 80); skip(400); narratorclean(vc, " I don't know.", 80); narratorclean(vc, " All I know is that I am stuck here in your mind and that you're gonna get us", 80); cout << endl; narrator("killed if you don't move,",80); skip(250); narratorclean(vc, " so please,", 100); skip(250); narratorclean(vc, " move,", 100); skip(250); narratorclean(vc, " and I'll tell you more when we're on the move.", 80); skip(1000); 
				cout << endl << endl; truenarrator("1) Why should I listen to you?", 50); cout << "\n"; truenarrator("2) Nope, still don't trust you. I refuse to believe this.", 50); cout << "\n"; truenarrator("3) Alright, I'll move", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,3);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc, "Why should I listen to you?", 80); skip(1000);
					narrator("You don't have a choice.", 80); skip(250); narratorclean(vc, " Or maybe you do,", 80); skip(250); narratorclean(vc, " do whatever you want,", 80); skip(250); narratorclean(vc, " you want to die?", 80); skip(400); narratorclean(vc, " Fine, then.", 80); skip(1000);
					cout << endl << endl; truenarrator("1) I'll go my own way.", 50); cout << "\n"; truenarrator("2) Okay, I'm sorry. I'll do what you want now.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = GVIclean(1,4);
					cout << "\033[0m";
					if(diadec5=="1"){
						MCSC(mc, "I'll go my own way.", 50); skip(1000);
						cout << endl;
						narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
						// endingplaceholder1();
					}
					else{
						MCSC(mc, "Okay,", 100); skip(250); narratorclean(mc, " I'm sorry.", 80); skip(400); narratorclean(mc, " I'll do what you want now.", 80); skip(1000);
						cout << endl;
						narrator("At last.", 80); skip(400); narratorclean(vc, " Well,", 100); skip(250); narratorclean(vc, " no time to lose,", 80); skip(250); narratorclean(vc, " get up and go that way.", 80); skip(1500);
					}
				}
				else if(diadec4=="2"){
					MCSC(mc, "Nope,", 100); skip(250); narratorclean(mc, " still don't trust you.", 80); skip(400); narratorclean(mc, " I refuse to believe this.", 80); skip(1000);
					cout << endl;
					narrator("So,", 100); skip(250); narratorclean(vc, " you want to die here then?", 80); skip(400); narratorclean(vc, " Alright,", 100); skip(250); narratorclean(vc, " go your own way then.", 80); skip(1000);
					cout << endl << endl; truenarrator("1) I'll be on my own way.", 50); cout << "\n"; truenarrator("2) You know what, fine, I'll listen to you for now.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						MCSC(mc, "I'll be on my own way.", 50); skip(1000);
						cout << endl;
						narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
						// endingplaceholder1();
					}
					else{
						MCSC(mc, "You know what,", 80); skip(250); narratorclean(mc, " fine,", 80); skip(250); narratorclean(mc, " I'll listen to you for now.", 80); skip(1000);
						cout << endl;
						narrator("Finally...", 80); skip(400); narratorclean(vc, " We can move.", 80); skip(400); narratorclean(vc, " Stand up,", 80); skip(250); narratorclean(vc, " and let's go this way.", 80); skip(1500);
					}
				}
				else{
					MCSC(mc, "Alright,", 100); skip(250); narratorclean(mc, " I'll move.", 80); skip(1000);
					cout << endl;
					narrator("Good,", 100); skip(250); narratorclean(vc, " alright,", 100); skip(250); narratorclean(vc, " we should 	go that way.", 80); skip(1500);
				}
			}
			else if(diadec3=="3"){
				MCSC(mc, "I don't understand, how is this possible?", 80); skip(1000);
				cout << endl;
				narrator("I don't understand either.", 80); skip(400); narratorclean(vc, " We can figure it out together,", 80); skip(250); narratorclean(vc, " just,", 80); skip(250); narratorclean(vc, " please,", 100); skip(250); narratorclean(vc, " move.", 100); skip(1000); 
				cout << endl << endl; truenarrator("1) Okay, I'm sorry, I'll move.", 50); cout << "\n"; truenarrator("2) How about, no?", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,2);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc, "Okay,", 100); skip(250); narratorclean(mc, " I'm sorry,", 80); skip(250); narratorclean(mc, " I'll move.", 90); skip(1000);
					cout << endl;
					narrator("It's okay", 80); skip(250); narratorclean(vc, " let's go that way.", 80); skip(250); narratorclean(vc, " I can see something sticking out, there might be something there.", 80); skip(1000);
				}
				else{
					MCSC(mc, "How about,", 80); skip(250); narratorclean(mc, " no?", 100); skip(1000);
					cout << endl;
					narrator("Are you sure you want me as your enemy?", 80); skip(400); narratorclean(vc, " Remember,", 80); skip(250); narratorclean(vc, " I am inside your mind,", 80); skip(250); narratorclean(vc, " and I can make this", 80); cout << endl; narrator("a living hell for you.", 80); skip(1000);
					cout << endl << endl; truenarrator("1) Yes, I want to go my own way.", 50); cout << "\n"; truenarrator("2) I changed my mind, I'm sorry, I'll listen to you.", 50); 
					cout << "\n\n\033[33m>>    ";
					diadec5 = GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						MCSC(mc, "Yes, I want to go my own way.", 80); skip(1000);
						cout << endl;
						narrator("You know what, fine, go your own way, we'll see how that goes.", 80); skip(1500);
						// endingplaceholder1();
					}
					else{
						MCSC(mc, "I changed my mind,",80); skip(250); narratorclean(mc, " I'm sorry,", 100); skip(250); narratorclean(mc, " I'll listen to you.", 80); skip(1000);
						cout << endl;
						narrator("At last,", 80); skip(250); narratorclean(vc, " okay,", 100); skip(250); narratorclean(vc, "let's go that way,", 80); skip(250); narratorclean(vc, " I'll try to explain what I know.", 80); skip(250); narratorclean(vc, " If we want to live together", 80); cout << endl; narrator("in peace,", 80); skip(250); narratorclean(vc, " we have to cooperate.", 80); skip(1500); 
					}
				}
			}
			else{
				MCSC(mc, "I'm not buying that.", 80); skip(250); narratorclean(mc, " You are trying to lure me out.", 80); skip(1000);
				cout << endl;
				narrator("Okay, seriously?", 75); skip(250); narratorclean(vc, " Listen,", 80); narratorclean(vc," you don't have a choice,", 80); narratorclean(vc," move,",100); narratorclean(vc," you have nothing to lose.", 80); skip(1000); 
				cout << endl << endl; truenarrator("1) Stop talking to me, I want to go my own way.", 50); cout << "\n"; truenarrator("2) Fine.", 50); cout << "\n"; truenarrator("3) I'm sorry, I was just  making sure. We can move now.", 50); 
				cout << "\n\n\033[33m>>    ";
				diadec4 = GVIclean(1,2);
				cout << "\033[0m";
				if(diadec4=="1"){
					MCSC(mc, "Stop talking to me,", 80); skip(250); narratorclean(mc, " I want to go my own way.", 80); skip(1000);
					cout << endl;
					narrator("You know what, fine, go your own way, we'll see how that goes.", 80); skip(1500);
					// endingplaceholder1();
				}
				else if(diadec4=="2"){
					MCSC(mc, "Fine.", 80); skip(1000);
					cout << endl;
					narrator("This attitude is insane,", 80); skip(250); narratorclean(vc, " show some respect to the inhabitant of your mind.", 80); skip(250); narratorclean(vc, "Look around a little,", 80); skip(250); cout << endl; narrator("there looks to be something that way.", 80); skip(1500);
				}
				else{
					MCSC(mc, "I'm sorry,", 100); skip(250); narratorclean(mc, " I was just making sure.", 80); skip(250); narratorclean(mc, " We can move now.", 80); skip(1000);
					cout << endl;
					narrator("It is alright,", 80); skip(250); narratorclean(vc, " I understand.", 80); skip(400); narratorclean(vc, " Let's go now.", 80); skip(250); narratorclean(vc, " That way seems to lead somewhere.", 80); skip(1500);
				}
			}
		}
		cout << endl;
		cout << endl;
		d1();
		while(true){
			if(a>0 || b>0) d1();
			cout << endl << endl;
			flushInput();
			cout << "\033[33m>>    ";
			decision1 = GVIclean(1,5);
			cout << "\033[0m";
			if(decision1=="1"){
				MCSC(mc, "I want to see the trees.", 80);
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
				MCSC(mc, "I want to see those trees.", 80);
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
				MCSC(mc, "I must see these trees.", 80);
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
				MCSC(mc, "I would like to see where this path leads.", 80);
				cout << endl << endl;
				truenarrator("Okay, you decide you want to see the destination of this path. Are you sure you don't want to check\n      the abandoned place where your stuff might lay out first?", 50);
				cout << endl << endl;
				skip(250);
				truenarrator("1) Go through with your initial decision\n      2) Abort", 50);
				cout << endl << endl;
				flushInput();
				cout << "\033[33m>>    ";
				decision1sub1 = GVI(1,2);
				cout << "\033[0m";
				if(decision1sub1=="1"){
					MCSC(mc, "I really want to know where it leads.", 80);
					cout << endl << endl;
					truenarrator("Very well, you decide to embark on an adventurous journe- nevermind, you die. Reason: UNKN0WN", 50);
					skip(400);
					cout << endl << endl << endl;
					truenarrator("\n      [Press F to pay respects(load the last save)]", 50);
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
					MCSC(mc, "I think we should check that strange abandoned place first.", 80);
					cout << endl << endl;
					truenarrator("At last, you decide to check the strange place with abandoned stuff out. You see the following:",50); cout << "\n\n"; truenarrator("- Tea",50); cout << "\n"; truenarrator("- An iron sword",50); cout << "\n"; truenarrator("- Golden armor with a low durability",50); cout << "\n"; truenarrator("- A shield",50); cout << "\n"; truenarrator("- Elixir of Love",50); cout << "\n"; truenarrator("- A stick",50); cout << "\n"; truenarrator("- Bandage x3",50); cout << "\n"; truenarrator("- A small backpack", 50);
					break;
				}
			}
			else if(decision1=="5"){
				MCSC(mc, "I would like to check the strange abandoned place out first.", 80);
				cout << endl << endl;
				truenarrator("Great choice, better than \"trees\" atleast, you near the abandoned things and find the following:",50); cout << "\n\n"; truenarrator("- Tea",50); cout << "\n"; truenarrator("- An iron sword",50); cout << "\n"; truenarrator("- Golden armor with a low durability",50); cout << "\n"; truenarrator("- A shield",50); cout << "\n"; truenarrator("- Elixir of Love",50); cout << "\n"; truenarrator("- A stick",50); cout << "\n"; truenarrator("- Bandage x3",50); cout << "\n"; truenarrator("- A small backpack", 50); break;
			}
		}
		cout << endl << endl;
		narrator("Great.", 100); skip(250); narratorclean(vc," These things will come in handy. Grab them and let's get out of here.", 80); skip(1000);
		cout << endl << endl;
		truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); skip(500);
		cout << endl << endl;
		MCS("Good idea, let's follow that path we saw earlier, it looks like it leads to a meadow.", 80); skip(1000);
		cout << endl << endl;
		truenarrator("You are approached by a pack of wolves ready to attack you. You have to defend yourself.", 50); cout << endl; truenarrator("In a quick manner, you have to choose the action you take: ", 50); cout << endl << endl; truenarrator("1) Use a stick to fight them",50); skip(200); cout << endl; truenarrator("2) Use an iron sword to fight them", 50); cout << endl; truenarrator("3) Try to distract them with the stick instead of fighting.", 50); cout << endl << endl;
		cout << "\033[33m>>    ";
		decision2 = GVI(1,3);
		cout << "\033[0m" << endl;
		if(decision2=="1"){
			truenarrator("You decide to take out the stick and use it to fight the wolves off. Commencing combat.", 50); skip(200);
			ambush("Wolves", 20, 3, 1, 1); 
		}
		else if(decision2=="2"){
			truenarrator("You decide to take out the iron sword and use it to fight the wolves off. Commencing combat.", 50); skip(200);
			ambush("Wolves", 20, 3, 1, 1); 
		}
		else if(decision2=="3"){
			int wolfescapechance = rand()%4;
			if(wolfescapechance==1){
				truenarrator("You attempt to distract the wolves using a stick. You throw it and the wolves indeed do get distracted.", 50); // Achievement, 25% chance to work 
			}
			else{
				truenarrator("You try to distract the wolves with the stick, but they fail to notice it and devour you.", 50); skip(400); cout << endl;
				truenarrator("[Press F to pay respects(load last save)]",50);
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		break;
						}
					}
				}
				sequence1();
			}
		}
		if(decision2=="3"){
			cout << endl << endl; narrator("That was really weird,", 80); narratorclean(vc," I never would have thought of that.", 80); narratorclean(vc," Great job.", 100); skip(1000);
			cout << endl;
			MCS("I too am surprised that worked.", 80); narratorclean(mc," Let's maybe get out of here.", 80); skip(1000);
		}
		else{
			narrator("Good job fighting those wolves off.", 80); skip(250); narratorclean(vc," We should probably get out of here.", 80); skip(400);
			cout << endl;
			MCS("Thank you, yes, we should get out of here.", 80); skip(1000); cout << endl;			
		}
		sequence2();
	}
	void sequence2(){
		if(sequence==1) sequence++; save(); system("cls"); Sleep(1000);
		cout << "\n\n\n\n\n\n        {[()]} Sequence 2 {[()]}\n\n\n"; Sleep(1000); truenarrator("  You're doing great!(not)", 50); Sleep(2000); system("cls"); Sleep(2500);
		cout << endl;
		truenarrator("You walk through a captivating meadow, full of birds, dead bodies and charred weapons.", 50); skip(1000);
		cout << endl << endl;
		MCS("What happened here?", 100); skip(750);
		cout << endl;
		narrator("A minor clash, it seems.", 80); skip(250);
		cout << endl;
		narrator("It reminds me of the field where they got me.", 75); skip(750);
		cout << endl;
		MCS("Got you?", 75); narratorclean(mc," When will you finally tell me what you meant by your death?", 80); skip(1000); 
		cout << endl;
		narrator("Very well.", 75); narratorclean(vc," My faction got into a fight with another faction. I was the general, leading an army.", 75); cout << endl;
		narrator("While I was fighting, an arrow hit me. Instead of dying, I saw a bright flash followed by darkness.", 75); cout << endl;
		narrator("I then woke up in a different body,", 75); skip(250); narratorclean(vc," your body.", 80); skip(400); narratorclean(vc," And now, we're here.", 75); skip(500);
		cout << endl;
		MCS("I don't remember what happened before we", 80); skip(200); narratorclean(mc,"...", 250); skip(250); narratorclean(mc,"merged.", 75); skip(1000); 
		cout << endl << endl;
	}
};
int main(){
	SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	HWND consoleWindow = GetConsoleWindow();
  SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	Game GameDef;
	srand(time(0));
	if(GameDef.CheckSave()) GameDef.savesequence();
	else GameDef.introsequence();
	return 0;
}
