package com.stdc.Instrumentation.Clients.HelloWorld;


public class HelloWorldMsgPayload implements com.stdc.Util.QMSMessage.QMSPayload {

  private String _category = null;
  private int _dataId = -1;
  private String _salutation = null;

  public HelloWorldMsgPayload() {
  }//--------

  public String getCategory() {
      return _category;
  }

  public void setCategory(String cat) {
      _category = cat;
  }

  public int getDataId() {
      return _dataId;
  }

  public void setDataId(int id) {
      _dataId = id;
  }

  public void setDataId(String id) {
      _dataId = Integer.parseInt(id);
  }

  public String getSalutation() {
      return _salutation;
  }

  public void setSalutation(String desc) {
      _salutation = desc;
  }

  public String toXml() {
      return "";
  }

  public String print() {
      StringBuffer tmpStr = new StringBuffer ( "HelloWorldMsgPayload\n" );
      tmpStr.append( "    Id: " + _dataId);
      tmpStr.append( "    Salutation: " + _salutation + "\n" );

      return tmpStr.toString();
  }

  public String toString() {
      return (_dataId + ":" + _salutation );
  }
}//HelloWorldMsgPayload
