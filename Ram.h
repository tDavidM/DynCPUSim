//---------------------------------------------------------------------------

#ifndef RamH
#define RamH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tf_Ram : public TForm
{
__published:	// Composants gérés par l'EDI
    TStringGrid *sg_Ram;
    TButton *b_Save;
    TButton *b_Load;
    TRadioButton *rb_Hex;
    TRadioButton *rb_Dec;
    TRadioButton *rb_Bin;
    TSaveDialog *sd_Ram;
    TOpenDialog *od_Ram;
    TClientDataSet *cds_Ram;
    TStringField *cds_RamField01;
    TStringField *cds_RamField23;
    TStringField *cds_RamField45;
    TStringField *cds_RamField67;
    TStringField *cds_RamField89;
    TStringField *cds_RamFieldAB;
    TStringField *cds_RamFieldCD;
    TStringField *cds_RamFieldEF;
    TIntegerField *cds_RamLine;
	TEdit *e_Page;
	TLabel *l_Page;
	TStringField *cds_RamPage;
	TButton *b_Import;
	TOpenDialog *od_Import;
	TUpDown *ud_Page;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall sg_RamKeyPress(TObject *Sender, char &Key);
    void __fastcall sg_RamExit(TObject *Sender);
    void __fastcall rb_BinClick(TObject *Sender);
    void __fastcall rb_DecClick(TObject *Sender);
    void __fastcall rb_HexClick(TObject *Sender);
    void __fastcall b_SaveClick(TObject *Sender);
    void __fastcall b_LoadClick(TObject *Sender);
    void __fastcall sg_RamSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall e_PageExit(TObject *Sender);
	void __fastcall b_ImportClick(TObject *Sender);
	void __fastcall ud_PageClick(TObject *Sender, TUDBtnType Button);
private:	// Déclarations de l'utilisateur
    int LastDataType;
	int LastX, LastY;
	String CurrentPage;

    String BinToHex(String Hex);
    String HexToDec(String Hex);
    String HexToBin(String Hex);
    String DecToHex(String Hex);
    void AddrToXY(String Addr, int &X, int &Y);
	void CleanUpData(int X, int Y);
	void SwapPage(String Current, String New);

public:		// Déclarations de l'utilisateur

	void Set(String Addr, String Value, String Page = '0');
	void Get(String Addr, char *Value, String Page = '0');
    __fastcall Tf_Ram(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Ram *f_Ram;
//---------------------------------------------------------------------------
#endif
