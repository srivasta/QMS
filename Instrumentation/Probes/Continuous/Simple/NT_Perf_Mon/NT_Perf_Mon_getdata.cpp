//                              -*- Mode: C++ -*- 
// NT_Perf_Mon_getdata.cpp --- 
// Author           : Shivakumar Patil and Bhanu Hosangadi.
// Status           : Unknown, Use with caution!
// HISTORY          : 
// Description      : 
// 
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


/** @file 
 *  @ingroup NTPerfMonProbe
 *  @brief Contains implementation of a Probe that delivers NT Performance Monitor data
 *
 * This probe contains an implementation of a probe that delivers Windows
 * NT performance monitor data. It can deliver any system counter that is
 * available on Windows NT.
 */


#include "NT_Perf_Mon_getdata.h"
#include "Instrumentation.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
 using namespace std;

#define INITIAL_CALL		1
#define DIFFERENT_COUNTER	2
#define NOT_A_COUNTER      -1
#define PS_COUNTER	"/proc/ps"

HQUERY						getData_hQuery	= 0;
HCOUNTER					getData_counters;
PDH_FMT_COUNTERVALUE		getData_fmtValue;


const char *perfmon_processList_fmt = "\
    <?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
    <perfmonProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/perfmonProbes\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/perfmonProbes \n\
      perfmonProbes.xsd\">\n\
      <perfmonData>\n\
        <dataid>%ld</dataid>\n\
        <resource>%s</resource>\n\
          <columnData>\n\
           <title>\n\
            <column>PID</column>\n\
            <column>Process Name</column>\n\
           </title>\n\
           %s\n\
         </columnData>\n\
      </perfmonData>\n\
    </perfmonProbe>\n\
\n";

const char *process_row_fmt = "\
           <row>\n\
              <column>%u</column>\n\
              <column>%s</column>\n\
           </row>\n\
";


const char *perfmon_counterValue_fmt = "\
    <?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
    <perfmonProbe xmlns=\"http://www.stdc.com/2001/QMS/Probes/perfmonProbes\"\n\
      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
      xsi:schemaLocation=\"http://www.stdc.com/2001/QMS/Probes/perfmonProbes \n\
      perfmonProbes.xsd\">\n\
      <perfmonData>\n\
        <dataid>%ld</dataid>\n\
	<resource>%s</resource>\n\
        <plotData>\n\
          <numericData>%ld.00</numericData>\n\
		  <units>%s</units>\n\
        </plotData>\n\
      </perfmonData>\n\
    </perfmonProbe>\n\
\n";


