#include<fstream>
#include <string>

#include <iostream>
#include <vector>

//#include <conio.h>
#include<windows.h>
//#include<cstdlib>

using namespace std;


string bad_letters = "";
int mistakes = 0;
string password = "kotek";
string visible_password = "";	//zakreskowane hasło żeby nie sprawdzać w pętlacha czy dana litera jest już odkryta
bool password_guessed = false;
ifstream password_file;
int amount = 20;
fstream ranking_file;
int result = 0;

void clearScreen()
{
	system("cls");
	cout << endl;
}

void PrintMistakes()
{
	//cout << "Mistakes:" << endl;
	cout << "Błędy:" << endl;

	for (int i = 0; i < bad_letters.size(); i++)
	{
		cout << bad_letters[i] << " ";
	}
	cout << endl;
}

void PrintPassword()
{
	//cout << "Password:" << endl;
	cout << "Hasło:" << endl;

	for (int i = 0; i < visible_password.size(); i++)
	{
		cout << visible_password[i] << " ";
	}
	cout << endl;
}

void GetToHallOfFame (vector<string> &ranking, int i, int place_size)
{
	string name;
	cout << "Witaj w galerii sław! Podaj swoja nazwę" << endl;
	//cin >> name;
	cin.ignore(); // Usuwanie znaku nowej linii pozostawiony w buforze przez poprzednie `cin`
	getline(cin, name); // Wczytujemy całą linię


	name = ranking[i].substr(0, place_size) + name + " - " + to_string(result);

	//cout << "Nowe name to:" << endl;
	//cout << name << endl;

	ranking[i] = name;
}

void SortRanking (vector<string> &ranking, int i)
{
	bool hard_break = false;
	for (;i > 1;i--)
	{
		//iscie po znaku
		for (int j = ranking[i-1].size() - 1;j >= 0;j--)
		{
			if (ranking[i-1][j] == '-')
			{
				//cout << "- jest na pozycji: " << j << endl;

				//sprawdzamy liczbe na mijscu wczsnij
				j = j + 2;	//przejsci 2 znaki w prawo gdzie zaczyna sie liczba

				int number_length = ranking[i-1].size() - j;	//ile cyfr ma ta liczba (zakladając z po liczbie nic nic nie ma)	

				string substr = ranking[i-1].substr(j, number_length);

				int number = stoi(substr);

				//cout << "wyciagnity numr to: " << number << endl;

				if (number < result)
				{
					string place1="";
					string place2="";

					//zbiramy 1 mijsc do zamiany
					for (int a = 0;;a++)
					{
						if (ranking[i-1][a] == '.')
						{
							break;
						}
						else
							{
								place1 = place1 + ranking[i - 1][a];
							}
					}

					//zbiramy 2 mijsc do zamiany
					for (int a = 0;;a++)
					{
						if (ranking[i][a] == '.')
						{
							break;
						}
						else
						{
							place2 = place2 + ranking[i][a];
						}
					}

					ranking[i - 1]=place2+  ranking[i - 1].substr(place1.size(), ranking[i - 1].size()- place1.size());		//to jst 2 mijsc + 1 linijka po odciciu 1 mijsca
					
					ranking[i]=place1+  ranking[i].substr(place2.size(), ranking[i].size()- place2.size());		//to samo na odwrot

					swap(ranking[i - 1], ranking[i]);

					break;
				}
				else
					{
						hard_break = true;
						break;
					}
			}
		}

		if (hard_break)
		{
			break;
		}
	}

	cout << "Galeria sław:" << endl;

	for (int a = 0;a < ranking.size();a++)
	{
		cout << ranking[a] << endl;
	}
}

void SaveResults(vector<string>& ranking)
{

	ranking_file.open("ranking.txt");

	for (int i = 0;i < ranking.size();i++)
	{
		ranking_file << ranking[i] << endl;
	}
	ranking_file.close();
}

