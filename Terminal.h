//---------------------------------------------------------------------------

#ifndef TerminalH
#define TerminalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "Ram.h"
//---------------------------------------------------------------------------
class Tf_Terminal : public TForm
{
__published:
    TPanel *pScreen;
    TTimer *tRefresh;
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall tRefreshTimer(TObject *Sender);
private:
    String screenArray[51][20];

    int HexToInt(String Hex);
public:
    __fastcall Tf_Terminal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Terminal *f_Terminal;
//---------------------------------------------------------------------------
#endif
