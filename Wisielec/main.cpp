#include <iostream>

using namespace std;


string bad_letters = "abc";
int mistakes = 3;
string password = "kotek";
string visible_password = "";	//zakreskowane has³o ¿eby nie sprawdzaæ w pêtlacha czy dana litera jest ju¿ odkryta

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


void CoutSign(int amount, string sign)
{
	for (int i = 0; i < amount; i++)
	{
		//cout << endl;
		cout << sign;
	}
}


void DrawHangman(int mistakes)
{
	switch (mistakes)
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

void Initialize()
{
	visible_password = password;

	for (int i = 0; i < visible_password.size(); i++)
	{
		visible_password[i] = '_';
	}
}

int main()
{
	setlocale(LC_CTYPE, "Polish");

	int mistakes = 0;

	cout << "This is drawing of your Hanging Man:" << endl << endl;

	Initialize();

	for (int i = 0; i <= 10; i++)
	{
		cout << "Step " << i << endl;
		DrawHangman(i);

		PrintMistakes();

		PrintPassword();
	}

	//Initialize();
		
	//while (/*!ExitGame*/ true)
	//{
	//	//GetInput();
	//	//UpdateGame();
	//	//Render();
	//}

	//ShutDown();

	return 0;
}
