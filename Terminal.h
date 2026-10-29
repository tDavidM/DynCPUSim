//---------------------------------------------------------------------------

#ifndef TerminalH
#define TerminalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>

#include "Ram.h"
#include "GraphIO.h"

//Idle=Gray, Awaiting=Yellow, Active=Red
enum InterruptStates: int {ITR_IDLE, ITR_AWAITING, ITR_ACTIVE};

//---------------------------------------------------------------------------
class Tf_Terminal : public TForm
{
__published:
   TPanel *pScreen;
   TTimer *tRefresh;
   TSpeedButton *sbBoot;
   TSpeedButton *sbHalt;
    TPanel *pBusy;
   TPanel *pInterrupt;
   TLabel *lValue;
    TPanel *pDebug;
    TLabel *lTimer;
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall tRefreshTimer(TObject *Sender);
   void __fastcall sbBootClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall sbHaltClick(TObject *Sender);
   void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall pDebugClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:
   int timerValue;
   int timerCmp;
   int clockCmp;
   int screenArray[51][20];
   int HexToInt(String Hex);
public:
   __fastcall Tf_Terminal(TComponent* Owner);

   void IOProcess(String cmdHex, String valueHex);
   void ClockTick(void);
   void RefreshScreen(void);
   void SetState(void);
   void ResetState(void);
   void __fastcall ToggleHalt(bool state);
   void __fastcall ToggleInterrupt(InterruptStates state);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Terminal *f_Terminal;
//---------------------------------------------------------------------------
#endif
