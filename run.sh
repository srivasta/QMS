#!/bin/sh

# I would prefer it this way, but there does not seem to be a way to
# find out the HOME of the JDK ...
# : ${JAVA_HOME:="@@@JAVA_HOME@@@"}
# ... If there is no JDK, simply set the following ...
# : ${JRE_HOME:="$JAVA_HOME/jre"}

# ... but we have to refer to the JRE only!
: ${JRE_HOME:="/var/local/opt/jdk/j2sdk1.3.1/jre"}

: ${JACORB_HOME:="/var/local/opt/jacorb/jacorb-1.3.3"}
export JACORB_HOME

: ${CLASSPATH:="/home/quite/QMS/build/classes:/home/quite/QMS/libjar/xerces.jar"}
export CLASSPATH

: ${JACORB_THREADS:="-native"}

# call java interpreter
echo ${JRE_HOME}/bin/java ${JACORB_THREADS} \
    -Xbootclasspath:${JACORB_HOME}/lib/jacorb.jar:${JRE_HOME}/lib/rt.jar:${CLASSPATH} \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton \
    -Dorg.xml.sax.driver=org.apache.xerces.parsers.SAXParser \
    "$@"

exec ${JRE_HOME}/bin/java ${JACORB_THREADS} \
    -Xbootclasspath:${JACORB_HOME}/lib/jacorb.jar:${JRE_HOME}/lib/rt.jar:${CLASSPATH} \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton \
    -Dorg.xml.sax.driver=org.apache.xerces.parsers.SAXParser \
    "$@"

