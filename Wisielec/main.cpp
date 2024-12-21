#include<fstream>
#include <string>

#include <iostream>
#include <vector>

using namespace std;


string bad_letters = "";
int mistakes = 0;
string password = "kotek";
string visible_password = "";	//zakreskowane has�o �eby nie sprawdza� w p�tlacha czy dana litera jest ju� odkryta
bool password_guessed = false;
ifstream password_file;
int amount = 20;
fstream ranking_file;
int result = 0;

void PrintMistakes()
{
	cout << "Mistakes:" << endl;

	for (int i = 0; i < bad_letters.size(); i++)
	{
		cout << bad_letters[i] << " ";
	}
	cout << endl;
}

void PrintPassword()
{
	cout << "Password:" << endl;

	for (int i = 0; i < visible_password.size(); i++)
	{
		cout << visible_password[i] << " ";
	}
	cout << endl;
}

void CheckRanking()
{
	result = password.size() * password.size() *(10 - mistakes) / 10;

	vector<string> ranking;

	cout << "rozmiar wktora ranking to: " << ranking.size() << endl;

	//ranking.reserve(11);

	for (int i = 0;i < 11;i++)
	{
		ranking.push_back("");
	}

	cout << "rozmiar wktora ranking to: " << ranking.size() << endl;

	ranking_file.open("ranking.txt");

	// Wczytanie x s�owa z pliku do zminnj
	for (int i = 0;i < 11;i++)
	{
		getline(ranking_file, ranking[i]);
	}
	ranking_file.close();

	for (int i = 0;i < 11;i++)
	{
		cout << ranking[i] << endl;
	}
}

void CoutSign(int amount, string sign)
{
	for (int i = 0; i < amount; i++)
	{
		//cout << endl;
		cout << sign;
	}
}

void GetInput()
{
	char letter;
	bool good_letter = false;

	cin >> letter;

	for (int i = 0; i < password.size(); i++)
	{
		if (password[i] == letter)
		{
			visible_password[i] = password[i];
			good_letter = true;
		}
	}

	if (good_letter)
	{
		if (password==visible_password)
		{
			password_guessed = true;

			CheckRanking();
		}

		return;	//jesli litera jest w hasle to koniec funkcji, jesli nie bylo to idziemy dalej zwiekkszajac ilosc bledow
	}

	bad_letters = bad_letters + letter;	

	mistakes++;
}

void DrawHangman(int mistakes_amount)
{
	switch (mistakes_amount)
	{
	case 0:
		CoutSign(10, "\n");	//enterowanie

		break;

	case 1:
		CoutSign(10, "\n");	//enterowanie
		CoutSign(18, "_");	//pod�oga
		cout << endl;

		break;

	case 2:
		CoutSign(10, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 3:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(9, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 4:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(7, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 5:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(6, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 6:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(1, "  |        |\n");	//s�upek i tu��w
		CoutSign(5, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 7:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(1, "  |       /|\n");	//s�upek i r�czka+tu��w
		CoutSign(5, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 8:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(1, "  |       /|\\\n");	//s�upek i r�czka+tu��w+r�czka
		CoutSign(5, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 9:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(1, "  |       /|\\\n");	//s�upek i r�czka+tu��w+r�czka
		CoutSign(1, "  |       /\n");	//s�upek i r�czka+tu��w+r�czka
		CoutSign(4, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	case 10:
		CoutSign(1, "  ");	//przerwa g�rny
		CoutSign(10, "_");	//belka g�rna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s�upek i lina
		CoutSign(1, "  |        O\n");	//s�upek i g�owa
		CoutSign(1, "  |       /|\\\n");	//s�upek i r�czka+tu��w+r�czka
		CoutSign(1, "  |       / \\\n");	//s�upek i r�czka+tu��w+r�czka
		CoutSign(4, "  |\n");	//s�upek i enterowanie
		CoutSign(2, "_");	//pod�oga
		CoutSign(1, "|");	//s�upek przy pod�odze
		CoutSign(16, "_");	//reszta - pod�ogi
		cout << endl;

		break;

	default:
		break;
	}
}

void SetPassword()
{
	// Losow haslo
	srand(time(nullptr)); // Generator losowy
	int randomIndex = rand() % 20;

	password_file.open("hasla.txt");

	// Wczytanie x s�owa z pliku do zminnj
	string word;
	for (int i = 0;i <= randomIndex;i++)
	{
		getline(password_file, word);
	}
	password_file.close();

	//cout << "word to " << word << endl;

	password = word;
}

void Initialize()
{
	password_guessed = false;
	mistakes = 0;
	bad_letters = "";

	SetPassword();

	visible_password = password;

	for (int i = 0; i < visible_password.size(); i++)
	{
		visible_password[i] = '_';
	}

	DrawHangman(0);
	PrintMistakes();
	PrintPassword();
}



void Render(int mistakes_amount)
{
	DrawHangman(mistakes_amount);
	PrintMistakes();
	PrintPassword();
}

int main()
{
	setlocale(LC_CTYPE, "Polish");
	bool again= false;

	//cout << "This is drawing of your Hanging Man:" << endl << endl;

	//Initialize();

	/*for (int i = 0; i <= 10; i++)
	{
		cout << "Step " << i << endl;
		DrawHangman(i);

		PrintMistakes();

		PrintPassword();
	}*/

	
	do
	{
		Initialize();

		while (mistakes < 10 && password_guessed == false)
		{
			GetInput();
			//UpdateGame();

			Render(mistakes);

		}

		cout << "Do you want to play again? 1=yes, 0=no" << endl;
		cin >> again;

	} while (again);
	

	//ShutDown();

	return 0;
}
