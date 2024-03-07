#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <map>
#include <string>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include <limits>
#include "CONFunctions.h"
using namespace std;
Functions FunctionDef;
bool isfighting = false, isdefeated = false, attackstate = true, keyPressed = false, displaystats = true, gu = true, tobreak = false;
int lives, enemydmg, lastphp, lastenemyhp, ecooldown, timeleft, maxdmg, blockbonus, easeofuse, tickspeed, x, i, z, level, xp, blocked=0, fhit=0;
float cooldown, hp, currenthp, enemyhp, enemyrage, enemyskill, dmgdealt, edmgdealt, plvlbonusdmg, wlvlbonusdmg, enemyblock;
string lastAttack, lastblock, attacker, currentweapon;
map<int, string> attack_map {
  {1, "O--|---"},
  {2, "-O-|---"},
  {3, "--O|---"},
  {4, "---I---"},
  {5, "---|O--"},
  {6, "---|-O-"}, 
  {7, "---|--O"},
  {8, "O--|"},
  {9, "-O-|"},
  {10, "--O|"},
  {11, "---I"},
  {12, "---X"}
};
int checktime(){
	if(timeleft <= 0){
		timeleft = ecooldown;
		attackstate = false;
		system("CLS");
		tobreak = true;
	}
}
int savingspace(){
	string currentattack = attack_map[z];
	system("CLS");
	cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
  cout << currentattack;
  lastAttack = currentattack;
  Sleep(tickspeed);
  timeleft -= tickspeed;
  if(z==7) gu = false;
  if(z==1) gu = true;
  if(_kbhit()){
		char key = _getch();
		if(key == 'a'){
			gu = false;
			tobreak = true;
		}
	}
	checktime();
}
int isattackinge(){
	if(attackstate){
		tobreak = false;
		while(true){
			for(z = 0; z<=7 && gu && attackstate && !tobreak; z++) savingspace();
			for(z = 6; z>=1 && !gu && attackstate && !tobreak; z--) savingspace();
			if(tobreak) break;
		}
	}
}
int savingspace1(){
	string currentdef = attack_map[z];
	system("CLS");
	cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
	cout << ""+attacker+" is attacking you." << endl;
	cout << currentdef;
	lastblock = currentdef;
	Sleep(tickspeed);
	if(_kbhit()){
		char key = _getch();
		if(key == 'b'){
			tobreak = true;
		}
	}
}
int isdefendinge(){
	tobreak = false;
	if(!attackstate){
		system("CLS");
		cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
		cout << "Attack incoming...";
		Sleep(500);
		for(z=7; z<13 && !tobreak; z++) savingspace1();
	}
}
int dodisatk(){
	for(cooldown=15; cooldown >= 0 && attackstate; cooldown-=1){
		system("CLS");
		cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
		cout << "Last attack: " << lastAttack << endl;
		if(x==1){
			enemyblock = i;
			cout << "\n"+attacker+" blocked " << enemyblock << "% of your dmg";	
		} 
		else{
			enemyblock = 0;
			cout << "\n"+attacker+" didn't dodge your attack.";
		} 
		cout << "\nDamage dealt: " << dmgdealt;
		cout << "\nCooldown: " << cooldown/10. << "s";
		Sleep(100);
		timeleft -= 100;
		checktime();
	}
}
int checkdef(){
	if(lastblock=="O--|"){
		edmgdealt = enemydmg*0.75-(enemydmg*0.75*blockbonus/100);
		cout << "You blocked 25% of the damage. "+attacker+" dealt " << endl << edmgdealt << " dmg.";
	}
	else if(lastblock=="-O-|"){
		edmgdealt = enemydmg*0.50-(enemydmg*0.50*blockbonus/100);
		cout << "You blocked 50% of the damage. "+attacker+" dealt " << endl << edmgdealt << " dmg.";
	}
	else if(lastblock=="--O|"){
		edmgdealt = enemydmg*0.25-(enemydmg*0.25*blockbonus/100);
		cout << "You blocked 75% of the damage. "+attacker+" dealt " << endl << edmgdealt << " dmg.";
	}
	else if(lastblock=="---I"){
		edmgdealt = enemydmg*0.;
		cout << "You blocked 100% of the damage.";
		blocked++;
	}
	else{
		edmgdealt = enemydmg*1.-(enemydmg*1.*blockbonus/100);
		cout << "You didn't block any of the damage. "+attacker+" dealt " << endl << edmgdealt << "dmg.";
	}	
}
int dodisdef(){
	for(cooldown=4; cooldown>=0 && !attackstate; cooldown-=1){
		system("CLS");
		cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
		cout << "Last block: " << lastblock << endl;
		checkdef();
		cout << "\nCooldown: " << cooldown/10. << "s";
		Sleep(100);
	}
}
int loop(){
	while(true){
		Sleep(100);
		timeleft-=100;
		if(timeleft <= 0){
			timeleft = ecooldown;
			attackstate = false;
			break;
		}
		if(_kbhit()){
			char key = _getch();
			if(key=='a'){
				attackstate = true;
				break;
			}
		}
	}
}
bool CheckSave() {
	const wstring folderPath = L"save";
	DWORD folderAttributes = GetFileAttributesW(folderPath.c_str());

	if (folderAttributes == INVALID_FILE_ATTRIBUTES || !(folderAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
		if (CreateDirectoryW(folderPath.c_str(), nullptr) == 0 && GetLastError() != ERROR_ALREADY_EXISTS) {
			cerr << "[!] Save File Cannot be created!" << endl;
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
		cout << "[!] An error occurred" << endl;
		return "";
	}
}
void load() {
	string strLevel = PrecitatInfo("PlayerLevel.txt");
	string strXp = PrecitatInfo("PlayerXp.txt");
	string strHp = PrecitatInfo("PlayerHp.txt");
	string strCurrenthp = PrecitatInfo("PlayerCurrentHp.txt");
	string strMaxdmg = PrecitatInfo("PlayerMaxDmg.txt");
	string strLives = PrecitatInfo("Lives.txt");
	
	currentweapon = PrecitatInfo("CurrentWeapon.txt");
	attacker = PrecitatInfo("attacker.txt");
	level = stoi(strLevel);
	xp = stoi(strXp);
	hp = stoi(strHp);
	currenthp = stoi(strCurrenthp);
	maxdmg = stoi(strMaxdmg);
	lives = stoi(strLives);
}
int main(){
		load();
		plvlbonusdmg = 1+(level/10*maxdmg);
		if(attacker=="Wolves"){
			enemyhp = 20;
			enemyrage = 1;
			enemydmg = 3;
			enemyskill = 1;
		}
		if(currentweapon=="Stick"){
			maxdmg=1;
			easeofuse=3;
			wlvlbonusdmg=1;
		}
		else if(currentweapon=="IronSword"){
			maxdmg=3;
			easeofuse=2;
			wlvlbonusdmg=2;
		}
		ofstream outputFile("testsave.txt");
		if (!outputFile.is_open()) {
		    cerr << "Error opening file for writing!" << endl;
		    return 1; 
		}
		outputFile << "1" << endl;
		outputFile.close();
		srand((unsigned)time(0));
		tickspeed = easeofuse*25;
		isfighting = true;
		ecooldown = 5000/enemyrage;
		timeleft = ecooldown;
		while(isfighting){
			if(displaystats){
				cout << "\nYour stats \n---------------------------- \nYour hp: " << hp << endl << "Your dmg: " << maxdmg << endl << "Ease of use: " << easeofuse << endl << "Dmg bonus from player level: " << plvlbonusdmg << endl << "Dmg bonus from weapon level: " << wlvlbonusdmg << endl << "\n"+attacker+" stats \n---------------------------- \n"+attacker+" hp: " << enemyhp << endl << ""+attacker+" dmg: " << enemydmg << endl;
				Sleep(3000);
				cout << endl; FunctionDef.truenarrator("Press a to begin the fight.", 50); cout << endl; FunctionDef.truenarrator("Controls are A for attack, B for defense.", 50);
				while(true){
					if(_kbhit()){
						char key1 = _getch();
						if(key1 == 'a') break;
					}
				}
				cout << "\nFight begins...";
				Sleep(500);
				cout << "\n\nYou are attacking...      ";
				Sleep(250);
				displaystats = false;
			}
			isattackinge();
			isdefendinge(); 
			if(attackstate){
				system("CLS");
				cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
				cout << "Last attack: " << lastAttack;    
				if(lastAttack == "O--|---" || lastAttack == "---|--O") dmgdealt = maxdmg*0.5;
				else if(lastAttack == "-O-|---" || lastAttack == "---|-O-") dmgdealt = maxdmg*0.75;
				else if(lastAttack == "--O|---" || lastAttack == "---|O--") dmgdealt = maxdmg;
				else{
					dmgdealt = maxdmg+wlvlbonusdmg+plvlbonusdmg;
					fhit++;
				}
				x = (rand()%2)+1;
				i = (rand()%15*enemyskill)+1;
				if(x==1){
					enemyblock = i;
					dmgdealt -= dmgdealt*enemyblock/100;
				} 
				enemyhp -= dmgdealt;
				if(enemyhp<=0){
					system("CLS");
					enemyhp = 0;
					cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
					cout << "\nDamage dealt: " << dmgdealt << "\n"+attacker+" defeated.";
					Sleep(3500);
					break;
				}
				dodisatk();
				if(!attackstate) continue;
				enemyblock = 0;
				i = 0;
				x = 0;
				dmgdealt = 0;
				loop();
			}
			else{
				cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
				cout << "Last block: " << lastblock << endl;
				checkdef();
				cout << "\nCooldown: 0.5s";
				hp -= edmgdealt;
				edmgdealt = 0;
				if(hp<=0){
					hp = 0;
					cout << "Your HP: " << hp << "   <->   "+attacker+" HP: " << enemyhp << "\n-------------------------------"<< endl << endl;
					cout << "You have been defeated. ";
					isfighting = false;
					isdefeated = true;
					Sleep(1500);
					break;
				}
				dodisdef();
				timeleft = ecooldown-500; 
				loop();
			}
		}
	if(!isdefeated){
		system("CLS");
		cout << "Gained xp and enemy items.";
		xp+=10+(lastenemyhp*enemyrage*enemyskill*enemydmg)/(10/(1+(1+blocked)*(1+fhit)));
	}
	else{
		system("CLS");
		if(lives!=-1) lives--;
		UlozitInfo(to_string(lives), "Lives.txt");
	}	
	outputFile.open("testsave.txt");
  if (!outputFile.is_open()) {
      cerr << "Error opening file for writing!" << endl;
      return 1; 
  }
  outputFile << "0" << endl;
  outputFile << xp << endl;
  outputFile.close();
}
