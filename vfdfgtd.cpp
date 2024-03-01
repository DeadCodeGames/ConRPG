#define _WIN32_WINNT 0x0500
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <clocale>
#include <cmath>
#include "CONFunctions.h"

using namespace std;class Game {
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
	void checkLevelUp(string language){
		if(xp>=requiredxp){
			initiallvl = level;
			hp = currenthp;
			while(xp>=requiredxp){
				hp += hp/10;
				level += 1;
				xp -= requiredxp;
				requiredxp += requiredxp/5;
			} 
		if(language=="en"){
			cout << "\n      Leveled up! Went from lvl " << initiallvl << " to lvl " << level << ". HP: " << currenthp << " -> " << hp << "\n";
			cout << "      Current xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << "\n";
		}
		else{
			cout << "\n      Zv��ila sa it �rove� " << initiallvl << " na �rove� " << level << ". HP: " << currenthp << " -> " << hp << "\n";
			cout << "      Moment�lne xp ->" << xp << "(" << xp << "/" << requiredxp << ")" << "\n";
		}
	}
	save();
	}
	void statreset(){
		playerName="", mode="", fightstatus="", input="", tb="", decision1="", decision1sub1="", b1pathdec="", decision2="", diadec1="", diadec2="", diadec3="", diadec4="", diadec5="", hp=20, level=0, xp=0, currenthp=20;
	}
	void deathsequence(string language){
		if(language=="en"){
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
				  		if(sequence==1) sequence1(lang);
				  		else if(sequence==2) sequence2(lang);
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
		else{
			system("cls");
			cout << "\n\n"; FunctionDef.truenarrator("Ups...", 50); FunctionDef.skip(200); FunctionDef.TNC(" Vypad� to trochu tak, �e niekto pri�iel o jeden �ivot.", 50); FunctionDef.skip(200); cout << "\n";
			if(lives!=0){
				FunctionDef.truenarrator("\tNemus� sa ale b�, odv�ny cestovate�!", 50); FunctionDef.skip(200); FunctionDef.TNC(" Smr� je sk�senos� a sk�senos� je �ivot.", 50); FunctionDef.skip(200); 
				if(lives==2) FunctionDef.TNC("Ost�vaju ti " + to_string(lives) + " �ivoty", 50);
				else if(lives==1) FunctionDef.TNC("Ost�va ti 1 �ivot.", 50);
				else{
					FunctionDef.TNC("M� nekonecno �ivotov.", 50);
				}
				cout << "\n"; FunctionDef.skip(250);
				FunctionDef.truenarrator("\t[Stlac F na o�ivenie, L na zacatie novej hry.]", 50);
				while(true){
					if(_kbhit()){
				  	char key = _getch();
				  	if(key=='f'){
				  		if(sequence==1) sequence1(lang);
				  		else if(sequence==2) sequence2(lang);
						}
						else{
							statreset();
							picklanguage();
						}
					}
				}
			}
			else{
				FunctionDef.truenarrator("\tA bol to tvoj posledn� �ivot...", 50); FunctionDef.skip(250); FunctionDef.TNC(" Je mi ��to �e sa ti toto stalo.", 50); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.truenarrator("\t[Stlac L na zacatie novej hry.]", 50); 
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
		if(language=="en"){
			cout << endl << "      "; FunctionDef.truenarrator("Prepare to fight...", 50); Sleep(500);
		}
		else if(language=="sk"){
			cout << endl << "      "; FunctionDef.truenarrator("Priprav sa na boj...", 50); Sleep(500);
		}
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
		    deathsequence(lang);
			}
			else{
	      FunctionDef.truenarrator("You finished the fight.", 50); cout << "\n";
	    }
		}
		else{
	if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		else {
			cout << "Chyba pri spusten� programu." << endl;
		}
		ifstream inputFile("testsave.txt");
	  if (!inputFile.is_open()) {
	    cerr << "Chyba pri otvoren� s�boru na nac�tanie �dajov." << endl;
	    return 1;
	  }
	  inputFile >> fightstatus;
	  inputFile >> xpgained;
	  if(fightstatus=="1"){
	  	FunctionDef.truenarrator("Preru�il si s�boj... Automaticky umiera�.", 50); cout << "\n"; FunctionDef.skip(250); FunctionDef.truenarrator("[Stlac F pre nac�tanie poslednej ulo�enej poz�cie alebo stlac L pre nac�tanie novej hry.]",50);
			while(true){
      	if(_kbhit()){
      		char c = _getch();
      		if(c=='f') sequence1(lang);
					else if(c=='f') introsequence(lang);
				}
			}
		}
		else{
      			FunctionDef.truenarrator("Dokoncil si s�boj.", 50); cout << "\n";
		}
		Sleep(3000);
		xp+=xpgained;
		checkLevelUp(lang);
		Sleep(2000);
	}
	}
	void endingplaceholder1(string language){
		if(language=="en"){
			cout << "\n\n";
			FunctionDef.truenarrator("You went your own way. You will never know what happened next.", 50); FunctionDef.skip(250); cout << "\n\n";
			FunctionDef.truenarrator("\tEnding: You went your own path", 50);
		}
		else{
			cout << "\n\n";
			FunctionDef.truenarrator("I�iel si vlastnout cestou. Nikdy sa nedozvie� co sa stalo.", 50); FunctionDef.skip(250); cout << "\n\n";
			FunctionDef.truenarrator("Koniec: Vlastn� cesta", 50);
		}
	}
	void d1n(string language) {
		if(language=="en"){
			if (a == 0) FunctionDef.truenarrator("\t  Trees, interesting choice. You come closer to the trees but you don't find anything.", 50);
			if (a == 1) FunctionDef.truenarrator("\t  For real? You visit the trees again, and... you don't find anything.", 50);
			if (a == 2) FunctionDef.truenarrator("\t  There is something weird about those trees. They're... trees.", 50);
			if (a > 2) {
				FunctionDef.truenarrator("\t  You visit the trees once more. Once again, you find nothin-", 50); cout << "\n";
				FunctionDef.truenarrator("\t  w- what's that sound? It seems like... you have awakened something. It's angry.", 75); cout << "\n"; FunctionDef.skip(300);
				FunctionDef.truenarrator("\t  Behold Mozz, the tree [BOSS] [10M HP] You stand no chance against this beast as it one hits you", 50); cout << "\n";
				FunctionDef.truenarrator("\t  before the fight even has a chance to begin.", 50); FunctionDef.skip(400); cout << "\n"; FunctionDef.skip(400); system("cls"); cout << "\n\n\n\n";
				FunctionDef.truenarrator("\t  \033[1;31mYou get the tree picker ending.\033[0m", 50); cout << "\n"; FunctionDef.skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
				lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
			}
		}
		else{
			if (a == 0) FunctionDef.truenarrator("\t  Stromy, zauj�mav� vo�ba. I�iel si bli��ie ku stromom, ale nic si nena�iel.", 50);
			if (a == 1) FunctionDef.truenarrator("\t  V�ne? Pri�iel si znova ku stromom, a... znova si nic nena�iel.", 50);
			if (a == 2) FunctionDef.truenarrator("\t  Nieco je divn� na t�ch stromoch. S� ako... stromy.", 50);
			if (a > 2) {
				FunctionDef.truenarrator("\t  I�iel si k stromom e�teb raz.A op� si nic nena�ie-", 50); cout << "\n";
				FunctionDef.truenarrator("\t  C- co to je za zvuk? Vyzer� to tak... �e si nieco zobudil. A je to na�tvan�.", 75); cout << "\n"; FunctionDef.skip(300);
				FunctionDef.truenarrator("\t  Axir, The Lord of the Forbidden Forest [BOSS] [10M HP] Nem� �ancu proti tomuto mon�tru zv�azi�, ke�e �a zabije", 50); cout << "\n";
				FunctionDef.truenarrator("\t  e�te predt�m, ne� m� s�boj v�bec �ancu zaca�.", 50); FunctionDef.skip(400); cout << "\n"; FunctionDef.skip(400); system("cls"); cout << "\n\n\n\n";
				FunctionDef.truenarrator("\t  \033[1;31mZ�skal si koniec Zberac Stromov.\033[0m", 50); cout << "\n"; FunctionDef.skip(400); cout << "\n\n\n\n\n\n\n\n\n\n";
				lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
			}
		}
	}

	// Decisions

	void d1(string language) {
		if(language=="en"){
			FunctionDef.truenarrator("You look around you. You see the following:", 50);
			cout << "\n";
			FunctionDef.truenarrator("1) Trees", 50); cout << "\n"; FunctionDef.truenarrator("2) Trees", 50); cout << "\n"; FunctionDef.truenarrator("3) Trees", 50); cout << "\n"; FunctionDef.truenarrator("4) A path", 50); cout << "\n"; FunctionDef.truenarrator("5) A strange place between the trees, where abandoned stuff can be seen.", 50); FunctionDef.skip(500); cout << "\n\n"; FunctionDef.truenarrator("What do you choose?", 50);
			cout << "\n";
		}
		else{
			FunctionDef.truenarrator("Poobzer� sa okolo seba a vid�:", 50);
			cout << "\n";
			FunctionDef.truenarrator("1) Stromy", 50); cout << "\n"; FunctionDef.truenarrator("2) Stromy", 50); cout << "\n"; FunctionDef.truenarrator("3) Stromy", 50); cout << "\n"; FunctionDef.truenarrator("4) Cestu", 50); cout << "\n"; FunctionDef.truenarrator("5) Divn� miesto medzi stromami, kde m��e� vidie� pohoden� veci.", 50); FunctionDef.skip(500); cout << "\n\n"; FunctionDef.truenarrator("What do you choose?", 50);
			cout << "\n";
		}
	}

	// Sequences
	void savesequence(string language) {
		if(language=="en"){
			FunctionDef.truenarrator("\tWelcome back, " + playerName, 50); FunctionDef.skip(250); cout << "\n";
			FunctionDef.truenarrator("\tDo you wish to load the latest save or start a new game? [F to Load, L to start over]", 50);
		}
		else{
			FunctionDef.truenarrator("\tVitaj sp�, " + playerName, 50); FunctionDef.skip(250); cout << "\n";
			FunctionDef.truenarrator("\tChce� nac�ta� posledn� ulo�en� poz�ciu alebo zaca� nov� hru? [F pre nac�tanie poz�cie, L pre nov� hru]", 50);
		}
		while (true) {
			if (_kbhit()) {
				char keypressed = _getch();
				if (keypressed == 'f') {
					saveload = 1;
					if (sequence == 1) sequence1(lang);
					else if (sequence == 2) sequence2(lang);
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
				system("cls");
		level = 0; hp = 20; xp = 0; currenthp = 20; maxdmg = 1;
		cout << "                                            V I T A J    V" << endl;
	 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
		cout << endl << "                                           The C++ Console RPG";
		cout << endl << "                                         Stlac [coko�vek] a zacni hru"; 
		_getch();
		cout << "\n";FunctionDef.truenarrator("Zdrav�m �a cestovate�!", 100); FunctionDef.skip(1000); cout << "\n";
		FunctionDef.truenarrator("...", 500); FunctionDef.skip(1000); cout << "\n";
		FunctionDef.truenarrator("Asi sa nevol� cestovate�, �e", 80); FunctionDef.skip(1500); cout << "\n";
		FunctionDef.truenarrator("Ako sa vol�?", 80); FunctionDef.skip(1000); cout << endl << "      [NAP͊ SVOJE MENO]" << endl;
		FunctionDef.flushInput();
		cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
		if (!playerName.empty()) {
			FunctionDef.truenarrator("R�d �a spozn�vam, "+playerName+"!", 100);
		} else {
			FunctionDef.truenarrator("Ty...", 500); FunctionDef.TNC(" ty nem� meno?", 125); FunctionDef.skip(500); FunctionDef.TNC(" Isto m� nejak� meno. D�m ti �ancu ho e�te zada�..", 80); cout << "\n"; 
			FunctionDef.flushInput();
			cout << ">>    "; getline(cin, input); FunctionDef.skip(1000); playerName = input; save();
			if (!playerName.empty()) {
			FunctionDef.truenarrator("V�borne, r�d �a spozn�vam, "+playerName+"!", 80);
		} else {
			FunctionDef.truenarrator("V�ne nem� meno?", 125); cout << "\n"; FunctionDef.skip(1000);
			FunctionDef.truenarrator("To je", 225); FunctionDef.TNC("...", 500); FunctionDef.skip(500); FunctionDef.TNC(" smutn�. Je mi �a ��to.", 200); cout << "\n"; FunctionDef.skip(750);
			FunctionDef.truenarrator("Ale aj tak �a nejako potrebujem vola�.", 80); cout << "\n"; FunctionDef.skip(500);
			FunctionDef.truenarrator("M��em �a vola� Cestovate�?", 75); FunctionDef.skip(500); FunctionDef.TNC(" Mysl�m, �e to budem fajn.", 75); playerName = "Cestovate�"; save();
		}
	} 
				FunctionDef.skip(1000); cout << "\n";
			FunctionDef.truenarrator("Na akej obtia�nosti si praje� hra� hru, drah� cestovate�?", 80); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<1> �AHK�", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<2> NORM�LNA", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<3> �A�K�", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("<4> TURBO", 50);
			mode = FunctionDef.GVIclean(1,4);
			if(mode=="1") mode = "easy";
			else if(mode=="2") mode = "normal";
			else if(mode=="3") mode = "hard";
			else if(mode=="4") mode = "speedrun";
			UlozitInfo(mode, "Mode.txt");
			system("cls");
			if(mode=="easy"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tJednoduch� obtia�nos�...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tM� neobmedzen� pocet o�iven�.", 50); 
				Sleep(2000); lives = -1;
			}
			else if(mode=="normal"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tNorm�lna obtia�nos�...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tM� k dispoz�cii 3 o�ivenia.", 50); 
				Sleep(2000); lives = 3;
			}
			else if(mode=="hard"){
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\t��k� obtia�nos�...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tM� k dispoz�cii jedno o�ivenie.", 50); 
				Sleep(2000); lives = 1;
			}
			else{
				cout << "\n\n\n\n\n\n"; FunctionDef.truenarrator("\t\tSpeedrun mode...", 100); FunctionDef.skip(250);
				cout << "\n\n"; FunctionDef.truenarrator("\t\tM� jedno o�ivenie a hra sa neuklad�. Tvoja cesta bude ma� t� spr�vnu r�chlos�.", 50); 
				Sleep(2000); lives = 1;
			}
			UlozitInfo(to_string(lives), "Lives.txt");
			sequence=0;
			sequence1(language);
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
						endingplaceholder1(lang);
					}
					if(diadec4=="4"){
						FunctionDef.MCSC(mc,"I'm not moving unless you tell me who you are.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Fine, fine.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," I'll tell you...", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," My name is Void.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I was the general of a faction", 75); cout << "\n";FunctionDef.narrator("called Terragnis.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," We were in a war against another faction called Slofridi.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I was in a battle,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("an arrow hit me.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," But,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," somehow,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," I didn't die.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Suddenly,", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("a bright light flashed before it was followed by darkness.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," When I came to my senses, I found myself in someone else's body...", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("in your body.", 75); FunctionDef.skip(400);FunctionDef.narratorclean(vc," And now,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," we're here.", 100); FunctionDef.skip(1500);
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
							endingplaceholder1(lang);
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
							endingplaceholder1(lang);
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
							endingplaceholder1(lang);
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
						endingplaceholder1(lang);
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
			d1(lang);
			while(true){
				if(a>0 || b>0) d1(lang);
				cout << endl << "\n";
				FunctionDef.flushInput();
				cout << "\033[33m>>    ";
				decision1 = FunctionDef.GVIclean(1,5);
				cout << "\033[0m";
				if(decision1=="1"){
					FunctionDef.MCSC(mc, "I want to see the trees.", 80);
					cout << endl << "\n";
					d1n(lang);
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="2"){
					FunctionDef.MCSC(mc, "I want to see those trees.", 80);
					cout << endl << "\n";
					d1n(lang);
					FunctionDef.skip(500);
					cout << endl << "\n";
					a++;
					continue;
				}
				else if(decision1=="3"){
					FunctionDef.MCSC(mc, "I must see these trees.", 80);
					cout << endl << "\n";
					d1n(lang);
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
						lives--; UlozitInfo(to_string(lives), "Lives.txt"); deathsequence(lang);
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
					UlozitInfo("Stick", "CurrentWeapon.txt"); ambush("Wolves", lang); 
				}
				else if(decision2=="2"){
					FunctionDef.truenarrator("You decide to take out the iron sword and use it to fight the wolves off. Commencing combat.", 50); FunctionDef.skip(200);
					UlozitInfo("IronSword", "CurrentWeapon.txt"); ambush("Wolves", lang); 
				}
				else if(decision2=="3"){
					int wolfescapechance = rand()%4;
					if(wolfescapechance==1){
						FunctionDef.truenarrator("You attempt to distract the wolves using a stick. You throw it and the wolves indeed do get distracted.", 50); // Achievement, 25% chance to work 
					}
					else{
						FunctionDef.truenarrator("You try to distract the wolves with the stick, but they fail to notice it and devour you.", 50); FunctionDef.skip(400); cout << "\n";
						deathsequence(lang);
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
		if(saveload==1){
				cout << "\n\n\n"; FunctionDef.truenarrator("\tVitaj sp� cestovate�. Ch�bal si n�m. M��e� pokracova� "+mode+ " na svojej ceste.", 50); Sleep(2500);
				system("cls");
			}
			if(sequence==0) sequence++;
			save();
			Sleep(500);
		cout << "\n\n\n\n\n\n\t\t{[()]} Akt 1 {[()]}\n\n\n"; Sleep(500);
		FunctionDef.truenarrator("\t\tHra automaticky uklad� ka�d� akt. Ve�a ��astia na cest�ch.", 50);
		Sleep(2000); system("cls");
		Sleep(2500);
		FunctionDef.MCS("Kde to som?", 80);FunctionDef.narratorclean(mc," Ako som sa sem dostal?",80); FunctionDef.skip(1000);
		cout << "\n";
		FunctionDef.MCS("V�ade okolo m�a je len hust� les.", 80); FunctionDef.skip(1000);
		cout << "\n";
		FunctionDef.MCS("Ja, ", 100);FunctionDef.narratorclean(mc,"...", 200); FunctionDef.skip(500);FunctionDef.narratorclean(mc," nic si nepam�t�m.", 80); FunctionDef.skip(1500);
		cout << "\n";
		FunctionDef.narrator("Co sa deje?! ", 80); FunctionDef.skip(600);FunctionDef.narratorclean(vc,"Preco nem��em ovl�da� svoje telo? ", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Pocka�, toto... ", 175); FunctionDef.skip(300);FunctionDef.narratorclean(vc,"Toto nie je moje telo!", 80);
		cout << "\n";
		FunctionDef.MCS("Kto to povedal? ", 40); FunctionDef.skip(750);
		cout << "\n";
		FunctionDef.MCS("Kde si? Uk� sa!", 75); FunctionDef.skip(1000);
		cout << "\n";
		FunctionDef.narrator("Nem��em sa uk�za�.", 80); FunctionDef.skip(1000); cout << "\n";
		FunctionDef.MCS("Ako to mysl� �e nem��e�?", 80); FunctionDef.skip(1000);
		cout << "\n";
		FunctionDef.narrator("S�m netu��m.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzer� to tak...", 120); FunctionDef.skip(400);FunctionDef.narratorclean(vc," �e som v tebe.", 100); FunctionDef.skip(750);
		cout << endl << endl;FunctionDef.truenarrator("1) Preco si vo mne?", 50); cout << "\n";FunctionDef.truenarrator("2) Ako je to mo�n�?",50); cout << "\n";FunctionDef.truenarrator("3) Co sa stalo s mojimi spomienkami?",50); cout << "\n";FunctionDef.truenarrator("4) Klame�!. Isto sa schov�va� niekde za t�mi stromami.",50); 
		cout << "\n\n\033[33m>>    ";
		diadec2 = FunctionDef.GVIclean(1,4);
		cout << "\033[0m";
		if(diadec2=="1"){
			FunctionDef.MCSC(mc, "Preco si vo mne?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("Dobr� ot�zka.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," V�etko co si pam�t�m, je moja smr�.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," a zrazu,", 125);FunctionDef.narratorclean(vc," som sa ocitol tu,", 100); FunctionDef.skip(500);FunctionDef.narratorclean(vc," v tvojom tele.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Co mysl� pod tvojou smr�ou?", 50); cout << "\n";FunctionDef.truenarrator("2) Pockaj, ty si m�tvy?",50); cout << "\n";FunctionDef.truenarrator("3) Toto je sen, �e?",50); cout << "\n";FunctionDef.truenarrator("4) Co?",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Co mysl� pod tvojou smr�ou?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Toto mus� by� nocn� mora.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Nu�,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nem�me moc na v�ber,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," postav sa a poobzeraj sa tu trochu.", 80 ); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("Medzit�m ti sk�sim vysvetli� co som myslel pod \"smr�ou\" a taktie� sk�sime zisti�, preco som v tvojej hlave ", 80);
				cout << "\n";
				FunctionDef.narrator("a preco si nic nepam�t�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Postav sa a po�me inde, sk�r ne� n�s niekto", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," alebo hor�ie,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," nieco n�jde.", 100); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mmal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nocn� mora,�e?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Mysl�, �e m� na v�ber? Co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� sa postav� a pohne� t�m svojim zadkom predt�m ne� n�s nieco n�jde a obidvoch n�s zabije.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nocn� mora,�e?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Ale no tak, vschop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasn�, �e toto nie je nocn� mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj ke� mo�no aj je, ale na tom nez�le��.", 80); FunctionDef.skip(200); cout << "\n";
					FunctionDef.narrator("Umiera� vo sne tie� stoj� za nic.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa pros�m �a postav a spolu na to pr�deme.", 80); FunctionDef.skip(1000);
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Oukej, mali by sme sa pohn��.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V�borne, po�me tadia�to.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzer� to tam s�ubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Pocka�, ty si m�tvy?", 70); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Potvrdzujem. Teda aspo� to tak vyzer�.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("No,", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nem�me zrovna cas na zbytocn� prem���ania,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," postav sa a poobzeraj sa.", 80 ); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("Medzit�m, ti sk�sim vysvetli� co som myslel pod \"smr�ou\" a taktie� sk�sime zisti�, preco som v tvojej hlave", 80);
				cout << "\n";
				FunctionDef.narrator("a preco si nic nepam�t�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Postav sa sk�r ne� n�s niekto", 100);FunctionDef.skip(200);FunctionDef.narratorclean(vc," alebo hor�ie,", 125); FunctionDef.skip(200);FunctionDef.narratorclean(vc," nieco n�jde.", 100); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nocn� mora, �e?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Mysl�, �e m� na v�ber? co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� sa pohne� s t�m svoj�m zadkom predt�m, ne� n�s nieco zabije.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nocn� mora, �e?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasn�, �e toto nie je nocn� mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj ke�, mo�no aj je, ale na tom nez�le��.", 80); FunctionDef.skip(200); cout << "\n";
					FunctionDef.narrator("Umieranie v sne tie� stoj� za nic.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa pros�m �a postav a spolu na to pr�deme.", 80); FunctionDef.skip(1000);
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohn��.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V�borne, po�me tadia�to.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Vyzer� to tam s�ubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="3"){
				FunctionDef.MCSC(mc,"To nie je mo�n�!", 70);FunctionDef.narratorclean(mc," Sn�vam?", 100); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Ch�pem, �e je �a�k� pochopi� tak�to situ�ciu,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," ale ka�dop�dne,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," ci u� sen alebo realita,", 100); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("mus�me sa pohn��. Tak�e by som ti navrhoval vsa� sk�r ne� n�s niekto", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," alebo hor�ie,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," nieco,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," n�jde.", 80 );
				cout << "\n";
				FunctionDef.narrator("Medzit�m, ti sk�sim vysvetli�, co som myslel pod \"smr�ou\" a taktie� sk�sime zisti�, preco som v tvojej hlave", 80);
				cout << "\n";
				FunctionDef.narrator("a preco si nic nepam�t�.", 80);
				cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) To je �ialenstvo.",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Mysl�, �e m� na v�ber? Co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� sa pohne� s t�m svoj�m zadkom predt�m, ne� n�s nieco zabije.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"To je �ialenstvo.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," Nerozumiem.", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale nem�m moc na v�ber. Tak�e ti vyhoviem.", 80 ); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Vysvetl�m ti v�etko, co viem, akon�hle sa odtia�to dostaneme.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohn��.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V�borne, po�me tadia�to.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzer� to tam s�ubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
			else if(diadec3=="4"){
				FunctionDef.MCSC(mc,"Co??", 70); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Ch�pem, �e to teraz asi nedok�e� pochopi�,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," ale ka�dop�dne,", 100); FunctionDef.skip(250); 
				cout << "\n";
				FunctionDef.narrator("mus�me sa pohn��. Tak�e by som ti radil vsta� a od�s� odtia�to sk�r ne� n�s niekto", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," alebo hor�ie,",80); FunctionDef.skip(300);FunctionDef.narratorclean(vc," nieco,", 80 ); FunctionDef.skip(250);FunctionDef.narratorclean(vc," n�jde.", 80 );
				cout << "\n";
				FunctionDef.narrator("Medzit�m, ti sk�sim vysvetli�, co som myslel pod \"death\" a taktie� sk�sime pr�s� na to, preco som v tvojej hlave", 80);
				cout << "\n";
				FunctionDef.narrator("a preco si nic nepam�t�.", 80);
				cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nocn� mora, �e?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 		
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Mysl�, �e m� na v�ber? Co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� pohne� s t�m svoj�m zadkom sk�r, ne� n�s nieco zabije.", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Toto je nocn� mora, �e?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasn�, �e toto nie je nocn� mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj ke� mo�no je, ale na tom nez�le��.", 80); FunctionDef.skip(200); cout << "\n";
					FunctionDef.narrator("Umiera� v sne tie� stoj� za dve veci.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa u� pros�m �a postav a spolu to nejako rozl�skneme.", 80); FunctionDef.skip(1000); cout << "\n";
					FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohn��.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V�borne, po�me tadia�to.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzer� to tam s�ubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
				}
			}
		}
		else if(diadec2=="2"){
			FunctionDef.MCSC(mc, "Ako je to mo�n�?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("Netu��m.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Ale co viem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," je to,", 125);FunctionDef.narratorclean(vc," �e by sme mali odtia�to vypadn��,", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("nechceme, aby n�s tu coko�vek na�lo, �e?", 80); FunctionDef.skip(1000);FunctionDef.narratorclean(vc," Odpovede ti d�m po ceste,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("proste sa postav a daj do pohybu,", 80); FunctionDef.skip(200);FunctionDef.narratorclean(vc, " pros�m.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto je nocn� mora, �e?",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 		
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Mysl�, �e m� na v�ber? Co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� pohne� s t�m svoj�m zadkom sk�r, ne� n�s nieco zabije.", 75); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="3"){
				FunctionDef.MCSC(mc,"Toto je nocn� mora, �e?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Ale no tak, vzchop sa.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Jasn�, �e toto nie je nocn� mora.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," Aj ke�, mo�no je, ale na tom nez�le��.", 80); FunctionDef.skip(200); cout << "\n";
				FunctionDef.narrator("Umiera� v sne tie� za moc nestoj�.", 80);  FunctionDef.skip(400);FunctionDef.narratorclean(vc," Tak sa u� pros�m �a postav a spolu to nejako rozl�skneme.", 80); FunctionDef.skip(1000); cout << "\n";
				FunctionDef.MCS("Dobre, vyhoviem ti.", 80); FunctionDef.skip(1500); relwvoid = 3;
			}
			if(diadec3=="4"){
				FunctionDef.MCSC(mc,"Dobre, mali by sme sa pohn��.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("V�borne, po�me tadia�to.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc,"Vyzer� to tam s�ubne.", 75); FunctionDef.skip(1500); relwvoid = 4;
			}
		}
		if(diadec2=="3"){
			FunctionDef.MCSC(mc, "Ale kde s� moje spomienky?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc," Len tak si sem pri�iel, a v�etky s� prec.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Co si snimi urobil?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("Ja som tvojim spomienkam nic neurobil.", 80); FunctionDef.skip(500);FunctionDef.narratorclean(vc," Nic o tom neviem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," rovnako ako ty.", 125); FunctionDef.skip(400);FunctionDef.narratorclean(vc," mysl�, �e tu chcem by�?", 100); FunctionDef.skip(500); cout << "\n";FunctionDef.narrator("Umrel som ani neviem ako a zrazu som v cudzom tele,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " v tvojom tele,", 100);FunctionDef.narratorclean(vc, " ktor� nem��em kontrolova�.", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("Ale,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," sme tam, kde sme,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," tak pohni s t�m svoj�m zadkom a postav sa.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Never�m ti.",50); cout << "\n";FunctionDef.truenarrator("3) Toto mus� by� nocn� mora.",50); cout << "\n";FunctionDef.truenarrator("4) Dobre, mali by sme sa pohn��.",50); 	
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc,"Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Mysl�, �e m� na v�ber? Co in� chce� robi�?", 75); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="2"){
				FunctionDef.MCSC(mc,"Never�m ti.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Nemus� mi veri�.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Stac�, ke� pohne� s t�m svoj�m zadkom sk�r, ne� n�s nieco zabije.", 75); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Fajn.", 100); FunctionDef.skip(1500); relwvoid = 2;
			}
			if(diadec3=="3"){
				FunctionDef.MCSC(mc,"Toto mus� by� nocn� mora!...", 80);FunctionDef.narratorclean(mc, "ARGHHHH!", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Nem�me na v�ber,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," mus�me spolupracova�,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc," jedine, �e by si chcel umrie�.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Dobre, tak po�me.", 50); cout << "\n";FunctionDef.truenarrator("2) Moment, preco by som mal umrie�?",50); cout << "\n";FunctionDef.truenarrator("3) Nie! Chcem �s� vlastnou cestou.",50); cout << "\n";FunctionDef.truenarrator("4) Nepohnem sa odtia�to, k�m mi nepovie�, kto si.",50); 	
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,4); 
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc,"Dobre, tak po�me.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V�borne.", 75);FunctionDef.narratorclean(vc," Vydajme sa t�mto smerom.", 75); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="2"){
					FunctionDef.MCSC(mc,"Pockaj, preco by som mal umrie�?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Preto�e bude� na tomto svete s�m,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " bez spomienok,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ukradtnut� ka�d�mu,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a �ahk� cie� pre nepriate�ov.", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("V tomto lese nie sme sami.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " A ja som ten, ktor� ti pom��e sa odtia�to bezpecne dosta�.", 75); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.MCS("Preco sa mi toto deje?", 75); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Viem, �e si vystra�en� a frustrovan�.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale ver mi,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," na�a jedin� �anca, ako pre�i�, je postavi� sa pohn�� sa odtia�to.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Vyzer� to tak, �e nem�m na v�ber...", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc," budem spolupracova�.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Super. Tak sa vydajme na cestu.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
				if(diadec4=="3"){
					FunctionDef.MCSC(mc,"Nie! Chcem �s� vlastnou cestou.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Vie� co, fajn, cho� si svojou cestou, uvid�me, kam n�s to zavedie.", 75); FunctionDef.skip(1500);
					// endingplaceholder1();
				}
				if(diadec4=="4"){
					FunctionDef.MCSC(mc,"Nepohnem sa odtia�to, k�m mi nepovie�, kto si.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Dobre, dobre.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," V�etko ti poviem...", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Vol�m sa Void.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Bol som gener�lom frakcie", 75); cout << "\n";FunctionDef.narrator("ktorej meno bolo Terragnis.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Boli sme vo vojne s inou frakciou, volali sa Slofridi.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Bol som uprostred boja,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("ke� ma zasiahol ��p.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ale,", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc," nejak�m z�zrakom,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," som neumrel.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Zrazu,", 100); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator(" som videl ostr� svetlo, po ktorom nasledovala tma.", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Ke� som pri�iel k vedomiu, na�iel som sa v cudzom tele...", 75); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("v tvojom tele.", 75); FunctionDef.skip(400);FunctionDef.narratorclean(vc," A teraz,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," sme tu.", 100); FunctionDef.skip(1500);
					cout << "\n";
					FunctionDef.MCS("Tak�e si umriel a zobudil sa v mojom tele.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("�no, v skratke.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("Ale ako je to mo�n�?", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Povedal som ti v�etko, co viem.", 80);  FunctionDef.skip(500);FunctionDef.narratorclean(vc," Tie� by som r�d vedel viac,", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale nic nezist�me, pokia� tu budeme len tak sedie�.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.MCS("M� pravdu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc," po�me odtia�to prec.", 75); FunctionDef.skip(1500);	relwvoid = 3;
					earlyexplanation = true;	
				}
			}
		}
		else if(diadec2=="4"){
			FunctionDef.MCSC(mc, "Klame�!", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Schov�va� sa za t�mi stromami, �e??", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.narrator("Nie som klam�r.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Iba vtedy, ke� je to fakt nevyhnutn�.", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("Ale zato ty by si sa mal pohn�� s t�m zadkom, inak kv�li tebe obidvaja umrieme.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Fajn, pohnime sa.", 50); cout << "\n";FunctionDef.truenarrator("2) Vyhoviem ti, ke� mi pod� lep�ie vysvetlenie.",50); cout << "\n";FunctionDef.truenarrator("3) Nech�pem, ako je to mo�n�?",50); cout << "\n";FunctionDef.truenarrator("4) Tak toto ti never�m. Iba sa ma sna�� vyl�ka� von.",50);
			cout << "\n\n\033[33m>>    ";
			diadec3 = FunctionDef.GVIclean(1,4);
			cout << "\033[0m";
			if(diadec3=="1"){
				FunctionDef.MCSC(mc, "Dobre,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, "tak sa dajme do pohybu.", 75); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Super.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Vydajme sa tadia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " vyzer� to tam s�ubne.", 80); FunctionDef.skip(1500); relwvoid = 3;
			}
			else if(diadec3=="2"){
				FunctionDef.MCSC(mc, "Vyhoviem ti, ke� mi pod� lep�ie vysvetlenie.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Povedal som ti,", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " fakt neviem.", 80);FunctionDef.narratorclean(vc, " Jedin� co viem je, �e som uv�znen� v tvojej hlave a �e n�s dostane� ", 80); cout << "\n";FunctionDef.narrator("do hrobu pokia� sa odtia�to nepohne�,",80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tak �a pros�m,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " pohni sa,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a poviem ti viac po ceste.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Preco by som �a mal poc�va�?", 50); cout << "\n";FunctionDef.truenarrator("2) Nie, st�le ti never�m. Odmietam tomuto v�etk�mu veri�.", 50); cout << "\n";FunctionDef.truenarrator("3) Fajn, tak sa teda d�m do pohybu", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,3);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Preco by som �a mal poc�va�?", 80); FunctionDef.skip(1000);
					FunctionDef.narrator("Nem� na v�ber.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Aj ke�, mo�no m�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " rob si co chce�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " chce� tak ve�mi umrie�?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Pros�m, v k�ude si cho�.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) P�jdem svojou vlastnou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Dobre, pockaj, ospravedl�ujem sa. Urob�m, co chce�.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,4);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "P�jdem svojou vlastnou cestou.", 50); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Vie� co, fajn, cho� kam chce�, uvid�me, kam sa dostane�.", 80);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prep�c.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Urob�m, co chce�.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Tak predsa len.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Nu�,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " nem�me casu nazvy�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " povsta� a vydaj sa tamtou cestou.", 80); FunctionDef.skip(1500); relwvoid = 3;
					}
				}
				else if(diadec4=="2"){
					FunctionDef.MCSC(mc, "Nie,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " st�le ti never�m.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Odmietam tomuto v�etk�mu veri�.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Aha,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tak�e tu chce� umrie�?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Pros�m,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " cho� kam chce�.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) P�jdem tam, kde chcem.", 50); cout << "\n";FunctionDef.truenarrator("2) Vie� co, fajn, poc�vnem �a.", 50);
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "P�jdem tam, kde chcem.", 50); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Vie� co, ako chce�, cho� svojou cestou. Aspo� uvid�me, kam to vedie.", 80);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Vie� co,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " fajn,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " poc�vnem �a.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Konecne...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " M��eme sa pohn��.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Postav sa,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a po�me touto cestou.", 80); FunctionDef.skip(1500); relwvoid = 1;
					}
				}
				else{
					FunctionDef.MCSC(mc, "Fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " d�m sa do pohybu.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " v poriadku,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mali by sme �s� tadia�to.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
			}
			else if(diadec3=="3"){
				FunctionDef.MCSC(mc, "Nerozumiem, ako je to mo�n�?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Tie� tomu nerozumiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " M��eme to spolu zisti�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " len sa u�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " pros�m �a,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " pohni.", 100); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Jasn�, prep�c, d�m sa do pohybu.", 50); cout << "\n";FunctionDef.truenarrator("2) Co ak nie?", 50);
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,2);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Jasn�,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prep�c,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " d�m sa do pohybu.", 90); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("V pohode", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " po�me tadia�to.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Zd� sa mi, �e tam nieco vid�m.", 80); FunctionDef.skip(1000); relwvoid = 3;
				}
				else{
					FunctionDef.MCSC(mc, "Co ak,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " nie?", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Fakt si chce� zo m�a urobi� nepriate�a?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Pam�taj,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " som v tvojej hlave,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " a kedyko�vek m��em pre teba z tohto urobi� ", 80); cout << "\n";FunctionDef.narrator("peklo na Zemi.", 80); FunctionDef.skip(1000);
					cout << endl << endl;FunctionDef.truenarrator("1) �no. A chcem �s� svojou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Zmenil som n�zor, prep�c, u� �a budem poc�va�.", 50); 
					cout << "\n\n\033[33m>>    ";
					diadec5 = FunctionDef.GVIclean(1,2);
					cout << "\033[0m";
					if(diadec5=="1"){
						FunctionDef.MCSC(mc, "�no. A chcem �s� svojou cestou.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Vie� co, rob si ako chce�, uvid�me, kam sa dostaneme.", 80); FunctionDef.skip(1500);
						// endingplaceholder1();
					}
					else{
						FunctionDef.MCSC(mc, "Zmenil som n�zor,",80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " prep�c,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " u� �a budem poc�va�.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Tak nakoniec predsa len,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "po�me tadia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Sk�sim ti vysvetli� v�etko, co viem.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Pokia� chceme spolu na��va�", 80); cout << "\n";FunctionDef.narrator("v mieri,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tak mus�me spolupracova�.", 80); FunctionDef.skip(1500); relwvoid = 2;
					}
				}
			}
			else{
				FunctionDef.MCSC(mc, "Na to ti neskoc�m.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Sna�� sa ma dosta� von.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("V�ne?", 75); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Poc�vaj,", 80);FunctionDef.narratorclean(vc," nem� na v�ber,", 80);FunctionDef.narratorclean(vc," pohni sa,",100);FunctionDef.narratorclean(vc," nem� co strati�.", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("1) Presta� na m�a hovori�, chcem �s� vlastnou cestou.", 50); cout << "\n";FunctionDef.truenarrator("2) Fajn.", 50); cout << "\n";FunctionDef.truenarrator("3) Prep�c, chcel som sa iba uisti�. M��eme �s�.", 50); 
				cout << "\n\n\033[33m>>    ";
				diadec4 = FunctionDef.GVIclean(1,3);
				cout << "\033[0m";
				if(diadec4=="1"){
					FunctionDef.MCSC(mc, "Presta� na m�a hovori�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " chcem �s� vlastnou cestou.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Vie� co, fajn, cho�, kadia� chce�, uvid�me, co z tohto vznikne.", 80); FunctionDef.skip(1500);
					// endingplaceholder1();
				}
				else if(diadec4=="2"){
					FunctionDef.MCSC(mc, "Fajn.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Tvoj postoj je otrasn�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mohol by si prejavi� aspo� trochu �cty tomu hlasu, co m� v hlave.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "Poobzeraj sa trochu,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("vyzer� to, �e tamt�m smerom nieco je.", 80); FunctionDef.skip(1500); relwvoid = 1;
				}
				else{
					FunctionDef.MCSC(mc, "Prep�c,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " chcel som sa len uisti�.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " M��eme sa da� do pohybu.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("To je v pohode,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Ch�pem �a.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " tak sa teda vydajme na cestu.", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Vyzer�, �e t�to cesta niekam vedie.", 80); FunctionDef.skip(1500); relwvoid = 3;
				}
			}
		}
		cout << "\n";
		cout << "\n";
		d1(lang);
		while(true){
			if(a>0 || b>0) d1(lang);
			cout << endl << endl;
			FunctionDef.flushInput();
			cout << "\033[33m>>    ";
			decision1 = FunctionDef.GVIclean(1,5);
			cout << "\033[0m";
			if(decision1=="1"){
				FunctionDef.MCSC(mc, "Chcem sa pozrie� na tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="2"){
				FunctionDef.MCSC(mc, "Chcem sa pozrie� na tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;
			}
			else if(decision1=="3"){
				FunctionDef.MCSC(mc, "Mus�m vidie� tie stromy.", 80);
				cout << endl << endl;
				d1n(lang);
				FunctionDef.skip(500);
				cout << endl << endl;
				a++;
				continue;		
			}
			else if(decision1=="4"){
				FunctionDef.MCSC(mc, "Chcel by som vedie�, kam vedie t�to cesta.", 80);
				cout << endl << endl;
				FunctionDef.truenarrator("Okej, rozhodol si sa zisti�, ak� je cie� tej cesty. Si si ist�, �e nechce� nask�r skontrolova�\n      to opusten� miesto medzi stromami, kde m��u le�a� u�itocn� veci?", 50);
				cout << endl << endl;
				FunctionDef.skip(250);
				FunctionDef.truenarrator("1) Pokracova� v p�vodnom rozhodnut� a �s� presk�ma� cestu\n      2) Upusti� od p�vodn�ho rozhodnutia a �s� presk�ma� opusten� miesto medzi stromami", 50);
				cout << endl << endl;
				FunctionDef.flushInput();
				cout << "\033[33m>>    ";
				decision1sub1 = FunctionDef.GVI(1,2);
				cout << "\033[0m";
				if(decision1sub1=="1"){
					FunctionDef.MCSC(mc, "Ve�mi chcem vedie�, kam to vedie.", 80);
					cout << endl << endl;
					FunctionDef.truenarrator("Nu� dobre, rozhodol si sa vyda� na dobrodr��nu cest- hups, tak nic, umrel si. D�vod: NEZN�MY", 50);
					FunctionDef.skip(400);
					lives--; deathsequence(lang);
				}
				else if(decision1sub1=="2"){
					FunctionDef.MCSC(mc, "Mysl�m, �e by sme mali najsk�r skontrolova� to opusten� miesto.", 80);
					cout << endl << endl;
					FunctionDef.truenarrator("Nakoniec si sa rozhodol skontrolova� to divn� miesto s opusten�mi vecami na zemi. A pred sebou m�:",50); cout << "\n\n";FunctionDef.truenarrator("- Caj",50); cout << "\n";FunctionDef.truenarrator("- �elezn� mec",50); cout << "\n";FunctionDef.truenarrator("- �ahko-znicite�n� zlat� brnenie",50); cout << "\n";FunctionDef.truenarrator("- �t�t",50); cout << "\n";FunctionDef.truenarrator("- Elix�r l�sky",50); cout << "\n";FunctionDef.truenarrator("- Palicu",50); cout << "\n";FunctionDef.truenarrator("- Obv�zy x3",50); cout << "\n";FunctionDef.truenarrator("- Mal� batoh", 50);
					break;
				}
			}
			else if(decision1=="5"){
				FunctionDef.MCSC(mc, "R�d by som najsk�r skontroloval to opusten� miesto medzi stromami.", 80);
				cout << endl << endl;
				FunctionDef.truenarrator("Skvel� vo�ba, teda minim�lne lep�ia ako \"stromy\", pribl�il si sa k opusten�m veciam a vid� nasledovn�:",50); cout << "\n\n";FunctionDef.truenarrator("- Caj",50); cout << "\n";FunctionDef.truenarrator("- �elezn� mec",50); cout << "\n";FunctionDef.truenarrator("- �ahko-znicite�n� zlat� brnenie",50); cout << "\n";FunctionDef.truenarrator("- �t�t",50); cout << "\n";FunctionDef.truenarrator("- Elix�r l�sky",50); cout << "\n";FunctionDef.truenarrator("- Palicu",50); cout << "\n";FunctionDef.truenarrator("- Obv�zy x3",50); cout << "\n";FunctionDef.truenarrator("- Mal� batoh", 50); break;
			}
		}
		cout << endl << endl; diadec1 = ""; diadec2 = ""; diadec3 = ""; diadec4 = ""; diadec5 = "";
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
			FunctionDef.narrator("Nielen, �e si �pln� kret�n,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc," ale e�te aj �plne hl�py.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Preco by si si vybral stromy 3-kr�t po sebe?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Vie� co,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " Rad�ej to ani nechcem pocu�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " presta� str�ca� n� cas, zober veci and vypadni odtia�to.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) Prep�c, fakt som chcel tie stromy.", 50); cout << "\n";FunctionDef.truenarrator("2) Ja som kret�n?! Ty si kret�n!", 50); cout << endl << endl; 
			cout << "\033[33m>>    ";
			diadec1 = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";
			if(diadec1=="1"){
				FunctionDef.MCSC(mc, "Prep�c, fakt som chcel tie stromy.", 80); FunctionDef.skip(500);
				cout << "\n";
				FunctionDef.narrator("Ulo� to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zober veci a CHO�!", 80); FunctionDef.skip(1000); 
				cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500); cout << "\n";
			}
			else{
				FunctionDef.MCSC(mc, "Ja som kret�n?!", 75); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Ty si kret�n!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Ty si ten, ktor�m sa mi vtrel do hlavy.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Ja?!", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Vie� co,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " cho� do certa,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " povedal som ti, co sa stalo a preco som tu.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Tak l�skavo presta�, zober veci a padaj prec odtia�to sk�r, ne� umrieme.", 80); FunctionDef.skip(1000);
				cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500); cout << endl << endl;
			}
			FunctionDef.narrator("Fakt sa sna��m by� mil�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale ty ma proste nenech�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Co navrhuje� teraz?", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("P�jdeme touto cestou?", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("1) �s� cestou, ktor� navrhol Void.", 80); cout << "\n";FunctionDef.truenarrator("2) �s� opacn�m smerom.", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			b1pathdec = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";
			if(b1pathdec=="1"){
				FunctionDef.MCSC(mc, "Fajn, po�me teda tvojou cestou.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Aspo� �e poc�va�.", 80); FunctionDef.skip(1000); relwvoid = 2;
			}
			else{
				FunctionDef.MCSC(mc, "Vie� co?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "nechce sa mi �a poc�va�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, "Rad�ej by som �iel tdia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " nem�me co strati�.", 80); 
				cout << "\n";
				FunctionDef.narrator("Vie� co,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " fajn,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " cho� do ktorejko�vek riti chce�.", 80); FunctionDef.skip(1000); relwvoid = 1; d="7";
			}
		}
		else if(b0=="2"){
			FunctionDef.narrator("Preco by si si vybral stromy 3-kr�t po sebe?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Nie si n�hodou", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, "-", 200);FunctionDef.narratorclean(vc, " Ospravedl�ujem sa.", 100); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Tvoj v�ber ma frustroval.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Je �plne jasn�, �e tam nic nie je,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " str�came n� cas.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme �s� �alej,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zobver veci a po�.", 80); FunctionDef.skip(1000);
			cout << "\n"; 
			FunctionDef.MCS("Prep�c.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Po�me t� cestu, co sme videli predt�m.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl; 
			FunctionDef.narrator("Pravda,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " t� cesta by n�s mohla zavies� niekde, kde m��eme n�js� odpovede.", 80); FunctionDef.skip(1000);
		}
		else if(b0=="3"){
			FunctionDef.narrator("Zober to a po�me.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " A inak,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " co je to s tebou?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Upusti od tak�chto rozhodnut�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " bude lep�ie, ke� sa dohodneme.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;FunctionDef.truenarrator("1) Ospravedl�ujem sa za to...", 50); cout << "\n";FunctionDef.truenarrator("2) ...", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			diadec1 = FunctionDef.GVIclean(1,2);
			cout << "\033[0m";			 
			if(diadec1=="1"){
				FunctionDef.MCSC(mc, "Ospravedl�ujem sa za to...", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Nemyslel som to tak,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " bol som iba opatrn�.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.MCS("But Ale aspo� u� vid�m, �e nie si zl� a �e si naozaj v mojej hlave.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("V poriadku,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " rozumiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Cen�m si tvoje ospravedlnenie.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme sa da� do pohybu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " po�me tou cestou, ktor� sme videli predt�m.", 80); FunctionDef.skip(1000);
				relwvoid = 3;
			}
			else{
				FunctionDef.MCSC(mc, "...", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Ja-", 150); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ch�pem, �e to mus� by� z tvojho poh�adu �a�k�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Ke� sa na to pozer�m z tvojej perspekt�vy,", 80);FunctionDef.narratorclean(vc, " tie� by som sebe neveril.", 80); FunctionDef.skip(400); cout << "\n";FunctionDef.narrator("Ch�pem �a,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " prep�c.", 100); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("�akujem,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " ale ja som ten, ktor� by sa tu mal ospravedl�ova�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Ale m� pravdu,", 80);FunctionDef.narratorclean(mc, " mali by sme sa da� do pohybu a o tomto sa porozpr�vame nesk�r.", 80); FunctionDef.skip(1000); 
				relwvoid = 3;
			}
		}
		else if(b0=="4"){
			FunctionDef.narrator("V�borne.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc," Tie veci m��u by� pre n�s u�itocn�.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Zober ich a po�me �alej.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;
			FunctionDef.MCS("Dobr� n�pad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " nasledujme t� cestu, ktor� sme videli predt�m,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " h�dam, �e vedie do mesta.",80); FunctionDef.skip(400); FunctionDef.narratorclean("\033[33m", " Nem��e predsa vies� odnikia� nikam,", 80);FunctionDef.narratorclean("\033[33m", " �e?", 100); FunctionDef.skip(1000);
		}
		else if(b0=="5"){
			FunctionDef.narrator("U�asn�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mali sme riadne ��astie.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mali by sme pokracova� v pohybe a dosta� sa odtia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " hne� ako zoberie� tie veci.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << endl << endl;FunctionDef.MCS("S�hlas�m,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " mali by sme sa odtia�to spakova�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " m� pravdu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " asi by sme mohli �s� tou cestou, ktor� sme videli predt�m,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.MCS("isto niekam vedie.", 80); FunctionDef.skip(1000);			
			cout << "\n";
			FunctionDef.narrator("Presne,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " niekam vedie,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " mus�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " neboj sa.", 80); FunctionDef.skip(1000);
		}
		else if(b0=="6"){
			FunctionDef.narrator("M��e� sa presta� tak extr�mne zauj�ma� o stromy, zobra� tie veci a vypadn�� odtia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " trkvas?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("Dobre, dobre,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " zoberiem tie veci.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << "\n";
			FunctionDef.MCS("A co teraz?", 80); FunctionDef.skip(1000);
			FunctionDef.narrator("Vypadneme odtia�to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " tamtou cestou.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Cho� a nic nehovor.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Tvoja rec ma zac�na iritova�", 80); cout << "\n";FunctionDef.narrator("a to sme sa spoznali len 3 min�ty dozadu.", 80); FunctionDef.skip(1000);			
		}
		else if(b0=="7"){
			FunctionDef.narrator("Super,", 100); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " niekam sa dost�vame.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Ale preco si si 2-kr�t vybral stromy?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Pr�de mi to dos� m�t�ce,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " ale co u�,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("mali by sme pojracova� �alej,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " m��eme �s� tou cestou, ktor� sme videli predt�m.", 80); FunctionDef.skip(1000);
			cout << "\n";
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << "\n";
			FunctionDef.MCS("M�m ich.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Vydajme sa teda tamtou cestou.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Mo�no niekam vedie.", 80); FunctionDef.skip(1000);					
			cout << "\n";
			FunctionDef.narrator("Mala by niekam vies�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " predpoklad�m, �e do dediny.", 80); FunctionDef.skip(1000);		
		}	
		else if(b0=="8"){
			FunctionDef.narrator("V�borne,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " zober ich,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " m��u by� u�itocn�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " A hne� potom,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " by sme sa mali da� do pohybu,", 80); FunctionDef.skip(250); cout << "\n";FunctionDef.narrator("m��eme �s� tou cestou, ktor� sme videli predt�m.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("Dobre.", 100); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << "\n";
			FunctionDef.narrator("Super,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " m��e� sa da� do pohybu,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " sk�s by� nen�padn�,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " nikdy nevieme, kto tu s nami m��e by�.", 80); FunctionDef.skip(1000);			
		}
		else if(b0=="9"){
			FunctionDef.narrator("Preco by si i�iel 2-kr�t k stromom?", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Absol�tna strata casu.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Proste iba zober tie veci a daj sa do pohybu.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("Ospravedl�ujem sa za to,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " ale s�hlas�m.", 100); FunctionDef.skip(250);FunctionDef.narratorclean(mc, " Pohnem sa, hne� ako to zoberiem.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(mc, " Mali by sme �s� tou cestou, ktor� sme videli predt�m.", 80); FunctionDef.skip(1000);
			cout << endl << endl;FunctionDef.truenarrator("Zobral si veci a odteraz ho m��e� n�js� vo svojom invent�ri, ktor�m je batoh.", 50); FunctionDef.skip(500);
			cout << "\n";FunctionDef.narrator("Mysl�m, �e je to na�a jedin� mo�nos�.", 80); FunctionDef.skip(400);FunctionDef.narratorclean(vc, " Mus� vies� do dediny,", 80); FunctionDef.skip(250);FunctionDef.narratorclean(vc, " na sto percent.", 80); FunctionDef.skip(1000);			 
		}
		if(b0!="1"&&relwvoid!=1){
			cout << endl << endl;FunctionDef.truenarrator("Si obk��cen� svorkou vlkov, ktor� je prepraven� na teba za�toci�. Mus� sa br�ni�.", 50); cout << "\n";FunctionDef.truenarrator("Mus� sa r�chlo rozhodn��, co urob�: ", 50); cout << endl << endl;FunctionDef.truenarrator("1) POu�i� palicu a bojova� s nimi",50); FunctionDef.skip(200); cout << "\n";FunctionDef.truenarrator("2) Pou�i� mec a bojova� s nimi", 50); cout << "\n";FunctionDef.truenarrator("3) Sk�si� ich odl�ka� palicou namiesto bojovania.", 50); cout << endl << endl;
			cout << "\033[33m>>    ";
			decision2 = FunctionDef.GVI(1,3);
			cout << "\033[0m" << endl;
			if(decision2=="1"){
				FunctionDef.truenarrator("Rozhodol si sa zobra� palicu a s �ou sa vrhn�� do boja. Zah�jujem s�boj.", 50); FunctionDef.skip(200);
				ambush("Wolves", lang); 
			}
			else if(decision2=="2"){
				FunctionDef.truenarrator("Rozhodol si sa zobra� mec a s n�m sa vrhn�� do boja. Zah�jujem s�boj.", 50); FunctionDef.skip(200);
				ambush("Wolves", lang); 
			}
			else if(decision2=="3"){
				int wolfescapechance = rand()%4;
				if(wolfescapechance==1){
					FunctionDef.truenarrator("Sk�sil si vlkov odl�ka� palicou. Hodil  si ho a podarilo sa ti ich odl�ka�.", 50); // Achievement, 25% chance to work 
				}
				else{
					FunctionDef.truenarrator("Sk�sil si vlkov odl�ka� palicou, ale v�bec nezareagovali a roztrhali �a ka k�sky.", 50); FunctionDef.skip(400); cout << "\n";
					lives--; deathsequence(lang);
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
			FunctionDef.narrator("Zbl�znil si sa?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Mohol si n�s zabi�.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " M� ��astie, �e to vy�lo.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("No nic, pokracujme �alej po ceste.", 80); FunctionDef.skip(1000);
			cout << "\n"; 
			FunctionDef.MCS("Bol to dobr� n�pad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " v boji by sme mohli umrie�.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Odl�kal som ich a teraz sme v bezpec�.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("Idem teda �alej.", 80); FunctionDef.skip(1000);
		}
		else if(c=="2"){
			FunctionDef.narrator("Wau!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " To s tou palicou bol dobr� n�pad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " necakal som, �e to bude fungova�.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("Tie� som si nemyslel, �e to m��e fungova�,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " ale som r�d, �e to vy�lo.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Nezastavujme a po�me �alej.", 80); FunctionDef.skip(1000);
		}
		else if(c=="3"){
			FunctionDef.narrator("Preco by si pou��val na vlkov palicu?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " M�me ��astie, �e sme st�le na�ive.", 80); FunctionDef.skip(1000);
			cout << "\n"; 
			FunctionDef.MCS("Bolo to ve�mi spont�nne rozhodnutie.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Mo�no to bolo ub�hlen�,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " ale ka�dop�dne sme vyhrali.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Pokracujme �alej.", 80); FunctionDef.skip(1000); 
		}
		else if(c=="4"){
			FunctionDef.narrator("Zauj�mav�...?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Dobr� pr�ca,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " ocividne vie�, ako pou��va� palicu.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Ale preco si namiesto toho nepou�il mec?", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("Netu��m.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Zobral som prv� vec, co mi pri�la do rany a n�hodou to bola zrovna palica,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " tak som ju pou�il.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Ale na to nez�le��.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Vyhrali sme,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " tak sa dajme to pohybu.", 80); FunctionDef.skip(1000);
		}
		else if(c=="5"){
			FunctionDef.narrator("Aspo� �e vie� bojova� s mecom.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Pokracuj smerom vpred.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("�akujem za uznanie, asi...", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Zatia� si mi nebol ve�mi n�pomocn�,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " vie� o tom?", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("Ale to asi nie je tvoja chyba.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Pokracujme �alej.", 80); FunctionDef.skip(400);
		}
		else if(c=="6"){
			FunctionDef.narrator("ڞasn�,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " bol si super!", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Mali by sme sa pohn�� �alej sk�r, ne� sem pr�de �al�ia svorka.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("Som si ist�, �e je ich tu ve�a.", 80); FunctionDef.skip(1000);
			cout << "\n";
			FunctionDef.MCS("�akujem,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " a s�hlas�m.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Po�me teda �alej.", 80); FunctionDef.skip(1000);		
		}
		sequence2(language);
		}
	}
	void sequence2(string language){
		if(lang=="en"){
			if(sequence==1) sequence++; 
			save(); system("cls"); Sleep(1000);
			diadec1 = ""; diadec2 = ""; diadec3 = "";
			cout << "\n\n\n\n\n\n        {[()]} Sequence 2 {[()]}\n\n\n"; Sleep(1000);FunctionDef.truenarrator("  You're doing great!(not)", 50); Sleep(2000); system("cls"); Sleep(2500);
			cout << "\n";
			FunctionDef.truenarrator("You walk through a captivating meadow, full of birds, dead bodies and charred weapons.", 50); FunctionDef.skip(1000);
			cout << "\n\n";
			if(earlyexplanation==true) d = "5";
			else if(relwvoid==1) d = "1";
			else if(relwvoid==2) d = "2";
			else if(relwvoid==3) d = "3";
			else if(relwvoid==4) d = "4"; 
			else if(relwvoid==5) d = "5";
			if(d=="1"){
				FunctionDef.MCS("What the hell happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Seems like more people couldn't take your mere existence.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " A clash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " from the looks of it.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) Shut up already.", 50); cout << "\n"; FunctionDef.truenarrator("2) I'm sorry about before.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,2);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Oh, why don't you shut up already and tell me what is going on and who you are now?", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Why don't you shut up,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " huh?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Can we not get a moment of peace here between us,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " huh?", 100); FunctionDef.skip(400); cout <<"\n"; FunctionDef.narrator("I want to tell you shit,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but you are being a complete,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " utter,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " asshole.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You want to know shit?", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("Then you better give me one hell of an apology for this behavior.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am not willing to be stuck in the body of a bastard who can't trust me.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'm sorry.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I want to be nice,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you're not letting me.", 80); FunctionDef.skip(1000);
					cout << "\n\n"; FunctionDef.truenarrator("1) No. Get the hell out of my mind.", 50); cout << "\n"; FunctionDef.truenarrator("2) ...", 50); cout << "\n"; FunctionDef.truenarrator("3) I'm sorry. I am really sorry about before.", 80); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, "No.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Get the hell out of my mind.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You want me,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " me to get out of your mind?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You realize who I am?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We're not gonna get along,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " are we?", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("You're gonna get us killed.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " You,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " go to hell.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " If you won't listen to me,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I will make the little time you have hellish.", 80); FunctionDef.skip(1000); 
					}
					if(diadec2=="2"){
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator(" You're not gonna say anything?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "Fine.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I'm not saying anything either.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Are we gonna stay here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " do nothing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, "say nothing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " forever?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "We're gonna die here.", 80); FunctionDef.skip(1000);
						cout << "\n\n"; FunctionDef.truenarrator("1) ...", 50); cout << "\n"; FunctionDef.truenarrator("2) You are right. We need to get out of here.", 50); cout << "\n";
						cout << "\033[33m>>    ";
						diadec3 = FunctionDef.GVI(1,2);
						cout << "\033[0m" << "\n";
						if(diadec3=="1"){
							FunctionDef.MCSC(mc, "...", 100); FunctionDef.skip(1000);
							FunctionDef.truenarrator("You don't say anything and you stay there until midnight.", 50); FunctionDef.skip(200); FunctionDef.TNC(" The unnamed inhabitant of your mind remains quiet as well.", 50); FunctionDef.skip(200); cout << "\n"; FunctionDef.truenarrator("After a while, you fall asleep on the field.", 50); FunctionDef.skip(200); FunctionDef.TNC("You never wake up... Reason of death: Unavailable.", 50); FunctionDef.skip(1000);
							cout << "\n"; 
							FunctionDef.truenarrator("ENDING: Asleep on the field.", 50); Sleep(2000);
							lives--;
							deathsequence(lang);
						}
						else{
							FunctionDef.MCSC(mc, "You are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We need to get out of here.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("Then go,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " get the hell out of here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " asshole.", 80); FunctionDef.skip(1000);
						}
					}
					else{
						FunctionDef.MCSC(mc, "I'm sorry.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I am really sorry about before.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I didn't want to be an asshole but at first I was so confused and scared,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I didn't trust you,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator(" but I suppose that doesn't excuse the behavior.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I am really sorry,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I want to survive and you are right,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " it's better if we get along.", 80); FunctionDef.skip(1000);
						cout << "\n"; 
						FunctionDef.narrator("Thank you for the heartfelt apology.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am glad that we can finally get along a little.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I'll tell you what I know now.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was the general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " In that battle,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I got hit by an arrow and...", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("died,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I suppose.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I saw a bright flash of light after the arrow hit me and then it was followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I do not recall anything else.", 80); FunctionDef.skip(1000);
						cout << "\n\n"; FunctionDef.truenarrator("1) We should get out of here first and then have a talk about it.", 50); cout << "\n"; FunctionDef.truenarrator("2) Wow, I am so sorry that happened to you.", 50); cout << "\n";
						cout << "\033[33m>>    ";
						diadec3 = FunctionDef.GVI(1,2);
						cout << "\033[0m" << "\n";
						if(diadec3=="1"){
							FunctionDef.MCSC(mc, " I think we should get out of here first and then talk about it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " It seems dangerous here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " we can figure it out,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " together,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("when we get to safety,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " okay?", 100); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("You are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's go.", 80); FunctionDef.skip(1000);
						}
						else{
							FunctionDef.MCSC(mc, "Wow,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I am so sorry that happened to you.", 80); FunctionDef.skip(1000);
							cout << "\n";
							FunctionDef.narrator("It's okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Thank you for finally coming to your senses and apologizing.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It's better now that we get along.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We should continue moving and get into safety and then try to figure things out.", 80); FunctionDef.skip(1000);
						}
						relwvoid = 3;
					}
				}
				else{
					FunctionDef.MCSC(mc, "Okay.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I'm sorry about before.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("I didn't mean to act like that,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I'm sorry.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I'm sorry I didn't trust you.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Can you please at least tell me who you are now?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("It's... okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I will tell you now,", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " thank you for the apology.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am the general,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("well,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I was the general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " In that battle,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I got hit by an arrow and...", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("died,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I suppose.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I saw a bright flash of light after the arrow hit me and then it was followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And then,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("I woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(1000);
					relwvoid = 3;
					cout << "\n\n"; FunctionDef.truenarrator("1) Okay, I see. We should keep moving and talk about this later.", 50); cout << "\n"; FunctionDef.truenarrator("2) Is that everything?", 50); cout << "\n"; FunctionDef.truenarrator("3) I am sorry about that. About you dying and about what happened.", 50); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, " Okay,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I see.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Interesting and sad,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " but I think we should keep on moving and talk about all this later,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narratorclean(mc, " once we're safer.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("You are right,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we have to keep moving and then we can try and figure it out,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " once we are safe.", 80); FunctionDef.skip(1000);
					}
					else if(diadec2=="2"){
						FunctionDef.MCSC(mc, "Is that everything?", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " that is everything I know,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'm afraid.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "We should keep moving until we find a safe spot,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " a village or a settlement perhaps.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We will have to figure the rest out there.", 80); FunctionDef.skip(1000);
					}
					else{
						FunctionDef.MCSC(mc, "I am sorry about that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " About you dying and about what happened.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("It's okay.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to keep moving if we want to survive.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to find a village or a settlement or something safe,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we can talk more there,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and figure things out.", 80); FunctionDef.skip(1000);
					}
				}
			}	
			else if(d=="2"){
				FunctionDef.MCS("What in the name of everything holy happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("It appears to have been a minor clash.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It does remind me a little of the field where they got me.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) Got you? Will you tell me what is happening already?", 50); cout << "\n"; FunctionDef.truenarrator("2) I'm sorry I didn't trust you before.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,2);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Got you?", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Will you tell me what is happening already?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Fine.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I am Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " The general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " my army,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We were confronted by an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " That's where I got hit by an arrow. ", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that happened,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator(" I saw a bright flash followed by darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Then I somehow wound up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(1000);
					cout << "\n\n"; FunctionDef.truenarrator("1) I see, we should keep moving though and talk later.", 50); cout << "\n"; FunctionDef.truenarrator("2) Is that everything you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) I am sorry, really sorry about how I was before.", 50); cout << "\n";
					cout << "\033[33m>>    ";
					diadec2 = FunctionDef.GVI(1,3);
					cout << "\033[0m" << "\n";
					if(diadec2=="1"){
						FunctionDef.MCSC(mc, "I see,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should keep moving though and talk about this later,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we don't really have much time, ", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we don't want to meet the people who did this,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " do we?", 80); FunctionDef.skip(1000);
						cout << "\n"; 
						FunctionDef.narrator("Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should keep on moving.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We will figure the rest out later.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And can we please get along and not be", 80); cout << "\n"; FunctionDef.narrator("asses to each other?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand your situation,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and why you didn't trust me before,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("but we have to get along if we want to work together.", 80); FunctionDef.skip(1000);  
					}
					else if(diadec2=="2"){
						FunctionDef.MCSC(mc, "Is that everything you know?", 80); FunctionDef.skip(400); 
						cout << "\n";
						FunctionDef.narrator("It seems like it.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should get out of here and figure the rest out once we are someplace safer.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " And when we get along more.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("You know,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you were kind of an asshole,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, "  but I understand.", 80); FunctionDef.skip(1000);
					}
					else{
						FunctionDef.MCSC(mc, "I am sorry,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " really sorry about how I was before and about what happened to you.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I was trying to be careful.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.MCS("Thank you for telling me this.", 80); FunctionDef.skip(1000);
						cout << "\n";
						FunctionDef.narrator("Thank you,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " for the apology", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I understand,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " it's okay", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably move quick though,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("and find find a shelter or somewhere to hole up and then we can talk in peace.", 80); FunctionDef.skip(1000);
					}
				}
				else{
					FunctionDef.MCSC(mc, "I'm sorry I didn't trust you before.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I was being careful.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, "Also,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " what did you mean by \"got you?\"", 80); FunctionDef.skip(1000);
				}
			}
			else if(d=="3"){
				FunctionDef.MCS("What the glyph happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("It seems like there was a minor clash here.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Can't be too long since it happened.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("It reminds me of the battle field where they got me.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("Got you?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Will you tell me what happened already?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Very well, then.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " The name's Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was a general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We found ourselves in a confrontation with an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We were fighting,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("and then I got hit by an arrow.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " It was followed by a bright flash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all I saw was darkness.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("And,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I guess then I just woke up here,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " in your body and mind.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, "That's all I know.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) That's sad. We should probably move though and talk about it later.", 50); cout << "\n"; FunctionDef.truenarrator("2) That's all you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) Wow, I'm sorry that happened to you.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "Okay,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " that's...", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " sad.", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " We should probably move now though,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " and perhaps talk about it later", 80); cout << "\n"; FunctionDef.narrator("when we are holed up somewhere safe,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " okay?", 100); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Yes,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " you are right.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should continue moving until we get to safety.", 80); FunctionDef.skip(1000);
				}
				else if(diadec1=="2"){
					FunctionDef.MCSC(mc, "Is that everything?", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("I'm afraid it is.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I don't know anything else,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all this is new to me as well.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably keep moving if we want to survive", 80); cout << "\n"; FunctionDef.narrator("this stupid day.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's try finding a shelter or a settlement before the sun sets.", 80); FunctionDef.skip(1000);
				}
				else{
					FunctionDef.MCSC(mc, "Oh, wow,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I am really sorry about that.", 80); FunctionDef.skip(1000);
					cout << "\n";
					FunctionDef.narrator("Yeah,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " dying sucks,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " but it's not your fault.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's make sure the same thing doesn't happen to you too,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " okay?", 100); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We have to get out of here as soon as possible if we wish to accomplish that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's move,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we can talk more when we get to safety.", 80); FunctionDef.skip(1000);
					relwvoid = 4;
				}
			}
			else if(d=="4"){
				FunctionDef.MCS("What happened here?", 100); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.narrator("A minor clash, it seems.", 80); FunctionDef.skip(250);
				cout << "\n";
				FunctionDef.narrator("It reminds me of the field where they got me.", 75); FunctionDef.skip(750);
				cout << "\n";
				FunctionDef.MCS("Woah,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " that's crazy.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " Wait,", 100); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " got you?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " What do you meanb by that?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " When will you finally tell me who you are?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Okay then.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " My name is Void.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was a general of a faction called Terragnis.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I was leading an army into a battle.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("We found ourselves in a confrontation with an enemy of our faction,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " the faction of Slofridi.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We were figthing,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then I got hit by an arrow.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("It was followed by a bright flash,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " and then,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " all I saw was darkness.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " After that,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I woke up in your body.", 80); FunctionDef.skip(400); cout << "\n"; FunctionDef.narrator("That's all I know.", 80); FunctionDef.skip(1000);
				cout << "\n\n"; FunctionDef.truenarrator("1) What?? So you really are dead.", 50); cout << "\n"; FunctionDef.truenarrator("2) That's all you know?", 50); cout << "\n"; FunctionDef.truenarrator("3) Wow, I'm sorry that happened to you.", 50); cout << "\n";
				cout << "\033[33m>>    ";
				diadec1 = FunctionDef.GVI(1,3);
				cout << "\033[0m" << "\n";
				if(diadec1=="1"){
					FunctionDef.MCSC(mc, "What??", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " So you really are dead.", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Positive,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I really am dead.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Well,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I think we should not waste more time looking at charred bodies and perhaps move,", 80); FunctionDef.skip(250); cout <<"\n"; FunctionDef.narrator("unless you want whoever did this to return and find us.", 80); FunctionDef.skip(1000); 
				}
				else if(diadec1=="2"){
					FunctionDef.MCSC(mc, "That's all you know?", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("I'm afraid so.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We should probably keep moving unless we want to wait for those who did this.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " I don't think they would be very welcoming.", 80); FunctionDef.skip(1000); 
				}
				else{
					FunctionDef.MCSC(mc, "Wow,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " I'm sorry that happened to you.", 80); FunctionDef.skip(1000); 
					cout << "\n";
					FunctionDef.narrator("Yeah,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " well,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " dying sucks.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's make sure that doesn't happen to you too,", 80); FunctionDef.skip(250); cout <<"\n"; FunctionDef.narrator("okay?", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We have to get out of here as soon as possible if we want to accomplish that.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " Let's move,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("we can talk when we get to safety.", 80); FunctionDef.skip(1000);
				}
			}
			else if(d=="5"){
				FunctionDef.MCS("Woah,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " what the hell happened here?", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("From the looks of it,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " I'd guess an unfriendly clash.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " This reminds me of the field where they got me,", 80); FunctionDef.skip(250); cout << "\n"; FunctionDef.narrator("with the arrow I mentioned earlier.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.MCS("I see,", 80); FunctionDef.skip(250); FunctionDef.narratorclean(mc, " it's unfortune what happened.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(mc, " I think we should just keep on moving until we get to safety.", 80); FunctionDef.skip(1000);
				cout << "\n";
				FunctionDef.narrator("Yes,", 100); FunctionDef.skip(250); FunctionDef.narratorclean(vc, " we should.", 80); FunctionDef.skip(400); FunctionDef.narratorclean(vc, " We need to find a settlement.", 80); FunctionDef.skip(1000);
			}
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
	setlocale(LC_ALL, "sk_SK.UTF-8");

	GameDef.ExistujeSave = GameDef.CheckSave();
	if (GameDef.ExistujeSave) {
		GameDef.load();
		if(GameDef.playerName!=""&&(GameDef.mode!="speedrun"&&GameDef.mode!=""))	GameDef.savesequence(GameDef.lang);
		else GameDef.introsequence(GameDef.lang);
	}
	else {
		GameDef.save();
		GameDef.picklanguage();
	}

	return 0;
}

