#!/bin/bash

eval 'nohup nice -n 10 ./MyLooper.exe < UnskimmedRunLists/tttt.txt >& logs/tttt_log.txt &'

