/*                               -*- Mode: C -*- 
 * Debug.h --- 
 * Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
 * Created On       : Sat Aug 11 20:17:42 2001
 * Created On Node  : ember.stdc.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Sat Aug 11 20:19:58 2001
 * Last Machine Used: ember.stdc.com
 * Update Count     : 1
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
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


#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifndef _WIN32 /* Only Win32 needs special treatment. */
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/time.h>
#endif


#include <stdio.h>
#include <signal.h>
#include <stddef.h>
#include <errno.h>

#include <tao/corba.h>

#include <string>
extern "C" {
#include <string.h>
}

namespace STDC 
{
  namespace QMS
  {


    /** @file Debug.h
     *  @ingroup Utilities
     *  @brief Debugging Macros
     *
     * 	This   allows you  to have   different  compile time levels of
     * 	debugging and there is no need to modify the  files to turn of
     * 	or on debugging, just a -DDEBUG=level is needed on the compile
     * 	line.   The  debugging output will  include  the file name and
     * 	line number so it  is  easily traced.  The DEBUG? calls become
     * 	null statements at run time, so there is no run time execution
     * 	time, or data space overheads. Additionally, more control over
     * 	the debug statements can be achieved by a
     * 	-DDEBUGMASK=0xFFFFFFFFL statement which turns on specific
     * 	debug levels (maximum 32). All messages at or below level
     *      DEBUG are suppressed. Assigning a high value for DEBUG ( > 32 )
     *      can suppress all the messages.
     *
     *      Tentatively, some rpedefined debug levels are defined,
     *      starting with the most voluble and decending, and should take
     *      into account most predetermined generic debug points.
     *
     * @section EXAMPLES EXAMPLES 
     * 	function(arg1,arg2,arg3)
     * 	....
     * 	...
     * 	DEBUG3(50,"Entering function(%d,%d,%d)",arg1,arg2,arg3);
     *
     *      ASSERT()
     *
     * @section DESCRIPTION DESCRIPTION
     * 	ASSERT(expr)   evaluates  an  expression.    If  expression is
     * 	non-zero (ie.,  true),  then no  action is  taken.     If  the
     * 	expression is zero, then the file name and line number and the
     * 	assertion are written  to  the standard  error. if a   #define
     * 	DEBUG hasn't been done, then ASSERT() does nothing.
     *
     *@section  EXAMPLES EXAMPLES2
     * 	ASSERT(strlen(name) < 20);
     * 	ASSERT(pBuf != NULL);
     *
     * @section NOTES NOTES
     * 	1). This macro definition is a modification of the one
     * 	suggested in the book "C traps and pitfalls", Andrew Koenig,
     * 	Addison-Wesley, 1989, page 82.
     *
     *
     */

    /*
     * Copyright (c) Manoj Srivastava, 1989
     *
     */

    /*
     * $Id: Debug.h,v 1.6 2001/10/22 15:38:24 srivasta Exp $
     *
     */

    /// Determine the sign of the argument
#   define SIGNOF(x) ((int) ((x) < 0) ? -1 : 1)

    /**
     * Macros are dangerous if they use an  if--then--else control statement,
     * because  they may  be  used in  an   if--then--else control  statement
     * themselsves, and should be enclosed  in the following block to prevent
     * problems (like dangling else statements).
     */
#   define	BEGIN_BLOCK	do {	/* begin macros with this */
    /// end macros with this
#   define	END_BLOCK	} while (0) /* end macros with this */

    /**
     * A wrapper around the ACE Trace facility selectable at compile
     * time. If QMS_DO_TRACE is not defined, the macro QMS_Trace is not
     * compiled into the code
     */
#   ifdef QMS_DO_TRACE
#      include "ace/Trace.h"
#      define QMS_Trace(Comment, Line, File) ACE_Trace (Comment, Line, File)
#   else
#      define QMS_Trace(Comment, Line, File)
#   endif

    /**
     * The following macro checks for an library error, and prints out the
     * argument string using perror, and returns non 0.
     */


