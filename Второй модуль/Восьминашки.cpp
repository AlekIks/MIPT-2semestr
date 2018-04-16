/*
"¬осьминашки" - упрощенный вариант известной головоломки "ѕ€тнашки". 
¬осемь кост€шек, пронумерованных от 1 до 8, расставлены по €чейкам игровой доски 3 на 3, 
одна €чейка при этом остаетс€ пустой. «а один ход разрешаетс€ передвинуть одну из кост€шек, 
расположенных р€дом с пустой €чейкой, на свободное место. ÷ель игры - дл€ заданной начальной 
конфигурации игровой доски за минимальное число ходов получить выигрышную конфигурацию (пуста€ €чейка обозначена нулем):
1 2 3
4 5 6
7 8 0

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

//////////////////////////////////////
//CONFIGURATION
/*
Matrix will be saved as integer.
Numbers of cells:
0 1 2
3 4 5
6 7 8

Grade in matrix:
0 1 2 3 4 5 6 7 8
 nine-digit (or eight) number
*/

class Configuration {
public:
    Configuration ();
    Configuration (int mat, int null_pos);
    ~Configuration();
    //copy constructor
    Configuration (const Configuration& other);

    //operator: smth equals smth (prisvayivaniya)
    Configuration& operator= (const Configuration& other);


    //know digit on the cell by its number
    int getDigit(int number) const;
    //swap digits on cells
    void swapDigits(int number1, int number2);
    //know the situation on field
    int getMatrix() const;

    //know the number of cell with 0
    int getNullPosition() const;

    //add a point to way that says how to reach this configuration from start
    void addToWayToComeThis (char a);
    //know the way that says how to reach this configuration from start
    string wayToComeToThis () const;

private:
    //set digit to the cell by number
    void setDigit(int number, int digit);
    //field itself
    int matrix;
    //U = UP, D = DOWN, L = LEFT, R = RIGHT
    string move_to_come_to_this;
    //necessary not to look for a empty cell
    int null_position;
};

/******************************************/
//CONSTRUCTORS

Configuration::Configuration() :
        matrix (0),
        move_to_come_to_this (""),
        null_position (0)
{
};

Configuration::Configuration(int mat, int null_pos) :
        matrix (mat),
        move_to_come_to_this (""),
        null_position (null_pos)
{
};
Configuration::~Configuration() {};


Configuration::Configuration(const Configuration &other) :
    matrix (other.matrix),
    move_to_come_to_this (other.move_to_come_to_this),
    null_position (other.null_position)
{
};


Configuration& Configuration::operator=(const Configuration &other) {
    matrix = other.matrix;
    null_position = other.null_position;
    move_to_come_to_this = other.move_to_come_to_this;
    return *this;
};
/******************************************/

int Configuration::getDigit(int number) const {
    int loc_number = 8 - number;
    return static_cast<int>(matrix / pow(10, loc_number)) % 10;
};

void Configuration::setDigit(int number, int digit) {
    if (digit == 0)
        null_position = number;


    int stepen = static_cast<int>(pow(10, 8 - number));
    int rightnumbers = matrix % stepen;
    int leftnumbers = matrix / (stepen * 10);

    leftnumbers *= 10;
    leftnumbers += digit;
    leftnumbers *= stepen;
    leftnumbers += rightnumbers;
    matrix = leftnumbers;
};

void Configuration::swapDigits(int number1, int number2) {
    int digit1 = getDigit(number1);
    int digit2 = getDigit(number2);
    setDigit(number1, digit2);
    setDigit(number2, digit1);
};

int Configuration::getMatrix() const {
    return matrix;
};

int Configuration::getNullPosition() const {
    return null_position;
};

void Configuration::addToWayToComeThis(char a) {
    move_to_come_to_this += a;
};
string Configuration::wayToComeToThis() const {
    return move_to_come_to_this;
};
//////////////////////////////////////
//MAIN

///////////////
//GO TO THE NECESSARY WAY, CHECK IS IT THE END CONFIGURATION
bool goAndCheck (unordered_map <int, bool>& used, queue <Configuration>& q, Configuration* next, char a) {
    if (!used[next -> getMatrix()]) {
        next -> addToWayToComeThis(a);
        used[next -> getMatrix()] = true;
        q.push(*next);
    }
    return next -> getMatrix() == 123456780;
}