void CheckRanking()
{
	result = password.size() * password.size() *(10 - mistakes) / 10;

	vector<string> ranking;
	bool hard_break = false;

	//cout << "rozmiar wktora ranking to: " << ranking.size() << endl;

	//ranking.reserve(11);

	for (int i = 0;i < 11;i++)
	{
		ranking.push_back("");
	}

	//cout << "rozmiar wktora ranking to: " << ranking.size() << endl;

	// Wczytanie rankingu
	ranking_file.open("ranking.txt");

	for (int i = 0;i < 11;i++)
	{
		getline(ranking_file, ranking[i]);
	}
	ranking_file.close();

	//for debug
	/*for (int i = 0;i < 11;i++)
	{
		cout << ranking[i] << endl;
	}*/

	//sprawdzenie czy trzeba rywalizowac o wejsci do rankingu
	//iscie po linijkach - najpozniej stanie w linijce z indx=0 bo tam jest wzor
	for (int i = ranking.size() - 1;i >= 0;i--)
	{
		//iscie po znaku
		for (int j = ranking[i].size() - 1;j >= 0;j--)
		{
			if (ranking[i][j] == '-')
			{
				//cout << "- jest na pozycji: " << j << endl;

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
					SortRanking(ranking, i + 1);
					hard_break = true;
					break;
				}
				else if(i==9)
					{
						GetToHallOfFame(ranking, i + 1, 4);		//wstawiamy na 10 miejsce a tam 10 zajmuje 1 znak więcej
						SortRanking(ranking, i + 1);
						hard_break = true;
						break;
					}
					else if (i == 10)
						{
							//sprawdzamy czy pobije 10 miejsc

							j = j + 2;	//przejsci 2 znaki w prawo gdzie zaczyna sie liczba

							int number_length = ranking[i].size() - j;	//ile cyfr ma ta liczba (zakladając z po liczbie nic nic nie ma)	

							string substr = ranking[i].substr(j, number_length);

							int number = stoi(substr);

							//cout << "wyciagnity numr to: " << number << endl;

							if (number < result)
							{
								GetToHallOfFame(ranking, 10, 4);		//wstawiamy na 10 miejsce a tam 10 zajmuje 1 znak więcej

								//sort czy wjdzi wyzej
								SortRanking(ranking, 10);
								
							}
							hard_break = true;
							break;
						}
				break;
			}
		}

		if (hard_break)
		{
			break;
		}
	}

	SaveResults(ranking);
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
		CoutSign(11, "\n");	//enterowanie

		break;

	case 1:
		CoutSign(10, "\n");	//enterowanie
		CoutSign(18, "_");	//podłoga
		cout << endl;

		break;

	case 2:
		CoutSign(10, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 3:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(9, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 4:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(7, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 5:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(6, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 6:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(1, "  |        |\n");	//słupek i tułów
		CoutSign(5, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 7:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(1, "  |       /|\n");	//słupek i rączka+tułów
		CoutSign(5, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 8:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(1, "  |       /|\\\n");	//słupek i rączka+tułów+rączka
		CoutSign(5, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 9:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(1, "  |       /|\\\n");	//słupek i rączka+tułów+rączka
		CoutSign(1, "  |       /\n");	//słupek i rączka+tułów+rączka
		CoutSign(4, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
		cout << endl;

		break;

	case 10:
		CoutSign(1, "  ");	//przerwa górny
		CoutSign(10, "_");	//belka górna
		CoutSign(1, "\n");	//enter
		CoutSign(2, "  |        |\n");	//słupek i lina
		CoutSign(1, "  |        O\n");	//słupek i głowa
		CoutSign(1, "  |       /|\\\n");	//słupek i rączka+tułów+rączka
		CoutSign(1, "  |       / \\\n");	//słupek i rączka+tułów+rączka
		CoutSign(4, "  |\n");	//słupek i enterowanie
		CoutSign(2, "_");	//podłoga
		CoutSign(1, "|");	//słupek przy podłodze
		CoutSign(16, "_");	//reszta - podłogi
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

	// Wczytanie x słowa z pliku do zminnj
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

	clearScreen();
	DrawHangman(0);
	PrintMistakes();
	PrintPassword();
}

void Render(int mistakes_amount)
{
	clearScreen();
	DrawHangman(mistakes_amount);
	PrintMistakes();
	PrintPassword();
}

int main()
{
	setlocale(LC_CTYPE, "Polish");
	bool again= false;
	
	do
	{
		Initialize();

		while (mistakes < 10 && password_guessed == false)
		{
			GetInput();
			//UpdateGame();

			Render(mistakes);

		}
		
		if (password_guessed)
		{
			cout << "Wygrałeś" << endl;
		}
		else
			{
				cout << "Przegrałeś" << endl;
			}
		//cout << "Do you want to play again? 1=yes, 0=no" << endl;
		cout << "Chcesz jeszcze zagrać? 1=tak, 0=nie" << endl;
		cin >> again;

	} while (again);
	

	//ShutDown();

	return 0;
}
