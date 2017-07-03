#!/bin/bash

# only dilepton samples
declare -a Samples=(dyjets_ht qcd_ht singletop ttsl ttdl ttg tth ttw_mg_lo ttz_mg_lo tttt twz wjets ww zinv_ht)

INDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/SkimmedMC_clean/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/3BSkim/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./3BSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_3B_selection_log.txt &'
done

