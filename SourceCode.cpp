#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<fstream>
#include<string>
using namespace std;
const int SIZE1 = 9;
const int r = 9;
const int c = 9;
void random_gen(int i_a[SIZE1][SIZE1]);
void printArr(int[][SIZE1], int i_a[][SIZE1]);
bool checkColumn(int arr[][SIZE1], int, int);
bool checkRow(int arr[][SIZE1], int, int);
void input(int arr[][SIZE1], int i_a[SIZE1][SIZE1], int moves = 0);
bool checkboxx(int arr[][SIZE1], int, int, int);
void readData(int board[][SIZE1], int slot);
bool load(int& moves, int arr[][SIZE1], int p_a[][SIZE1]);
void Del(int p_arr[][SIZE1]);
void writeData(int board[][SIZE1], int slot);
void random_gen(int i_a[SIZE1][SIZE1]);
void random_gen(int i_a[SIZE1][SIZE1])
{

    srand(time(0));
    for (int i = 0; i < SIZE1; i++)
    {
        for (int j = 0; j < SIZE1; j++)
        {
            if (i_a[i][j] != 0)
            {
                int temp = rand() % 10;
                while (checkColumn(i_a, j, temp) || checkRow(i_a, i, temp) || checkboxx(i_a, i, j, temp) || temp == 0)
                {


                    temp = rand() % 10;
                }
                i_a[i][j] = temp;

            }

        }
    }
}
int mainmenu(int p_arr[][SIZE1])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 9);
    int arr[SIZE1][SIZE1];
    for (int i = 0; i < SIZE1; i++)
    {
        for (int j = 0; j < SIZE1; j++)
        {
            arr[i][j] = p_arr[i][j];
        }
    }
    system("cls");

    int option;
    char sud[6] = { 'S','U','D','O','K','U' };
    for (int i = 0; i < 6; i++) {
        cout << "\n";
    }
    cout << "\t\t";

    for (int i = 0; i < 6; i++)
    {
        cout << " ";
        Sleep(450);
        static CONSOLE_FONT_INFOEX  fontex;
        fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetCurrentConsoleFontEx(hOut, 0, &fontex);
        fontex.FontWeight = 1200;
        fontex.dwFontSize.X = 60;
        fontex.dwFontSize.Y = 60;
        SetCurrentConsoleFontEx(hOut, NULL, &fontex);
        cout << sud[i];
    }
    Sleep(850);
    system("cls");
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 500;
    fontex.dwFontSize.X = 30;
    fontex.dwFontSize.Y = 30;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
    cout << "\nEnter 1 for New game\nEnter 2 to load game\nEnter 3 to Delete Saved Game\nEnter 4 to quit\n";
    cin >> option;
    while ((option != 1 && option != 2 && option != 3 && option != 4) || cin.fail())
    {
        cout << "\n Invalid Input...Enter again:\n";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> option;

    }
    int moves = 0;
    bool flagg;
    switch (option)
    {
    case 1:
    {
        random_gen(arr);
        printArr(arr, p_arr);
        input(arr, p_arr);
        break;

    }
    case 2:
    {
        flagg = load(moves, arr, p_arr);
        if (flagg)
        {
            system("pause");
            printArr(arr, p_arr);
            input(arr, p_arr, moves);
        }

        break;



    }
    case 3:
    {
        Del(p_arr);
    }
    case 4:
    {
        return 0;
        break;
    }
    default:
    {
        cout << "\nInvalid input";
        break;


    }
    }
    return option;
}
bool iss_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
bool save(int moves, int arr[][SIZE1])
{
    ofstream file1, file2, file3;
    ifstream file1_1, file2_2, file3_3;
    file1_1.open("game1.txt", ios::in);
    file2_2.open("game2.txt", ios::in);
    file3_3.open("game3.txt", ios::in);
    bool flag1 = iss_empty(file1_1);
    bool flag2 = iss_empty(file2_2);
    bool flag3 = iss_empty(file3_3);
    if (iss_empty(file1_1))
    {
        file1.open("game1.txt", ios::out);
        file1 << moves;
        file1 << endl;
        for (int i = 0; i < SIZE1; i++)
        {
            for (int j = 0; j < SIZE1; j++)
            {
                file1 << arr[i][j] << " ";
            }
            file1 << endl;
        }
        cout << "\nGame saved in file1...";
        file1.close();
        return true;
    }

    else if (iss_empty(file2_2))
    {
        file2.open("game2.txt", ios::out);
        file2 << moves;
        file2 << endl;
        for (int i = 0; i < SIZE1; i++)
        {
            for (int j = 0; j < SIZE1; j++)
            {
                file2 << arr[i][j] << " ";
            }
            file2 << endl;

        }
        cout << "\nGame saved in file2...";
        file2.close();
        return true;
    }
    else if (iss_empty(file3_3))
    {
        file3.open("game3.txt", ios::out);
        file3 << moves;
        file3 << endl;
        for (int i = 0; i < SIZE1; i++)
        {
            for (int j = 0; j < SIZE1; j++)
            {
                file3 << arr[i][j] << " ";
            }
            file3 << endl;
        }
        cout << "\nGame saved in file3...";
        return true;
        file3.close();
        file1_1.close();
        file2_2.close();
        file3_3.close();
    }
    else
    {
        cout << "\nGame cannot be saved... \nAtleast 1 File Must be Emptied Before Any New Game gets Saved.." << endl;
        return false;
        system("pause");
    }

}

