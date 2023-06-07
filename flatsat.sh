#!/bin/bash

# usage: ./flatsat.sh "hello world"

input_msg="$1"

echo "Message sent: $input_msg"
echo "$input_msg" | ./encode

# should move this venv into the local repo
/opt/homebrew/Cellar/gnuradio/3.10.6.0/libexec/venv/bin/python -u OFDM_Test_1.py

echo -n "Message received: "
./decode out.hoff