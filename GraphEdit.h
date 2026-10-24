//---------------------------------------------------------------------------

#ifndef GraphEditH
#define GraphEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "NodeCPU.h"
//---------------------------------------------------------------------------
enum NodeTypes : int;

class Tf_GraphEdit : public TForm
{
__published:
   TLabel *l_lIntid;
   TEdit *e_PosX;
   TLabel *l_InternalID;
   TLabel *l_lposx;
   TLabel *l_lposy;
   TEdit *e_PosY;
   TEdit *e_Name;
   TLabel *l_lname;
   TEdit *e_NameOutUp;
   TEdit *e_NameOutDown;
   TLabel *l_lNameUp;
   TLabel *l_lNameDown;
   TComboBox *cb_Type;
   TLabel *l_lType;
   TLabel *l_pinidinup;
   TLabel *l_lpinidindown;
   TLabel *l_lpinidoutup;
   TLabel *l_lpinidoutdown;
   TEdit *e_PinIDInUp;
   TEdit *e_PinIDInDown;
   TEdit *e_PinIDOutUp;
   TEdit *e_PinIDOutDown;
   TButton *b_Update;
   TButton *b_delete;
   TCheckBox *cb_Delete;
   TLabel *l_SaveName;
   TLabel *l_NameOutUp;
   TLabel *l_NameOutDown;
   void __fastcall b_UpdateClick(TObject *Sender);
   void __fastcall b_deleteClick(TObject *Sender);
   void __fastcall e_NameOutUpKeyPress(TObject *Sender, char &Key);
   void __fastcall FormShow(TObject *Sender);

private:
public:
   __fastcall Tf_GraphEdit(TComponent* Owner);

   void SetFocusName(void);

   String __fastcall GetName(void);
   void __fastcall SetName(String name);
   int __fastcall GetPosX(void);
   int __fastcall GetPosY(void);
   void __fastcall SetPos(int X, int Y);
   void __fastcall SetType(NodeTypes type);
   NodeTypes __fastcall GetType(void);
   void __fastcall SetNameOutputUp(String name);
   String __fastcall GetNameOutputUp(void);
   void __fastcall SetNameOutputDown(String name);
   String __fastcall GetNameOutputDown(void);
   void __fastcall SetPinIDInputUp(int id);
   int __fastcall GetPinIDInputUp(void);
   void __fastcall SetPinIDInputDown(int id);
   int __fastcall GetPinIDInputDown(void);
   void __fastcall SetPinIDOutputUp(int id);
   int __fastcall GetPinIDOutputUp(void);
   void __fastcall SetPinIDOutputDown(int id);
   int __fastcall GetPinIDOutputDown(void);
   void __fastcall SetIsDelete(bool val);
   bool __fastcall GetIsDelete(void);
   String __fastcall GetSaveName(void);
   void __fastcall SetSaveName(String name);
   void __fastcall SetInternalID(int id);
   //String __fastcall GetInternalID(void);
   void __fastcall SetNameLabelOutputUp(String name);
   String __fastcall GetNameLabelOutputUp(void);
   void __fastcall SetNameLabelOutputDown(String name);
   String __fastcall GetNameLabelOutputDown(void);

   //void __fastcall Set();
   //__fastcall Get(void);

};
//---------------------------------------------------------------------------
extern PACKAGE Tf_GraphEdit *f_GraphEdit;
//---------------------------------------------------------------------------
#endif
