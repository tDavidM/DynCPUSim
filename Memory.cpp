//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Memory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_Memory *f_Memory;

//---------------------------------------------------------------------------
//Constructor for an Instruction
TInstruc::TInstruc(int pID, String pName, String pOpCode, int pDisplayOrder)
{
   this->ID           = pID;
   this->Name         = pName;
   this->OpCode       = pOpCode;
   this->DisplayOrder = pDisplayOrder;

   this->DataWidth = 8;
   this->NbParam   = 0;

   this->DataAct   = false;
   this->FieldBAct = false;
   this->FieldCAct = false;
   this->FieldDAct = false;

   this->BlockAFix = false;
   this->BlockBFix = false;
   this->BlockCFix = false;
   this->BlockDFix = false;

   this->BlockASource = "";
   this->BlockAVal    = "0000";
   this->BlockBSource = "";
   this->BlockBVal    = "0000";
   this->BlockCSource = "";
   this->BlockCVal    = "0000";
   this->BlockDSource = "";
   this->BlockDVal    = "0000";

   this->HeadMnemo    = "NOP";
   this->HeadSuffix   = " () ";
   this->Param1Type   = "";
   this->Param1Source = "";
   this->Param1Suffix = "";
   this->Param2Type   = "";
   this->Param2Source = "";
   this->Param2Suffix = "";
   this->Param3Type   = "";
   this->Param3Source = "";
   this->Param3Suffix = "";
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
__fastcall Tf_Memory::Tf_Memory(TComponent* Owner)
    : TForm(Owner)
{
   this->InstrucList = new TList;
   this->currentExecLine = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cb_OpCodeChange(TObject *Sender)
{
   (void)Sender;

   TInstruc* Instruc;

   Instruc = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
   this->cb_OpCode->Hint = Instruc->Comm;
   this->l_Width->Caption = "MaxData: " + IntToStr(Instruc->DataWidth) + " bits";

   this->e_Data->Enabled = Instruc->DataAct;
   this->l_Data->Enabled = Instruc->DataAct;
   this->rb_Bin->Enabled = Instruc->DataAct;
   this->rb_Dec->Enabled = Instruc->DataAct;
   this->rb_Hex->Enabled = Instruc->DataAct;

   this->cb_B->Enabled = Instruc->FieldBAct;
   this->cb_C->Enabled = Instruc->FieldCAct;
   this->cb_D->Enabled = Instruc->FieldDAct;
}
//---------------------------------------------------------------------------
String Tf_Memory::BinToHex(String Bin)
{
        if (Bin == "1111") { return "F"; }
   else if (Bin == "1110") { return "E"; }
   else if (Bin == "1101") { return "D"; }
   else if (Bin == "1100") { return "C"; }
   else if (Bin == "1011") { return "B"; }
   else if (Bin == "1010") { return "A"; }
   else if (Bin == "1001") { return "9"; }
   else if (Bin == "1000") { return "8"; }
   else if (Bin == "0111") { return "7"; }
   else if (Bin == "0110") { return "6"; }
   else if (Bin == "0101") { return "5"; }
   else if (Bin == "0100") { return "4"; }
   else if (Bin == "0011") { return "3"; }
   else if (Bin == "0010") { return "2"; }
   else if (Bin == "0001") { return "1"; }
   else if (Bin == "0000") { return "0"; }
   else { return "0"; } // =^.^= here's a kitty
}
//---------------------------------------------------------------------------
String Tf_Memory::HexToDec(String Hex)
{
         if (Hex == "0") { return "0"; }
    else if (Hex == "1") { return "1"; }
    else if (Hex == "2") { return "2"; }
    else if (Hex == "3") { return "3"; }
    else if (Hex == "4") { return "4"; }
    else if (Hex == "5") { return "5"; }
    else if (Hex == "6") { return "6"; }
    else if (Hex == "7") { return "7"; }
    else if (Hex == "8") { return "8"; }
    else if (Hex == "9") { return "9"; }
    else if (Hex == "A") { return "10"; }
    else if (Hex == "B") { return "11"; }
    else if (Hex == "C") { return "12"; }
    else if (Hex == "D") { return "13"; }
    else if (Hex == "E") { return "14"; }
    else if (Hex == "F") { return "15"; }
    else { return "0"; }
}
//---------------------------------------------------------------------------
String Tf_Memory::HexToBin(String Hex)
{
         if (Hex == "0") { return "0000"; }
    else if (Hex == "1") { return "0001"; }
    else if (Hex == "2") { return "0010"; }
    else if (Hex == "3") { return "0011"; }
    else if (Hex == "4") { return "0100"; }
    else if (Hex == "5") { return "0101"; }
    else if (Hex == "6") { return "0110"; }
    else if (Hex == "7") { return "0111"; }
    else if (Hex == "8") { return "1000"; }
    else if (Hex == "9") { return "1001"; }
    else if (Hex == "A") { return "1010"; }
    else if (Hex == "B") { return "1011"; }
    else if (Hex == "C") { return "1100"; }
    else if (Hex == "D") { return "1101"; }
    else if (Hex == "E") { return "1110"; }
    else if (Hex == "F") { return "1111"; }
    else { return "0"; }
}
//---------------------------------------------------------------------------
String Tf_Memory::DecToHex(String pDec, int pMax)
{
   int Dec = StrToInt(pDec);
   int Div;
   String Stack = "";

   if (Dec < 0) {
      return "0";
   }

   if (Dec > pMax) {
      return "0";
   }

   if (Dec > 4095) {
      Div = Dec / 4095;
      Dec = Dec % 4095;
      switch (Div) {
         case 0:{Stack  = "0"; break;}
         case 1:{Stack  = "1"; break;}
         case 2:{Stack  = "2"; break;}
         case 3:{Stack  = "3"; break;}
         case 4:{Stack  = "4"; break;}
         case 5:{Stack  = "5"; break;}
         case 6:{Stack  = "6"; break;}
         case 7:{Stack  = "7"; break;}
         case 8:{Stack  = "8"; break;}
         case 9:{Stack  = "9"; break;}
         case 10:{Stack = "A"; break;}
         case 11:{Stack = "B"; break;}
         case 12:{Stack = "C"; break;}
         case 13:{Stack = "D"; break;}
         case 14:{Stack = "E"; break;}
         case 15:{Stack = "F"; break;}
      }
   }
   if (Dec > 255) {
      Div = Dec / 256;
      Dec = Dec % 256;
      switch (Div) {
         case 0:{Stack  = Stack + "0"; break;}
         case 1:{Stack  = Stack + "1"; break;}
         case 2:{Stack  = Stack + "2"; break;}
         case 3:{Stack  = Stack + "3"; break;}
         case 4:{Stack  = Stack + "4"; break;}
         case 5:{Stack  = Stack + "5"; break;}
         case 6:{Stack  = Stack + "6"; break;}
         case 7:{Stack  = Stack + "7"; break;}
         case 8:{Stack  = Stack + "8"; break;}
         case 9:{Stack  = Stack + "9"; break;}
         case 10:{Stack = Stack + "A"; break;}
         case 11:{Stack = Stack + "B"; break;}
         case 12:{Stack = Stack + "C"; break;}
         case 13:{Stack = Stack + "D"; break;}
         case 14:{Stack = Stack + "E"; break;}
         case 15:{Stack = Stack + "F"; break;}
      }
   }
   Div = Dec / 16;
   switch (Div) {
      case 0:{Stack  = Stack + "0"; break;}
      case 1:{Stack  = Stack + "1"; break;}
      case 2:{Stack  = Stack + "2"; break;}
      case 3:{Stack  = Stack + "3"; break;}
      case 4:{Stack  = Stack + "4"; break;}
      case 5:{Stack  = Stack + "5"; break;}
      case 6:{Stack  = Stack + "6"; break;}
      case 7:{Stack  = Stack + "7"; break;}
      case 8:{Stack  = Stack + "8"; break;}
      case 9:{Stack  = Stack + "9"; break;}
      case 10:{Stack = Stack + "A"; break;}
      case 11:{Stack = Stack + "B"; break;}
      case 12:{Stack = Stack + "C"; break;}
      case 13:{Stack = Stack + "D"; break;}
      case 14:{Stack = Stack + "E"; break;}
      case 15:{Stack = Stack + "F"; break;}
   }
   Div = Dec % 16;
   switch (Div) {
      case 0:{Stack  = Stack + "0"; break;}
      case 1:{Stack  = Stack + "1"; break;}
      case 2:{Stack  = Stack + "2"; break;}
      case 3:{Stack  = Stack + "3"; break;}
      case 4:{Stack  = Stack + "4"; break;}
      case 5:{Stack  = Stack + "5"; break;}
      case 6:{Stack  = Stack + "6"; break;}
      case 7:{Stack  = Stack + "7"; break;}
      case 8:{Stack  = Stack + "8"; break;}
      case 9:{Stack  = Stack + "9"; break;}
      case 10:{Stack = Stack + "A"; break;}
      case 11:{Stack = Stack + "B"; break;}
      case 12:{Stack = Stack + "C"; break;}
      case 13:{Stack = Stack + "D"; break;}
      case 14:{Stack = Stack + "E"; break;}
      case 15:{Stack = Stack + "F"; break;}
   }
   return Stack;
}
//---------------------------------------------------------------------------
void Tf_Memory::CreateLine(void)
{
   String BasePrefix;
   int BaseId, WidthHex;
   String BinData, HexData, InstrucText, InstrucCode;
   TInstruc* Instruc;

   Instruc = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
   WidthHex = Instruc->DataWidth/4;

   if (this->rb_Bin->Checked) {
      BasePrefix = "0b";
      BaseId     = 0;
      while (BinData.Length() < Instruc->DataWidth) {
         BinData = "0" + BinData;
      }
      BinData    = this->e_Data->Text.SubString(this->e_Data->Text.Length()-Instruc->DataWidth+1, Instruc->DataWidth);
   } else if (this->rb_Dec->Checked) {
      BasePrefix = "0d";
      BaseId     = 1;
      this->e_Data->Text = this->e_Data->Text.UpperCase();
      HexData    = DecToHex(this->e_Data->Text);
      while (HexData.Length() < WidthHex) {
         HexData = "0" + HexData;
      }
      HexData    = HexData.SubString(HexData.Length()-WidthHex+1, WidthHex);
      for (int i=1; i<=WidthHex; i++) {
         BinData = BinData + HexToBin(HexData.SubString(i,1));
     }
   } else {
      BasePrefix = "0x";
      BaseId     = 2;
      this->e_Data->Text = this->e_Data->Text.UpperCase();
      HexData    = this->e_Data->Text;
      while (HexData.Length() < WidthHex) {
         HexData = "0" + HexData;
      }
      HexData    = HexData.SubString(HexData.Length()-WidthHex+1, WidthHex);
      for (int i=1; i<=WidthHex; i++) {
         BinData = BinData + HexToBin(HexData.SubString(i,1));
      }
   }

   this->cds_MemOpCode->AsInteger   = this->cb_OpCode->ItemIndex;
   this->cds_MemMnemonic->AsString  = Instruc->HeadMnemo;
   this->cds_MemData->AsString      = this->e_Data->Text;
   this->cds_MemComment->AsString   = this->e_Comment->Text;
   this->cds_MemRB->AsInteger       = StrToInt(this->cb_B->ItemIndex);
   this->cds_MemRC->AsInteger       = StrToInt(this->cb_C->ItemIndex);
   this->cds_MemRD->AsInteger       = StrToInt(this->cb_D->ItemIndex);
   this->cds_MemDataType->AsInteger = BaseId;
   this->cds_MemBreakPoint->AsBoolean = false;

   InstrucText = Instruc->Name + Instruc->HeadSuffix;
   if (Instruc->NbParam > 0) {
      InstrucText = InstrucText + Instruc->Param1Type;
      if (Instruc->Param1Source == "B") {
         InstrucText = InstrucText + this->cb_B->Text + Instruc->Param1Suffix;
      } else if (Instruc->Param1Source == "C") {
         InstrucText = InstrucText + this->cb_C->Text + Instruc->Param1Suffix;
      } else if (Instruc->Param1Source == "D") {
         InstrucText = InstrucText + this->cb_D->Text + Instruc->Param1Suffix;
      } else if (Instruc->Param1Source == "Data") {
         InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param1Suffix;
      }

      if (Instruc->NbParam > 1) {
         InstrucText = InstrucText + Instruc->Param2Type;
         if (Instruc->Param2Source == "B") {
            InstrucText = InstrucText + this->cb_B->Text + Instruc->Param2Suffix;
         } else if (Instruc->Param2Source == "C") {
            InstrucText = InstrucText + this->cb_C->Text + Instruc->Param2Suffix;
         } else if (Instruc->Param2Source == "D"){
            InstrucText = InstrucText + this->cb_D->Text + Instruc->Param2Suffix;
         } else if (Instruc->Param2Source == "Data") {
            InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param2Suffix;
         }

         if (Instruc->NbParam > 2) {
            InstrucText = InstrucText + Instruc->Param3Type;
            if (Instruc->Param3Source == "B") {
               InstrucText = InstrucText + this->cb_B->Text + Instruc->Param3Suffix;
            } else if (Instruc->Param3Source == "C") {
               InstrucText = InstrucText + this->cb_C->Text + Instruc->Param3Suffix;
            } else if (Instruc->Param3Source == "D") {
               InstrucText = InstrucText + this->cb_D->Text + Instruc->Param3Suffix;
            } else if (Instruc->Param3Source == "Data") {
               InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param3Suffix;
            }
         }
      }
   }
   this->cds_MemHumData->AsString = InstrucText;

   InstrucCode = "";
   if (Instruc->BlockAFix) {
      InstrucCode = Instruc->BlockAVal;
   } else if (Instruc->BlockASource == "B") {
      InstrucCode = HexToBin(this->cb_B->Text);
   } else if (Instruc->BlockASource == "C") {
      InstrucCode = HexToBin(this->cb_C->Text);
   } else if (Instruc->BlockASource == "D") {
      InstrucCode = HexToBin(this->cb_D->Text);
   } else if (Instruc->BlockASource == "Data") {
      InstrucCode = BinData;
   }

   if (Instruc->BlockBFix) {
      InstrucCode = InstrucCode + Instruc->BlockBVal;
   } else if (Instruc->BlockBSource == "B") {
      InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
   } else if (Instruc->BlockBSource == "C") {
      InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
   } else if (Instruc->BlockBSource == "D") {
      InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
   } else if (Instruc->BlockBSource == "Data") {
      InstrucCode = InstrucCode + BinData;
   }

   if (Instruc->BlockCFix) {
      InstrucCode = InstrucCode + Instruc->BlockCVal;
   } else if (Instruc->BlockCSource == "B") {
      InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
   } else if (Instruc->BlockCSource == "C") {
      InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
   } else if (Instruc->BlockCSource == "D") {
      InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
   } else if (Instruc->BlockCSource == "Data") {
      InstrucCode = InstrucCode + BinData;
   }

   if (Instruc->BlockDFix) {
      InstrucCode = InstrucCode + Instruc->BlockDVal;
   } else if (Instruc->BlockDSource == "B") {
      InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
   } else if (Instruc->BlockDSource == "C") {
      InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
   } else if (Instruc->BlockDSource == "D") {
      InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
   } else if (Instruc->BlockDSource == "Data") {
      InstrucCode = InstrucCode + BinData;
   }

   this->cds_MemCode->AsString     = InstrucCode;
   this->cds_MemCodeHex->AsString  = BinToHex(InstrucCode.SubString(1,4)) + BinToHex(InstrucCode.SubString(5,4)) +
                                     BinToHex(InstrucCode.SubString(9,4)) + BinToHex(InstrucCode.SubString(13,4));

}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_AddClick(TObject *Sender)
{
   (void)Sender;

   this->cds_Mem->Append();
   //this->cds_MemSort->AsInteger = this->cds_Mem->RecordCount + 1;
   //this->e_Sort->Text = this->cds_MemSort->AsString;
   //this->e_Sort->Enabled = true;
   this->CreateLine();
   this->cds_Mem->Post();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::FormCreate(TObject *Sender)
{
   (void)Sender;

   this->cb_OpCode->Clear();

   this->cds_Mem->CreateDataSet();
   this->cds_Mem->Open();
   //this->rb_Hex->Checked = true;
   this->LastDataType = 2;
   this->LastSelLine = 0;
   //this->cb_OpCode->ItemIndex = this->cb_OpCode->Items->IndexOf("NOP( )"); //30;
   //this->b_Add->Click();

   this->ExecCmp = 0;
   this->currentExecLine = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   (void)Sender;

   CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cds_MemCalcFields(TDataSet *DataSet)
{
   (void)DataSet;

   this->cds_MemAddress->AsInteger = this->cds_Mem->RecNo - 1;
   this->cds_MemAddrHex->AsString  = DecToHex(IntToStr(this->cds_Mem->RecNo - 1), 65535);
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::dbg_MemDblClick(TObject *Sender)
{
   (void)Sender;

   this->cds_MemAddress->Visible = ! this->cds_MemAddress->Visible;
   this->cds_MemAddrHex->Visible = ! this->cds_MemAddrHex->Visible;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_InsertClick(TObject *Sender)
{
  (void)Sender;

  //int SaveSortVal = this->cds_MemSort->AsInteger;
  this->cds_Mem->Insert();
  //this->cds_MemSort->AsInteger = SaveSortVal;
  //this->e_Sort->Text = this->cds_MemSort->AsString;
  //this->e_Sort->Enabled = true;
  this->CreateLine();
  this->cds_Mem->Post();

  /*
  TBookmark CurrAddr;

  this->cds_Mem->DisableControls();
  CurrAddr = this->cds_Mem->GetBookmark();
  while (!cds_Mem->Eof) {
    this->cds_Mem->Edit();
    SaveSortVal += 1;
    this->cds_MemSort->AsInteger = SaveSortVal;
    this->cds_Mem->Post();
    this->cds_Mem->Next();
  }
  this->cds_Mem->go GotoBookmark(CurrAddr);

  this->cds_Mem->EnableControls();
  */
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_EditClick(TObject *Sender)
{
   (void)Sender;

   this->cds_Mem->Edit();
   //this->cds_MemSort->AsString = this->e_Sort->Text;
   this->CreateLine();
   this->cds_Mem->Post();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::ds_MemDataChange(TObject *Sender, TField *Field)
{
   (void)Sender;
   (void)Field;

   if (this->cds_Mem->State == dsBrowse) {
      //this->e_Sort->Text         = this->cds_MemSort->AsString;
      //this->e_Sort->Enabled      = true;
      this->cb_OpCode->ItemIndex = this->cds_MemOpCode->AsInteger;
      this->e_Comment->Text      = this->cds_MemComment->AsString;
      this->cb_B->ItemIndex      = this->cds_MemRB->AsInteger;
      this->cb_C->ItemIndex      = this->cds_MemRC->AsInteger;
      this->cb_D->ItemIndex      = this->cds_MemRD->AsInteger;
      switch (this->cds_MemDataType->AsInteger) {
         case 0: {
            this->rb_Bin->Checked = true;
            break;
         }
         case 1: {
            this->rb_Dec->Checked = true;
            break;
         }
         case 2: {
            this->rb_Hex->Checked = true;
            break;
         }
      }
      this->e_Data->Text         = this->cds_MemData->AsString;
      if (this->cb_OpCode->Items->Count != 0) {
         this->cb_OpCodeChange(Sender);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_DeleteClick(TObject *Sender)
{
   (void)Sender;

   if (this->cds_Mem->RecordCount > 1) {
      if (Application->MessageBox( L"Delete Instruction ?", L"Instruction Node", MB_YESNO) == mrYes) {
         this->cds_Mem->Delete();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::e_DataKeyPress(TObject *Sender, char &Key)
{
   (void)Sender;

   if (Key != VK_RETURN && Key != VK_TAB && Key != VK_LEFT && Key != VK_RIGHT && Key != VK_BACK && Key != VK_CLEAR &&
       Key != VK_ESCAPE && Key != VK_DELETE  && Key != VK_HOME && Key != VK_END && Key != VK_INSERT && Key != VK_CANCEL) {
      if (this->rb_Bin->Checked) {
         if ( Key != '0' && Key != '1') {
            Key = 0;
         }
      } else if (this->rb_Dec->Checked) {
         if ( Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
              Key != '8' && Key != '9') {
            Key = 0;
              }
      } else {
         if ( Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
              Key != '8' && Key != '9' && Key != 'A' && Key != 'B' && Key != 'C' && Key != 'D' && Key != 'E' && Key != 'F' &&
              Key != 'a' && Key != 'b' && Key != 'c' && Key != 'd' && Key != 'e' && Key != 'f') {
            Key = 0;
         }
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_BinClick(TObject *Sender)
{
   (void)Sender;

   int WidthHex;
   String BinData;
   TInstruc* Instruc;

   if (this->cb_OpCode->ItemIndex >= 0) {
      Instruc  = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
      WidthHex = Instruc->DataWidth/4;
  
      if (this->e_Data->Text != "") {
         if (this->LastDataType == 1) {
            this->e_Data->Text = this->e_Data->Text.UpperCase();
            this->e_Data->Text = DecToHex(this->e_Data->Text);
            while (this->e_Data->Text.Length() < WidthHex) {
               this->e_Data->Text = "0" + this->e_Data->Text;
            }
            for (int i=1; i<=WidthHex; i++) {
               BinData = BinData + HexToBin(this->e_Data->Text.SubString(i,1));
            }
            this->e_Data->Text = BinData;
         } else if (this->LastDataType == 2) {
            this->e_Data->Text = this->e_Data->Text.UpperCase();
            for (int i=1; i<=WidthHex; i++) {
               BinData = BinData + HexToBin(this->e_Data->Text.SubString(i,1));
            }
            this->e_Data->Text = BinData;
         }
      }
      this->LastDataType = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_DecClick(TObject *Sender)
{
   (void)Sender;

   int WidthHex, DecData = 0, Muliplier;
   String BinData, HexData;
   TInstruc* Instruc;

   if (this->cb_OpCode->ItemIndex >= 0) {
      Instruc  = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
      WidthHex = Instruc->DataWidth/4;

      if (this->e_Data->Text != "") {
         if (this->LastDataType == 0) {
            for (int i=1; i<=Instruc->DataWidth; i+=4) {
               HexData = HexData + BinToHex(this->e_Data->Text.SubString(i,4));
            }
            this->e_Data->Text = HexData;
            for (int i=1; i<=WidthHex; i++) {
               Muliplier = WidthHex==3?(i==1?256:i==2?16:1):WidthHex==2?(i==1?16:1):1;
               DecData = DecData + (StrToInt(HexToDec(this->e_Data->Text.SubString(i,1))) * Muliplier );
            }
            this->e_Data->Text = IntToStr(DecData);
         } else if (this->LastDataType == 2) {
            this->e_Data->Text = this->e_Data->Text.UpperCase();
            for (int i=1; i<=WidthHex; i++) {
               Muliplier = WidthHex==3?(i==1?256:i==2?16:1):WidthHex==2?(i==1?16:1):1;
               DecData = DecData + (StrToInt(HexToDec(this->e_Data->Text.SubString(i,1))) * Muliplier );
            }
            this->e_Data->Text = IntToStr(DecData);
         }
      }
      this->LastDataType = 1;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_HexClick(TObject *Sender)
{
   (void)Sender;

   String HexData;
   TInstruc* Instruc;

   if (this->cb_OpCode->ItemIndex >= 0) {
      Instruc  = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];

      if (this->e_Data->Text != "") {
         if (this->LastDataType == 0) {
            for (int i=1; i<=Instruc->DataWidth; i+=4) {
               HexData = HexData + BinToHex(this->e_Data->Text.SubString(i,4));
            }
            this->e_Data->Text = HexData;
         } else if (this->LastDataType == 1) {
            this->e_Data->Text = DecToHex(this->e_Data->Text);
            while (this->e_Data->Text.Length() < (Instruc->DataWidth/4)) {
               this->e_Data->Text = "0" + this->e_Data->Text;
            }
         }
      }
      this->LastDataType = 2;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::cds_MemAfterScroll(TDataSet *DataSet)
{
   (void)DataSet;

   int Delta = this->cds_Mem->RecNo - this->LastSelLine;

   if (Delta < 128 && Delta > -128) {
      if (Delta >=0) {
         Delta = (Delta-1)+128;
      } else {
         Delta = abs(Delta);
         Delta = 128 - Delta;
      }
      this->l_AddrVal->Caption = DecToHex(IntToStr(Delta) );
   } else {
      this->l_AddrVal->Caption = "0x____";
   }
   this->LastSelLine = this->cds_Mem->RecNo;
}
//---------------------------------------------------------------------------
int Tf_Memory::DeltaToAddr(int Delta)
{
   int Target = 0;

   if (Delta <= 127 && Delta >= 0) {
      Delta = 128 - Delta;
      Target = this->cds_MemAddress->AsInteger - Delta;

      while (Target < 0) {
         Target = Target + this->cds_Mem->RecordCount;
      }
   } else if (Delta >= 128 && Delta <= 255) {
      Delta = (Delta - 128) + 1;
      Target = this->cds_MemAddress->AsInteger + Delta;

      while (Target >= this->cds_Mem->RecordCount) {
         Target = Target - this->cds_Mem->RecordCount;
      }
   }
   return Target;
}
//---------------------------------------------------------------------------
void Tf_Memory::MoveAddrByDelta(int Delta)
{
   this->cds_Mem->DisableControls();
   this->cds_Mem->First();

   if (this->cds_Mem->RecordCount > 1 ) {
      int Target = this->currentExecLine;
      while (!this->cds_Mem->Eof && this->cds_MemAddress->AsInteger != Target) {
         this->cds_Mem->Next();
      }

      Target = DeltaToAddr(Delta);
      while (!this->cds_Mem->Eof && this->cds_MemAddress->AsInteger != Target) {
         this->cds_Mem->Next();
      }
      this->currentExecLine = Target;
   }

   /*TByteDynArray Location = cds_Mem->GetBookmark();
   if (cds_Mem->BookmarkValid(Location)) {
      cds_Mem->GotoBookmark(Location);
   }
   cds_Mem->FreeBookmark(Location);*/

   char instruction[17];
   strncpy(instruction, AnsiString(this->cds_MemCode->AsString).c_str(),17);
   instruction[16] = '\0';
   f_GraphIO->SetInstruction(instruction);

   this->cds_Mem->EnableControls();
   this->ExecCmp++;
   f_GraphIO->l_PgrmCmp->Caption = "PgrmCmp: " + IntToStr(this->ExecCmp);

   if (this->cds_MemBreakPoint->AsBoolean) {
     f_GraphIO->Pin29->Checked = true;
     if (!f_CPUNode->cb_ActiveDraw->Checked) {
        f_CPUNode->CallDrawArea(1);
     }
   }
}
//---------------------------------------------------------------------------
void Tf_Memory::MoveAddrByAbsolute(int Addr)
{
   this->cds_Mem->DisableControls();
   this->cds_Mem->First();

   if (this->cds_Mem->RecordCount > 1 ) {
      while (!this->cds_Mem->Eof && this->cds_MemAddress->AsInteger != Addr) {
         this->cds_Mem->Next();
      }
      this->currentExecLine = Addr;
   }

   /*TByteDynArray Location = cds_Mem->GetBookmark();
   if (cds_Mem->BookmarkValid(Location)) {
      cds_Mem->GotoBookmark(Location);
   }
   cds_Mem->FreeBookmark(Location);*/

   char instruction[17];
   strncpy(instruction, AnsiString(this->cds_MemCode->AsString).c_str(),17);
   instruction[16] = '\0';
   f_GraphIO->SetInstruction(instruction);

   this->cds_Mem->EnableControls();
   this->ExecCmp++;
   f_GraphIO->l_PgrmCmp->Caption = "PgrmCmp: " + IntToStr(this->ExecCmp);

   if (this->cds_MemBreakPoint->AsBoolean) {
      f_GraphIO->Pin29->Checked = true;
      b_Next->Enabled = true;
      if (!f_CPUNode->cb_ActiveDraw->Checked) {
         f_CPUNode->CallDrawArea(1);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_SaveClick(TObject *Sender)
{
   (void)Sender;

   if (this->sd_Mem->Execute()) {
      if (this->sd_Mem->FileName != "") {
         TBookmark CurrAddr;

         this->cds_Mem->MergeChangeLog();
         //this->cds_Save->FieldDefs = this->cds_Mem->FieldDefs;
         //this->cds_Save->co
         this->cds_Mem->LogChanges = false;

         this->cds_Mem->DisableControls();
         CurrAddr = this->cds_Mem->GetBookmark();
         this->cds_Mem->First();
         while (!this->cds_Mem->Eof) {
            this->cds_Mem->Edit();
            //this->cds_MemAddrDelta->AsInteger = this->cds_Mem->RecNo;
            this->cds_MemSort->AsInteger = this->cds_Mem->RecNo;
            this->cds_Mem->Post();
            this->cds_Mem->Next();
         }
         this->cds_Mem->GotoBookmark(CurrAddr);
         this->cds_Mem->First();

         //this->cds_Mem->ApplyUpdates(0);
         this->cds_Mem->MergeChangeLog();
         this->cds_Mem->LogChanges = false;

         this->cds_Mem->SaveToFile(this->sd_Mem->FileName, dfXML);
         this->cds_Mem->LogChanges = false;
         this->cds_Mem->EnableControls();
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_LoadClick(TObject *Sender)
{
   (void)Sender;

   if (this->od_Mem->Execute()) {
      if (this->od_Mem->FileName != "") {
         this->cds_Mem->LogChanges = false;
         this->cds_Mem->LoadFromFile(this->od_Mem->FileName);
         this->cds_Mem->LogChanges = false;

         this->ExecCmp = 0;
      }
   }
   //this->cds_Mem->IndexFieldNames = "Sort";
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::e_DataExit(TObject *Sender)
{
   (void)Sender;

   int WidthHex, MaxDecimal;
   TInstruc* Instruc;
   String Data = this->e_Data->Text;

   Instruc = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
   WidthHex   = Instruc->DataWidth/4;
   MaxDecimal = (2<<(Instruc->DataWidth-1))-1;
      if (this->rb_Bin->Checked) {
         if (Data.Length() < Instruc->DataWidth) {
            while (Data.Length() < Instruc->DataWidth) {
               Data = "0" + Data;
            }
         } else {
            Data = Data.SubString(Data.Length()-Instruc->DataWidth+1, Instruc->DataWidth);
            //Data = Data.SubString(1,Instruc->DataWidth);
         }
   } else if (this->rb_Dec->Checked) {
      Data = Data.SubString(1,WidthHex+1); // 16, 256, 4096
      if (Data == "") {
         Data = "0";
      } else if (StrToInt(Data) > MaxDecimal) {
         Data = MaxDecimal;
      }
   } else {
      if (Data.Length() < WidthHex) {
         while (Data.Length() < WidthHex) {
             Data = "0" + Data;
         }
      } else {
         Data = Data.SubString(Data.Length()-WidthHex+1, WidthHex);
         //Data = Data.SubString(1,2);
      }
   }
   this->e_Data->Text = Data;
}
//---------------------------------------------------------------------------

void Tf_Memory::LoadInstructionSet(_di_IXMLNode pInstructionSet)
{
   TList* TempInstrucList = new TList;
   TInstruc* Instruc;
   TInstruc* TempInstruc;
   int ID, DisplayOrder;
   String Name, OpCode, FieldWidth;

   //Flush all Instruction...if any
   for (int i = 0; i<this->InstrucCmp; i++) {
      Instruc = (TInstruc*)this->InstrucList->Items[i];
      delete Instruc;
   }
   this->InstrucList->Clear();
   this->cb_OpCode->Clear();
   this->cds_Mem->EmptyDataSet();

   this->InstrucCmp = 0;
   _di_IXMLNodeList AllInstruction = pInstructionSet->ChildNodes;
   this->InstrucCmp = AllInstruction->Count;

   for (int i = 0; i < AllInstruction->Count; i++) {
      ID           = AllInstruction->Get(i)->GetAttribute("ID");
      Name         = AllInstruction->Get(i)->GetAttribute("Name");
      OpCode       = AllInstruction->Get(i)->GetAttribute("OpCode");
      DisplayOrder = AllInstruction->Get(i)->GetAttribute("DisplayOrder");

      Instruc = new TInstruc(ID, Name, OpCode, DisplayOrder);
      TempInstrucList->Add(Instruc);

      _di_IXMLNode DescInstr      = AllInstruction->Get(i)->ChildNodes->Nodes[0];
      _di_IXMLNode CommInstr      = AllInstruction->Get(i)->ChildNodes->Nodes[1];
      _di_IXMLNode DataFieldInstr = AllInstruction->Get(i)->ChildNodes->Nodes[2];
      _di_IXMLNode CodeBlockInstr  = AllInstruction->Get(i)->ChildNodes->Nodes[3];
      _di_IXMLNode TextBlockInstr  = AllInstruction->Get(i)->ChildNodes->Nodes[4];

      Instruc->Descr = DescInstr->Text;
      Instruc->Comm  = CommInstr->Text;

      Instruc->DataAct   = DataFieldInstr->GetAttribute("Data")=="True";
      FieldWidth = DataFieldInstr->GetAttribute("Width");
      FieldWidth = FieldWidth=="Triple"?"12":FieldWidth=="Double"?"8":FieldWidth=="Single"?"4":"0";
      Instruc->DataWidth = StrToInt(FieldWidth);
      Instruc->FieldBAct = DataFieldInstr->GetAttribute("B")=="True";
      Instruc->FieldCAct = DataFieldInstr->GetAttribute("C")=="True";
      Instruc->FieldDAct = DataFieldInstr->GetAttribute("D")=="True";

      _di_IXMLNode CodeBlockA = CodeBlockInstr->ChildNodes->Nodes[0];
      Instruc->BlockAFix    = CodeBlockA->GetAttribute("Fix")=="True";
      Instruc->BlockASource = CodeBlockA->GetAttribute("Source");
      Instruc->BlockAVal    = CodeBlockA->Text;

      _di_IXMLNode CodeBlockB = CodeBlockInstr->ChildNodes->Nodes[1];
      Instruc->BlockBFix    = CodeBlockB->GetAttribute("Fix")=="True";
      Instruc->BlockBSource = CodeBlockB->GetAttribute("Source");
      Instruc->BlockBVal    = CodeBlockB->Text;

      _di_IXMLNode CodeBlockC = CodeBlockInstr->ChildNodes->Nodes[2];
      Instruc->BlockCFix    = CodeBlockC->GetAttribute("Fix")=="True";
      Instruc->BlockCSource = CodeBlockC->GetAttribute("Source");
      Instruc->BlockCVal    = CodeBlockC->Text;

      _di_IXMLNode CodeBlockD = CodeBlockInstr->ChildNodes->Nodes[3];
      Instruc->BlockDFix    = CodeBlockD->GetAttribute("Fix")=="True";
      Instruc->BlockDSource = CodeBlockD->GetAttribute("Source");
      Instruc->BlockDVal    = CodeBlockD->Text;

      Instruc->NbParam = TextBlockInstr->GetAttribute("NbParam");

      _di_IXMLNode TextBlockHead = TextBlockInstr->ChildNodes->Nodes[0];
      Instruc->HeadMnemo  = TextBlockHead->GetAttribute("Mnemonic");
      Instruc->HeadSuffix = TextBlockHead->GetAttribute("Suffix");

      if (Instruc->NbParam > 0) {
         _di_IXMLNode TextBlockParam1 = TextBlockInstr->ChildNodes->Nodes[1];
         Instruc->Param1Type    = TextBlockParam1->GetAttribute("Type");
         Instruc->Param1Source  = TextBlockParam1->GetAttribute("Source");
         Instruc->Param1Suffix  = TextBlockParam1->GetAttribute("Suffix");

         if (Instruc->NbParam > 1) {
            _di_IXMLNode TextBlockParam2 = TextBlockInstr->ChildNodes->Nodes[2];
            Instruc->Param2Type   = TextBlockParam2->GetAttribute("Type");
            Instruc->Param2Source = TextBlockParam2->GetAttribute("Source");
            Instruc->Param2Suffix = TextBlockParam2->GetAttribute("Suffix");

            if (Instruc->NbParam > 2) {
               _di_IXMLNode TextBlockParam3 = TextBlockInstr->ChildNodes->Nodes[3];
               Instruc->Param3Type   = TextBlockParam3->GetAttribute("Type");
               Instruc->Param3Source = TextBlockParam3->GetAttribute("Source");
               Instruc->Param3Suffix = TextBlockParam3->GetAttribute("Suffix");

            }
         }
      }
   }
   
   for (int i = 0; i<this->InstrucCmp; i++) {
      for (int j = 0; j<TempInstrucList->Count; j++) {
         TempInstruc = (TInstruc*)TempInstrucList->Items[j];
         if (TempInstruc->DisplayOrder==i) {
            //Instruc = new TInstruc(TempInstruc->ID, TempInstruc->Name, TempInstruc->OpCode, TempInstruc->DisplayOrder);
            this->InstrucList->Add(TempInstruc);
            this->cb_OpCode->Items->Add(TempInstruc->Descr);
            TempInstrucList->Delete(j);
            break;
         }
      }     
   }
   delete TempInstrucList;

   /*for (int i = 0; i<this->InstrucCmp; i++) {
      Instruc = (TInstruc*)this->InstrucList->Items[i];
      this->cb_OpCode->Items->Add(Instruc->Descr);
   }*/

   this->b_Import->Enabled     = true;
   this->b_Clear->Enabled      = true;
   this->b_Load->Enabled       = true;
   this->b_Add->Enabled        = true;
   this->b_Insert->Enabled     = true;
   this->b_Edit->Enabled       = true;
   this->b_BreakPoint->Enabled = true;

   this->rb_Hex->Checked = true;
   this->cb_OpCode->ItemIndex = this->cb_OpCode->Items->IndexOf("NOP ()");
   this->b_Add->Click();
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_ClearClick(TObject *Sender)
{
   (void)Sender;

   this->ExecCmp = 0;

   this->b_Add->Enabled    = true;
   this->b_Insert->Enabled = true;
   this->b_Edit->Enabled   = true;
   this->b_Delete->Enabled = true;

   this->e_Comment->Enabled = true;
   this->cb_OpCode->Enabled = true;
   this->l_Width->Enabled   = true;

   this->cds_Mem->EmptyDataSet();
   this->rb_Hex->Checked = true;
   this->cb_OpCode->ItemIndex = this->cb_OpCode->Items->IndexOf("NOP ()");
   this->b_Add->Click();
}
//---------------------------------------------------------------------------

void Tf_Memory::Parse4MacroDefineAndInclude(TStringList *pASMFile, TList* pMacroList, TStringList *pMacroUsageCmp, TList* pMacroLabelList, String* pIncludes, TStringList* pErrorList, TStringList* pMetaASMFile)
{
   String Line, MacroName, LineLbl, LbLName, LineData;
   TStringList *MacroLine;
   TStringList *LocalLabelList;
   TStringList *ASMFileInclude;
   bool FoundEnd;

   //Main loop, line Count will vary with Insert and Delete made here
   for(int i = 0; i<pASMFile->Count ; i++) {
      Line = pASMFile->Strings[i];
      Line = Line.Trim();

      //Looking for include tag
      if (Line.SubString(1,9) == "#INCLUDE " ) {
         // from #INCLUDE "exemple.asm" to exemple.asm
         Line = Line.SubString(11,Line.Length()-11);
         //Remove comment
         if (Line.Pos(";")>0) {
            Line = Line.SubString(1,Line.Pos(";")-1);
         }
         Line = Line.Trim();

         if (FileExists(ExtractFilePath(this->od_Assembler->FileName) + Line)) {
            //remove the line with #include
            pASMFile->Delete(i);
            pMetaASMFile->Delete(i);

            ASMFileInclude = new TStringList;
            ASMFileInclude->LoadFromFile(ExtractFilePath(this->od_Assembler->FileName) + Line);
            *pIncludes = *pIncludes + Line + " , ";

            //Once opened, insert every line from the included file at that location
            for (int j = 0; j<ASMFileInclude->Count ; j++) {
               pASMFile->Insert(i+j, ASMFileInclude->Strings[j]);
               pMetaASMFile->Insert(i+j, "[" + Line + ":" + IntToStr(j+1) + "]");
            }
            //As #include was remove, line at i must be scanned again
            i--;
            ASMFileInclude->Free();
         } else {
            pErrorList->Add(ERR_UNKNOWN_FILE + Line + pMetaASMFile->Strings[i]);
            pASMFile->Strings[i] = ";" + pASMFile->Strings[i];
         }
         continue;
      }

      //Looking for Macro definition start tag
      if (Line.SubString(1,1) == "[" ) {
         //Exact the name of the Macro
         Line = Line + " ";
         MacroName = Line.SubString(2,Line.Pos(" ")-2);

         if (pMacroUsageCmp->IndexOfName(MacroName.UpperCase()) > 0) {
            pErrorList->Add(ERR_REDEFINED_MACRO + MacroName + pMetaASMFile->Strings[i]);

            pASMFile->Delete(i);
            pMetaASMFile->Delete(i);

            while (i < pASMFile->Count && !FoundEnd) {
               Line = pASMFile->Strings[i];
               Line = Line.TrimRight();

               if (Line.SubString(1,1) == "]" ) {
                  FoundEnd = true;
               }
               pASMFile->Delete(i);
               pMetaASMFile->Delete(i);

               //if the end tag ] was not found
               if (!FoundEnd) {
                  pErrorList->Add(ERR_NO_ENDTAG_MACRO + MacroName + pMetaASMFile->Strings[i]);
                  ShowMessage("Error in macro " + MacroName + ": No End Tag");
               }
            }
            continue;
         }

         //Add that name as index 0 to:
         MacroLine      = new TStringList;
         LocalLabelList = new TStringList;
         //Keep the code of the Macro itself in MacroLine
         pMacroList->Add(MacroLine);
         //Keep the labels used in the Macro in LocalLabelList
         pMacroLabelList->Add(LocalLabelList);
         MacroLine->Add(MacroName.UpperCase());
         LocalLabelList->Add(MacroName.UpperCase());

         //Keep a list of the number of calls to a Macro to rewrite the lable with a unique name
         pMacroUsageCmp->Add(MacroName.UpperCase() + "=0");
         pASMFile->Delete(i);
         pMetaASMFile->Delete(i);

         FoundEnd = false;
         //Loop until the Macro end tag ] is found
         while ( i < pASMFile->Count && !FoundEnd ) {
            Line = pASMFile->Strings[i];
            Line = Line.TrimRight();

            //Extract Label
            if (Line.Pos("/")) {
               LineLbl  = Line.SubString(1, Line.Pos("/")-1);
            } else {
               LineLbl  = Line.SubString(1,24);
            }
            LineLbl  = LineLbl.Trim();

            //Process Label
            if(LineLbl.SubString(1,1) == ":" ) {
               //First Label
               LineLbl = LineLbl + " ";
               LbLName = LineLbl.SubString(2,LineLbl.Pos(" ")-2);
               LineLbl = LineLbl.SubString(LineLbl.Pos(" "), LineLbl.Length()-LineLbl.Pos(" "));
               LineLbl = LineLbl.Trim();

               //Test if already defined, keep the Label in a list for renaming later
               if (LocalLabelList->IndexOfName(LbLName.UpperCase()) < 0) {
                  LocalLabelList->Add(LbLName);
               } else {
                  pErrorList->Add(ERR_REDEFINED_LABEL + MacroName + ":" + LbLName + pMetaASMFile->Strings[i]);
               }

               //Second Label
               if( LineLbl != "" && LineLbl.SubString(1,1) == ":" ) {
                  LbLName = LineLbl.SubString(2, LineLbl.Length());

                  //Test if already defined, keep the Label in a list for renaming later
                  if (LocalLabelList->IndexOfName(LbLName.UpperCase()) < 0) {
                     LocalLabelList->Add(LbLName.UpperCase());
                  } else {
                     pErrorList->Add(ERR_REDEFINED_LABEL + MacroName + ":" + LbLName + pMetaASMFile->Strings[i]);
                  }
               }
            }

            //Looking for Macro end tag ], otherwise, keep the line in memory for later when called
            if (Line.SubString(1,1) == "]" ) {
               FoundEnd = true;
            } else {
               MacroLine->Add(Line);
            }

            //Line from Macro are removed from the main file, but kept in MacroLine for when it's called
            pASMFile->Delete(i);
            pMetaASMFile->Delete(i);
         }

         //if the end tag ] was not found
         if (!FoundEnd) {
            pErrorList->Add(ERR_NO_ENDTAG_MACRO + MacroName + pMetaASMFile->Strings[i]);
            //ShowMessage("Error in macro " + MacroName + ": No End Tag");
         }
      }
   }
}
//---------------------------------------------------------------------------

void Tf_Memory::Parse4MacroUsage(TStringList *pASMFile, TList* pMacroList, TStringList *pMacroUsageCmp, TList* pMacroLabelList, TStringList* pErrorList, TStringList* pMetaASMFile)
{
   String Line, MacroName, LineLbl, LbLName, LineData;
   TStringList *MacroLine;  
   TStringList *LocalLabelList;
   bool FoundMatch = false;

   //Main loop, line Count will vary with Insert and Delete made here
   for (int i = 0; i<pASMFile->Count ; i++) {
      Line = pASMFile->Strings[i];
      Line = Line.Trim();

      //Looking for Macro call tag
      if (Line.SubString(1,1) == "%" ) {
         Line = Line + " ";
         //Extract Macro name
         MacroName = Line.SubString(2,Line.Pos(" ")-2);
         MacroName = MacroName.UpperCase();

         FoundMatch = false;
         //Look for the code lines of the Macro 
         for (int j = 0; j < pMacroList->Count && !FoundMatch; j++) {
            MacroLine = (TStringList*)pMacroList->Items[j];
            FoundMatch = MacroLine->Strings[0] == MacroName;
         }

         //If that Macro was found on the first pass
         if (FoundMatch) {
            FoundMatch = false;
            //Look for the list of Labels for that Macro 
            for (int j = 0; j < pMacroLabelList->Count && !FoundMatch; j++) {
               LocalLabelList = (TStringList*)pMacroLabelList->Items[j];
               FoundMatch = LocalLabelList->Strings[0] == MacroName;
            }

            //Remove the Macro Call line
            pASMFile->Delete(i);
            String macroLocation = pMetaASMFile->Strings[i];
            pMetaASMFile->Delete(i);
            //Loop for the number of lines contained in the macro
            for (int j = 1; j < MacroLine->Count; j++) {
               Line = MacroLine->Strings[j];

               //Extract Labels
               if (Line.Pos("/")) {
                  LineLbl  = Line.SubString(1, Line.Pos("/")-1);
                  LineData = Line.SubString(Line.Pos("/")+1,Line.Length()-Line.Pos("/"));
               } else {
                  LineLbl  = Line.SubString(1,24);
                  LineData = Line.SubString(25,Line.Length()-24);
               }
               LineLbl  = LineLbl.Trim() + " ";
               LineData = LineData.Trim();
               LineLbl  = LineLbl.UpperCase();
               //LineData = LineData.UpperCase();

               //Skip Macro call lines
               if (LineLbl.SubString(1,1) != "%" ) {
                  //Loop to replace all Labels found in the Macro
                  for (int k = 1; k < LocalLabelList->Count; k++) {
                     //Rename by concatenting "_MACRO_[X]" to the name where X goes from 0 to the number of time the Macro is called
                     //That insure every Macro call as a unique set of Labels
                     LineLbl = StringReplace(LineLbl, ":" + LocalLabelList->Strings[k] + " ",
                                          ":" + LocalLabelList->Strings[k] + "_MACRO_" + pMacroUsageCmp->Values[MacroName] + " ",
                                          TReplaceFlags() << rfReplaceAll );
                     LineData = StringReplace(LineData, ":" + LocalLabelList->Strings[k] + " ",
                                          ":" + LocalLabelList->Strings[k] + "_MACRO_" + pMacroUsageCmp->Values[MacroName] + " ",
                                          TReplaceFlags() << rfReplaceAll );
                     LineData = StringReplace(LineData, "::" + LocalLabelList->Strings[k] + " ",
                                          "::" + LocalLabelList->Strings[k] + "_MACRO_" + pMacroUsageCmp->Values[MacroName] + " ",
                                          TReplaceFlags() << rfReplaceAll );
                     LineData = StringReplace(LineData, ":*" + LocalLabelList->Strings[k] + " ",
                                          ":*" + LocalLabelList->Strings[k] + "_MACRO_" + pMacroUsageCmp->Values[MacroName] + " ",
                                          TReplaceFlags() << rfReplaceAll );
                  }
                  //Rewrite them with the / separator instead of the fix 24 char as renaming may have make them longer than 24 char
                  Line = LineLbl.Trim() + "/" + LineData;
               }
               //Insert the line in place
               pASMFile->Insert(i+(j-1), Line);
               pMetaASMFile->Insert(i+(j-1), "[MACRO:" + MacroName + "->" + macroLocation + ":" + IntToStr(j) + "]");
            }
            //As the Macro call line was removed (%) the line at i must be reprocessed
            i--;
            //Macro call counter incremented so later calls will rename the Labels with a different number
            pMacroUsageCmp->Values[MacroName] = IntToStr(StrToInt(pMacroUsageCmp->Values[MacroName])+1);
         } else {
            pErrorList->Add(ERR_UNKNOWN_MACRO + MacroName + pMetaASMFile->Strings[i]);
            pASMFile->Delete(i);
            pMetaASMFile->Delete(i);
         }
      }
   }
}
//---------------------------------------------------------------------------

void Tf_Memory::Parse4LabelConstBlank(TStringList *pASMFile, TStringList *pLabelList, TStringList *pConstList, TStringList* pErrorList, TStringList* pMetaASMFile)
{
   int lineCount = 1;

   //Main loop
   for (int i = 0; i<pASMFile->Count ; i++) {
      String line = pASMFile->Strings[i];
      String lineData;
      String lineComment = "";

      //Extract Comment
      if (line.Pos(";") > 0) {
         lineComment = line.SubString(line.Pos(";")+1, line.Length()-line.Pos(";"));
         lineData    = line.SubString(1, line.Pos(";")-1);

         //If double semicolon, the comment line is kept with an NOP instruction placeholder
         if (lineComment.Pos(";;") == 1) {
            lineData = " /NOP  ;";
         }
      } else {
         lineData = line;
      }
      //Remove blank lines
      if (lineData.Trim() == "") {
         pASMFile->Delete(i);
         pMetaASMFile->Delete(i);
         i--;
         continue;
      }

      //Looking for define tag
      if (lineData.SubString(1, 8) == "#DEFINE " ) {
         lineData = lineData.SubString(8, lineData.Length());
         lineData = lineData.Trim();

         String lineConst = lineData.SubString(1, lineData.Pos(" ")-1);
         String lineValue = lineData.SubString(lineData.Pos(" "), lineData.Length());
         lineValue = lineValue.Trim();

         //Test if already defined
         if (pConstList->IndexOfName(lineConst.UpperCase()) < 0) {
            pConstList->Add(lineConst.UpperCase() + "=" + lineValue);

            //remove the line with #define
            pASMFile->Delete(i);
            pMetaASMFile->Delete(i);
            //As #define was remove, line at i must be scanned again
            i--;
         } else {
            pErrorList->Add(ERR_REDEFINED_CONST + lineConst + pMetaASMFile->Strings[i]);
            pASMFile->Strings[i] = ";" + pASMFile->Strings[i];
         }
         continue;
      }

      String lineLabel;

      //Extract Label
      if (lineData.Pos("/")) {
         lineLabel = lineData.SubString(1, lineData.Pos("/")-1);
         lineData  = lineData.SubString(lineData.Pos("/")+1, lineData.Length()-lineData.Pos("/"));
      } else {
         lineLabel = lineData.SubString(1, 24);
         lineData  = lineData.SubString(25, lineData.Length()-24);
      }
      lineLabel  = lineLabel.Trim();
      lineData   = lineData.Trim();
      line       = lineData + "  ;";

      //Process Label
      if ( lineLabel.SubString(1,1) == ":" ) {
         String labelName;

         //First Label
         lineLabel = lineLabel + " ";
         labelName = lineLabel.SubString(2, lineLabel.Pos(" ")-2);
         lineLabel = lineLabel.SubString(lineLabel.Pos(" "), lineLabel.Length()-lineLabel.Pos(" "));
         lineLabel = lineLabel.Trim();
         line      = line + ":" + labelName + " ";

         //Test if already defined
         if (pLabelList->IndexOfName(labelName.UpperCase()) < 0) {
            pLabelList->Add(labelName.UpperCase() + "=" + IntToStr(lineCount));
         } else {
            pErrorList->Add(ERR_REDEFINED_LABEL + labelName + pMetaASMFile->Strings[i]);
         }

         //Second Label
         if (lineLabel.SubString(1,1) == ":" ) {
            labelName = lineLabel.SubString(2, lineLabel.Length());
            line    = line + ":" + labelName + " ";

            //Test if already defined
            if (pLabelList->IndexOfName(labelName.UpperCase()) < 0) {
               pLabelList->Add(labelName.UpperCase() + "=" + IntToStr(lineCount));
            } else {
               pErrorList->Add(ERR_REDEFINED_LABEL + labelName + pMetaASMFile->Strings[i]);
            }
         }
      }

      //If the label was on a empty line (no instruction)
      if (lineData == "") {
         pASMFile->Delete(i);
         pMetaASMFile->Delete(i);
         i--;
         continue;
      }


      //Output instruction + comment
      line = line + lineComment;
      pASMFile->Strings[i] = line;
      lineCount++;
      
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_ImportClick(TObject *Sender)
{
   (void)Sender;

   String DataHex , DataLineText, DataLineCode, includes;
   TStringList *ASMFile   = new TStringList;
   TStringList *LabelList = new TStringList;
   TStringList *constList = new TStringList;
   TList* MacroList       = new TList;
   TStringList *MacroUsageCmp = new TStringList;
   TList* MacroLabelList  = new TList;
   TStringList *errorList = new TStringList;
   TStringList *metaASMFile = new TStringList;
   
   LabelList->NameValueSeparator = '=';
   constList->NameValueSeparator = '=';
   MacroUsageCmp->NameValueSeparator = '=';

   if (! this->od_Assembler->Execute()) {
      return;
   }

   this->b_Clear->Click();
   this->cds_Mem->Delete();

   this->b_Add->Enabled    = false;
   this->b_Insert->Enabled = false;
   this->b_Edit->Enabled   = false;
   this->b_Delete->Enabled = false;

   this->e_Comment->Enabled = false;
   this->cb_OpCode->Enabled = false;
   this->l_Width->Enabled   = false;

   this->e_Data->Enabled = false;
   this->l_Data->Enabled = false;
   this->rb_Bin->Enabled = false;
   this->rb_Dec->Enabled = false;
   this->rb_Hex->Enabled = false;

   this->cb_B->Enabled = false;
   this->cb_C->Enabled = false;
   this->cb_D->Enabled = false;

   ASMFile->LoadFromFile(this->od_Assembler->FileName);
   for (int i = 1; i<=ASMFile->Count; i++) {
      metaASMFile->Add("[" + ExtractFileName(this->od_Assembler->FileName) + ":" + IntToStr(i) + "]");
   }

   //First pass, process includes and list macros definitions
   this->Parse4MacroDefineAndInclude(ASMFile, MacroList, MacroUsageCmp, MacroLabelList, &includes, errorList, metaASMFile);
   //Second pass, replace calls for macros, and rename labels inside macros
   this->Parse4MacroUsage(ASMFile, MacroList, MacroUsageCmp, MacroLabelList, errorList, metaASMFile);
   //Third pass, remove empty or blank lines, comment lines and list labels
   this->Parse4LabelConstBlank(ASMFile, LabelList, constList, errorList, metaASMFile);

   //Fourth pass, process instruction lines and any comments at the end of a line
   for (int i = 0; i<ASMFile->Count ; i++) {
      String line = ASMFile->Strings[i];
      String lineComment = "";
      String lineData;

      //Extract Comment if at the end of a line
      if (line.Pos(";") > 0) {
         lineComment = line.SubString(line.Pos(";")+1, line.Length()-line.Pos(";"));
         lineData    = line.SubString(1, line.Pos(";")-1);
      } else {
         lineData = line;
      }

      lineData = lineData.UpperCase();

      //Remove Special chars
      lineData = StringReplace(lineData, "GOTO", " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "->",   ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "<-",   ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "-",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, ">>",   ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, ">",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "<<",   ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "<",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "+",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "|",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "&",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "^",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "?",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "==",   ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "=",    ", ", TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "!",    " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "@",    " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "#",    " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "(",    " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, ")",    " ",  TReplaceFlags() << rfReplaceAll );
      lineData = StringReplace(lineData, "\"",   " ",  TReplaceFlags() << rfReplaceAll );
      lineData = lineData.Trim();
         
      String lineOpCode = lineData.SubString(1,5);
      lineOpCode = lineOpCode.Trim();
      //Skip empty line
      if (lineOpCode == "") {
         continue;
      }
      lineData = lineData.SubString(7, lineData.Length());//-7);
      lineData = lineData.Trim();

      //Find the Instruction in the list
      TInstruc* instruc;
      bool foundIt = false;
      for (int j = 0; j<this->InstrucCmp; j++) {
         instruc = (TInstruc*)this->InstrucList->Items[j];
         if (instruc->HeadMnemo.UpperCase() == lineOpCode) {
            foundIt = true;
            break;
         }
      }
      if (!foundIt) {
         errorList->Add(ERR_UNKNOWN_OPCODE + lineOpCode + metaASMFile->Strings[i]);
      }

      String lineParam[3];
      lineParam[0] = "";
      lineParam[1] = "";
      lineParam[2] = "";
      int paramCount = 0;

      //Process Params
      if (lineData != "") {
         if (lineData.Pos(",") > 0) {
            lineParam[0] = lineData.SubString(1, lineData.Pos(",")-1);
            lineParam[0] = lineParam[0].Trim();
            if (lineParam[0] == "") { 
               errorList->Add(ERR_OPCODE_PARAM_EMPTY + lineOpCode + metaASMFile->Strings[i]);
               lineParam[0] = "0";
            }
            lineData = lineData.SubString(lineData.Pos(",")+1, lineData.Length());
            lineData = lineData.Trim();

            if (lineData.Pos(",") > 0 ) {
               lineParam[1] = lineData.SubString(1, lineData.Pos(",")-1);
               lineParam[1] = lineParam[1].Trim();
               if (lineParam[1] == "") { 
                  errorList->Add(ERR_OPCODE_PARAM_EMPTY + lineOpCode + metaASMFile->Strings[i]);
                  lineParam[1] = "0";
               }
               lineData = lineData.SubString(lineData.Pos(",")+1, lineData.Length());
               lineData = lineData.Trim();

               if (lineData.Pos(",") > 0 ) {
                  errorList->Add(ERR_OPCODE_PARAM_MANY + lineOpCode + metaASMFile->Strings[i]);
               } else {
                  lineParam[2] = lineData;
                  paramCount = 3;
               }
            } else {
               lineParam[1] = lineData;
               paramCount = 2;
            }
         } else {
            lineParam[0]  = lineData;
            paramCount = 1;
         }
      }
      if (instruc->NbParam != paramCount) {
         errorList->Add(ERR_OPCODE_PARAM_COUNT + lineOpCode + metaASMFile->Strings[i]);
         lineParam[0] = "0";
         lineParam[1] = "0";
         lineParam[2] = "0";
      }

      //Constants
      for (int j=0; j<3; j++) {
         if (lineParam[j].SubString(1, 2) == ":%") {
   
            String constantName = lineParam[j].SubString(3, lineParam[j].Length()-2);
            String constantVal  = constList->Values[constantName];
            if (constantVal == "") {
               errorList->Add(ERR_UNKNOWN_CONST + constantName + metaASMFile->Strings[i]);
               constantVal = "0";
            }
            lineParam[j] = constantVal;
         }
      }

      //Print readable line
      String instrucText = instruc->HeadMnemo + instruc->HeadSuffix;
      String instrucTextParam[3] = {"", "", ""};

      switch (instruc->NbParam) {
         case 3:
            if (instruc->Param3Source == "Data") {
               DataLineCode = DataToBin(lineParam[2], instruc->DataWidth, LabelList, i, errorList, metaASMFile);
               DataLineText = "0x";
               for (int j=1; j<=instruc->DataWidth; j+=4) {
                  DataLineText = DataLineText + BinToHex(DataLineCode.SubString(j,4));
               }
               instrucTextParam[2] = instruc->Param3Type + DataLineText + instruc->Param3Suffix;
            } else if (instruc->Param3Source != "") {
               if (lineParam[2].SubString(1, 1) != "$") {
                  errorList->Add(ERR_OPCODE_PARAM_TYPE + lineParam[2] + metaASMFile->Strings[i]);
                  lineParam[2] = "$0";
               }
               instrucTextParam[2] = instruc->Param3Type + lineParam[2].SubString(2,1) + instruc->Param3Suffix;
            }

         case 2:
            if (instruc->Param2Source == "Data") {
               DataLineCode = DataToBin(lineParam[1], instruc->DataWidth, LabelList, i, errorList, metaASMFile);
               DataLineText = "0x";
               for (int j=1; j<=instruc->DataWidth; j+=4) {
                  DataLineText = DataLineText + BinToHex(DataLineCode.SubString(j,4));
               }
               instrucTextParam[1] = instruc->Param2Type + DataLineText + instruc->Param2Suffix;
            } else if (instruc->Param2Source != "") {
               if (lineParam[1].SubString(1, 1) != "$") {
                  errorList->Add(ERR_OPCODE_PARAM_TYPE + lineParam[1] + metaASMFile->Strings[i]);
                  lineParam[1] = "$0";
               }
               instrucTextParam[1] = instruc->Param2Type + lineParam[1].SubString(2,1) + instruc->Param2Suffix;
            }

         case 1:
            if (instruc->Param1Source == "Data") {
               DataLineCode = DataToBin(lineParam[0], instruc->DataWidth, LabelList, i, errorList, metaASMFile);
               DataLineText = "0x";
               for (int j=1; j<=instruc->DataWidth; j+=4) {
                  DataLineText = DataLineText + BinToHex(DataLineCode.SubString(j,4));
               }
               instrucTextParam[0] = instruc->Param1Type + DataLineText + instruc->Param1Suffix;
            } else if (instruc->Param1Source != "") {
               if (lineParam[0].SubString(1, 1) != "$") {
                  errorList->Add(ERR_OPCODE_PARAM_TYPE + lineParam[0] + metaASMFile->Strings[i]);
                  lineParam[0] = "$0";
               }
               instrucTextParam[0] = instruc->Param1Type + lineParam[0].SubString(2,1) + instruc->Param1Suffix;
            }

         //case 0:
         //default:
      }

      instrucText = instrucText + instrucTextParam[0] + instrucTextParam[1] + instrucTextParam[2] ;

      //Compute Machine Code
      String instrucCode = "";
      int currParam = 0;

      if (instruc->BlockAFix) {
         instrucCode = instruc->BlockAVal;
      } else if (instruc->BlockASource == "Data") {
         instrucCode = DataToBin(lineParam[currParam], instruc->DataWidth, LabelList, i, NULL, NULL);
         currParam++;
      } else if (instruc->BlockASource != "") {
         instrucCode = HexToBin(lineParam[currParam].SubString(2, lineParam[currParam].Length()));
         currParam++;
      }

      if (instruc->BlockBFix) {
         instrucCode = instrucCode + instruc->BlockBVal;
      } else if (instruc->BlockBSource == "Data") {
         instrucCode = instrucCode + DataToBin(lineParam[currParam], instruc->DataWidth, LabelList, i, NULL, NULL);
         currParam++;
      } else if (instruc->BlockBSource != "") {
         instrucCode = instrucCode + HexToBin(lineParam[currParam].SubString(2, lineParam[currParam].Length()));
         currParam++;
      }

      if (instruc->BlockCFix) {
         instrucCode = instrucCode + instruc->BlockCVal;
      } else if (instruc->BlockCSource == "Data") {
         instrucCode = instrucCode + DataToBin(lineParam[currParam], instruc->DataWidth, LabelList, i, NULL, NULL);
         currParam++;
      } else if (instruc->BlockCSource != "") {
         instrucCode = instrucCode + HexToBin(lineParam[currParam].SubString(2, lineParam[currParam].Length()));
         currParam++;
      }

      if (instruc->BlockDFix) {
         instrucCode = instrucCode + instruc->BlockDVal;
      } else if (instruc->BlockDSource == "Data") {
         instrucCode = instrucCode + DataToBin(lineParam[currParam], instruc->DataWidth, LabelList, i, NULL, NULL);
         currParam++;
      } else if (instruc->BlockDSource != "") {
         instrucCode = instrucCode + HexToBin(lineParam[currParam].SubString(2, lineParam[currParam].Length()));
         currParam++;
      }

      //Save to DataSet
      this->cds_Mem->Append();
      this->cds_MemOpCode->AsInteger   = this->cb_OpCode->Items->IndexOf(instruc->Descr);
      this->cds_MemMnemonic->AsString  = lineOpCode;
      //this->cds_MemData->AsString      = ;
      this->cds_MemComment->AsString   = lineComment;
      //this->cds_MemRB->AsInteger       = StrToInt(this->cb_B->ItemIndex);
      //this->cds_MemRC->AsInteger       = StrToInt(this->cb_C->ItemIndex);
      //this->cds_MemRD->AsInteger       = StrToInt(this->cb_D->ItemIndex);
      //this->cds_MemDataType->AsInteger = 0:0b 1: 2:0x   //LineParam[CurrParam].SubString(1,2) == "0X"
      this->cds_MemBreakPoint->AsBoolean = false;
      this->cds_MemHumData->AsString   = instrucText;
      this->cds_MemCode->AsString      = instrucCode;
      this->cds_MemCodeHex->AsString   = BinToHex(instrucCode.SubString(1,4)) + BinToHex(instrucCode.SubString(5,4)) +
                                         BinToHex(instrucCode.SubString(9,4)) + BinToHex(instrucCode.SubString(13,4));
      this->cds_MemSource->AsString    = metaASMFile->Strings[i];

      this->cds_Mem->Post();
   }
   ASMFile->Clear();

   //Show Errors
   if (errorList->Count != 0) {
      Tf_ErrorList *f_ErrorList = ::new Tf_ErrorList(NULL);
      try {
         errorList->Insert(0, this->od_Assembler->FileName);
         errorList->Insert(1, FormatDateTime("yyyy-mm-dd hh:mm:ss", Now()));
         errorList->Insert(2, "");
         errorList->Insert(3, "Includes: " + includes);
         errorList->Insert(4, "");
         errorList->Insert(5, "Error count: " + IntToStr(errorList->Count));
         errorList->Insert(6, "");

         f_ErrorList->InitList(errorList);

         f_ErrorList->ShowModal();
      } __finally {
          delete f_ErrorList;
      }
   }

   //Cleanup
   ASMFile->Free();
   LabelList->Free();
   MacroUsageCmp->Free();
   errorList->Free();
   metaASMFile->Free();

   for (int i = 0; i<MacroList->Count ; i++) {
      ASMFile = (TStringList*)MacroList->Items[i];
      ASMFile->Free();
   }

   for (int i = 0; i<MacroLabelList->Count ; i++) {
      ASMFile = (TStringList*)MacroLabelList->Items[i];
      ASMFile->Free();
   }

   MacroList->Free();
   MacroLabelList->Free();

   //First line of code
   this->cds_Mem->First();
}
//---------------------------------------------------------------------------
String Tf_Memory::DataToBin(String pData, int pSize, TStringList *pLabelList, int pCurrLine, TStringList* pErrorList, TStringList* pMetaASMFile)
{
   String DataIn, DataOut = "", Addr, lblName;
   int Delta;

   if (pData.SubString(1, 1) == '$') {
      if (pErrorList != NULL) {
         pErrorList->Add(ERR_OPCODE_PARAM_TYPE + pData + pMetaASMFile->Strings[pCurrLine]);
      }
      for (int i=1; i<=pSize; i++) {
         DataOut = DataOut + 0;
      }

   } else if (pData.SubString(1, 2) == ":*") {
   //Absolute Addr (Higer bits)
      lblName = pData.SubString(3, pData.Length()-2);
      Addr = pLabelList->Values[lblName];
      if (Addr == "") {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_UNKNOWN_LABEL + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         Addr = "0";
      }

      if (StrToInt(Addr) >= 65536 ) {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_ABS_ADDR_FAR + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         Addr = "0";
      }
      Addr = DecToHex(Addr, 65535);

      //Left Padding
      while (Addr.Length() < 4) {
         Addr = "0" + Addr;
      }
      for (int i=1; i<=pSize/4; i++) {
         DataOut = DataOut + HexToBin(Addr.SubString(i, 1));
      }

   } else if (pData.SubString(1,2) == ":.") {
   //Absolute Addr (Lower bits)
      lblName = pData.SubString(3,pData.Length()-2);
      Addr = pLabelList->Values[lblName];
      if (Addr == "") {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_UNKNOWN_LABEL + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         Addr = "0";
      }

      if (StrToInt(Addr) >= 65536 ) {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_ABS_ADDR_FAR + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         Addr = "0";
      }
      Addr = DecToHex(Addr, 65535);

      //Left Padding
      while (Addr.Length() < 4) {
         Addr = "0" + Addr;
      }
      for (int i=4; i>4-(pSize/4); i--) {
         DataOut = HexToBin(Addr.SubString(i, 1)) + DataOut;
      }

   } else if (pData.SubString(1, 1) == ":") {
   //Relative  Addr
      //Lookup
      lblName = pData.SubString(2, pData.Length()-1);
      if (pLabelList->Values[lblName] == "") {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_UNKNOWN_LABEL + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         Delta = 0;
      } else {
         Delta = StrToInt(pLabelList->Values[lblName]) - pCurrLine - 1;
      }

      if (Delta < 128 && Delta > -128) {
         if (Delta >=0) {
            Delta = (Delta-1)+128;
         } else {
            Delta = abs(Delta);
            Delta = 128 - Delta;
         }
         DataIn = DecToHex(IntToStr(Delta));
         if (DataIn.Length() == 1) {
            DataIn = "0" + DataIn;
         }
      } else {
         if (pErrorList != NULL) {
            pErrorList->Add(ERR_REL_ADDR_FAR + lblName + pMetaASMFile->Strings[pCurrLine]);
         }
         DataIn = "80";
      }
      DataOut = HexToBin(DataIn.SubString(1, 1)) + HexToBin(DataIn.SubString(2,1));
   } else if (pData.SubString(1, 2) == "0X") {
   //Hex Value
      DataIn = pData.SubString(3, pData.Length()); //,(pSize/4)-2);
      //Left Padding
      while (DataIn.Length() < pSize/4) {
         DataIn = "0" + DataIn;
      }
      DataIn = DataIn.SubString(DataIn.Length()-(pSize/4)+1, pSize/4);
      for (int i=1; i<=pSize/4; i++) {
         DataOut = DataOut + HexToBin(DataIn.SubString(i, 1));
      }

   } else if (pData.SubString(1, 2) == "0B") {
   //Binary Value
      DataOut = pData.SubString(3, pData.Length()); //,(pSize)-2);
      //Left Padding
      while (DataOut.Length() < pSize) {
         DataOut = "0" + DataOut;
      }

   } else {
   //Decimal Value
      DataIn = pData.SubString(1, (pSize/4)+1);
      DataIn = DecToHex(DataIn);
      //Left Padding
      while (DataIn.Length() < pSize/4) {
         DataIn = "0" + DataIn;
      }
      DataIn = DataIn.SubString(DataIn.Length()-(pSize/4)+1, pSize/4);
      for (int i=1; i<=pSize/4; i++) {
         DataOut = DataOut + HexToBin(DataIn.SubString(i, 1));
      }

   }
   DataOut = DataOut.Trim();
   return DataOut;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cb_StepByStepClick(TObject *Sender)
{
   (void)Sender;

   b_Next->Enabled = cb_StepByStep->Checked;
   if (f_GraphIO->Pin39->Checked == true) {
      b_Next->Click();
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_NextClick(TObject *Sender)
{
   (void)Sender;

   f_GraphIO->Pin39->Checked = false;
   if (!cb_StepByStep->Checked) {
      b_Next->Enabled = false;
   }
}
//---------------------------------------------------------------------------
/*
void __fastcall Tf_Memory::dbg_MemDrawDataCell(TObject *Sender, const TRect &Rect,
          TField *Field, TGridDrawState State)
{
   (void)Sender;
   //(void)State;

   if (Field->Name == "cds_MemAddress" || Field->Name == "cds_MemAddrHex" ) {
      if (this->cds_MemBreakPoint->AsBoolean) {
         //dbg_Mem->Canvas->Font->Style = dbg_Mem->Canvas->Font->Style << fsBold;
         dbg_Mem->Canvas->Brush->Color = clRed;
         //dbg_Mem->Canvas->FillRect(Rect);
         //dbg_Mem->Canvas->TextRect(Rect, Rect.Left + 2, Rect.Top + 2, Field->AsString);
         dbg_Mem->DefaultDrawDataCell(Rect, Field, State);
      }
   }
}
*/
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::dbg_MemDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State)
{
   (void)Sender;

   if (Column->FieldName == "Address" || Column->FieldName == "AddrHex") {
      if (this->cds_MemBreakPoint->AsBoolean) {
         if (this->cds_MemAddress->AsInteger == currentExecLine) {
            dbg_Mem->Canvas->Brush->Color = clYellow;
         } else {
            dbg_Mem->Canvas->Brush->Color = clRed;
         }
         dbg_Mem->DefaultDrawColumnCell(Rect, DataCol, Column, State);
      } else if (this->cds_MemAddress->AsInteger == currentExecLine) {
         dbg_Mem->Canvas->Brush->Color = clLime;
         dbg_Mem->DefaultDrawColumnCell(Rect, DataCol, Column, State);
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_BreakPointClick(TObject *Sender)
{
   (void)Sender;

   this->cds_Mem->Edit();
   this->cds_MemBreakPoint->AsBoolean = !this->cds_MemBreakPoint->AsBoolean;
   this->cds_Mem->Post();
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_bootClick(TObject *Sender)
{
   (void)Sender;

   if (f_GraphIO->Pin70->Checked) {
      f_GraphIO->Pin70->Checked = false;
      this->b_boot->Caption = "Boot";
      f_CPUNode->b_Reset->Click();
   } else {
      f_GraphIO->Pin70->Checked = true;
      this->b_boot->Caption = "Reset";
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::FormShow(TObject *Sender)
{
   (void)Sender;

   this->Left = Screen->Width - (this->Width + 5);
   this->Top = Screen->Height - (this->Height + 50);
   this->b_boot->Caption = "Reset";
}
//---------------------------------------------------------------------------

void Tf_Memory::ResetState(void)
{
   this->dbg_Mem->Color = clWindow;
   this->cds_Mem->First();
   this->currentExecLine = 0;
   this->LastDataType = 2;
   this->LastSelLine = 0;
   this->ExecCmp = 0;
   this->b_boot->Caption = "Boot";
}

//---------------------------------------------------------------------------