void Del(int p_arr[][SIZE1])
{
    int ans, flag_1, flag_2, flag_3;
    cout << "\nDelete Game...";
    ifstream File1, File2, File3;
    ofstream File1_1, File2_2, File3_3;
    File1.open("game1.txt");
    File2.open("game2.txt");
    File3.open("game3.txt");
    if (!(iss_empty(File1)) || !(iss_empty(File2)) || !(iss_empty(File3)))
    {
        cout << " ";
        flag_1 = (!iss_empty(File1));
        flag_2 = (!iss_empty(File2));
        flag_3 = (!iss_empty(File3));
        if (flag_1)
        {
            cout << "\n1-File1";
        }
        cout << "  ";
        if (flag_2)
        {
            cout << "\n2-File2";
        }
        cout << " ";
        if (flag_3)
        {
            cout << "\n3-File3";
        }
        File1.close();
        File2.close();
        File3.close();

        int ak = 0;
        while (!ak)
        {
            cout << "\nEnter file num to Delete: ";
            cin >> ans;
            while (cin.fail())
            {

                cout << "\nInvalid Input...";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> ans;
            }
            switch (ans)
            {
            case 1:
            {
                if (flag_1)
                {
                    ak = 1;
                    File1_1.open("game1.txt", ios::out | ios::trunc);
                    File1_1.close();
                    cout << "\nGame Stored in File-1 deleted Successfully";

                }
                else
                {
                    cout << "\n File-1 Does not Exists";
                    system("pause");
                }
                break;

            }
            case 2:
            {
                if (flag_2)
                {
                    ak = 1;
                    File2_2.open("game2.txt", ios::out | ios::trunc);
                    File2_2.close();
                    cout << "\nGame Stored in File-2 deleted Successfully";
                }
                else
                {
                    cout << "\n File-2 Does not Exists";

                }
                break;

            }
            case 3:
            {
                if (flag_3)
                {
                    ak = 1;
                    File3_3.open("game3.txt", ios::out | ios::trunc);
                    File3_3.close();
                    cout << "\nGame Stored in File-3 deleted Successfully";
                }
                else
                {
                    cout << "\n File-3 Does not Exists";
                }
                break;

            }
            default:
            {
                cout << "\n Invalid Choice...";
                break;
            }
            }

        }

    }
    else
    {
        cout << "\nNo File Exists..";

    }
    int anss;
    cout << "\nEnter 0 to Go Back to Menu, Enter 1 to Exit...";
    cin >> anss;
    while (cin.fail() || (anss != 1 && anss != 0))
    {
        cout << "\nInvalid Input.. Enter 0 to Go Back to Menu, Enter 1 to Exit...";
        cin.clear();
        cin.ignore(100, '\n');
        cin >> anss;
    }
    if (anss == 0)
    {
        mainmenu(p_arr);
    }

}

