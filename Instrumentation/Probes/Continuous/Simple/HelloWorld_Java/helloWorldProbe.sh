#!/bin/sh

# I would prefer it this way, but there does not seem to be a way to
# find out the HOME of the JDK ...
# : ${JAVA_HOME:="@@@JAVA_HOME@@@"}
# ... If there is no JDK, simply set the following ...
# : ${JRE_HOME:="$JAVA_HOME/jre"}

# ... but we have to refer to the JRE only!
: ${JRE_HOME:="/var/local/opt/jdk/j2sdk1.3.1/jre"}

: ${CLASSPATH:="/home/quite/QMS/build/classes"}
export CLASSPATH

# call java interpreter
exec 6>&-
exec ${JRE_HOME}/bin/java -native -classpath $CLASSPATH \
    com.stdc.Instrumentation.Probes.HelloWorld.HelloWorldProbe $@

