//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ErrorList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_ErrorList *f_ErrorList;
//---------------------------------------------------------------------------
__fastcall Tf_ErrorList::Tf_ErrorList(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_ErrorList::InitList(TStringList* pErrorList)
{
   for (int i = 0; i < pErrorList->Count; i++) {
      mLog->Lines->Add(pErrorList->Strings[i]);
   }
}
//---------------------------------------------------------------------------

