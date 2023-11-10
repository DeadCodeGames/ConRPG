#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));
	cout << "                                          W E L C O M E    T O" << endl;
 	cout << " .----------------.    .----------------.  .----------------.  .-----------------.   .----------------. " << endl << "| .--------------. |  | .--------------. || .--------------. || .--------------. |  | .--------------. |" << endl << "| |              | |  | |     ______   | || |     ____     | || | ____  _____  | |  | |              | |" << endl << "| |              | |  | |   .' ___  |  | || |   .'    `.   | || ||_   \\|_   _| | |  | |              | |" << endl << "| |    ______    | |  | |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\ | |   | |  | |    ______    | |" << endl << "| |   |______|   | |  | |  | |         | || |  | |    | |  | || |  | |\\ \\| |   | |  | |   |______|   | |" << endl << "| |              | |  | |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\   |_  | |  | |              | |" << endl << "| |              | |  | |   `._____.'  | || |   `.____.'   | || ||_____|\\____| | |  | |              | |" << endl << "| |              | |  | |              | || |              | || |              | |  | |              | |" << endl << "| '--------------' |  | '--------------' || '--------------' || '--------------' |  | '--------------' |" << endl << " '----------------'    '----------------'  '----------------'  '----------------'    '----------------' ";
	cout << endl << "                                           The C++ Console RPG";
	cout << endl << "                                         Press [ANY KEY] to Begin";
	_getch();
	cout << endl << "   Hello, Player!" << endl << "  ";
	Sleep(1000);
	cout << " .";  Sleep(500); cout << "."; Sleep(500); cout << "." << endl << "  "; Sleep(1000);
	cout << " Your name isn't Player, is it?" << endl << "  ";
	Sleep(1500);
	cout << " What's your name?" << endl << "  [ENTER YOUR NAME NOW]" << endl << "   ";
	string playerName;
	getline(wcin, playerName);
	if (!playerName.empty()) {
		wcout << "   Nice to meet you, " << playerName << "!";;
	} else {
		cout << "   You"; Sleep(1000); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(1000); cout << " Don't have a name?" << endl << "   I will give you one more chance to tell me your name." << endl;
		getline(cin, playerName);
		if (!playerName.empty()) {
		wcout << "   At last! Nice to meet you, " << playerName << "!";;
	} else {
		cout << "   You sure?" << endl; Sleep(1500);
		cout << "   That's"; Sleep(1000); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "."; Sleep(1000); cout << " sad." << endl; Sleep(1000);
		cout << "   I still need something to call you by, though." << endl; Sleep(750);
		cout << "   Will Player suffice?" << endl; Sleep(1000);
		cout << "   I think it will be alright." << endl << "[PRESS ANY KEY TO CONTINUE]"; _getch(); system("cls");
		
	};
}
}
