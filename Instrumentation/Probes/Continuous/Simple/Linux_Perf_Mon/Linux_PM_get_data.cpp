/*********************************************************************
 * Copyright (c) 2001-2002, System/Technology Development Corporation .
 *                
 * Filename:      Linux_PM_get_data.cpp
 * Version:       1.0
 * Description:   Linux Performance Monitor Probe
 *                
 * Author:        Shivakumar Patil (shivakumar.patil@stdc.com)
 * Created at:    Tue Dec 11 19:20:01 2001
 * Modified by:   Amarendranath Vadlamudi <nath@vedam>
 * Modified at:   Sat Jan 26 12:26:31 2002
 * Status:        Experimental, do not distribute.
 * Update count:  227
 ********************************************************************/

#include "Linux_PM_get_data.h"
#include "Debug.h"
#include "ace/OS.h"


int get_data (char *counter,  char *probe_output)
{

    long total = 0, used = 0;
    double value = 0.0 ;
        
    // variables needed for CPU utilization calculation
    long e_user = 0 , e_nice = 0, e_system = 0 ;
    double e_timestamp = 0; 
    struct timeval time ;
    struct timezone tz;

    FILE * fp;
    char buf[MAX_LINE_BUFFER], *t1, *t2, *debug;
    debug = getenv("RESOURCE_DEBUG");

    // The formats that most of these probes use for printing the
    // output as defined by the schema .
    const char *plotData_fmt = "<plotData>\n\
         <numericData>%.2f</numericData>\n\
         <units>%s</units>\n\
       </plotData>";

    const char *columnData_fmt = "<columnData>\n\
          %s\
        </columnData>";

    const char *rowData_fmt = "          <row>\n\
            %s\n\
          </row>\n";

    const char *titleData_fmt = "<title>\n\
            %s\n\
          </title>\n";

    // Get Mem %Utilization from /proc/meminfo
    if(strcmp(counter, MEM_COUNTER) == 0)
    {  /* format is :Mem:   ddddd    ddddd xxxxxxxxxxxxxxx" */

	fp = fopen("/proc/meminfo", "r");
	if(fp == NULL)
	{
	    DEBUG0(2, "ERROR: Unable to find /proc/meminfo.\n");
	    fclose(fp);
	    return -1;
	}
     
	// Mem: is the second line in /proc/meminfo. So forward 2 lines
	fgets(buf, MAX_LINE_BUFFER-1, fp);
	fgets(buf, MAX_LINE_BUFFER-1, fp);
	if(strncmp(buf, "Mem:", 4) != 0)
	{
	    DEBUG0(2, "Invalid format in /proc/meminfo file\n");
	    fclose(fp);
	    return -1;
	}
	t1 = &buf[4];   //Offset the string "Mem:"
	while(*t1 == ' ')
	    t1++;

	if(debug != NULL)
	    DEBUG1 (2, "INPUT = \"%s\"\n", t1);
	if((t2 = strchr(t1, ' ')) != NULL)
	{
	    *t2 = '\0';
	    total = atol(t1);
	    t2++;
	    while(*t2 == ' ')
		t2++;
	    if((t1 = strchr(t2, ' ')) != NULL)
	    {
		*t1 = '\0';
		used = atol(t2);
	    }
	    else
	    {
		DEBUG0 (2, "Invalid format in /proc/meminfo file\n");
		fclose(fp);
		return -1;
	    }
	}
	else
	{
	    DEBUG0 (2, "Invalid format in /proc/meminfo file\n");
	    fclose(fp);
	    return -1;
	}
	if(debug != NULL)
	    DEBUG2 (2, 
		    "total mem = %ld, used mem = %ld  (bytes)\n", total, used);
	if(total != 0 )
	{

	    value = (used*100.0)/total;
	    DEBUG1 (2, "Percent Memory Utilization = %f\n", value);
	    snprintf(probe_output, BUFSIZ + 24576, plotData_fmt, value, 
		     "%Utilization");
	}
	fclose(fp);
	return 0;
    }

    // Get Swap %Utilization from /proc/meminfo
    else if(strcmp(counter, SWAP_COUNTER) == 0)
    {  /* format is :Swap:   ddddd    ddddd xxxxxxxxxxxxxxx" */

	fp = fopen("/proc/meminfo", "r");
	if(fp == NULL)
	{
	    DEBUG0 (2, "ERROR: Unable to find /proc/meminfo.\n");
	    fclose(fp);
	    return -1;
	}

	// Swap: is the third line in /proc/meminfo. So forward 3 lines
	fgets(buf, MAX_LINE_BUFFER-1, fp);
	fgets(buf, MAX_LINE_BUFFER-1, fp);
	fgets(buf, MAX_LINE_BUFFER-1, fp);
	if(strncmp(buf, "Swap:", 5) != 0)
	{
	    DEBUG0 (2, "Invalid format in /proc/meminfo file\n");
	    fclose(fp);
	    return -1;
	}
	t1 = &buf[5]; //Offset the string "Swap:"
	while(*t1 == ' ')
	    t1++;

	if(debug != NULL)
	    DEBUG1 (2, "INPUT = \"%s\"\n", t1);
	if((t2 = strchr(t1, ' ')) != NULL)
	{
	    *t2 = '\0';
	    total = atol(t1);
	    t2++;
	    while(*t2 == ' ')
		t2++;
	    if((t1 = strchr(t2, ' ')) != NULL)
	    {
		*t1 = '\0';
		used = atol(t2);
	    }
	    else
	    {
		DEBUG0 (2, "Invalid format in /proc/meminfo file\n");
		fclose(fp);
		return -1;
	    }
	}
	else
	{
	    DEBUG0 (2, "Invalid format in /proc/meminfo file\n");
	    fclose(fp);
	    return -1;
	}
	if(debug != NULL)
	    DEBUG2 (2, "total swap = %ld, used swap = %ld (bytes)\n", 
		    total, used);
	if(total != 0 )
	{
//        *value = (total - used)*100.0/total;
	    value = (used * 100.0)/total;
	    DEBUG1 (2, "Percent Swap Utilization = %f\n", value);
	    snprintf(probe_output, BUFSIZ + 24576, plotData_fmt, 
		     value, "%Utilization");
	}
	fclose(fp);
	return 0;
    }
	
    // Get CPU %Utlization from /proc/stat
    else if(strcmp(counter, CPU_COUNTER) == 0)
    { 

	// Reading the line for cpu. We may wish to diversify this
	// to work for all cpu's on the machine
	// format is: cpu ddddd ddddd ddddd ddddd

	// Need two successive reads to do the calculations
	// Do it as fast as possible.
	fp = fopen("/proc/stat", "r");
	if (fp == NULL )
	{
	    DEBUG0(2, "ERROR: Unable to open /proc/stat.\n");
	    fclose(fp);
	    return -1;
	}
		
	// cpu: is the first line in /proc/meminfo. So forward 1 line
	fgets(buf, MAX_LINE_BUFFER-1, fp);

	if ((gettimeofday(&time, &tz)) != 0)
	{
	    DEBUG0 (2, "Unable to get time - gettimeoday failed\n");
	    fclose(fp);
	    return -1;
	}

	if (strncmp(buf, "cpu ", 4) != 0)
	{
	    DEBUG0(2, "Invalid format in /proc/stat file\n");
	    fclose(fp);
	    return -1;
	}
		
	t1 = &buf[4]; //Offset the string "cpu "
	while (*t1 == ' ')
	    t1++;
		
	if (debug != NULL)
	    DEBUG1 (2, "INPUT = \"%s\"\n", t1);
		

	if ((sscanf(t1,"%lu %lu %lu", &e_user, &e_nice, \
		    &e_system )) != 3) 
	{
	    DEBUG0 (2, "Invalid format in /proc/stat file\n");
	    fclose(fp);
	    return -1;		
	}
		
	// Time in seconds since the Epoch
	e_timestamp =  (double) time.tv_sec + 
	    (double)time.tv_usec/(1000*1000) ;

	if(debug != NULL)
	    DEBUG1 (2, " %f\n", e_timestamp);

	total = (long) (((e_user + e_nice + e_system) 
			 - (s_user + s_nice + s_system))/(e_timestamp - \
							  s_timestamp)) ;


	// Make sure we have sane values. The first iteration will 
	// always be insane. So value will return default of 0.
	if( total <= 100 )
	{

	    value = total;
	    DEBUG1 (2, "Percent CPU Utilization = %f\n", value);

	    snprintf(probe_output, BUFSIZ + 24576, plotData_fmt, value,
		    "%Utilization");
	    

	}

	// Make sure we save the values for next time ;
	s_user = e_user ;
	s_nice = e_nice ;
	s_system = e_system;
	s_timestamp = e_timestamp ;


	fclose(fp);
	return 0;
    }

    else if(strcmp(counter, PS_COUNTER) == 0)
    {  /* Use /bin/ps to read the process table */

	// variables used for column data creation
	char column_xml[BUFSIZ];
	char row_xml[BUFSIZ + 24576] ; // The process list could be huge
	int i = 0 ; // used to identify the title line
	int ret = 0 ; // the return value of snprintf
        string encoded_buf;
	
	// The output from the above command will have the format 
	// PID PPID COMMAND
	fp = popen("/bin/ps -eo %p%P%a", "r");
	if (fp == NULL)
	{
	    perror("popen");
	    std::cerr << "Unable to open pipe" << std::endl;
	    DEBUG0 (2, "ERROR: Unable to execute /bin/ps \n");
	    pclose(fp);
	    return -1;
	}
		
	while (fgets(buf, MAX_LINE_BUFFER-1, fp) != NULL) 
	{
	    i++ ;
	    encoded_buf.erase();
	    encoded_buf.append(buf);
	    
	    // Escape the special characters for XML
	    modify_data(encoded_buf, "&", "&amp;");
	    modify_data(encoded_buf, "<", "&lt;");
	    modify_data(encoded_buf, ">", "&gt;");
	    
	    strcpy(buf, encoded_buf.c_str());
	      
	    // Split the line into the three tokens and put the XML tags on
	    create_column_data( buf, column_xml);

	    // Now add the row/title tags on
	    if ( i == 1)
	    {
		// This is the first line, so it deserves a title tag
		// Note we are reusing buf since it is garbage at this point
		sprintf(buf, titleData_fmt, column_xml);
		strcpy(row_xml, buf);
	    } else {
		sprintf(buf, rowData_fmt, column_xml);
		strcat(row_xml, buf); // Concatenate output		
	    }
	}

	// Create the output that goes between the columnData tags

	ret = snprintf(probe_output, BUFSIZ+ 24576 , columnData_fmt, row_xml);
	if (ret == -1)
	{
	    DEBUG0 (2, "Probe output converted to XML is greater than buffer size\n");
	    std::cerr << "Probe output greater than buffer size" << std::endl;
	}
	
	pclose(fp);
	return 0;
    }
	
    // Counter does not exist
    else
    {
	DEBUG1 (2, "Currently counter \"%s\" is not implemented.\n", counter);
	return -1;
    }

}

