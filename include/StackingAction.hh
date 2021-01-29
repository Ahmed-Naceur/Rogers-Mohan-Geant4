
#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4ThreeVector.hh"
#include "RunAction.hh"

class G4Track;

class StackingActionMessenger;

class StackingAction : public G4UserStackingAction
{
  public:
    static StackingAction* GetInstance();
    StackingAction(RunAction *theRunAction)  {
      pinst=this;
      runAction = theRunAction;
    };

    ~StackingAction(){};
  private:
    static StackingAction *pinst;
    RunAction *runAction;

  public:
    virtual G4ClassificationOfNewTrack  ClassifyNewTrack(const G4Track* fTrack);
};

#endif