    //commented the below line because errno defined in errno.h
    //extern int errno;		/* lib functions set this on error */

#   define CHECK_ERROR(MSG) \
    BEGIN_BLOCK\
    if (errno != 0) /* ie, there is an error*/ \
      {\
        fprintf(stderr,"(%s)%d: ",__FILE__, __LINE__);\
        perror (#MSG); /* print the message */\
        return -1;\
      }\
    END_BLOCK


    /**
     * The following macro checks for an library error, and prints out the
     * argument string using perror, and exits.
     */


#define ERROR_EXIT(MSG) \
  BEGIN_BLOCK\
  if (errno != 0) /* ie, there is an error*/ \
    {\
      fprintf(stderr,"(%s)%d: ",__FILE__, __LINE__);\
      perror (#MSG); /* print the message */\
      exit (errno);\
    }\
  END_BLOCK


    /**
     * Figure out what \a really is. Extracted from Gnu Awk 2.11.1.
     */

#ifdef __STDC__
#define BELL	'\a'		/* sure makes life easy, don't it? */
#else
#	if 'z' - 'a' == 25	/* ascii */
#		if 'a' != 97	/* machine is dumb enough to use mark parity */
#			define BELL	'\207'
#		else
#			define BELL	'\07'
#		endif
#	else
#		define BELL	'\057'
#	endif
#endif


    /**
     * DEBUGMASK provides explicit control over which debug  levels are to be
     * turned on, ie, DEBUGMASK = 0xFFFFFFFFL gives 32 DEBUG levels (all on);
     * DEBUGMASK =  0x00000001L  turns  on  level  1, DEBUGMASK = 0x00000009L
     * turns on level 1 and 8, and so on.
     */

#ifndef DEBUGMASK
#	define DEBUGMASK 0xFFFFFFFFL    /* 32 DEBUG levels (all on) */
#else
#	ifndef DEBUG
#		define DEBUG 1L	/* default level, in case the user did */
				/* not turn it on*/
#	endif
#endif

    /*
     * Some predefined LEVELS
     */

#define DEBUG_L_ENTER    0x00000001L
    /** Leave function */
#define DEBUG_L_LEAVE    0x00000002L
    /** Our arguments */
#define DEBUG_L_ARGS     0x00000004L
    /** Enter function */

    /** Arguments of function calls */
#define DEBUG_L_CALLARGS 0x00000008L
    /** function calls */
#define DEBUG_L_CALL     0x00000010L
    /** Enter Block */
#define DEBUG_L_B_ENTER  0x00000020L
    /** Leave Block */
#define DEBUG_L_B_LEAVE  0x00000040L

    /* Five levels left undefined for use */

    /** Informational */
#define DEBUG_L_INFO     0x00001000L
    /** Warnings */
#define DEBUG_L_WARN     0x00002000L
    /** Errors */
#define DEBUG_L_ERROR    0x00004000L
    /** Alerts*/
#define DEBUG_L_ALERT    0x00008000L
    /** Critical Errors */
#define DEBUG_L_CRIT     0x00010000L

#ifdef DEBUG   /* that is, if we *ARE* debugging */

    /** A drop in replacement for assert.h */
#define ASSERT(expr)\
BEGIN_BLOCK	\
   if(!(expr)) /* so assert is false*/ \
     {\
       fprintf (stderr, "%s(%d):Assert failed, %s\n", __FILE__,\
	       __LINE__, #expr);\
       exit (33); /* a nice , non standard value*/ \
     }\
END_BLOCK

    /// No argument debug macro
#define DEBUG0(level,str)\
BEGIN_BLOCK\
  if(level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1))))) \
  /* that is, this is a a valid debug statement */ \
  fprintf(stderr,"%s(%d): %s\n", __FILE__,__LINE__,str);\
END_BLOCK


    /// Single argument debug macro
#define DEBUG1(level,str,a1)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  /* that is, this is a a valid debug statement */ \
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr,str, a1);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK

    /// Double argument debug macro
#define DEBUG2(level,str,a1,a2)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr,str,a1,a2);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK

    /// Triple argument debug macro
#define DEBUG3(level,str,a1,a2,a3)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr, str,a1,a2,a3);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK

    /// Quadruple argument debug macro
#define DEBUG4(level,str,a1,a2,a3,a4)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr, str,a1,a2,a3,a4);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK

    /// Quintiple argument debug macro
#define DEBUG5(level,str,a1,a2,a3,a4,a5)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr, str,a1,a2,a3,a4,a5);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK

    /// Variable argument debug macro
#define DEBUGN(level,str,pargs)\
BEGIN_BLOCK\
     if( level && (DEBUG < level && (DEBUGMASK & (1L << (level - 1)))))\
       {\
	  fprintf(stderr,"%s(%d): ", __FILE__,__LINE__);\
	  fprintf(stderr, str,pargs);\
	  fprintf(stderr,"\n");\
	}\
END_BLOCK


#else /* DEBUG , ie , we are *not* debugging*/
#ifdef DEBUGMASK
#	undef  DEBUGMASK
#	define DEBUGMASK	/* remove the definition */
#endif
    /** A drop in replacement for assert.h */
#define ASSERT(expr)
    /// No argument debug macro
#define DEBUG0(level,s)
    /// Single argument debug macro
#define DEBUG1(level,s,a1)
    /// Double argument debug macro
#define DEBUG2(level,s,a1,a2)
    /// Triple argument debug macro
#define DEBUG3(level,s,a1,a2,a3)
    /// Quadruple argument debug macro
#define DEBUG4(level,s,a1,a2,a3,a4)
    /// Quintiple argument debug macro
#define DEBUG5(level,s,a1,a2,a3,a4,a5)
    /// Variable argument debug macro
#define DEBUGN(level,s,pargs)

#endif /* DEBUG */
  };
};

#endif /* _DEBUG_H_ */

/* Local Variables: */
/* mode: c++ */
/* comment-column: 32 */
/* indent-tab-mode: nil */
/* End: */



