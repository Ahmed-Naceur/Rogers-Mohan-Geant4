//using namespace std;

#include "StackingAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ios.hh"
#include "G4VTouchable.hh"

StackingAction*  StackingAction::pinst=NULL;

StackingAction*  StackingAction::GetInstance() 
{
  return pinst;
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track * aTrack) 
{
  G4ClassificationOfNewTrack classification = fUrgent;
  G4String particleName = aTrack->GetDefinition()->GetParticleName();
  if
    (
      particleName == "proton" || particleName == "neutron" ||
      particleName == "anti_proton" || particleName == "GenericIon " ||
      particleName == "alpha" || particleName == "kaon+" || particleName == "kaon-" ||
      particleName == "mu+" || particleName == "mu-" || 
      particleName == "pi+" || particleName == "pi-"
    ) 

  {
     classification = fKill;
  }

  if (aTrack->GetCreatorProcess() != NULL)
  {
    G4String particleName = aTrack->GetDefinition()->GetParticleName();

    if 
      (
      particleName == "proton" || particleName == "neutron" ||
      particleName == "anti_proton" || particleName == "GenericIon " ||
      particleName == "alpha" || particleName == "kaon+" || particleName == "kaon-" ||
      particleName == "mu+" || particleName == "mu-" || 
      particleName == "pi+" || particleName == "pi-"
      )

    {
       classification = fKill;
    }

  }

//  if (aTrack->GetCreatorProcess() != NULL) 
//  {
//    if (aTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay") 
//    {
//      G4String particleName = aTrack->GetDefinition()->GetParticleName();
//      if (particleName == "anti_nu_e" || particleName == "e-" || particleName == "e+" || particleName == "nu_e" || particleName == "alpha+") 
//      {
//        classification = fKill;
//      }
//      //else if(particleName == "gamma") 
//      //{
//      //  runAction->fNGammasCreated++;
//      //}
//    }
//  }

  return classification;
}

