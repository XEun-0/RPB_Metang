#/bin/bash

cat /sys/firmware/devicetree/bash/model
echo -e "\n"
cat /etc/os-release

VAR_BASH_TYPE="$(echo $SHELL)"
VAR_BASH_LITERAL_TYPE="Shell name: $(ps -p $$ -o comm=)"
echo $VAR_BASH_TYPE
echo $VAR_BASH_LITERAL_TYPE