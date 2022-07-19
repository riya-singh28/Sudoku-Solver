/* ===============================================================
   ===============================================================
        This app takes in a sudoku puzzle and outputs solution.
        Author - Riya Singh

    ==============================================================
    ===============================================================
*/

/*/* ==========================
     ==========================
        SUDOKU SOLVER
     ==========================
     ==========================
*/

#include<iostream>
#include<fstream>
using namespace std;


/**	
  *	We are making a Sudoku class which holds and manipulate the values in a sudoku puzzle.
*/
class Sudoku{
	
	int sudoku[9][9]; //This matrix will hold all the values in the given puzzle.
	int editableFrame[9][9]; //This matrix will tell us all the values which are editable in the given puzzle.

	/**	
	  *	@desc This constructor calls the menu() func to provide the menu.
	  *	@param none
	  *	@return none
	*/

	public: Sudoku(){
		menu();
	}
	
	/**
	  *	@desc Displays a menu to the user which contains all possible options a user has.
	  *
	  *	@param none
	  *	@return none
	*/
	private: void menu(){
		
		cout<<"\n======================\n";
		cout<<"    Sudoku Solver\n";
		cout<<"======================\n\n";

		cout<<"Aloha!.......Welcome to Sudoku Solver!\n";
		cout<<"Before we start, you will have to input the puzzle into this program.\n\n";
		cout<<"You have the following options :-\n";
		cout<<"\t1. To Input the puzzle by entering the values manually. (Enter 1)\n";
		cout<<"\t2. To Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout<<"\t   The file must not have a name of more than 20 characters.\n";
		cout<<"\t   The file must be in the same directory as this C++ file.\n";
		cout<<"\t   The file must have all 81 values seperated with spaces.\n";
		cout<<"\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
		cout<<"\t   --> ";

		int option;
		cin>>option;

		if(option==1) readFrameValues();             //this function read user inputs.
		else if(option==2) readFrameValuesFile();     // this function read values from the file specified by user.
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
	  *	@desc Reads the values for the Sudoku Frame cell-by-cell.
	  *	@param none
	  *	@return none
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

				if(!(enteredValue>=0 && enteredValue<=9)){ //Entered value should be either 0 for blanks or between 1 to 9 (included).
					while(true){ //We loop until valid input is read from user.
						cout<<"Oooooooops! You seem to have entered a wrong value! Try again.\n";
						cout<<"Enter value for cell ["<<rowNo+1<<"]["<<colNo+1<<"] --> ";
						cin>>enteredValue;

						if(enteredValue>=0 && enteredValue<=9) break;
					}
				}

				sudoku[rowNo][colNo]=enteredValue;

				if(enteredValue==0) editableFrame[rowNo][colNo]=0;   //editable frame keeps a track of all the editable values in matrix.
				else editableFrame[rowNo][colNo]=1;
			}
			cout<<"-------\n"; //Display a break after every row for convenience.
		}
	}



    /**
	  *	@desc Reads the values from a file containing the frame values seperated by whitespaces.
	  *	@param none
	  *	@return none
	*/
	private:void readFrameValuesFile(){

		char filename[30]; //Getting filename.

		cout<<"\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout<<"\t   --> ";
		cin>>filename;

		ifstream sudokuFile; //Opening file for reading.
		sudokuFile.open(filename,ios::in);
		
		int rowNo, colNo;

		for(rowNo=0; rowNo<9; rowNo++){ //Iterating over file values.
			for(colNo=0; colNo<9; colNo++){
				int readValue;
		
				sudokuFile>>readValue;

				if(!(readValue>=0 && readValue<=9)){ //Checking bounds for input.
					cout<<"\nValue "<<((rowNo*9)+colNo+1)<<" in "<<filename;
					cout<<" seems to be wrong! Correct the value and try again!\n";
					exit(EXIT_FAILURE);
				}

				sudoku[rowNo][colNo]=readValue;

				if(sudoku[rowNo][colNo]==0) editableFrame[rowNo][colNo]=0;
				else editableFrame[rowNo][colNo]=1;

				if(sudokuFile.eof()) break; //Breaking if EOF is reached.
			}
		}

		sudokuFile.close();
	}

