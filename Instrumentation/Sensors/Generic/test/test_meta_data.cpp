   //                              -*- Mode: C++ -*- 
// test_meta_data.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Sun Jul 22 15:31:03 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Wed Dec  5 00:11:34 2001
// Last Machine Used: glaurung.green-gryphon.com
// Update Count     : 12
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
// 

/** @file 
 *  @ingroup GenericSensor 
 *  @brief implementation of a test program
 *
 * $Id: test_meta_data.cpp,v 1.6 2001/12/09 02:06:24 nath Exp $
 */


/*
 * Copyright (C) 2001 System/Technology Development Corporation
 * This file is part of QoS Metrics Services (QMS)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA
 *
 * You may contact System/Technology Development Corporation at
 *
 *     System/Technology Development Corporation
 *     Suite 500, Center for Innovative Technology,
 *     2214 Rock Hill Road,
 *     Herndon, VA 20170    
 *     (703) 476-0687
 */


/// RCS version string
static const char* version = 
"$Id: test_meta_data.cpp,v 1.6 2001/12/09 02:06:24 nath Exp $";

#include "Meta_Data.cpp"

int main(int argc, char *argv[])
{
  char *filename_p = 0;

  DEBUG0 (DEBUG_L_CALL, "DEBUG: parsing arguments\n");
  for (int i = 0; i < argc; i++)
   {
     if (!argv[i])           { break; }
     if (argv[i][0] != '-')  { continue; }
     int j = 1;
     if (argv[i][1] == '-')  {
       if (argv[i][2] == 0)  { break; } // handle -- end of options
       j = 2;                   // handle --argument
     }
     if (strstr((argv[i] + j), "ORB"))  { continue; }
     if (! strcmp((argv[i] + j), "help") || strchr((argv[i] + j), 'h'))
      {                         // -h or --help
        cout << argv[0] << version << endl
             << "Usage: " << argv[0] << "[CORBA OPTIONS] [OPTIONS]"
             << endl
             << "\t-h             : This help text"  << endl
             << "\t-v             : Prints out the version"  << endl
             << "\t-file Filename : Read XML data from here"  << endl
             << "\t-f    Filename : Read XML data from here"  << endl
          ;
        exit (0);
      }
     if (! strcmp((argv[i] + j), "version") || strchr((argv[i] + j), 'v'))
      {
        cout << argv[0] << ": Version "<< version << endl;
        exit (0);
      }

     if (! strcmp((argv[i] + j), "file") || strchr((argv[i] + j), 'f'))
      {
        filename_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(filename_p,argv[i + 1]);
        continue;
      }
     std::cerr << "unknown argument " << argv[i] << std::endl;
   }

  STDC::QMS::Citizen::Meta_Data *my_data_object = 
    new STDC::QMS::Citizen::Meta_Data();
  STDC::QMS::Citizen::Sensor_Data_Element *my_data_one = 
    new STDC::QMS::Citizen::Sensor_Data_Element;
  STDC::QMS::Citizen::Sensor_Data_Element *my_data_two = 
    new STDC::QMS::Citizen::Sensor_Data_Element;
  cout << "Created the data objects" << std::endl;
  string name = "this is my name: One";
  string second = "this is my name: Two";

  my_data_one->set_name(name);
  my_data_two->set_name(second);
  cout << my_data_one->get_name()  << std::endl;
  cout << my_data_two->get_name()  << std::endl;

  
  my_data_one->set_int_val(101);
  my_data_two->set_int_val(202);
  cout << "And the integer value for one is" 
       << my_data_one->get_int_val()  << std::endl;
  cout << "And the integer value for two is" 
       << my_data_two->get_int_val()  << std::endl;

  string value_one = "My Value is one";
  string value_two = "My Value is one";

  my_data_one->set_string_val(value_one);
  my_data_two->set_string_val(value_two);
  cout << my_data_one->get_string_val()  << std::endl;
  cout << my_data_two->get_string_val()  << std::endl;

  my_data_object->add_invocation_parameter(my_data_one);
  my_data_object->add_invocation_parameter(my_data_two);
  
  my_data_object->add_offer_parameter(my_data_one);
  my_data_object->add_offer_parameter(my_data_two);
  
  vector<STDC::QMS::Citizen::Sensor_Data_Element *> invocation_params =
    my_data_object->get_invocation_parameters();

  unsigned int i = 0;
  
  for(i = 0; i < invocation_params.size(); i++)
   {
     if(invocation_params[i])
      {
	cout << invocation_params[i]->get_name()  << std::endl;
	cout << invocation_params[i]->get_int_val()  << std::endl;
	cout << invocation_params[i]->get_string_val()  << std::endl;
	
      } /* end of if(test_p) */
     
   } /* end of for(i = 0, i < invocation_params.size(), i++) */
  

  exit (0);
} /* end of main() */

