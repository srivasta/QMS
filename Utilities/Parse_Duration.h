/*                               -*- Mode: C -*- 
 * Parse_Duration.h --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
 * Created On       : Wed Dec  5 18:21:24 2001
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Wed Dec  5 22:51:55 2001
 * Last Machine Used: glaurung.green-gryphon.com
 * Update Count     : 5
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

/** @file 
 *  @ingroup Utilities
 *  @brief A convenient interface to parsing QMS XML durations
 *
 * $Id: Parse_Duration.h,v 1.1 2001/12/06 05:53:27 srivasta Exp $
 */



#ifndef _PARSE_DURATION_H_
#define _PARSE_DURATION_H_
#include <time.h>

namespace STDC 
{
  namespace QMS 
  {
    struct timespec duration_to_tv(const char * duration);
  };
};


#endif /* _PARSE_DURATION_H_ */
