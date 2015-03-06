#include "JPetParamUtils.h"

 double JPetParamUtils::distanceXY(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) 
{
  double angle = TMath::Abs(slot2.getTheta() - slot1.getTheta());
  double radius1= slot1.getLayer().getRadius(); 
  double radius2= slot2.getLayer().getRadius();
  double radUnit = TMath::Pi()/180;
  double radiusDiff = TMath::Abs(radius1 - radius2);

  if(radiusDiff < 0.01){
    double dist = 2*radius1*TMath::Sin(0.5*angle*radUnit); 
    return dist;
  }
  else{
    WARNING(Form("For PMTs with different radius distanceXY() never tested"));
    double dist1 = radius1*TMath::Sin(0.5*angle*radUnit);
    double dist2 = radius2*TMath::Sin(0.5*angle*radUnit);
    double xDist = dist1+dist2;
    double y1 = radius1*TMath::Cos(0.5*angle*radUnit);
    double y2 = radius2*TMath::Cos(0.5*angle*radUnit);
    double deltaY = TMath::Abs(y2 - y1);
    double dist = TMath::Sqrt(xDist*xDist + deltaY*deltaY);
    return dist;
  }
}


 double JPetParamUtils::distanceXY(const JPetPM& PM1, const JPetPM& PM2) 
{
  const JPetBarrelSlot& slot1 = PM1.getBarrelSlot();
  const JPetBarrelSlot& slot2 = PM2.getBarrelSlot();
  return distanceXY(slot1, slot2);
}