/**
	  *	@desc Assigns the passed-in number to the specified row and col if the value of that cell in editableFrame is 0.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return none
	*/
	public:void setCellValue(int row, int col, int num){
		if(editableFrame[row][col]==0) sudoku[row][col]=num;
	}
	
	/**	
	  *	@desc Returns the value of the cell at the specified row and col if the 
	  * value of that cell in editableFrame is 0.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (int) cellValue value at the specified cell
	*/
	public:int getCellValue(int row, int col){
		int cellValue=sudoku[row][col];
		return cellValue;
	}
	
/**
	  *	@desc Function to check if the specified cell is editable or not. 
	  * Returns 0/1 depending on editableFrame values.
	  *	@param row (int) row of the required cell
 	  *	@param col (int) col of the required cell
	  *	@return (int) 1 if editable; 0 if not
	*/
	public:int isEditable(int row, int col){
		return (editableFrame[row][col]-1)*(-1);
	}

	/**
	  *	@desc Clears all the values from frame, other than the question values, from
	  *	the specified cell to the last cell.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	*/
	public:void clearFrameFrom(int row, int col){
		int jcount=0;
		int rowNo, colNo;

		for(rowNo=row; rowNo<9; rowNo++){
			
			if(jcount==0) colNo=col;
			else colNo=0;

			for(; colNo<9; colNo++){
				if(editableFrame[rowNo][colNo]==0) sudoku[rowNo][colNo]=0;
			}

			jcount++;

		}
	}

	/**
	  *	@desc Displays the values stored in the frame with designs. We also use
	  *	ANSI colors, using escape sequences, to display the frame.
	  * It makes a frame of yellow colour around the sudoku.
	  *	@param none
	  *	@return none
	*/
	public:void displayFrame(){

		cout<<"\033[0;36m++=====================================++";
		int rowNo, colNo;

		for(rowNo=0; rowNo<9; rowNo++){
			int cellNo=1;

			cout<<"\n\033[0;36m||";
			for(colNo=0; colNo<9; colNo++){
				if(cellNo==3){
					cout<<"\033[0m "<<sudoku[rowNo][colNo]<<" ";
					cout<<"\033[0;36m||";
					cellNo=1;
				}
				else{
					cout<<"\033[0m "<<sudoku[rowNo][colNo]<<"  ";
					cellNo++;	
				}
			}

			if(rowNo%3!=2) cout<<"\n\033[0;36m++-----------++-----------++-----------++";
			else cout<<"\n\033[0;36m++=====================================++";
		}

	}

};


class Node{
	public:
	int value;
	Node* next;

	Node(int val){
		value = val;
		next = NULL;
	}
};


class possibleNos{
	
	// struct node{
	// 	int value;
	// 	struct node* next;
	// }; //The struct for the node
	
	// typedef struct node* Node;

	Node* head; //The head node
	Node* pos; //A node iterator variable
	

	/**	
	  *	@desc This constructor initialises the head (or sentinel) node.
	  *	@param none
	*/
	public:possibleNos(int val){
		head=new Node(val);
		head->next=NULL;
	}
	
	/**	
	  *	@desc This destructor destroys the linked list once the object
 	  *	has finished its lifespan. Calls the destroy() function.
	*/
	public:~possibleNos(){
	}

	/**	
	  *	@desc This functions takes in a number and adds it as a node in
	  *	the linked list.
	  *	@param number (int) the number which we want to append
	  *	@return none
	*/
	public:void append(int number){
		Node* temp=new Node(number);

		// temp->value=number;
		temp->next=NULL;

		pos=head;
		while(pos!=NULL){
			if(pos->next==NULL){
				pos->next=temp;
				break;
			}
			pos=pos->next;
		}
	}

