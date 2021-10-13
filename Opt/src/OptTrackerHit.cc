#include "OptTrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<OptTrackerHit>* OptTrackerHitAllocator=0;


OptTrackerHit::OptTrackerHit()
 : G4VHit(),
   fTrackID(-1),
   fEdep(0.),
   fPos(G4ThreeVector()),
   fGlobalTime(0.)
{}


OptTrackerHit::~OptTrackerHit() {}


OptTrackerHit::OptTrackerHit(const OptTrackerHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  fGlobalTime = right.fGlobalTime;
}


const OptTrackerHit& OptTrackerHit::operator=(const OptTrackerHit& right)
{
  fTrackID   = right.fTrackID;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  fGlobalTime = right.fGlobalTime;

  return *this;
}


G4int OptTrackerHit::operator==(const OptTrackerHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}


void OptTrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}


void OptTrackerHit::Print()
{
  G4cout
     << "Hit " << fTrackID
     << ":   Edep = "
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << "  Time = "
     << std::setw(7) << G4BestUnit(fGlobalTime,"Time") << "." << G4endl;
}