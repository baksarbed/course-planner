/**
 * @file header file for helper functions
 *
 */


#include <iostream>
using namespace std;
#include <fstream>


#ifndef UTILS_H
#define UTILS_H


/**
  *	@brief macros for input course files
  */
#define COMMENT "##"
#define START '>'
#define END '<'
#define NAME "course_name"
#define ID "course_id"
#define INSTRUCTOR "course_professor"
#define SECTION "course_section"
#define SEMESTER "course_semester"
#define TYPE "course_type"
#define TIME "course_time"
#define SEPERATOR ","



#define NUM_DAYS	5
#define NUM_HOURS	9

/**
 *	@brief node declaration for course list
 */

enum weekdays { monday=1 , tuesday , wednesday, thursday, friday };
enum time_spot { _9_10=1 , _10_11 , _11_12 , _12_1 , _1_2 , _2_3 , _3_4 , _4_5 , _5_6 };
enum class_type { LEC=1, LAB , TUT };

/**
 * @brief struget_name(cture that holds classes and hours for a course
 *
 */
struct course_time {
	weekdays	day; 
	time_spot	hour;
};


#define convert_time(m)  switch(m){ \
			case _9_10: \
				cout << "9:00 - 10:00" << endl; \
				break; \
			case _10_11: \
				cout << "10:00 - 11:00" << endl; \
				break; \
			case _11_12: \
				cout << "11:00 - 12:00" << endl; \
				break; \
			case _12_1: \
				cout << "12:00 - 1:00" << endl; \
				break; \
			case _1_2: \
				cout << "1:00 - 2:00" << endl; \
				break; \
			case _2_3: \
				cout << "2:00 - 3:00" << endl; \
				break; \
			case _3_4: \
				cout << "3:00 - 4:00" << endl; \
				break; \
			case _4_5: \
				cout << "4:00 - 5:00" << endl; \
				break; \
			case _5_6: \
				cout << "5:00 - 6:00" << endl; \
				break; \
			default: \
				cout << "Error: Invalid Time" << endl; \
				break; }

#define convert_day(m)  switch(m){ \
			case monday: \
				cout << "Monday "; \
				break; \
			case tuesday: \
				cout << "Tuesday ";\
				break; \
			case wednesday: \
				cout << "Wednesday "; \
				break; \
			case thursday: \
				cout << "Thursday "; \
				break; \
			case friday: \
				cout << "Friday "; \
				break; \
			default: \
				cout << "Error: Invalid Day" << endl; \
				break; }


void print_type(class_type type);
void print_times(course_time* times,class_type type);
int	parse_course_files(char* filename);
void print_full_courses();
void print_course_list();


#endif