	/**	
	  *	@desc An operator overload function which overloads the [] operator.
	  *	@param index (int) the index of the required node in the linked list.
	  *	@return (int) the value contained in the specified node.
	*/
	public:int operator[](int index){
		int count=0;
		pos=head->next;
		
		while(pos!=NULL){
			if(count==index)
				return pos->value;
			pos=pos->next;
			count++;
		}

		return -1;
	}

	/**	print()

	  *	@desc Prints the values inside all the nodes of the linked list.
	  *	@param none
	  *	@return none
	*/
	public:void print(){
		pos=head->next;
		while(pos!=NULL){
			cout<<pos->value<<",";
			pos=pos->next;
		}
		cout<<"\b";
	}

	/**
	  *	@desc Returns the length of the linked list.
	  *	@param none
	  *	@return (int) the length of the linked list.
	*/
	public:int length(){
		pos=head->next;
		int count=0;

		while(pos!=NULL){
			count++;
			pos=pos->next;
		}
		
		return count;
	}
	
	/**
	  *	@desc This function takes in a possibilities object and copies
	  *	the contents into THIS object.
	  *	@param possibilities (PossibleNos) the object which is to be copied
	  *	@return none
	*/
	public:void copy(possibleNos possibilities){ //Need to make this clear the old list if exists
		int oldLength=possibilities.length();
		int iter=0;
		
		pos=head;
		for(iter=0; iter<oldLength; iter++){
			Node* temp=new Node(possibilities[iter]);   //uses operaor[] to get the value at specified index.

			temp->next=NULL;
			// temp->value=possibilities[iter];

			pos->next=temp;
			pos=pos->next;
		}
	}

	/**
	  *	@desc Frees all the nodes in the linked list.
	  *	@param none
	  *	@return none
	*/
	private:void destroy(){
		Node* temp;
		pos=head;
		while(pos!=NULL){
			temp=pos;
			pos=pos->next;
			delete temp;
		}
	}

};

class SudokuSolver{
	
	int recursiveCount; //Stats variable
	Sudoku frame; //The frame object
	
	/**
	  *	@desc The constructor initialises the recursiveCount variable and also calls
	  *	the solve() function which solves the puzzle. It also displays the frames
	  *	before and after the solving.
	  *	@param none
	*/
	public:SudokuSolver(){
		recursiveCount=0;

		cout<<"\nCalculating possibilities...\n";
		cout<<"Backtracking across puzzle....\n";
		cout<<"Validating cells and values...\n\n";
		
		solve();
		cout<<"QED. Your puzzle has been solved!\n\n";
		displayFrame();

		cout<<"\n\n";
	}

