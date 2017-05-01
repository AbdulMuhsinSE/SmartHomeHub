ssh -tt pi@SE620-2-3<< EOF
./kill
python mary_control_switch.py > /dev/null 2 >&1 & disown;
python newer_mary_demo_light.py > /dev/null 2 >&1 & disown;
exit;
EOF
