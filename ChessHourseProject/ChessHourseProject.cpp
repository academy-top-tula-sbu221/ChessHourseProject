#include <iostream>
#include <iomanip>

using namespace std;

const int SizeDesk{ 8 };
const int SizeDiff{ 8 };

struct Cell
{
    int row;
    int col;
};

Cell diff[8]{ {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };

int desk[SizeDesk][SizeDesk]{};

int CellValue(Cell cell);
int MinValueCell(int values[], int size);
bool IsDesk(int row, int col);
bool IsStep(int values[], int size);
void PrintDesk();

int main()
{
    int rowCurr{ 3 };
    int colCurr{ 4 };
    int step{};

    desk[rowCurr][colCurr] = ++step;

    while (1)
    {
        std::cout << "\n";
        PrintDesk();

        int values[8]{};

        for (int i = 0; i < SizeDiff; i++)
        {
            Cell dcell;
            dcell.row = rowCurr + diff[i].row;
            dcell.col = colCurr + diff[i].col;
            if(IsDesk(dcell.row, dcell.col) && !desk[dcell.row][dcell.col])
                values[i] = CellValue(dcell);
        }

        if (!IsStep(values, SizeDiff))
        {
            //desk[rowCurr][colCurr] = ++step;
            break;
        }
            

        int indexDiff = MinValueCell(values, SizeDiff);

        rowCurr += diff[indexDiff].row;
        colCurr += diff[indexDiff].col;

        desk[rowCurr][colCurr] = ++step;

        //if (step == 64) break;
    }
    std::cout << "\n";
    PrintDesk();
}

int CellValue(Cell cell)
{
    int value{};
    for (int d = 0; d < SizeDesk; d++)
    {
        int drow = cell.row + diff[d].row;
        int dcol = cell.col + diff[d].col;
        
        if (!IsDesk(drow, dcol))
            continue;

        if (!desk[drow][dcol])
            value++;
    }
    return value;
}

int MinValueCell(int values[], int size)
{
    int index{};
    for(int s = 0; s < size; s++)
        if (values[s])
        {
            index = s;
            break;
        }
            
    for (int s = index + 1; s < size; s++)
        if (values[s] != 0 && values[index] > values[s])
            index = s;
    return index;
}

bool IsDesk(int row, int col)
{
    return row >= 0 && row < SizeDesk && col >= 0 && col < SizeDesk;
}

bool IsStep(int values[], int size)
{
    bool isStep{ false };
    for (int i = 0; i < size; i++)
        if (values[i])
            isStep = true;
    return isStep;
}

void PrintDesk()
{
    for (int r = 0; r < SizeDesk; r++)
    {
        for (int c = 0; c < SizeDesk; c++)
            cout << setw(3) << desk[r][c];
        cout << "\n";
    }
}