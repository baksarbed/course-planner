


//  if you want to take a course with a particular prof take the rest out the input file

#include <iostream>
using namespace std;

#include "planner.h"

extern course_base* list;

// menue options
#define PRINT  "print"
#define SELECT "select"
#define EXIT "exit"
#define AUTO "auto"
#define FULL "full"

#define MAX_NUM_COURSES 5	// max number of courses to compare


void select_module();
void print_module();
void menu_screen();
void auto_module();

void menu_screen()
{
	cout << endl;
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
	cout << "|             menu:                     |" << endl;
	cout << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << endl << endl;
	cout << "Please type an option: " << endl;
	cout << "---------------------- " << endl;
	cout << PRINT << " : to print a list of courses" << endl;
	cout << FULL <<  " : to print a full listing of courses" << endl;
	cout << SELECT << " : to select 1-" << MAX_NUM_COURSES << " specific courses manually and check conflics" << endl;
	cout << AUTO << " : to select 1-" << MAX_NUM_COURSES << " course names, and recieve a conflict-free time-table" << endl;
	cout << EXIT << " : to end the program" << endl;
	cout << ">> ";
}

void print_module()
{
	print_course_list();
	cout << endl << "Note: this is only a list of existing courses. Each course may have different sections" << endl;
	cout << "see 'full' for a full listing of courses" << endl << endl;
}
void select_module()
{
	course_base* keys[MAX_NUM_COURSES];
	int count=0;

	print_course_list();

	while(count < MAX_NUM_COURSES)
	{
		// get name 
		char cmd[20];
		cout << "Enter course name, or 'end' if done : ";
		cin >> cmd;		
		if( cin.eof() || strcmp(cmd,"end") == 0 ) break;	

		char* course_name = new char[strlen(cmd)+1];
		strcpy(course_name,cmd);
		cin.ignore(80,'\n');

		// get section
		cout << "Enter course section (e.g. 2): ";
		int sec;
		cin >> sec;

		// find course
		course_base* listPtr = list;
		while( listPtr != NULL && strcmp(listPtr->get_name(),course_name ) !=0 ) 
		{
			listPtr=listPtr->next_course;
		}

		if( listPtr == NULL ) 
		{
			cout << "Error: course not found" << endl;
		}
		else
		{
			while( listPtr != NULL && listPtr->get_section() != sec )	listPtr = listPtr->next;
			if( listPtr == NULL )
				cout << "Error: section not found" << endl;
			else
			{
				// add found course to the list of keys
				keys[count] = listPtr->get_address();
				count++;
			}
		}
		

	}

	cout  << endl << ")()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()(" << endl;
	// validate
	cout << "number of conflicts: " << has_conflic(keys,count) << endl << endl;
	cout  << endl << ")()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()(" << endl;

	// clean up ?!?!!?
}
void auto_module()
{
	course_base* keys[MAX_NUM_COURSES]= {NULL};
	int count=0;

	print_course_list();

	while(count < MAX_NUM_COURSES)
	{
		// get name 
		char cmd[20];
		cout << "Enter course name, or 'end' if done : ";
		cin >> cmd;		
		if( cin.eof() || strcmp(cmd,"end") == 0 ) break;	

		char* course_name = new char[strlen(cmd)+1];
		strcpy(course_name,cmd);
		cin.ignore(80,'\n');

		// find course
		course_base* listPtr = list;
		while( listPtr != NULL && strcmp(listPtr->get_name(),course_name ) !=0 ) 
		{
			listPtr=listPtr->next_course;
		}

		if( listPtr == NULL ) 
		{
			cout << "Error: course not found" << endl;
		}
		else
		{
			// add found course to the list of keys
			keys[count] = listPtr->get_address();
			count++;
		}
	}
	if( count < 2 )
	{
		cout << "Warning: only one course selected" << endl << "Returning back to main menu..." << endl << endl;
		return;
	}
	// find a match 
	// Note: very inefficient
	course_base* temp_keys[MAX_NUM_COURSES]= {NULL};
	temp_keys[0] = keys[0];
	int status=0;

	cout  << endl << ")()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()(" << endl;	
	while(temp_keys[0] != NULL)
	{
		temp_keys[1]= keys[1];
		while( temp_keys[1] != NULL )
		{
			temp_keys[2]= keys[2];
			while( count>=3 && temp_keys[2] != NULL )
			{
				temp_keys[3]= keys[3];
				while( count>=4 && temp_keys[3] != NULL )
				{
					temp_keys[4]= keys[4];
					while( count == MAX_NUM_COURSES && temp_keys[4] != NULL )
					{
						status = has_conflic(temp_keys,count); 		// check conflicts
						if( !status )
						{
							cout << endl << "*** found a match: " << endl;
							temp_keys[0]->print_course_id(); cout <<"section: " << temp_keys[0]->get_section() << endl;
							temp_keys[1]->print_course_id(); cout <<"section: " << temp_keys[1]->get_section() << endl;
							temp_keys[2]->print_course_id(); cout <<"section: " << temp_keys[2]->get_section() << endl;
							temp_keys[3]->print_course_id(); cout <<"section: " << temp_keys[3]->get_section() << endl;
							temp_keys[4]->print_course_id(); cout <<"section: " << temp_keys[4]->get_section() << endl;
						}
						else
						{
							cout << "--- Caught conflicts, see above for details" << endl;
						}
						temp_keys[4]= temp_keys[4]->next;	// try next section
					}
					if( count == 4 ) // check conflicts
					{
						status = has_conflic(temp_keys,count);
						if( !status )
						{
							cout << endl << "*** found a match: " << endl;
							temp_keys[0]->print_course_id(); cout << "section: " << temp_keys[0]->get_section() << endl;
							temp_keys[1]->print_course_id(); cout << "section: " << temp_keys[1]->get_section() << endl;
							temp_keys[2]->print_course_id(); cout << "section: " << temp_keys[2]->get_section() << endl;
							temp_keys[3]->print_course_id(); cout << "section: " << temp_keys[3]->get_section() << endl;
						}
						else
						{
							cout << "--- Caught conflicts, see above for details" << endl;
						}
					}
					temp_keys[3]= temp_keys[3]->next;	// try next section
				}
				if( count == 3 )  // check conflicts
				{
					status = has_conflic(temp_keys,count);
					if( !status )
					{
						cout << endl << "*** found a match: " << endl;
						temp_keys[0]->print_course_id(); cout << "section: " << temp_keys[0]->get_section() << endl;
						temp_keys[1]->print_course_id(); cout << "section: " << temp_keys[1]->get_section() << endl;
						temp_keys[2]->print_course_id(); cout << "section: " << temp_keys[2]->get_section() << endl;
					}
					else
					{
						cout << "--- Caught conflicts, see above for details" << endl;
					}
				}
				temp_keys[2]= temp_keys[2]->next;	// try next section
			}
			if( count == 2 )  // check conflicts
			{
				status = has_conflic(temp_keys,count);
				if( !status )
				{
					cout << endl << "*** found a match: " << endl;
					temp_keys[0]->print_course_id(); cout << "section: " <<temp_keys[0]->get_section()<< endl;
					temp_keys[1]->print_course_id(); cout << "section: " <<temp_keys[1]->get_section()<< endl;
				}
				else
				{
					cout << "--- Caught conflicts, see above for details" << endl;
				}
			}
			temp_keys[1]= temp_keys[1]->next;	// try next section
		}
		temp_keys[0]= temp_keys[0]->next;	// try next section

	}
	cout  << endl << ")()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()(" << endl;

	// clean up ?!?!!?

}

int main()
{
	parse_course_files("fall2009.txt");
	
	while(true)
	{
		menu_screen();
	
		char cmd[20];
		cin >> cmd;
		
		if( cin.eof() ) break;	

		cout << endl;

		if ( !strcmp(cmd,PRINT) ) print_module();
		else if ( !strcmp(cmd,SELECT) ) select_module();
		else if ( !strcmp(cmd,EXIT) ) break;
		else if ( !strcmp(cmd,AUTO) ) auto_module();
		else if ( !strcmp(cmd,FULL) ) print_full_courses();
		else
			cout << "Error: unkown command." << endl;

		cin.ignore(80,'\n');
	
	}



return 0;
}
