package com.stdc.Util.QMSMessage;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class QMSUniqueName {

  private String category;
  private String host;
  private String hostDisplayName;
  private String uuid;

  public QMSUniqueName() {
    category = null;
    host = null;
    uuid = null;
  }//--------

  public String getCategory() {
      return category;
  }

  public void setCategory(String cat) {
      category = cat;
  }

  public String getHost() {
      return host;
  }

  public String getHostDisplayName() {
      return hostDisplayName;
  }

  public void setHost(String h) {
      host = h;
      try {
          hostDisplayName = InetAddress.getByName(host).getHostName();
      } catch (UnknownHostException uhe) {
          hostDisplayName = h;
      } 
  }

  public String getUuid() {
      return uuid;
  }

  public void setUuid(String u) {
      uuid = u;
  }

  public boolean equal(QMSUniqueName target) {
       if ( category.equals(target.getCategory()) )
           if ( host.equals(target.getHost()) )
               if ( uuid.equals(target.getUuid()) )
                   return true;
       return false;
  }

  public String toXml() {
      StringBuffer sb = 
      new StringBuffer("<QMSUniqueName>\n");
      sb.append("<category>" + category + "</category>\n");
      sb.append("<host>" + host + "</host>\n");
      sb.append("<uuid>" + uuid + "</uuid>\n");
      sb.append("</QMSUniqueName>\n");
      
      return sb.toString();
  }

  public String print() {
      StringBuffer tmpStr = new StringBuffer ( "QMSUniqueName\n" );
      tmpStr.append( "    Category: " + category + "\n");
      tmpStr.append( "    Host: " + host + "\n" );
      tmpStr.append( "    UUID: " + uuid + "\n" );

      return tmpStr.toString();
  }

  public String toString() {
      return (category + ":" + host + ":" + uuid);
  }
}//QMSUniqueName
