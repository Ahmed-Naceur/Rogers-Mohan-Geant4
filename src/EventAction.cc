
//    **********************************
//    *                                *
//    *     EventAction Class          *
//    *                                *
//    **********************************
//

#include "EventAction.hh" // Statistical event by event accumulation of energy deposition
#include "RunAction.hh"   // Sums the event energy deposition 

#include "G4Event.hh"
#include "G4RunManager.hh"  // controls the flow of the program 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{} 


EventAction::~EventAction()
{}



//------------------------------------------------------------------------------
// START ACTION
//------------------------------------------------------------------------------
// This method is invoked before converting the primary particles to G4Track 
// objects. A typical use of this method would be to initialize and/or book  
// histograms for a particular event.
//------------------------------------------------------------------------------

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}


//------------------------------------------------------------------------------
// END ACTION
//------------------------------------------------------------------------------
// This method is invoked at the very end of event processing. 
// It is typically used for a simple analysis of the processed event.
// If the user wants to keep the currently processing event until the end of the 
// current run. The user can invoke fpEventManager->KeepTheCurrentEvent(); so 
// that it is kept in G4Run object. This should be quite useful if you simulate 
// quite many events and want to visualize only the most interest ones after the 
// long execution. Given the memory size of an event and its contents may be large, 
// it is the user’s responsibility not to keep unnecessary events.
//------------------------------------------------------------------------------
void EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in run action

  fRunAction->AddEdep(fEdep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