bool load(int& moves, int new_arr[][SIZE1], int p_arr[][SIZE1])
{
    int ans, flag_1, flag_2, flag_3;
    cout << "\nLoad Game...";
    ifstream File1, File2, File3;
    File1.open("game1.txt");
    File2.open("game2.txt");
    File3.open("game3.txt");
    if (!(iss_empty(File1)) || !(iss_empty(File2)) || !(iss_empty(File3)))
    {
        cout << " ";
        flag_1 = (!iss_empty(File1));
        flag_2 = (!iss_empty(File2));
        flag_3 = (!iss_empty(File3));
        if (flag_1)
        {
            cout << "\n1-File1";
        }
        cout << "  ";
        if (flag_2)
        {
            cout << "\n2-File2";
        }
        cout << " ";
        if (flag_3)
        {
            cout << "\n3-File3";
        }
        File1.close();
        File2.close();
        File3.close();

        int ak = 0;
        while (!ak)
        {
            cout << "\nEnter file num to load: ";
            cin >> ans;
            while (cin.fail())
            {

                cout << "\nInvalid Input...";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> ans;
            }
            switch (ans)
            {
            case 1:
            {
                if (flag_1)
                {
                    File1.open("game1.txt");

                    File1 >> moves;
                    for (int i = 0; i < SIZE1; i++)
                    {
                        for (int j = 0; j < SIZE1; j++)
                        {
                            File1 >> new_arr[i][j];
                        }
                        ak = 1;


                    }
                    File1.close();


                }
                else
                {
                    cout << "\n File-1 Does not Exists";
                    system("pause");
                }
                break;

            }
            case 2:
            {
                if (flag_2)
                {
                    ak = 1;
                    File2.open("game2.txt");
                    File2 >> moves;
                    for (int i = 0; i < SIZE1; i++)
                    {
                        for (int j = 0; j < SIZE1; j++)
                        {
                            File2 >> new_arr[i][j];

                        }

                        cout << endl;

                    }
                    File2.close();
                }
                else
                {
                    cout << "\n File-2 Does not Exists";
                }
                break;

            }
            case 3:
            {
                if (flag_3)
                {
                    ak = 1;
                    File3.open("game3.txt");
                    File3 >> moves;
                    for (int i = 0; i < SIZE1; i++)
                    {
                        for (int j = 0; j < SIZE1; j++)
                        {
                            File3 >> new_arr[i][j];
                        }

                    }
                    File3.close();
                }
                else
                {
                    cout << "\n File-3 Does not Exists";
                }
                break;

            }
            default:
            {
                cout << "\n Invalid Choice...";
                break;
            }
            }

        }

    }
    else
    {
        int anss = 0;
        cout << "\nNo File Exists... Enter 0 to Go Back to Menu, Enter 1 to Exit...";
        cin >> anss;
        while (cin.fail() || (anss != 1 && anss != 0))
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\nInvalid Input.. Enter 0 to Go Back to Menu, Enter 1 to Exit...";
            cin >> anss;
        }
        if (anss == 0)
        {
            mainmenu(p_arr);
        }
        if (anss == 1)
        {
            return false;
        }
    }
}









