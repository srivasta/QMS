package com.stdc.Util.SaxMapper;

import java.util.*;
import java.io.*;
import org.xml.sax.*;


public class TagTracker {

	// Table of tag trackers.
	// This table contains an entry for
	// every tag name that this TagTracker
	// has been configured to follow.
	// This is a single-level parent-child relation.
	//
	private Hashtable trackers = new Hashtable();

	// Useful for skipping tag names that are not
	// being tracked.
	private static SkippingTagTracker skip = new SkippingTagTracker();


	// default constructor
	public TagTracker() {}


	// Configuration method for setting up a network
	// of tag trackers...
	// Each parent tag name should be configured
	// ( call this method ) for each child tag name
	// that it will track.
	public void track( String tagName, TagTracker tracker ){

		
		int slashOffset = tagName.indexOf( "/" );
		
		if( slashOffset < 0 ) { 
			// if it is a simple tag name ( no "/" seperators )
			// simply add it.
			trackers.put( tagName, tracker);
		
		} else if ( slashOffset == 0 ) {
			// Oooops leading slash, remove it and 
			// try again recursivley.
			track( tagName.substring( 1 ), tracker );

		} else {	
			// if it is not a simple tag name
			// recursively add the tag.
			String topTagName = tagName.substring( 0, slashOffset );	
			String remainderOfTagName = tagName.substring( slashOffset + 1 );
			TagTracker child = (TagTracker)trackers.get( topTagName );
			if ( child == null ) {
                         	// Not currently tracking this 
				// tag. Add new tracker.
				child = new TagTracker();
				trackers.put( topTagName, child );
			}
			child.track( remainderOfTagName, tracker );

		}


	}


	// Tag trackers work together on a stack.
	// The tag tracker at the top of the stack
	// is the "active" tag tracker and is responsible
	// for delegating the tracking to a child tag
	// tracker or putting a skipping place marker on the
	// stack.
	//
	public void startElement( String namespaceURI,
			 	  String localName,
				  String qName,
				  Attributes attr,
				  Stack tagStack ) {


		// Lookup up the tag name in the tracker table.
		// Note, this implementation does not address 
		// using XML name space support that is now available
		// with SAX2.
		// We are simply using the localName as a key
		// to find a possible tracker.
		TagTracker tracker = (TagTracker) trackers.get( localName );

		//
		// Are we tracking this tag name?
		//
		if ( tracker == null ) {
			// Not tracking this
			// tag name.  Skip the
			// entire branch.
			SaxMapperLog.trace( "Skipping tag: [" + localName + "]");
			tagStack.push( skip );
		}
		else {

			// Found a tracker for this
			// tag name.  Make it the
			// new top of stack tag
			// tracker
			SaxMapperLog.trace( "Tracking tag: [" + localName + "]");

			// Send the deactivate event to this tracker.
			SaxMapperLog.trace( "Deactivating current tracker.");
			onDeactivate();

			// Send the on start to the new active 
			// tracker.
			SaxMapperLog.trace( "Sending start event to [" + localName + "] tracker.");
			tracker.onStart(namespaceURI, localName, 
					qName, attr );
			tagStack.push( tracker );

		}

	}


	// Tag trackers work together on a stack.
	// The tag tracker at the top of the stack
	// is the "active" tag tracker and is responsible
	// for reestablishing it's parent tag tracker
	// ( next to top of stack ) when it has
	// been notified of the closing tag.
	//
	public void endElement(   String namespaceURI,
			 	  String localName,
				  String qName,
				  CharArrayWriter contents,
				  Stack tagStack ) {

                                        
		// Send the end event.
		SaxMapperLog.trace( "Finished tracking tag: [" + localName + "]");
		onEnd( namespaceURI, localName, qName, contents );

		// Clean up the stack...
		tagStack.pop();

		// Send the reactivate event.
		TagTracker activeTracker = (TagTracker) tagStack.peek();
		if ( activeTracker != null ) {
			SaxMapperLog.trace( "Reactivating previous tag tracker.");		
                 	activeTracker.onReactivate();
		}


	}


	// Methods for collecting content. These methods 
	// are intended to be overridden with specific
	// actions for nodes in the tag tracking network 
	// that require 

	public void onStart( String namespaceURI,
			     String localName,
			     String qName,
			     Attributes attr ) {

		// default is no action...
	}

	public void onDeactivate() {

		// default is no action...
	}

	public void onEnd(   String namespaceURI,
			 	  String localName,
				  String qName,
				  CharArrayWriter contents ){

		// default is no action...
	}

	public void onReactivate() {

		// default is no action...
	}

}


class SkippingTagTracker extends TagTracker {


	// Tag trackers work together on a stack.
	// The tag tracker at the top of the stack
	// is the "active" tag tracker.
	//
	// This class represents a skipping place
	// marker on the stack.  When a real tag
	// tracker places a skipping tag tracker on
	// the stack, that is an indication that
	// all tag names found during the skip are
	// of no intrest to the tag tracking network.
	//
	// This means that if the skipping tag tracker
	// is notified of a new tag name, this new
	// tag name should also be skipped.
	//
	// Since this class never varies it's behavior,
	// it is ok for it to skip new tag names by
	// placing itself on the stack again.
	public void startElement( String namespaceURI,
			 	  String localName,
				  String qName,
				  Attributes attr, 
				  Stack tagStack ) {


		//
		// If the current tag name is being
		// skipped, all children should be
		// skipped.
		//
		SaxMapperLog.trace( "Skipping tag: [" + localName + "]");
		tagStack.push( this );

	}

	//
	// The skipping tag tracker has
	// nothing special to do when
	// a closing tag is found other
	// than to remove itself from
	// the stack, which as a side
	// effect replaces it with it's
	// parent as the "active", top
	// of stack tag tracker.
	//
	public void endElement(   String namespaceURI,
			 	  String localName,
				  String qName,
				  CharArrayWriter contents,
				  Stack tagStack ) {

		// Clean up the stack...
		SaxMapperLog.trace( "Finished skipping tag: [" + localName + "]");
		tagStack.pop();

	}



}
