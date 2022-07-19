/*
 *========================
 *    Sudoku-Validator
 *========================
 *
 * Author:- RIYA SINGH
 * Objective: To verify whether a completed Sudoku puzzle is valid or not.
 * Purpose:- This application takes in input a solved puzzle and verify it is correct solution or not. 
 *           Every Sudoku puzzle has one and only one unique solution.
 * Theory:-  A Sudoku is said to be solved if every column and row has 1-9 digits atleast and only once.
 *           And every small 3*3 squares should have 1-9 digits alteast once.
*/

#include<iostream>
#include<fstream>
using namespace std;

class Sudoku{

	int sudokuFrame[9][9];

	public:Sudoku(){
		menu();
	}


    /**
	  *	@desc This function generates a menu for the user at the starting of the
	  *	program execution. This lets the user select the input method for entering
	  *	the values for the Sudoku Puzzle into the SudokuFrame object.
	  *
	  *	@param none
	  *	@return none
	*/
	private:void menu(){

                cout<<"\n======================\n";
                cout<<"   Sudoku Validator\n";
                cout<<"======================\n\n";

                cout<<"Aloha!......Welcome to Sudoku Validator!\n";
                cout<<"Before we start, you have to input the puzzle into this program.\n\n";
                cout<<"You have the following options:-\n";
                cout<<"\t1. To input the puzzle by entering the values manually. (Enter 1)\n";
                cout<<"\t2. To input the puzzle by reading a file with values in it. (Enter 2)\n";
                cout<<"Instructions for option 2:---";
                cout<<"\t   The file must not have a name > 30 characters.\n";
                cout<<"\t   The file must be in the same directory as this C++ file.\n";
                cout<<"\t   The file must have all 81 values seperated with spaces.\n";
                cout<<"\t   Blank cells must be filled in as 0 (eg; 1 2 9 8 1 9 ...).\n";
                cout<<"\t   --> ";

                int option;
                cin>>option;

                if(option==1) readFrameValues();
                else if(option==2) readFrameValuesFile();
                else{
                        while(true){
                                cout<<"\nYou seem to have entered an invalid option. Try again.\n";
                                cout<<"\t   --> ";
                                cin>>option;

                                if(option==1) readFrameValues();
                                else if(option==2) readFrameValuesFile();
                                else continue;

                                break;
                        }
                }

        }

	    /**
          *     @desc Reads the values for the Sudoku Frame cell-by-cell.
          *     @param none
          *     @return none
        */
        private:void readFrameValues(){
                cout<<"\nEnter the specified value when prompted.\n";
                cout<<"Enter 0 if cell is empty.\n\n";

		int rowNo, colNo;

                for(rowNo=0; rowNo<9; rowNo++){ //Iterating over cells to read vals.
                        for(colNo=0; colNo<9; colNo++){
                                int enteredValue;

                                cout<<"Enter value for cell["<<rowNo+1<<"]["<<colNo+1<<"] --> ";
                                cin>>enteredValue;

                                if(!(enteredValue>=1 && enteredValue<=9)){ //Checking for bounds in input.
                                        while(true){ //We loop until valid input is read from user.
                                                cout<<"Oooooops! You have entered a invalid value! Try again.\n";
                                                cout<<"Enter value for cell ["<<rowNo+1<<"]["<<colNo+1<<"] --> ";
                                                cin>>enteredValue;

                                                if(enteredValue>=1 && enteredValue<=9) break;
                                        }
                                }

                                sudokuFrame[rowNo][colNo]=enteredValue;
                        }
                        cout<<"-------\n"; //Display a break after every row for convenience.
                }
        }
	
	/**
	  *	@desc This function reads values from a specified file.
	  *	@param none
	  *	@return none
	 */
	private:void readFrameValuesFile(){
		
		int rowNo, colNo;
		char filename[30];
		ifstream file;
		
		cout<<"\nEnter the name of the file which contains the puzzle --> ";
		cin>>filename;

		file.open(filename,ios::in);

		for(rowNo=0; rowNo<9; rowNo++){
			for(colNo=0; colNo<9; colNo++){

				int readValue;
				file>>readValue;

				sudokuFrame[rowNo][colNo]=readValue;

				if(file.eof()) break;

			}
		}
		
		//If there aren't 81 values in the file, then it is invalid.	
		if((colNo*rowNo)!=81){
			cout<<"Oops! The file doesn't have the required amount of values.\n";
			cout<<"Try again!\n";
			exit(EXIT_FAILURE);
		}

		file.close();

	}

/**
	  *	@desc Returns the value of a cell of a specified col and row.
	  *	@param row (int) The specified row.
	  *	@param col (int) The specified column.
	  *	@return The value in the specified cell.
	 */
	public:int getCellValue(int row, int col){
		return sudokuFrame[row][col];
	}

};


