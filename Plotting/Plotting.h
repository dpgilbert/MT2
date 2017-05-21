#ifndef PLOTTING_H
#define PLOTTING_H

std::map< std::string, TH1F* > hist_list_1D;
std::map< std::string, TH1F* > hist_list_sig;
void CopyAxes (THStack* hs, TH1* h, TCanvas& c);
void overlay (THStack* hs, TLegend* tl, TH1F* h, TCanvas& c, std::string type);

#endif