	/**
	  *	@desc Checks if the value in the specified cell is valid or not.
	  *	@param row (int) row of the required value
	  *	@param col (int) col of the required value
	  *	@param currentValue (int) the required value
	  *	@return (bool) whether the value is valid or not in the sudoku frame
	*/
	private:bool cellValueValid(int row, int col, int currentValue){
		int rowNo, colNo;

		//Checking if value exists in same column
		for(rowNo=0; rowNo<9; rowNo++){
			if(rowNo!=row){
				int comparingValue=frame.getCellValue(rowNo,col);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in same row
		for(colNo=0; colNo<9; colNo++){
			if(colNo!=col){
				int comparingValue=frame.getCellValue(row,colNo);
				if(comparingValue==currentValue) return false;
			}
		}

		//Checking if value exists in the same 3x3 square block
		if(ThreeByThreeGridValid(row,col,currentValue)==false) return false;

		return true;
	}
	
	/**
	  *	@desc Checks if the same value is also present in the same 3x3 grid block.
	  *	@param row (int) row of the required cell
	  *	@param col (int) col of the required cell
	  *	@param currentValue (int) required value
	  *	@return (bool) whether the value is present or not
	*/
	private:bool ThreeByThreeGridValid(int row, int col, int currentValue){
		int rowStart=(row/3)*3;
		int rowEnd=(rowStart+2);

		int colStart=(col/3)*3;
		int colEnd=(colStart+2);

		int rowNo, colNo;

		for(rowNo=rowStart; rowNo<=rowEnd; rowNo++){
			for(colNo=colStart; colNo<=colEnd; colNo++){
				if(frame.getCellValue(rowNo,colNo)==currentValue) return false;
			}
		}

		return true;	
	}
	
	/**
	  *	@desc Gets the possible values and assigns them to the possibilities list.
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (Possibilities) Possibilities object containing all the possible values.
	*/
	private:possibleNos getCellPossibilities(int row, int col){
		int iter=0;
		
		possibleNos possibilities(iter);
		
		for(iter=1; iter<=9; iter++){
			if(cellValueValid(row,col,iter)==true)
				possibilities.append(iter);
		}

		return possibilities;
	}


/**	
	  *	@desc The recursive function which does all the work, this iterates over the
	  *	possible values for the specified cell one-by-one. Once a value has been filled, it
	  *	goes to the next cell. Here, the same thing happens. If none of the possible values
	  *	work out, then the function backtracks to the previous cell.
  	  *
	  *	@param row (int) row of the specified cell
	  *	@param col (int) col of the specified cell
	  *	@return (int) whether the value put in the cell made it a SUCCESS or NOT
	*/
	private:int singleCellSolve(int row, int col){
		
		statsIncrement(); //This is used to see how many times the func is called.

		if(frame.isEditable(row,col)==true){
			
			possibleNos possibilities(0);
			possibilities.copy(getCellPossibilities(row,col));

			int posLength=possibilities.length();
			int posIter=0, newRow=row, newCol=col;

			for(posIter=0; posIter<posLength; posIter++){ //We iter over the possible values
				int possibility=possibilities[posIter];
				frame.setCellValue(row,col,possibility);
				
				//We now increment the col/row values for the next recursion
				if(col<8) newCol=col+1; 
				else if(col==8){
					if(row==8) return 1; //this means success
					newRow=row+1;
					newCol=0;
				}

				{

					if(singleCellSolve(newRow,newCol)==0){ //If wrong, clear frame and start over
						frame.clearFrameFrom(newRow,newCol);
					}
					else return 1;

				} //Recursion block ends here

			} //Loop ends here

			return 0;
			
		} //The isEditable() if block ends here.
		else{

			int newRow=row, newCol=col;
			
			//Same incrementing of the col/row values
			if(col<8) newCol=col+1;
			else if(col==8){
				if(row==8) return 1;
				newRow=row+1;
				newCol=0;
			}

			return singleCellSolve(newRow,newCol);

		} //The else block ends here

	}

	/**
	  *	@desc Calls the singleCellSolve() func and prints a success/fail mesg.
	  *	@param none
	  *	@return none
	*/
	private:void solve(){
		int success=singleCellSolve(0,0);
	}
	
	/**
	  *	@desc Displays the sudoku frame by calling the displayFrame() func of the
	  *	SudokuFrame object.
	  *	@param none
	  *	@return none
	*/
	private:void displayFrame(){
		frame.displayFrame();
	}


	/**
	  *	@desc This increments the count variable to keep track of the recursions done.
	  *	@param none
	  *	@return none
	*/
	private:void statsIncrement(){
		recursiveCount++;
	}

	/**
	  *	@desc This displays the number of times recursion has happened.
	  *	@param none
	  *	@return none
	*/
	public:void statsPrint(){
		cout<<"\nThe singleCellSolve() function was recursively called "<<recursiveCount<<" times.\n";
	}
	
};
	

	
	


int main(){
	SudokuSolver ss;
	return 0;
}

