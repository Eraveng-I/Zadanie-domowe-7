#include<fstream>
#include <string>

#include <iostream>
#include <vector>

using namespace std;


string bad_letters = "";
int mistakes = 0;
string password = "kotek";
string visible_password = "";	//zakreskowane has³o ¿eby nie sprawdzaæ w pêtlacha czy dana litera jest ju¿ odkryta
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

void GetToHallOfFame (vector<string> &ranking, int i, int place_size)
{
	string name;
	cout << "Podaj swoja nazwê" << endl;
	cin >> name;

	name = ranking[i].substr(0, place_size) + name + " - " + to_string(result);
	//wyciagnac do funkcji dodani do rankingu => 1. sprawdz czy trzba walczyc =>2. jak ni to znajdz woln mijsc i sort =>3. jak tak to sprawdz czy wjdzi=>4. jak ni to nic a jak tak to wchodzi na 10 i sort

	cout << "Nowe name to:" << endl;
	cout << name << endl;

	ranking[i] = name;
}

void CheckRanking()
{
	result = password.size() * password.size() *(10 - mistakes) / 10;

	vector<string> ranking;
	bool hard_break = false;

	cout << "rozmiar wktora ranking to: " << ranking.size() << endl;

	//ranking.reserve(11);

	for (int i = 0;i < 11;i++)
	{
		ranking.push_back("");
	}

	cout << "rozmiar wktora ranking to: " << ranking.size() << endl;


	// Wczytanie rankingu
	ranking_file.open("ranking.txt");

	for (int i = 0;i < 11;i++)
	{
		getline(ranking_file, ranking[i]);
	}
	ranking_file.close();

	//for debug
	for (int i = 0;i < 11;i++)
	{
		cout << ranking[i] << endl;
	}

	//sprawdznie czy trzeba rywalizowac o wejsci do rankingu
	//iscie po linijkach - najpozniej stanie w linijce z indx=0 bo tam jest wzor
	for (int i = ranking.size() - 1;i >= 0;i--)
	{
		//iscie po znaku
		for (int j = ranking[i].size() - 1;j >= 0;j--)
		{
			if (ranking[i][j] == '-')
			{
				cout << "- jest na pozycji: " << j << endl;

				if (i < 9)
				{
					if (i == 0)
					{
						GetToHallOfFame(ranking, i + 1, 3);		//skoro to 1 zapisany wynik to nie bedzie sortowania
						hard_break = true;
						break;
					}

					GetToHallOfFame(ranking, i + 1, 3);

					//sort czy wejdzie wyzej
				}
				else if(i==9)
					{
						GetToHallOfFame(ranking, i + 1, 4);		//wstawiamy na 10 miejsce a tam 10 zajmuje 1 znak wiêcej
					}
					else if (i == 10)
						{
							//sprawdzamy czy pobije 10 miejsc

							j = j + 2;	//przejsci 2 znaki w prawo gdzie zaczyna sie liczba

							int number_length = ranking[i].size() - j;	//ile cyfr ma ta liczba (zakladaj¹c z po liczbie nic nic nie ma)	

							string substr = ranking[i].substr(j, number_length);

							int number = stoi(substr);

							/*for (int k = number_length;k > 0;k--)
							{

							}*/

							cout << "wyciagnity numr to: " << number << endl;

							if (number < result)
							{
								GetToHallOfFame(ranking, 10, 4);		//wstawiamy na 10 miejsce a tam 10 zajmuje 1 znak wiêcej

								//sort czy wjdzi wyzej

								hard_break = true;
							}

						}

				break;
			}
		}
		if (hard_break)
		{
			break;
		}
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
		CoutSign(18, "_");	//pod³oga
		cout << endl;

		break;

	case 2:
		CoutSign(10, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 3:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(9, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 4:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(7, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 5:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(6, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 6:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(1, "  |        |\n");	//s³upek i tu³ów
		CoutSign(5, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 7:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(1, "  |       /|\n");	//s³upek i r¹czka+tu³ów
		CoutSign(5, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 8:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(1, "  |       /|\\\n");	//s³upek i r¹czka+tu³ów+r¹czka
		CoutSign(5, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 9:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(1, "  |       /|\\\n");	//s³upek i r¹czka+tu³ów+r¹czka
		CoutSign(1, "  |       /\n");	//s³upek i r¹czka+tu³ów+r¹czka
		CoutSign(4, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
		cout << endl;

		break;

	case 10:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//s³upek i lina
		CoutSign(1, "  |        O\n");	//s³upek i g³owa
		CoutSign(1, "  |       /|\\\n");	//s³upek i r¹czka+tu³ów+r¹czka
		CoutSign(1, "  |       / \\\n");	//s³upek i r¹czka+tu³ów+r¹czka
		CoutSign(4, "  |\n");	//s³upek i enterowanie
		CoutSign(2, "_");	//pod³oga
		CoutSign(1, "|");	//s³upek przy pod³odze
		CoutSign(16, "_");	//reszta - pod³ogi
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

	// Wczytanie x s³owa z pliku do zminnj
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
