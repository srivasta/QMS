<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>
<tagfile>
  <compound kind="page">
    <filename>index</filename>
    <title>QMS Documentation</title>
    <name>index</name>
    <docanchor>SubIndex1</docanchor>
    <docanchor>Capabilities</docanchor>
    <docanchor>SubIndex2</docanchor>
    <docanchor>QMSOverview</docanchor>
    <docanchor>Acknowledgements</docanchor>
  </compound>
  <compound kind="file">
    <name>Backend.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Backend/</path>
    <filename>Backend_8h</filename>
  </compound>
  <compound kind="file">
    <name>bench_capability.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>bench__capability_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bench_message.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>bench__message_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>message_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bench_parse_xml.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>bench__parse__xml_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>bench_xslt.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>bench__xslt_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Benchmark_Client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Benchmark__Client_8cpp</filename>
    <includes id="Client_8h" name="Client.h" local="yes">Client.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>NUM_RUNS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUM_ITERATIONS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check_message</name>
      <anchor>a9</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_fmt</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_High_Res_Timer</type>
      <name>timer</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_result_guard</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>count</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>run</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_hrtime_t</type>
      <name>receiving</name>
      <anchor>a8</anchor>
      <arglist>[NUM_RUNS][NUM_ITERATIONS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Benchmark_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>Benchmark__Remos_8cpp</filename>
    <includes id="Client__Remos_8h" name="Client_Remos.h" local="yes">Client_Remos.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>NUM_RUNS</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NUM_ITERATIONS</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>check_message</name>
      <anchor>a9</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_fmt</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_High_Res_Timer</type>
      <name>timer</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_result_guard</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>count</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>run</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_hrtime_t</type>
      <name>receiving</name>
      <anchor>a8</anchor>
      <arglist>[NUM_RUNS][NUM_ITERATIONS]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CallBack.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>CallBack_8cpp</filename>
    <includes id="Generic__Sensor__Impl_8h" name="Generic_Sensor_Impl.h" local="yes">Generic_Sensor_Impl.h</includes>
    <class kind="struct">pack_args</class>
    <member kind="function">
      <type>void</type>
      <name>do_query</name>
      <anchor>a1</anchor>
      <arglist>(void *args_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a2</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CallBack_HW.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>CallBack__HW_8cpp</filename>
    <includes id="Hello__World__Impl_8h" name="Hello_World_Impl.h" local="yes">Hello_World_Impl.h</includes>
    <class kind="struct">pack_args</class>
    <member kind="function">
      <type>void</type>
      <name>do_query</name>
      <anchor>a1</anchor>
      <arglist>(void *args_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a2</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CallBack_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>CallBack__Remos_8cpp</filename>
    <includes id="Remos__Sensor__Impl_8h" name="Remos_Sensor_Impl.h" local="yes">Remos_Sensor_Impl.h</includes>
    <class kind="struct">pack_args</class>
    <member kind="function">
      <type>void</type>
      <name>do_query</name>
      <anchor>a1</anchor>
      <arglist>(void *args_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a2</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Capability.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Capability_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <class kind="class">IDOMTreeErrorReporter</class>
    <member kind="function">
      <type>const char *</type>
      <name>get_node_type</name>
      <anchor>a1</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_node_details</name>
      <anchor>a2</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_ruler</name>
      <anchor>a3</anchor>
      <arglist>(int level, string &amp;ruler)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>variable_element_handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>uniq_name_element_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>xsl_param_element_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instance_element_handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>offer_element_handler</name>
      <anchor>a9</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invoke_element_handler</name>
      <anchor>a10</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mandatoryServiceOfferProperties</name>
      <anchor>a11</anchor>
      <arglist>(IDOM_Node *child_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mandatoryCorbaOfferProperties</name>
      <anchor>a12</anchor>
      <arglist>(IDOM_Node *child_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mandatorySchemaOfferProperties</name>
      <anchor>a13</anchor>
      <arglist>(IDOM_Node *child_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>genericSensorProbeProperties</name>
      <anchor>a14</anchor>
      <arglist>(IDOM_Node *child_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe_element_handler</name>
      <anchor>a15</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sensorService_element_handler</name>
      <anchor>a16</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>QoSParameters_handler</name>
      <anchor>a17</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>minRepetitions_handler</name>
      <anchor>a18</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>session_handler</name>
      <anchor>a19</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>QMSMessage_handler</name>
      <anchor>a20</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sensorConfiguration_handler</name>
      <anchor>a21</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sensorCapability_handler</name>
      <anchor>a22</anchor>
      <arglist>(IDOM_Node *node_p, int level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>doc_handler</name>
      <anchor>a23</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a24</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Client_8cpp</filename>
    <includes id="Client_8h" name="Client.h" local="yes">Client.h</includes>
    <member kind="function">
      <type>bool</type>
      <name>check_message</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Client.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Client_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Generic__SensorC_8h" name="Generic_SensorC.h" local="yes">Generic_SensorC.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Payload_8h" name="Payload.h" local="yes">Payload.h</includes>
    <class kind="class">Test_Client</class>
  </compound>
  <compound kind="file">
    <name>Client_HW.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/test/</path>
    <filename>Client__HW_8cpp</filename>
    <includes id="Client__HW_8h" name="Client_HW.h" local="yes">Client_HW.h</includes>
    <member kind="function">
      <type>bool</type>
      <name>check_message</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Client_HW.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/test/</path>
    <filename>Client__HW_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Payload__HW_8h" name="Payload_HW.h" local="yes">Payload_HW.h</includes>
    <class kind="class">Test_Client</class>
  </compound>
  <compound kind="file">
    <name>Client_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>Client__Remos_8cpp</filename>
    <includes id="Client__Remos_8h" name="Client_Remos.h" local="yes">Client_Remos.h</includes>
    <member kind="function">
      <type>bool</type>
      <name>check_message</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Client_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>Client__Remos_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Payload__Remos_8h" name="Payload_Remos.h" local="yes">Payload_Remos.h</includes>
    <class kind="class">Test_Client</class>
  </compound>
  <compound kind="file">
    <name>Command.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Core/</path>
    <filename>Command_8idl</filename>
    <includes id="Control_8idl" name="Control.idl" local="yes">Control.idl</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Continuous.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/</path>
    <filename>Continuous_8h</filename>
  </compound>
  <compound kind="file">
    <name>Continuous_Pipe_Proxy.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Continuous__Pipe__Proxy_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Continuous__Pipe__Proxy_8h" name="Continuous_Pipe_Proxy.h" local="yes">Continuous_Pipe_Proxy.h</includes>
    <member kind="function">
      <type>int</type>
      <name>internal_deploy</name>
      <anchor>a0</anchor>
      <arglist>(char *file_name_p_, int ctrlpipe[2], int datapipe[2], char *argv_[], STDC::QMS::Citizen::Meta_Data &amp;_metadata, string _key)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Continuous_Pipe_Proxy.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Continuous__Pipe__Proxy_8h</filename>
    <includes id="Pipe__Proxy_8h" name="Pipe_Proxy.h" local="yes">Pipe_Proxy.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Continuous_Pipe_Proxy_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Continuous__Pipe__Proxy__Remos_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Continuous__Pipe__Proxy__Remos_8h" name="Continuous_Pipe_Proxy_Remos.h" local="yes">Continuous_Pipe_Proxy_Remos.h</includes>
    <member kind="function">
      <type>int</type>
      <name>internal_deploy</name>
      <anchor>a0</anchor>
      <arglist>(char *file_name_p_, int ctrlpipe[2], int datapipe[2], char *argv_[], STDC::QMS::Citizen::Meta_Data_Remos &amp;_metadata, string _key)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Continuous_Pipe_Proxy_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Continuous__Pipe__Proxy__Remos_8h</filename>
    <includes id="Pipe__Proxy__Remos_8h" name="Pipe_Proxy_Remos.h" local="yes">Pipe_Proxy_Remos.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Control.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Core/</path>
    <filename>Control_8idl</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>CORBA_Handles.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>CORBA__Handles_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CORBA_Handles.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>CORBA__Handles_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Debug.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>Debug_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>SIGNOF</name>
      <anchor>a0</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BEGIN_BLOCK</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>END_BLOCK</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>QMS_Trace</name>
      <anchor>a3</anchor>
      <arglist>(Comment, Line, File)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CHECK_ERROR</name>
      <anchor>a4</anchor>
      <arglist>(MSG)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ERROR_EXIT</name>
      <anchor>a5</anchor>
      <arglist>(MSG)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>BELL</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUGMASK</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_ENTER</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_LEAVE</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_ARGS</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_CALLARGS</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_CALL</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_B_ENTER</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_B_LEAVE</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_INFO</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_WARN</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_ERROR</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_ALERT</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_L_CRIT</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUGMASK</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ASSERT</name>
      <anchor>a21</anchor>
      <arglist>(expr)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG0</name>
      <anchor>a22</anchor>
      <arglist>(level, s)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG1</name>
      <anchor>a23</anchor>
      <arglist>(level, s, a1)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG2</name>
      <anchor>a24</anchor>
      <arglist>(level, s, a1, a2)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG3</name>
      <anchor>a25</anchor>
      <arglist>(level, s, a1, a2, a3)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG4</name>
      <anchor>a26</anchor>
      <arglist>(level, s, a1, a2, a3, a4)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG5</name>
      <anchor>a27</anchor>
      <arglist>(level, s, a1, a2, a3, a4, a5)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUGN</name>
      <anchor>a28</anchor>
      <arglist>(level, s, pargs)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EC_Adapter.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>EC__Adapter_8cpp</filename>
    <includes id="EC__Adapter_8h" name="EC_Adapter.h" local="yes">EC_Adapter.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>EC_Adapter.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>EC__Adapter_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ECInfo.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>ECInfo_8cpp</filename>
    <includes id="ECInfo_8h" name="ECInfo.h" local="yes">ECInfo.h</includes>
    <member kind="function">
      <type>ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchor>a0</anchor>
      <arglist>(ostream &amp;out, const ECInfo &amp;info)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ECInfo.h</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>ECInfo_8h</filename>
    <namespace>std</namespace>
    <class kind="class">ECInfo</class>
  </compound>
  <compound kind="file">
    <name>generic_client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>generic__client_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Client_8h" name="Client.h" local="yes">Client.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="class">client_error_handler</class>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Test_Client *</type>
      <name>client_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_Continuous_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Generic/</path>
    <filename>Generic__Continuous__Probe_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Generic__Continuous__Probe_8h" name="Generic_Continuous_Probe.h" local="yes">Generic_Continuous_Probe.h</includes>
    <includes id="get__data__GCP_8h" name="get_data_GCP.h" local="yes">get_data_GCP.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a1</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a3</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a4</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_Continuous_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Generic/</path>
    <filename>Generic__Continuous__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a13a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>pause_probe</name>
      <anchor>a13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a13a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repetitions</name>
      <anchor>a13a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repeatInterval</name>
      <anchor>a13a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a10</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;, void *)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>enum status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_asset_guard</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>repeat_count</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>timespec</type>
      <name>refresh_rate</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_OneShot_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/</path>
    <filename>Generic__OneShot__Probe_8cpp</filename>
    <includes id="Generic__OneShot__Probe_8h" name="Generic_OneShot_Probe.h" local="yes">Generic_OneShot_Probe.h</includes>
    <includes id="get__data__O_8h" name="get_data_O.h" local="yes">get_data_O.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_OneShot_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/</path>
    <filename>Generic__OneShot__Probe_8h</filename>
  </compound>
  <compound kind="file">
    <name>generic_sensor.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>generic__sensor_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Generic__Sensor__Impl_8h" name="Generic_Sensor_Impl.h" local="yes">Generic_Sensor_Impl.h</includes>
    <class kind="class">sensor_error_handler</class>
    <member kind="function">
      <type>void</type>
      <name>add_handler</name>
      <anchor>a4</anchor>
      <arglist>(sensor_error_handler *signal_handler_p, STDC::QMS::CORBA_Handles *handles_p, int signal)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>ior_output_file</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>ior</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Generic_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_Sensor.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__Sensor_8h</filename>
  </compound>
  <compound kind="file">
    <name>Generic_Sensor.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__Sensor_8idl</filename>
    <includes id="Command_8idl" name="Command.idl" local="yes">Command.idl</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Generic_Sensor_Impl.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__Sensor__Impl_8cpp</filename>
    <includes id="Generic__Sensor__Impl_8h" name="Generic_Sensor_Impl.h" local="yes">Generic_Sensor_Impl.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <member kind="function">
      <type>void</type>
      <name>print_message_data</name>
      <anchor>a2</anchor>
      <arglist>(STDC::QMS::QMSMessage &amp;config)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a0</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_Sensor_Impl.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__Sensor__Impl_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Generic__SensorS_8h" name="Generic_SensorS.h" local="yes">Generic_SensorS.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="Meta__Data_8h" name="Meta_Data.h" local="yes">Meta_Data.h</includes>
    <includes id="Message__Format_8h" name="Message_Format.h" local="yes">Message_Format.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_SensorC.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorC_8cpp</filename>
    <includes id="Generic__SensorC_8h" name="Generic_SensorC.h" local="yes">Generic_SensorC.h</includes>
    <member kind="function">
      <type>STDC::QMS::Citizen::Generic_Sensor_ptr</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_duplicate</name>
      <anchor>a1</anchor>
      <arglist>(STDC::QMS::Citizen::Generic_Sensor_ptr p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_release</name>
      <anchor>a2</anchor>
      <arglist>(STDC::QMS::Citizen::Generic_Sensor_ptr p)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Citizen::Generic_Sensor_ptr</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_nil</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Citizen::Generic_Sensor_ptr</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_narrow</name>
      <anchor>a4</anchor>
      <arglist>(CORBA::Object *p, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Object *</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_upcast</name>
      <anchor>a5</anchor>
      <arglist>(void *src)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>CORBA::TypeCode</type>
      <name>_tc_TAO_tc_STDC_QMS_Citizen_Generic_Sensor</name>
      <anchor>a6</anchor>
      <arglist>(CORBA::tk_objref, sizeof(_oc_STDC_QMS_Citizen_Generic_Sensor),(char *)&amp;_oc_STDC_QMS_Citizen_Generic_Sensor, 0, sizeof(STDC::QMS::Citizen::Generic_Sensor))</arglist>
    </member>
    <member kind="function">
      <type>TAO_NAMESPACE_END TAO_NAMESPACE_END TAO_NAMESPACE_END void</type>
      <name>operator&lt;&lt;=</name>
      <anchor>a7</anchor>
      <arglist>(CORBA::Any &amp;_tao_any, STDC::QMS::Citizen::Generic_Sensor_ptr _tao_elem)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&gt;&gt;=</name>
      <anchor>a8</anchor>
      <arglist>(const CORBA::Any &amp;_tao_any, STDC::QMS::Citizen::Generic_Sensor_ptr &amp;_tao_elem)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&lt;&lt;</name>
      <anchor>a9</anchor>
      <arglist>(TAO_OutputCDR &amp;strm, const STDC::QMS::Citizen::Generic_Sensor_ptr _tao_objref)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&gt;&gt;</name>
      <anchor>a10</anchor>
      <arglist>(TAO_InputCDR &amp;strm, STDC::QMS::Citizen::Generic_Sensor_ptr &amp;_tao_objref)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const CORBA::Long</type>
      <name>_oc_STDC_QMS_Citizen_Generic_Sensor</name>
      <anchor>a0</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_SensorC.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorC_8h</filename>
    <includes id="Generic__SensorC_8i" name="Generic_SensorC.i" local="yes">Generic_SensorC.i</includes>
    <member kind="define">
      <type>#define</type>
      <name>TAO_EXPORT_MACRO</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_STDC_QMS_CITIZEN_GENERIC_SENSOR___PTR_CH_</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_STDC_QMS_CITIZEN_GENERIC_SENSOR___VAR_CH_</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_STDC_QMS_CITIZEN_GENERIC_SENSOR___OUT_CH_</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>_STDC_QMS_CITIZEN_GENERIC_SENSOR_CH_</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator&lt;&lt;=</name>
      <anchor>a5</anchor>
      <arglist>(CORBA::Any &amp;, STDC::QMS::Citizen::Generic_Sensor_ptr)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&gt;&gt;=</name>
      <anchor>a6</anchor>
      <arglist>(const CORBA::Any &amp;, STDC::QMS::Citizen::Generic_Sensor *&amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_SensorC.i</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorC_8i</filename>
    <member kind="define">
      <type>#define</type>
      <name>_STDC_QMS_CITIZEN_GENERIC_SENSOR___CI_</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&lt;&lt;</name>
      <anchor>a1</anchor>
      <arglist>(TAO_OutputCDR &amp;, const STDC::QMS::Citizen::Generic_Sensor_ptr)</arglist>
    </member>
    <member kind="function">
      <type>CORBA::Boolean</type>
      <name>operator&gt;&gt;</name>
      <anchor>a2</anchor>
      <arglist>(TAO_InputCDR &amp;, STDC::QMS::Citizen::Generic_Sensor_ptr &amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS_8cpp</filename>
    <includes id="Generic__SensorS_8h" name="Generic_SensorS.h" local="yes">Generic_SensorS.h</includes>
    <class kind="class">TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable</class>
    <member kind="function">
      <type>STDC::QMS::Citizen::_TAO_Generic_Sensor_Proxy_Broker *</type>
      <name>STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_function</name>
      <anchor>a2</anchor>
      <arglist>(CORBA::Object_ptr obj)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Factory_Initializer</name>
      <anchor>a3</anchor>
      <arglist>(long)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable</type>
      <name>tao_STDC_QMS_Citizen_Generic_Sensor_optable</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>int</type>
      <name>STDC_QMS_Citizen__TAO_Generic_Sensor_Proxy_Broker_Stub_Factory_Initializer_Scarecrow</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS_8h</filename>
    <includes id="Generic__SensorC_8h" name="Generic_SensorC.h" local="yes">Generic_SensorC.h</includes>
    <includes id="Generic__SensorS__T_8h" name="Generic_SensorS_T.h" local="yes">Generic_SensorS_T.h</includes>
    <includes id="Generic__SensorS_8i" name="Generic_SensorS.i" local="yes">Generic_SensorS.i</includes>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS.i</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS_8i</filename>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS_T.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS__T_8cpp</filename>
    <includes id="Generic__SensorS__T_8h" name="Generic_SensorS_T.h" local="yes">Generic_SensorS_T.h</includes>
    <includes id="Generic__SensorS__T_8i" name="Generic_SensorS_T.i" local="yes">Generic_SensorS_T.i</includes>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS_T.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS__T_8h</filename>
    <includes id="Generic__SensorS__T_8i" name="Generic_SensorS_T.i" local="yes">Generic_SensorS_T.i</includes>
  </compound>
  <compound kind="file">
    <name>Generic_SensorS_T.i</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Generic__SensorS__T_8i</filename>
  </compound>
  <compound kind="file">
    <name>Generic_Wrapper_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/DLL_Intercept/</path>
    <filename>Generic__Wrapper__Probe_8cpp</filename>
    <includes id="Generic__Wrapper__Probe_8h" name="Generic_Wrapper_Probe.h" local="yes">Generic_Wrapper_Probe.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a1</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a3</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a4</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>dll_intercept_fmt</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Generic_Wrapper_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/DLL_Intercept/</path>
    <filename>Generic__Wrapper__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a4a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a4a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_flow.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>get__data__flow_8cpp</filename>
    <includes id="get__data__flow_8h" name="get_data_flow.h" local="yes">get_data_flow.h</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a1</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a1</anchor>
      <arglist>(string hostnames, char *node_names[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_flow.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>get__data__flow_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MAXNAMELEN</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NODES</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a2</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a3</anchor>
      <arglist>(string, char *[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_GCP.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Generic/</path>
    <filename>get__data__GCP_8cpp</filename>
    <includes id="get__data__GCP_8h" name="get_data_GCP.h" local="yes">get_data_GCP.h</includes>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a2</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>graph_payload_fmt</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>graph_payload_data</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_GCP.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Generic/</path>
    <filename>get__data__GCP_8h</filename>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a0</anchor>
      <arglist>(void *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_graph.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>get__data__graph_8cpp</filename>
    <includes id="get__data__graph_8h" name="get_data_graph.h" local="yes">get_data_graph.h</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a0</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a1</anchor>
      <arglist>(string hostnames, char *node_names[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_graph.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>get__data__graph_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MAXNAMELEN</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NODES</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a2</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a3</anchor>
      <arglist>(string, char *[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_O.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/</path>
    <filename>get__data__O_8cpp</filename>
    <includes id="get__data__O_8h" name="get_data_O.h" local="yes">get_data_O.h</includes>
    <member kind="function">
      <type>void</type>
      <name>get_data</name>
      <anchor>a0</anchor>
      <arglist>(char *src, char *dest)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>get_data_O.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/</path>
    <filename>get__data__O_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>get_data</name>
      <anchor>a0</anchor>
      <arglist>(char *, char *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>hello_world.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>hello__world_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Hello__World__Impl_8h" name="Hello_World_Impl.h" local="yes">Hello_World_Impl.h</includes>
    <class kind="class">sensor_error_handler</class>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Hello_World_Impl *</type>
      <name>sensor_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hello_World.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Hello__World_8h</filename>
  </compound>
  <compound kind="file">
    <name>Hello_World.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Hello__World_8idl</filename>
    <includes id="Command_8idl" name="Command.idl" local="yes">Command.idl</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>hello_world_client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/test/</path>
    <filename>hello__world__client_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Client__HW_8h" name="Client_HW.h" local="yes">Client_HW.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="class">client_error_handler</class>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Test_Client *</type>
      <name>client_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hello_World_Impl.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Hello__World__Impl_8cpp</filename>
    <includes id="Hello__World__Impl_8h" name="Hello_World_Impl.h" local="yes">Hello_World_Impl.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a2</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>request_handler</name>
      <anchor>a3</anchor>
      <arglist>(IDOM_Node *node_p, struct Hello_World_Request &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>helloWorld_handler</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p, struct helloWorld &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_message_data</name>
      <anchor>a6</anchor>
      <arglist>(STDC::QMS::QMSMessage &amp;config, struct hw_payload_data &amp;request_data)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a0</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Hello_World_Impl.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Hello__World__Impl_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="Meta__Data__HW_8h" name="Meta_Data_HW.h" local="yes">Meta_Data_HW.h</includes>
    <includes id="Message__Format__HW_8h" name="Message_Format_HW.h" local="yes">Message_Format_HW.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>instantiate.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/test/</path>
    <filename>instantiate_8cpp</filename>
    <includes id="QMS__MLD_8h" name="QMS_MLD.h" local="yes">QMS_MLD.h</includes>
  </compound>
  <compound kind="file">
    <name>Instrumentation.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/</path>
    <filename>Instrumentation_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Linux_Perf_Mon_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Linux_Perf_Mon/</path>
    <filename>Linux__Perf__Mon__Probe_8cpp</filename>
    <includes id="Linux__Perf__Mon__Probe_8h" name="Linux_Perf_Mon_Probe.h" local="yes">Linux_Perf_Mon_Probe.h</includes>
    <includes id="Linux__PM__get__data_8h" name="Linux_PM_get_data.h" local="yes">Linux_PM_get_data.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a2</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a3</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a4</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>payload_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Linux_Perf_Mon_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Linux_Perf_Mon/</path>
    <filename>Linux__Perf__Mon__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a13a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>pause_probe</name>
      <anchor>a13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a13a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repetitions</name>
      <anchor>a13a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repeatInterval</name>
      <anchor>a13a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a10</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;, void *)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>enum status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_asset_guard</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>repeat_count</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>timespec</type>
      <name>repeat_interval</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Linux_PM_get_data.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Linux_Perf_Mon/</path>
    <filename>Linux__PM__get__data_8cpp</filename>
    <includes id="Linux__PM__get__data_8h" name="Linux_PM_get_data.h" local="yes">Linux_PM_get_data.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>get_data</name>
      <anchor>a1</anchor>
      <arglist>(char *counter, char *probe_output)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>modify_data</name>
      <anchor>a1</anchor>
      <arglist>(string &amp;src, const char *pattern, const char *replace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_column_data</name>
      <anchor>a2</anchor>
      <arglist>(char *src, char *replace)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Linux_PM_get_data.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Linux_Perf_Mon/</path>
    <filename>Linux__PM__get__data_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MEM_COUNTER</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SWAP_COUNTER</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CPU_COUNTER</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PS_COUNTER</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GET_RESOURECE_BUF</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAX_LINE_BUFFER</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_data</name>
      <anchor>a10</anchor>
      <arglist>(char *counter, char *probe_output)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_column_data</name>
      <anchor>a11</anchor>
      <arglist>(char *src, char *replace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>modify_data</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;src, const char *pattern, const char *replace)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>long</type>
      <name>s_user</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>long</type>
      <name>s_nice</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>long</type>
      <name>s_system</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>double</type>
      <name>s_timestamp</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>List_Data.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>List__Data_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>List_Data_HW.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>List__Data__HW_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>List_Data_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>List__Data__Remos_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>ListOffers.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>ListOffers_8cpp</filename>
    <includes id="ListOffers_8h" name="ListOffers.h" local="yes">ListOffers.h</includes>
    <member kind="function">
      <type>void</type>
      <name>sig_handler</name>
      <anchor>a1</anchor>
      <arglist>(int sig)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_all_types</name>
      <anchor>a3</anchor>
      <arglist>(CosTrading::Lookup_ptr lookup_if, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_offers</name>
      <anchor>a4</anchor>
      <arglist>(CosTrading::Lookup_ptr lookup_if, char *type_name, char *category_p, CORBA_Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ListOffers.h</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>ListOffers_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <namespace>CosTrading</namespace>
    <namespace>CosTradingRepos</namespace>
    <member kind="function">
      <type>void</type>
      <name>print_offers</name>
      <anchor>a0</anchor>
      <arglist>(CosTrading::Lookup_ptr, char *, char *, CORBA_Environment &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_all_types</name>
      <anchor>a1</anchor>
      <arglist>(CosTrading::Lookup_ptr, CORBA::Environment &amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Message_Format.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Message__Format_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <class kind="struct">helloWorld</class>
    <class kind="struct">payload_data</class>
    <class kind="struct">probe_info</class>
    <class kind="struct">query_info</class>
    <class kind="struct">Request</class>
    <member kind="variable">
      <type>const int</type>
      <name>MAX_DATA</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Message_Format_HW.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Message__Format__HW_8h</filename>
    <class kind="struct">Hello_World_Request</class>
    <class kind="struct">helloWorld</class>
    <class kind="struct">hw_payload_data</class>
  </compound>
  <compound kind="file">
    <name>Message_Format_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Message__Format__Remos_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <class kind="struct">helloWorld</class>
    <class kind="struct">payload_data</class>
    <class kind="struct">probe_info</class>
    <class kind="struct">query_info</class>
    <class kind="struct">Request</class>
    <member kind="variable">
      <type>const int</type>
      <name>MAX_DATA</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Meta_Data.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Meta__Data_8cpp</filename>
    <includes id="Meta__Data_8h" name="Meta_Data.h" local="yes">Meta_Data.h</includes>
    <includes id="Generic__Sensor__Impl_8h" name="Generic_Sensor_Impl.h" local="yes">Generic_Sensor_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Continuous__Pipe__Proxy_8h" name="Continuous_Pipe_Proxy.h" local="yes">Continuous_Pipe_Proxy.h</includes>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a3</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Generic_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a2</anchor>
      <arglist>[11]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Meta_Data.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Meta__Data_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="List__Data_8h" name="List_Data.h" local="yes">List_Data.h</includes>
    <includes id="Probe__Proxy_8h" name="Probe_Proxy.h" local="yes">Probe_Proxy.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Message__Format_8h" name="Message_Format.h" local="yes">Message_Format.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Meta_Data_HW.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Meta__Data__HW_8cpp</filename>
    <includes id="Meta__Data__HW_8h" name="Meta_Data_HW.h" local="yes">Meta_Data_HW.h</includes>
    <includes id="Hello__World__Impl_8h" name="Hello_World_Impl.h" local="yes">Hello_World_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Parse__Duration_8h" name="Parse_Duration.h" local="yes">Parse_Duration.h</includes>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a5</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Hello_World_Impl *</type>
      <name>sensor_p</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a2</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>response_fmt</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>err_response_fmt</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Meta_Data_HW.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>Meta__Data__HW_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="List__Data__HW_8h" name="List_Data_HW.h" local="yes">List_Data_HW.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Message__Format__HW_8h" name="Message_Format_HW.h" local="yes">Message_Format_HW.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Meta_Data_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Meta__Data__Remos_8cpp</filename>
    <includes id="Meta__Data__Remos_8h" name="Meta_Data_Remos.h" local="yes">Meta_Data_Remos.h</includes>
    <includes id="Remos__Sensor__Impl_8h" name="Remos_Sensor_Impl.h" local="yes">Remos_Sensor_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Continuous__Pipe__Proxy__Remos_8h" name="Continuous_Pipe_Proxy_Remos.h" local="yes">Continuous_Pipe_Proxy_Remos.h</includes>
    <includes id="Parse__Duration_8h" name="Parse_Duration.h" local="yes">Parse_Duration.h</includes>
    <member kind="function">
      <type>void</type>
      <name>CallBack</name>
      <anchor>a4</anchor>
      <arglist>(const string &amp;query, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>request_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, struct Request &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>helloWorld_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, struct helloWorld &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Remos_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a2</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>response_fmt</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Meta_Data_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Meta__Data__Remos_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="List__Data__Remos_8h" name="List_Data_Remos.h" local="yes">List_Data_Remos.h</includes>
    <includes id="Probe__Proxy__Remos_8h" name="Probe_Proxy_Remos.h" local="yes">Probe_Proxy_Remos.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="Message__Format__Remos_8h" name="Message_Format_Remos.h" local="yes">Message_Format_Remos.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>NT_Perf_Mon_getdata.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/NT_Perf_Mon/</path>
    <filename>NT__Perf__Mon__getdata_8cpp</filename>
    <includes id="NT__Perf__Mon__getdata_8h" name="NT_Perf_Mon_getdata.h" local="yes">NT_Perf_Mon_getdata.h</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>INITIAL_CALL</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DIFFERENT_COUNTER</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NOT_A_COUNTER</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PS_COUNTER</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getdata</name>
      <anchor>a10</anchor>
      <arglist>(char *counterName, char *perfmon_data)</arglist>
    </member>
    <member kind="variable">
      <type>HQUERY</type>
      <name>getData_hQuery</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>HCOUNTER</type>
      <name>getData_counters</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PDH_FMT_COUNTERVALUE</type>
      <name>getData_fmtValue</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>perfmon_processList_fmt</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>process_row_fmt</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>perfmon_counterValue_fmt</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>NT_Perf_Mon_getdata.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/NT_Perf_Mon/</path>
    <filename>NT__Perf__Mon__getdata_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>getdata</name>
      <anchor>a0</anchor>
      <arglist>(char *, char *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>NT_Perf_Mon_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/NT_Perf_Mon/</path>
    <filename>NT__Perf__Mon__Probe_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="NT__Perf__Mon__Probe_8h" name="NT_Perf_Mon_Probe.h" local="yes">NT_Perf_Mon_Probe.h</includes>
    <includes id="NT__Perf__Mon__getdata_8h" name="NT_Perf_Mon_getdata.h" local="yes">NT_Perf_Mon_getdata.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a1</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a3</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a4</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>NT_Perf_Mon_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/NT_Perf_Mon/</path>
    <filename>NT__Perf__Mon__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a13a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>pause_probe</name>
      <anchor>a13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a13a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repetitions</name>
      <anchor>a13a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repeatInterval</name>
      <anchor>a13a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a10</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;, void *)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>enum status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_asset_guard</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>repeat_count</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>timespec</type>
      <name>refresh_rate</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>One_Shot_Pipe_Proxy.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>One__Shot__Pipe__Proxy_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="One__Shot__Pipe__Proxy_8h" name="One_Shot_Pipe_Proxy.h" local="yes">One_Shot_Pipe_Proxy.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>One_Shot_Pipe_Proxy.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>One__Shot__Pipe__Proxy_8h</filename>
    <includes id="Pipe__Proxy_8h" name="Pipe_Proxy.h" local="yes">Pipe_Proxy.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>One_Shot_Pipe_Proxy_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>One__Shot__Pipe__Proxy__Remos_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="One__Shot__Pipe__Proxy__Remos_8h" name="One_Shot_Pipe_Proxy_Remos.h" local="yes">One_Shot_Pipe_Proxy_Remos.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>One_Shot_Pipe_Proxy_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>One__Shot__Pipe__Proxy__Remos_8h</filename>
    <includes id="Pipe__Proxy__Remos_8h" name="Pipe_Proxy_Remos.h" local="yes">Pipe_Proxy_Remos.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>OneShot.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/</path>
    <filename>OneShot_8h</filename>
  </compound>
  <compound kind="file">
    <name>Parse_Duration.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>Parse__Duration_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
  </compound>
  <compound kind="file">
    <name>Parse_Duration.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>Parse__Duration_8h</filename>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
  </compound>
  <compound kind="file">
    <name>Parse_XML.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>Parse__XML_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Parse_XML.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>Parse__XML_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <class kind="class">IDOMTreeErrorReporter</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Payload_8cpp</filename>
    <includes id="Payload_8h" name="Payload.h" local="yes">Payload.h</includes>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a3</anchor>
      <arglist>(string QMSUniqueName_Host, struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>perfmon_payload_print</name>
      <anchor>a4</anchor>
      <arglist>(string QMSUniqueName_Host, struct PerfMon_Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>plotData_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>perfmonData_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probeData_handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p, struct Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>perfmonProbe_handler</name>
      <anchor>a9</anchor>
      <arglist>(IDOM_Node *node_p, struct PerfMon_Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>genericCProbe_handler</name>
      <anchor>a10</anchor>
      <arglist>(IDOM_Node *node_p, struct Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a11</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>perfmon_payload_generator</name>
      <anchor>a13</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>action_payload_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>action_perfmon_payload_fmt</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Payload_8h</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="struct">Payload_Data</class>
    <class kind="struct">PerfMon_Payload_Data</class>
    <class kind="struct">plotData</class>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a0</anchor>
      <arglist>(IDOM_Node *node_P, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a1</anchor>
      <arglist>(string QMSUniqueName_Host, struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>perfmon_payload_print</name>
      <anchor>a2</anchor>
      <arglist>(string QMSUniqueName_Host, struct PerfMon_Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a3</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>perfmon_payload_generator</name>
      <anchor>a4</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload_HW.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/test/</path>
    <filename>Payload__HW_8cpp</filename>
    <includes id="Payload__HW_8h" name="Payload_HW.h" local="yes">Payload_HW.h</includes>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a3</anchor>
      <arglist>(struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>data_handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p, struct Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>helloWorld_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, struct Payload_Data *results_p)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a8</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>request_payload_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>action_payload_fmt</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload_HW.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/test/</path>
    <filename>Payload__HW_8h</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="struct">Payload_Data</class>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a0</anchor>
      <arglist>(IDOM_Node *node_P, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a1</anchor>
      <arglist>(struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;probe_schema_uri, const char *action)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>Payload__Remos_8cpp</filename>
    <includes id="Payload__Remos_8h" name="Payload_Remos.h" local="yes">Payload_Remos.h</includes>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a4</anchor>
      <arglist>(struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>linkData_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, struct linkData &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>bandwidthData_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, struct bandwidthData &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>remosProbe_handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p, struct RemosData &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a9</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a10</anchor>
      <arglist>(string &amp;probe_schema_uri, list&lt; string &gt; &amp;hosts, const char *action)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>payload_clean</name>
      <anchor>a11</anchor>
      <arglist>(struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>flow_payload_fmt</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>graph_payload_fmt</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>action_payload_fmt</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Payload_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>Payload__Remos_8h</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="struct">bandwidthData</class>
    <class kind="struct">linkData</class>
    <class kind="struct">Payload_Data</class>
    <class kind="struct">RemosData</class>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a0</anchor>
      <arglist>(IDOM_Node *node_P, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>payload_print</name>
      <anchor>a1</anchor>
      <arglist>(struct Payload_Data &amp;response_data)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>payload_generator</name>
      <anchor>a2</anchor>
      <arglist>(string &amp;probe_schema_uri, list&lt; string &gt; &amp;hosts, const char *action)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>payload_clean</name>
      <anchor>a3</anchor>
      <arglist>(struct Payload_Data &amp;)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Pipe_Proxy.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Pipe__Proxy_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Pipe__Proxy_8h" name="Pipe_Proxy.h" local="yes">Pipe_Proxy.h</includes>
  </compound>
  <compound kind="file">
    <name>Pipe_Proxy.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Pipe__Proxy_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Probe__Proxy_8h" name="Probe_Proxy.h" local="yes">Probe_Proxy.h</includes>
    <includes id="EC__Adapter_8h" name="EC_Adapter.h" local="yes">EC_Adapter.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Pipe_Proxy_Remos.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Pipe__Proxy__Remos_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Pipe__Proxy__Remos_8h" name="Pipe_Proxy_Remos.h" local="yes">Pipe_Proxy_Remos.h</includes>
  </compound>
  <compound kind="file">
    <name>Pipe_Proxy_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Pipe__Proxy__Remos_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Probe__Proxy__Remos_8h" name="Probe_Proxy_Remos.h" local="yes">Probe_Proxy_Remos.h</includes>
    <includes id="EC__Adapter_8h" name="EC_Adapter.h" local="yes">EC_Adapter.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/</path>
    <filename>Probe_8h</filename>
  </compound>
  <compound kind="file">
    <name>Probe_Proxy.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/</path>
    <filename>Probe__Proxy_8h</filename>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <includes id="Meta__Data_8h" name="Meta_Data.h" local="yes">Meta_Data.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Probe_Proxy_Remos.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Probe__Proxy__Remos_8h</filename>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <includes id="Meta__Data__Remos_8h" name="Meta_Data_Remos.h" local="yes">Meta_Data_Remos.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Push_Consumer.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>Push__Consumer_8cpp</filename>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Push_Consumer.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>Push__Consumer_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Push_Supplier.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>Push__Supplier_8cpp</filename>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Push_Supplier.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/</path>
    <filename>Push__Supplier_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS.h</name>
    <path>/home/srivasta/Work/devel/QMS/</path>
    <filename>QMS_8h</filename>
  </compound>
  <compound kind="file">
    <name>QMS_Linked_List.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Linked__List_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>QMS_Linked_List.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Linked__List_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="QMS__MLD__Containers_8h" name="QMS_MLD_Containers.h" local="yes">QMS_MLD_Containers.h</includes>
    <includes id="QMS__Linked__List_8cpp" name="QMS_Linked_List.cpp" local="yes">QMS_Linked_List.cpp</includes>
    <class kind="class">QMS_Linked_List</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Linked_List_Iterators.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Linked__List__Iterators_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>QMS_Linked_List_Iterators.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Linked__List__Iterators_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="QMS__Linked__List_8h" name="QMS_Linked_List.h" local="yes">QMS_Linked_List.h</includes>
    <includes id="QMS__Linked__List__Iterators_8cpp" name="QMS_Linked_List_Iterators.cpp" local="yes">QMS_Linked_List_Iterators.cpp</includes>
    <class kind="class">QMS_Linked_List_Iterator</class>
    <class kind="class">QMS_Linked_List_Iterator_Base</class>
    <class kind="class">QMS_Linked_List_Reverse_Iterator</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Logger.h</name>
    <path>/home/srivasta/Work/devel/QMS/PlugIns/Logger/</path>
    <filename>QMS__Logger_8h</filename>
  </compound>
  <compound kind="file">
    <name>QMS_MLD.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__MLD_8h</filename>
    <includes id="QMS__Type__list_8h" name="QMS_Type_list.h" local="yes">QMS_Type_list.h</includes>
    <includes id="QMS__Nodes_8h" name="QMS_Nodes.h" local="yes">QMS_Nodes.h</includes>
    <includes id="QMS__MLD__Factory_8h" name="QMS_MLD_Factory.h" local="yes">QMS_MLD_Factory.h</includes>
    <includes id="QMS__MLD__Containers_8h" name="QMS_MLD_Containers.h" local="yes">QMS_MLD_Containers.h</includes>
    <includes id="QMS__Linked__List__Iterators_8h" name="QMS_Linked_List_Iterators.h" local="yes">QMS_Linked_List_Iterators.h</includes>
    <includes id="QMS__Linked__List_8h" name="QMS_Linked_List.h" local="yes">QMS_Linked_List.h</includes>
  </compound>
  <compound kind="file">
    <name>QMS_MLD_Containers.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__MLD__Containers_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>QMS_MLD_Containers.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__MLD__Containers_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="QMS__Type__list_8h" name="QMS_Type_list.h" local="yes">QMS_Type_list.h</includes>
    <includes id="QMS__Nodes_8h" name="QMS_Nodes.h" local="yes">QMS_Nodes.h</includes>
    <includes id="QMS__MLD__Containers_8cpp" name="QMS_MLD_Containers.cpp" local="yes">QMS_MLD_Containers.cpp</includes>
    <class kind="class">QMS_MLD_Containers</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_MLD_Factory.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__MLD__Factory_8h</filename>
    <class kind="class">Linked_List_Factory</class>
    <class kind="class">QMS_MLD_Factory</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Nodes.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Nodes_8cpp</filename>
  </compound>
  <compound kind="file">
    <name>QMS_Nodes.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Nodes_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="QMS__Type__list_8h" name="QMS_Type_list.h" local="yes">QMS_Type_list.h</includes>
    <includes id="QMS__Nodes_8cpp" name="QMS_Nodes.cpp" local="yes">QMS_Nodes.cpp</includes>
    <class kind="class">QMS_Node</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>NODE_COLOUR</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BLACK</name>
      <anchor>a3a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RED</name>
      <anchor>a3a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Sensor.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/</path>
    <filename>QMS__Sensor_8h</filename>
    <class kind="class">QMS_Sensor</class>
  </compound>
  <compound kind="file">
    <name>QMS_Trader_ECInfo.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>QMS__Trader__ECInfo_8cpp</filename>
    <includes id="QMS__Trader__ECInfo_8h" name="QMS_Trader_ECInfo.h" local="yes">QMS_Trader_ECInfo.h</includes>
    <member kind="function">
      <type>void</type>
      <name>sig_handler</name>
      <anchor>a3</anchor>
      <arglist>(int sig)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a4</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl *</type>
      <name>ecreg</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Trader_ECInfo.h</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>QMS__Trader__ECInfo_8h</filename>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
  </compound>
  <compound kind="file">
    <name>QMS_Trader_ECInfo_Impl.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>QMS__Trader__ECInfo__Impl_8cpp</filename>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
  </compound>
  <compound kind="file">
    <name>QMS_Trader_ECInfo_Impl.h</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>QMS__Trader__ECInfo__Impl_8h</filename>
    <includes id="ECInfo_8h" name="ECInfo.h" local="yes">ECInfo.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>QMS_UNIQUE_CATEGORY_NAME</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>QT_SERVICE_TYPE</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ECINFO_SERVICE_TYPE</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SUPPLIER_SERVICE_TYPE</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_ANNOUNCE_CHANNEL</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_DATA_CHANNEL</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_REQUEST_CHANNEL</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>QMS_Type_list.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/</path>
    <filename>QMS__Type__list_8h</filename>
    <includes id="QMS__MLD__Factory_8h" name="QMS_MLD_Factory.h" local="yes">QMS_MLD_Factory.h</includes>
    <class kind="class">QMS_Sub_Type_Element</class>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>README</name>
    <path>/home/srivasta/Work/devel/QMS/</path>
    <filename>README</filename>
  </compound>
  <compound kind="file">
    <name>README.background</name>
    <path>/home/srivasta/Work/devel/QMS/Documentation/</path>
    <filename>README_8background</filename>
  </compound>
  <compound kind="file">
    <name>README.FAQ</name>
    <path>/home/srivasta/Work/devel/QMS/Documentation/</path>
    <filename>README_8FAQ</filename>
  </compound>
  <compound kind="file">
    <name>README.hello_world</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Hello_World/</path>
    <filename>README_8hello__world</filename>
  </compound>
  <compound kind="file">
    <name>README.install</name>
    <path>/home/srivasta/Work/devel/QMS/Documentation/</path>
    <filename>README_8install</filename>
  </compound>
  <compound kind="file">
    <name>README.misc</name>
    <path>/home/srivasta/Work/devel/QMS/Documentation/</path>
    <filename>README_8misc</filename>
  </compound>
  <compound kind="file">
    <name>README.run</name>
    <path>/home/srivasta/Work/devel/QMS/Documentation/</path>
    <filename>README_8run</filename>
  </compound>
  <compound kind="file">
    <name>README.trader</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>README_8trader</filename>
  </compound>
  <compound kind="file">
    <name>Receiver.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Receiver_8cpp</filename>
    <includes id="Receiver_8h" name="Receiver.h" local="yes">Receiver.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Receiver.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>Receiver_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Generic__SensorC_8h" name="Generic_SensorC.h" local="yes">Generic_SensorC.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="class">Test_Receiver</class>
  </compound>
  <compound kind="file">
    <name>receiver_client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>receiver__client_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Receiver_8h" name="Receiver.h" local="yes">Receiver.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="class">client_error_handler</class>
    <member kind="function">
      <type>void</type>
      <name>add_handler</name>
      <anchor>a2</anchor>
      <arglist>(client_error_handler *signal_handler_p, STDC::QMS::CORBA_Handles *handles_p, int signal)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a3</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Test_Receiver *</type>
      <name>client_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>remos_client.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>remos__client_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Client__Remos_8h" name="Client_Remos.h" local="yes">Client_Remos.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="class">client_error_handler</class>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Test_Client *</type>
      <name>client_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Flow_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>Remos__Flow__Probe_8cpp</filename>
    <includes id="Remos__Flow__Probe_8h" name="Remos_Flow_Probe.h" local="yes">Remos_Flow_Probe.h</includes>
    <includes id="get__data__graph_8h" name="get_data_graph.h" local="yes">get_data_graph.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <member kind="function">
      <type>void</type>
      <name>handler</name>
      <anchor>a1</anchor>
      <arglist>(Remos_Error err, Remos_Ptr ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a2</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a3</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a4</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Flow_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>Remos__Flow__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a13a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>pause_probe</name>
      <anchor>a13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a13a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repetitions</name>
      <anchor>a13a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repeatInterval</name>
      <anchor>a13a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a10</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;, void *)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_asset_guard</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>repeat_count</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>timespec</type>
      <name>refresh_rate</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Flow_Probe_Oneshot.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/Remos/</path>
    <filename>Remos__Flow__Probe__Oneshot_8cpp</filename>
    <includes id="Remos__Flow__Probe__Oneshot_8h" name="Remos_Flow_Probe_Oneshot.h" local="yes">Remos_Flow_Probe_Oneshot.h</includes>
    <member kind="function">
      <type>void</type>
      <name>handler</name>
      <anchor>a1</anchor>
      <arglist>(Remos_Error err, Remos_Ptr ptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFlowInfo</name>
      <anchor>a3</anchor>
      <arglist>(char *node_names[], int num_nodes, int request_id, int data_id, double sleep_interval)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a4</anchor>
      <arglist>(string hostnames, char *node_names[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Flow_Probe_Oneshot.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/Remos/</path>
    <filename>Remos__Flow__Probe__Oneshot_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NODES</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXNAMELEN</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFlowInfo</name>
      <anchor>a3</anchor>
      <arglist>(char **, int, int, int, double)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a4</anchor>
      <arglist>(string, char *[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Graph_Probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>Remos__Graph__Probe_8cpp</filename>
    <includes id="Remos__Graph__Probe_8h" name="Remos_Graph_Probe.h" local="yes">Remos_Graph_Probe.h</includes>
    <includes id="get__data__graph_8h" name="get_data_graph.h" local="yes">get_data_graph.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <member kind="function">
      <type>void</type>
      <name>handler</name>
      <anchor>a1</anchor>
      <arglist>(Remos_Error err, Remos_Ptr ptr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a2</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a3</anchor>
      <arglist>(string &amp;cmdstr, void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a4</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Graph_Probe.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/Remos/</path>
    <filename>Remos__Graph__Probe_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_states</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>start_probe</name>
      <anchor>a13a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>pause_probe</name>
      <anchor>a13a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>stop_probe</name>
      <anchor>a13a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repetitions</name>
      <anchor>a13a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>read_repeatInterval</name>
      <anchor>a13a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>worker</name>
      <anchor>a10</anchor>
      <arglist>(void *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listener</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>setflags</name>
      <anchor>a12</anchor>
      <arglist>(string &amp;, void *)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>status_states</type>
      <name>status</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>TD_asset_guard</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>repeat_count</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>timespec</type>
      <name>refresh_rate</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Graph_Probe_Oneshot.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/Remos/</path>
    <filename>Remos__Graph__Probe__Oneshot_8cpp</filename>
    <includes id="Remos__Graph__Probe__Oneshot_8h" name="Remos_Graph_Probe_Oneshot.h" local="yes">Remos_Graph_Probe_Oneshot.h</includes>
    <member kind="function">
      <type>void</type>
      <name>handler</name>
      <anchor>a1</anchor>
      <arglist>(Remos_Error err, Remos_Ptr ptr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGraphInfo</name>
      <anchor>a3</anchor>
      <arglist>(char *node_names[], int num_nodes, int request_id, int data_id, double sleep_interval)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a4</anchor>
      <arglist>(string hostnames, char *node_names[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Graph_Probe_Oneshot.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/OneShot/Simple/Remos/</path>
    <filename>Remos__Graph__Probe__Oneshot_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MAX_NODES</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_SLEEP</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXNAMELEN</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getGraphInfo</name>
      <anchor>a3</anchor>
      <arglist>(char **, int, int, int, double)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>StringToCharHosts</name>
      <anchor>a4</anchor>
      <arglist>(string, char *[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>remos_sensor.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>remos__sensor_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">Push_Supplier.h</includes>
    <includes id="Remos__Sensor__Impl_8h" name="Remos_Sensor_Impl.h" local="yes">Remos_Sensor_Impl.h</includes>
    <class kind="class">sensor_error_handler</class>
    <member kind="function">
      <type>void</type>
      <name>add_handler</name>
      <anchor>a2</anchor>
      <arglist>(sensor_error_handler *signal_handler_p, STDC::QMS::CORBA_Handles *handles_p, int signal)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a3</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Remos_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Sensor.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Remos__Sensor_8h</filename>
  </compound>
  <compound kind="file">
    <name>Remos_Sensor.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Remos__Sensor_8idl</filename>
    <includes id="Command_8idl" name="Command.idl" local="yes">Command.idl</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>Remos_Sensor_Impl.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Remos__Sensor__Impl_8cpp</filename>
    <includes id="Remos__Sensor__Impl_8h" name="Remos_Sensor_Impl.h" local="yes">Remos_Sensor_Impl.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <member kind="function">
      <type>void</type>
      <name>print_message_data</name>
      <anchor>a2</anchor>
      <arglist>(STDC::QMS::QMSMessage &amp;config)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>propnames</name>
      <anchor>a0</anchor>
      <arglist>[11]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Remos_Sensor_Impl.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/</path>
    <filename>Remos__Sensor__Impl_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <includes id="QMS__Trader__ECInfo__Impl_8h" name="QMS_Trader_ECInfo_Impl.h" local="yes">QMS_Trader_ECInfo_Impl.h</includes>
    <includes id="Meta__Data__Remos_8h" name="Meta_Data_Remos.h" local="yes">Meta_Data_Remos.h</includes>
    <includes id="Message__Format__Remos_8h" name="Message_Format_Remos.h" local="yes">Message_Format_Remos.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="define">
      <type>#define</type>
      <name>Dllexport</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RM_SEND_IC.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/DLL_Intercept/</path>
    <filename>RM__SEND__IC_8cpp</filename>
    <includes id="RM__SEND__IC_8h" name="RM_SEND_IC.h" local="yes">RM_SEND_IC.h</includes>
    <member kind="function">
      <type>BOOL WINAPI</type>
      <name>DllMain</name>
      <anchor>a0</anchor>
      <arglist>(HMODULE hInst, ULONG reason, LPVOID lpReserved)</arglist>
    </member>
    <member kind="function">
      <type>DllExport int WINAPI</type>
      <name>Med_send</name>
      <anchor>a1</anchor>
      <arglist>(void *icall, SOCKET s, const char FAR *buf, int len, int flags)</arglist>
    </member>
    <member kind="function">
      <type>DllExport void</type>
      <name>InitializeWrapper</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>DllExport void</type>
      <name>CloseWrapper</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>RM_SEND_IC.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Probes/Continuous/Simple/DLL_Intercept/</path>
    <filename>RM__SEND__IC_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MAX_LENGTH</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DllExport</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WINAPI</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WSAAPI</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AnchoredMatch</name>
      <anchor>a4</anchor>
      <arglist>(str, conststr)</arglist>
    </member>
    <member kind="variable">
      <type>HANDLE</type>
      <name>hNamedPipe</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Sensor.h</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/</path>
    <filename>Sensor_8h</filename>
  </compound>
  <compound kind="file">
    <name>Simple_Logger.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/PlugIns/Logger/</path>
    <filename>Simple__Logger_8cpp</filename>
    <includes id="Simple__Logger_8h" name="Simple_Logger.h" local="yes">Simple_Logger.h</includes>
    <member kind="function">
      <type>void</type>
      <name>sig_handler</name>
      <anchor>a1</anchor>
      <arglist>(int sig)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>my_callback</name>
      <anchor>a2</anchor>
      <arglist>(const string &amp;data, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a3</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_offers</name>
      <anchor>a4</anchor>
      <arglist>(CosTrading::Lookup_ptr lookup_if, STDC::QMS::Citizen::Query *query_info, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iterate_thru_offers</name>
      <anchor>a5</anchor>
      <arglist>(CosTrading::OfferIterator_ptr offer_iterator, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_name_id</name>
      <anchor>a6</anchor>
      <arglist>(string &amp;data, CORBA::Long &amp;id, string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_qms_trader_ref</name>
      <anchor>a7</anchor>
      <arglist>(CosTrading::Lookup_ptr lookup_if, STDC::QMS::Citizen::QMS_Trader_ECInfo_var &amp;qt_var, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fill_query_struct</name>
      <anchor>a8</anchor>
      <arglist>(list&lt; string &gt; &amp;quns, vector&lt; STDC::QMS::Citizen::Query * &gt; &amp;query_list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_consumers</name>
      <anchor>a9</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_consumers</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_consumer_info_list</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Simple_Logger.h</name>
    <path>/home/srivasta/Work/devel/QMS/PlugIns/Logger/</path>
    <filename>Simple__Logger_8h</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
    <member kind="function">
      <type>void</type>
      <name>get_offers</name>
      <anchor>a5</anchor>
      <arglist>(CosTrading::Lookup_ptr lookup_if, STDC::QMS::Citizen::Query *query_info, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>iterate_thru_offers</name>
      <anchor>a6</anchor>
      <arglist>(CosTrading::OfferIterator_ptr offer_iterator, CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_name_id</name>
      <anchor>a7</anchor>
      <arglist>(string &amp;, CORBA::Long &amp;, string &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fill_query_struct</name>
      <anchor>a8</anchor>
      <arglist>(list&lt; string &gt; &amp;, vector&lt; STDC::QMS::Citizen::Query * &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_qms_trader_ref</name>
      <anchor>a9</anchor>
      <arglist>(CosTrading::Lookup_ptr, STDC::QMS::Citizen::QMS_Trader_ECInfo_var &amp;, CORBA::Environment &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>my_callback</name>
      <anchor>a10</anchor>
      <arglist>(const string &amp;, void *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_consumers</name>
      <anchor>a11</anchor>
      <arglist>(CORBA::Environment &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_consumers</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_consumer_info_list</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; STDC::QMS::Citizen::Query * &gt;</type>
      <name>Query_List</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list&lt; string &gt;</type>
      <name>EC_Info</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>list&lt; string &gt;</type>
      <name>query_strings</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; STDC::QMS::Push_Consumer * &gt;</type>
      <name>consumer_list</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; STDC::QMS::Citizen::Consumer_Info * &gt;</type>
      <name>consumer_info_list</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_capability.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__capability_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_Capability.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>test__Capability_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <class kind="class">IDOMTreeErrorReporter</class>
    <member kind="function">
      <type>const char *</type>
      <name>get_node_type</name>
      <anchor>a2</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_node_details</name>
      <anchor>a3</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>qms_uniq_name_element_handler</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe_type_element_handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe_data_reusable_element_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>name_element_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>value_element_handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>variable_element_handler</name>
      <anchor>a9</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invoke_element_handler</name>
      <anchor>a10</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>offer_element_handler</name>
      <anchor>a11</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probe_element_handler</name>
      <anchor>a12</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>qms_sensor_capability_handler</name>
      <anchor>a13</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>doc_handler</name>
      <anchor>a14</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a15</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>message_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_CORBA_Handles.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__CORBA__Handles_8cpp</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_duration.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__duration_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Parse__Duration_8cpp" name="Parse_Duration.cpp" local="yes">Parse_Duration.cpp</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_EC_Adapter.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/test/</path>
    <filename>test__EC__Adapter_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_exec.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>test__exec_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>deploy</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Am_I_Active</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ctrlpipe</name>
      <anchor>a2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datapipe</name>
      <anchor>a3</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>file_name_p_</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>argv_</name>
      <anchor>a5</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>delimiter</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_list_data.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>test__list__data_8cpp</filename>
    <includes id="List__Data_8h" name="List_Data.h" local="yes">List_Data.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_message.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__message_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <class kind="struct">helloWorld</class>
    <class kind="struct">payload_data</class>
    <class kind="struct">Request</class>
    <member kind="function">
      <type>const char *</type>
      <name>get_node_type</name>
      <anchor>a2</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_node_details</name>
      <anchor>a3</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>request_handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p, struct Request results)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>helloWorld_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p, struct helloWorld results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>payload_Handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a8</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>message_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_meta_data.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>test__meta__data_8cpp</filename>
    <includes id="Meta__Data_8cpp" name="Meta_Data.cpp" local="yes">Meta_Data.cpp</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_parse_xml.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__parse__xml_8cpp</filename>
    <includes id="Parse__XML_8h" name="Parse_XML.h" local="yes">Parse_XML.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_probe.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Remos/test/</path>
    <filename>test__probe_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Instrumentation_8h" name="Instrumentation.h" local="yes">Instrumentation.h</includes>
    <member kind="function">
      <type>void</type>
      <name>pause_probe</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resume_probe</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop_probe</name>
      <anchor>a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>deploy</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Am_I_Active</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ctrlpipe</name>
      <anchor>a2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>datapipe</name>
      <anchor>a3</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>ctrl_write_fd</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>file_name_p_</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>argv_</name>
      <anchor>a6</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_Push_Consumer.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/test/</path>
    <filename>test__Push__Consumer_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="Push__Consumer_8h" name="Push_Consumer.h" local="yes">Push_Consumer.h</includes>
    <member kind="function">
      <type>void</type>
      <name>sig_handler</name>
      <anchor>a2</anchor>
      <arglist>(int sig)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>my_callback</name>
      <anchor>a3</anchor>
      <arglist>(const string &amp;data, void *arg_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a4</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const RtecEventComm::EventType</type>
      <name>QMS_Remos_Data</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_Push_Supplier.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/EC_Adapter/test/</path>
    <filename>test__Push__Supplier_8cpp</filename>
    <includes id="Push__Supplier_8h" name="Push_Supplier.h" local="yes">EC_Adapter/Push_Supplier.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_trading.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>test__trading_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_XML.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Instrumentation/Sensors/Generic/test/</path>
    <filename>test__XML_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <class kind="class">IDOMTreeErrorReporter</class>
    <member kind="function">
      <type>const char *</type>
      <name>get_node_type</name>
      <anchor>a2</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_node_details</name>
      <anchor>a3</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sequence_element_handler</name>
      <anchor>a4</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sender_id_element_handler</name>
      <anchor>a5</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_date_element_handler</name>
      <anchor>a6</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_time_element_handler</name>
      <anchor>a7</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>event_type_element_handler</name>
      <anchor>a8</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>qms_data_element_handler</name>
      <anchor>a9</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>doc_handler</name>
      <anchor>a10</anchor>
      <arglist>(IDOM_Node *doc_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a11</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>message_p</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>test_xslt.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/test/</path>
    <filename>test__xslt_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>testLinkedList.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/Multi_Level_Data/test/</path>
    <filename>testLinkedList_8cpp</filename>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <includes id="QMS__Linked__List_8h" name="QMS_Linked_List.h" local="yes">QMS_Linked_List.h</includes>
    <includes id="QMS__Nodes_8h" name="QMS_Nodes.h" local="yes">QMS_Nodes.h</includes>
    <includes id="QMS__Linked__List__Iterators_8h" name="QMS_Linked_List_Iterators.h" local="yes">QMS_Linked_List_Iterators.h</includes>
    <member kind="typedef">
      <type>QMS_Sub_Type_Element&lt; string, string, ACE_RW_Mutex &gt;</type>
      <name>my_sub_Type</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>my_compare</name>
      <anchor>a3</anchor>
      <arglist>(const string &amp;A, const string &amp;B)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Node&lt; string, string, ACE_RW_Mutex &gt; *</type>
      <name>find</name>
      <anchor>a4</anchor>
      <arglist>(QMS_Linked_List&lt; string, string, ACE_RW_Mutex &gt; *list_p, string &amp;key, int(*cmp_p)(const string &amp;, const string &amp;))</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchor>a5</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>words</name>
      <anchor>a2</anchor>
      <arglist>[26][3]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Trader.idl</name>
    <path>/home/srivasta/Work/devel/QMS/Core/Trader/</path>
    <filename>Trader_8idl</filename>
    <includes id="Command_8idl" name="Command.idl" local="yes">Command.idl</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <namespace>STDC::QMS::Citizen</namespace>
  </compound>
  <compound kind="file">
    <name>YP_Offer.cpp</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>YP__Offer_8cpp</filename>
    <includes id="YP__Offer_8h" name="YP_Offer.h" local="yes">YP_Offer.h</includes>
    <includes id="Debug_8h" name="Debug.h" local="yes">Debug.h</includes>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>YP_Offer.h</name>
    <path>/home/srivasta/Work/devel/QMS/Utilities/</path>
    <filename>YP__Offer_8h</filename>
    <includes id="CORBA__Handles_8h" name="CORBA_Handles.h" local="yes">CORBA_Handles.h</includes>
    <namespace>STDC</namespace>
    <namespace>STDC::QMS</namespace>
    <member kind="define">
      <type>#define</type>
      <name>YP_SERVICE_TYPE</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>bandwidthData</name>
    <filename>structbandwidthData.html</filename>
    <member kind="variable">
      <type>linkData</type>
      <name>linkdata</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>client_error_handler</name>
    <filename>classclient__error__handler.html</filename>
    <member kind="function">
      <type></type>
      <name>client_error_handler</name>
      <anchor>a0</anchor>
      <arglist>(Test_Client *client_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a1</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>client_error_handler</name>
      <anchor>a2</anchor>
      <arglist>(Test_Client *client_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a3</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>client_error_handler</name>
      <anchor>a4</anchor>
      <arglist>(Test_Client *client_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a5</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>client_error_handler</name>
      <anchor>a6</anchor>
      <arglist>(Test_Receiver *client_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a7</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~client_error_handler</name>
      <anchor>c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~client_error_handler</name>
      <anchor>c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~client_error_handler</name>
      <anchor>c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~client_error_handler</name>
      <anchor>c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Test_Client *</type>
      <name>_client_p</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Test_Client *</type>
      <name>_client_p</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Test_Client *</type>
      <name>_client_p</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Test_Receiver *</type>
      <name>_client_p</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>Shut_Up_G_Plus_Plus</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ECInfo</name>
    <filename>classECInfo.html</filename>
    <member kind="function">
      <type></type>
      <name>ECInfo</name>
      <anchor>a0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ECInfo</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ECInfo</name>
      <anchor>a2</anchor>
      <arglist>(const ECInfo &amp;)</arglist>
    </member>
    <member kind="function">
      <type>ECInfo &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const ECInfo &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchor>a4</anchor>
      <arglist>(const ECInfo &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchor>a5</anchor>
      <arglist>(ECInfo &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchor>a6</anchor>
      <arglist>(ECInfo &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchor>a7</anchor>
      <arglist>(string)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>getName</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setId</name>
      <anchor>a9</anchor>
      <arglist>(long)</arglist>
    </member>
    <member kind="function">
      <type>long</type>
      <name>getId</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>name</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long</type>
      <name>id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchor>l0</anchor>
      <arglist>(ostream &amp;, const ECInfo &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Hello_World_Request</name>
    <filename>structHello__World__Request.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>firstname</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>lastname</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>action</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>helloWorld</name>
    <filename>structhelloWorld.html</filename>
    <member kind="variable">
      <type>Hello_World_Request</type>
      <name>request</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Request</type>
      <name>request</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Request</type>
      <name>request</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Request</type>
      <name>request</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>hw_payload_data</name>
    <filename>structhw__payload__data.html</filename>
    <member kind="variable">
      <type>helloWorld</type>
      <name>data</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>IDOMTreeErrorReporter</name>
    <filename>classIDOMTreeErrorReporter.html</filename>
    <member kind="function">
      <type></type>
      <name>IDOMTreeErrorReporter</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IDOMTreeErrorReporter</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchor>a2</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchor>a3</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fatalError</name>
      <anchor>a4</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetErrors</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getSawErrors</name>
      <anchor>a6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IDOMTreeErrorReporter</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IDOMTreeErrorReporter</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchor>a9</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchor>a10</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fatalError</name>
      <anchor>a11</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetErrors</name>
      <anchor>a12</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getSawErrors</name>
      <anchor>a13</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IDOMTreeErrorReporter</name>
      <anchor>a14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IDOMTreeErrorReporter</name>
      <anchor>a15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchor>a16</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchor>a17</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fatalError</name>
      <anchor>a18</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetErrors</name>
      <anchor>a19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getSawErrors</name>
      <anchor>a20</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IDOMTreeErrorReporter</name>
      <anchor>a21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~IDOMTreeErrorReporter</name>
      <anchor>a22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warning</name>
      <anchor>a23</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error</name>
      <anchor>a24</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fatalError</name>
      <anchor>a25</anchor>
      <arglist>(const SAXParseException &amp;toCatch)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resetErrors</name>
      <anchor>a26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getSawErrors</name>
      <anchor>a27</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>fSawErrors</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>linkData</name>
    <filename>structlinkData.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>dataID</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>source</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>destination</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>latency</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>available</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>maximum</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Linked_List</name>
    <filename>classQMS__Linked__List.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <base>QMS_MLD_Containers</base>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List</name>
      <anchor>a0</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List</name>
      <anchor>a1</anchor>
      <arglist>(QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *type_p, int(*cmp_p)(const KeyType &amp;, const KeyType &amp;))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List</name>
      <anchor>a2</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QMS_Linked_List</name>
      <anchor>a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>insert_head</name>
      <anchor>a5</anchor>
      <arglist>(NodeType *new_item_p, KeyType *key_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>insert_tail</name>
      <anchor>a6</anchor>
      <arglist>(NodeType *new_item_p, KeyType *key_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>delete_head</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>delete_tail</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>delete_element</name>
      <anchor>a9</anchor>
      <arglist>(QMS_Node&lt; NodeType, KeyType, Lock &gt; *delete_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>insert_element</name>
      <anchor>a10</anchor>
      <arglist>(NodeType *new_item_p, KeyType *key_p, QMS_Node&lt; NodeType, KeyType, Lock &gt; *before_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>copy_nodes</name>
      <anchor>a11</anchor>
      <arglist>(QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; &amp;copy)</arglist>
    </member>
    <member kind="function" protection="public" virtualness="virtual">
      <type>virtual void</type>
      <name>delete_nodes</name>
      <anchor>b0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>Linked_List_Factory&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Linked_List_Factory</name>
    <filename>classLinked__List__Factory.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <base>QMS_MLD_Factory</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Linked_List_Factory</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>create_object</name>
      <anchor>a1</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Linked_List_Iterator</name>
    <filename>classQMS__Linked__List__Iterator.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <base>QMS_Linked_List_Iterator_Base</base>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List_Iterator</name>
      <anchor>a0</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List_Iterator</name>
      <anchor>a1</anchor>
      <arglist>(QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;iter)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchor>a3</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>advance_and_remove</name>
      <anchor>a4</anchor>
      <arglist>(int dont_remove)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>first</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>last</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>advance</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>advance</name>
      <anchor>a8</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator++</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt;</type>
      <name>operator++</name>
      <anchor>a10</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator--</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt;</type>
      <name>operator--</name>
      <anchor>a12</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Linked_List_Iterator_Base</name>
    <filename>classQMS__Linked__List__Iterator__Base.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchor>a0</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>next</name>
      <anchor>a1</anchor>
      <arglist>(NodeType *&amp;NodePtr)</arglist>
    </member>
    <member kind="function">
      <type>NodeType *</type>
      <name>next</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>KeyType *</type>
      <name>key</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>NodeType &amp;</type>
      <name>operator *</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>NodeType *</type>
      <name>begin</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>NodeType *</type>
      <name>end</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>done</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>get_node</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual NodeType *</type>
      <name>advance_and_remove</name>
      <anchor>a9</anchor>
      <arglist>(int dont_remove)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>first</name>
      <anchor>a10</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>last</name>
      <anchor>a11</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>advance</name>
      <anchor>a12</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>advance</name>
      <anchor>a13</anchor>
      <arglist>(int)=0</arglist>
    </member>
    <member kind="function" protection="public">
      <type></type>
      <name>QMS_Linked_List_Iterator_Base</name>
      <anchor>b0</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type></type>
      <name>QMS_Linked_List_Iterator_Base</name>
      <anchor>b1</anchor>
      <arglist>(QMS_Linked_List_Iterator_Base&lt; NodeType, KeyType, Lock &gt; &amp;iter)</arglist>
    </member>
    <member kind="function" protection="public" virtualness="virtual">
      <type>virtual</type>
      <name>~QMS_Linked_List_Iterator_Base</name>
      <anchor>b2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="public">
      <type>QMS_Linked_List_Iterator_Base&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator=</name>
      <anchor>b3</anchor>
      <arglist>(QMS_Linked_List_Iterator_Base&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>int</type>
      <name>go_head</name>
      <anchor>b4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>int</type>
      <name>go_tail</name>
      <anchor>b5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>NodeType *</type>
      <name>do_advance</name>
      <anchor>b6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>NodeType *</type>
      <name>do_retreat</name>
      <anchor>b7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>NodeType *</type>
      <name>not_done</name>
      <anchor>b8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>current_p_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>list_p_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Linked_List_Reverse_Iterator</name>
    <filename>classQMS__Linked__List__Reverse__Iterator.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <base>QMS_Linked_List_Iterator_Base</base>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List_Reverse_Iterator</name>
      <anchor>a0</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Linked_List_Reverse_Iterator</name>
      <anchor>a1</anchor>
      <arglist>(QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;iter)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchor>a3</anchor>
      <arglist>(QMS_Linked_List&lt; NodeType, KeyType, Lock &gt; *list_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual NodeType *</type>
      <name>advance_and_remove</name>
      <anchor>a4</anchor>
      <arglist>(int dont_remove)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>first</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>last</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>advance</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>advance</name>
      <anchor>a8</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator++</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt;</type>
      <name>operator++</name>
      <anchor>a10</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator--</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt;</type>
      <name>operator--</name>
      <anchor>a12</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_MLD_Containers</name>
    <filename>classQMS__MLD__Containers.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <member kind="function">
      <type></type>
      <name>QMS_MLD_Containers</name>
      <anchor>a0</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_MLD_Containers</name>
      <anchor>a1</anchor>
      <arglist>(QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *type_p, int(*cmp_p)(const KeyType &amp;, const KeyType &amp;))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QMS_MLD_Containers</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_cmp</name>
      <anchor>a3</anchor>
      <arglist>(int(*cmp_ptr)(const KeyType &amp;, const KeyType &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_type</name>
      <anchor>a4</anchor>
      <arglist>(QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *type_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_sublevel</name>
      <anchor>a5</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>a6</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const bool</type>
      <name>is_empty</name>
      <anchor>a7</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const bool</type>
      <name>is_full</name>
      <anchor>a8</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const size_t</type>
      <name>size</name>
      <anchor>a9</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copy_nodes</name>
      <anchor>a10</anchor>
      <arglist>(QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; &amp;copy)=0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_read_lock</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_write_lock</name>
      <anchor>a12</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>release_lock</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public" virtualness="pure">
      <type>virtual void</type>
      <name>delete_nodes</name>
      <anchor>b0</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>Lock</type>
      <name>lock_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>head_p_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt;</type>
      <name>sub_levels_</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>type_p_</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int(*</type>
      <name>cmp_</name>
      <anchor>n4</anchor>
      <arglist>)(const KeyType &amp;, const KeyType &amp;)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>size_t</type>
      <name>size_</name>
      <anchor>n5</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Node&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l1</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>Linked_List_Factory&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l2</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Iterator_Base&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l3</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l4</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_MLD_Factory</name>
    <filename>classQMS__MLD__Factory.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QMS_MLD_Factory</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>create_object</name>
      <anchor>a1</anchor>
      <arglist>(ACE_Double_Linked_List&lt; QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &gt; *levels_p)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Node</name>
    <filename>classQMS__Node.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <member kind="function">
      <type></type>
      <name>QMS_Node</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Node</name>
      <anchor>a1</anchor>
      <arglist>(NodeType *node_p, KeyType *key_p, QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *root_p, QMS_Node&lt; NodeType, KeyType, Lock &gt; *parent_p=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Node</name>
      <anchor>a2</anchor>
      <arglist>(const QMS_Node&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(QMS_Node&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>NodeType *</type>
      <name>get_data</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>KeyType *</type>
      <name>get_key</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>get_container</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~QMS_Node</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_read_lock</name>
      <anchor>a8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_write_lock</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>release_lock</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>Lock</type>
      <name>lock_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>NodeType *</type>
      <name>node_p_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>KeyType *</type>
      <name>key_p_</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>root_p_</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>data_container_p_</name>
      <anchor>n4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>prev_p_</name>
      <anchor>n5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>next_p_</name>
      <anchor>n6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>QMS_Node&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>parent_p_</name>
      <anchor>n7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>enum NODE_COLOUR</type>
      <name>colour_</name>
      <anchor>n8</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_MLD_Containers&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l1</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Iterator_Base&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l2</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Iterator&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l3</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>QMS_Linked_List_Reverse_Iterator&lt; NodeType, KeyType, Lock &gt;</name>
      <anchor>l4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>pack_args</name>
    <filename>structpack__args.html</filename>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Hello_World_Impl *</type>
      <name>sensor_p</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>query</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Remos_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Generic_Sensor_Impl *</type>
      <name>sensor_p</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Payload_Data</name>
    <filename>structPayload__Data.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>salutation</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>data_id</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>RemosData</type>
      <name>remos_data</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>response</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>payload_data</name>
    <filename>structpayload__data.html</filename>
    <member kind="variable">
      <type>helloWorld</type>
      <name>data</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>helloWorld</type>
      <name>data</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>helloWorld</type>
      <name>data</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>PerfMon_Payload_Data</name>
    <filename>structPerfMon__Payload__Data.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>resource_name</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>data_id</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>plotData</type>
      <name>value</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>plotData</name>
    <filename>structplotData.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>resource_value</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>probe_info</name>
    <filename>structprobe__info.html</filename>
    <member kind="variable">
      <type>unsigned long</type>
      <name>id</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>current_index</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>data_store</name>
      <anchor>m2</anchor>
      <arglist>[MAX_DATA]</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Probe_Proxy_Remos *</type>
      <name>probe_p</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>data_count</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>data_store</name>
      <anchor>m5</anchor>
      <arglist>[MAX_DATA]</arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Probe_Proxy *</type>
      <name>probe_p</name>
      <anchor>m6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>query_info</name>
    <filename>structquery__info.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>query</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>key</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::QMSMessage</type>
      <name>config</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Probe_Proxy_Remos *</type>
      <name>probe_p</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>probe_info *</type>
      <name>probe_info_p</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>STDC::QMS::Citizen::Probe_Proxy *</type>
      <name>probe_p</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>probe_info *</type>
      <name>probe_info_p</name>
      <anchor>m6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RemosData</name>
    <filename>structRemosData.html</filename>
    <member kind="variable">
      <type>vector&lt; bandwidthData * &gt;</type>
      <name>bandwidth_data</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Request</name>
    <filename>structRequest.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>firstname</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>lastname</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>action</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Sensor</name>
    <filename>classQMS__Sensor.html</filename>
    <member kind="function">
      <type></type>
      <name>QMS_Sensor</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~QMS_Sensor</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>start</name>
      <anchor>a2</anchor>
      <arglist>(string credentials, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>pause</name>
      <anchor>a3</anchor>
      <arglist>(string reason, string credentials, short &amp;ack, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>resume</name>
      <anchor>a4</anchor>
      <arglist>(string reason, string credentials, short &amp;ack, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>stop</name>
      <anchor>a5</anchor>
      <arglist>(string reason, string credentials, short &amp;ack, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update_registration</name>
      <anchor>a6</anchor>
      <arglist>(string reason, string credentials, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>reload_configuration</name>
      <anchor>a7</anchor>
      <arglist>(string reason, string credentials, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>get_security_policy</name>
      <anchor>a8</anchor>
      <arglist>(string credentials, string &amp;policy, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_security_policy</name>
      <anchor>a9</anchor>
      <arglist>(string policy, string credentials, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>get_attributes</name>
      <anchor>a10</anchor>
      <arglist>(string credentials, string &amp;attributes, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_attributes</name>
      <anchor>a11</anchor>
      <arglist>(string attributes, string credentials, CORBA::Environment &amp;ACE_TRY_ENV)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sensor_error_handler</name>
    <filename>classsensor__error__handler.html</filename>
    <member kind="function">
      <type></type>
      <name>sensor_error_handler</name>
      <anchor>a0</anchor>
      <arglist>(STDC::QMS::Citizen::Hello_World_Impl *sensor_p, STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a1</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>sensor_error_handler</name>
      <anchor>a2</anchor>
      <arglist>(STDC::QMS::Citizen::Remos_Sensor_Impl *sensor_p, STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a3</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>sensor_error_handler</name>
      <anchor>a4</anchor>
      <arglist>(STDC::QMS::Citizen::Generic_Sensor_Impl *sensor_p, STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>handle_signal</name>
      <anchor>a5</anchor>
      <arglist>(int signum, siginfo_t *info_p, ucontext_t *context_p)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~sensor_error_handler</name>
      <anchor>c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~sensor_error_handler</name>
      <anchor>c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~sensor_error_handler</name>
      <anchor>c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::Hello_World_Impl *</type>
      <name>sensor_p_</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::Remos_Sensor_Impl *</type>
      <name>sensor_p_</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::Generic_Sensor_Impl *</type>
      <name>sensor_p_</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>Shut_Up_G_Plus_Plus</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Sub_Type_Element</name>
    <filename>classQMS__Sub__Type__Element.html</filename>
    <templarg>NodeType</templarg>
    <templarg>KeyType</templarg>
    <templarg>Lock</templarg>
    <member kind="function">
      <type></type>
      <name>QMS_Sub_Type_Element</name>
      <anchor>a0</anchor>
      <arglist>(QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *type_p=0, int(*cmp_func)(const KeyType &amp;, const KeyType &amp;)=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>QMS_Sub_Type_Element</name>
      <anchor>a1</anchor>
      <arglist>(const QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>QMS_Sub_Type_Element &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const QMS_Sub_Type_Element &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchor>a3</anchor>
      <arglist>(QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *type_p, int(*cmp_func)(const KeyType &amp;, const KeyType &amp;))</arglist>
    </member>
    <member kind="function">
      <type>QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>get_type</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int(*</type>
      <name>get_cmp</name>
      <anchor>a5</anchor>
      <arglist>(void))(const KeyType &amp;, const KeyType &amp;)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>prev_</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QMS_Sub_Type_Element&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>next_</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QMS_MLD_Factory&lt; NodeType, KeyType, Lock &gt; *</type>
      <name>type_p_</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int(*</type>
      <name>cmp_</name>
      <anchor>o3</anchor>
      <arglist>)(const KeyType &amp;, const KeyType &amp;)</arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>ACE_Double_Linked_List&lt; QMS_Sub_Type_Element &gt;</name>
      <anchor>l0</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>ACE_Double_Linked_List_Iterator_Base&lt; QMS_Sub_Type_Element &gt;</name>
      <anchor>l1</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>ACE_Double_Linked_List_Iterator&lt; QMS_Sub_Type_Element &gt;</name>
      <anchor>l2</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>ACE_Double_Linked_List_Reverse_Iterator&lt; QMS_Sub_Type_Element &gt;</name>
      <anchor>l3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TAO_STDC_QMS_Citizen_Generic_Sensor_Perfect_Hash_OpTable</name>
    <filename>classTAO__STDC__QMS__Citizen__Generic__Sensor__Perfect__Hash__OpTable.html</filename>
    <member kind="function">
      <type>const TAO_operation_db_entry *</type>
      <name>lookup</name>
      <anchor>a0</anchor>
      <arglist>(const char *str, unsigned int len)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned int</type>
      <name>hash</name>
      <anchor>c0</anchor>
      <arglist>(const char *str, unsigned int len)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Test_Client</name>
    <filename>classTest__Client.html</filename>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a1</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Test_Client</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a6</anchor>
      <arglist>(STDC::QMS::CORBA_Handles &amp;handles, char *identity_p, char *category_name_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a9</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client &amp;</type>
      <name>operator=</name>
      <anchor>a10</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a12</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Test_Client</name>
      <anchor>a13</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a14</anchor>
      <arglist>(STDC::QMS::CORBA_Handles &amp;handles, char *identity_p, char *filename_p, char *category_name_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a15</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a16</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Client</name>
      <anchor>a17</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client &amp;</type>
      <name>operator=</name>
      <anchor>a18</anchor>
      <arglist>(const Test_Client &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Test_Client *</type>
      <name>operator &amp;</name>
      <anchor>a20</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Test_Client</name>
      <anchor>a21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a22</anchor>
      <arglist>(STDC::QMS::CORBA_Handles &amp;handles, char *identity_p, char *category_name_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>callback</name>
      <anchor>d0</anchor>
      <arglist>(const string &amp;response, void *arg_p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_messages</name>
      <anchor>d1</anchor>
      <arglist>(void *arg_p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>callback</name>
      <anchor>d2</anchor>
      <arglist>(const string &amp;response, void *arg_p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_messages</name>
      <anchor>d3</anchor>
      <arglist>(void *arg_p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>callback</name>
      <anchor>d4</anchor>
      <arglist>(const string &amp;response, void *arg_p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>send_messages</name>
      <anchor>d5</anchor>
      <arglist>(void *arg_p)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>check_message</name>
      <anchor>c0</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c3</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>c4</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_offers</name>
      <anchor>c5</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_offers</name>
      <anchor>c6</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>choose_offer</name>
      <anchor>c7</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_selected_properties</name>
      <anchor>c8</anchor>
      <arglist>(const CosTrading::PropertySeq &amp;selected_properties, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>extract_name_id</name>
      <anchor>c9</anchor>
      <arglist>(string &amp;data, RtecEventComm::EventType &amp;id, string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>connect_EC</name>
      <anchor>c10</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>create_message</name>
      <anchor>c11</anchor>
      <arglist>(long version, string &amp;data, const char *action)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>check_message</name>
      <anchor>c12</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c15</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>c16</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_offers</name>
      <anchor>c17</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_offers</name>
      <anchor>c18</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>choose_offer</name>
      <anchor>c19</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_selected_properties</name>
      <anchor>c20</anchor>
      <arglist>(const CosTrading::PropertySeq &amp;selected_properties, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>extract_name_id</name>
      <anchor>c21</anchor>
      <arglist>(string &amp;data, RtecEventComm::EventType &amp;id, string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>connect_EC</name>
      <anchor>c22</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>create_message</name>
      <anchor>c23</anchor>
      <arglist>(long version, string &amp;data, const char *action)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>check_message</name>
      <anchor>c24</anchor>
      <arglist>(string &amp;message)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c25</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c27</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>c28</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_offers</name>
      <anchor>c29</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_offers</name>
      <anchor>c30</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>choose_offer</name>
      <anchor>c31</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_selected_properties</name>
      <anchor>c32</anchor>
      <arglist>(const CosTrading::PropertySeq &amp;selected_properties, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>extract_name_id</name>
      <anchor>c33</anchor>
      <arglist>(string &amp;data, RtecEventComm::EventType &amp;id, string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>connect_EC</name>
      <anchor>c34</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>create_message</name>
      <anchor>c35</anchor>
      <arglist>(long version, string &amp;data, const char *action)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>_identity_p</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventSourceID</type>
      <name>_supplier_id</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles</type>
      <name>_handles</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_parser_initialized</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_category_name</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_probe_schema_uri</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_qms_schema_uri</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_request_channel</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_request_event_type</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_data_channel</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_data_event_type</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Push_Consumer</type>
      <name>_consumer</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Push_Supplier</type>
      <name>_supplier</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_host_addr</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>_identity_p</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>list&lt; string &gt;</type>
      <name>hosts</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>_identity_p</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Test_Receiver</name>
    <filename>classTest__Receiver.html</filename>
    <member kind="function">
      <type></type>
      <name>Test_Receiver</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Test_Receiver</name>
      <anchor>a1</anchor>
      <arglist>(const Test_Receiver &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Receiver &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Test_Receiver &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Test_Receiver *</type>
      <name>operator &amp;</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Test_Receiver *</type>
      <name>operator &amp;</name>
      <anchor>a4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Test_Receiver</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a6</anchor>
      <arglist>(STDC::QMS::CORBA_Handles &amp;handles, char *identity_p, char *category_name_p, char *limiter_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>void</type>
      <name>callback</name>
      <anchor>d0</anchor>
      <arglist>(const string &amp;response, void *arg_p)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_offers</name>
      <anchor>c0</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_offers</name>
      <anchor>c1</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>choose_offer</name>
      <anchor>c2</anchor>
      <arglist>(CosTrading::OfferSeq *offer_seq_ptr, CosTrading::OfferIterator_var iterator, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>handle_selected_properties</name>
      <anchor>c3</anchor>
      <arglist>(const CosTrading::PropertySeq &amp;selected_properties, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>extract_name_id</name>
      <anchor>c4</anchor>
      <arglist>(string &amp;data, RtecEventComm::EventType &amp;id, string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>connect_EC</name>
      <anchor>c5</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>_identity_p</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles</type>
      <name>_handles</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_category_name</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_data_channel</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_data_event_type</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Push_Consumer</type>
      <name>_consumer</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_host_addr</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>_limiter_p</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>QMS_Trader_ECInfo_Impl</name>
    <filename>classQMS__Trader__ECInfo__Impl.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cerr</name>
    <filename>classstd_1_1cerr.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cin</name>
    <filename>classstd_1_1cin.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::cout</name>
    <filename>classstd_1_1cout.html</filename>
  </compound>
  <compound kind="class">
    <name>std::endl</name>
    <filename>classstd_1_1endl.html</filename>
  </compound>
  <compound kind="class">
    <name>std::endl</name>
    <filename>classstd_1_1endl.html</filename>
  </compound>
  <compound kind="class">
    <name>std::ifstream</name>
    <filename>classstd_1_1ifstream.html</filename>
  </compound>
  <compound kind="class">
    <name>std::invalid_argument</name>
    <filename>classstd_1_1invalid__argument.html</filename>
  </compound>
  <compound kind="class">
    <name>std::invalid_argument</name>
    <filename>classstd_1_1invalid__argument.html</filename>
  </compound>
  <compound kind="class">
    <name>std::invalid_argument</name>
    <filename>classstd_1_1invalid__argument.html</filename>
  </compound>
  <compound kind="class">
    <name>std::invalid_argument</name>
    <filename>classstd_1_1invalid__argument.html</filename>
  </compound>
  <compound kind="class">
    <name>std::invalid_argument</name>
    <filename>classstd_1_1invalid__argument.html</filename>
  </compound>
  <compound kind="class">
    <name>std::ios</name>
    <filename>classstd_1_1ios.html</filename>
  </compound>
  <compound kind="class">
    <name>std::ostream</name>
    <filename>classstd_1_1ostream.html</filename>
  </compound>
  <compound kind="class">
    <name>std::resetiosflags</name>
    <filename>classstd_1_1resetiosflags.html</filename>
  </compound>
  <compound kind="class">
    <name>std::setiosflags</name>
    <filename>classstd_1_1setiosflags.html</filename>
  </compound>
  <compound kind="class">
    <name>std::setprecision</name>
    <filename>classstd_1_1setprecision.html</filename>
  </compound>
  <compound kind="class">
    <name>std::setw</name>
    <filename>classstd_1_1setw.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="class">
    <name>std::string</name>
    <filename>classstd_1_1string.html</filename>
  </compound>
  <compound kind="page">
    <name>README</name>
    <title>README.first</title>
    <filename>README</filename>
  </compound>
  <compound kind="page">
    <name>README.Trader</name>
    <title>The QMS Trader</title>
    <filename>README.Trader</filename>
    <docanchor>QMS_Trader_ECInfoFunction</docanchor>
    <docanchor>Running_QMS_Trader_ECInfo</docanchor>
    <docanchor>QMS_Trader_ECInfo_Overview</docanchor>
    <docanchor>QMS_Trader_ECInfo</docanchor>
  </compound>
  <compound kind="page">
    <name>README.background</name>
    <title>Understanding QMS</title>
    <filename>README.background</filename>
  </compound>
  <compound kind="page">
    <name>QMSTerminology</name>
    <title>Terminology in QMS</title>
    <filename>QMSTerminology</filename>
  </compound>
  <compound kind="page">
    <name>QMSEventChannels</name>
    <title>Understanding CORBA Event Channels in QMS</title>
    <filename>QMSEventChannels</filename>
  </compound>
  <compound kind="page">
    <name>QMSUniqueName</name>
    <title>Understanding QMSUniqueName</title>
    <filename>QMSUniqueName</filename>
  </compound>
  <compound kind="page">
    <name>QMSMessage</name>
    <title>Understanding QMS Messages</title>
    <filename>QMSMessage</filename>
  </compound>
  <compound kind="page">
    <name>QMSSensors</name>
    <title>Understanding QMS Sensors</title>
    <filename>QMSSensors</filename>
  </compound>
  <compound kind="page">
    <name>QMSProbes</name>
    <title>Understanding QMS Probes</title>
    <filename>QMSProbes</filename>
  </compound>
  <compound kind="page">
    <name>QMSTraderOverview</name>
    <title>Understanding QMS Trader</title>
    <filename>QMSTraderOverview</filename>
  </compound>
  <compound kind="page">
    <name>QMSClients</name>
    <title>Understanding QMS Clients</title>
    <filename>QMSClients</filename>
  </compound>
  <compound kind="page">
    <name>README.install</name>
    <title>Installing QMS</title>
    <filename>README.install</filename>
  </compound>
  <compound kind="page">
    <name>SystemRequirements</name>
    <title>System Requirements</title>
    <filename>SystemRequirements</filename>
    <docanchor>RequiredSW</docanchor>
    <docanchor>RequiredOS</docanchor>
  </compound>
  <compound kind="page">
    <name>LinuxInstall</name>
    <title>QMS on Linux</title>
    <filename>LinuxInstall</filename>
    <docanchor>LinuxBuild</docanchor>
    <docanchor>LinuxMakeIntroduction</docanchor>
  </compound>
  <compound kind="page">
    <name>WindowsInstall</name>
    <title>QMS on Windows NT</title>
    <filename>WindowsInstall</filename>
    <docanchor>WindowsMakeIntroduction</docanchor>
    <docanchor>WindowsBuild</docanchor>
  </compound>
  <compound kind="page">
    <name>LinuxBuildDetails</name>
    <title>The QMS Build System on Linux</title>
    <filename>LinuxBuildDetails</filename>
    <docanchor>MakefileSynopsis</docanchor>
    <docanchor>MakefileNotes</docanchor>
    <docanchor>MakefileCustomization</docanchor>
    <docanchor>LinuxInstallDetails</docanchor>
    <docanchor>MakefileVariables</docanchor>
    <docanchor>MakefileExample</docanchor>
  </compound>
  <compound kind="page">
    <name>QMSTeam</name>
    <title>The S/TDC QMS Team</title>
    <filename>QMSTeam</filename>
  </compound>
  <compound kind="page">
    <name>README.run</name>
    <title>Running QMS</title>
    <filename>README.run</filename>
  </compound>
  <compound kind="page">
    <name>README.misc</name>
    <title>Building your own QMS citizens</title>
    <filename>README.misc</filename>
  </compound>
  <compound kind="page">
    <name>UnderstandingSchemas</name>
    <title>Understanding XML in QMS</title>
    <filename>UnderstandingSchemas</filename>
  </compound>
  <compound kind="page">
    <name>UnderstandingXSL</name>
    <title>Understanding XML Stylesheets (XSL) in QMS</title>
    <filename>UnderstandingXSL</filename>
  </compound>
  <compound kind="page">
    <name>BuildSensor</name>
    <title>Building your own QMS Sensor</title>
    <filename>BuildSensor</filename>
  </compound>
  <compound kind="page">
    <name>BuildClient</name>
    <title>Building your own QMS Client</title>
    <filename>BuildClient</filename>
  </compound>
  <compound kind="page">
    <name>BuildPlugin</name>
    <title>Building your own QMS Plugins</title>
    <filename>BuildPlugin</filename>
  </compound>
  <compound kind="page">
    <name>README.FAQ</name>
    <title>Frequently Asked Questions</title>
    <filename>README.FAQ</filename>
  </compound>
  <compound kind="page">
    <name>README.hello_world</name>
    <title>An Example Sensor - Hello World</title>
    <filename>README.hello_world</filename>
    <docanchor>Running_Hello_World</docanchor>
    <docanchor>HelloWorldFunction</docanchor>
    <docanchor>HelloWorldOverview</docanchor>
  </compound>
  <compound kind="group">
    <name>QMS</name>
    <title>QoS Metric Services</title>
    <filename>group__QMS.html</filename>
    <file>Instrumentation.h</file>
    <subgroup>Services</subgroup>
    <subgroup>Facilities</subgroup>
    <subgroup>Utilities</subgroup>
    <subgroup>Contrib</subgroup>
    <subgroup>Instrumentation</subgroup>
  </compound>
  <compound kind="group">
    <name>Services</name>
    <title>The Core services provided by QMS</title>
    <filename>group__Services.html</filename>
    <subgroup>COMMAND</subgroup>
    <subgroup>Trader</subgroup>
  </compound>
  <compound kind="group">
    <name>COMMAND</name>
    <title>The QMS Command and control Interface and adapter</title>
    <filename>group__COMMAND.html</filename>
    <file>Command.idl</file>
    <file>Control.idl</file>
    <namespace>STDC</namespace>
  </compound>
  <compound kind="group">
    <name>Facilities</name>
    <title>Plug ins and add-on facilities provided with QMS</title>
    <filename>group__Facilities.html</filename>
    <subgroup>Visualizer</subgroup>
    <subgroup>Logger</subgroup>
  </compound>
  <compound kind="group">
    <name>Visualizer</name>
    <title>The QMS Data visualization plugin</title>
    <filename>group__Visualizer.html</filename>
  </compound>
  <compound kind="group">
    <name>Utilities</name>
    <title>Utilities - Miscellaneous software utilities</title>
    <filename>group__Utilities.html</filename>
    <file>CORBA_Handles.cpp</file>
    <file>CORBA_Handles.h</file>
    <file>Debug.h</file>
    <file>instantiate.cpp</file>
    <file>Parse_Duration.cpp</file>
    <file>Parse_Duration.h</file>
    <file>Parse_XML.cpp</file>
    <file>Parse_XML.h</file>
    <file>YP_Offer.cpp</file>
    <file>YP_Offer.h</file>
    <subgroup>TAOEC</subgroup>
    <subgroup>Testing</subgroup>
    <subgroup>Benchmarks</subgroup>
    <subgroup>Backend</subgroup>
    <subgroup>MLD</subgroup>
    <class kind="class">STDC::QMS::CORBA_Handles</class>
    <class kind="class">IDOMTreeErrorReporter</class>
    <class kind="class">STDC::QMS::Parse_XML</class>
  </compound>
  <compound kind="group">
    <name>TAOEC</name>
    <title>The TAO Event Channel Interface and Adapter</title>
    <filename>group__TAOEC.html</filename>
    <file>EC_Adapter.cpp</file>
    <file>EC_Adapter.h</file>
    <file>Push_Consumer.cpp</file>
    <file>Push_Consumer.cpp</file>
    <file>Push_Consumer.h</file>
    <file>Push_Supplier.cpp</file>
    <file>Push_Supplier.h</file>
    <class kind="class">STDC::QMS::EC_Adapter</class>
    <class kind="class">STDC::QMS::Push_Consumer</class>
    <class kind="class">STDC::QMS::Push_Supplier</class>
  </compound>
  <compound kind="group">
    <name>Contrib</name>
    <title>Third party software integrated with QMS</title>
    <filename>group__Contrib.html</filename>
  </compound>
  <compound kind="group">
    <name>Testing</name>
    <title>Testing - Non production code used for testing</title>
    <filename>group__Testing.html</filename>
    <file>instantiate.cpp</file>
    <file>testLinkedList.cpp</file>
  </compound>
  <compound kind="group">
    <name>Benchmarks</name>
    <title>Benchmarks - Non production code for performance measurement</title>
    <filename>group__Benchmarks.html</filename>
  </compound>
  <compound kind="group">
    <name>Trader</name>
    <title>QMS Trader - Underpinnings of the QMS publish/subscribe services</title>
    <filename>group__Trader.html</filename>
    <file>ECInfo.cpp</file>
    <file>ECInfo.h</file>
    <file>ListOffers.cpp</file>
    <file>ListOffers.h</file>
    <file>QMS_Trader_ECInfo.cpp</file>
    <file>QMS_Trader_ECInfo.h</file>
    <file>QMS_Trader_ECInfo_Impl.cpp</file>
    <file>QMS_Trader_ECInfo_Impl.h</file>
    <file>Trader.idl</file>
    <class kind="class">QMS_Trader_ECInfo_Impl</class>
  </compound>
  <compound kind="group">
    <name>Instrumentation</name>
    <title>Instrumentation - QoS intrumentation that uses QMS</title>
    <filename>group__Instrumentation.html</filename>
    <subgroup>Probes</subgroup>
    <subgroup>Sensors</subgroup>
  </compound>
  <compound kind="group">
    <name>Probes</name>
    <title>QMS Probes - Simple QoS metric probes deployed by the sensors</title>
    <filename>group__Probes.html</filename>
    <file>Continuous.h</file>
    <file>Generic_OneShot_Probe.cpp</file>
    <file>Generic_OneShot_Probe.h</file>
    <file>get_data_O.cpp</file>
    <file>Linux_Perf_Mon_Probe.cpp</file>
    <file>OneShot.h</file>
    <file>Probe.h</file>
    <subgroup>Continuous</subgroup>
    <subgroup>OneShot</subgroup>
    <member kind="function">
      <type>int</type>
      <name>get_data</name>
      <anchor>a1</anchor>
      <arglist>(char *counter, char *probe_output)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Continuous</name>
    <title>Continuous Probes</title>
    <filename>group__Continuous.html</filename>
    <file>Linux_Perf_Mon_Probe.h</file>
    <subgroup>DLLInterceptProbe</subgroup>
    <subgroup>NTPerfMonProbe</subgroup>
    <subgroup>RemosProbes</subgroup>
    <subgroup>GenericProbe</subgroup>
  </compound>
  <compound kind="group">
    <name>DLLInterceptProbe</name>
    <title>DLL Intercept Probe - probes for transparent insrumentation</title>
    <filename>group__DLLInterceptProbe.html</filename>
    <file>Generic_Wrapper_Probe.cpp</file>
    <file>Generic_Wrapper_Probe.h</file>
  </compound>
  <compound kind="group">
    <name>NTPerfMonProbe</name>
    <title>Windows NT Performance Monitor Probes</title>
    <filename>group__NTPerfMonProbe.html</filename>
    <file>NT_Perf_Mon_getdata.cpp</file>
    <file>NT_Perf_Mon_getdata.h</file>
    <file>NT_Perf_Mon_Probe.cpp</file>
    <file>NT_Perf_Mon_Probe.h</file>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>RemosProbes</name>
    <title>Remos Probes - probes for network QoS metrics</title>
    <filename>group__RemosProbes.html</filename>
    <file>get_data_flow.cpp</file>
    <file>get_data_flow.h</file>
    <file>get_data_graph.cpp</file>
    <file>get_data_graph.h</file>
    <file>Remos_Flow_Probe.cpp</file>
    <file>Remos_Flow_Probe.h</file>
    <file>Remos_Graph_Probe.cpp</file>
    <file>Remos_Graph_Probe.h</file>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>GenericProbe</name>
    <title>Generic Probes - simple probe to test Generic Sensor</title>
    <filename>group__GenericProbe.html</filename>
    <file>Generic_Continuous_Probe.cpp</file>
    <file>Generic_Continuous_Probe.h</file>
    <file>get_data_GCP.cpp</file>
    <file>get_data_GCP.h</file>
    <member kind="function">
      <type>char *</type>
      <name>get_data</name>
      <anchor>a1</anchor>
      <arglist>(void *args)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>OneShot</name>
    <title>OneShot Probes</title>
    <filename>group__OneShot.html</filename>
    <subgroup>Remos</subgroup>
  </compound>
  <compound kind="group">
    <name>Remos</name>
    <title>A Probe that delivers Remos flow data</title>
    <filename>group__Remos.html</filename>
    <file>get_data_O.h</file>
    <file>Remos_Flow_Probe_Oneshot.cpp</file>
    <file>Remos_Flow_Probe_Oneshot.h</file>
    <file>Remos_Graph_Probe_Oneshot.cpp</file>
    <file>Remos_Graph_Probe_Oneshot.h</file>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>version</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Sensors</name>
    <title>QMS Sensors - QoS metrics gatherers and data supplier</title>
    <filename>group__Sensors.html</filename>
    <file>QMS_Sensor.h</file>
    <file>Sensor.h</file>
    <subgroup>HelloWorld</subgroup>
    <subgroup>RemosSensor</subgroup>
    <subgroup>GenericSensor</subgroup>
    <class kind="class">QMS_Sensor</class>
  </compound>
  <compound kind="group">
    <name>HelloWorld</name>
    <title>Hello-World sensor - an example sensor implementation</title>
    <filename>group__HelloWorld.html</filename>
    <file>CallBack_HW.cpp</file>
    <file>Client_HW.cpp</file>
    <file>Client_HW.h</file>
    <file>Generic_Sensor.idl</file>
    <file>hello_world.cpp</file>
    <file>Hello_World.idl</file>
    <file>hello_world_client.cpp</file>
    <file>Hello_World_Impl.cpp</file>
    <file>Hello_World_Impl.h</file>
    <file>List_Data_HW.h</file>
    <file>Message_Format_HW.h</file>
    <file>Meta_Data_HW.cpp</file>
    <file>Meta_Data_HW.h</file>
    <file>Payload_HW.cpp</file>
    <file>Payload_HW.h</file>
  </compound>
  <compound kind="group">
    <name>RemosSensor</name>
    <title>Remos Sensor - a hybrid sensor implementation</title>
    <filename>group__RemosSensor.html</filename>
    <file>Benchmark_Remos.cpp</file>
    <file>CallBack_Remos.cpp</file>
    <file>Client_Remos.cpp</file>
    <file>Client_Remos.h</file>
    <file>Continuous_Pipe_Proxy_Remos.cpp</file>
    <file>Continuous_Pipe_Proxy_Remos.h</file>
    <file>List_Data_Remos.h</file>
    <file>Message_Format_Remos.h</file>
    <file>Meta_Data_Remos.cpp</file>
    <file>Meta_Data_Remos.h</file>
    <file>One_Shot_Pipe_Proxy_Remos.cpp</file>
    <file>One_Shot_Pipe_Proxy_Remos.h</file>
    <file>Payload_Remos.cpp</file>
    <file>Payload_Remos.h</file>
    <file>Pipe_Proxy_Remos.cpp</file>
    <file>Pipe_Proxy_Remos.h</file>
    <file>Probe_Proxy_Remos.h</file>
    <file>remos_client.cpp</file>
    <file>remos_sensor.cpp</file>
    <file>Remos_Sensor.idl</file>
    <file>Remos_Sensor_Impl.cpp</file>
    <file>Remos_Sensor_Impl.h</file>
    <file>test_exec.cpp</file>
    <file>test_probe.cpp</file>
    <class kind="class">STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos</class>
    <class kind="class">STDC::QMS::Citizen::One_Shot_Pipe_Proxy_Remos</class>
    <class kind="class">STDC::QMS::Citizen::Pipe_Proxy_Remos</class>
    <class kind="class">STDC::QMS::Citizen::Probe_Proxy_Remos</class>
  </compound>
  <compound kind="group">
    <name>GenericSensor</name>
    <title>Generic sensor - an example sensor implementation with external probes</title>
    <filename>group__GenericSensor.html</filename>
    <file>Benchmark_Client.cpp</file>
    <file>CallBack.cpp</file>
    <file>Capability.cpp</file>
    <file>Client.cpp</file>
    <file>Client.h</file>
    <file>Continuous_Pipe_Proxy.cpp</file>
    <file>Continuous_Pipe_Proxy.h</file>
    <file>generic_client.cpp</file>
    <file>generic_sensor.cpp</file>
    <file>Generic_Sensor.idl</file>
    <file>Generic_Sensor_Impl.cpp</file>
    <file>Generic_Sensor_Impl.h</file>
    <file>List_Data.h</file>
    <file>Message_Format.h</file>
    <file>Meta_Data.cpp</file>
    <file>Meta_Data.h</file>
    <file>One_Shot_Pipe_Proxy.cpp</file>
    <file>One_Shot_Pipe_Proxy.h</file>
    <file>Payload.cpp</file>
    <file>Payload.h</file>
    <file>Pipe_Proxy.cpp</file>
    <file>Pipe_Proxy.h</file>
    <file>Probe_Proxy.h</file>
    <file>Receiver.cpp</file>
    <file>Receiver.h</file>
    <file>receiver_client.cpp</file>
    <file>test_Capability.cpp</file>
    <file>test_list_data.cpp</file>
    <file>test_meta_data.cpp</file>
    <file>test_trading.cpp</file>
    <file>test_XML.cpp</file>
    <class kind="class">STDC::QMS::Citizen::Continuous_Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::One_Shot_Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::Probe_Proxy</class>
  </compound>
  <compound kind="group">
    <name>Logger</name>
    <title>QMS Logger -- flexible data recorder and logger</title>
    <filename>group__Logger.html</filename>
    <file>QMS_Logger.h</file>
    <file>Simple_Logger.cpp</file>
    <file>Simple_Logger.h</file>
  </compound>
  <compound kind="group">
    <name>Backend</name>
    <title>QMS BE - A generic interface to persistent local storage</title>
    <filename>group__Backend.html</filename>
    <file>Backend.h</file>
    <subgroup>BE_Retrieve</subgroup>
    <subgroup>BE_Store</subgroup>
  </compound>
  <compound kind="group">
    <name>BE_Retrieve</name>
    <title>QMS BE Retrieve - Modules related to querying and retrieving data from local storage</title>
    <filename>group__BE__Retrieve.html</filename>
  </compound>
  <compound kind="group">
    <name>BE_Store</name>
    <title>QMS BE Store - Modules related to storing data to local storage</title>
    <filename>group__BE__Store.html</filename>
  </compound>
  <compound kind="group">
    <name>MLD</name>
    <title>Multi level data structures</title>
    <filename>group__MLD.html</filename>
    <file>QMS_Linked_List.cpp</file>
    <file>QMS_Linked_List.h</file>
    <file>QMS_Linked_List_Iterators.cpp</file>
    <file>QMS_Linked_List_Iterators.h</file>
    <file>QMS_MLD.h</file>
    <file>QMS_MLD_Containers.cpp</file>
    <file>QMS_MLD_Containers.h</file>
    <file>QMS_MLD_Factory.h</file>
    <file>QMS_Nodes.cpp</file>
    <file>QMS_Nodes.h</file>
    <file>QMS_Type_list.h</file>
    <file>testLinkedList.cpp</file>
    <class kind="class">Linked_List_Factory</class>
    <class kind="class">QMS_MLD_Factory</class>
  </compound>
  <compound kind="namespace">
    <name>CosTrading</name>
    <filename>namespaceCosTrading.html</filename>
  </compound>
  <compound kind="namespace">
    <name>CosTradingRepos</name>
    <filename>namespaceCosTradingRepos.html</filename>
  </compound>
  <compound kind="namespace">
    <name>std</name>
    <filename>namespacestd.html</filename>
  </compound>
  <compound kind="namespace">
    <name>STDC</name>
    <filename>namespaceSTDC.html</filename>
  </compound>
  <compound kind="namespace">
    <name>STDC::QMS</name>
    <filename>namespaceSTDC_1_1QMS.html</filename>
    <class kind="class">STDC::QMS::CORBA_Handles</class>
    <class kind="class">STDC::QMS::EC_Adapter</class>
    <class kind="exception">STDC::QMS::QMS_Error</class>
    <class kind="struct">STDC::QMS::expandedVariableType</class>
    <class kind="struct">STDC::QMS::genericSensorProbeProperties</class>
    <class kind="struct">STDC::QMS::invocationType</class>
    <class kind="struct">STDC::QMS::mandatoryCorbaOfferProperties</class>
    <class kind="struct">STDC::QMS::mandatorySchemaOfferProperties</class>
    <class kind="struct">STDC::QMS::mandatoryServiceOfferProperties</class>
    <class kind="struct">STDC::QMS::minRepetitions</class>
    <class kind="class">STDC::QMS::Parse_XML</class>
    <class kind="struct">STDC::QMS::ProbeDefinitionType</class>
    <class kind="struct">STDC::QMS::pubsubIDType</class>
    <class kind="class">STDC::QMS::Push_Consumer</class>
    <class kind="class">STDC::QMS::Push_Supplier</class>
    <class kind="struct">STDC::QMS::QMSMessage</class>
    <class kind="struct">STDC::QMS::QoSParameters</class>
    <class kind="struct">STDC::QMS::sensorConfiguration</class>
    <class kind="struct">STDC::QMS::sensorServiceType</class>
    <class kind="struct">STDC::QMS::sessionType</class>
    <class kind="struct">STDC::QMS::uniqueNameType</class>
    <class kind="struct">STDC::QMS::variableType</class>
    <member kind="typedef">
      <type>string</type>
      <name>QMSSchemaURIType</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>QMSTransformURIType</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>versionType</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>ipv4AddressType</name>
      <anchor>a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>requestID</name>
      <anchor>a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>versionNumber</name>
      <anchor>a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>dataID</name>
      <anchor>a10</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>minRepeatInterval</name>
      <anchor>a11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>dataScope</name>
      <anchor>a12</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>bool</type>
      <name>forceReuseType</name>
      <anchor>a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned long</type>
      <name>msgSequenceNo</name>
      <anchor>a14</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ipv4AddressType</type>
      <name>originatingHost</name>
      <anchor>a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>pubsubIDType</type>
      <name>msgSender</name>
      <anchor>a16</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>pubsubIDType</type>
      <name>msgDestination</name>
      <anchor>a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>pubsubIDType</type>
      <name>msgReplyTo</name>
      <anchor>a18</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>string</type>
      <name>typeofProbeType</name>
      <anchor>a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector&lt; expandedVariableType &gt;</type>
      <name>optionalOfferType</name>
      <anchor>a20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector&lt; variableType &gt;</type>
      <name>instanceType</name>
      <anchor>a21</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>vector&lt; ProbeDefinitionType &gt;</type>
      <name>sensorCapability</name>
      <anchor>a22</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>timespec</type>
      <name>duration_to_tv</name>
      <anchor>a24</anchor>
      <arglist>(const char *duration_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add_YP_ServiceType</name>
      <anchor>a25</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Add_YP_SubType</name>
      <anchor>a26</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, const char *service_type, const char *interface_repository_id, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const RtecEventComm::EventType</type>
      <name>QMS_DISCONNECT</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const RtecEventComm::EventType</type>
      <name>SUPPLIER_DISCONNECT</name>
      <anchor>a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const long</type>
      <name>QMS_DEFAULT_retry_sleep_interval</name>
      <anchor>a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const int</type>
      <name>QMS_DEFAULT_number_of_retries</name>
      <anchor>a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const RtecEventComm::EventType</type>
      <name>DEFAULT_PUSH_SUPPLIER_DISCONNECT</name>
      <anchor>a23</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::CORBA_Handles</name>
    <filename>classSTDC_1_1QMS_1_1CORBA__Handles.html</filename>
    <member kind="function">
      <type></type>
      <name>CORBA_Handles</name>
      <anchor>a0</anchor>
      <arglist>(CORBA::ORB_ptr orb=0, PortableServer::POA_ptr poa=0, PortableServer::POAManager_ptr poa_manager=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CORBA_Handles</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a2</anchor>
      <arglist>(int argc, char **argv, const char *orb_name_p=&quot;QMS_API&quot;, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_child_poa</name>
      <anchor>a3</anchor>
      <arglist>(int &amp;argc, char *argv[], const char *poa_name, const char *orb_name=&quot;QMS_API&quot;, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_event_channel</name>
      <anchor>a4</anchor>
      <arglist>(const char *event_channel_name_p, RtecEventChannelAdmin::EventChannel_var &amp;event_channel, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>activate_poa_manager</name>
      <anchor>a5</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>PortableServer::ObjectId_var</type>
      <name>activate</name>
      <anchor>a6</anchor>
      <arglist>(PortableServer::Servant servant, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deactivate</name>
      <anchor>a7</anchor>
      <arglist>(const char *id, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>activate_under_child_poa</name>
      <anchor>a8</anchor>
      <arglist>(const char *object_name, PortableServer::Servant servant, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deactivate_under_child_poa</name>
      <anchor>a9</anchor>
      <arglist>(const char *id, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchor>a10</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>CORBA::ORB_var</type>
      <name>get_orb_handle</name>
      <anchor>a11</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>PortableServer::POA_var</type>
      <name>get_root_poa_handle</name>
      <anchor>a12</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>PortableServer::POA_var</type>
      <name>get_poa_handle</name>
      <anchor>a13</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>PortableServer::POAManager_var</type>
      <name>get_poa_mgr_handle</name>
      <anchor>a14</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>CosNaming::NamingContext_var</type>
      <name>get_naming_handle</name>
      <anchor>a15</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>RtecScheduler::Scheduler_var</type>
      <name>get_scheduler_handle</name>
      <anchor>a16</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>RtecEventChannelAdmin::EventChannel_var</type>
      <name>get_ec_handle</name>
      <anchor>a17</anchor>
      <arglist>(void) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fini</name>
      <anchor>a18</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchor>a19</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>CosTrading::Lookup_var</type>
      <name>get_lookup_handle</name>
      <anchor>a20</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_event_channel</name>
      <anchor>a21</anchor>
      <arglist>(const char *event_channel_name_p, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>delete_event_channel</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ORB_var</type>
      <name>_orb</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::POA_var</type>
      <name>_root_poa</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::POA_var</type>
      <name>_child_poa</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::POAManager_var</type>
      <name>_poa_manager</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosNaming::NamingContext_var</type>
      <name>_naming_context</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecScheduler::Scheduler_var</type>
      <name>_scheduler</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventChannelAdmin::EventChannel_var</type>
      <name>_event_channel</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::Lookup_var</type>
      <name>_lookup_var</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>EC_Name</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_initialized</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_poa_activated</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::EC_Adapter</name>
    <filename>classSTDC_1_1QMS_1_1EC__Adapter.html</filename>
    <member kind="function">
      <type></type>
      <name>EC_Adapter</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EC_Adapter</name>
      <anchor>a1</anchor>
      <arglist>(EC_Adapter &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~EC_Adapter</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const EC_Adapter</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(EC_Adapter &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>register_callback</name>
      <anchor>a4</anchor>
      <arglist>(void(*callback)(const string &amp;data, void *arg_p), void *arg_p=0, unsigned int which_consumer=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>send</name>
      <anchor>a5</anchor>
      <arglist>(const string &amp;data, unsigned int which_supplier=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a6</anchor>
      <arglist>(int argc, char **argv, RtecEventComm::EventSourceID my_id, RtecEventComm::EventType send_event=0, RtecEventComm::EventType get_event=0, char *event_channel_name_p=&quot;QMS_Channel&quot;, STDC::QMS::CORBA_Handles *handle_p=0, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a7</anchor>
      <arglist>(int argc, char **argv, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Push_Supplier *</type>
      <name>add_supplier</name>
      <anchor>a8</anchor>
      <arglist>(int &amp;slot_num, char *event_channel_name_p, RtecEventComm::EventSourceID my_id=0, RtecEventComm::EventType send_event=0)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Push_Consumer *</type>
      <name>add_consumer</name>
      <anchor>a9</anchor>
      <arglist>(int &amp;slot_num, char *event_channel_name_p, RtecEventComm::EventType get_event=0)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Push_Supplier *</type>
      <name>add_supplier</name>
      <anchor>a10</anchor>
      <arglist>(int &amp;slot_num)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::Push_Consumer *</type>
      <name>add_consumer</name>
      <anchor>a11</anchor>
      <arglist>(int &amp;slot_num)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>connect_supplier</name>
      <anchor>a12</anchor>
      <arglist>(unsigned int which_supplier=0, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>connect_consumer</name>
      <anchor>a13</anchor>
      <arglist>(unsigned int which_consumer=0, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>disconnect_consumer</name>
      <anchor>a15</anchor>
      <arglist>(unsigned int which_consumer=0, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>disconnect_supplier</name>
      <anchor>a16</anchor>
      <arglist>(unsigned int which_supplier=0, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>listen</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_consumer</name>
      <anchor>a18</anchor>
      <arglist>(STDC::QMS::Push_Consumer *&amp;consumer_p, unsigned int which_consumer=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_supplier</name>
      <anchor>a19</anchor>
      <arglist>(STDC::QMS::Push_Supplier *&amp;supplier_p, unsigned int which_supplier=0)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; STDC::QMS::Push_Consumer * &gt; *</type>
      <name>get_consumer_list</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; STDC::QMS::Push_Supplier * &gt; *</type>
      <name>get_supplier_list</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>get_handles</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>argc</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char **</type>
      <name>argv</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Simple_mode</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>send_event_type</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>get_event_type</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventSourceID</type>
      <name>my_id</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles</type>
      <name>handles</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>i_own_handles</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>EC_Name</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; STDC::QMS::Push_Consumer * &gt;</type>
      <name>Consumers</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Suppliers</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const RtecEventComm::EventType</type>
      <name>DEFAULT_SEND_TYPE</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const RtecEventComm::EventType</type>
      <name>DEFAULT_GET_TYPE</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const RtecEventComm::EventSourceID</type>
      <name>DEFAULT_ID</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="exception">
    <name>STDC::QMS::QMS_Error</name>
    <filename>exceptionSTDC_1_1QMS_1_1QMS__Error.html</filename>
    <member kind="variable">
      <type>short</type>
      <name>cause</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>msg</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::expandedVariableType</name>
    <filename>structSTDC_1_1QMS_1_1expandedVariableType.html</filename>
    <member kind="variable">
      <type>variableType</type>
      <name>variable</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>searchable</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>maptoProperty</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::genericSensorProbeProperties</name>
    <filename>structSTDC_1_1QMS_1_1genericSensorProbeProperties.html</filename>
    <member kind="variable">
      <type>typeofProbeType</type>
      <name>probeType</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>dataReusable</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::invocationType</name>
    <filename>structSTDC_1_1QMS_1_1invocationType.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>probeExecutable</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QMSTransformURIType</type>
      <name>probeXSLTFile</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; variableType &gt;</type>
      <name>xslParameters</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::mandatoryCorbaOfferProperties</name>
    <filename>structSTDC_1_1QMS_1_1mandatoryCorbaOfferProperties.html</filename>
    <member kind="variable">
      <type>versionType</type>
      <name>interfaceVersion</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>interfaceDescription</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::mandatorySchemaOfferProperties</name>
    <filename>structSTDC_1_1QMS_1_1mandatorySchemaOfferProperties.html</filename>
    <member kind="variable">
      <type>QMSSchemaURIType</type>
      <name>probeSchema</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>versionType</type>
      <name>schemaVersion</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::mandatoryServiceOfferProperties</name>
    <filename>structSTDC_1_1QMS_1_1mandatoryServiceOfferProperties.html</filename>
    <member kind="variable">
      <type>uniqueNameType</type>
      <name>QMSUniqueName</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::minRepetitions</name>
    <filename>structSTDC_1_1QMS_1_1minRepetitions.html</filename>
    <member kind="variable">
      <type>unsigned long</type>
      <name>count</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned long</type>
      <name>current</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Parse_XML</name>
    <filename>classSTDC_1_1QMS_1_1Parse__XML.html</filename>
    <member kind="function">
      <type></type>
      <name>Parse_XML</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Parse_XML</name>
      <anchor>a1</anchor>
      <arglist>(const Parse_XML &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Parse_XML &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Parse_XML &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Parse_XML *</type>
      <name>operator &amp;</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Parse_XML *</type>
      <name>operator &amp;</name>
      <anchor>a4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Parse_XML</name>
      <anchor>a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parse_config</name>
      <anchor>a6</anchor>
      <arglist>(char *filename_p, sensorConfiguration &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parse_capability</name>
      <anchor>a7</anchor>
      <arglist>(char *filename_p, sensorCapability &amp;results)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>parse_message</name>
      <anchor>a8</anchor>
      <arglist>(MemBufInputSource &amp;message, QMSMessage &amp;results, bool(*payload_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *payload_arg_p=0, void(*error_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *error_arg_p=0)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>char *</type>
      <name>get_child_value</name>
      <anchor>b0</anchor>
      <arglist>(IDOM_Node *node_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>session_handler</name>
      <anchor>b1</anchor>
      <arglist>(IDOM_Node *node_p, sessionType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>sensorConfiguration_handler</name>
      <anchor>b2</anchor>
      <arglist>(IDOM_Node *node_p, struct sensorConfiguration &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>sensorService_element_handler</name>
      <anchor>b3</anchor>
      <arglist>(IDOM_Node *node_p, struct sensorServiceType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>sensorCapability_handler</name>
      <anchor>b4</anchor>
      <arglist>(IDOM_Node *node_p, sensorCapability &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>QMSMessage_handler</name>
      <anchor>b5</anchor>
      <arglist>(IDOM_Node *node_p, QMSMessage &amp;result, bool(*payload_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *payload_arg_p=0, void(*error_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *error_arg_p=0)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>uniq_name_element_handler</name>
      <anchor>b6</anchor>
      <arglist>(IDOM_Node *node_p, uniqueNameType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>genericSensorProbeProperties_handler</name>
      <anchor>b7</anchor>
      <arglist>(IDOM_Node *child_p, genericSensorProbeProperties &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>mandatoryServiceOfferProperties_handler</name>
      <anchor>b8</anchor>
      <arglist>(IDOM_Node *child_p, mandatoryServiceOfferProperties &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>mandatorySchemaOfferProperties_handler</name>
      <anchor>b9</anchor>
      <arglist>(IDOM_Node *child_p, mandatorySchemaOfferProperties &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>mandatoryCorbaOfferProperties_handler</name>
      <anchor>b10</anchor>
      <arglist>(IDOM_Node *child_p, mandatoryCorbaOfferProperties &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>probe_element_handler</name>
      <anchor>b11</anchor>
      <arglist>(IDOM_Node *node_p, ProbeDefinitionType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>instance_element_handler</name>
      <anchor>b12</anchor>
      <arglist>(IDOM_Node *node_p, vector&lt; variableType &gt; &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>invoke_element_handler</name>
      <anchor>b13</anchor>
      <arglist>(IDOM_Node *node_p, invocationType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>offer_element_handler</name>
      <anchor>b14</anchor>
      <arglist>(IDOM_Node *node_p, optionalOfferType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>expanded_variable_element_handler</name>
      <anchor>b15</anchor>
      <arglist>(IDOM_Node *node_p, expandedVariableType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>variable_element_handler</name>
      <anchor>b16</anchor>
      <arglist>(IDOM_Node *node_p, variableType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>pubsubIDType_handler</name>
      <anchor>b17</anchor>
      <arglist>(IDOM_Node *node_p, pubsubIDType &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>QoSParameters_handler</name>
      <anchor>b18</anchor>
      <arglist>(IDOM_Node *node_p, QoSParameters &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>minRepetitions_handler</name>
      <anchor>b19</anchor>
      <arglist>(IDOM_Node *node_p, minRepetitions &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>cleanup</name>
      <anchor>b20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>create_parser</name>
      <anchor>b21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_file</name>
      <anchor>b22</anchor>
      <arglist>(char *filename_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_mem</name>
      <anchor>b23</anchor>
      <arglist>(MemBufInputSource &amp;message)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>config_handler</name>
      <anchor>b24</anchor>
      <arglist>(IDOM_Node *doc_p, sensorConfiguration &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>capability_handler</name>
      <anchor>b25</anchor>
      <arglist>(IDOM_Node *doc_p, sensorCapability &amp;results)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>message_handler</name>
      <anchor>b26</anchor>
      <arglist>(IDOM_Node *doc_p, QMSMessage &amp;results, bool(*payload_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *payload_arg_p=0, void(*error_handler)(IDOM_Node *doc_p, void *arg_p)=0, void *error_arg_p=0)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>IDOMParser *</type>
      <name>parser</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>IDOMTreeErrorReporter *</type>
      <name>errReporter</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::ProbeDefinitionType</name>
    <filename>structSTDC_1_1QMS_1_1ProbeDefinitionType.html</filename>
    <member kind="variable">
      <type>genericSensorProbeProperties</type>
      <name>generic_prop</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatoryServiceOfferProperties</type>
      <name>offer_prop</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatorySchemaOfferProperties</type>
      <name>schema_prop</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>optionalOfferType</type>
      <name>offer_param</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>invocationType</type>
      <name>invocation_param</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::pubsubIDType</name>
    <filename>structSTDC_1_1QMS_1_1pubsubIDType.html</filename>
    <member kind="variable">
      <type>unsigned long</type>
      <name>id</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>description</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Push_Consumer</name>
    <filename>classSTDC_1_1QMS_1_1Push__Consumer.html</filename>
    <member kind="function">
      <type></type>
      <name>Push_Consumer</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Push_Consumer</name>
      <anchor>a1</anchor>
      <arglist>(const Push_Consumer &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Push_Consumer</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Push_Consumer</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const Push_Consumer &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a4</anchor>
      <arglist>(STDC::QMS::CORBA_Handles Handle, RtecEventComm::EventType get_event_type, const char *ec_name_p=&quot;QMS_Channel&quot;, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push</name>
      <anchor>a5</anchor>
      <arglist>(const RtecEventComm::EventSet &amp;, CORBA::Environment &amp;=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchor>a6</anchor>
      <arglist>(CORBA::Environment &amp;=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchor>a7</anchor>
      <arglist>(CORBA::Environment &amp;=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_push_consumer</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Environment &amp;)</arglist>
    </member>
    <member kind="function">
      <type>RtecScheduler::handle_t &amp;</type>
      <name>get_schedule</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_schedule</name>
      <anchor>a10</anchor>
      <arglist>(RtecScheduler::handle_t &amp;schedule)</arglist>
    </member>
    <member kind="function">
      <type>ACE_ConsumerQOS_Factory &amp;</type>
      <name>get_subscription</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_subscription</name>
      <anchor>a12</anchor>
      <arglist>(ACE_ConsumerQOS_Factory &amp;qos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_callback</name>
      <anchor>a13</anchor>
      <arglist>(void(*callback)(const string &amp;data, void *arg_p), void *arg_p=0)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>get_handles</name>
      <anchor>a14</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>default_schedule</name>
      <anchor>c0</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles</type>
      <name>handles</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>connected_to_proxy</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>ec_name_p</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_get_event_type</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>EventName</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventChannelAdmin::ConsumerAdmin_var</type>
      <name>_consumer_admin</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventChannelAdmin::ProxyPushSupplier_var</type>
      <name>_supplier_proxy</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecScheduler::handle_t</type>
      <name>rt_info</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Is_Scheduled</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_ConsumerQOS_Factory</type>
      <name>qos</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Is_Subscribed</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void(*</type>
      <name>callback</name>
      <anchor>o12</anchor>
      <arglist>)(const string &amp;data, void *arg_p)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void *</type>
      <name>arg_p</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Push_Supplier</name>
    <filename>classSTDC_1_1QMS_1_1Push__Supplier.html</filename>
    <member kind="function">
      <type></type>
      <name>Push_Supplier</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Push_Supplier</name>
      <anchor>a1</anchor>
      <arglist>(Push_Supplier &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Push_Supplier</name>
      <anchor>a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Push_Supplier</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const Push_Supplier &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a4</anchor>
      <arglist>(STDC::QMS::CORBA_Handles Handles, RtecEventComm::EventType send_event_type, RtecEventComm::EventSourceID my_id, const char *ec_name_p=&quot;QMS_Channel&quot;, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>send</name>
      <anchor>a5</anchor>
      <arglist>(const string &amp;data, CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchor>a6</anchor>
      <arglist>(CORBA::Environment &amp;=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchor>a7</anchor>
      <arglist>(long etype=DEFAULT_PUSH_SUPPLIER_DISCONNECT, CORBA::Environment &amp;=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_push_supplier</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Environment &amp;)</arglist>
    </member>
    <member kind="function">
      <type>RtecScheduler::handle_t &amp;</type>
      <name>get_schedule</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_schedule</name>
      <anchor>a10</anchor>
      <arglist>(RtecScheduler::handle_t &amp;schedule)</arglist>
    </member>
    <member kind="function">
      <type>ACE_SupplierQOS_Factory &amp;</type>
      <name>get_subscription</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_subscription</name>
      <anchor>a12</anchor>
      <arglist>(ACE_SupplierQOS_Factory &amp;qos)</arglist>
    </member>
    <member kind="function">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>get_handles</name>
      <anchor>a13</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>send_disconnect_event</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>default_schedule</name>
      <anchor>c1</anchor>
      <arglist>(CORBA_Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles</type>
      <name>handles</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventChannelAdmin::SupplierAdmin_var</type>
      <name>_supplier_admin</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventChannelAdmin::ProxyPushConsumer_var</type>
      <name>_consumer_proxy</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecScheduler::handle_t</type>
      <name>rt_info</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Is_Scheduled</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_SupplierQOS_Factory</type>
      <name>qos</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Is_Subscribed</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>ec_name_p</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_send_event_type</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventType</type>
      <name>_disconnect_event_type</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RtecEventComm::EventSourceID</type>
      <name>_my_id</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>EventName</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>connected_to_proxy</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::QMSMessage</name>
    <filename>structSTDC_1_1QMS_1_1QMSMessage.html</filename>
    <member kind="variable">
      <type>msgSequenceNo</type>
      <name>sequence_no</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>msgDate</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>msgTime</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>originatingHost</type>
      <name>sender_host</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>msgSender</type>
      <name>sender</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; msgDestination &gt;</type>
      <name>destinations</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; msgReplyTo &gt;</type>
      <name>reply_tos</name>
      <anchor>m6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uniqueNameType</type>
      <name>QMSUniqueName</name>
      <anchor>m7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sessionType</type>
      <name>Session</name>
      <anchor>m8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::QoSParameters</name>
    <filename>structSTDC_1_1QMS_1_1QoSParameters.html</filename>
    <member kind="variable">
      <type>unsigned long</type>
      <name>Priority</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::sensorConfiguration</name>
    <filename>structSTDC_1_1QMS_1_1sensorConfiguration.html</filename>
    <member kind="variable">
      <type>QMSSchemaURIType</type>
      <name>QMS_Schema</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatoryServiceOfferProperties</type>
      <name>offer_prop</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatoryCorbaOfferProperties</type>
      <name>corba_prop</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>optionalOfferType</type>
      <name>offer_param</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>instanceType</type>
      <name>Instance</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; sensorServiceType &gt;</type>
      <name>sensorServices</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::sensorServiceType</name>
    <filename>structSTDC_1_1QMS_1_1sensorServiceType.html</filename>
    <member kind="variable">
      <type>genericSensorProbeProperties</type>
      <name>generic_prop</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatoryServiceOfferProperties</type>
      <name>offer_prop</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>mandatorySchemaOfferProperties</type>
      <name>schema_prop</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>optionalOfferType</type>
      <name>offer_param</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>instanceType</type>
      <name>Instance</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::sessionType</name>
    <filename>structSTDC_1_1QMS_1_1sessionType.html</filename>
    <member kind="variable">
      <type>requestID</type>
      <name>request_id</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>dataID</type>
      <name>data_id</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>versionNumber</type>
      <name>version</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>minRepetitions</type>
      <name>repititions</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>minRepeatInterval</type>
      <name>interval</name>
      <anchor>m4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>dataScope</type>
      <name>scope</name>
      <anchor>m5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>forceReuseType</type>
      <name>forceReuse</name>
      <anchor>m6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QoSParameters</type>
      <name>qos_params</name>
      <anchor>m7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::uniqueNameType</name>
    <filename>structSTDC_1_1QMS_1_1uniqueNameType.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>category</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ipv4AddressType</type>
      <name>host</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>uuid</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::variableType</name>
    <filename>structSTDC_1_1QMS_1_1variableType.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>name</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>value</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>STDC::QMS::Citizen</name>
    <filename>namespaceSTDC_1_1QMS_1_1Citizen.html</filename>
    <class kind="exception">STDC::QMS::Citizen::QMS_Citizen_Error</class>
    <class kind="interface">STDC::QMS::Citizen::Command</class>
    <class kind="struct">STDC::QMS::Citizen::Consumer_Info</class>
    <class kind="class">STDC::QMS::Citizen::Continuous_Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos</class>
    <class kind="interface">STDC::QMS::Citizen::Control</class>
    <class kind="interface">STDC::QMS::Citizen::Generic_Sensor</class>
    <class kind="class">STDC::QMS::Citizen::Generic_Sensor_Impl</class>
    <class kind="interface">STDC::QMS::Citizen::Hello_World</class>
    <class kind="class">STDC::QMS::Citizen::Hello_World_Impl</class>
    <class kind="class">STDC::QMS::Citizen::Hello_World_Meta_Data</class>
    <class kind="class">STDC::QMS::Citizen::Meta_Data</class>
    <class kind="class">STDC::QMS::Citizen::Meta_Data_Remos</class>
    <class kind="class">STDC::QMS::Citizen::One_Shot_Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::One_Shot_Pipe_Proxy_Remos</class>
    <class kind="class">STDC::QMS::Citizen::Pipe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::Pipe_Proxy_Remos</class>
    <class kind="class">STDC::QMS::Citizen::Probe_Proxy</class>
    <class kind="class">STDC::QMS::Citizen::Probe_Proxy_Remos</class>
    <class kind="struct">STDC::QMS::Citizen::Query</class>
    <class kind="interface">STDC::QMS::Citizen::Remos_Sensor</class>
    <class kind="class">STDC::QMS::Citizen::Remos_Sensor_Impl</class>
    <class kind="class">STDC::QMS::Citizen::Sensor_Data_Element</class>
    <class kind="class">STDC::QMS::Citizen::Sensor_Data_Element_HW</class>
    <class kind="class">STDC::QMS::Citizen::Sensor_Data_Element_Remos</class>
    <class kind="struct">STDC::QMS::Citizen::QMS_Trader_ECInfo::ECInfo</class>
    <class kind="interface">STDC::QMS::Citizen::QMS_Trader_ECInfo</class>
    <class kind="class">STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl</class>
    <class kind="exception">STDC::QMS::Citizen::USERERROR</class>
    <member kind="enumeration">
      <name>status_Type</name>
      <anchor>a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RUN</name>
      <anchor>a6a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PAUSE</name>
      <anchor>a6a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STOP</name>
      <anchor>a6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_Type</name>
      <anchor>a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RUN</name>
      <anchor>a6a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PAUSE</name>
      <anchor>a6a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STOP</name>
      <anchor>a6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>status_Type</name>
      <anchor>a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RUN</name>
      <anchor>a6a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PAUSE</name>
      <anchor>a6a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>STOP</name>
      <anchor>a6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>const char *</type>
      <name>delimiter</name>
      <anchor>a0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="exception">
    <name>STDC::QMS::Citizen::QMS_Citizen_Error</name>
    <filename>exceptionSTDC_1_1QMS_1_1Citizen_1_1QMS__Citizen__Error.html</filename>
    <member kind="variable">
      <type>short</type>
      <name>cause</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>msg</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::Command</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1Command.html</filename>
    <base>STDC::QMS::Citizen::Control</base>
    <member kind="function">
      <type>void</type>
      <name>disconnect_EC</name>
      <anchor>a0</anchor>
      <arglist>(in string reason, in string credentials)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reconnect_EC</name>
      <anchor>a1</anchor>
      <arglist>(in string reason, in string EC_Name, in string credentials)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>show_operating_level</name>
      <anchor>a2</anchor>
      <arglist>(out short level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_operating_level</name>
      <anchor>a3</anchor>
      <arglist>(in short level, in string credentials)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stats</name>
      <anchor>a4</anchor>
      <arglist>(in string credentials, out string stats)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ping</name>
      <anchor>a5</anchor>
      <arglist>(out short ack)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::Citizen::Consumer_Info</name>
    <filename>structSTDC_1_1QMS_1_1Citizen_1_1Consumer__Info.html</filename>
    <member kind="variable">
      <type>FILE *</type>
      <name>file_handle_p</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>ec_name</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>event_id</name>
      <anchor>m3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Continuous_Pipe_Proxy</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Continuous__Pipe__Proxy.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Pipe_Proxy</base>
    <member kind="function">
      <type></type>
      <name>Continuous_Pipe_Proxy</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Continuous_Pipe_Proxy</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Continuous_Pipe_Proxy_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Continuous__Pipe__Proxy__Remos.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Pipe_Proxy_Remos</base>
    <member kind="function">
      <type></type>
      <name>Continuous_Pipe_Proxy_Remos</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data_Remos &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Continuous_Pipe_Proxy_Remos</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::Control</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1Control.html</filename>
    <member kind="function">
      <type>void</type>
      <name>pause</name>
      <anchor>a0</anchor>
      <arglist>(in string reason, in string credentials, out short ack)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resume</name>
      <anchor>a1</anchor>
      <arglist>(in string reason, in string credentials, out short ack)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchor>a2</anchor>
      <arglist>(in string reason, in string credentials, out short ack)</arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::Generic_Sensor</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1Generic__Sensor.html</filename>
    <base>STDC::QMS::Citizen::Command</base>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Generic_Sensor_Impl</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Generic__Sensor__Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Generic_Sensor_Impl</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Generic_Sensor_Impl</name>
      <anchor>a1</anchor>
      <arglist>(const Generic_Sensor_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Generic_Sensor_Impl &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Generic_Sensor_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Generic_Sensor_Impl</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>pause</name>
      <anchor>a4</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resume</name>
      <anchor>a5</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stop</name>
      <anchor>a6</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>register_with_naming</name>
      <anchor>a7</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unregister_with_naming</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>connect_EC</name>
      <anchor>a9</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>disconnect_EC</name>
      <anchor>a10</anchor>
      <arglist>(const char *reason, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reconnect_EC</name>
      <anchor>a11</anchor>
      <arglist>(const char *reason, const char *EC_Name, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>show_operating_level</name>
      <anchor>a12</anchor>
      <arglist>(CORBA::Short_out level)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_operating_level</name>
      <anchor>a13</anchor>
      <arglist>(CORBA::Short level, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stats</name>
      <anchor>a14</anchor>
      <arglist>(const char *credentials, CORBA::String_out stats)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ping</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>start</name>
      <anchor>a16</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>init</name>
      <anchor>a17</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, string credentials, char *config_file_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>cleanup</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>update_registration</name>
      <anchor>a19</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reload_configuration</name>
      <anchor>a20</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_security_policy</name>
      <anchor>a21</anchor>
      <arglist>(string credentials, string &amp;policy)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_security_policy</name>
      <anchor>a22</anchor>
      <arglist>(string policy, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_attributes</name>
      <anchor>a23</anchor>
      <arglist>(string credentials, string &amp;attributes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_attributes</name>
      <anchor>a24</anchor>
      <arglist>(string attributes, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>add_handle</name>
      <anchor>a25</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::CORBA_Handles *</type>
      <name>get_handle</name>
      <anchor>a26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>activate</name>
      <anchor>a27</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>deactivate</name>
      <anchor>a28</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>handle_query</name>
      <anchor>a29</anchor>
      <arglist>(const string &amp;query)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_config</name>
      <anchor>b0</anchor>
      <arglist>(char *file_name_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_capability</name>
      <anchor>b1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>b2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_ECInfo</name>
      <anchor>b3</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>b4</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c1</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>builtin_probes</name>
      <anchor>c3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>external_probes</name>
      <anchor>c4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>probe_offers</name>
      <anchor>c5</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>attributes</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>policy</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::ObjectId_var</type>
      <name>oid_</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Object_var</type>
      <name>obj_</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>id_</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>level_</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Long</type>
      <name>_supplier_id</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, STDC::QMS::Citizen::Meta_Data * &gt;</type>
      <name>probes_</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::sensorConfiguration</type>
      <name>config</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_capability_file</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::sensorCapability</type>
      <name>capability</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_parser_initialized</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_activated</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_registered</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::Hello_World</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1Hello__World.html</filename>
    <base>STDC::QMS::Citizen::Command</base>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Hello_World_Impl</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Hello__World__Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Hello_World_Impl</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Hello_World_Impl</name>
      <anchor>a1</anchor>
      <arglist>(const Hello_World_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Hello_World_Impl &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Hello_World_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Hello_World_Impl</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>pause</name>
      <anchor>a4</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resume</name>
      <anchor>a5</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stop</name>
      <anchor>a6</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>register_with_naming</name>
      <anchor>a7</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unregister_with_naming</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>connect_EC</name>
      <anchor>a9</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>disconnect_EC</name>
      <anchor>a10</anchor>
      <arglist>(const char *reason, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reconnect_EC</name>
      <anchor>a11</anchor>
      <arglist>(const char *reason, const char *EC_Name, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>show_operating_level</name>
      <anchor>a12</anchor>
      <arglist>(CORBA::Short_out level)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_operating_level</name>
      <anchor>a13</anchor>
      <arglist>(CORBA::Short level, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stats</name>
      <anchor>a14</anchor>
      <arglist>(const char *credentials, CORBA::String_out stats)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ping</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>start</name>
      <anchor>a16</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>init</name>
      <anchor>a17</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, string credentials, char *config_file_p, const char *criticality_p, const char *importance_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>cleanup</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>update_registration</name>
      <anchor>a19</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reload_configuration</name>
      <anchor>a20</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_security_policy</name>
      <anchor>a21</anchor>
      <arglist>(string credentials, string &amp;policy)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_security_policy</name>
      <anchor>a22</anchor>
      <arglist>(string policy, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_attributes</name>
      <anchor>a23</anchor>
      <arglist>(string credentials, string &amp;attributes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_attributes</name>
      <anchor>a24</anchor>
      <arglist>(string attributes, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>add_handle</name>
      <anchor>a25</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::CORBA_Handles *</type>
      <name>get_handle</name>
      <anchor>a26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>activate</name>
      <anchor>a27</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>deactivate</name>
      <anchor>a28</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>handle_query</name>
      <anchor>a29</anchor>
      <arglist>(const string &amp;query)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_config</name>
      <anchor>b0</anchor>
      <arglist>(char *file_name_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>b1</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_ECInfo</name>
      <anchor>b2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>b3</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c1</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>builtin_probes</name>
      <anchor>c3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>probe_offers</name>
      <anchor>c4</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>attributes</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>policy</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::ObjectId_var</type>
      <name>oid_</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Object_var</type>
      <name>obj_</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>id_</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>level_</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Long</type>
      <name>_supplier_id</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, STDC::QMS::Citizen::Hello_World_Meta_Data * &gt;</type>
      <name>probes_</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::sensorConfiguration</type>
      <name>config</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>_criticality_p</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>_importance_p</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_parser_initialized</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_activated</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_registered</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Hello_World_Meta_Data</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Hello__World__Meta__Data.html</filename>
    <member kind="function">
      <type></type>
      <name>Hello_World_Meta_Data</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Hello_World_Meta_Data</name>
      <anchor>a1</anchor>
      <arglist>(Hello_World_Meta_Data &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>const Hello_World_Meta_Data</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(Hello_World_Meta_Data &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a3</anchor>
      <arglist>(STDC::QMS::sensorServiceType &amp;config, CORBA::Long supplier_id, string &amp;QMS_Schema, const char *criticality_p, const char *importance_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a5</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Hello_World_Meta_Data</name>
      <anchor>a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>send</name>
      <anchor>a7</anchor>
      <arglist>(const string data, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_ec_registry</name>
      <anchor>a8</anchor>
      <arglist>(STDC::QMS::Citizen::QMS_Trader_ECInfo_var ec_registry)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_EC_info</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_EC_info</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_announce_suppliers</name>
      <anchor>a11</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_request_consumers</name>
      <anchor>a12</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_data_suppliers</name>
      <anchor>a13</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_announce_suppliers</name>
      <anchor>a14</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_request_consumers</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_data_suppliers</name>
      <anchor>a16</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_announce_suppliers</name>
      <anchor>a17</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_request_consumers</name>
      <anchor>a18</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_data_suppliers</name>
      <anchor>a19</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_announce_suppliers</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_request_consumers</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_data_suppliers</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_query</name>
      <anchor>a23</anchor>
      <arglist>(const string query, STDC::QMS::QMSMessage &amp;config, struct hw_payload_data &amp;request_data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>a24</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_announce_info</name>
      <anchor>b0</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_HW *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_request_info</name>
      <anchor>b1</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_HW *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_data_info</name>
      <anchor>b2</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_HW *param)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>STDC::QMS::sensorServiceType</type>
      <name>_config</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_HW * &gt;</type>
      <name>announce_list_info_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_HW * &gt;</type>
      <name>request_list_info_</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_HW * &gt;</type>
      <name>data_list_info_</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c1</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Announcement_Suppliers</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Consumer * &gt;</type>
      <name>Request_Consumers</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Data_Suppliers</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ULong</type>
      <name>_supplier_id</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long</type>
      <name>msg_sequence_no_</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>enum status_Type</type>
      <name>status</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_RW_Mutex</type>
      <name>status_guard</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_QMS_Schema</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>_criticality_p</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const char *</type>
      <name>_importance_p</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Meta_Data</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Meta__Data.html</filename>
    <member kind="function">
      <type></type>
      <name>Meta_Data</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Meta_Data</name>
      <anchor>a1</anchor>
      <arglist>(Meta_Data &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>const Meta_Data</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(Meta_Data &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a3</anchor>
      <arglist>(STDC::QMS::sensorServiceType &amp;config, CORBA::Long supplier_id, string &amp;QMS_Schema)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a4</anchor>
      <arglist>(STDC::QMS::ProbeDefinitionType &amp;capability, CORBA::Long supplier_id, string &amp;QMS_Schema)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a6</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Meta_Data</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>send</name>
      <anchor>a8</anchor>
      <arglist>(const string data, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_ec_registry</name>
      <anchor>a9</anchor>
      <arglist>(STDC::QMS::Citizen::QMS_Trader_ECInfo_var ec_registry)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_EC_info</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_EC_info</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_announce_suppliers</name>
      <anchor>a12</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_request_consumers</name>
      <anchor>a13</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_data_suppliers</name>
      <anchor>a14</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_announce_suppliers</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_request_consumers</name>
      <anchor>a16</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_data_suppliers</name>
      <anchor>a17</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_announce_suppliers</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_request_consumers</name>
      <anchor>a19</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_data_suppliers</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_announce_suppliers</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_request_consumers</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_data_suppliers</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_query</name>
      <anchor>a24</anchor>
      <arglist>(struct query_info *request_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_data</name>
      <anchor>a25</anchor>
      <arglist>(string key, string data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>a26</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_announce_info</name>
      <anchor>b0</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_request_info</name>
      <anchor>b1</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_data_info</name>
      <anchor>b2</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element *param)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>bool</type>
      <name>_is_internal</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>STDC::QMS::sensorServiceType</type>
      <name>_config</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>STDC::QMS::ProbeDefinitionType</type>
      <name>_capability</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element * &gt;</type>
      <name>announce_list_info_</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element * &gt;</type>
      <name>request_list_info_</name>
      <anchor>n4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element * &gt;</type>
      <name>data_list_info_</name>
      <anchor>n5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c1</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>internal_handle_query</name>
      <anchor>c2</anchor>
      <arglist>(const string &amp;query)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>send_error</name>
      <anchor>c3</anchor>
      <arglist>(const string &amp;error, STDC::QMS::QMSMessage &amp;config, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Announcement_Suppliers</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Consumer * &gt;</type>
      <name>Request_Consumers</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Data_Suppliers</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; string, struct probe_info * &gt;</type>
      <name>_probes</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; string, struct query_info * &gt;</type>
      <name>_requests</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ULong</type>
      <name>_supplier_id</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long</type>
      <name>msg_sequence_no_</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long</type>
      <name>_num_probes</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>enum status_Type</type>
      <name>status</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_RW_Mutex</type>
      <name>status_guard</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_QMS_Schema</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Meta_Data_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Meta__Data__Remos.html</filename>
    <member kind="function">
      <type></type>
      <name>Meta_Data_Remos</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Meta_Data_Remos</name>
      <anchor>a1</anchor>
      <arglist>(Meta_Data_Remos &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>const Meta_Data_Remos</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(Meta_Data_Remos &amp;copy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a3</anchor>
      <arglist>(STDC::QMS::sensorServiceType &amp;config, CORBA::Long supplier_id, string &amp;QMS_Schema)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a4</anchor>
      <arglist>(STDC::QMS::ProbeDefinitionType &amp;capability, CORBA::Long supplier_id, string &amp;QMS_Schema)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cleanup</name>
      <anchor>a6</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Meta_Data_Remos</name>
      <anchor>a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>send</name>
      <anchor>a8</anchor>
      <arglist>(const string data, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_ec_registry</name>
      <anchor>a9</anchor>
      <arglist>(STDC::QMS::Citizen::QMS_Trader_ECInfo_var ec_registry)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_EC_info</name>
      <anchor>a10</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_EC_info</name>
      <anchor>a11</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_announce_suppliers</name>
      <anchor>a12</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_request_consumers</name>
      <anchor>a13</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>create_data_suppliers</name>
      <anchor>a14</anchor>
      <arglist>(RtecEventComm::EventSourceID my_id, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_announce_suppliers</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_request_consumers</name>
      <anchor>a16</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect_data_suppliers</name>
      <anchor>a17</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_announce_suppliers</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_request_consumers</name>
      <anchor>a19</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect_data_suppliers</name>
      <anchor>a20</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_announce_suppliers</name>
      <anchor>a21</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_request_consumers</name>
      <anchor>a22</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clean_data_suppliers</name>
      <anchor>a23</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_query</name>
      <anchor>a24</anchor>
      <arglist>(struct query_info *request_p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>handle_data</name>
      <anchor>a25</anchor>
      <arglist>(string key, string data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>a26</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_announce_info</name>
      <anchor>b0</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_Remos *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_request_info</name>
      <anchor>b1</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_Remos *param)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>add_data_info</name>
      <anchor>b2</anchor>
      <arglist>(STDC::QMS::Citizen::Sensor_Data_Element_Remos *param)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>bool</type>
      <name>_is_internal</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>STDC::QMS::sensorServiceType</type>
      <name>_config</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>STDC::QMS::ProbeDefinitionType</type>
      <name>_capability</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_Remos * &gt;</type>
      <name>announce_list_info_</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_Remos * &gt;</type>
      <name>request_list_info_</name>
      <anchor>n4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>vector&lt; STDC::QMS::Citizen::Sensor_Data_Element_Remos * &gt;</type>
      <name>data_list_info_</name>
      <anchor>n5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Object_ptr obj, STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c1</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>internal_handle_query</name>
      <anchor>c2</anchor>
      <arglist>(const string &amp;query)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>int</type>
      <name>send_error</name>
      <anchor>c3</anchor>
      <arglist>(const string &amp;error, STDC::QMS::QMSMessage &amp;config, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Announcement_Suppliers</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Consumer * &gt;</type>
      <name>Request_Consumers</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; STDC::QMS::Push_Supplier * &gt;</type>
      <name>Data_Suppliers</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; string, struct probe_info * &gt;</type>
      <name>_probes</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; string, struct query_info * &gt;</type>
      <name>_requests</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ULong</type>
      <name>_supplier_id</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>long</type>
      <name>msg_sequence_no_</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned long</type>
      <name>_num_probes</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>enum status_Type</type>
      <name>status</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_RW_Mutex</type>
      <name>status_guard</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_QMS_Schema</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::One_Shot_Pipe_Proxy</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1One__Shot__Pipe__Proxy.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Pipe_Proxy</base>
    <member kind="function">
      <type></type>
      <name>One_Shot_Pipe_Proxy</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data &amp;parent, string &amp;key, double refresh_rate=DEFAULT_SLEEP, int iterations=9999)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~One_Shot_Pipe_Proxy</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>double</type>
      <name>refresh_rate_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>iterations_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::One_Shot_Pipe_Proxy_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1One__Shot__Pipe__Proxy__Remos.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Pipe_Proxy_Remos</base>
    <member kind="function">
      <type></type>
      <name>One_Shot_Pipe_Proxy_Remos</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data_Remos &amp;parent, string &amp;key, double refresh_rate=DEFAULT_SLEEP, int iterations=9999)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~One_Shot_Pipe_Proxy_Remos</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>double</type>
      <name>refresh_rate_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>iterations_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Pipe_Proxy</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Pipe__Proxy.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Probe_Proxy</base>
    <member kind="function">
      <type></type>
      <name>Pipe_Proxy</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Pipe_Proxy</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="public" virtualness="virtual">
      <type>virtual int</type>
      <name>init</name>
      <anchor>b0</anchor>
      <arglist>(const char *file_name_p, char *const argv[])</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>char *</type>
      <name>file_name_p_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>char **</type>
      <name>argv_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>ctrlpipe</name>
      <anchor>n2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>datapipe</name>
      <anchor>n3</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Pipe_Proxy_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Pipe__Proxy__Remos.html</filename>
    <base virtualness="virtual">STDC::QMS::Citizen::Probe_Proxy_Remos</base>
    <member kind="function">
      <type></type>
      <name>Pipe_Proxy_Remos</name>
      <anchor>a0</anchor>
      <arglist>(const char *file_name_p, char *const argv[], Meta_Data_Remos &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Pipe_Proxy_Remos</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="public" virtualness="virtual">
      <type>virtual int</type>
      <name>init</name>
      <anchor>b0</anchor>
      <arglist>(const char *file_name_p, char *const argv[])</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>char *</type>
      <name>file_name_p_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>char **</type>
      <name>argv_</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>ctrlpipe</name>
      <anchor>n2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>datapipe</name>
      <anchor>n3</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Probe_Proxy</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Probe__Proxy.html</filename>
    <member kind="function">
      <type></type>
      <name>Probe_Proxy</name>
      <anchor>a0</anchor>
      <arglist>(Meta_Data &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Probe_Proxy</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="enumeration">
      <name>Status</name>
      <anchor>t3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INACTIVE</name>
      <anchor>t3t0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ACTIVE</name>
      <anchor>t3t1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KILLED</name>
      <anchor>t3t2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>enum STDC::QMS::Citizen::Probe_Proxy::Status</type>
      <name>status_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>bool</type>
      <name>Am_I_Active</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>ACE_RW_Thread_Mutex</type>
      <name>lock_</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>Meta_Data &amp;</type>
      <name>_metadata</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_key</name>
      <anchor>n4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Probe_Proxy_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Probe__Proxy__Remos.html</filename>
    <member kind="function">
      <type></type>
      <name>Probe_Proxy_Remos</name>
      <anchor>a0</anchor>
      <arglist>(Meta_Data_Remos &amp;parent, string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>start</name>
      <anchor>a1</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>pause</name>
      <anchor>a2</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>resume</name>
      <anchor>a3</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>kill</name>
      <anchor>a4</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>deploy</name>
      <anchor>a5</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>destroy</name>
      <anchor>a6</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>send_command</name>
      <anchor>a7</anchor>
      <arglist>(const string command)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Probe_Proxy_Remos</name>
      <anchor>a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="enumeration">
      <name>Status</name>
      <anchor>t3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>INACTIVE</name>
      <anchor>t3t0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ACTIVE</name>
      <anchor>t3t1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KILLED</name>
      <anchor>t3t2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>enum STDC::QMS::Citizen::Probe_Proxy_Remos::Status</type>
      <name>status_</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>bool</type>
      <name>Am_I_Active</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>ACE_RW_Thread_Mutex</type>
      <name>lock_</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>Meta_Data_Remos &amp;</type>
      <name>_metadata</name>
      <anchor>n3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_key</name>
      <anchor>n4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::Citizen::Query</name>
    <filename>structSTDC_1_1QMS_1_1Citizen_1_1Query.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>qun_category</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>supplier_id</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>string</type>
      <name>ec_name</name>
      <anchor>m2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::Remos_Sensor</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1Remos__Sensor.html</filename>
    <base>STDC::QMS::Citizen::Command</base>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Remos_Sensor_Impl</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Remos__Sensor__Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Remos_Sensor_Impl</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Remos_Sensor_Impl</name>
      <anchor>a1</anchor>
      <arglist>(const Remos_Sensor_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Remos_Sensor_Impl &amp;</type>
      <name>operator=</name>
      <anchor>a2</anchor>
      <arglist>(const Remos_Sensor_Impl &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Remos_Sensor_Impl</name>
      <anchor>a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>pause</name>
      <anchor>a4</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resume</name>
      <anchor>a5</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stop</name>
      <anchor>a6</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>register_with_naming</name>
      <anchor>a7</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>unregister_with_naming</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>connect_EC</name>
      <anchor>a9</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>disconnect_EC</name>
      <anchor>a10</anchor>
      <arglist>(const char *reason, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reconnect_EC</name>
      <anchor>a11</anchor>
      <arglist>(const char *reason, const char *EC_Name, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>show_operating_level</name>
      <anchor>a12</anchor>
      <arglist>(CORBA::Short_out level)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_operating_level</name>
      <anchor>a13</anchor>
      <arglist>(CORBA::Short level, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stats</name>
      <anchor>a14</anchor>
      <arglist>(const char *credentials, CORBA::String_out stats)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ping</name>
      <anchor>a15</anchor>
      <arglist>(CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>start</name>
      <anchor>a16</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>init</name>
      <anchor>a17</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p, string credentials, char *config_file_p, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>cleanup</name>
      <anchor>a18</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>update_registration</name>
      <anchor>a19</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reload_configuration</name>
      <anchor>a20</anchor>
      <arglist>(string reason, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_security_policy</name>
      <anchor>a21</anchor>
      <arglist>(string credentials, string &amp;policy)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_security_policy</name>
      <anchor>a22</anchor>
      <arglist>(string policy, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get_attributes</name>
      <anchor>a23</anchor>
      <arglist>(string credentials, string &amp;attributes)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_attributes</name>
      <anchor>a24</anchor>
      <arglist>(string attributes, string credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>add_handle</name>
      <anchor>a25</anchor>
      <arglist>(STDC::QMS::CORBA_Handles *handles_p)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::CORBA_Handles *</type>
      <name>get_handle</name>
      <anchor>a26</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>activate</name>
      <anchor>a27</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>deactivate</name>
      <anchor>a28</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>handle_query</name>
      <anchor>a29</anchor>
      <arglist>(const string &amp;query)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_config</name>
      <anchor>b0</anchor>
      <arglist>(char *file_name_p)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>bool</type>
      <name>parse_capability</name>
      <anchor>b1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_supplier_id</name>
      <anchor>b2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>get_ECInfo</name>
      <anchor>b3</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="public">
      <type>void</type>
      <name>yp_offer</name>
      <anchor>b4</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>get_ec_registry</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c1</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>withdraw_offer</name>
      <anchor>c2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>builtin_probes</name>
      <anchor>c3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>external_probes</name>
      <anchor>c4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>probe_offers</name>
      <anchor>c5</anchor>
      <arglist>(string credentials)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init_parser</name>
      <anchor>c6</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>parser_cleanup</name>
      <anchor>c7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p_</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>attributes</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>policy</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::OfferId_var</type>
      <name>offer_id</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PortableServer::ObjectId_var</type>
      <name>oid_</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Object_var</type>
      <name>obj_</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>id_</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>level_</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Long</type>
      <name>_supplier_id</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; std::string, STDC::QMS::Citizen::Meta_Data_Remos * &gt;</type>
      <name>probes_</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo_var</type>
      <name>_ec_registry</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::sensorConfiguration</type>
      <name>config</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>_capability_file</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::sensorCapability</type>
      <name>capability</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_parser_initialized</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_activated</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_offer_created</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_registered</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Sensor_Data_Element</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Sensor__Data__Element.html</filename>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element</name>
      <anchor>a0</anchor>
      <arglist>(string name=&quot;&quot;, int value=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element</name>
      <anchor>a1</anchor>
      <arglist>(string name, string value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element</name>
      <anchor>a2</anchor>
      <arglist>(const Sensor_Data_Element &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Sensor_Data_Element &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const Sensor_Data_Element &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_name</name>
      <anchor>a4</anchor>
      <arglist>(string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_name</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_string_val</name>
      <anchor>a6</anchor>
      <arglist>(string &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_string_val</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_int_val</name>
      <anchor>a8</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_int_val</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_name</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>_valInt</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_valString</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Sensor_Data_Element_HW</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Sensor__Data__Element__HW.html</filename>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_HW</name>
      <anchor>a0</anchor>
      <arglist>(string name=&quot;&quot;, int value=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_HW</name>
      <anchor>a1</anchor>
      <arglist>(string name, string value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_HW</name>
      <anchor>a2</anchor>
      <arglist>(const Sensor_Data_Element_HW &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Sensor_Data_Element_HW &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const Sensor_Data_Element_HW &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_name</name>
      <anchor>a4</anchor>
      <arglist>(string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_name</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_string_val</name>
      <anchor>a6</anchor>
      <arglist>(string &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_string_val</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_int_val</name>
      <anchor>a8</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_int_val</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_name</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>_valInt</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_valString</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::Sensor_Data_Element_Remos</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1Sensor__Data__Element__Remos.html</filename>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_Remos</name>
      <anchor>a0</anchor>
      <arglist>(string name=&quot;&quot;, int value=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_Remos</name>
      <anchor>a1</anchor>
      <arglist>(string name, string value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Sensor_Data_Element_Remos</name>
      <anchor>a2</anchor>
      <arglist>(const Sensor_Data_Element_Remos &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>Sensor_Data_Element_Remos &amp;</type>
      <name>operator=</name>
      <anchor>a3</anchor>
      <arglist>(const Sensor_Data_Element_Remos &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_name</name>
      <anchor>a4</anchor>
      <arglist>(string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_name</name>
      <anchor>a5</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_string_val</name>
      <anchor>a6</anchor>
      <arglist>(string &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>get_string_val</name>
      <anchor>a7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_int_val</name>
      <anchor>a8</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_int_val</name>
      <anchor>a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_name</name>
      <anchor>n0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>int</type>
      <name>_valInt</name>
      <anchor>n1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="public">
      <type>string</type>
      <name>_valString</name>
      <anchor>n2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::Citizen::QMS_Trader_ECInfo::ECInfo</name>
    <filename>structSTDC_1_1QMS_1_1Citizen_1_1QMS__Trader__ECInfo_1_1ECInfo.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>EventChannelName</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>EventId</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="interface">
    <name>STDC::QMS::Citizen::QMS_Trader_ECInfo</name>
    <filename>interfaceSTDC_1_1QMS_1_1Citizen_1_1QMS__Trader__ECInfo.html</filename>
    <base>STDC::QMS::Citizen::Command</base>
    <member kind="typedef">
      <type>sequence&lt; ECInfo &gt;</type>
      <name>AnnounceSeq</name>
      <anchor>s0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sequence&lt; ECInfo &gt;</type>
      <name>DataSeq</name>
      <anchor>s1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sequence&lt; ECInfo &gt;</type>
      <name>RequestSeq</name>
      <anchor>s2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>AnnounceSeq</type>
      <name>getAnnounceChannels</name>
      <anchor>a0</anchor>
      <arglist>(in string qms_unique_name)</arglist>
    </member>
    <member kind="function">
      <type>DataSeq</type>
      <name>getDataChannels</name>
      <anchor>a1</anchor>
      <arglist>(in string qms_unique_name)</arglist>
    </member>
    <member kind="function">
      <type>RequestSeq</type>
      <name>getRequestChannels</name>
      <anchor>a2</anchor>
      <arglist>(in string qms_unique_name)</arglist>
    </member>
    <member kind="function">
      <type>unsigned long</type>
      <name>getSupplierID</name>
      <anchor>a3</anchor>
      <arglist>(in string description)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>STDC::QMS::Citizen::QMS_Trader_ECInfo::ECInfo</name>
    <filename>structSTDC_1_1QMS_1_1Citizen_1_1QMS__Trader__ECInfo_1_1ECInfo.html</filename>
    <member kind="variable">
      <type>string</type>
      <name>EventChannelName</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long</type>
      <name>EventId</name>
      <anchor>m1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>STDC::QMS::Citizen::QMS_Trader_ECInfo_Impl</name>
    <filename>classSTDC_1_1QMS_1_1Citizen_1_1QMS__Trader__ECInfo__Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>QMS_Trader_ECInfo_Impl</name>
      <anchor>a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~QMS_Trader_ECInfo_Impl</name>
      <anchor>a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchor>a2</anchor>
      <arglist>(char *, STDC::QMS::CORBA_Handles *ptr=0, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>pause</name>
      <anchor>a3</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>resume</name>
      <anchor>a4</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stop</name>
      <anchor>a5</anchor>
      <arglist>(const char *reason, const char *credentials, CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>disconnect_EC</name>
      <anchor>a6</anchor>
      <arglist>(const char *reason, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reconnect_EC</name>
      <anchor>a7</anchor>
      <arglist>(const char *reason, const char *EC_Name, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>show_operating_level</name>
      <anchor>a8</anchor>
      <arglist>(CORBA::Short_out level)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set_operating_level</name>
      <anchor>a9</anchor>
      <arglist>(CORBA::Short level, const char *credentials)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>stats</name>
      <anchor>a10</anchor>
      <arglist>(const char *credentials, CORBA::String_out stats)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ping</name>
      <anchor>a11</anchor>
      <arglist>(CORBA::Short_out ack)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *</type>
      <name>getAnnounceChannels</name>
      <anchor>a12</anchor>
      <arglist>(const char *qms_unique_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq *</type>
      <name>getDataChannels</name>
      <anchor>a13</anchor>
      <arglist>(const char *qms_unique_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq *</type>
      <name>getRequestChannels</name>
      <anchor>a14</anchor>
      <arglist>(const char *qms_unique_name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual CORBA::ULong</type>
      <name>getSupplierID</name>
      <anchor>a15</anchor>
      <arglist>(const char *description)</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>list&lt; string &gt;</type>
      <name>stringList</name>
      <anchor>u0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>list&lt; ECInfo &gt;</type>
      <name>ECList</name>
      <anchor>u1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>add_yp_serviceType</name>
      <anchor>c0</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>add_registry_serviceType</name>
      <anchor>c1</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>add_supplier_serviceType</name>
      <anchor>c2</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>offer_exporter</name>
      <anchor>c3</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>offer_importer</name>
      <anchor>c4</anchor>
      <arglist>(string &amp;, string &amp;, list&lt; ECInfo &gt; &amp;, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>supplier_importer</name>
      <anchor>c5</anchor>
      <arglist>(CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>supplier_exporter</name>
      <anchor>c6</anchor>
      <arglist>(string &amp;supplier_name, CORBA::Environment &amp;ACE_TRY_ENV=TAO_default_environment())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>make_offer</name>
      <anchor>c7</anchor>
      <arglist>(CORBA::Environment &amp;)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>yp_service_type</name>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>r_service_type</name>
      <anchor>o1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>supplier_service_type</name>
      <anchor>o2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>char *</type>
      <name>config_file</name>
      <anchor>o3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ULong</type>
      <name>supplierid_num</name>
      <anchor>o4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::CORBA_Handles *</type>
      <name>handles_p</name>
      <anchor>o5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>handles_flag</name>
      <anchor>o6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::Lookup_ptr</type>
      <name>lookup_p</name>
      <anchor>o7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::Lookup_var</type>
      <name>lookup_v</name>
      <anchor>o8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::ULong</type>
      <name>eventid_num</name>
      <anchor>o9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ACE_Thread_Mutex</type>
      <name>asset_guard</name>
      <anchor>o10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTradingRepos::ServiceTypeRepository_var</type>
      <name>repos_</name>
      <anchor>o11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTradingRepos::ServiceTypeRepository::TypeStruct</type>
      <name>type_struct_</name>
      <anchor>o12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::Register_var</type>
      <name>register_</name>
      <anchor>o13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CosTrading::PropertySeq</type>
      <name>eprops</name>
      <anchor>o14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>desc</name>
      <anchor>o15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>CORBA::Short</type>
      <name>level_</name>
      <anchor>o16</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vector&lt; CosTrading::OfferId_var &gt;</type>
      <name>offerid_list</name>
      <anchor>o17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ECList</type>
      <name>announce_values</name>
      <anchor>o18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ECList</type>
      <name>data_values</name>
      <anchor>o19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ECList</type>
      <name>request_values</name>
      <anchor>o20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ECInfo</type>
      <name>Info</name>
      <anchor>o21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>index</name>
      <anchor>o22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo::AnnounceSeq *</type>
      <name>announceECSeq</name>
      <anchor>o23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo::DataSeq *</type>
      <name>dataECSeq</name>
      <anchor>o24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>STDC::QMS::Citizen::QMS_Trader_ECInfo::RequestSeq *</type>
      <name>requestECSeq</name>
      <anchor>o25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="exception">
    <name>STDC::QMS::Citizen::USERERROR</name>
    <filename>exceptionSTDC_1_1QMS_1_1Citizen_1_1USERERROR.html</filename>
    <member kind="variable">
      <type>any</type>
      <name>reason</name>
      <anchor>m0</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
