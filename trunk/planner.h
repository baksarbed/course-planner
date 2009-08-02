/**
 * @file header file for declarations
 *
 */


#include <iostream>
using namespace std;

#include "utils.h"

#ifndef PLANNER_H
#define PLANNER_H

/**
 * @brief Base class for a course
 *
 *
 */
class course_base{

	private:
			
	protected:
		char*	course_name; // course_id includes the name and the code (e.g. ece316)
		char*	course_id;
		int		count;		// count of number of courses
		
	public:
		course_base();	// default constructor
		course_base(char* _course_name, char* _course_id);
		course_base(const course_base& _course_base);	// copy constructor
		~course_base();	// destructor	

		void print_course_id();	// prints full name + id of a course + semester(s/f)
		void increment_count();

		course_base* next;	// pointer to create linked list
		course_base* next_course;
		void	set_next(course_base* );	// to set the next pointer
		void	set_next_course(course_base* );	// to set the next pointer
		course_base* get_address() { return this;}	// returns the address of this object

		char *	get_name(){	return this->course_name; }

		virtual void print_course() = 0;	// prints full description of a course
		virtual course_time*  get_times() = 0;		// returns days for a course along with hours
		virtual class_type  get_type()= 0;	// returns type: LEC,LAB,TUT
		virtual int	get_section()=0;	// returns section
};


/**
 * @brief class that contains full information about 
 *
 *
 */
class course : public course_base{

	private:
		char 		semester;	// (f)all or (w)inter
		char*		professor;	// professor's name of this section
		int		section;	// section
		class_type	type;		// 1->lecture  2->lab	3-> tutorial
		course_time*	times;		// class hours

	protected:

	public:
		course(); // default constructor
		course(char* _professor,int _section,class_type _type,course_time* _times,char* _course_name, char* _course_id);
		course(char* _professor,int _section,class_type _type,course_time* _times,const course_base &_course_base);
		course(const course & _course); // copy constructor
		~course();	// destructor


		// virtual members
		void print_course();	// prints full course info
		course_time* get_times();	// returns hours and days for a day
		class_type get_type();	// returns type: LEC,LAB,TUT
		int	get_section() { return section; }
};

int has_conflic(course_base**, int);

#endif
