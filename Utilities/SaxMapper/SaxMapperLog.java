package com.stdc.Util.SaxMapper;


public class SaxMapperLog {

	static boolean doTraceLogging = Boolean.getBoolean( "reh.SaxMapper.trace" );


	public static void trace( String msg ){

		if ( doTraceLogging )  {
			System.out.println( "trace: " + msg );
		}                                                              	
	}

	public static void error(  String msg ){

		System.out.println( "error: " + msg );

	}


	// testing main method...
	public static void main( String[] argv ) {
		
		Boolean b = new Boolean( doTraceLogging );

		System.out.println( "Tracing is: [" 
					+ b.toString() 
					+ "]" );

		trace( "test message" );
	}	

}
