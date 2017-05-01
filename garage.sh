#!/bin/bash

ssh -tt pi@SE620-1-3<< EOF
cd MFRC522-python;
./KillGarageReader;
python GarageMotor.py > /dev/null 2 >&1 & disown;
python GarageReader.py >/dev/null 2>&1 & disown;
exit;
EOF
