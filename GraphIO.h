//---------------------------------------------------------------------------

#ifndef GraphIOH
#define GraphIOH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "NodeCPU.h"
#include "Memory.h"
#include "Ram.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tf_GraphIO : public TForm
{
__published:	// Composants gérés par l'EDI
    TPanel *p_MemInput;
    TLabel *l_MemInput;
    TCheckBox *Pin41;
    TCheckBox *Pin42;
    TCheckBox *Pin43;
    TCheckBox *Pin44;
    TCheckBox *Pin45;
    TCheckBox *Pin46;
    TCheckBox *Pin47;
    TCheckBox *Pin48;
    TPanel *p_ROM;
    TLabel *l_rom;
    TPanel *p_Misc;
    TLabel *l_misc;
    TCheckBox *Pin50;
    TCheckBox *Pin1;
    TCheckBox *Pin2;
    TCheckBox *Pin3;
    TCheckBox *Pin4;
    TCheckBox *Pin8;
    TCheckBox *Pin7;
    TCheckBox *Pin6;
    TCheckBox *Pin5;
    TCheckBox *Pin16;
    TCheckBox *Pin15;
    TCheckBox *Pin14;
    TCheckBox *Pin13;
    TCheckBox *Pin12;
    TCheckBox *Pin11;
    TCheckBox *Pin10;
    TCheckBox *Pin9;
    TCheckBox *Pin52;
    TCheckBox *Pin51;
    TCheckBox *Pin53;
    TCheckBox *Pin54;
    TLabel *l_Romdata;
    TLabel *Label1;
    TCheckBox *Pin21;
    TCheckBox *Pin31;
    TCheckBox *Pin32;
    TCheckBox *Pin22;
    TCheckBox *Pin23;
    TCheckBox *Pin33;
    TCheckBox *Pin34;
    TCheckBox *Pin24;
    TCheckBox *Pin25;
    TCheckBox *Pin35;
    TCheckBox *Pin36;
    TCheckBox *Pin26;
    TCheckBox *Pin27;
    TCheckBox *Pin37;
    TCheckBox *Pin38;
    TCheckBox *Pin28;
    TLabel *l_MemOutput;
    TLabel *l_memflag;
    TLabel *Label2;
    TCheckBox *Pin29;
    TCheckBox *Pin30;
    TCheckBox *Pin39;
    TCheckBox *Pin40;
	TCheckBox *Pin70;
    TLabel *l_Line1;
   TLabel *l_Line5;
   TLabel *l_Line2;
   TLabel *l_Line3;
   TLabel *l_Line4;
    TCheckBox *Pin55;
    TCheckBox *Pin56;
    TCheckBox *Pin57;
    TCheckBox *Pin58;
	TLabel *Label3;
	TCheckBox *Pin61;
	TCheckBox *Pin62;
	TCheckBox *Pin63;
	TCheckBox *Pin64;
	TCheckBox *Pin65;
	TCheckBox *Pin66;
	TCheckBox *Pin67;
	TCheckBox *Pin68;
	TLabel *l_Line6;
	TCheckBox *Pin60;
	TLabel *Label4;
   TLabel *l_Line7;
	TCheckBox *Pin71;
	TCheckBox *Pin72;
	TCheckBox *Pin73;
	TCheckBox *Pin74;
	TCheckBox *Pin75;
	TCheckBox *Pin76;
	TCheckBox *Pin77;
	TCheckBox *Pin78;
   TLabel *l_PgrmCmp;
   TLabel *Label5;
   TLabel *l_Line8;
   TCheckBox *Pin81;
   TCheckBox *Pin89;
   TCheckBox *Pin82;
   TCheckBox *Pin90;
   TCheckBox *Pin83;
   TCheckBox *Pin91;
   TCheckBox *Pin84;
   TCheckBox *Pin92;
   TCheckBox *Pin85;
   TCheckBox *Pin93;
   TCheckBox *Pin86;
   TCheckBox *Pin94;
   TCheckBox *Pin87;
   TCheckBox *Pin95;
   TCheckBox *Pin88;
   TCheckBox *Pin96;
   TCheckBox *Pin80;
   TCheckBox *Pin19;
   TCheckBox *Pin20;
   TCheckBox *Pin18;
   TPanel *p_IOs;
   TLabel *l_IOs;
   TLabel *l_IOAin;
   TLabel *l_Line9;
   TCheckBox *Pin97;
   TCheckBox *Pin98;
   TCheckBox *Pin99;
   TCheckBox *Pin100;
   TCheckBox *Pin101;
   TCheckBox *Pin102;
   TCheckBox *Pin103;
   TCheckBox *Pin104;
   TCheckBox *Pin112;
   TCheckBox *Pin111;
   TLabel *l_Line10;
   TCheckBox *Pin110;
   TLabel *Label10;
   TCheckBox *Pin109;
   TCheckBox *Pin108;
   TCheckBox *Pin107;
   TCheckBox *Pin106;
   TCheckBox *Pin105;
   TCheckBox *Pin121;
   TCheckBox *Pin113;
   TCheckBox *Pin122;
   TCheckBox *Pin114;
   TLabel *Label11;
   TCheckBox *Pin123;
   TCheckBox *Pin115;
   TCheckBox *Pin124;
   TLabel *Label12;
   TCheckBox *Pin116;
   TCheckBox *Pin125;
   TLabel *l_Line11;
   TCheckBox *Pin126;
   TCheckBox *Pin117;
   TCheckBox *Pin118;
   TCheckBox *Pin127;
   TCheckBox *Pin128;
   TCheckBox *Pin120;
   TCheckBox *Pin119;
   TLabel *l_Line12;
   TLabel *Label6;
   TCheckBox *Pin17;
   TCheckBox *Pin49;
   TCheckBox *Pin59;
   TCheckBox *Pin69;
   TCheckBox *Pin79;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall b_ResetClick(TObject *Sender);
    void __fastcall Line1Click(TObject *Sender);
    void __fastcall Line10Click(TObject *Sender);
    void __fastcall Line2Click(TObject *Sender);
    void __fastcall Line9Click(TObject *Sender);
    void __fastcall Line12Click(TObject *Sender);
    void __fastcall Pin70Click(TObject *Sender);
    void __fastcall Pin50Click(TObject *Sender);
    void __fastcall Pin30Click(TObject *Sender);
    void __fastcall Pin40Click(TObject *Sender);
	void __fastcall Pin29Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Pin39Click(TObject *Sender);
	void __fastcall Line6Click(TObject *Sender);
   void __fastcall Pin60Click(TObject *Sender);
   void __fastcall Line7Click(TObject *Sender);
   void __fastcall l_romDblClick(TObject *Sender);
   void __fastcall Line8Click(TObject *Sender);
   void __fastcall Line11Click(TObject *Sender);
   void __fastcall Line3Click(TObject *Sender);
   void __fastcall Line4Click(TObject *Sender);
   void __fastcall Line5Click(TObject *Sender);
private:	// Déclarations de l'utilisateur
	char BinToHex(bool p1, bool p2, bool p3, bool p4 );

public:		// Déclarations de l'utilisateur
    __fastcall Tf_GraphIO(TComponent* Owner);
    bool DebugOutState;
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_GraphIO *f_GraphIO;
//---------------------------------------------------------------------------
#endif
