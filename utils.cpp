/**
 * @file
 * @author shervin.mehryar@gmail.com
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Please be use
 * caution when used and always DOUBLE CHECK RESULTS!!!!!
 *
 * @section DESCRIPTION
 *
 * Implementation of utils.h
 */
#include <iostream>
#include "planner.h"
#include "utils.h"
using namespace std;
#include <fstream>


course_base * list=NULL;

/**
 * @brief prints type of class: lecture, tutorial, practical
 */
void print_type(class_type type)
{
	switch(type){
		case LEC:
			cout << "LEC" << endl;
		break;
		case TUT:
			cout << "TUT" << endl;
		break;
		case LAB:
			cout << "LAB" << endl;
		break;
	default:
		cout << "Error: Invalid type" << endl;
	}
}
/**
 * @brief prints hours of class: day and hour
 */
void print_times(course_time* times,class_type type)
{
	switch(type){
		case LEC:
			for(int i=0;i<3;i++)
			{
				convert_day(times[i].day);
				convert_time(times[i].hour);
			}
		break;
		case TUT:
				convert_day(times->day);
				convert_time(times->hour);
		break;
		case LAB:
				convert_day(times->day);
				convert_time(times->hour);
		break;
	default:
		cout << "Error: Invalid type" << endl;
	}

}

/**
 *	@brief parses course files and extract stored courses
 *
 */
