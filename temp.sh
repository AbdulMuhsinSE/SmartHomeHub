#!/bin/bash
TEMP1="$1";
TEMP2="$2";

ssh -tt pi@SE620-2-4<< EOF
cd wiringPi;
echo ${TEMP1};
echo ${TEMP2};
./KillThermostat;
./thermostat2 ${TEMP1} ${TEMP2} > /dev/null 2 >&1 & disown;
exit;
EOF
