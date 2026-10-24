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
   (void)Sender;

   if (this->e_Name->Text == "") {
      ShowMessage("Must have a Name");
   }
   if (this->l_SaveName->Caption != this->e_Name->Text &&
       f_CPUNode->NodeNameExists(this->e_Name->Text)) {
      ShowMessage("Name Already Exists");
   } else {
      if (this->e_PosX->Text == "") {
         ShowMessage("Must have a X");
      } else if (this->e_PosY->Text == "") {
         ShowMessage("Must have a Y");
      } else {
         if (this->e_PinIDInUp->Text == "") {
            this->e_PinIDInUp->Text = "0";
         }
         if (this->e_PinIDInDown->Text == "") {
            this->e_PinIDInDown->Text = "0";
         }
         if (this->e_PinIDOutUp->Text == "") {
            this->e_PinIDOutUp->Text = "0";
         }
         if (this->e_PinIDOutDown->Text == "") {
            this->e_PinIDOutDown->Text = "0";
         }

         f_CPUNode->UpdateNode();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::b_deleteClick(TObject *Sender)
{
   (void)Sender;

   if (Application->MessageBox( L"Delete Node ?", L"Delete Node", MB_YESNO) == mrYes) {
      this->cb_Delete->Checked = true;
      f_CPUNode->UpdateNode();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::e_NameOutUpKeyPress(TObject *Sender, char &Key)
{
   (void)Sender;

   if (Key == VK_RETURN ) {
      this->b_UpdateClick(Sender);
   } else if (Key == VK_DELETE ) {
      this->b_delete->Click();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::FormShow(TObject *Sender)
{
   (void)Sender;

   this->Left = 5;
   this->Top = Screen->Height - (this->Height + 50);
}
//---------------------------------------------------------------------------
void Tf_GraphEdit::SetFocusName(void) { this->e_Name->SetFocus(); }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetName(void) { return this->e_Name->Text; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetName(String name) { this->e_Name->Text = name; }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPosX(void) { return StrToInt(this->e_PosX->Text); }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPosY(void) { return StrToInt(this->e_PosY->Text); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetPos(int X, int Y) { this->e_PosX->Text = IntToStr(X); this->e_PosY->Text = IntToStr(Y); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetType(NodeTypes type) { this->cb_Type->ItemIndex = static_cast<int>(type); }
//---------------------------------------------------------------------------
NodeTypes __fastcall Tf_GraphEdit::GetType(void) { return static_cast<NodeTypes>(this->cb_Type->ItemIndex); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetNameOutputUp(String name) { this->e_NameOutUp->Text = name; }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetNameOutputUp(void) { return this->e_NameOutUp->Text; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetNameOutputDown(String name) { this->e_NameOutDown->Text = name; }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetNameOutputDown(void) { return this->e_NameOutDown->Text; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetPinIDInputUp(int id) { this->e_PinIDInUp->Text = IntToStr(id); }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPinIDInputUp(void) { return StrToInt(this->e_PinIDInUp->Text); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetPinIDInputDown(int id) { this->e_PinIDInDown->Text = IntToStr(id); }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPinIDInputDown(void) { return StrToInt(this->e_PinIDInDown->Text); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetPinIDOutputUp(int id) { this->e_PinIDOutUp->Text = IntToStr(id); }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPinIDOutputUp(void) { return StrToInt(this->e_PinIDOutUp->Text); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetPinIDOutputDown(int id) { this->e_PinIDOutDown->Text = IntToStr(id); }
//---------------------------------------------------------------------------
int __fastcall Tf_GraphEdit::GetPinIDOutputDown(void) { return StrToInt(this->e_PinIDOutDown->Text); }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetIsDelete(bool val) { this->cb_Delete->Checked = val; }
//---------------------------------------------------------------------------
bool __fastcall Tf_GraphEdit::GetIsDelete(void) { return this->cb_Delete->Checked; }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetSaveName(void) { return this->l_SaveName->Caption; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetSaveName(String name) { this->l_SaveName->Caption = name; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetInternalID(int id) { this->l_InternalID->Caption = IntToStr(id); }
//---------------------------------------------------------------------------
//String __fastcall Tf_GraphEdit::GetInternalID(void) { return this->l_InternalID->Caption; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetNameLabelOutputUp(String name) { this->l_NameOutUp->Caption = name; }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetNameLabelOutputUp(void) { return this->l_NameOutUp->Caption; }
//---------------------------------------------------------------------------
void __fastcall Tf_GraphEdit::SetNameLabelOutputDown(String name) { this->l_NameOutDown->Caption = name; }
//---------------------------------------------------------------------------
String __fastcall Tf_GraphEdit::GetNameLabelOutputDown(void) { return this->l_NameOutDown->Caption; }
//---------------------------------------------------------------------------

//void __fastcall Tf_GraphEdit::Set( val) { this-> = val; }
//---------------------------------------------------------------------------
//__fastcall Tf_GraphEdit::Get(void) { return this->; }
//---------------------------------------------------------------------------

