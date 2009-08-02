/**
 *  @file Implementation of planner.h
 *
 *
 */

#include <iostream>
#include "planner.h"
using namespace std;


/**
 * constructor	default 
 */
course_base::course_base()	// default constructor
{
	course_name = NULL;
	course_id = NULL;	
	count = 0;
	next = NULL;
	next_course = NULL;
}
/**
 * constructor 1 to create a course that doesn't exist already
 */
course_base::course_base(char* _course_name, char* _course_id)
{
	course_name = new char[strlen(_course_name)+1];			// WARNING: allocating dynamic memory
	course_id = new char[strlen(_course_id)+1];
	strcpy(course_name,_course_name);
	strcpy(course_id,_course_id);
	count = 1;
	next= NULL;
	next_course= NULL;
}
/**
 * constructor	2 to add a course with different section
 */
course_base::course_base(const course_base& _course_base)	// copy constructor
{
	course_name = new char[strlen( _course_base.course_name )];			// WARNING: allocating dynamic memory
	course_id = new char[strlen( _course_base.course_id )];
	strcpy(course_name,_course_base.course_name);
	strcpy(course_id,_course_base.course_id);
	
	next=NULL;
	next_course= NULL;
}
/**
 * destructor
 */
course_base::~course_base()	// destructor	
{
	if( course_name != NULL )
		delete [] course_name;
	if( course_name != NULL )
		delete [] course_id;

/*				????????????		deleting the list ***		** ?!?!?!??!??!?!? */
}
/**
 * @brief	prints course name and id
 */
void course_base::print_course_id()	// prints full name + id of a course + semester(s/f)
{
	cout << "course: " << course_name << endl;	
	cout << "id: " << course_id << endl;
}

/**
 *	@brief increment count which keeps count of objects
 */
void course_base::increment_count()
{
	count++;
}

/**
 *	@brief sets the next pointer to create a linked list
 */
void course_base::set_next(course_base* _next)
{
	next = _next;
}

/**
 *	@brief sets the next course to create a linked list
 */
void course_base::set_next_course(course_base* _next)
{
	next_course = _next;
}

/**************************************
*	Course
*
***************************************/

/**
 * @brief default constructor
 */
course::course()
{
	semester='\0';
	professor = NULL;
	times = NULL;
}
/**
 * @brief constructor 1
 */
course::course(char* _professor,int _section,class_type _type,course_time* _times,char* _course_name, char* _course_id) \
: course_base(_course_name,_course_id)
{
	section = _section;
	type = _type;
		
	professor = new char[strlen(_professor)+1];
	strcpy(professor,_professor);
	
	if( _type == LAB || _type == TUT )
	{
		times = new course_time[1];
		times = _times;
	}
	else	// lecture
	{
		times = new course_time[3];
		for(int i=0;i<3;i++)
		{
			times[i] = _times[i];
		}
	}
}
/**
 * @brief constructor 2 when a course already exists, for a new section
 */
course::course(char* _professor,int _section,class_type _type,course_time* _times,const course_base &_course_base)  \
: course_base(_course_base)
{
	section = _section;
	type = _type;
		
	professor = new char[strlen(_professor)+1];
	strcpy(professor,_professor);
	
	if( _type == LAB || _type == TUT )
	{
		times = new course_time[1];
		times = _times;
	}
	else	// lecture
	{
		times = new course_time[3];
		for(int i=0;i<3;i++)
		{
			times[i] = _times[i];
		}
	}
}
/**
 * @brief copy constructor
 */
course::course(const course & _course) \
: course_base(_course.course_name,_course.course_id)
{
	section = _course.section;
	type = _course.type;
		
	professor = new char[strlen(_course.professor)+1];
	strcpy(professor,_course.professor);
	
	if( _course.type == LAB || _course.type == TUT )
	{
		times = new course_time[1];
		times = _course.times;
	}
	else	// lecture
	{
		times = new course_time[3];
		for(int i=0;i<3;i++)
		{
			times[i] = _course.times[i];
		}
	}

}		
/**
 * @brief destructor
 */
course::~course()
{
	if( professor != NULL ) delete [] professor;
	//if( times != NULL ) delete [] times;
}
/**
 * @brief prints full information about a course:
 *        name, id, professor, section, type, hourse
 */ 
void course::print_course()
{
	course_base::print_course_id();
	cout << semester << " " << section << endl;
	cout << "Professor " << professor << endl;

	print_type(type);
	print_times(times,type);
}
/**
 *	@breif returns days+times
 */
course_time* course::get_times()		
{
	return ( this->times );
}
/**
 *	@breif returns type of class
 */
class_type course::get_type()
{
	return (this->type);
}








/**
 * @brief checks if the given course have a confilct
 *
 *
 * @return 0 if no conflicts, otherwise number of conflicts found
 */
int has_conflic(course_base** keys,int num_of_courses)
{
	int num_conflicts = 0;
	// create a matrix of all time slots in a week
	int week_calender[NUM_HOURS][NUM_DAYS]= {0};
	// traverse courses and mark their times
	// print conflic
	for(int i=0;i<num_of_courses;i++)
	{
	   if( keys[i]->get_type() == LEC )
	   {
		course_time* temp=keys[i]->get_times();
		for(int j=0;j<3;j++)
		{
			if( week_calender[temp[j].hour-1][temp[j].day-1] == 0 )
				week_calender[temp[j].hour-1][temp[j].day-1] = i+1; // mark using the index of the course in keys[]
			else
			{
				cout << endl << "!!! Found the following conflict: ";
				convert_day(temp[j].day);
				convert_time(temp[j].hour);
				cout << 	"----------------------------------" << endl;
				keys[ week_calender[temp[j].hour-1][temp[j].day-1]-1 ]->print_course_id();
				cout << "section: " << keys[ week_calender[temp[j].hour-1][temp[j].day-1]-1 ]->get_section() << endl ;
				cout << " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
				keys[i]->print_course_id();
				cout << "section: " <<  keys[i]->get_section() << endl;
				cout << 	"----------------------------------" << endl;
				num_conflicts++;
			}
		}
	   }
	   else // for TUT and Practical
	   {
		if( week_calender[keys[i]->get_times()->hour-1][keys[i]->get_times()->day-1] == 0 )
			week_calender[keys[i]->get_times()->hour-1][keys[i]->get_times()->day-1] = i+1; // mark using the index of the course in keys[]
		else
		{
			cout << endl << "!!! Found the following conflict: " << endl;
			convert_day(keys[i]->get_times()->day);
			convert_time(keys[i]->get_times()->hour);
			cout << 	"----------------------------------" << endl;
			keys[ week_calender[keys[i]->get_times()->hour-1][keys[i]->get_times()->day-1]-1 ]->print_course_id();
			cout << "section: " << keys[ week_calender[keys[i]->get_times()->hour-1][keys[i]->get_times()->day-1]-1 ]->get_section() <<endl;
			cout << " XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX " << endl;
			keys[i]->print_course_id();
			cout << "section: " << keys[i]->get_section() << endl;
			cout << 	"----------------------------------" << endl;
			num_conflicts++;
		}

	   }
	}
	return num_conflicts;

}







