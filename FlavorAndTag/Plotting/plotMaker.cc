#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <iostream>
#include "TStyle.h"
#include "TGaxis.h"

int main (int argc, char ** argv)
{
  gStyle->SetOptStat(0);

  if (argc == 1) {std::cout << "Need input" << std::endl; return 0;}

  TString file_name(argv[1]);
  int start = file_name.Last('/')+1;
  TString clean_name = file_name(start,file_name.Index(".root") - start);
  TFile * tf = TFile::Open(file_name);
  tf->cd();
  TH1F * h_lf = (TH1F*) tf->Get("h_light_fakes");
  TH1F * h_cf = (TH1F*) tf->Get("h_charm_fakes");
  TH1F * h_tt = (TH1F*) tf->Get("h_true_tags");
  TH1F * h_tagged_pt = (TH1F*) tf->Get("h_tagged_pt");
  TH1F * h_trueb_pt = (TH1F*) tf->Get("h_trueb_pt");
  TH1F * h_trueb_eta = (TH1F*) tf->Get("h_trueb_eta");

  const int LINE_WIDTH = 3;
  h_lf->SetLineWidth(LINE_WIDTH);
  h_cf->SetLineWidth(LINE_WIDTH);
  h_tt->SetLineWidth(LINE_WIDTH);
  h_tagged_pt->SetLineWidth(LINE_WIDTH);
  h_trueb_pt->SetLineWidth(LINE_WIDTH);
  h_trueb_eta->SetLineWidth(LINE_WIDTH);

  h_cf->SetLineColor(kRed);
  h_tt->SetLineColor(kGreen);
  TLegend leg(0.7, 0.7, 0.85, 0.8);
  leg.AddEntry(h_lf, "Light Fakes");
  leg.AddEntry(h_cf, "Charm Fakes");
  leg.AddEntry(h_tt, "True Tags");

  h_lf->SetMaximum(h_lf->Integral());
  h_lf->SetTitle(clean_name.Copy().Append(" Tag Multiplicity Distribution (3+ Tag Events);Multiplicity;Count @ 35.9 fb^{-1}"));
  TCanvas c1("tmp_canvas","drawing canvas");
  c1.SetLogy();
 
  h_lf->Draw();
  h_cf->Draw("same");
  h_tt->Draw("same");
  leg.Draw();
  c1.SaveAs( Form("PNGs/%s.png", clean_name.Data()) );
  
  c1.SetLogy(false);
  c1.Update();

  float rightmax = gPad->GetUymax() / h_lf->Integral();

  // L = linear, + means draw ticks internal to plot
  // G = log
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
			    gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
  axis->SetTitle("Fraction");
  float labelsize = h_lf->GetYaxis()->GetLabelSize();
  axis->SetLabelSize(labelsize);
  axis->Draw();

  c1.SaveAs( Form("PNGs/%s_norm.png", clean_name.Data()) );
  
  TString tagged_pt_title = clean_name.Copy().Append(" ");
  tagged_pt_title.Append(h_tagged_pt->GetTitle());
  h_tagged_pt->SetTitle(tagged_pt_title);
  h_tagged_pt->Draw();

  c1.SaveAs( Form("PNGs/%s_tagged_pt.png", clean_name.Data()));
  
  TString trueb_pt_title = clean_name.Copy().Append(" ");
  trueb_pt_title.Append(h_trueb_pt->GetTitle());
  h_trueb_pt->SetTitle(trueb_pt_title);
  h_trueb_pt->Draw();
  
  c1.SaveAs( Form("PNGs/%s_trueb_pt.png", clean_name.Data()));

  TString trueb_eta_title = clean_name.Copy().Append(" ");
  trueb_eta_title.Append(h_trueb_eta->GetTitle());
  h_trueb_eta->SetTitle(trueb_eta_title);
  h_trueb_eta->Draw();
  
  c1.SaveAs( Form("PNGs/%s_trueb_eta.png", clean_name.Data()));
}
