#!/bin/bash

# only dilepton samples
declare -a Samples=(tth_zero ttz_mg_lo_zero)

INDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/LowMT2Skim/SkimmedMC/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/3BSkim/SkimmedMC_zero/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./3BSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_3B_selection_log.txt &'
done