void initializerr(int arr[][SIZE1], int i_a[SIZE1][SIZE1], int r, int c)
{

    system("cls");

    int b;
    if (r <= 2 && r >= 0 && c >= 0 && c <= 2)
    {
        b = 1;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }

    }
    if (r <= 2 && r >= 0 && c > 2 && c <= 5)
    {
        b = 2;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 3; j <= 5; j++)
            {

                arr[i][j] = i_a[i][j];

            }
        }


    }
    if (r <= 2 && r >= 0 && c > 5 && c <= 8)
    {
        b = 3;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }

    }
    //pt2
    if (r <= 5 && r > 2 && c >= 0 && c <= 2)
    {
        b = 4;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }

    }
    if (r <= 5 && r > 2 && c > 2 && c <= 5)
    {
        b = 5;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 3; j <= 5; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }


    }
    if (r <= 5 && r > 2 && c > 5 && c <= 8)
    {
        b = 6;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }

    }
    //pt3
    if (r <= 8 && r > 5 && c >= 0 && c <= 2)
    {
        b = 7;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }


    }
    if (r <= 8 && r > 5 && c > 2 && c <= 5)
    {
        b = 8;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 3; j <= 5; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }

    }
    if (r <= 8 && r > 5 && c > 5 && c <= 8)
    {
        b = 9;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                arr[i][j] = i_a[i][j];
            }
        }


    }






    printArr(arr, i_a);
    input(arr, i_a);
}
bool solve(int arr[][SIZE1], int r, int c)
{
    int b = -1;
    for (int i = 1; i <= SIZE1; i++)
    {
        if (!checkColumn(arr, c, i) && !checkRow(arr, r, i) && !checkboxx(arr, r, c, i))
        {
            b = 0;
        }
    }
    if (b == 0)
    {
        return true;// solution possible...
    }
    return false;
}
bool result(int arr[][SIZE1])
{
    for (int i = 0; i < SIZE1; i++)
    {
        for (int j = 0; j < SIZE1; j++)
        {
            if (arr[i][j] == 0)
            {
                return false; // table has not been solved
            }
        }
    }
    return true;

}
bool checkColumn(int arr[][SIZE1], int c, int value)
{
    for (int r = 0; r < SIZE1; r++)
    {
        if (arr[r][c] == value)
        {
            return true;

        }


    }

    return false;
}
void printArr(int arr[][SIZE1], int i_a[][SIZE1])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    int p = 0;
    cout << "\n";
    cout << "\n";
    cout << "\t";
    cout << "   ";
    int z = 9;
    SetConsoleTextAttribute(h, z);
    for (int i = 1; i <= SIZE1; i++) {
        cout << i << " ";
        if (i == 3)
        {
            cout << "  ";
        }
        if (i == 6) {
            cout << "  ";
        }
    }
    cout << "\n";
    cout << "\t";
    //cout << " ";
    //cout << "\t";
    for (int i = 0; i < 25; i++)
    {

        int z = 9;
        SetConsoleTextAttribute(h, z);

        cout << "_";

    }
    cout << endl;
    cout << "\t";
    for (int i = 0; i < 25; i++)
    {
        int z = 7;
        SetConsoleTextAttribute(h, z);
        cout << "-";


    }
    cout << "\n";

    for (int i = 0; i < SIZE1; i++)
    {
        z = 9;
        SetConsoleTextAttribute(h, z);
        cout << "\t" << i + 1;

        cout << "| ";
        for (int j = 0; j < 9; j++)
        {
            int z;
            if (i_a[i][j] == 0) {
                z = 6;
            }
            else {
                z = 15;
            }

            SetConsoleTextAttribute(h, z);



            cout << arr[i][j] << " ";


            /* if (j == 3||j==4||j==0||j==1||j==6||j==7) {

                     cout << "|";


             }*/



            if (j == 2 || j == 5 || j == 8)
            {
                z = 9;
                SetConsoleTextAttribute(h, z);

                cout << "| ";
            }
        }
        cout << endl;
        //cout << "\t";

        /*if (i == 0||i==1||i==3||i==4||i==6||i==7) {

            for (int i = 0; i < 25; i++) {
                cout << "-";
            }
            cout << "\n";
        }
        */


        ////cout << "\t";


       /* cout << endl;*/
        ///*if (i == 5 || i == 8)
        //{
        //    cout << "\n";
        //}*/
        if (i == 2 || i == 5 || i == 8)
        {
            cout << "\t";
            /* for (int i = 0; i < 26; i++)
             {
                 int z = 9;
                 SetConsoleTextAttribute(h, z);

                 cout << "=";

             }
             cout << endl;*/
            for (int i = 0; i <= 25; i++)
            {

                int z = 9;
                SetConsoleTextAttribute(h, z);

                cout << "_";

            }
            cout << endl;
            cout << "\t";
            for (int i = 0; i < 25; i++)
            {
                int z = 7;
                SetConsoleTextAttribute(h, z);
                cout << "-";


            }
            cout << "\n";

        }

    }
}
bool checkRow(int arr[][SIZE1], int r, int value)
{
    for (int c = 0; c < SIZE1; c++)
    {
        if (arr[r][c] == value)
        {
            return true;

        }


    }

    return false;
}
bool checkboxx(int arr[][SIZE1], int r, int c, int value)
{
    int b;
    if (r <= 2 && r >= 0 && c >= 0 && c <= 2)
    {
        b = 1;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 2 && r >= 0 && c > 2 && c <= 5)
    {
        b = 2;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 3; j <= 5; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 2 && r >= 0 && c > 5 && c <= 8)
    {
        b = 3;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    //pt2
    if (r <= 5 && r > 2 && c >= 0 && c <= 2)
    {
        b = 4;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 5 && r > 2 && c > 2 && c <= 5)
    {
        b = 5;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 3; j <= 5; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 5 && r > 2 && c > 5 && c <= 8)
    {
        b = 6;
        for (int i = 3; i <= 5; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    //pt3
    if (r <= 8 && r > 5 && c >= 0 && c <= 2)
    {
        b = 7;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 8 && r > 5 && c > 2 && c <= 5)
    {
        b = 8;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 3; j <= 5; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    if (r <= 8 && r > 5 && c > 5 && c <= 8)
    {
        b = 9;
        for (int i = 6; i <= 8; i++)
        {
            for (int j = 6; j <= 8; j++)
            {
                if (value == arr[i][j])
                {
                    return true;
                }
            }
        }
        return false;

    }
    return false;





}
void input(int arr[][SIZE1], int i_a[SIZE1][SIZE1], int moves)
{
    int r, c, temp, temp1;


    while (!(result(arr)))
    {

        cout << "\nMoves: " << moves << " \nFor Input...";
        cout << "\nEnter Row Number:";
        cin >> r;
        r = r - 1;
        while (r > 9 || r < 0 || cin.fail())
        {
            cout << "Invalid Input...\n Enter Row Number Again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> r;
        }
        cout << "\nEnter Column Number:";
        cin >> c;
        c = c - 1;
        while (c > 9 || c < 0 || cin.fail())
        {

            cout << "Invalid Input...\n Enter Column Number Again: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> c;
        }
        if (i_a[r][c] == 0)
        {
            if (solve(arr, r, c))
            {
                cout << "\nEnter Value for [" << r + 1 << "][" << c + 1 << "]:";
                cin >> temp;
                moves++;
                while (checkColumn(arr, c, temp) || checkRow(arr, r, temp) || checkboxx(arr, r, c, temp) || temp > 9 || temp <= 0)
                {

                    cout << "\nMoves: " << moves;
                    cout << "\nInvalid input...\nEnter Value for [" << r + 1 << "][" << c + 1 << "]:";
                    cin.clear();
                    cin.ignore(100, '\n');
                    cin >> temp;
                    moves++;


                }
                arr[r][c] = temp;
                system("cls");
                printArr(arr, i_a);

            }
            else
            {
                int n;
                cout << "\nThis Current form of Sudoku Table is impossible to solve...\n Enter 1 to reset the current block, enter 2 to continue: ";
                cin >> n;
                while (n != 1 && n != 2)
                {
                    cout << "Invalid Input...\n Enter 1 to reset this block, enter 2 to continue:";
                    cin >> n;
                }

                if (n == 1)
                {
                    initializerr(arr, i_a, r, c);
                }
                else if (n == 2)
                {
                    system("cls");
                    printArr(arr, i_a);
                    //continue...
                }


            }


        }
        else
        {
            cout << "\nIndex is Non Editable...";
        }
        int ans;
        cout << "\nEnter -1 to Save or Enter 0 to Continue...";
        cin >> ans;
        while ((ans != -1 && ans != 0) || cin.fail())
        {
            cout << "\n Invalid input...\n Enter Again:";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> ans;
        }
        int flag;
        if (ans == -1)
        {
            flag = save(moves, arr);
            if (flag)
            {
                break;
            }


        }
        else
        {
            system("cls");
            printArr(arr, i_a);
        }




    }
    if (result(arr))
    {
        cout << "\n Boi, You Did it....";
        cout << "\nMoves:" << moves;
    }
    cout << "\n Exiting......";

}


int main() {

    int i_a[SIZE1][SIZE1] = { { 0, 5, 0, 2, 0, 0, 0, 9, 8 },
    { 0, 0, 9, 0, 0, 0, 0, 0, 0 },
    { 6, 4, 0, 0, 7, 0, 0, 0, 0 },
    { 3, 0, 1, 0, 0, 6, 0, 0, 7 },
    { 2, 0, 0, 3, 0, 0, 9, 0, 0 },
    { 0, 0, 5, 0, 0, 1, 3, 0, 6 },
    { 5, 0, 0, 0, 0, 2, 0, 1, 9 },
    { 0, 9, 0, 8, 0, 0, 0, 3, 0 },
    { 0, 0, 8, 0, 0, 0, 0, 0, 0 } };
    int n = mainmenu(i_a);
}