int	parse_course_files(char* filename)
{
	string line;
	ifstream myfile(filename);
	//  open file
	if (myfile.is_open())
	{	
		while (! myfile.eof() )
		{	
			char* name_temp; char* sec_temp;  char* day_temp ;
			char* id_temp; char* prof_temp;char* type_tempChar; char* time_temp;
			course_time* course_time_temp= new course_time[3]; class_type type_temp;

			int num_of_times = 0;	// how many days/times specified

			getline (myfile,line);	       		
			while( line.find(END) == string::npos && !myfile.eof()  )
			{	
				if( line.find(COMMENT) == string::npos )	// ignore comments
				{
					if( line.find(NAME) !=  string::npos )
					{ 
						// extract name
						int ind1 = line.find(SEPERATOR);
						int ind2 = line.find(SEPERATOR,ind1+1);
						name_temp = new char[ind2-ind1+1];
						int length=line.copy(name_temp,ind2-ind1-1,ind1+1);
						name_temp[length]='\0';
						// extract id
						ind1 = line.find(SEPERATOR,ind2+1);
						ind2 = line.find(SEPERATOR,ind1+1);
						id_temp = new char[ind2-ind1+1];
						length=line.copy(id_temp,ind2-ind1-1,ind1+1);
						id_temp[length]='\0';
						//cout << "name: " << name_temp << " || id: " << id_temp <<  endl;

					}
					else if( line.find(INSTRUCTOR) !=  string::npos )
					{
						// extract instructor
						int ind1 = line.find(SEPERATOR);
						int ind2 = line.find(SEPERATOR,ind1+1);
						prof_temp = new char[ind2-ind1+1];
						int length=line.copy(prof_temp,ind2-ind1-1,ind1+1);
						prof_temp[length]='\0';
						//cout << "instructor: " << prof_temp << endl;

					}
					else if( line.find(SECTION) !=  string::npos )
					{
						// extract section
						int ind1 = line.find(SEPERATOR);
						int ind2 = line.find(SEPERATOR,ind1+1);
						sec_temp = new char[ind2-ind1+1];
						int length=line.copy(sec_temp,ind2-ind1-1,ind1+1);
						sec_temp[length]='\0';
						//cout << "section: " << sec_temp << endl;

					}
					else if( line.find(TYPE) !=  string::npos )
					{
						// extract type
						int ind1 = line.find(SEPERATOR);
						int ind2 = line.find(SEPERATOR,ind1+1);
						type_tempChar = new char[ind2-ind1+1];
						int length=line.copy(type_tempChar,ind2-ind1-1,ind1+1);
						type_tempChar[length]='\0';
						if( strcmp(type_tempChar,"LEC") == 0 ) type_temp=LEC;
						else if( strcmp(type_tempChar,"LAB") == 0 ) type_temp=LAB;
						else if( strcmp(type_tempChar,"TUT") == 0 ) type_temp=TUT;
						//cout << "type: " << type_tempChar << endl;

					}
					else if( line.find(TIME) !=  string::npos )
					{
						// extract day
						int ind1 = line.find(SEPERATOR);
						int ind2 = line.find(SEPERATOR,ind1+1);
						day_temp = new char[ind2-ind1+1];
						int length=line.copy(day_temp,ind2-ind1-1,ind1+1);
						day_temp[length]='\0';
						// extract time
						ind1 = line.find(SEPERATOR,ind2+1);
						time_temp = new char[ind1-ind2+1];
						length=line.copy(time_temp,ind1-ind2-1,ind2+1);
						time_temp[length]='\0';
						//cout << "day: " << day_temp << " || time: " << time_temp <<  endl;
						// set values to structure
						if( strcmp(day_temp,"monday") == 0 ) course_time_temp[num_of_times].day = monday;
						else if( strcmp(day_temp,"tuesday") == 0 ) course_time_temp[num_of_times].day = tuesday;
						else if( strcmp(day_temp,"wednesday") == 0 ) course_time_temp[num_of_times].day = wednesday;
						else if( strcmp(day_temp,"thursday") == 0 ) course_time_temp[num_of_times].day = thursday;
						else if( strcmp(day_temp,"friday") == 0 ) course_time_temp[num_of_times].day = friday;
						if( strcmp(time_temp,"_9_10") == 0 ) course_time_temp[num_of_times].hour =_9_10;
						else if( strcmp(time_temp,"_10_11") == 0 )course_time_temp[num_of_times].hour=_10_11;
						else if( strcmp(time_temp,"_11_12") == 0 )course_time_temp[num_of_times].hour=_11_12;
						else if( strcmp(time_temp,"_12_1") == 0 )course_time_temp[num_of_times].hour=_12_1;
						else if( strcmp(time_temp,"_1_2") == 0 )course_time_temp[num_of_times].hour=_1_2;
						else if( strcmp(time_temp,"_2_3") == 0 )course_time_temp[num_of_times].hour=_2_3;
						else if( strcmp(time_temp,"_3_4") == 0 )course_time_temp[num_of_times].hour=_3_4;
						else if( strcmp(time_temp,"_4_5") == 0 )course_time_temp[num_of_times].hour=_4_5;
						else if( strcmp(time_temp,"_5_6") == 0 )course_time_temp[num_of_times].hour=_5_6;
						else if( strcmp(time_temp,"_0_0") == 0 )course_time_temp[num_of_times].hour=_0_0;
						else { cout << "Error: invalid time: " << name_temp <<" " << id_temp << " "  << sec_temp << ":"<< time_temp << endl; num_of_times = 0; }

						num_of_times++;
					}// end of if

				}//end of if
				getline (myfile,line);	
		 	}// end of while()
			if( num_of_times > 0 )	// add info to course list
			{
			

				course_base *listPtr = list;
				course_base *old_listPtr=NULL;
				// check if course already listed
				while( listPtr != NULL && strcmp(listPtr->get_name(),name_temp)!= 0){ old_listPtr = listPtr; listPtr = listPtr->next_course; }
				if(listPtr!= NULL && strcmp(listPtr->get_name(),name_temp)== 0 ) // if already exists
				{
					course_base *base_coursePtr = listPtr;
					while( listPtr != NULL ){ old_listPtr = listPtr; listPtr = listPtr->next; } // find last location
					course* temp_obj= new course(prof_temp,atoi(sec_temp),type_temp, course_time_temp ,*base_coursePtr);
					base_coursePtr->increment_count();
					old_listPtr->set_next( temp_obj->get_address() );	
				}		
				else	// if doesn't exist
				{
					course* temp_obj= new course(prof_temp,atoi(sec_temp), type_temp, course_time_temp, name_temp, id_temp);
					if( list == NULL )
					{
						list = temp_obj;
					}
					else
					{
						old_listPtr->set_next_course( temp_obj->get_address() );
					}
				}
			}
		} // end of while( !myfile.eof() )
		myfile.close();
	 }

return 0;
}
/**
 * @brief prints full list of courses in memory
 */
void print_full_courses()
{
	cout << "\t\tfull courses:\t\t" << endl;
	cout << "--------------------------------------------------" << endl;
	course_base* basePtr = list;
	while(basePtr != NULL)
	{
		course_base* floatPtr=basePtr;
		while(floatPtr != NULL)
		{
			floatPtr->print_course();
			cout << endl;
			floatPtr = floatPtr->next;
		}
		cout << "\t - - * * * - - \t" << endl;
		basePtr = basePtr->next_course;
		floatPtr = basePtr;
	}

}
/**
 * @brief prints list of courses
 */
void print_course_list()
{
	int counter=0;
	cout << "\t\tcourses:\t\t" << endl;
	cout << "--------------------------------------------------" << endl;
	course_base* basePtr = list;
	while(basePtr != NULL)
	{
		cout << ++counter << " ) ";
		basePtr->print_course_id();
		basePtr = basePtr->next_course;
	}

}



