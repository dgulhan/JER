#include <iostream>
#include <vector>
#include <algorithm>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom1.h"
#include "TLorentzVector.h"
#include "TH1F.h"

#include "TFile.h"
#include "TTree.h"
#include "TColor.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TF1.h"
#include "TLatex.h"
#include "TString.h" 
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h"  

void drawText(const char *text, float xp, float yp, int size=20){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw("same");
}

void fit(){
TFile * file_pp = new TFile("pp_sigma.root");
TFile * file_PbPb = new TFile("PbPb_sigma.root");

TH1D * JER_pp = (TH1D*)file_pp->Get("JER_pp");
TH1D * JER_0_10 = (TH1D*)file_PbPb->Get("JER_0_10");
TH1D * JER_10_30 = (TH1D*)file_PbPb->Get("JER_10_30");
TH1D * JER_30_50 = (TH1D*)file_PbPb->Get("JER_30_50");
TH1D * JER_50_100 = (TH1D*)file_PbPb->Get("JER_50_100");


TF1 *f_pp = new TF1("f_pp","sqrt(pow([0],2)+pow([1]/sqrt(x),2))",40,300);
f_pp->SetParameters(0.01,1.1);
JER_pp->Fit("f_pp");

TF1 *f_0_10 = new TF1("f_0_10",Form("sqrt(pow(%.4f,2)+pow(%.4f/sqrt(x),2)+pow([0]/x,2))",f_pp->GetParameter(0),f_pp->GetParameter(1)),40,300);
TF1 *f_10_30 = new TF1("f_10_30",Form("sqrt(pow(%.4f,2)+pow(%.4f/sqrt(x),2)+pow([0]/x,2))",f_pp->GetParameter(0),f_pp->GetParameter(1)),40,300);
TF1 *f_30_50 = new TF1("f_30_50",Form("sqrt(pow(%.4f,2)+pow(%.4f/sqrt(x),2)+pow([0]/x,2))",f_pp->GetParameter(0),f_pp->GetParameter(1)),40,300);
TF1 *f_50_100 = new TF1("f_50_100",Form("sqrt(pow(%.4f,2)+pow(%.4f/sqrt(x),2)+pow([0]/x,2))",f_pp->GetParameter(0),f_pp->GetParameter(1)),40,300);

f_0_10->SetParameter(0,5);
f_10_30->SetParameter(0,1);
f_30_50->SetParameter(0,1);
f_50_100->SetParameter(0,1);
JER_0_10->Fit(f_0_10,"R");
JER_10_30->Fit(f_10_30,"R");
JER_30_50->Fit(f_30_50,"R");
JER_50_100->Fit(f_50_100,"R");

JER_pp->GetXaxis()->SetRangeUser(50,300);
JER_0_10->GetXaxis()->SetRangeUser(50,300);
JER_10_30->GetXaxis()->SetRangeUser(50,300);
JER_30_50->GetXaxis()->SetRangeUser(50,300);
JER_50_100->GetXaxis()->SetRangeUser(50,300);
JER_0_10->SetMarkerStyle(20);
JER_10_30->SetMarkerStyle(20);
JER_30_50->SetMarkerStyle(20);
JER_50_100->SetMarkerStyle(20);
JER_0_10->SetMarkerSize(1);
JER_10_30->SetMarkerSize(1);
JER_30_50->SetMarkerSize(1);
JER_50_100->SetMarkerSize(1);
JER_pp->SetNdivisions(505);
JER_0_10->SetNdivisions(505);
JER_10_30->SetNdivisions(505);
JER_30_50->SetNdivisions(505);
JER_50_100->SetNdivisions(505);
JER_pp->GetXaxis()->SetLabelSize(0.0625);
JER_0_10->GetXaxis()->SetLabelSize(0.0625);
JER_10_30->GetXaxis()->SetLabelSize(0.0625);
JER_30_50->GetXaxis()->SetLabelSize(0.0625);
JER_50_100->GetXaxis()->SetLabelSize(0.0625);
JER_0_10->GetYaxis()->SetLabelSize(0.);
JER_10_30->GetYaxis()->SetLabelSize(0.);
JER_30_50->GetYaxis()->SetLabelSize(0.);
JER_50_100->GetYaxis()->SetLabelSize(0.);
JER_pp->GetXaxis()->SetTitleSize(0.0625);
JER_0_10->GetXaxis()->SetTitleSize(0.0625);
JER_10_30->GetXaxis()->SetTitleSize(0.0625);
JER_30_50->GetXaxis()->SetTitleSize(0.0625);
JER_50_100->GetXaxis()->SetTitleSize(0.0625);

JER_0_10->GetYaxis()->SetTitleSize(0.);
JER_10_30->GetYaxis()->SetTitleSize(0.);
JER_30_50->GetYaxis()->SetTitleSize(0.);
JER_50_100->GetYaxis()->SetTitleSize(0.);

JER_pp->GetYaxis()->SetTitle("#sigma");
JER_pp->GetXaxis()->SetTitle("p_{T,gen} (GeV/c)");
JER_0_10->GetXaxis()->SetTitle("p_{T,gen} (GeV/c)");
JER_10_30->GetXaxis()->SetTitle("p_{T,gen} (GeV/c)");
JER_30_50->GetXaxis()->SetTitle("p_{T,gen} (GeV/c)");
JER_50_100->GetXaxis()->SetTitle("p_{T,gen} (GeV/c)");
JER_pp->GetYaxis()->SetTitleOffset(1.2);
JER_pp->GetXaxis()->SetTitleOffset(0.5);
JER_0_10->GetXaxis()->SetTitleOffset(0.5);
JER_10_30->GetXaxis()->SetTitleOffset(0.5);
JER_30_50->GetXaxis()->SetTitleOffset(0.5);
JER_50_100->GetXaxis()->SetTitleOffset(0.5);

TCanvas *c2 = new TCanvas("c2","",1600,400);
c2->Divide(5,1);
c2->cd(1);
c2->cd(1)->SetLogx(); 
c2->cd(1)->SetRightMargin(0);
c2->cd(1)->SetLeftMargin(0.12);
JER_pp->Draw();
f_pp->Draw("same");
drawText("0-10%, PYTHIA",0.15,0.9);
drawText("ak3Calo",0.15,0.85);
drawText(Form("C=%.3f",f_pp->GetParameter(0)),0.55,0.8);
drawText(Form("S=%.3f",f_pp->GetParameter(1)),0.55,0.75);

c2->cd(2);
c2->cd(2)->SetLogx();
c2->cd(2)->SetRightMargin(0);
c2->cd(2)->SetLeftMargin(0);
JER_50_100->Draw();
f_50_100->Draw("same");
drawText("50-100%, PYTHIA+HYDJET",0.1,0.9);
drawText("akVs3Calo",0.1,0.85);
drawText(Form("N=%.3f",f_50_100->GetParameter(0)),0.5,0.8);

c2->cd(3);
c2->cd(3)->SetLogx();
c2->cd(3)->SetRightMargin(0);
c2->cd(3)->SetLeftMargin(0);
JER_30_50->Draw();
f_30_50->Draw("same");
drawText("30-50%, PYTHIA+HYDJET",0.1,0.9);
drawText("akVs3Calo",0.1,0.85);
drawText(Form("N=%.3f",f_30_50->GetParameter(0)),0.5,0.8);

c2->cd(4);
c2->cd(4)->SetLogx();
c2->cd(4)->SetRightMargin(0);
c2->cd(4)->SetLeftMargin(0);
JER_10_30->Draw();
f_10_30->Draw("same");
drawText("10-30%, PYTHIA+HYDJET",0.1,0.9);
drawText("akVs3Calo",0.1,0.85);
drawText(Form("N=%.3f",f_10_30->GetParameter(0)),0.5,0.8);

c2->cd(5);
c2->cd(5)->SetLogx();
c2->cd(5)->SetRightMargin(0);
c2->cd(5)->SetLeftMargin(0.);
JER_0_10->Draw();
f_0_10->Draw("same");
drawText("0-10%, PYTHIA+HYDJET",0.1,0.9);

drawText("akVs3Calo",0.1,0.85);
drawText(Form("N=%.3f",f_0_10->GetParameter(0)),0.5,0.8);

c2->SaveAs("PbPb_fits.png");
cout<<"p0 pp "<<f_pp->GetParameter(0)<<endl;
cout<<"p1 pp "<<f_pp->GetParameter(1)<<endl;

cout<<"p0 0-10 "<<f_0_10->GetParameter(0)<<endl;
cout<<"p0 10-30 "<<f_10_30->GetParameter(0)<<endl;
cout<<"p0 30-50 "<<f_30_50->GetParameter(0)<<endl;
cout<<"p0 50-100 "<<f_50_100->GetParameter(0)<<endl;

}