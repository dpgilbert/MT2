{  
  TCanvas *c1 = new TCanvas();
  c1->SetLogy();
  c1->cd();
  
  TString title = h_njet_nocut->GetTitle();
  h_njet_nocut->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_nocut->SetFillColor(kRed);
  h_njet_nocut->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_nocut.pdf");

  title = h_njet_trigger->GetTitle();
  h_njet_trigger->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_trigger->SetFillColor(kRed);
  h_njet_trigger->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_trigger.pdf");

  title = h_njet_njet->GetTitle();
  h_njet_njet->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_njet->SetFillColor(kRed);
  h_njet_njet->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_njet.pdf");

  title = h_njet_dphi->GetTitle();
  h_njet_dphi->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_dphi->SetFillColor(kRed);
  h_njet_dphi->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_dphi.pdf");

  title = h_njet_diff->GetTitle();
  h_njet_diff->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_diff->SetFillColor(kRed);
  h_njet_diff->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_diff.pdf");

  title = h_njet_lep->GetTitle();
  h_njet_lep->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_lep->SetFillColor(kRed);
  h_njet_lep->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_lep.pdf");

  title = h_njet_mt2->GetTitle();
  h_njet_mt2->SetTitle(title.Append(";N_{J};Counts at 1 fb^{-1}"));
  h_njet_mt2->SetFillColor(kRed);
  h_njet_mt2->Draw("Ehist");
  c1->Print("../../UnskimmedPlots/njet_mt2.pdf");
}
