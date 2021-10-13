//---------------------------------------------------------------------------

#ifndef MemoryH
#define MemoryH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Tf_Memory : public TForm
{
__published:	// Composants g�r�s par l'EDI
    TComboBox *cb_OpCode;
    TComboBox *cb_D;
    TComboBox *cb_C;
    TComboBox *cb_B;
    TEdit *e_Data;
    TLabel *l_Data;
    TRadioButton *rb_Bin;
    TRadioButton *rb_Dec;
    TRadioButton *rb_Hex;
    TButton *b_Delete;
    TButton *b_Edit;
    TButton *b_Add;
    TLabel *l_AddrTx;
    TLabel *l_AddrVal;
    TClientDataSet *cds_Mem;
    TDataSource *ds_Mem;
    TDBGrid *dbg_Mem;
    TIntegerField *cds_MemAddrDelta;
    TStringField *cds_MemHumData;
    TStringField *cds_MemCode;
    TIntegerField *cds_MemAddress;
    TIntegerField *cds_MemOpCode;
    TStringField *cds_MemData;
    TIntegerField *cds_MemDataType;
    TIntegerField *cds_MemRB;
    TIntegerField *cds_MemRC;
    TIntegerField *cds_MemRD;
    TIntegerField *cds_MemSort;
    TEdit *e_Sort;
    TLabel *l_Sort;
    TButton *b_Insert;
    TButton *b_Save;
    TButton *b_Load;
    TSaveDialog *sd_Mem;
    TOpenDialog *od_Mem;
    TButton *b_Import;
    void __fastcall cb_OpCodeChange(TObject *Sender);
    void __fastcall b_AddClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall cds_MemCalcFields(TDataSet *DataSet);
    void __fastcall b_EditClick(TObject *Sender);
    void __fastcall ds_MemDataChange(TObject *Sender, TField *Field);
    void __fastcall b_DeleteClick(TObject *Sender);
    void __fastcall e_DataKeyPress(TObject *Sender, char &Key);
    void __fastcall rb_BinClick(TObject *Sender);
    void __fastcall rb_DecClick(TObject *Sender);
    void __fastcall rb_HexClick(TObject *Sender);
    void __fastcall cds_MemAfterScroll(TDataSet *DataSet);
    void __fastcall b_InsertClick(TObject *Sender);
    void __fastcall b_SaveClick(TObject *Sender);
    void __fastcall b_LoadClick(TObject *Sender);
    void __fastcall e_DataExit(TObject *Sender);
private:	// D�clarations de l'utilisateur
    int LastDataType;
    int LastSelLine;

    void CreateLine(void);
    int DeltaToAddr(int Delta);
    String BinToHex(String Hex);
    String HexToDec(String Hex);
    String HexToBin(String Hex);
    String DecToHex(String Hex);

public:		// D�clarations de l'utilisateur
    __fastcall Tf_Memory(TComponent* Owner);
    void MoveAddrByDelta(int Delta);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Memory *f_Memory;
//---------------------------------------------------------------------------
#endif
