//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_GraphEdit *f_GraphEdit;
//---------------------------------------------------------------------------
__fastcall Tf_GraphEdit::Tf_GraphEdit(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::b_UpdateClick(TObject *Sender)
{
  if(e_Name->Text == ""){ShowMessage("Must have a Name");}
  if(   l_SaveName->Caption != e_Name->Text
     && f_CPUNode->NodeNameExists(AnsiString(e_Name->Text).c_str()))
  {
     ShowMessage("Name Already Exists");
  }

  if(e_PosX->Text == ""){ShowMessage("Must have a X");}
  if(e_PosY->Text == ""){ShowMessage("Must have a Y");}

  if(e_PinIDInUp->Text == "")   {e_PinIDInUp->Text = "0";}
  if(e_PinIDInDown->Text == "") {e_PinIDInDown->Text = "0";}
  if(e_PinIDOutUp->Text == "")  {e_PinIDOutUp->Text = "0";}
  if(e_PinIDOutDown->Text == ""){ e_PinIDOutDown->Text = "0";}

  f_CPUNode->UpdateNode();
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::b_deleteClick(TObject *Sender)
{
  if (Application->MessageBox( L"Delete Node ?", L"Delete Node", MB_YESNO) == mrYes)
  {
    cb_Delete->Checked = true;
    f_CPUNode->UpdateNode();
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::e_NameOutUpKeyPress(TObject *Sender, char &Key)
{
  if(Key == VK_RETURN )
  {
    this->b_UpdateClick(Sender);
  }
  else if(Key == VK_DELETE )
  {
    this->b_delete->Click();
  }
}
//---------------------------------------------------------------------------
