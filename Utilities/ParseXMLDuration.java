package com.stdc.Util;

// ParseXMLDuration.java
//
// ============================================================================
//
// = FILENAME
//    ParseXMLDuration.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   This is a utility class to parse xml duration string.
//
// ============================================================================


/**
 * @authors Amit Haldankar April 2002
 *
 * A Utility class to parse xml duration string.
 *
 */

public class ParseXMLDuration
{
  public static long getMilliSeconds(String duration) throws Exception {
      int startIdx = 0;
      int endIdx = 0;
      float value = 0;
      float frac = 0;
      char durArray[] = duration.toCharArray();
      if ( durArray[0] == 'P' ) {
          boolean seen_T = false;
          boolean seen_secs = false;
          //System.out.println ( "Duration char array length " + durArray.length);
          for ( int i=1; i < durArray.length; i++ ) {
              startIdx = i;
              int count = 0;
              int val = 0;

              while ( i < durArray.length && Character.isDigit(durArray[i]) ) {
                  count++; i++;
              }
              String number = null;
              if ( count > 0 ) {
                  try {
                      if ( !seen_secs ) {
                          number = new String ( durArray, startIdx, count );
                          val = Integer.parseInt( number );
//                          System.out.println("V=" + val);
                      } else {
                          number = new String ( durArray, startIdx -1, count+1);
                          frac = Float.parseFloat( number );
//                          System.out.println("F=" + frac);
                      }
                  } catch (NumberFormatException ex) {
                      System.err.println("Number format exception" + number);
                      val = 0;
                      frac=0;
                  }
              }

              if ( i < durArray.length ) {
                  switch(durArray[i]) {
                    case 'Y':
                      //System.out.println("Y");
                      value  += (val * 365.25 * 86400);
                      break;
                         
                    case 'M':
                      //System.out.println("M");
                      if(!seen_T) {
                         value  += (val * 30  * 86400);
                      } // end of if(seen_T)
                      else {
                         value  += (val * 60);
                      } // end of else
                      break;
                      
                    case 'D':
                      //System.out.println("D");
                         value  += (val * 86400);
                      break;
                    
                    case 'H':
                      //System.out.println("H");
                      value  += (val * 3600);
                      break;
                    
                    case '.':
                      //System.out.println(".");
                      value  += (val);
                      seen_secs=true;
                      break;
                      
                    case 'S':
                      //System.out.println("S");
                      if(!seen_secs) {
                          value  += (val * 1000);
                      }
                      break;
                         
                    case 'T':
                      //System.out.println("T");
                      seen_T = true;
                      break;
    
                    default:
                      //System.out.println("Error " + durArray[i] );
                      break;
                      
                   } // end of switch(durArray[i]
               } // end of if ( i < durArray.length )
               else {
                   throw new Exception ("Illegal XML Duration String");
               }
          }
      } else {
          throw new Exception ("XML Duration String doesn't start with P");
      }
//      System.out.println ( "Mantissa " + value );
//      System.out.println ( "Fraction " + frac );
      return ( (long)((value * 1000.0 ) + (frac * 1000.0)) );
  }

  static public void main  (String args[])
  {
      System.out.println ( "The input duration string is " + args[0] );
      try {
          long value = getMilliSeconds(args[0]);
          System.out.println ( "The value in milli seconds is " + value );
      } catch ( Exception ex) {
          System.out.println ("Error in parsing duration string: " + ex.getMessage());
      }
  }

}
