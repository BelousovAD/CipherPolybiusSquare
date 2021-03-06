#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

string latinAlphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
string cyrillicAlphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ123";

class Coder
{
private:
	string password, const alphabet;
	vector<vector<char>> square;
	char a1, a2;
	bool lang;
public:
	void setPassword(string& password) {
		this->password = password;
	};
	void setLanguage(bool lang) {
		this->lang = lang;
	};
	void setAlphabet(string& alphabet){
		this->alphabet = alphabet;
	}
	void setSquare() {
		square.resize(5 + lang);
		for (int i = 0; i < square.size(); i++) {
			square[i].resize(5 + lang);
		}
		int r = 0, c = 0, size = password.size();
		for (int i = 0; i < size; i = i + 1) {
			if (password.find(password.at(i)) != i) {
				password.erase(password.begin() + i);
				--size;
				i = i - 1;
			}
		}
		for (int i = 0; i < password.size(); i++) {
			square[r][c] = password.at(i);
			c++;
			if (c == 5 + lang) {
				c = 0;
				r++;
			}
		}
		for (int i = 0; i < alphabet.size(); i++) {
			if (password.find(alphabet[i]) != -1) {
				continue;
			}
			square[r][c] = alphabet.at(i);
			c++;
			if (c == 5 + lang) {
				c = 0;
				r++;
			}
		}
	};
	void cipher(istream& in) {
		int x1, x2, y1, y2;
		cout << "Введите текст" << endl;
		in.read(&a1, 1);
		if (a1 == '\n') {
			return;
		}
		in.read(&a2, 1);
		while (a2 != '\n') {
			for (int i = 0; i < 5 + lang; i++) {
				for (int j = 0; j < 5 + lang; j++) {
					if (a1 == square[i][j]) {
						x1 = i;
						y1 = j;
					}
					if (a2 == square[i][j]) {
						x2 = i;
						y2 = j;
					}
				}
			}
			cout << square[x1][x2] << square[y1][y2];
			in.read(&a1, 1);
			if (a1 == '\n') {
				a2 = '\n';
			}
			else {
				in.read(&a2, 1);
			}
		}
		if (a1 != '\n') {
			for (int i = 0; i < 5 + lang; i++) {
				for (int j = 0; j < 5 + lang; j++) {
					if (a1 == square[i][j]) {
						x1 = i;
						y1 = j;
						break;
					}
				}
			}
			cout << square[y1][x1];
		}
	};
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Coder x;
	string password, language;
	bool lang;
	cout << "Введите алфавит (латиница/кириллица)" << endl;
	cin >> language;
	if (language == "кириллица") {
		lang = true;
		x.setLanguage(true);
		x.setAlphabet(cyrillicAlphabet);
	}
	else {
		lang = false;
		x.setLanguage(false);
		x.setAlphabet(latinAlphabet);
	}
	cout << "Введите пароль, состоящий из букв ";
	if (lang) {
		cout << cyrillicAlphabet << endl;
	}
	else {
		cout << latinAlphabet << endl;
	}
	cin >> password;
	cin.ignore();
	x.setPassword(password);
	x.setSquare();
	x.cipher(cin);
}