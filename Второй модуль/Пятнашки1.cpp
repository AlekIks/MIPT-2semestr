#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

/*
Matrix will be saved as integer.
Numbers of cells:
0 1 2 3
4 5 6 7
8 9 10 11
12 13 14 15

Grade in matrix:
aabbccddeeffgghhiijjkkllmmnnoopp ~ 10^32

Number of cells:
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
a b c d e f g h i j  k  l  m  n  o  p

two sixteen-digit (or fifteen) number:
1) aabbccddeeffgghh
2) iijjkkllmmnnoopp
*/

//////////
unsigned long long power (int a, int b) {
    unsigned long long t = 1;
    for (int i = 0; i < b; i ++) {
        t *= a;
    }
    return t;
}

////////////////////////////////////////////////
//Matrix

struct Matrix {
    Matrix();
    Matrix(unsigned long long f, unsigned long long s);
    unsigned long long first_group_of_cells;
    unsigned long long second_group_of_cells;
};

Matrix::Matrix() :
        first_group_of_cells(0),
        second_group_of_cells(0)
{
};
Matrix::Matrix(unsigned long long f, unsigned long long s) :
        first_group_of_cells(f),
        second_group_of_cells(s)
{
};

bool operator==(Matrix first, Matrix second) {
    return first.first_group_of_cells == second.first_group_of_cells && first.second_group_of_cells == second.second_group_of_cells;
};



namespace std {
    template<>
    class hash<Matrix> {
    public:
        size_t operator()(const Matrix &mat) const {
            size_t h1 = hash<unsigned long long>()(mat.first_group_of_cells);
            size_t h2 = hash<unsigned long long>()(mat.second_group_of_cells);
            return h1 ^ (h2 << 1);
        }
    };
}

//////////////////////////////////////
//CONFIGURATION

class Configuration {
public:
    Configuration ();
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
    Matrix getMatrix() const;
    //set digit to the cell by number
    void setDigit(int number, int digit);

    //know the number of cell with 0
    int getNullPosition() const;

    //add a point to way that says how to reach this configuration from start
    void addToWayToComeThis (char a);
    //know the way that says how to reach this configuration from start
    string wayToComeToThis () const;

private:
    //field itself
    Matrix matrix;
    //U = UP, D = DOWN, L = LEFT, R = RIGHT
    string move_to_come_to_this;
    //necessary not to look for a empty cell
    int null_position;
};

/******************************************/
//CONSTRUCTORS

Configuration::Configuration() :
        matrix (0, 0),
        move_to_come_to_this (""),
        null_position (0)
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
    if (number < 8) {
        int loc_number = 7 - number;
        return static_cast<int>(matrix.first_group_of_cells / power(10, loc_number * 2) % 100);
    }
    int loc_number = 15 - number;
    return static_cast<int>(matrix.second_group_of_cells / power(10, loc_number * 2) % 100);
};

void Configuration::setDigit(int number, int digit) {
    if (digit == 0)
        null_position = number;

    if (number < 8) {
        unsigned long long stepen = power(10, (7 - number) * 2);
        unsigned long long rightnumbers = matrix.first_group_of_cells % stepen;
        unsigned long long leftnumbers = matrix.first_group_of_cells / (stepen * 100);

        leftnumbers *= 100;
        leftnumbers += digit;
        leftnumbers *= stepen;
        leftnumbers += rightnumbers;
        matrix.first_group_of_cells = leftnumbers;
    }
    else {
        unsigned long long stepen = power(10, (15 - number) * 2);
        unsigned long long rightnumbers = matrix.second_group_of_cells % stepen;
        unsigned long long leftnumbers = matrix.second_group_of_cells / (stepen * 100);

        leftnumbers *= 100;
        leftnumbers += digit;
        leftnumbers *= stepen;
        leftnumbers += rightnumbers;
        matrix.second_group_of_cells = leftnumbers;
    }
};

void Configuration::swapDigits(int number1, int number2) {
    int digit1 = getDigit(number1);
    int digit2 = getDigit(number2);
    setDigit(number1, digit2);
    setDigit(number2, digit1);
};

