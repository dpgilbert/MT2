#!/bin/bash

declare -a Samples=(ttsl ttdl singletop qcd_ht ttw_mg_lo ttz_mg_lo ttg tth dyjetsll_ht gjets_dr0p05_ht wjets_ht100to200 wjets_ht1200to2500 wjets_ht200to400 wjets_ht2500toInf wjets_ht400to600 wjets_ht600to800 wjets_ht800to1200 zinv_ht)

INDIR=/nfs-6/userdata/mt2/V00-08-18_mc_skim_base_mt2gt200_ZinvV6_JECs/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/DDvsMC/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./SelectionSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_selection_log.txt &'
done

