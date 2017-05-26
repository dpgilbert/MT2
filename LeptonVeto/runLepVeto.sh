#!/bin/bash

eval 'nohup nice -n 10 ./LeptonVetoLooper.exe < ../UnskimmedRunLists/ww.txt >& ww_log.txt &'

