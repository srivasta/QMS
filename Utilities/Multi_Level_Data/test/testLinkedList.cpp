//                              -*- Mode: C++ -*- 
// testLinkedList.cpp --- 
// Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
// Created On       : Wed Apr 25 16:21:29 2001
// Created On Node  : glaurung.stdc.com
// Last Modified By : Manoj Srivastava
// Last Modified On : Tue Aug 14 10:26:34 2001
// Last Machine Used: ember.stdc.com
// Update Count     : 149
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// $Id: testLinkedList.cpp,v 1.3 2001/10/21 08:54:13 srivasta Exp $
// 

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
static const char* version = "$Id: testLinkedList.cpp,v 1.3 2001/10/21 08:54:13 srivasta Exp $";

/** @file testLinkedList.cpp
 *  @ingroup MLD Testing
 *  @brief The test program for the multilevel data structures
 *
 */

#include <stdio.h>

#include <string>
#include <iostream>
extern "C" {
#include <string.h>
}

#include "ace/Synch.h"

#include "Debug.h"
#include "QMS_Linked_List.h"
#include "QMS_Nodes.h"
#include "QMS_Linked_List_Iterators.h"

/// A simple string comparison function
int
my_compare(const string &A, const string &B)
{
  return A < B? -1 : A == B ? 0 : 1;
}

/// a convenience declaration
typedef QMS_Sub_Type_Element<string,string,ACE_RW_Mutex> my_sub_Type;

/// Words to seed the linked lists with
const char *words[26][3] = 
  {   
    {  "abandoned",   	 "abasement",     "abashment"     },
    {  "baalist",      	 "Babbiesm",      "babble"        },
    {  "cabbagy",     	 "cableman",      "cabrerite"     },
    {  "dacker",      	 "dacryopyosis",  "dactyliotheca" },
    {  "eachwhere",   	 "earnings",      "earthfast"     },
    {  "fabulously",  	 "facilitative",  "factable"      },
    {  "gabbroic",    	 "gablewise",     "Gadaria"       },
    {  "habena",      	 "habilitate",    "habitability"  },
    {  "ianthine",    	 "Iberismal",     "Ibycus"        },
    {  "jacamar",     	 "jackbird",      "jackboy"       },
    {  "Kafir",       	 "kaikafull",     "kaiwhiria"     },
    {  "labiograph",  	 "labioplasty",   "laborously"    },
    {  "Macanese",    	 "Macedonian",    "machan"        },
    {  "nace",        	 "Naemorhedus",   "naething"      },
    {  "oarsmanship", 	 "obambulatory",  "obdurately"    },
    {  "pabular",     	 "pabulation",    "Pachons"       },
    {  "quadra",      	 "quadratus",     "quadrifarious" },
    {  "rabbi",        	 "rabbinite",     "rabbithearted" },
    {  "sabbat",      	 "sabellan",      "saboted"       },
    {  "tabefaction", 	 "tabernacle",    "tablefellow"   },
    {  "Ubiquist",    	 "udellion",      "Udolphoish"    },
    {  "vaccination",    "vacillatingly", "vacuolated"    },
    {  "waagart",        "waapanism",     "wachna"        },
    {  "xanthogen",      "Xanthomonas",   "xarque"        },
    {  "Yahganan",       "Yakutatist",    "Yankton"       },
    {  "zaffer",         "Zaglossus",     "Zaglossus"     }
  };

/**
 * @brief find a node in a linked list associated with a key
 * @return the node found, or 0, if no match
 *
 */
QMS_Node <string, string, ACE_RW_Mutex> *
find(QMS_Linked_List <string, string, ACE_RW_Mutex> *list_p, 
     string &key, int (*cmp_p)(const string&, const string&))
{
  QMS_Trace("find: ",  __LINE__, __FILE__);
  
  if((!list_p) || (!cmp_p))
   {
     std::cout << "Bad arguments" << std::endl;
     return 0;
   } /* end of if((!list_p) || (!cmp_p)) */
  
  for(QMS_Linked_List_Iterator<string, string, ACE_RW_Mutex> 
	iter(list_p);  !iter.done(); iter.advance())
   {
     if(!cmp_p(key, *(iter.key())))
      {
	return iter.get_node();
      } /* end of if(!cmp_p(key, *(this->key()))) */
   }
  return 0;
}

/**
 * @brief The main test function
 */
