package com.stdc.Util.QMSMessage;

public class QMSMessage {
  private long _msgSequenceNo = -1;
  private String _msgDate = null;
  private String _msgTime = null;
  private String _originatingHost = null;
  private QMSMessageSender _msgSender = null;
  private QMSUniqueName _QMSUniqueName = null;
  private QMSSession _QMSSession = null;
  private QMSPayload _payload = null;

  public QMSMessage() {
  }//--------

  public long getMsgSequenceNo() {
      return _msgSequenceNo;
  }

  public void setMsgSequenceNo(long msgSequenceNo) {
      _msgSequenceNo = msgSequenceNo;
  }

  public void setMsgSequenceNo(String msgSequenceNo) {
      _msgSequenceNo = Long.parseLong(msgSequenceNo);
  }

  public String getMsgDate() {
      return _msgDate;
  }

  public void setMsgDate(String msgDate) {
      _msgDate = msgDate;
  }

  public String getMsgTime() {
      return _msgTime;
  }

  public void setMsgTime(String msgTime) {
      _msgTime = msgTime;
  }

  public String getOriginatingHost() {
      return _originatingHost;
  }

  public void setOriginatingHost(String originatingHost) {
      _originatingHost = originatingHost;
  }

  public QMSMessageSender getMessageSender() {
      return _msgSender;
  }

  public void setMessageSender(QMSMessageSender msgSender) {
      _msgSender = msgSender;
  }

  public QMSUniqueName getQMSUniqueName() {
      return _QMSUniqueName;
  }

  public void setQMSUniqueName(QMSUniqueName qmsName) {
      _QMSUniqueName = qmsName;
  }

  public QMSSession getQMSSession() {
      return _QMSSession;
  }

  public void setQMSSession(QMSSession qmsSession) {
      _QMSSession = qmsSession;
  }

  public QMSPayload getPayload() {
      return _payload;
  }

  public void setPayload(QMSPayload payload) {
      _payload = payload;
  }

  public String print() {
      StringBuffer tmpStr = new StringBuffer ();
      tmpStr.append( "QMS Message :\n");
      tmpStr.append( "Sequence No. " + _msgSequenceNo + "\n");
      tmpStr.append( _QMSUniqueName.print() );
      tmpStr.append( _payload.print() );
      tmpStr.append( "--------------------------------------------------------------------\n" );
      return tmpStr.toString();
  }

}//QMSMessage
