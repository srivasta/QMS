package com.stdc.Util.QMSMessage;


public class QMSMessageSender {

  private int _id;
  private String _description;

  public QMSMessageSender() {
    _id = -1;
    _description = null;
  }//--------

  public int getId() {
      return _id;
  }

  public void setId(int id) {
      _id = id;
  }

  public void setId(String id) {
      _id = Integer.parseInt(id);
  }

  public String getDescription() {
      return _description;
  }

  public void setDescription(String desc) {
      _description = desc;
  }

  public boolean equal(QMSMessageSender target) {
       if ( _id == target.getId() )
           return true;
       return false;
  }

  public String toXml() {
      StringBuffer sb = 
      new StringBuffer("<qms:msgSender>\n");
      sb.append("  <id>" + _id + "</id>\n");
      sb.append("  <description>" + _description + "</description>\n");
      sb.append("</qms:msgSender>\n");
      
      return sb.toString();
  }

  public String print() {
      StringBuffer tmpStr = new StringBuffer ( "QMSMessageSender\n" );
      tmpStr.append( "    Id: " + _id + "\n");
      tmpStr.append( "    Description: " + _description + "\n" );

      return tmpStr.toString();
  }

  public String toString() {
      return (_id + ":" + _description );
  }
}//QMSMessageSender