int
main(int argc, char *argv[])
{ 
  char * ecname_p = (char *) "QMS_Channel";
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
             << "\t-ecname NAME   : The name of the event channel"  << endl
             << "\t-e      NAME   : The name of the event channel"  << endl
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
     if (! strcmp((argv[i] + j), "ecname") || strchr((argv[i] + j), 'e'))
      {
        ecname_p = (char *) malloc (sizeof(argv[i + 1]) + 1);
        strcpy(ecname_p,argv[i + 1]);
        continue;
      }
     DEBUG1 (DEBUG_L_ERROR, "unknown argument %s", argv[i] );
   }


  /*
   * Step 1. Create the description of the multilevel data struct we
   * are going to construct. For the test, we are going to construct a
   * linked list of linked lists, and we use strings as the data as
   * well as the key. 
   */
  
  // First step: we create an object factory that we need
  Linked_List_Factory<string, string, ACE_RW_Mutex> my_object_factory;
  
  // Now need to create a linked list that shall contain the
  // descriptions of the levels we want
  ACE_Double_Linked_List<my_sub_Type > *my_type_list_p = 
    new ACE_Double_Linked_List<my_sub_Type>();
  
    
  // Now, we create the sub type element for the first level
  QMS_Sub_Type_Element<string, string, ACE_RW_Mutex> *sub_level_p =
    new QMS_Sub_Type_Element<string, string, ACE_RW_Mutex>(&my_object_factory,
							   &my_compare);

  // Insert this descripton into the linked list
  my_type_list_p->insert_tail(sub_level_p);
  
  // Now for the next level. Since the original element is saved ihn
  // the linked list, we can retask the pointer:
  sub_level_p = 
    new QMS_Sub_Type_Element<string, string, ACE_RW_Mutex>(&my_object_factory,
							   &my_compare);
  
  // Insert this description into the linked list
  my_type_list_p->insert_tail(sub_level_p);

  // Create the data structure, passing the details of the sublevels,
  // given that we know that the top level is going to be a linked
  // list. 
  QMS_Linked_List<string, string, ACE_RW_Mutex> *my_data_struct_p =
    new QMS_Linked_List<string, string, ACE_RW_Mutex>(my_type_list_p);
  

  /*
   * Step 2: Fill in the data structure. 
   * 
   */
  
  // Fill in the top level
  for(char c='a'; c <= 'z'; c++)
   {
     
     string *tmp_p = new string();
     string *key_p = new string();
     string *ret_p;
     
     tmp_p[0] = c;
     key_p[0] = c;

     ret_p = my_data_struct_p->insert_tail(tmp_p, key_p);
   } /* end of for(char c='a'; c = <= 'z'; c++) */


  // Now for the second level  
  string *tmp_p = new string;
  QMS_Node <string, string, ACE_RW_Mutex> *my_node_p = 0;
  QMS_Linked_List<string, string, ACE_RW_Mutex> *lower_level_p = 0;
  
  for(char c='a'; c <= 'z'; c++)
   {
     tmp_p[0] = c;
     my_node_p = find(my_data_struct_p, *tmp_p, &my_compare);
     if(!my_node_p)
      {
	std::cout << "DEBUG: Could not find node for char "
		  << *tmp_p
		  << std::endl;
	continue;
      } /* end of if(!my_node_p) */
     
     lower_level_p = 
       static_cast<QMS_Linked_List<string, string, ACE_RW_Mutex> * >
       (my_node_p->get_container());

     if(!lower_level_p)
      {
	std::cout << "DEBUG: No second level list for char "  
		  << *tmp_p
		  << std::endl;
	continue;
      } /* end of if(!lower_level_p) */
     
     // lock the top level, since we are going to be adding to the
     // second level
     int ret = my_data_struct_p->get_read_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not lock the top level"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */
     
     // lock the node
     ret = my_node_p->get_write_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not lock node"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */
     
     for(int i = 0; i < 3; i++)
      {
	string *value_p = new string(words[c - 'a'][i]);
	string *key_p   = new string(words[c - 'a'][i]);

	lower_level_p->insert_tail(value_p, key_p);
      } /* end of for(int i = 0; i < 2; i++) */
     
     // Unlock the node
     ret = my_node_p->release_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not unlock node"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */
     
     // Unlock the top level
     ret = my_data_struct_p->release_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not unlock the top level"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */

   } /* end of for(char c='a'; c <= 'z'; c++) */
  delete tmp_p;  

  /*
   * Step 2: print
   * 
   */
  
  for(QMS_Linked_List_Reverse_Iterator<string, string, ACE_RW_Mutex>
 	outer(my_data_struct_p);  !outer.done(); outer.advance())
   {
     std::cout << *(outer.next()) << ":\t";

     lower_level_p = 
       static_cast<QMS_Linked_List<string, string, ACE_RW_Mutex> * >
       ((outer.get_node())->get_container());
  
     // lock the top level
     int ret = my_data_struct_p->get_read_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not lock the top level"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */
     
     std::cout << "    ";
     for(QMS_Linked_List_Iterator<string, string, ACE_RW_Mutex>
	   inner(lower_level_p);  !inner.done(); inner.advance())
      {
	std::cout << *inner.next() << "\t\t";
      } /* end of for(QMS_Linked_List_Iterator<string, string, ACE_RW_Mutex> inner(lower_level_p);  !inner.done(); inner.advance()) */
     std::cout << std::endl;
     
     // Unlock the top level
     ret = my_data_struct_p->release_lock();
     if(ret < 0)
      {
	std::cout << "DEBUG: Could not unlock the top level"
		  << std::endl;
	continue;
      } /* end of if(ret < 0) */

   } /* end of for(QMS_Linked_List_Iterator<string, string, ACE_RW_Mutex> 	outer(list_p);  !outer.done(); outer.advance()) */
  

  exit (0);
} /* end of main() */
 