int getdata(char *counterName, char *perfmon_data)
{
	// variables used by the processlist logic.
	DWORD  aProcesses[1024], cbNeeded, oProcesses;
    unsigned int i;
    HMODULE hMod;
    char rows_data[BUFSIZ + 8192] = "", data[BUFSIZ] = "";
	int ret = 0;

	// variables used by the NT counter value.
	static char prevCounter[500];
	int error, rc = 0;
	unsigned long value;
	static unsigned long dataid=0;

	DEBUG0 (2, "Inside the getdata function");

	if (strcmp (counterName, PS_COUNTER) == 0)
	{
		if ( !EnumProcesses ( aProcesses, sizeof (aProcesses), &cbNeeded ) )
		{
			fprintf(stderr,"Unable to open get proceses list\n");
		}
		else
		{
			// Calculate how many process identifiers were returned.
			oProcesses = cbNeeded / sizeof (DWORD);
			//std::cerr << "No of processes are ->  " << oProcesses 
				      //<< std::endl ;

			for ( i = 0; i < oProcesses; i++ )
			{
				char szProcessName[MAX_PATH] = "unknown";

				HANDLE hProcess = OpenProcess(	PROCESS_QUERY_INFORMATION |
												PROCESS_VM_READ,
												FALSE, 
												aProcesses[i]);

				// Get a process name.

				if (hProcess )
				{
					if (EnumProcessModules ( hProcess, &hMod, sizeof (hMod),
											&cbNeeded) )
					{
						//GetModuleBaseName
						GetModuleFileNameEx ( hProcess, hMod, szProcessName,
				  						sizeof(szProcessName) );
					}
				}
				if(strcmp(szProcessName, "unknown") != 0)
				{
					//std::cerr << szProcessName<< "\t" << aProcesses[i] << std::endl;
                    //sprintf (tbuf, "%u", aProcesses[i]);
					//std::cerr << tbuf <<  aProcesses[i] << std::endl;
					ret = _snprintf(data, BUFSIZ, process_row_fmt, aProcesses[i], szProcessName);
        
					if(ret == -1 || ret > (BUFSIZ) )
					{
                        std::cerr << "Buffer overflow in single row data , ignoring"
                                  << std::endl;
					}
                    
					strcat(rows_data, data);

				} // end of if(strcmp(szProcessName, "unknown") != 0)

			} // end of for ( i = 0; i < oProcesses; i++ )


			//std::cerr << "About to send the process list data\n"; 
			// Now send the process list data.
			ret = _snprintf(perfmon_data, BUFSIZ + 8192, perfmon_processList_fmt,
				            dataid++, counterName, rows_data);

			if(ret == -1 || ret > (BUFSIZ + 8192 ) )
					{
                        std::cerr << "Buffer overflow in processList data, ignoring"
                                  << std::endl;
					}

			strcat(perfmon_data, STDC::QMS::Citizen::delimiter);
			strcat(perfmon_data, "\n");

		} // end of else 
		
		return 0;

	} // if (strcmp (counterName, PS_COUNTER) == 0)

	if(getData_hQuery == 0)  // first time initialize
	{
	  error = PdhOpenQuery( NULL, 0, &getData_hQuery );
      //printf("PdhOpenQuery error = %x\n", error);
	  strcpy(prevCounter, counterName);
	  error = PdhAddCounter( getData_hQuery, prevCounter, 0,
		                     &getData_counters);
	  rc = INITIAL_CALL;
	  if(error != ERROR_SUCCESS)
	  {
	    rc = NOT_A_COUNTER;
	  }
      //printf("return of adding counter = %x\n", error);
	}
	else if(strcmp(counterName, prevCounter) != 0)
    {
	  PdhRemoveCounter(getData_counters); // remove old one and add new
      //printf("PdhOpenQuery error = %x\n", error);
	  strcpy(prevCounter, counterName);
	  error = PdhAddCounter( getData_hQuery, prevCounter, 0,
		                     &getData_counters);
      //printf("return of adding counter = %x\n", error);
	  rc = DIFFERENT_COUNTER;
	  if(error != ERROR_SUCCESS)
	  {
	    rc = NOT_A_COUNTER;
	  }
	}
      
	 DEBUG0 (2, "Go update the data in the getData_counters");
	  // Go update the data in the getData_counters
	  error = PdhCollectQueryData( getData_hQuery );

	  // Get the formatted version of the counter
	  // value & fill it in
	  DEBUG0 (2, "Get the formatted version of the counter");
	  error = PdhGetFormattedCounterValue(
		         getData_counters,PDH_FMT_LONG,0, &getData_fmtValue);
	  value = getData_fmtValue.longValue;

	  DEBUG0 ( 2, "Creating the XML message");

	  // Using the counter name to create the units field, since that is most
	  // reflective of the actual data being sent back by the read_counter call

	  //Now send the process list data.
	  ret = _snprintf(perfmon_data, BUFSIZ + 8192, perfmon_counterValue_fmt,
		  dataid++, counterName, value, (counterName + ((std::string) counterName).rfind('\\') + 1 ) );

	  if(ret == -1 || ret > (BUFSIZ + 8192 ) )
	  {
		  std::cerr << "Buffer overflow in counter value data, ignoring"
                    << std::endl;
	  }

	  DEBUG0 ( 2, "Adding the Probe delimiter");
	  strcat(perfmon_data, STDC::QMS::Citizen::delimiter);
	  strcat(perfmon_data, "\n");

	  DEBUG0 (2, "Leaving the getdata method");

	  return rc;
}

