//
//  Grid.h
//  sudoku
//
//  Created by Jayendra Ashutosh Jog on 7/26/15.
//  Copyright (c) 2015 Jsquared Productions. All rights reserved.
//

#ifndef sudoku_Grid_h
#define sudoku_Grid_h
#define GRID_WIDTH 9
#include "Cell.h"
#include "GroupOfCells.h"
#include <iostream>

using namespace std;

class Grid{
    
    public:
    
    /***************************************************************
     
                               Constructors
     
    ****************************************************************/

    Grid(int input[9][9])
    {
        for(int row = 0; row < GRID_WIDTH; row++)
        {
            for(int col = 0; col < GRID_WIDTH; col++)
            {
                int val = input[row][col];
                if(val != 0)
                    m_cells[row*GRID_WIDTH + col] = new Cell(val);
                else m_cells[row*GRID_WIDTH + col] = new Cell;
            }
        }
        createGroups();
    }
    
    Grid(Cell *input[81])
    {
        for(int row = 0; row < GRID_WIDTH; row++)
        {
            for(int col = 0; col < GRID_WIDTH; col++)
            {
                int val = input[row* GRID_WIDTH + col]->getVal();
                if(val != 0 && val < 10)
                    m_cells[row*GRID_WIDTH + col] = new Cell(val);
                else m_cells[row*GRID_WIDTH + col] = new Cell;
            }
        }
        createGroups();
    }
    
    Grid(string input)
    {
        for(int row = 0; row < GRID_WIDTH; row++)
        {
            for(int col = 0; col < GRID_WIDTH; col++)
            {
                int val = (input[row* GRID_WIDTH + col] - '0');
                if(val != 0)
                    m_cells[row*GRID_WIDTH + col] = new Cell(val);
                else m_cells[row*GRID_WIDTH + col] = new Cell;
            }
        }
        createGroups();
    }
    
    
    void createGroups()
    {
        //all 9 rows
        for(int row = 0; row < GRID_WIDTH; row++)
        {
            groups[row] = new GroupOfCells(&m_cells[row * GRID_WIDTH]);
        }
        
        //all 9 columns
        for(int col = 0; col < GRID_WIDTH; col++)
        {
            Cell *cells[9] ;
            for(int row = 0; row < GRID_WIDTH; row++)
            {
                cells[row] = m_cells[row * GRID_WIDTH + col];
            }
            groups[GRID_WIDTH + col] = new GroupOfCells(cells);
        }
        
        //all 9 boxes
        for(int run = 0; run < 3; run++)
        {
            int counter = 0;
            int counter2 = 0;
            int counter3 = 0;
            Cell *cells[9];
            Cell *cells2[9];
            Cell *cells3[9];
            for(int row = 0; row < 3; row++)
            {
                for(int col = 0; col < 3; col++)
                {
                    cells[counter] = m_cells[run*27 + row*GRID_WIDTH + col];
                    counter++;
                }
                for(int col = 3; col < 6; col++)
                {
                    cells2[counter2] = m_cells[run*27 + row*GRID_WIDTH + col];
                    counter2++;
                }
                for(int col = 6; col < 9; col++)
                {
                    cells3[counter3] = m_cells[run*27 + row*GRID_WIDTH + col];
                    counter3++;
                }
            }
            groups[GRID_WIDTH*2 + run*3] = new GroupOfCells(cells);
            groups[GRID_WIDTH*2 + run*3 + 1] = new GroupOfCells(cells2);
            groups[GRID_WIDTH*2 + run*3 + 2] = new GroupOfCells(cells3);
        }
    }
    /***************************************************************
     
                                Destructor
     
    ****************************************************************/
    
    ~Grid()
    {
        for(int index = 0; index < 81; index++)
        {
            delete m_cells[index];
        }
        for(int index = 0; index < 27; index++)
        {
            delete groups[index];
        }
    }
    
    /***************************************************************
     
                                Mutators
     
     ****************************************************************/
    
