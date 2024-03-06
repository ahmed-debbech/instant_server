#!/bin/bash

echo "===TSARM==="

if [ -z "$1" ]; then
    #no param
    ./prog
else
    if [[ "$1" == "-i" ]]; then        
        if [ -n "$2" ]; then
            echo "setting IP... success";
            ./prog $1 $2
        else
            echo "Server IP missing, please specify the ip"
        fi
    else
        echo "wrong arguments";
    fi
fi