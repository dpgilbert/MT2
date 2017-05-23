#!/bin/bash

eval 'nohup nice -n 10 ./LeptonVetoLooper.exe < ../UnskimmedRunLists/ttdl.txt >& ttdl_log.txt &'

