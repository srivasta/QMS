package com.stdc.Instrumentation.Probes.HelloWorld;

// HelloWorldProbeConsole.java
//
// ============================================================================
//
// = FILENAME
//    HelloWorldProbeConsole.java
//
// = AUTHOR
//    Amit Haldankar (amit.haldankar@stdc.com)
//
// = DESCRIPTION
//   This is the gui console for qms probe written in java.
//
// ============================================================================

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import java.awt.BorderLayout;
import java.awt.GridLayout;

/**
 * @authors Amit Haldankar April 2002
 *
 * A start for QMS in java
 *
 */

public class HelloWorldProbeConsole extends JFrame
{

  // Repeat count
  int _count = 1;
  String _argStr = null;
  JPanel buttonPanel = null;
  JRadioButton[] buttonArray;

  int _rows;
  int _columns;
  int _grid;

  public HelloWorldProbeConsole(int repeatCount, String arg)
  {
      super("Hello " + arg + " !!");
      _count = repeatCount;
      _argStr = arg;

      _rows = _columns = (int)Math.round(Math.sqrt ( (double)repeatCount ));
      _grid = _rows * _columns;

      getContentPane().setLayout(new BorderLayout());
      setSize(300, 300);

      buttonPanel = new JPanel();
      buttonPanel.setLayout(new GridLayout(_rows, _columns, 2, 2));

      this.init();

      getContentPane().add(buttonPanel, "Center");
  }

  public void init()
  {      

      buttonArray = new JRadioButton[_grid];
      for (int i=0; i < _grid; i++)
      {
          buttonArray[i] = new JRadioButton();
          buttonPanel.add(buttonArray[i]);
      }

  } // end init

  public void setSelected(int i) {
      if ( i < _grid )
          buttonArray[i].setSelected(true);
  }

  public void setRepeatCount(int count) {
      if ( count > 0 )
          _count = count;
  }

}
