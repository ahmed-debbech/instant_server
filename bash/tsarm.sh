#!/bin/bash

echo "hello"

if [ -z "$1" ]; then
    #no param
    echo "Reading message...";
else
    if [[ "$1" == "-i" ]]; then        
        if [ -n "$2" ]; then
            echo "setting IP";
        else
            echo "Server IP missing, please specify the ip"
        fi
    else
        echo "msg"
    fi
fi