void 
modify_data (string &src, const char *pattern, const char *replace)
{
  string::size_type x = src.find(pattern);
  while ( x < string::npos )
   {
     src.replace(x,1,replace);
     x = src.find(pattern, x + strlen(replace) + 1);
   }
}


void 
create_column_data (char *src, char *replace)
{
    
    char *pid_ptr;
    char *ppid_ptr;
    char *command_ptr;
    
    // In case things go wrong, just return the original, so set it here
    strcpy(replace, src);

    // Now start the processing of each line
    pid_ptr = src;

    while (*pid_ptr == ' ')  // Keep moving till you find the first nonspace
	pid_ptr++;

    ppid_ptr = strchr(pid_ptr, ' '); // Find the space
    // Check for an error
    if (ppid_ptr == NULL)
    {
	DEBUG0(2, "ERROR: Unable to find spaces, invalid process list line.\n");
	return;
    }
    
    *ppid_ptr++ ='\0'; // Null terminate the pid_ptr string and move to next

    while (*ppid_ptr == ' ')  // Keep moving till you find the first nonspace
	ppid_ptr++;

    command_ptr = strchr(ppid_ptr, ' '); // Find the space
    // Check for an error
    if (command_ptr == NULL) 
    {
	DEBUG0(2, "ERROR: Unable to find spaces, invalid process list line.\n");
	return;
    }
    
    *command_ptr++ = '\0';  //Null terminate the PPID ptr and move to next
    while (*command_ptr == ' ')
	command_ptr++ ;
    
    *(strchr(command_ptr, '\n')) = '\0';  // Remove new line at the end
    
    std::ostringstream xml_data ;
    xml_data << "<column>" << pid_ptr << "</column>" << std::endl
	     << "            <column>" << ppid_ptr << "</column>" << std::endl
             << "            <column>" << command_ptr << "</column>" ;
    
    strcpy(replace, xml_data.str().c_str());

    //    std::cerr << "pid_ptr is:" <<  pid_ptr << std::endl;
    //    std::cerr << "ppid_ptr is:" << ppid_ptr <<  std::endl;
    //    std::cerr << "command_ptr is:" << command_ptr <<  std::endl;
    //    std::cerr << "Replace is:|" << replace << "|" << std::endl;
    
}

    
