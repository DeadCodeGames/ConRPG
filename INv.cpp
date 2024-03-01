#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
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
void inventorystart(double& phealth, double& hhealth, double& pstrenght, int& hcapacity, double& pendurance, double& hspeed, int& level, int& hdistance, double& perlevel, string hname) {
	
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
		cout << " " << left << setw(5) << hhealth << "|";
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
	cout << right << setw(4) << hcapacity << " Kg| *" << endl << "     |  STAT    Endurance |" << left << setw(4) << pendurance << " %| |                    | -----     Speed   |" << right << setw(5) << hspeed << " %| |" << endl;
	cout << "     *            [";
	if (level < 10)
		cout << "00";
	else if (level < 100)
		cout << "0";
	cout << level << "]            *                    * STATS     Distance|" << right << setw(4) << hdistance << "  m| *" << endl << "     | [";
	xpbar(perlevel);
	cout << "] |                    |    Name: " << right << setw(18) << hname << " |" << endl << "     '--*--*--*--*--*--*--*--*--*--'                    '--*--*--*--*--*--*--*--*--*--'" << endl;
}
void pickem(int& slot, bool& inv, bool& select) {

	if (slot < 1)
		slot = 1;
	if (slot > 6)
		slot = 6;
	cout << "                        ,--*--*--*--*--*--*---*--*--*--*--*--*--," << endl;
	cout << "                        | ";
	if (slot == 1)
		cout << ",---------,";
	else cout << "           ";
	cout << "  ";
	if (slot == 3)
		cout << ",---------,";
	else cout << "           ";
	cout << "  ";
	if (slot == 5)
		cout << ",---------,";
	else cout << "           ";
	cout << " |" << endl << "                        | ";
	if (slot == 1)
		cout << "| Pockets |";
	else cout << "  Pockets  ";
	cout << "  ";
	if (slot == 3)
		cout << "|  Hands  |";
	else cout << "   Hands   ";
	cout << "  ";
	if (slot == 5)
		cout << "|  Sling  |";
	else cout << "   Sling   ";
	cout << " |" << endl << "                        | ";
	if (slot == 1)
		cout << "'---------'";
	else if(slot == 2)
		cout << ",---------,";
	else cout << "           ";
	cout << "  ";
	if (slot == 3)
		cout << "'---------'";
	else if (slot == 4)
		cout << ",---------,";
	else cout << "           ";
	cout << "  ";
	if (slot == 5)
		cout << "'---------'";
	else if (slot == 6)
		cout << ",---------,";
	else cout << "           ";
	cout << " |" << endl << "                        | ";
	if (slot == 2)
		cout << "|  Belt   |";
	else cout << "   Belt    ";
	cout << "  ";
	if (slot == 4)
		cout << "|Backpack |";
	else cout << " Backpack  ";
	cout << "  ";
	if (slot == 6)
		cout << "|  Horse  |";
	else cout << "   Horse   ";
	cout << " |" << endl << "                        | ";
	if (slot == 2)
		cout << "'---------'";
	else cout << "           ";
	cout << "  ";
	if (slot == 4)
		cout << "'---------'";
	else cout << "           ";
	cout << "  ";
	if (slot == 6)
		cout << "'---------'";
	else cout << "           ";
	cout << " |" << endl << "                        '--*--*--*--*--*--*---*--*--*--*--*--*--'" << endl;
	cout << "w - up\n" << "s - down\n" << "a - left\n" << "d - right\n" << "f - enter\n" << "e - exit\n";
	char a;
	a = _getch();
	switch (a)
	{
	case 'w':
		slot--;
		break;
	case 's':
		slot++;
		break;
	case 'a':
		slot--;
		slot--;
		break;
	case 'd':
		slot++;
		slot++;
		break;
	case 'e':
		inv = false;
		break;
	case 'f':
		select = true;
		inv = false;
		break;
	case 'W':
		slot--;
		break;
	case 'S':
		slot++;
		break;
	case 'A':
		slot--;
		slot--;
		break;
	case 'D':
		slot++;
		slot++;
		break;
	case 'E':
		inv = false;
		break;
	case 'F':
		select = true;
		inv = false;
		break;
	default:
		break;
	}
}
void pockets() {
	cout << ",------------------------," << endl;
	cout << "| Pockets                |" << endl;
	cout << "|------------------------|" << endl;
	
}
void presmerovanie(int& slot) {
		if (slot == 1)
			cout << "slot 1";
		else if (slot == 2)
			cout << "slot 2";
		else if (slot == 3)
			cout << "slot 3";
		else if (slot == 4)
			cout << "slot 4";
		else if (slot == 5)
			cout << "slot 5";
		else if (slot == 6)
			cout << "slot 6";
		cout << endl;
		system("pause");
} 
void inventory(double phealth, double pstrenght, double pendurance, double perlevel, int level, int selected, bool hotbar, int slot, bool inv, bool select, double hspeed1[], double hhealth1[], string hname1[], int hcapacity1[], int hdistance1[], int kon, int pockket_coins, bool pckt_coins) {
	if (pockket_coins == 0)
		pckt_coins = false;
	double hhealth = hhealth1[kon - 1];
	double hspeed = hspeed1[kon - 1];
	string hname = hname1[kon - 1];
	int hcapacity = hcapacity1[kon - 1];
	int hdistance = hdistance1[kon - 1];

	do {
		select = false;
		inventorystart(phealth, hhealth, pstrenght, hcapacity, pendurance, hspeed, level, hdistance, perlevel, hname);
		pickem(slot, inv, select);
		if (select == true) presmerovanie(slot);
	} while (inv == true);
}
int main() {
	double phealth = 10500, pstrenght = 10555, pendurance = 93.3, perlevel = 94.85;
	int level = 64, selected = 0;
	bool hotbar = false;
	double hspeed1[7] = {0.0,58.0,87.0,38.0,69.0,34.0,85.0 };
	double hhealth1[7] = { 0,2310,1896,1200,1945,1019,3007 };
	string hname1[7] = { "No horse aquared","Pablo Paresco","Valeria Casino","Bogdan Boojack","Mustang Schefchovic","Ishtvan Ludvajovic","Pepan the Igen"};
	int hcapacity1[7] = { 0,64,42,50,54,29,78 };
	int hdistance1[7] = { 0,865,3290,920,1389,731,5841 };
	int kon = 1;
	int slot = 1;
	bool inv = true;
	bool select = false;
//---------------------------------------------
	int pockket_coins = 10;
	bool pckt_coins = true;
	inventory(phealth, pstrenght, pendurance, perlevel, level, selected, hotbar, slot, inv, select, hspeed1, hhealth1, hname1, hcapacity1, hdistance1, kon, pockket_coins, pckt_coins);
	return 0;
}
