package com.stdc.Util.QMSMessage;


public class QMSSession {

  private long _requestId;
  private int _version;
  private int _repeatCount;
  private int _currentCount;
  private String _repeatInterval;

  public QMSSession() {
    _requestId = -1;
    _version = -1;
    _repeatCount = -1;
    _currentCount = -1;
    _repeatInterval = null;
  }//--------

  public long getRequestId() {
      return _requestId;
  }

  public void setRequestId(long requestId) {
      _requestId = requestId;
  }

  public void setRequestId(String requestId) {
      _requestId = Long.parseLong(requestId);
  }

  public int getVersion() {
      return _version;
  }

  public void setVersion(int version) {
      _version = version;
  }

  public void setVersion(String version) {
      _version = Integer.parseInt(version);
  }

  public int getRepeatCount() {
      return _repeatCount;
  }

  public void setRepeatCount(int repeatCount) {
      _repeatCount = repeatCount;
  }

  public void setRepeatCount(String repeatCount) {
      _repeatCount = Integer.parseInt(repeatCount);
  }

  public int getCurrentCount() {
      return _currentCount;
  }

  public void setCurrentCount(int currentCount) {
      _currentCount = currentCount;
  }

  public void setCurrentCount(String currentCount) {
      _currentCount = Integer.parseInt(currentCount);
  }

  public String getRepeatInterval() {
      return _repeatInterval;
  }

  public void setRepeatInterval(String repeatInterval) {
      _repeatInterval = repeatInterval;
  }

  public String toXml() {
      StringBuffer sb = 
      new StringBuffer("<qms:Session>\n");
      sb.append("  <requestID>" + _requestId + "</requestID>\n");
      sb.append("  <version>" + _version + "</version>\n");
      sb.append("  <minRepetitions>" );
      sb.append("    <count>" + _repeatCount + "</count>\n");
      sb.append("    <current>" + _currentCount + "</current>\n");
      sb.append("  </minRepetitions>" );
      sb.append("  <minRepeatInterval>" + _repeatInterval + "</minRepeatInterval>\n");
      sb.append("</qms:Session>\n");
      
      return sb.toString();
  }

  public String print() {
      StringBuffer tmpStr = new StringBuffer ( "QMSSession\n" );
      tmpStr.append( "    RequestId: " + _requestId + "\n");
      tmpStr.append( "    Version: " + _version + "\n" );
      tmpStr.append( "    Current Count: " + _currentCount + "\n" );

      return tmpStr.toString();
  }

  public String toString() {
      return (_requestId + ":" + _version + ":" + _currentCount );
  }
}//QMSSession
