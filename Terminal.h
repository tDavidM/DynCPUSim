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

//---------------------------------------------------------------------------
class Tf_Terminal : public TForm
{
__published:
   TPanel *pScreen;
   TTimer *tRefresh;
   TSpeedButton *sbBoot;
   TSpeedButton *sbHalt;
   TPanel *pBuzy;
    TPanel *pInterrupt;
    TLabel *lValue;
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall tRefreshTimer(TObject *Sender);
   void __fastcall sbBootClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall sbHaltClick(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
private:
   void RefreshScreen(void);

   int screenArray[51][20];
   int HexToInt(String Hex);
public:
   __fastcall Tf_Terminal(TComponent* Owner);

   void IOOut(String cmdHex, String valueHex);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Terminal *f_Terminal;
//---------------------------------------------------------------------------
#endif