    void candidateCheck()
    {
        for(int index = 0; index < 27; index++)
        {
            groups[index]->candidateCheck();
        }
    }
    
    
    int counter = 0;
    bool constraintPropogation(Grid *g, int startIndex)
    {
        bool done = g->determineValidity();
        //if it works, return true
        if(done)
            return true;
        
        //if it's already full and doesn't work, return false
        if(!done)
        {
            bool messedUp = true;
            for(int i = 0; i < 81; i++)
            {
                if(g->m_cells[i]->getVal() == 0)
                    messedUp = false;
            }
            if(messedUp)
                return false;
        }
        //iterate through the cells, taking lowest index each time
        
        for(int index = g->getLowestPossible(startIndex); ; index = g->getLowestPossible(index))
        {
            if(g->m_cells[index]->getVal() != 0)
            {
                continue;
            }
            //iterate through possible values
            for(int value = 1; value < 10; value++)
            {
                if(g->checkIfPossible(index, value))
                {
                    //create a new grid
                    Grid * theTemp = new Grid(g->m_cells);
                    
                    //add the random cell
                    g->m_cells[index]->setVal(value);
                    g->candidateCheck();
                    
                    //recurse
                    if(constraintPropogation(g, index))
                    {
                        return true;
                    }
                    
                    //backtrack
                    g->copy(theTemp);
                    g->candidateCheck();
                    delete theTemp;
                }
            }
            return false;
        }
        return false;
     }
    
    void copy(Grid *g)
    {
        for(int index = 0; index < 27; index++)
        {
            delete groups[index];
        }
        for(int i = 0; i < 81; i++)
        {
            delete m_cells[i];
            Cell *temp = g->getCell(i);
            int val = temp->getVal();
            if(val != 0)
                m_cells[i] = new Cell(val);
            else m_cells[i] = new Cell;
        }
        createGroups();
    }
    
    void initializeArray(Cell *cells[81], string input)
    {
        for(int i = 0; i < 81; i++)
        {
            cells[i]->setVal(input[i] - '0');
        }
    }
    /***************************************************************
     
                                Accessors
     
     ****************************************************************/
    
    Cell *getCell(int index)
    {
        return m_cells[index];
    }
    
    GroupOfCells *getGroup(int index)
    {
        return groups[index];
    }
    
    int getLowestPossible(int startIndex)
    {
        int lowest = 10;
        int indexLowest = 0;
        for(int i = startIndex; i < 81; i++)
        {
            if(m_cells[i]->getVal() != 0)
                continue;
            int temp = m_cells[i]->getPossibleValues();
            if(temp < lowest)
            {
                lowest = temp;
                indexLowest = i;
            }
            if(temp == 2)
                break;
        }
        return indexLowest;
    }
    
    bool determineValidity()
    {
        bool valid = true;
        for(int index = 0; index < 27; index++)
        {
            valid = valid && (groups[index]->checkIfValid());
        }
        return valid;
    }
    
   bool checkIfPossible(int index, int value)
    {
        return (m_cells[index]->checkPossibility(value));
    }
    
    bool determineValidity(Cell *cells[81])
    {
        Grid temp(cells);
        bool valid = true;
        for(int index = 0; index < 27; index++)
        {
            valid = valid && (temp.groups[index]->checkIfValid());
        }
        return valid;
    }
    
    string getString(Cell cells[81])
    {
        string theCells = "";
        for(int i = 0; i < 81; i++)
        {
            theCells += std::to_string(cells[i].getVal());
        }
        return theCells;
    }
    
    /***************************************************************
     
                                Solve
     
     *****************************************************************/
    
    void solve()
    {
         constraintPropogation(this, 0);
    }
    
    static void testOne(string input)
    {
        for(int i = 0; i < 81; i++)
        {
            if(input[i] == '.')
                input[i] = '0';
        }
        Grid temp(input);
        temp.solve();
        temp.print();
    }
    
    static void testAll(string input)
    {
        int size = input.size();
        for(int i = 0; i < size/81; i++)
        {
            string substr = input.substr(i*81, i*81+81);
            testOne(substr);
        }
    }
    /***************************************************************
     
                                Graphics
     
     *****************************************************************/
    
    void print()
    {
        for (int row = 0; row < GRID_WIDTH; row++)
        {
            if(row != 0 && row % 3 == 0)
                cout << "------+-------+------" << endl;
            for (int col = 0; col < GRID_WIDTH ; col++)
            {
                if(col != 0 && col % 3 == 0)
                    cout << "| ";
                cout << m_cells[row*GRID_WIDTH + col]->getVal() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void printPossible()
    {
        for (int row = 0; row < GRID_WIDTH; row++)
        {
            for (int col = 0; col < GRID_WIDTH ; col++)
            {
                m_cells[row*GRID_WIDTH + col]->printPossible();
                
            }
            cout << endl;
        }
    }
    
    void printGroups()
    {
        for(int group = 0; group < 27; group++)
        {
            cout << "value for group " << group << " ";
            for(int val = 0; val < 9; val++)
            {
                cout << groups[group]->getVal(val)->getVal();
            }
            cout << endl;
        }
    }
    
    private:
    Cell *m_cells[81];
    GroupOfCells *groups[27];
 };


#endif
