#include <iostream>
#include "TF1.h"

double smearPt(double pt,int hiBin){
TF1 *f_pp = new TF1("f_pp","0.018+1.251/sqrt(x)",40,300);
TF1 *f_0_10 = new TF1("f_0_10","0.018+1.251/sqrt(x)+0.480/x",40,300);
TF1 *f_10_30 = new TF1("f_10_30","0.018+1.251/sqrt(x)+0.528/x",40,300);
TF1 *f_30_50 = new TF1("f_30_50","0.018+1.251/sqrt(x)+0.829/x",40,300);
TF1 *f_50_100 = new TF1("f_50_100","0.018+1.251/sqrt(x)+2.119/x",40,300);

TF1 * fgaus=new TF1("fgaus","gaus(0)",-20,20);
fgaus->SetParameters(1,0,1);

double sigma_pp=f_pp->Eval(pt);
double sigma_PbPb=sigma_pp;

if(hiBin<20) sigma_PbPb=f_0_10->Eval(pt);
else if(hiBin<60) sigma_PbPb=f_10_30->Eval(pt);
else if(hiBin<100) sigma_PbPb=f_30_50->Eval(pt);
else sigma_PbPb=f_50_100->Eval(pt);

double smearedPt=pt*(1+sqrt(pow(sigma_PbPb,2)-pow(sigma_pp,2))*fgaus->GetRandom());

return smearedPt;
}