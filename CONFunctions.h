
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



using namespace std;



class Functions
{
public:
	string playerName, input, tb, decision1, decision1sub1, decision2 = "";
	int a = 0, b = 0, sequence, level, xp, requiredxp, initiallvl, hp, currenthp, maxdmg, plvlbonusdmg;
	bool isAlive = true;
	const string mc = "\033[33m", vc = "\033[36m";

	void clearLine() {
		cout << "\r                                              \r";
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
	void skip(int time) {
		for (time; time > 0; time -= 50) {
			if (_kbhit()) {
				char key = _getch();
				if (key == '\r' or key == ' ') {
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
		while (_kbhit()) {
			_getch();
			Sleep(50);
		}
	}
};