Matrix Configuration::getMatrix() const {
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

bool canReachEnd (Configuration* conf){
    int ans = 0;
    for (int i = 0; i < 16; i ++) {
    	int loc_i = conf -> getDigit(i);
        for (int j = i + 1; j < 16; j ++) {
        	int loc_j = conf -> getDigit(j);
            if (loc_i != 0 && loc_j != 0 && loc_i > loc_j)
                ans ++;
    	}
    }
    if (ans % 2 != (conf -> getNullPosition() / 4) % 2)
    	return true;
    return false;
}

///////////////
//GO TO THE NECESSARY WAY, CHECK IS IT THE END CONFIGURATION
bool goAndCheck (unordered_map <Matrix, bool>& used, queue <Configuration>& q, Configuration* next, char a) {
    if (!used[next -> getMatrix()] && canReachEnd(next)) {
        next -> addToWayToComeThis(a);
        used[next -> getMatrix()] = true;
        q.push(*next);
    }
    return (next -> getMatrix().first_group_of_cells == 102030405060708 && next -> getMatrix().second_group_of_cells == 910111213141500);
}


///////////////
//RETURN THE WAY TO "END" CONFIGURATION - 123456780
string wayToLastConfig (Configuration start) {
    queue <Configuration> q;
    unordered_map <Matrix, bool> used;

    if (start.getMatrix().first_group_of_cells == 102030405060708 && start.getMatrix().second_group_of_cells == 910111213141500)
        return "";

    q.push (start);
    while (!q.empty()) {
        Configuration loc = q.front();
        q.pop();
        int loc_null = loc.getNullPosition();
		
		//cout << loc.getMatrix().first_group_of_cells << endl << loc.getMatrix().second_group_of_cells << endl << endl;

        switch(loc_null) {
            case 0:
            {
                Configuration next01 = loc;
                //0 goes from position 0 to position 1
                next01.swapDigits(0, 1);
                if (goAndCheck(used, q, &next01, 'L')) {
                    return next01.wayToComeToThis();
                }
                Configuration next04 = loc;
                //0 goes from position 0 to position 4
                next04.swapDigits(0, 4);
                if (goAndCheck(used, q, &next04, 'U')) {
                    return next04.wayToComeToThis();
                }
                break;
            }
            case 1:
            {
                Configuration next10 = loc;
                //0 goes from position 1 to position 0
                next10.swapDigits(1, 0);
                if (goAndCheck(used, q, &next10, 'R')) {
                    return next10.wayToComeToThis();
                }
                //0 goes from position 1 to position 2
                Configuration next12 = loc;
                next12.swapDigits(1, 2);
                if (goAndCheck(used, q, &next12, 'L')) {
                    return next12.wayToComeToThis();
                }
                //0 goes from position 1 to position 5
                Configuration next15 = loc;
                next15.swapDigits(1, 5);
                if (goAndCheck(used, q, &next15, 'U')) {
                    return next15.wayToComeToThis();
                }
                break;;
            }
            case 2:
            {
                //0 goes from position 2 to position 1
                Configuration next21 = loc;
                next21.swapDigits(2, 1);
                if (goAndCheck(used, q, &next21, 'R')) {
                    return next21.wayToComeToThis();
                }
                //0 goes from position 2 to position 6
                Configuration next26 = loc;
                next26.swapDigits(2, 6);
                if (goAndCheck(used, q, &next26, 'U')) {
                    return next26.wayToComeToThis();
                }
                //0 goes from position 2 to position 3
                Configuration next23 = loc;
                next23.swapDigits(2, 3);
                if (goAndCheck(used, q, &next23, 'L')) {
                    return next23.wayToComeToThis();
                }
                break;
            }
            case 3:
            {
                //0 goes from position 3 to position 2
                Configuration next32 = loc;
                next32.swapDigits(3, 2);
                if (goAndCheck(used, q, &next32, 'R')) {
                    return next32.wayToComeToThis();
                }
                //0 goes from position 3 to position 7
                Configuration next37 = loc;
                next37.swapDigits(3, 7);
                if (goAndCheck(used, q, &next37, 'U')) {
                    return next37.wayToComeToThis();
                }
                break;
            }
            case 4:
            {
                //0 goes from position 4 to position 0
                Configuration next40 = loc;
                next40.swapDigits(4, 0);
                if (goAndCheck(used, q, &next40, 'D')) {
                    return next40.wayToComeToThis();
                }
                //0 goes from position 4 to position 5
                Configuration next45 = loc;
                next45.swapDigits(4, 5);
                if (goAndCheck(used, q, &next45, 'L')) {
                    return next45.wayToComeToThis();
                }
                //0 goes from position 4 to position 8
                Configuration next48 = loc;
                next48.swapDigits(4, 8);
                if (goAndCheck(used, q, &next48, 'U')) {
                    return next48.wayToComeToThis();
                }
                break;
            }
            case 5:
            {
                //0 goes from position 5 to position 2
                Configuration next51 = loc;
                next51.swapDigits(5, 1);
                if (goAndCheck(used, q, &next51, 'D')) {
                    return next51.wayToComeToThis();
                }
                //0 goes from position 5 to position 4
                Configuration next54 = loc;
                next54.swapDigits(5, 4);
                if (goAndCheck(used, q, &next54, 'R')) {
                    return next54.wayToComeToThis();
                }
                //0 goes from position 5 to position 6
                Configuration next56 = loc;
                next56.swapDigits(5, 6);
                if (goAndCheck(used, q, &next56, 'L')) {
                    return next56.wayToComeToThis();
                }
                //0 goes from position 5 to position 9
                Configuration next59 = loc;
                next59.swapDigits(5, 9);
                if (goAndCheck(used, q, &next59, 'U')) {
                    return next59.wayToComeToThis();
                }
                break;
            }
            case 6: {
                //0 goes from position 6 to position 2
                Configuration next62 = loc;
                next62.swapDigits(6, 2);
                if (goAndCheck(used, q, &next62, 'D')) {
                    return next62.wayToComeToThis();
                }
                //0 goes from position 6 to position 5
                Configuration next65 = loc;
                next65.swapDigits(6, 5);
                if (goAndCheck(used, q, &next65, 'R')) {
                    return next65.wayToComeToThis();
                }
                //0 goes from position 6 to position 7
                Configuration next67 = loc;
                next67.swapDigits(6, 7);
                if (goAndCheck(used, q, &next67, 'L')) {
                    return next67.wayToComeToThis();
                }
                //0 goes from position 6 to position 10
                Configuration next610 = loc;
                next610.swapDigits(6, 10);
                if (goAndCheck(used, q, &next610, 'U')) {
                    return next610.wayToComeToThis();
                }
                break;
            }
            case 7:
            {
                //0 goes from position 7 to position 6
                Configuration next76 = loc;
                next76.swapDigits(7, 6);
                if (goAndCheck(used, q, &next76, 'R')) {
                    return next76.wayToComeToThis();
                }
                //0 goes from position 7 to position 3
                Configuration next73 = loc;
                next73.swapDigits(7, 3);
                if (goAndCheck(used, q, &next73, 'D')) {
                    return next73.wayToComeToThis();
                }
                //0 goes from position 7 to position 11
                Configuration next711 = loc;
                next711.swapDigits(7, 11);
                if (goAndCheck(used, q, &next711, 'U')) {
                    return next711.wayToComeToThis();
                }
                break;
            }
            case 8:
            {
                //0 goes from position 8 to position 4
                Configuration next84 = loc;
                next84.swapDigits(8, 4);
                if (goAndCheck(used, q, &next84, 'D')) {
                    return next84.wayToComeToThis();
                }
                //0 goes from position 8 to position 9
                Configuration next89 = loc;
                next89.swapDigits(8, 9);
                if (goAndCheck(used, q, &next89, 'L')) {
                    return next89.wayToComeToThis();
                }
                //0 goes from position 8 to position 12
                Configuration next812 = loc;
                next812.swapDigits(8, 12);
                if (goAndCheck(used, q, &next812, 'U')) {
                    return next812.wayToComeToThis();
                }
                break;
            }
            case 9:
            {
                //0 goes from position 9 to position 5
                Configuration next95 = loc;
                next95.swapDigits(9, 5);
                if (goAndCheck(used, q, &next95, 'D')) {
                    return next95.wayToComeToThis();
                }
                //0 goes from position 9 to position 8
                Configuration next98 = loc;
                next98.swapDigits(9, 8);
                if (goAndCheck(used, q, &next98, 'R')) {
                    return next98.wayToComeToThis();
                }
                //0 goes from position 9 to position 13
                Configuration next913 = loc;
                next913.swapDigits(9, 13);
                if (goAndCheck(used, q, &next913, 'U')) {
                    return next913.wayToComeToThis();
                }
                //0 goes from position 9 to position 10
                Configuration next910 = loc;
                next910.swapDigits(9, 10);
                if (goAndCheck(used, q, &next910, 'L')) {
                    return next910.wayToComeToThis();
                }
                break;
            }
            case 10:
            {
                //0 goes from position 10 to position 6
                Configuration next106 = loc;
                next106.swapDigits(10, 6);
                if (goAndCheck(used, q, &next106, 'D')) {
                    return next106.wayToComeToThis();
                }
                //0 goes from position 10 to position 9
                Configuration next109 = loc;
                next109.swapDigits(10, 9);
                if (goAndCheck(used, q, &next109, 'R')) {
                    return next109.wayToComeToThis();
                }
                //0 goes from position 10 to position 14
                Configuration next1014 = loc;
                next1014.swapDigits(10, 14);
                if (goAndCheck(used, q, &next1014, 'U')) {
                    return next1014.wayToComeToThis();
                }
                //0 goes from position 10 to position 11
                Configuration next1011 = loc;
                next1011.swapDigits(10, 11);
                if (goAndCheck(used, q, &next1011, 'L')) {
                    return next1011.wayToComeToThis();
                }
                break;
            }
            case 11:
            {
                //0 goes from position 11 to position 7
                Configuration next117 = loc;
                next117.swapDigits(11, 7);
                if (goAndCheck(used, q, &next117, 'D')) {
                    return next117.wayToComeToThis();
                }
                //0 goes from position 11 to position 10
                Configuration next1110 = loc;
                next1110.swapDigits(11, 10);
                if (goAndCheck(used, q, &next1110, 'R')) {
                    return next1110.wayToComeToThis();
                }
                //0 goes from position 11 to position 15
                Configuration next1115 = loc;
                next1115.swapDigits(11, 15);
                if (goAndCheck(used, q, &next1115, 'U')) {
                    return next1115.wayToComeToThis();
                }
                break;
            }
            case 12:
            {
                //0 goes from position 12 to position 8
                Configuration next128 = loc;
                next128.swapDigits(12, 8);
                if (goAndCheck(used, q, &next128, 'D')) {
                    return next128.wayToComeToThis();
                }
                //0 goes from position 12 to position 13
                Configuration next1213 = loc;
                next1213.swapDigits(12, 13);
                if (goAndCheck(used, q, &next1213, 'L')) {
                    return next1213.wayToComeToThis();
                }
                break;
            }
            case 13:
            {
                //0 goes from position 13 to position 12
                Configuration next1312 = loc;
                next1312.swapDigits(13, 12);
                if (goAndCheck(used, q, &next1312, 'R')) {
                    return next1312.wayToComeToThis();
                }
                //0 goes from position 13 to position 9
                Configuration next139 = loc;
                next139.swapDigits(13, 9);
                if (goAndCheck(used, q, &next139, 'D')) {
                    return next139.wayToComeToThis();
                }
                //0 goes from position 13 to position 14
                Configuration next1314 = loc;
                next1314.swapDigits(13, 14);
                if (goAndCheck(used, q, &next1314, 'L')) {
                    return next1314.wayToComeToThis();
                }
                break;
            }
            case 14:
            {
                //0 goes from position 14 to position 10
                Configuration next1410 = loc;
                next1410.swapDigits(14, 10);
                if (goAndCheck(used, q, &next1410, 'D')) {
                    return next1410.wayToComeToThis();
                }
                //0 goes from position 14 to position 13
                Configuration next1413 = loc;
                next1413.swapDigits(14, 13);
                if (goAndCheck(used, q, &next1413, 'R')) {
                    return next1413.wayToComeToThis();
                }
                //0 goes from position 14 to position 15
                Configuration next1415 = loc;
                next1415.swapDigits(14, 15);
                if (goAndCheck(used, q, &next1415, 'L')) {
                    return next1415.wayToComeToThis();
                }
                break;
            }
            case 15:
            {
                //0 goes from position 15 to position 11
                Configuration next1511 = loc;
                next1511.swapDigits(15, 11);
                if (goAndCheck(used, q, &next1511, 'D')) {
                    return next1511.wayToComeToThis();
                }
                //0 goes from position 15 to position 14
                Configuration next1514 = loc;
                next1514.swapDigits(15, 14);
                if (goAndCheck(used, q, &next1514, 'R')) {
                    return next1514.wayToComeToThis();
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
	freopen("8test.txt", "r", stdin);
    int a = 0;

    Configuration start;
    for (int i = 0; i < 16; i ++) {
        cin >> a;
        start.setDigit(i, a);
    }
    string s = wayToLastConfig (start);
    if (s != "-1")
        cout << s.length() << endl;
    cout << s;
    return 0;
}

