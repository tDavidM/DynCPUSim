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
TInstruc::TInstruc(int pID, String pName, String pOpCode)
{
   this->ID     = pID;
   this->Name   = pName;
   this->OpCode = pOpCode;

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
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cb_OpCodeChange(TObject *Sender)
{
   TInstruc* Instruc;

   Instruc = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];
   this->cb_OpCode->Hint = Instruc->Comm;

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
String Tf_Memory::BinToHex(String Hex)
{
    if     (Hex == "1111") { return "F"; }
    else if(Hex == "1110") { return "E"; }
    else if(Hex == "1101") { return "D"; }
    else if(Hex == "1100") { return "C"; }
    else if(Hex == "1011") { return "B"; }
    else if(Hex == "1010") { return "A"; }
    else if(Hex == "1001") { return "9"; }
    else if(Hex == "1000") { return "8"; }
    else if(Hex == "0111") { return "7"; }
    else if(Hex == "0110") { return "6"; }
    else if(Hex == "0101") { return "5"; }
    else if(Hex == "0100") { return "4"; }
    else if(Hex == "0011") { return "3"; }
    else if(Hex == "0010") { return "2"; }
    else if(Hex == "0001") { return "1"; }
    else if(Hex == "0000") { return "0"; }
    else { return "0"; } // =^.^= here's a kitty
}
//---------------------------------------------------------------------------
String Tf_Memory::HexToDec(String Hex)
{
      if     (Hex == "0") { return "0"; }
      else if(Hex == "1") { return "1"; }
      else if(Hex == "2") { return "2"; }
      else if(Hex == "3") { return "3"; }
      else if(Hex == "4") { return "4"; }
      else if(Hex == "5") { return "5"; }
      else if(Hex == "6") { return "6"; }
      else if(Hex == "7") { return "7"; }
      else if(Hex == "8") { return "8"; }
      else if(Hex == "9") { return "9"; }
      else if(Hex == "A") { return "10"; }
      else if(Hex == "B") { return "11"; }
      else if(Hex == "C") { return "12"; }
      else if(Hex == "D") { return "13"; }
      else if(Hex == "E") { return "14"; }
      else if(Hex == "F") { return "15"; }
      else { return "0"; }
}
//---------------------------------------------------------------------------
String Tf_Memory::HexToBin(String Hex)
{
      if     (Hex == "0") { return "0000"; }
      else if(Hex == "1") { return "0001"; }
      else if(Hex == "2") { return "0010"; }
      else if(Hex == "3") { return "0011"; }
      else if(Hex == "4") { return "0100"; }
      else if(Hex == "5") { return "0101"; }
      else if(Hex == "6") { return "0110"; }
      else if(Hex == "7") { return "0111"; }
      else if(Hex == "8") { return "1000"; }
      else if(Hex == "9") { return "1001"; }
      else if(Hex == "A") { return "1010"; }
      else if(Hex == "B") { return "1011"; }
      else if(Hex == "C") { return "1100"; }
      else if(Hex == "D") { return "1101"; }
      else if(Hex == "E") { return "1110"; }
      else if(Hex == "F") { return "1111"; }
      else { return "0"; }
}
//---------------------------------------------------------------------------
String Tf_Memory::DecToHex(String Hex)
{
  int Dec = StrToInt(Hex);
  int Div;
  String Stack = "";

  if(Dec > 255){return "0";}
  else if(Dec < 0)  {return "0";}
  else
  {
      Div = Dec / 16;
      switch(Div)
      {
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
      Div = Dec % 16;
      switch(Div)
      {
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
}
//---------------------------------------------------------------------------
void Tf_Memory::CreateLine(void)
{
  String BasePrefix;
  int BaseId;
  String BinData, InstrucText, InstrucCode;
  TInstruc* Instruc;

  if(this->rb_Bin->Checked) {
     BasePrefix = "0b";
     BaseId     = 0;
     BinData    = this->e_Data->Text;
  } else if (this->rb_Dec->Checked) {
     BasePrefix = "0d";
     BaseId     = 1;
     this->e_Data->Text = this->e_Data->Text.UpperCase();
     BinData    = DecToHex(this->e_Data->Text);
     BinData    = HexToBin(BinData.SubString(1,1)) + HexToBin(BinData.SubString(2,1));
  } else {
     BasePrefix = "0x";
     BaseId     = 2;
     this->e_Data->Text = this->e_Data->Text.UpperCase();
     BinData    = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
  }

  while(BinData.Length() < 8)
     BinData = "0" + BinData;

  this->cds_MemOpCode->AsInteger   = this->cb_OpCode->ItemIndex;
  this->cds_MemData->AsString      = this->e_Data->Text;
  this->cds_MemRB->AsInteger       = StrToInt(this->cb_B->ItemIndex);
  this->cds_MemRC->AsInteger       = StrToInt(this->cb_C->ItemIndex);
  this->cds_MemRD->AsInteger       = StrToInt(this->cb_D->ItemIndex);
  this->cds_MemDataType->AsInteger = BaseId;

  Instruc = (TInstruc*)this->InstrucList->Items[this->cb_OpCode->ItemIndex];

  InstrucText = Instruc->Name + Instruc->HeadSuffix;
  if (Instruc->NbParam > 0) {
     InstrucText = InstrucText + Instruc->Param1Type;
     if (Instruc->Param1Source == "B")
       InstrucText = InstrucText + this->cb_B->Text + Instruc->Param1Suffix;
     else if (Instruc->Param1Source == "C")
       InstrucText = InstrucText + this->cb_C->Text + Instruc->Param1Suffix;
     else if (Instruc->Param1Source == "D")
       InstrucText = InstrucText + this->cb_D->Text + Instruc->Param1Suffix;
     else if (Instruc->Param1Source == "Data")
       InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param1Suffix;

     if (Instruc->NbParam > 1) {
        InstrucText = InstrucText + Instruc->Param2Type;
        if (Instruc->Param2Source == "B")
          InstrucText = InstrucText + this->cb_B->Text + Instruc->Param2Suffix;
        else if (Instruc->Param2Source == "C")
          InstrucText = InstrucText + this->cb_C->Text + Instruc->Param2Suffix;
        else if (Instruc->Param2Source == "D")
          InstrucText = InstrucText + this->cb_D->Text + Instruc->Param2Suffix;
        else if (Instruc->Param2Source == "Data")
          InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param2Suffix;

        if (Instruc->NbParam > 2) {
           InstrucText = InstrucText + Instruc->Param3Type;
           if (Instruc->Param3Source == "B")
             InstrucText = InstrucText + this->cb_B->Text + Instruc->Param3Suffix;
           else if (Instruc->Param3Source == "C")
             InstrucText = InstrucText + this->cb_C->Text + Instruc->Param3Suffix;
           else if (Instruc->Param3Source == "D")
             InstrucText = InstrucText + this->cb_D->Text + Instruc->Param3Suffix;
           else if (Instruc->Param3Source == "Data")
             InstrucText = InstrucText + BasePrefix + this->e_Data->Text + Instruc->Param3Suffix;
        }
     }
  }
  this->cds_MemHumData->AsString = InstrucText;

  InstrucCode = "";
  if (Instruc->BlockAFix)
    InstrucCode = Instruc->BlockAVal;
  else if (Instruc->BlockASource == "B")
    InstrucCode = HexToBin(this->cb_B->Text);
  else if (Instruc->BlockASource == "C")
    InstrucCode = HexToBin(this->cb_C->Text);
  else if (Instruc->BlockASource == "D")
    InstrucCode = HexToBin(this->cb_D->Text);
  else if (Instruc->BlockASource == "Data")
    InstrucCode = BinData;

  if (Instruc->BlockBFix)
    InstrucCode = InstrucCode + Instruc->BlockBVal;
  else if (Instruc->BlockBSource == "B")
    InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
  else if (Instruc->BlockBSource == "C")
    InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
  else if (Instruc->BlockBSource == "D")
    InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
  else if (Instruc->BlockBSource == "Data")
    InstrucCode = InstrucCode + BinData;

  if (Instruc->BlockCFix)
    InstrucCode = InstrucCode + Instruc->BlockCVal;
  else if (Instruc->BlockCSource == "B")
    InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
  else if (Instruc->BlockCSource == "C")
    InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
  else if (Instruc->BlockCSource == "D")
    InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
  else if (Instruc->BlockCSource == "Data")
    InstrucCode = InstrucCode + BinData;

  if (Instruc->BlockDFix)
    InstrucCode = InstrucCode + Instruc->BlockDVal;
  else if (Instruc->BlockDSource == "B")
    InstrucCode = InstrucCode + HexToBin(this->cb_B->Text);
  else if (Instruc->BlockDSource == "C")
    InstrucCode = InstrucCode + HexToBin(this->cb_C->Text);
  else if (Instruc->BlockDSource == "D")
    InstrucCode = InstrucCode + HexToBin(this->cb_D->Text);
  else if (Instruc->BlockDSource == "Data")
    InstrucCode = InstrucCode + BinData;

  this->cds_MemCode->AsString  = InstrucCode;

/*
  switch (this->cb_OpCode->ItemIndex) {
    case 0: { //WRITE
      this->cds_MemHumData->AsString   = "SET( " + BasePrefix + this->e_Data->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0000" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 1: { //READ Val
      this->cds_MemHumData->AsString   = "READ( @" + BasePrefix + this->e_Data->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0001" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 2: { //WRITE Val
      this->cds_MemHumData->AsString   = "WRITE( @" + BasePrefix + this->e_Data->Text + " , <- $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "0010" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 3: { //READ Reg
      this->cds_MemHumData->AsString   = "READ( @$" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110111" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 4: { //WRITE Reg
      this->cds_MemHumData->AsString   = "WRITE( @$" + this->cb_C->Text + " , <- $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "11111000" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 5: { //IFZERO Reg
      this->cds_MemHumData->AsString   = "IFZERO( $" + this->cb_B->Text + " ) Goto #$" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0011" + HexToBin(this->cb_B->Text) + "0000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 6: { //IFZERO Val
	  this->cds_MemHumData->AsString   = "IFZERO( $" + this->cb_B->Text + " ) Goto #" + BasePrefix + this->e_Data->Text;
	  this->cds_MemCode->AsString      = "0100" + HexToBin(this->cb_B->Text) + BinData;
      break;
    }

	case 7: { //SKIPZERO
	  this->cds_MemHumData->AsString   = "SKIPZERO( $" + this->cb_D->Text + " )";
	  this->cds_MemCode->AsString      = "111111110110" + HexToBin(this->cb_D->Text);
      break;
    }

	case 8: { //SKIPEQUAL
	  this->cds_MemHumData->AsString   = "SKIPEQUAL( $" + this->cb_B->Text + " , $" + this->cb_C->Text + " )";
	  this->cds_MemCode->AsString      = "0101" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + "0000";
	  break;
	}
	case 9: { //SKIPGREATER
	  this->cds_MemHumData->AsString   = "SKIPGREATER( $" + this->cb_B->Text + " , $" + this->cb_C->Text + " )";
	  this->cds_MemCode->AsString      = "1101" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + "0000";
      break;
    }



    case 10: { //ADD
      this->cds_MemHumData->AsString   = "ADD( $" + this->cb_B->Text + " + $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0110" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 11: { //SUBTRACT
      this->cds_MemHumData->AsString   = "SUBSTRACT( $" + this->cb_B->Text + " - $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0111" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 12: { //INC
      this->cds_MemHumData->AsString   = "INC( $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "111111110100" + HexToBin(this->cb_D->Text);
      break;
    }
    case 13: { //DEC
      this->cds_MemHumData->AsString   = "DEC( $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "111111110101" + HexToBin(this->cb_D->Text);
      break;
    }
    case 14: { //AND
      this->cds_MemHumData->AsString   = "AND( $" + this->cb_B->Text + " & $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1000" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 15: { //OR
      this->cds_MemHumData->AsString   = "OR( $" + this->cb_B->Text + " | $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1001" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 16: { //XOR
      this->cds_MemHumData->AsString   = "XOR( $" + this->cb_B->Text + " x $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1010" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 17: { //NOT
      this->cds_MemHumData->AsString   = "NOT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110000" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 18: { //LEFT SHIFT
      this->cds_MemHumData->AsString   = "LEFTSH( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110001" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 19: { //RIGHT SHIFT
      this->cds_MemHumData->AsString   = "RIGHTSH( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110011" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 20: { //LEFT ROTATE
      this->cds_MemHumData->AsString   = "LEFTRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110010" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 21: { //RIGHT ROTATE
      this->cds_MemHumData->AsString   = "RIGHTRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110100" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 22: { //LEFTCRRT
      this->cds_MemHumData->AsString   = "LEFTCRRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111100" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 23: { //RIGHTCRRT
      this->cds_MemHumData->AsString   = "RIGHTCRRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111101" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 24: { //JUMP Reg
      this->cds_MemHumData->AsString   = "JUMP( ) Goto #$" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111101010000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 25: { //JUMP Val
      this->cds_MemHumData->AsString   = "JUMP( ) Goto #" + BasePrefix + this->e_Data->Text;
      this->cds_MemCode->AsString      = "11110110" + BinData;
      break;
    }
    case 26: { //WIDEJUMP Reg
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111100000000";//"1011";
      break;
    }
    case 27: { //WIDEJUMP Val
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111100000000";//"1100";
      break;
    }
    case 28: { //CARRYFLG
      this->cds_MemHumData->AsString   = "CARRYFLG( ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111110110000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 29: { //RAND
      this->cds_MemHumData->AsString   = "RAND( ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111111110111" + HexToBin(this->cb_D->Text);
      break;
    }
    case 30: { //NOP
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111111110000";
      break;
    }

    case 31: { //COPY AND
      this->cds_MemHumData->AsString   = "* COPY( $" + this->cb_B->Text + " )-> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1000" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_B->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 32: { //ERASE XOR
      this->cds_MemHumData->AsString   = "* ERASE( )-> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1010" + HexToBin(this->cb_D->Text) + HexToBin(this->cb_D->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 33: { //HALT SET
      this->cds_MemHumData->AsString   = "* HALT( )";
      this->cds_MemCode->AsString      = "0000000000001110";
      break;
    }
  }
*/

}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_AddClick(TObject *Sender)
{
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
  this->cb_OpCode->Clear();

  this->cds_Mem->CreateDataSet();
  this->cds_Mem->Open();
  //this->rb_Hex->Checked = true;
  this->LastDataType = 2;
  this->LastSelLine = 0;
  //this->cb_OpCode->ItemIndex = this->cb_OpCode->Items->IndexOf("NOP( )"); //30;
  //this->b_Add->Click();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cds_MemCalcFields(TDataSet *DataSet)
{
  this->cds_MemAddress->AsInteger = this->cds_Mem->RecNo - 1;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_InsertClick(TObject *Sender)
{
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
  while(!cds_Mem->Eof)
  {
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
  this->cds_Mem->Edit();
  //this->cds_MemSort->AsString = this->e_Sort->Text;
  this->CreateLine();
  this->cds_Mem->Post();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::ds_MemDataChange(TObject *Sender, TField *Field)
{
  if (this->cds_Mem->State == dsBrowse) {
      //this->e_Sort->Text         = this->cds_MemSort->AsString;
      //this->e_Sort->Enabled      = true;
      this->cb_OpCode->ItemIndex = this->cds_MemOpCode->AsInteger;
      this->cb_B->ItemIndex      = this->cds_MemRB->AsInteger;
      this->cb_C->ItemIndex      = this->cds_MemRC->AsInteger;
      this->cb_D->ItemIndex      = this->cds_MemRD->AsInteger;
      switch (this->cds_MemDataType->AsInteger) {
        case 0: {
          this->rb_Bin->Checked = true; break;
        }
        case 1: {
          this->rb_Dec->Checked = true; break;
        }
        case 2: {
          this->rb_Hex->Checked = true; break;
        }
      }
      this->e_Data->Text         = this->cds_MemData->AsString;
      if (this->cb_OpCode->Items->Count != 0)
         this->cb_OpCodeChange(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_DeleteClick(TObject *Sender)
{
  if(this->cds_Mem->RecordCount > 1) {
      if (Application->MessageBox( L"Delete Instruction ?", L"Instruction Node", MB_YESNO) == mrYes)
        this->cds_Mem->Delete();
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::e_DataKeyPress(TObject *Sender, char &Key)
{
  if (Key != VK_RETURN && Key != VK_TAB && Key != VK_LEFT && Key != VK_RIGHT && Key != VK_BACK && Key != VK_CLEAR &&
      Key != VK_ESCAPE && Key != VK_DELETE  && Key != VK_HOME && Key != VK_END && Key != VK_INSERT && Key != VK_CANCEL) {
      if (this->rb_Bin->Checked) {
         if ( Key != '0' && Key != '1')
            Key = 0;
      } else if (this->rb_Dec->Checked) {
         if ( Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
              Key != '8' && Key != '9')
            Key = 0;
      } else {
         if ( Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
              Key != '8' && Key != '9' && Key != 'A' && Key != 'B' && Key != 'C' && Key != 'D' && Key != 'E' && Key != 'F' &&
              Key != 'a' && Key != 'b' && Key != 'c' && Key != 'd' && Key != 'e' && Key != 'f')
            Key = 0;
      }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_BinClick(TObject *Sender)
{
  if (this->e_Data->Text != "") {
    if (this->LastDataType == 1) {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = DecToHex(this->e_Data->Text);
       this->e_Data->Text = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
    } else if (this->LastDataType == 2) {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
    }
  }
  this->LastDataType = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_DecClick(TObject *Sender)
{
  if (this->e_Data->Text != "") {
    if (this->LastDataType == 0) {
      this->e_Data->Text = BinToHex(this->e_Data->Text.SubString(1,4)) + BinToHex(this->e_Data->Text.SubString(5,4));
      this->e_Data->Text = IntToStr( (StrToInt(HexToDec(this->e_Data->Text.SubString(1,1))) * 16) + StrToInt(HexToDec(this->e_Data->Text.SubString(2,1))) );
    } else if (this->LastDataType == 2) {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = IntToStr( (StrToInt(HexToDec(this->e_Data->Text.SubString(1,1))) * 16) + StrToInt(HexToDec(this->e_Data->Text.SubString(2,1))) );
    }
  }
  this->LastDataType = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_HexClick(TObject *Sender)
{
  if (this->e_Data->Text != "") {
    if (this->LastDataType == 0)
      this->e_Data->Text = BinToHex(this->e_Data->Text.SubString(1,4)) + BinToHex(this->e_Data->Text.SubString(5,4));
    else if (this->LastDataType == 1)
      this->e_Data->Text = DecToHex(this->e_Data->Text);
  }
  this->LastDataType = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::cds_MemAfterScroll(TDataSet *DataSet)
{
  int Delta = this->cds_Mem->RecNo - this->LastSelLine;

  if (Delta < 128 && Delta > -128) {
    if (Delta >=0)
      Delta = (Delta-1)+128;
    else {
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

     while (Target < 0)
        Target = Target + this->cds_Mem->RecordCount;
  } else if (Delta >= 128 && Delta <= 255) {
     Delta = (Delta - 128) + 1;
     Target = this->cds_MemAddress->AsInteger + Delta;

     while (Target >= this->cds_Mem->RecordCount)
        Target = Target - this->cds_Mem->RecordCount;
  }
  return Target;
}
//---------------------------------------------------------------------------
void Tf_Memory::MoveAddrByDelta(int Delta)
{
   int Target = DeltaToAddr(Delta);
   this->cds_Mem->DisableControls();
   this->cds_Mem->First();

   if (this->cds_Mem->RecordCount > 1 ) {
       while (!this->cds_Mem->Eof && this->cds_MemAddress->AsInteger != Target)
           this->cds_Mem->Next();
   }
   this->cds_Mem->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_SaveClick(TObject *Sender)
{
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
  if (this->od_Mem->Execute()) {
    if (this->od_Mem->FileName != "") {
	   this->cds_Mem->LogChanges = false;
	   this->cds_Mem->LoadFromFile(this->od_Mem->FileName);
	   this->cds_Mem->LogChanges = false;
    }
  }
  //this->cds_Mem->IndexFieldNames = "Sort";
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::e_DataExit(TObject *Sender)
{
   String Data = this->e_Data->Text;
   if (this->rb_Bin->Checked) {
      if (Data.Length() < 8) {
         while (Data.Length() < 8)
             Data = "0" + Data;
      } else
         Data = Data.SubString(1,8);
   } else if (this->rb_Dec->Checked) {
      Data = Data.SubString(1,3);
      if(Data == "")
         Data = "0";
      else if (StrToInt(Data) > 255)
         Data = "255";
   } else {
      if (Data.Length() < 2) {
         while (Data.Length() < 2)
             Data = "0" + Data;
      } else
         Data = Data.SubString(1,2);
   }
   this->e_Data->Text = Data;
}
//---------------------------------------------------------------------------

void Tf_Memory::LoadInstructionSet(_di_IXMLNode pInstructionSet)
{
   TInstruc* Instruc;
   int ID;
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

   for(int i = 0; i < AllInstruction->Count; i++) {
      ID     = AllInstruction->Get(i)->GetAttribute("ID");
      Name   = AllInstruction->Get(i)->GetAttribute("Name");
      OpCode = AllInstruction->Get(i)->GetAttribute("OpCode");

      Instruc = new TInstruc(ID, Name, OpCode);
      this->InstrucList->Add(Instruc);

      _di_IXMLNode DescInstr      = AllInstruction->Get(i)->ChildNodes->Nodes[0];
      _di_IXMLNode CommInstr      = AllInstruction->Get(i)->ChildNodes->Nodes[1];
      _di_IXMLNode DataFieldInstr = AllInstruction->Get(i)->ChildNodes->Nodes[2];
      _di_IXMLNode CodeBlockInstr  = AllInstruction->Get(i)->ChildNodes->Nodes[3];
      _di_IXMLNode TextBlockInstr  = AllInstruction->Get(i)->ChildNodes->Nodes[4];

      Instruc->Descr = DescInstr->Text;
      Instruc->Comm  = CommInstr->Text;

      Instruc->DataAct   = DataFieldInstr->GetAttribute("Data")=="True";
      FieldWidth = DataFieldInstr->GetAttribute("Width");
      FieldWidth = FieldWidth=="Triple"?"12":FieldWidth=="Double"?"8":FieldWidth=="Single"?"8":"0";
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
            Instruc->Param3Suffix = TextBlockParam2->GetAttribute("Suffix");

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
      Instruc = (TInstruc*)this->InstrucList->Items[i];
      this->cb_OpCode->Items->Add(Instruc->Descr);
   }

   this->rb_Hex->Checked = true;
   this->cb_OpCode->ItemIndex = this->cb_OpCode->Items->IndexOf("NOP ()");
   this->b_Add->Click();

}
//---------------------------------------------------------------------------