class SudokuValidator{

	Sudoku frame;
	
	/**
	  *	@desc Calls the function which validates the values in the Sudoku frame.
	  *	@param none
	 */
	public:SudokuValidator(){
		validateFrame();		
	}

	/**
	  *	@desc Calls functions which validates the rows, columns and 3x3 grids.
	  *	@param none
	  *	@return none
	*/
	private:void validateFrame(){
		if(valuesAreValid()){
			if(rowsAreValid()){
				if(columnsAreValid()){
					if(ThreeByThreeSquaresAreValid()){
						cout<<"\nYour puzzle is valid!\n\n";
					}
					else cout<<"Your puzzle in invalid!\n";
				}
				else cout<<"Your puzzle is invalid!\n";
			}
			else cout<<"Your puzzle is invalid!\n";
		}
		else cout<<"Your puzzle is invalid!\n";
	}
	

	/**
	  *	@desc Checks if all values in the frame are between the ranges of 1-9.
	  *	@param none
	  *	@return (bool) Whether all the values are valid or not.
	*/
	private:bool valuesAreValid(){		
		int rowNo, colNo;

		for(rowNo=0; rowNo<9; rowNo++){
			for(colNo=0; colNo<9; colNo++){
				int cellValue=frame.getCellValue(rowNo,colNo);
				if(!(cellValue>0 && cellValue<=9)) return false;
			}
		}

		return true;
	}

	/**
	  *	@desc Checks if the rows are valid in the frame.
	  *	@param none	
	  *	@return (bool) Whether the rows are valid or not.
	*/
	private:bool rowsAreValid(){
		
		int rowNo, valNo;

		for(rowNo=0; rowNo<9; rowNo++){ //Iterating over rows

			for(valNo=1; valNo<=9; valNo++){ //Iter over 1-9

				if(rowContains(rowNo,valNo)==false)
					return false;

			} //Value iteration loop ends here

		} //Row iteration loop ends here

		return true;
	}

	/**
	  *	@desc Checks if the columns in the frame are valid.
	  *	@param none
	  *	@return (bool) Whether the columns are valid or not.
	*/
	private:bool columnsAreValid(){
		
		int colNo, valNo;
		
		for(colNo=0; colNo<9; colNo++){ //Iterating over cols
		
			for(valNo=1; valNo<=9; valNo++){ //Iter over 1-9
				
				if(columnContains(colNo,valNo)==false)
					return false;

			} //Value iteration loops ends

		} //Col iteration loop ends here
		
		return true;
	}
	
	/**
	  *	@desc Checks if the 3x3 grids in the frame are valid.
	  *	@param none
	  *	@return (bool) Whether the 3x3 grids are valid or not.
	*/
	private:bool ThreeByThreeSquaresAreValid(){
		
		int squareNo, valNo;

		for(squareNo=0; squareNo<9; squareNo++){ //Iter over squares
			
			for(valNo=1; valNo<=9; valNo++){ //Iter over 1-9

				if(squareContains(squareNo,valNo)==false)
					return false;

			} //Value iteration loop ends here

		} //Square iteration loop ends here
		
		return true;
	}

	/**
	  *	@desc Checks whether a given value is present in a specified row.
	  *	@param row (int) The specified row.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present in the row or not.
	*/
	private:bool rowContains(int row, int value){
		int colNo;
		for(colNo=0; colNo<9; colNo++){
			if(frame.getCellValue(row,colNo)==value)
				return true;
		}
		return false;
	}

	/**
	  *	@desc Checks whether a given value is present in the specified column.
	  *	@param col (int) The specified column.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present in the col or not.
	*/
	private:bool columnContains(int col, int value){
		int rowNo=0;
		for(rowNo=0; rowNo<9; rowNo++){
			if(frame.getCellValue(rowNo,col)==value)
				return true;
		}
		return false;
	}

	/**
	  *	@desc Checks whether a given value is present in the specified 3x3 grid.
	  *	@param squareNumber (int) The 3x3 grid specified. The available grids are 0-8.
	  *	@param value (int) The value to be checked for.
	  *	@return (bool) Whether the value is present or not.
	*/
	private:bool squareContains(int squareNumber, int value){
		int rowStart=(squareNumber/3)*3;
		int rowEnd=rowStart+2;
		
		int colStart=(squareNumber%3)*3;
		int colEnd=colStart+2;

		int rowNo, colNo;
		for(rowNo=rowStart; rowNo<=rowEnd; rowNo++){
			for(colNo=colStart; colNo<=colEnd; colNo++){
				if(frame.getCellValue(rowNo,colNo)==value)
					return true;
			}
		}

		return false;
	}

};


int main(){
	SudokuValidator s;
	return 0;
}




