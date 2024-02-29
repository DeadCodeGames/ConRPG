#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>

#include "CONFunctions.h"

using namespace std;
class Game {
public:

	Functions FunctionDef;
	string lang, playerName="", mode, fightstatus, input, tb, decision1, decision1sub1, b1pathdec, decision2="";
	string diadec1, diadec2, diadec3, diadec4, diadec5;
	string b0, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
	const string mc = "\033[33m", vc = "\033[36m";
	int saveload, relwvoid, a=0, b=0, sequence, level, xp, requiredxp, xpgained, initiallvl, plvlbonusdmg, lives;
	double perlevel, hp, currenthp, maxdmg;
	bool isAlive = true, earlyexplanation = false, ExistujeSave;

	bool CheckSave() {
		const wstring folderPath = L"save";
		DWORD folderAttributes = GetFileAttributesW(folderPath.c_str());

		if (folderAttributes == INVALID_FILE_ATTRIBUTES || !(folderAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (CreateDirectoryW(folderPath.c_str(), nullptr) == 0 && GetLastError() != ERROR_ALREADY_EXISTS) {
				cerr << "[!] Save File Cannot be created!" << "\n";
				return false;
			}

			return false;
		}
		
		return true;
	}

	void UlozitInfo(const string& data, const string& fileName) {
		const string folderPath = "save";
		const string filePath = folderPath + "\\" + fileName;

		ofstream file(filePath);

		if (file.is_open()) {
			file << data;

			file.close();
		}
		else {
			cout << "[!] An error occurred";
		}
	}
	string PrecitatInfo(const string& fileName) {
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
			cout << "[!] An error occurred" << "\n";
			return "";
		}
	}
	void save() {
		UlozitInfo(to_string(sequence), "sequence.txt");
		UlozitInfo(to_string(level), "PlayerLevel.txt");
		UlozitInfo(to_string(xp), "PlayerXp.txt");
		UlozitInfo(to_string(hp), "PlayerHp.txt");
		UlozitInfo(to_string(currenthp), "PlayerCurrentHp.txt");
		UlozitInfo(to_string(maxdmg), "PlayerMaxDmg.txt");
		UlozitInfo(playerName, "PlayerName.txt");
		UlozitInfo(mode, "Mode.txt");
	}
	void load() {
		string strSequence = PrecitatInfo("sequence.txt");
		string strLevel = PrecitatInfo("PlayerLevel.txt");
		string strXp = PrecitatInfo("PlayerXp.txt");
		string strHp = PrecitatInfo("PlayerHp.txt");
		string strCurrenthp = PrecitatInfo("PlayerCurrentHp.txt");
		string strMaxdmg = PrecitatInfo("PlayerMaxDmg.txt");
		playerName = PrecitatInfo("PlayerName.txt");
		mode = PrecitatInfo("Mode.txt");
		lang = PrecitatInfo("Language.txt");

		sequence = stoi(strSequence);
		level = stoi(strLevel);
		xp = stoi(strXp);
		hp = stoi(strHp);
		currenthp = stoi(strCurrenthp);
		maxdmg = stoi(strMaxdmg);
		requiredxp=10*pow(1.2, level);
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
	cout << "\n      Leveled up! Went from lvl " << initiallvl << " to lvl " << level << ". HP: " << currenthp << " -> " << hp << "\n";
	cout << "      Current xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << "\n";
	}
	save();
	}
	void statreset(){
		playerName="", mode="", fightstatus="", input="", tb="", decision1="", decision1sub1="", b1pathdec="", decision2="", diadec1="", diadec2="", diadec3="", diadec4="", diadec5="", hp=20, level=0, xp=0, currenthp=20;
	}
	void deathsequence(){
		system("cls");
		cout << "\n\n"; FunctionDef.truenarrator("\tWhoops...", 50); FunctionDef.skip(200); FunctionDef.TNC(" it lowkey seems like someone has lost a life.", 50); FunctionDef.skip(200); cout << "\n";
		if(lives!=0){
			FunctionDef.truenarrator("\tDon't worry though, brave traveller.", 50); FunctionDef.skip(200); FunctionDef.TNC(" Death is experience, and experience is life.", 50); FunctionDef.skip(200); 
			if(lives!=1) FunctionDef.TNC("You have " + to_string(lives) + " lives remaining.", 50);
			else FunctionDef.TNC("You have 1 life remaining...", 50);
			cout << "\n"; FunctionDef.skip(250);
			FunctionDef.truenarrator("\t[Press F to respawn, L to start new game]", 50);
			while(true){
				if(_kbhit()){
			  	char key = _getch();
			  	if(key=='f'){
			  		if(sequence==1) sequence1();
			  		else if(sequence==2) sequence2();
					}
					else{
						statreset();
						picklanguage();
					}
				}
			}
		}
		else{
			FunctionDef.truenarrator("\tAnd it was your last one...", 50); FunctionDef.skip(250); FunctionDef.TNC("I'm sorry this happened to you.", 50); FunctionDef.skip(250);
			cout << "\n";
			FunctionDef.truenarrator("\t[Press L to start new game.]", 50); 
			while(true){
				if(_kbhit()){
			  	char key = _getch();
					if(key=='l'){
						statreset();
						picklanguage();
					}
				}
			}
		}
	}
	int ambush(string attacker, string language) {

		UlozitInfo(to_string(sequence), "sequence.txt");
		UlozitInfo(to_string(level), "PlayerLevel.txt");
		UlozitInfo(to_string(xp), "PlayerXp.txt");
		UlozitInfo(to_string(hp), "PlayerHp.txt");
		UlozitInfo(to_string(currenthp), "PlayerCurrentHp.txt");
		UlozitInfo(to_string(maxdmg), "PlayerMaxDmg.txt");
		UlozitInfo(playerName, "PlayerName.txt");

		UlozitInfo(attacker, "attacker.txt");

		Sleep(2000);
		cout << endl << "      "; FunctionDef.truenarrator("Prepare to fight...", 50); Sleep(500);
		const char* programName = "combatmoreeffective.exe";
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		WCHAR wProgramName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, programName, -1, wProgramName, MAX_PATH); 
		char commandLine[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, wProgramName, -1, commandLine, MAX_PATH, NULL, NULL);
		if(language=="en"){
			if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
				WaitForSingleObject(pi.hProcess, INFINITE);
			}
			else {
				cout << "Error launching program" << "\n";
			}
			ifstream inputFile("testsave.txt");
		  if (!inputFile.is_open()) {
		    cerr << "Error opening file for reading!" << "\n";
		    return 1;
		  }
		  inputFile >> fightstatus;
		  inputFile >> xpgained;
		  if(fightstatus=="1"){
		  	FunctionDef.truenarrator("You aborted the fight... You automatically die.", 50); cout << "\n"; FunctionDef.skip(250); FunctionDef.truenarrator("[Press F to load the latest save/L to start over]",50);
				string strlives = PrecitatInfo("Lives.txt");
		    lives = stoi(strlives);
		    deathsequence();
			}
			else{
	      FunctionDef.truenarrator("You finished the fight.", 50); cout << "\n";
	    }
		}
		else{
			// tu preklad
		}
		Sleep(3000);
		xp+=xpgained;
		checkLevelUp();
		Sleep(2000);
	}
	void d1n() {
		if (a == 0) FunctionDef.truenarrator("\t  Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
		if (a == 1) FunctionDef.truenarrator("\t  For real? You visit the trees again, and... you don't find anything.", 50);
		if (a == 2) FunctionDef.truenarrator("\t  There is something weird about those trees. They're... trees.", 50);
		if (a > 2) {
			FunctionDef.truenarrator("\t  You visit the trees once more. Once again, you find nothin-", 50); cout << "\n";
			FunctionDef.truenarrator("\t  w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << "\n"; FunctionDef.skip(300);
			FunctionDef.truenarrator("\t  Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << "\n";
			FunctionDef.truenarrator("\t  before the fight even has a chance to begin.", 50); FunctionDef.skip(400); cout << "\n"; FunctionDef.skip(400); system("cls"); cout << "\n\n\n\n";
			FunctionDef.truenarrator("\t  \033[1;31mYou get the tree picker ending.\033[0m", 50); cout << "\n"; FunctionDef.skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
			lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence();
		}
	}

	// Decisions

	void d1() {
		FunctionDef.truenarrator("\t  You look around you. You see the following:", 50);
		cout << "\n";
		FunctionDef.truenarrator("\t  1) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  2) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  3) Trees", 50); cout << "\n"; FunctionDef.truenarrator("\t  4) A path", 50); cout << "\n"; FunctionDef.truenarrator("\t  5) A strange place between the trees, where abandoned stuff can be seen.", 50); FunctionDef.skip(500); cout << endl << "\n"; FunctionDef.truenarrator("\t  What do you choose?", 50);
		cout << "\n";
	}

	// Sequences
	void savesequence() {
		load();
		FunctionDef.truenarrator("\tWelcome back, " + playerName, 50); FunctionDef.skip(250); cout << "\n";
		FunctionDef.truenarrator("\tDo you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		while (true) {
			if (_kbhit()) {
				char keypressed = _getch();
				if (keypressed == 'f') {
					saveload = 1;
					if (sequence == 1) sequence1();
					else if (sequence == 2) sequence2();
				}
				else if (keypressed == 'l') {
					picklanguage();
				}
			}
		}
	}
	void picklanguage(){
		system("cls");
		FunctionDef.truenarrator("\tPick a language.", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("1 < English-EN >", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("2 < Slovak-SK >", 50);
		lang = FunctionDef.GVIclean(1,2);
		if(lang=="1") lang = "en";
		else lang = "sk";
		UlozitInfo(lang, "Language.txt");
		introsequence(lang);
	}
	void introsequence(string language){
		if(language=="en"){
			system("cls");
			if(mode=="speedrun"){
				mode = ""; UlozitInfo(mode, "Mode.txt");
				cout << "\n\n\n"; FunctionDef.truenarrator("\tYeahhhh, uhhh, you kind of abandoned your last speedrun session sooo, yeah, you know what that means...", 50); Sleep(2000);
				system("cls");
			}
			
			level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
			cout << "                                          W E L C O M E    T O" << "\n";
		 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
			cout << endl << "                                           The C++ Console RPG";
			cout << endl << "                                         Press [ANY KEY] to Begin";
			_getch();
			cout << "\n";FunctionDef.truenarrator("Hello Player", 100); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("...", 500); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("Your name isn't Player, is it?", 80); FunctionDef.skip(1500); cout << "\n";
			FunctionDef.truenarrator("What's your name?", 80); FunctionDef.skip(1000); cout << endl << "      [ENTER YOUR NAME NOW]" << "\n";
			FunctionDef.flushInput();
			cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
			if (!playerName.empty()) {
				FunctionDef.truenarrator("Nice to meet you, "+playerName+"!", 100);
			} 
			else {
				FunctionDef.truenarrator("You...", 500); FunctionDef.TNC(" don't have a name?", 125); FunctionDef.skip(500); FunctionDef.TNC(" I will give you one more chance to give me your name.", 80); cout << "\n"; 
				FunctionDef.flushInput();
				cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
				if (!playerName.empty()) {
					FunctionDef.truenarrator("At last, nice to meet you, "+playerName+"!", 80);
				} 
				else {
					FunctionDef.truenarrator("You sure?", 125); cout << "\n"; FunctionDef.skip(1000);
					FunctionDef.truenarrator("That's", 225); FunctionDef.TNC("...", 500); FunctionDef.skip(500); FunctionDef.TNC(" sad.", 200); cout << "\n"; FunctionDef.skip(750);
					FunctionDef.truenarrator("I still need something to call you by, though", 80); cout << "\n"; FunctionDef.skip(500);
					FunctionDef.truenarrator("Will Player suffice?", 75); FunctionDef.skip(500); FunctionDef.TNC(" I think it will be alright.", 75); playerName = "Player"; save();
				}
			} 
			FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("What mode would you like to explore today, fellow adventurer?", 80); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<1> EASY", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<2> NORMAL", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<3> HARD", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<4> SPEEDRUN", 50);
			mode = FunctionDef.GVIclean(1,4);
			if(mode=="1") mode = "easy";
			else if(mode=="2") mode = "normal";
			else if(mode=="3") mode = "hard";
			else if(mode=="4") mode = "speedrun";
			UlozitInfo(mode, "Mode.txt");
			system("cls");
			if(mode=="easy"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tEasy mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have an unlimited amount of respawns.", 50); 
				Sleep(2000); lives = -1;
			}
			else if(mode=="normal"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tNormal mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 3 respawns.", 50); 
				Sleep(2000); lives = 3;
			}
			else if(mode=="hard"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tHard mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 1 respawn.", 50); 
				Sleep(2000); lives = 1;
			}
			else{
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tSpeedrun mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tYou have 1 respawn and the game does not save. Godspeed on your adventure.", 50); 
				Sleep(2000); lives = 1;
			}
			UlozitInfo(to_string(lives), "Lives.txt");
			sequence=0;
			sequence1(language);
		}
		else{
			// tuto vlož svoj preklad introsequence, iba to co je vo vnutri funkcie, nie aj s tou funkciou, nezabudni na to ze som tam aj pridaval veci vsade som pridaval takze vsetko musis prejst znova ci tam nie je nieco navyse alebo namenej xd
		}
	}
	void sequence1(string language){
		if(language=="en"){
			system("cls");
			if(saveload==1){
				cout << "\n\n\n"; FunctionDef.truenarrator("\tWelcome back traveller. We missed you. You may now continue on your "+mode+ " mode journey.", 50); Sleep(2500);
				system("cls");
			}
			if(sequence==0) sequence++;
			save();
			Sleep(500);
			cout << "\n\n\n\n\n\n\t\t{[()]} Sequence 1 {[()]}\n\n\n"; Sleep(500);
			if(mode!="speedrun") FunctionDef.truenarrator("\t\tThe game saves every sequence. Good luck on your journey.", 50);
			else FunctionDef.truenarrator("\t\tThe game savesn't every sequence. Good luck on your journey.", 50);
			Sleep(2000); system("cls");
			Sleep(2500);
			FunctionDef.MCS("Where am I?", 80);FunctionDef.narratorclean(mc," How did I get here?",80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("There is a thick forest all around me.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("I, ", 100);FunctionDef.narratorclean(mc,"...", 200); FunctionDef.skip(500);FunctionDef.narratorclean(mc," can't remember anything.", 80); FunctionDef.skip(1500);
			cout << "\n";
			FunctionDef.narrator("What's happening! ", 80); FunctionDef.skip(600);FunctionDef.narratorclean(vc,"Why can't I control my body? ", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc,"This... ", 175); FunctionDef.skip(300);FunctionDef.narratorclean(vc,"This is not my body!", 80);
			cout << "\n";
			FunctionDef.MCS("Who said that? ", 40); FunctionDef.skip(750);
			cout << "\n";
			FunctionDef.MCS("Where are you? Show yourself!", 75); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("I can't show myself.", 80); FunctionDef.skip(1000); cout << "\n";
			FunctionDef.MCS("What do you mean?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("I myself have no idea.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," It seems like...", 120); FunctionDef.skip(400);FunctionDef.narratorclean(vc," I am in you.", 100); FunctionDef.skip(750);
			cout << endl << "\n";FunctionDef.truenarrator("1) Why are you in me?", 50); cout << "\n";FunctionDef.truenarrator("2) How is that possible?",50); cout << "\n";FunctionDef.truenarrator("3) What happened to my memories?",50); cout << "\n";FunctionDef.truenarrator("4) You're lying. You're hiding behind those trees aren't you?",50); 
			cout << "\n\n\033[33m>>    ";
			diadec2 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec2=="1"){
				FunctionDef.MCSC(mc, "Why are you in me?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Good question.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," All I can remember is my death,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," and now,", 125);FunctionDef.narratorclean(vc," I find myself here,", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc," in your body.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) What do you mean your death?", 50); cout << "\n";FunctionDef.truenarrator("2) Hold on, you're dead?",50); cout << "\n";FunctionDef.truenarrator("3) Is this a dream?",50); cout << "\n";FunctionDef.truenarrator("4) Huh?",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"What do you mean your death?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("This has to be a nightmare.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Well,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we don't really have a choice,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," stand up and look around.", 80 ); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Stand up before someone,", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," or worse,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," something finds us.", 100); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nigthmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000);
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="2"){
					FunctionDef.MCSC(mc,"Hold on, you're dead?", 70); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Affirmative, it does seem that way.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Well,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we don't really have time and a choice,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," stand up and look around.", 80 ); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Stand up before someone,", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," or worse,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," something finds us.", 100); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nightmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000);
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="3"){
					FunctionDef.MCSC(mc,"That's not possible!", 70);FunctionDef.narratorclean(mc," Am I dreaming?", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I understand the difficulty of comprehending a situation like this,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," however,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," dream or not,", 100); FunctionDef.skip(250);
					cout << "\n";
					FunctionDef.narrator("we have to move. So, I would advise you to get up before someone,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," or worse,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," something,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," finds us.", 80 );
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) This is insane.",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"This is insane.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," I don't understand.", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But I'll comply.", 80 ); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("I'll explain what I know once we get out of here.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
				else if(diadec3=="4"){
					FunctionDef.MCSC(mc,"Huh?", 70); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I understand if comprehending it is beyond your current capabilities,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," however,", 100); FunctionDef.skip(250); 
					cout << "\n";
					FunctionDef.narrator("we have to move. So, I would advise you to get up before someone,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," or worse,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," something,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," finds us.", 80 );
					cout << "\n";
					FunctionDef.narrator("Meanwhile, I will try to explain what I meant by \"death\" and we'll try to figure out why I am in your mind", 80);
					cout << "\n";
					FunctionDef.narrator("and why you don't remember anything.", 80);
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"Is this a nightmare?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
						FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000); cout << "\n";
						FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
					}
				}
			}
			else if(diadec2=="2"){
				FunctionDef.MCSC(mc, "How is that possible?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I don't know.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," But what I do know,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," is,", 125);FunctionDef.narratorclean(vc," that we should get out of here,", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("we don't want anyone or anything to find us, do we now?", 80); FunctionDef.skip(1000);FunctionDef.narratorclean(vc," I'll tell you the answers on the way out of here,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("just get up and move,", 80); FunctionDef.skip(200);FunctionDef.narratorclean(vc, " please.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) Is this a nightmare?",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="2"){
					FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="3"){
					FunctionDef.MCSC(mc,"Is this a nigthmare?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Oh, come on.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," No, this is not a nightmare.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Or maybe it is, but it doesn't matter.", 80); FunctionDef.skip(200); cout << "\n";
					FunctionDef.narrator("Dying in a dream sucks as well.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," So please, just stand up and we'll figure it out together.", 80); FunctionDef.skip(1000); cout << "\n";
					FunctionDef.MCS("Okay, I'll comply.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec3=="4"){
					FunctionDef.MCSC(mc,"Okay, we should get going.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Great, let's go that way.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," It looks like there might be something there.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			if(diadec2=="3"){
				FunctionDef.MCSC(mc, "But where are my memories?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," You just came here into my mind, and all of them are gone.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " What have you done to them?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I haven't done anything to your memories.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," I know nothing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," same as you.", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Do you think I want to be here?", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("I somehow died and now I am here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " in your body,", 100);FunctionDef.narratorclean(vc, " which I can't control.", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("But,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," here we are,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," so move your ass and get up.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) I don't trust you.",50); cout << "\n";FunctionDef.truenarrator("3) This has to be a nightmare.",50); cout << "\n";FunctionDef.truenarrator("4) Okay, we should get going.",50); 	
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc,"Why should I listen to you?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Does it look like you have a choice? What else do you want to do?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="2"){
					FunctionDef.MCSC(mc,"I don't trust you.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("You don't have to trust me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Just get up and move your ass before something kills us both.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fine.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec3=="3"){
					FunctionDef.MCSC(mc,"This has to be a nightmare!...", 80);FunctionDef.narratorclean(mc, "URGHHHH!", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("We have no choice,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," we must cooperate,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," unless you want to die.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Okay, let's go.", 50); cout << "\n";FunctionDef.truenarrator("2) Wait, why would I die?",50); cout << "\n";FunctionDef.truenarrator("3) No! I want to go my own way.",50); cout << "\n";FunctionDef.truenarrator("4) I'm not moving unless you tell me who you are.",50); 	
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,4); 
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc,"Okay, let's go.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Great.", 75);FunctionDef.narratorclean(vc," Time to move this way.", 75); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="2"){
						FunctionDef.MCSC(mc,"Wait, why would I die?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Because you will be alone in this world,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " without memories,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " forgotten to everyone,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and an easy target for enemies.", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("We're not alone in this forest.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I can help you get out of here safely.", 75); FunctionDef.skip(1000); 
						cout << "\n";
						FunctionDef.MCS("Why is this happening to me?", 75); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("I know you're scared and frustrated.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But trust me,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," the only way for both of us to survive is to get up and move.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("I guess I have no choice...", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," Fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," I'll cooperate.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Okay, great. Let's go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
					if(diadec4=="3"){
						FunctionDef.MCSC(mc,"No! I want to go my own way.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 75); FunctionDef.skip(1500);
						// endingplaceholder1();
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"I'm not moving unless you tell me who you are.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Fine, fine.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," I'll tell you...", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," My name is Void.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I was the general of a faction", 75); cout << "\n";FunctionDef.narrator("called Terragnis.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," We were in a war against another faction called Slofridi.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I was in a battle,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("an arrow hit me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," somehow,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I didn't die.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Suddenly,", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator(" a bright light flashed before it was followed by darkness.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I came to my senses, I found myself in someone else's body...", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("in your body.", 75); FunctionDef.skip(400);FunctionDef.narratorclean(vc," And now,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," we're here.", 100); FunctionDef.skip(1500);
						cout << "\n";
						FunctionDef.MCS("So, you died and woke up in my head.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("To put it shortly, yes.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("But, how is that possible?", 80); FunctionDef.skip(1000); 
						cout << "\n";
						FunctionDef.narrator("I told you everything I know.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," I would like to know more too,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but we will find out nothing if we just sit here.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCS("You have a point,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," let's get out of here.", 75); FunctionDef.skip(1500);	relwvoid = 3;
						earlyexplanation = true;	
					}
				}
			}
			else if(diadec2=="4"){
				FunctionDef.MCSC(mc, "You're lying.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You're hiding behind those trees, aren't you?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("I am not one lie to lie.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Only when it is an utter necessity.", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("You should get up and move your ass before you get us both killed by someone or something.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Alright, let's get going.", 50); cout << "\n";FunctionDef.truenarrator("2) I will need a further explanation in order to comply.",50); cout << "\n";FunctionDef.truenarrator("3) I don't understand, how is this possible?",50); cout << "\n";FunctionDef.truenarrator("4) I'm not buying that. You are trying to lure me out.",50);
				cout << "\n\n\033[33m>>    ";
				diadec3 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec3=="1"){
					FunctionDef.MCSC(mc, "Alright,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " let's get going.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Okay, great.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Let's go that way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it seems like there might be something there.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				else if(diadec3=="2"){
					FunctionDef.MCSC(mc, "I will need a further explanation in order to comply.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I told you,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " I don't know.", 80);FunctionDef.narratorclean(vc, " All I know is that I am stuck here in your mind and that you're gonna get us", 80); cout << "\n";FunctionDef.narrator("killed if you don't move,",80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " so please,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " move,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and I'll tell you more when we're on the move.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Why should I listen to you?", 50); cout << "\n";FunctionDef.truenarrator("2) Nope, still don't trust you. I refuse to believe this.", 50); cout << "\n";FunctionDef.truenarrator("3) Alright, I'll move", 50);
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,3);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Why should I listen to you?", 80); FunctionDef.skip(1000);
						FunctionDef.narrator("You don't have a choice.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Or maybe you do,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " do whatever you want,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you want to die?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Fine, then.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) I'll go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) Okay, I'm sorry. I'll do what you want now.", 50);
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,4);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "I'll go my own way.", 50); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
							// endingplaceholder1();
						}
						else{
							FunctionDef.MCSC(mc, "Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I'll do what you want now.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("At last.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Well,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " no time to lose,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " get up and go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
						}
					}
					else if(diadec4=="2"){
						FunctionDef.MCSC(mc, "Nope,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " still don't trust you.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I refuse to believe this.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("So,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you want to die here then?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go your own way then.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) I'll be on my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) You know what, fine, I'll listen to you for now.", 50);
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,2);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "I'll be on my own way.", 50); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80);
							// endingplaceholder1();
						}
						else{
							FunctionDef.MCSC(mc, "You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " fine,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll listen to you for now.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("Finally...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We can move.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Stand up,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and let's go this way.", 80); FunctionDef.skip(1500); relwvoid = 1;
						}
					}
					else{
						FunctionDef.MCSC(mc, "Alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll move.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Good,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " alright,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we should 	go that way.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
				else if(diadec3=="3"){
					FunctionDef.MCSC(mc, "I don't understand, how is this possible?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I don't understand either.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We can figure it out together,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " just,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " please,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " move.", 100); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Okay, I'm sorry, I'll move.", 50); cout << "\n";FunctionDef.truenarrator("2) How about, no?", 50);
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll move.", 90); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It's okay", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " let's go that way.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I can see something sticking out, there might be something there.", 80); FunctionDef.skip(1000); relwvoid = 3;
					}
					else{
						FunctionDef.MCSC(mc, "How about,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " no?", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Are you sure you want me as your enemy?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Remember,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I am inside your mind,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " and I can make this", 80); cout << "\n";FunctionDef.narrator("a living hell for you.", 80); FunctionDef.skip(1000);
						cout << endl << "\n";FunctionDef.truenarrator("1) Yes, I want to go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) I changed my mind, I'm sorry, I'll listen to you.", 50); 
						cout << "\n\n\033[33m>>    ";
						diadec5 = FunctionDef.GVIclean(1,2);
						cout << "\033[0m";
						if(diadec5=="1"){
							FunctionDef.MCSC(mc, "Yes, I want to go my own way.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80); FunctionDef.skip(1500);
							// endingplaceholder1();
						}
						else{
							FunctionDef.MCSC(mc, "I changed my mind,",80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'm sorry,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll listen to you.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("At last,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "let's go that way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'll try to explain what I know.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " If we want to live together", 80); cout << "\n";FunctionDef.narrator("in peace,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we have to cooperate.", 80); FunctionDef.skip(1500); relwvoid = 2;
						}
					}
				}
				else{
					FunctionDef.MCSC(mc, "I'm not buying that.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You are trying to lure me out.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Okay, seriously?", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Listen,", 80);FunctionDef.narratorclean(vc," you don't have a choice,", 80);FunctionDef.narratorclean(vc," move,",100);FunctionDef.narratorclean(vc," you have nothing to lose.", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("1) Stop talking to me, I want to go my own way.", 50); cout << "\n";FunctionDef.truenarrator("2) Fine.", 50); cout << "\n";FunctionDef.truenarrator("3) I'm sorry, I was just  making sure. We can move now.", 50); 
					cout << "\n\n\033[33m>>    ";
					diadec4 = FunctionDef.GVIclean(1,3);
					cout << "\033[0m";
					if(diadec4=="1"){
						FunctionDef.MCSC(mc, "Stop talking to me,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I want to go my own way.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You know what, fine, go your own way, we'll see how that goes.", 80); FunctionDef.skip(1500);
						// endingplaceholder1();
					}
					else if(diadec4=="2"){
						FunctionDef.MCSC(mc, "Fine.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("This attitude is insane,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " show some respect to the inhabitant of your mind.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Look around a little,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("there looks to be something that way.", 80); FunctionDef.skip(1500); relwvoid = 1;
					}
					else{
						FunctionDef.MCSC(mc, "I'm sorry,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I was just making sure.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " We can move now.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It is alright,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Let's go now.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " That way seems to lead somewhere.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
			}
			cout << "\n";
			cout << "\n";
			d1();
			while(true){
				if(a>0 || b>0) d1();
				cout << endl << "\n";
				FunctionDef.flushInput();
				cout << "\033[33m>>    ";
				decision1 = FunctionDef.GVIclean(1,5);
				cout << "\033[0m";
				if(decision1=="1"){
					FunctionDef.MCSC(mc, "I want to see the trees.", 80);
					cout << endl << "\n";
					d1n();
					if(!isAlive){
						system("cls");
						sequence1();
						break;
					}
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="2"){
					FunctionDef.MCSC(mc, "I want to see those trees.", 80);
					cout << endl << "\n";
					d1n();
					if(!isAlive){
						system("cls");
						sequence1();
						break;
					}
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="3"){
					FunctionDef.MCSC(mc, "I must see these trees.", 80);
					cout << endl << "\n";
					d1n();
					if(!isAlive){
						system("cls");
						sequence1();
						break;
					}
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;		
				}
				else if(decision1=="4"){
					FunctionDef.MCSC(mc, "I would like to see where this path leads.", 80);
					cout << endl << "\n";
					FunctionDef.truenarrator("Okay, you decide you want to see the destination of this path. Are you sure you don't want to check\n      the abandoned place where your stuff might lay out first?", 50);
					cout << endl << "\n";
					FunctionDef.skip(250);
					FunctionDef.truenarrator("1) Go through with your initial decision\n      2) Abort", 50);
					cout << endl << "\n";
					FunctionDef.flushInput();
					cout << "\033[33m>>    ";
					decision1sub1 = FunctionDef.GVI(1,2);
					cout << "\033[0m";
					if(decision1sub1=="1"){
						FunctionDef.MCSC(mc, "I really want to know where it leads.", 80);
						cout << endl << "\n";
						FunctionDef.truenarrator("Very well, you decide to embark on an adventurous journe- nevermind, you die. Reason: UNKN0WN", 50);
						FunctionDef.skip(400);
						cout << endl << endl << "\n";
						lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence();
					}
					else if(decision1sub1=="2"){
						FunctionDef.MCSC(mc, "I think we should check that strange abandoned place first.", 80);
						cout << endl << "\n";
						FunctionDef.truenarrator("At last, you decide to check the strange place with abandoned stuff out. You see the following:",50); cout << "\n\n";FunctionDef.truenarrator("- Tea",50); cout << "\n";FunctionDef.truenarrator("- An iron sword",50); cout << "\n";FunctionDef.truenarrator("- Golden armor with a low durability",50); cout << "\n";FunctionDef.truenarrator("- A shield",50); cout << "\n";FunctionDef.truenarrator("- Elixir of Love",50); cout << "\n";FunctionDef.truenarrator("- A stick",50); cout << "\n";FunctionDef.truenarrator("- Bandage x3",50); cout << "\n";FunctionDef.truenarrator("- A small backpack", 50);
						break;
					}
				}
				else if(decision1=="5"){
					FunctionDef.MCSC(mc, "I would like to check the strange abandoned place out first.", 80);
					cout << endl << "\n";
					FunctionDef.truenarrator("Great choice, better than \"trees\" atleast, you near the abandoned things and find the following:",50); cout << "\n\n";FunctionDef.truenarrator("- Tea",50); cout << "\n";FunctionDef.truenarrator("- An iron sword",50); cout << "\n";FunctionDef.truenarrator("- Golden armor with a low durability",50); cout << "\n";FunctionDef.truenarrator("- A shield",50); cout << "\n";FunctionDef.truenarrator("- Elixir of Love",50); cout << "\n";FunctionDef.truenarrator("- A stick",50); cout << "\n";FunctionDef.truenarrator("- Bandage x3",50); cout << "\n";FunctionDef.truenarrator("- A small backpack", 50); break;
				}
			}
			cout << endl << "\n"; diadec1 = ""; diadec2 = ""; diadec3 = ""; diadec4 = ""; diadec5 = "";
			if(a==3&&(relwvoid==1||relwvoid==2)) b0 = "1";
			else if(a==3&&(relwvoid==3||relwvoid==4)) b0 = "2";
			else if(a<2&&(relwvoid==1||relwvoid==2)) b0 = "3";
			else if(a<2&&(relwvoid==3)) b0 = "4";
			else if(a<2&&relwvoid==4) b0 = "5";
			else if(a==2&&(relwvoid==1||relwvoid==2)) b0 = "6";
			else if(a==2&&(relwvoid==3||relwvoid==4)) b0 = "7";
			else if(earlyexplanation==true&&a<2) b0 = "8";
			else if(earlyexplanation==true&&a>1) b0 = "9";
			if(b0=="1"){
				FunctionDef.narrator("Not only are you an asshole right away,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," you're also dumb.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Why would you choose the trees three times?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I don't want to hear it,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " stop wasting our time and grab the things and get the hell out of here.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Sorry, I really wanted to see the trees.", 50); cout << "\n";FunctionDef.truenarrator("2) I'm an asshole? You're an asshole!", 50); cout << endl << "\n"; 
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Sorry, I really wanted to see the trees.", 80); FunctionDef.skip(500);
					cout << "\n";
					FunctionDef.narrator("Save it,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab the things and GO!", 80); FunctionDef.skip(1000); 
					cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500); cout << "\n";
				}
				else{
					FunctionDef.MCSC(mc, "I'm an asshole?!", 75); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " You're an asshole!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " You're the one who invaded my mind.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Me?!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go to hell,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I told you I don't know whath appened and how I got here.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Stop it and get the things before we die here.", 80); FunctionDef.skip(1000);
					cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500); cout << endl << "\n";
				}
				FunctionDef.narrator("I'm really trying to be nice here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but you're not letting me.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " What do you suggest we do now?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Do we take the path this way?", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("1) Take the path in Void's desired direction.", 80); cout << "\n";FunctionDef.truenarrator("2) Go the opposite way.", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				b1pathdec = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(b1pathdec=="1"){
					FunctionDef.MCSC(mc, "Fine, let's go your way.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Atleast you listen.", 80); FunctionDef.skip(1000); relwvoid = 2;
				}
				else{
					FunctionDef.MCSC(mc, "You know what?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "I don't like listening to you.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "I prefer if we went this way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " we can't lose anything.", 80); 
					cout << "\n";
					FunctionDef.narrator("You know what,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " go wherever the hell you want.", 80); FunctionDef.skip(1000); relwvoid = 1; d="7";
				}
			}
			else if(b0=="2"){
				FunctionDef.narrator("Why would you choose trees three times?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Are you", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "-", 200);FunctionDef.narratorclean(vc, " I'm sorry.", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " You choosing trees 3 times frustrated me.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("There was clearly nothing there,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we wasted our time.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should probably get going,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab the things and go.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("I'm sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Let's take the path we saw before.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n"; 
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " that path should lead us someplace we can find answers.", 80); FunctionDef.skip(1000);
			}
			else if(b0=="3"){
				FunctionDef.narrator("Grab that and go.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Also,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " what's up with you?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Quit acting this way,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it's better if we get along.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";FunctionDef.truenarrator("1) I'm sorry about that...", 50); cout << "\n";FunctionDef.truenarrator("2) ...", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";			 
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "I'm sorry about that...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " I didn't mean what I said before,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I was just being careful.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.MCS("But I see that you're not a bad guy and that you are actually in my mind now.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("It's okay,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Thank you for the apology.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should move,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " let's take the path we saw earlier.", 80); FunctionDef.skip(1000);
					relwvoid = 3;
				}
				else{
					FunctionDef.MCSC(mc, "...", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I-", 150); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I know it must be hard from your perspective.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Looking at it from your shoes,", 80);FunctionDef.narratorclean(vc, " I wouldn't trust myself either.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("I understand,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'm sorry.", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Thank you,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I should be the one sorry.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " But you're right,", 80);FunctionDef.narratorclean(mc, " we should move and talk about this later.", 80); FunctionDef.skip(1000); 
					relwvoid = 3;
				}
			}
			else if(b0=="4"){
				FunctionDef.narrator("Great.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," These things will come in handy.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Grab them and let's go.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";
				FunctionDef.MCS("Good idea,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " let's follow that path we saw earlier,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " perhaps it leads into a town.",80); FunctionDef.skip(400); FunctionDef.narratorclean("\033[33m", " Can't be a path from nowhere to nowhere,", 80);FunctionDef.narratorclean("\033[33m", " right?", 100); FunctionDef.skip(1000);
			}
			else if(b0=="5"){
				FunctionDef.narrator("Amazing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we got really lucky.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " We should continue moving and get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " right after you grab these things.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << endl << "\n";FunctionDef.MCS("Okay,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " we should get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " you're right,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " perhaps we should take that path we saw earlier,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.MCS("it could lead somewhere.", 80); FunctionDef.skip(1000);			
				cout << "\n";
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it will lead somewhere,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " it has to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " don't worry.", 80); FunctionDef.skip(1000);
			}
			else if(b0=="6"){
				FunctionDef.narrator("Can you stop choosing the trees and grab the things and get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " asshole?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Fine,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " I'll grab the things.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.MCS("Now what?", 80); FunctionDef.skip(1000);
				FunctionDef.narrator("We get out of here,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " using that path.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Go and don't talk.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " I'm becoming allergic to you speaking and we only", 80); cout << "\n";FunctionDef.narrator("met 3 minutes ago.", 80); FunctionDef.skip(1000);			
			}
			else if(b0=="7"){
				FunctionDef.narrator("Good,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we're getting somewhere.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " But why did you choose the trees twice?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " It is kind of confusing,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " but whatever,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("we should continue moving,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we could take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.MCS("Got them.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " We should take the path we saw earlier.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " It might lead somewhere.", 80); FunctionDef.skip(1000);					
				cout << "\n";
				FunctionDef.narrator("It should lead somewhere,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I assume a village.", 80); FunctionDef.skip(1000);		
			}	
			else if(b0=="8"){
				FunctionDef.narrator("Great,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " grab those,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " they will be very useful.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we should continue moving,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("we could take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Okay.", 100); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.narrator("Good,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " you can walk now,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " try to be stealthy,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " we don't know what might be here with us.", 80); FunctionDef.skip(1000);			
			}
			else if(b0=="9"){
				FunctionDef.narrator("Why would you pick the trees frist?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Such a waste of time.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Let's just grab these and let's keep moving.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Sorry about that,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " yes.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " let's keep moving after I grab those.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " We should take that path we saw earlier.", 80); FunctionDef.skip(1000);
				cout << endl << "\n";FunctionDef.truenarrator("You grab the stuff and it can now be found in your inventory, which is the backpack.", 50); FunctionDef.skip(500);
				cout << "\n";FunctionDef.narrator("I suppose that is the only path and choice we have.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " It must lead to a village,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " I'm pretty positive.", 80); FunctionDef.skip(1000);			 
			}
			if(b0!="1"&&relwvoid!=1){
				cout << endl << "\n";FunctionDef.truenarrator("You are approached by a pack of wolves ready to attack you. You have to defend yourself.", 50); cout << "\n";FunctionDef.truenarrator("In a quick manner, you have to choose the action you take: ", 50); cout << endl << "\n";FunctionDef.truenarrator("1) Use a stick to fight them",50); FunctionDef.skip(200); cout << "\n";FunctionDef.truenarrator("2) Use an iron sword to fight them", 50); cout << "\n";FunctionDef.truenarrator("3) Try to distract them with the stick instead of fighting.", 50); cout << endl << "\n";
				cout << "\033[33m>>    ";
				decision2 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(decision2=="1"){
					FunctionDef.truenarrator("You decide to take out the stick and use it to fight the wolves off. Commencing combat.", 50); FunctionDef.skip(200);
					UlozitInfo("Stick", "CurrentWeapon.txt"); ambush("Wolves"); 
				}
				else if(decision2=="2"){
					FunctionDef.truenarrator("You decide to take out the iron sword and use it to fight the wolves off. Commencing combat.", 50); FunctionDef.skip(200);
					UlozitInfo("IronSword", "CurrentWeapon.txt"); ambush("Wolves"); 
				}
				else if(decision2=="3"){
					int wolfescapechance = rand()%4;
					if(wolfescapechance==1){
						FunctionDef.truenarrator("You attempt to distract the wolves using a stick. You throw it and the wolves indeed do get distracted.", 50); // Achievement, 25% chance to work 
					}
					else{
						FunctionDef.truenarrator("You try to distract the wolves with the stick, but they fail to notice it and devour you.", 50); FunctionDef.skip(400); cout << "\n";
						deathsequence();
					}
				}
			}
			if((b0=="1"||b0=="6")&&decision2=="3") c="1";
			else if((b0!="1"&&b0!="6")&&decision2=="3") c="2";
			else if((b0=="1"||b0=="6")&&decision2=="1") c="3";
			else if((b0!="1"&&b0!="6")&&decision2=="1") c="4";
			else if((b0=="1"||b0=="6")&&decision2=="2") c="5";
			else if((b0!="1"&&b0!="6")&&decision2=="2") c="6";
			if(c=="1"){
				FunctionDef.narrator("Are you crazy?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You could have gotten us killed.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You are lucky that worked.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("You should continue walking on this path.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("It was a good idea,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " we could have died fighting.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It distracted them and we are safe now.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("I'll continue walking now.", 80); FunctionDef.skip(1000);
			}
			else if(c=="2"){
				FunctionDef.narrator("Woah.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Good idea with that stick,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I didn't expect it would work.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I didn't think it would work either,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but I am glad it did.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's keep on going.", 80); FunctionDef.skip(1000);
			}
			else if(c=="3"){
				FunctionDef.narrator("Why would you use the stick on the wolves?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We're lucky that we're still alive.", 80); FunctionDef.skip(1000);
				cout << "\n"; 
				FunctionDef.MCS("It was a decision I had to make on the spot.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It might have been rash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but we won the fight.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's continue moving.", 80); FunctionDef.skip(1000); 
			}
			else if(c=="4"){
				FunctionDef.narrator("Okay...?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Good job,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you've got some skill with that stick.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Why didn't you use the sword though?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I don't know.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " The stick was the first thing I got a hold of,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " so I used it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " But it doesn't matter.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We won,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " so let's move.", 80); FunctionDef.skip(1000);
			}
			else if(c=="5"){
				FunctionDef.narrator("Atleast you're decent at fighting with a sword.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Continue moving forward.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Thanks for the appreciation I guess...", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " You haven't been very useful to me,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " you know?", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("But that's probably not your fault.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's keep moving.", 80); FunctionDef.skip(400);
			}
			else if(c=="6"){
				FunctionDef.narrator("Amazing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you did great!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should continue before we are met by another pack of wolves.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I'm sure there is a lot of them around here.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Thank you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " and I agree.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Let's continue on our way.", 80); FunctionDef.skip(1000);		
			}
			sequence2(language);
		}
		else{
			// sem to isté vloz si sem svoje veci petko okrem funkcie
		}
	}
	void sequence2(string language){
		if(lang=="en"){
			if(sequence==1) sequence++; save(); system("cls"); Sleep(1000);
			diadec1 = ""; diadec2 = ""; diadec3 = "";
			cout << "\n\n\n\n\n\n        {[()]} Sequence 2 {[()]}\n\n\n"; Sleep(1000);FunctionDef.truenarrator("  You're doing great!(not)", 50); Sleep(2000); system("cls"); Sleep(2500);
			cout << "\n";
			FunctionDef.truenarrator("You walk through a captivating meadow, full of birds, dead bodies and charred weapons.", 50); FunctionDef.skip(1000);
			cout << endl << "\n";
			if(earlyexplanation==true) d = "5";
			else if(relwvoid==1) d = "1";
			else if(relwvoid==2) d = "2";
			else if(relwvoid==3) d = "3";
			else if(relwvoid==4) d = "4"; 
			else if(relwvoid==5) d = "5";
			/*if(d==1)
			else if(d==2)
			else if(d==3)
			else */if(d=="4"){
				FunctionDef.MCS("What happened here?", 100); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.narrator("A minor clash, it seems.", 80); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("It reminds me of the field where they got me.", 75); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.MCS("Woah,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " that's crazy.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Wait,", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " got you?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " What do you meanb by that?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " When will you finally tell me who you are?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Okay then.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was a general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We found ourselves in a confrontation with an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We were figthing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then I got hit by an arrow.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("It was followed by a bright flash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all I saw was darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I woke up in your body.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("That's all I know.", 80); FunctionDef.skip(1000);
				cout << endl << "\n"; FunctionDef.truenarrator("1) What?? So you really are dead.", 50); cout << "\n"; FunctionDef.truenarrator("2) That's all you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) Wow, I'm sorry that happened to you.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
			}
			// else if(d==5)
		}
		else{
			// sem to iste xd
		}
	}
};
int main() {
	Functions FunctionsDef;
	Game GameDef;
	srand(time(0));

	GameDef.ExistujeSave = GameDef.CheckSave();
	if (GameDef.ExistujeSave) {
		GameDef.load();
		if(GameDef.playerName!=""&&(GameDef.mode!="speedrun"&&GameDef.mode!=""))	GameDef.savesequence();
		else GameDef.introsequence(GameDef.lang);
	}
	else {
		GameDef.save();
		GameDef.picklanguage();
	}

	return 0;
}
