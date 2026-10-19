//---------------------------------------------------------------------------

#ifndef ErrorListH
#define ErrorListH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class Tf_ErrorList : public TForm
{
__published:
   TButton *bOk;
   TMemo *mLog;
private:
public:
   void __fastcall InitList(TStringList* pErrorList);
   __fastcall Tf_ErrorList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_ErrorList *f_ErrorList;
//---------------------------------------------------------------------------
#endif