///////////////
//RETURN THE WAY TO "END" CONFIGURATION - 123456780
string wayToLastConfig (Configuration start) {
    queue <Configuration> q;
    unordered_map <int, bool> used;

    if (start.getMatrix() == 123456780)
        return "";

    q.push (start);
    while (!q.empty()) {
        Configuration loc = q.front();
        q.pop();
        int loc_null = loc.getNullPosition();
        
        
        switch(loc_null) {
            case 0:
            {
                Configuration next01 = loc;
                //0 goes from position 0 to position 1
                next01.swapDigits(0, 1);
                if (goAndCheck(used, q, &next01, 'R')) {
                    return next01.wayToComeToThis();
                }
                Configuration next03 = loc;
                //0 goes from position 0 to position 3
                next03.swapDigits(0, 3);
                if (goAndCheck(used, q, &next03, 'D')) {
                    return next03.wayToComeToThis();
                }
                break;
            }
            case 1:
            {
                Configuration next10 = loc;
                //0 goes from position 1 to position 0
                next10.swapDigits(1, 0);
                if (goAndCheck(used, q, &next10, 'L')) {
                    return next10.wayToComeToThis();
                }
                //0 goes from position 1 to position 2
                Configuration next12 = loc;
                next12.swapDigits(1, 2);
                if (goAndCheck(used, q, &next12, 'R')) {
                    return next12.wayToComeToThis();
                }
                //0 goes from position 1 to position 4
                Configuration next14 = loc;
                next14.swapDigits(1, 4);
                if (goAndCheck(used, q, &next14, 'D')) {
                    return next14.wayToComeToThis();
                }
                break;;
            }
            case 2:
            {
                //0 goes from position 2 to position 1
                Configuration next21 = loc;
                next21.swapDigits(2, 1);
                if (goAndCheck(used, q, &next21, 'L')) {
                    return next21.wayToComeToThis();
                }
                //0 goes from position 2 to position 5
                Configuration next25 = loc;
                next25.swapDigits(2, 5);
                if (goAndCheck(used, q, &next25, 'D')) {
                    return next25.wayToComeToThis();
                }
                break;
            }
            case 3:
            {
                //0 goes from position 3 to position 0
                Configuration next30 = loc;
                next30.swapDigits(3, 0);
                if (goAndCheck(used, q, &next30, 'U')) {
                    return next30.wayToComeToThis();
                }
                //0 goes from position 3 to position 4
                Configuration next34 = loc;
                next34.swapDigits(3, 4);
                if (goAndCheck(used, q, &next34, 'R')) {
                    return next34.wayToComeToThis();
                }
                //0 goes from position 3 to position 6
                Configuration next36 = loc;
                next36.swapDigits(3, 6);
                if (goAndCheck(used, q, &next36, 'D')) {
                    return next36.wayToComeToThis();
                }
                break;
            }
            case 4:
            {
                //0 goes from position 4 to position 1
                Configuration next41 = loc;
                next41.swapDigits(4, 1);
                if (goAndCheck(used, q, &next41, 'U')) {
                    return next41.wayToComeToThis();
                }
                //0 goes from position 4 to position 3
                Configuration next43 = loc;
                next43.swapDigits(4, 3);
                if (goAndCheck(used, q, &next43, 'L')) {
                    return next43.wayToComeToThis();
                }
                //0 goes from position 4 to position 5
                Configuration next45 = loc;
                next45.swapDigits(4, 5);
                if (goAndCheck(used, q, &next45, 'R')) {
                    return next45.wayToComeToThis();
                }
                //0 goes from position 4 to position 7
                Configuration next47 = loc;
                next47.swapDigits(4, 7);
                if (goAndCheck(used, q, &next47, 'D')) {
                    return next47.wayToComeToThis();
                }
                break;
            }
            case 5:
            {
                //0 goes from position 5 to position 2
                Configuration next52 = loc;
                next52.swapDigits(5, 2);
                if (goAndCheck(used, q, &next52, 'U')) {
                    return next52.wayToComeToThis();
                }
                //0 goes from position 5 to position 4
                Configuration next54 = loc;
                next54.swapDigits(5, 4);
                if (goAndCheck(used, q, &next54, 'L')) {
                    return next54.wayToComeToThis();
                }
                //0 goes from position 5 to position 8
                Configuration next58 = loc;
                next58.swapDigits(5, 8);
                if (goAndCheck(used, q, &next58, 'D')) {
                    return next58.wayToComeToThis();
                }
                break;
            }
            case 6: {
                //0 goes from position 6 to position 3
                Configuration next63 = loc;
                next63.swapDigits(6, 3);
                if (goAndCheck(used, q, &next63, 'U')) {
                    return next63.wayToComeToThis();
                }
                //0 goes from position 6 to position 7
                Configuration next67 = loc;
                next67.swapDigits(6, 7);
                if (goAndCheck(used, q, &next67, 'R')) {
                    return next67.wayToComeToThis();
                }
                break;
            }
            case 7:
            {
                //0 goes from position 7 to position 6
                Configuration next76 = loc;
                next76.swapDigits(7, 6);
                if (goAndCheck(used, q, &next76, 'L')) {
                    return next76.wayToComeToThis();
                }
                //0 goes from position 7 to position 4
                Configuration next74 = loc;
                next74.swapDigits(7, 4);
                if (goAndCheck(used, q, &next74, 'U')) {
                    return next74.wayToComeToThis();
                }
                //0 goes from position 7 to position 8
                Configuration next78 = loc;
                next78.swapDigits(7, 8);
                if (goAndCheck(used, q, &next78, 'R')) {
                    return next78.wayToComeToThis();
                }
                break;
            }
            case 8:
            {
                //0 goes from position 8 to position 5
                Configuration next85 = loc;
                next85.swapDigits(8, 5);
                if (goAndCheck(used, q, &next85, 'U')) {
                    return next85.wayToComeToThis();
                }
                //0 goes from position 8 to position 7
                Configuration next87 = loc;
                next87.swapDigits(8, 7);
                if (goAndCheck(used, q, &next87, 'L')) {
                    return next87.wayToComeToThis();
                }
                break;
            }
            default:
                return "-1";
        }
    }
    return "-1";
}

//////////////////////////////////////
int main() {
    int a = 0;
    int loc_matrix = 0;
    int loc_null_pos = 0;
    for (int i = 0; i < 9; i ++) {
        cin >> a;
        if (a == 0) {
            loc_null_pos = i;
        }
        loc_matrix *= 10;
        loc_matrix += a;
    }

    Configuration start (loc_matrix, loc_null_pos);

    string s = wayToLastConfig (start);
    if (s != "-1")
        cout << s.length() << endl;
    cout << s;
    return 0;
}

