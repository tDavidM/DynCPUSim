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
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

//---------------------------------------------------------------------------
#include "GraphIO.h"
#include "ErrorList.h"

#define ERR_UNKNOWN_FILE "File not found: "
#define ERR_REDEFINED_MACRO "Macro redefined: "
#define ERR_REDEFINED_LABEL "Label redefined: "
#define ERR_REDEFINED_CONST "Constant redefined: "
#define ERR_NO_ENDTAG_MACRO "No end tag for macro: "
#define ERR_UNKNOWN_MACRO "Unknown macro: "

#define ERR_UNKNOWN_OPCODE "Unknown opcode: "
#define ERR_OPCODE_PARAM_EMPTY "Empty parameter: "
#define ERR_OPCODE_PARAM_MANY "Too many parameters: "
#define ERR_OPCODE_PARAM_COUNT "Wrong parameter count for opcode: "

#define ERR_UNKNOWN_CONST "Unknown constant: "
#define ERR_OPCODE_PARAM_TYPE "Wrong parameter type: "
#define ERR_UNKNOWN_LABEL "Unknown label: "
#define ERR_ABS_ADDR_FAR "Absolute Addr Out of Range : "
#define ERR_REL_ADDR_FAR "Relative Addr Out of Range : "


//---------------------------------------------------------------------------
class TInstruc
{
public:
   int ID, DataWidth, NbParam, DisplayOrder;
   String Name, OpCode, Descr, Comm;
   bool DataAct, FieldBAct, FieldCAct, FieldDAct;
   bool BlockAFix, BlockBFix, BlockCFix, BlockDFix;
   String BlockASource, BlockAVal, BlockBSource, BlockBVal,
          BlockCSource, BlockCVal, BlockDSource, BlockDVal;
   String HeadMnemo, HeadSuffix,
          Param1Type, Param1Source, Param1Suffix,
          Param2Type, Param2Source, Param2Suffix,
          Param3Type, Param3Source, Param3Suffix;

   TInstruc(int pID, String pName, String pOpCode, int pDisplayOrder);
};
//---------------------------------------------------------------------------
class Tf_Memory : public TForm
{
__published:
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
   TLabel *l_Width;
   TStringField *cds_MemMnemonic;
   TStringField *cds_MemAddrHex;
   TStringField *cds_MemCodeHex;
   TEdit *e_Comment;
   TStringField *cds_MemComment;
   TButton *b_Clear;
   TOpenDialog *od_Assembler;
   TCheckBox *cb_StepByStep;
   TButton *b_Next;
   TButton *b_BreakPoint;
   TBooleanField *cds_MemBreakPoint;
   TButton *b_boot;
   TStringField *cds_MemSource;
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
   void __fastcall dbg_MemDblClick(TObject *Sender);
   void __fastcall b_ClearClick(TObject *Sender);
   void __fastcall b_ImportClick(TObject *Sender);
   void __fastcall cb_StepByStepClick(TObject *Sender);
   void __fastcall b_NextClick(TObject *Sender);
   //void __fastcall dbg_MemDrawDataCell(TObject *Sender, const TRect &Rect, TField *Field, TGridDrawState State);
   void __fastcall b_BreakPointClick(TObject *Sender);
   void __fastcall b_bootClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall dbg_MemDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol,
          TColumn *Column, TGridDrawState State);
private:
   int LastDataType;
   int LastSelLine;
   int InstrucCmp;
   int ExecCmp;
   int currentExecLine;

   TList* InstrucList;

   void CreateLine(void);
   int DeltaToAddr(int Delta);
   String BinToHex(String Bin);
   String HexToDec(String Hex);
   String HexToBin(String Hex);
   String DecToHex(String pDec, int pMax=4095);
   String DataToBin(String pData, int pSize, TStringList *pLabelList, int pCurrLine, TStringList* pErrorList, TStringList* pMetaASMFile);

   void Parse4LabelConstBlank(TStringList *pASMFile, TStringList *pLabelList, TStringList *pConstList, TStringList* pErrorList, TStringList* pMetaASMFile);
   void Parse4MacroDefineAndInclude(TStringList *pASMFile, TList* pMacroList, TStringList *pMacroUsageCmp, TList* pMacroLabelList, String* pIncludes, TStringList* pErrorList, TStringList* pMetaASMFile);
   void Parse4MacroUsage(TStringList *pASMFile, TList* pMacroList, TStringList *pMacroUsageCmp, TList* pMacroLabelList, TStringList* pErrorList, TStringList* pMetaASMFile);

public:
   __fastcall Tf_Memory(TComponent* Owner);
   void MoveAddrByDelta(int Delta);
   void MoveAddrByAbsolute(int Addr);
   void LoadInstructionSet(_di_IXMLNode pInstructionSet);
   void ResetState(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tf_Memory *f_Memory;
//---------------------------------------------------------------------------
#endif
