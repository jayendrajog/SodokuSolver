//
//  Cell.h
//  sudoku
//
//  Created by Jayendra Ashutosh Jog on 7/26/15.
//  Copyright (c) 2015 Jsquared Productions. All rights reserved.
//

#ifndef sudoku_Cell_h
#define sudoku_Cell_h
#include <iostream>
using namespace std;
class Cell{
    public:
    
    /***************************************************************
     
                                Constructors
     
    ***************************************************************/
   
    Cell()
    {
        for(int i = 1; i < 10; i++)
        {
            m_possible_values[i-1] = true;
        }
        m_value = 0;
        numPossibleVal = 9;
    }
    
    Cell(int val)
    {
        setVal(val);
    }
    
    /***************************************************************
     
                                Destructor
     
     ***************************************************************/
    
    ~Cell()
    {

    }
    
    /***************************************************************
     
                                Mutators
     
     ***************************************************************/
    
    void setVal(int val)
    {
        for(int i = 1; i < 10; i++)
        {
            m_possible_values[i-1] = false;
        }
        m_possible_values[val-1] = true;
        m_value = val;
        numPossibleVal = 1;
    }
    
    void refresh()
    {
        for(int i = 1; i < 10; i++)
        {
            m_possible_values[i-1] = true;
        }
        m_value = 0;
        numPossibleVal = 9;
    }
    
    void removePossibility(int index)
    {
        if(m_possible_values[index])
        {
            m_possible_values[index] = false;
            numPossibleVal--;
        }
        if(numPossibleVal == 1 && m_value==0)
        {
            for(int i = 0; i < 9; i++)
            {
                if(m_possible_values[i] == true)
                {
                    m_value = i+1;
                }
            }
        }
    }
    
    /***************************************************************
     
                            Accessors
     
     ***************************************************************/
    int getVal()
    {
        return m_value;
    }
    
    int getPossibleValues()
    {
        return numPossibleVal;
    }
    
    bool checkPossibility(int value)
    {
        return m_possible_values[value-1];
    }
    
    void printPossible()
    {
        for(int i = 0; i < 9; i++)
        {
            if(m_possible_values[i])
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    private:
    
    
    /***************************************************************
     
                        Member Variables
     
     ***************************************************************/
    int m_value; //0 indicates that no value has been deduced yet
    
    //contains all remaining possible values that the cell can have
    bool m_possible_values[9];
    
    int numPossibleVal;
    
};

#endif
