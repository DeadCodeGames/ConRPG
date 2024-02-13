#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;
void xpbar(double& perlevel) {
	if (perlevel == 0) {
		cout << "\033[1;30m";
		cout << "-------------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 4) {
		cout << "\033[1;32m";
		cout << "-";
		cout << "\033[1;30m";
		cout << "------------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 8) {
		cout << "\033[1;32m";
		cout << "--";
		cout << "\033[1;30m";
		cout << "-----------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 12) {
		cout << "\033[1;32m";
		cout << "---";
		cout << "\033[1;30m";
		cout << "----------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 16) {
		cout << "\033[1;32m";
		cout << "----";
		cout << "\033[1;30m";
		cout << "---------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 20) {
		cout << "\033[1;32m";
		cout << "-----";
		cout << "\033[1;30m";
		cout << "--------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 24) {
		cout << "\033[1;32m";
		cout << "------";
		cout << "\033[1;30m";
		cout << "-------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 28) {
		cout << "\033[1;32m";
		cout << "-------";
		cout << "\033[1;30m";
		cout << "------------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 32) {
		cout << "\033[1;32m";
		cout << "--------";
		cout << "\033[1;30m";
		cout << "-----------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 36) {
		cout << "\033[1;32m";
		cout << "---------";
		cout << "\033[1;30m";
		cout << "----------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 40) {
		cout << "\033[1;32m";
		cout << "----------";
		cout << "\033[1;30m";
		cout << "---------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 44) {
		cout << "\033[1;32m";
		cout << "-----------";
		cout << "\033[1;30m";
		cout << "--------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 48) {
		cout << "\033[1;32m";
		cout << "------------";
		cout << "\033[1;30m";
		cout << "-------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 52) {
		cout << "\033[1;32m";
		cout << "-------------";
		cout << "\033[1;30m";
		cout << "------------";
		cout << "\033[0m";
	}
	else if (perlevel <= 56) {
		cout << "\033[1;32m";
		cout << "--------------";
		cout << "\033[1;30m";
		cout << "-----------";
		cout << "\033[0m";
	}
	else if (perlevel <= 60) {
		cout << "\033[1;32m";
		cout << "---------------";
		cout << "\033[1;30m";
		cout << "----------";
		cout << "\033[0m";
	}
	else if (perlevel <= 64) {
		cout << "\033[1;32m";
		cout << "----------------";
		cout << "\033[1;30m";
		cout << "---------";
		cout << "\033[0m";
	}
	else if (perlevel <= 68) {
		cout << "\033[1;32m";
		cout << "-----------------";
		cout << "\033[1;30m";
		cout << "--------";
		cout << "\033[0m";
	}
	else if (perlevel <= 72) {
		cout << "\033[1;32m";
		cout << "------------------";
		cout << "\033[1;30m";
		cout << "-------";
		cout << "\033[0m";
	}
	else if (perlevel <= 76) {
		cout << "\033[1;32m";
		cout << "-------------------";
		cout << "\033[1;30m";
		cout << "------";
		cout << "\033[0m";
	}
	else if (perlevel <= 80) {
		cout << "\033[1;32m";
		cout << "--------------------";
		cout << "\033[1;30m";
		cout << "-----";
		cout << "\033[0m";
	}
	else if (perlevel <= 84) {
		cout << "\033[1;32m";
		cout << "---------------------";
		cout << "\033[1;30m";
		cout << "----";
		cout << "\033[0m";
	}
	else if (perlevel <= 88) {
		cout << "\033[1;32m";
		cout << "----------------------";
		cout << "\033[1;30m";
		cout << "---";
		cout << "\033[0m";
	}
	else if (perlevel <= 92) {
		cout << "\033[1;32m";
		cout << "-----------------------";
		cout << "\033[1;30m";
		cout << "--";
		cout << "\033[0m";
	}
	else if (perlevel <= 96) {
		cout << "\033[1;32m";
		cout << "------------------------";
		cout << "\033[1;30m";
		cout << "-";
		cout << "\033[0m";
	}






}
void inventorystart(double& phealth, double& hhealth, double& pstrenght, int& hcapacity, double& pendurance, double& hspeed, int& level, int& hdistance, double& perlevel, string hname[]) {
	system("cls");
	cout << ",--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--," << endl << "|  _____ ____  _____ ____   ____ ________ ____  _____ _________   ___   _______  ____,_____  |" << endl << "* |_   _|_   \\|_   _|_  _| |_  _|_   __  |_   \\|_   _|  _   _  |.'   `.|_   __ \\|_  _||_  _| *" << endl << "|   | |   |   \\ | |   \\ \\   / /   | |_ \\_| |   \\ | | |_/ | | \\_/  .-.  \\ | |__) | \\ \\  / /   |" << endl << "*   | |   | |\\ \\| |    \\ \\ / /    |  _| _  | |\\ \\| |     | |   | |   | | |  __ /   \\ \\/ /    *" << endl << "|  _| |_ _| |_\\   |_    \\ ' /    _| |__/ |_| |_\\   |_   _| |_  \\  `-'  /_| |  \\ \\_ _|  |_    |" << endl << "* |_____|_____|\\____|    \\_/    |________|_____|\\____| |_____|  `.___.'|____| |___|______|   *" << endl << "|                                                                                            |" << endl << "'--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--*--'" << endl;
	cout << "     ,--*--*--*--*--*--*--*--*--*--,                    ,--*--*--*--*--*--*--*--*--*--," << endl;
	cout << "     | PLAYER   Health    |";
	if (phealth < 1000)
		cout << "  " << left << setw(4) << phealth << "|";
	else if (phealth == 1000)
		cout << " " << left << setw(5) << phealth << "|";
	else if (phealth < 10000)
		cout << " " << left << setw(3) << fixed << setprecision(1) << phealth / 1000 << " K|";
	else
		cout << left << setw(4) << fixed << setprecision(1) << phealth / 1000 << " K|";
	cout << " |                    |           Health  | ";
	if (hhealth < 1000)
		cout << " " << left << setw(4) << hhealth << "|";
	else if (hhealth == 1000)
		cout << " " << left << setw(5) << hhealth << "|";
	else if (hhealth < 10000)
		cout << left << setw(4) << fixed << setprecision(1) << hhealth / 1000 << " K|";
	else
		cout << left << setw(4) << fixed << setprecision(1) << hhealth / 1000 << " K|";
	cout << " |" << endl << "     * ------   Strenght  |";
	if (pstrenght < 1000)
		cout << "  " << left << setw(4) << pstrenght << "|";
	else if (pstrenght == 1000)
		cout << " " << left << setw(5) << pstrenght << "|";
	else if (pstrenght < 10000)
		cout << " " << left << setw(3) << fixed << setprecision(1) << pstrenght / 1000 << " K|";
	else
		cout << left << setw(4) << fixed << setprecision(1) << phealth / 1000 << " K|";
	cout << " *                    * HORSE     Capacity|";
	cout << right << setw(4) << hcapacity << " Kg| *" << endl << "     |  STAT    Endurance |" << left << setw(4) << pendurance << " %| |                    | -----     Speed   |" << left << setw(5) << hspeed << " %| |" << endl;
	cout << "     *            [";
	if (level < 10)
		cout << "00";
	else if (level < 100)
		cout << "0";
	cout << level << "]            *                    * STATS     Distance|" << right << setw(4) << hdistance << "  m| *" << endl << "     | [";
	xpbar(perlevel);
	cout << "] |                    |    Name: " << right << setw(18) << hname[0] << " |" << endl << "     '--*--*--*--*--*--*--*--*--*--'                    '--*--*--*--*--*--*--*--*--*--'" << endl;
}
void invselect(){
	cout << "                     ,--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--," << endl;
	cout << "                     |             Weapons |  2. Pockets  5. Hands    |" << endl;
	cout << "                     * 1. Hotbar:  Potions *  3. Belt     6. Backpack *" << endl;
	cout << "                     |             Keys    |  4. Sling    7. Horse    |" << endl;
	cout << "                     '--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--'";
}
void invselectslot1_1() {
	cout << "                     ,--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--," << endl;
	cout << "                     |           > Weapons |  2. Pockets  5. Hands    |" << endl;
	cout << "                     * 1. Hotbar:  Potions *  3. Belt     6. Backpack *" << endl;
	cout << "                     |             Keys    |  4. Sling    7. Horse    |" << endl;
	cout << "                     '--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--'";
}
void invselectslot1_2() {
	cout << "                     ,--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--," << endl;
	cout << "                     |             Weapons |  2. Pockets  5. Hands    |" << endl;
	cout << "                     * 1. Hotbar:> Potions *  3. Belt     6. Backpack *" << endl;
	cout << "                     |             Keys    |  4. Sling    7. Horse    |" << endl;
	cout << "                     '--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--'";
}
void invselectslot1_3() {
	cout << "                     ,--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--," << endl;
	cout << "                     |             Weapons |  2. Pockets  5. Hands    |" << endl;
	cout << "                     * 1. Hotbar:  Potions *  3. Belt     6. Backpack *" << endl;
	cout << "                     |           > Keys    |  4. Sling    7. Horse    |" << endl;
	cout << "                     '--*--*--*--*--*--*---*--*--*--*--*--*--*--*--*--'";
}
int main() {
	double phealth = 10500, hhealth = 10500, pstrenght = 10555, pendurance = 93.3, hspeed = 120.2, perlevel = 94.85;
	int hcapacity = 958, level = 64, hdistance = 400;
	string hname[13] = { "No horse aquaried","Sergej Baracuda","Napoli Partobona","Mustang Shefchovic","Pablo Paresco","Ishtvan Ludvajovic","Nicolaj Francessco","Valeria Casino","Pepan the Igen","Iron Josif","Benito Soliny","Carina Wieck","Bogdan Boojack" };
	//	p(health) - player
	//	h(health) - horse
	//int selectedhotbar =
	inventorystart(phealth, hhealth, pstrenght, hcapacity, pendurance, hspeed, level, hdistance, perlevel, hname);
	invselect();
	return 0;
}
