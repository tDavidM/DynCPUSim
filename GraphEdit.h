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
class Tf_GraphEdit : public TForm
{
__published:	// Composants gérés par l'EDI
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

private:	// Déclarations de l'utilisateur
public:		// Déclarations de l'utilisateur
    __fastcall Tf_GraphEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_GraphEdit *f_GraphEdit;
//---------------------------------------------------------------------------
#endif
