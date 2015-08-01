//
//  GroupOfCells.h
//  sudoku
//
//  Created by Jayendra Ashutosh Jog on 7/26/15.
//  Copyright (c) 2015 Jsquared Productions. All rights reserved.
//

#ifndef sudoku_GroupOfCells_h
#define sudoku_GroupOfCells_h
#define GRID_WIDTH 9
#include "Cell.h"
#include <iostream>

using namespace std;


class GroupOfCells{
public:
    GroupOfCells(Cell *cells[9])
    {
        for(int index = 0 ; index < 9; index++)
        {
            m_nineCells[index] = cells[index];
        }
        candidateCheck();
    }
    
    bool checkIfValid()
    {
        bool valid[9] = {0,0,0,0,0,0,0,0,0};
        
        for(int index = 0; index < GRID_WIDTH; index++)
        {
            int val = m_nineCells[index]->getVal();
            if( val > 0 && val < 10)
            {
                if(valid[val-1] == false)
                    valid[val - 1] = true;
                else
                    return false;
            }
        }
        int counter = 0;
        for(int index = 0 ; index < GRID_WIDTH; index++)
        {
            counter += valid[index];
        }
        if(counter == 9)
            return true;
        return false;
    }

    void candidateCheck()
    {
        //iterate through the nine cells
        for(int i = 0; i < GRID_WIDTH; i++)
        {
            int temp = m_nineCells[i]->getVal();
            if(temp != 0)
            {
                for(int j = 0; j < GRID_WIDTH; j++)
                {
                    if(temp != m_nineCells[j]->getVal())
                    {
                        m_nineCells[j]->removePossibility(temp-1);
                    }
                }
            }
        }
    }
    
    void reveseCandidateCheck()
    {
        
    }
    
    Cell * getVal(int index)
    {
        return m_nineCells[index];
    }
    
private:
    Cell * m_nineCells[9];
};
#endif
