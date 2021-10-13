//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Memory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_Memory *f_Memory;
//---------------------------------------------------------------------------
__fastcall Tf_Memory::Tf_Memory(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::cb_OpCodeChange(TObject *Sender)
{
   this->e_Data->Enabled = false;
   this->l_Data->Enabled = false;
   this->cb_B->Enabled = false;
   this->cb_C->Enabled = false;
   this->cb_D->Enabled = false;
   this->rb_Bin->Enabled = false;
   this->rb_Dec->Enabled = false;
   this->rb_Hex->Enabled = false;

   if(this->cb_OpCode->ItemIndex >= 0 && this->cb_OpCode->ItemIndex <= 2)
   {
	  this->e_Data->Enabled = true;
      this->l_Data->Enabled = true;
      this->cb_D->Enabled   = true;
      this->rb_Bin->Enabled = true;
      this->rb_Dec->Enabled = true;
      this->rb_Hex->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 3 || this->cb_OpCode->ItemIndex == 4)
   {
      this->cb_C->Enabled = true;
      this->cb_D->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 5 || this->cb_OpCode->ItemIndex == 30)
   {
      this->cb_B->Enabled = true;
      this->cb_D->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 6)
   {
      this->cb_B->Enabled = true;
	  this->e_Data->Enabled = true;
      this->l_Data->Enabled = true;
      this->rb_Bin->Enabled = true;
      this->rb_Dec->Enabled = true;
      this->rb_Hex->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 7 || this->cb_OpCode->ItemIndex == 8)
   {
      this->cb_B->Enabled = true;
      this->cb_C->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 9 || this->cb_OpCode->ItemIndex == 10
      || (this->cb_OpCode->ItemIndex >= 13 && this->cb_OpCode->ItemIndex <= 15))
   {
      this->cb_B->Enabled = true;
      this->cb_C->Enabled = true;
      this->cb_D->Enabled = true;
   }

   if(this->cb_OpCode->ItemIndex == 11 || this->cb_OpCode->ItemIndex == 12
      ||(this->cb_OpCode->ItemIndex >= 16 && this->cb_OpCode->ItemIndex <= 22))
   {
      this->cb_C->Enabled = true;
      this->cb_D->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 23 || this->cb_OpCode->ItemIndex == 27
      || this->cb_OpCode->ItemIndex == 28 || this->cb_OpCode->ItemIndex == 31)
   {
      this->cb_D->Enabled = true;
   }
   if(this->cb_OpCode->ItemIndex == 24)
   {
	  this->e_Data->Enabled = true;
      this->l_Data->Enabled = true;
      this->rb_Bin->Enabled = true;
      this->rb_Dec->Enabled = true;
      this->rb_Hex->Enabled = true;
   }
   //25
   //26
   //29 NOP
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
  String BinData;

  if(this->rb_Bin->Checked)
  {
     BasePrefix = "0b";
     BaseId     = 0;
     BinData    = this->e_Data->Text;
  }
  else if(this->rb_Dec->Checked)
  {
     BasePrefix = "0d";
     BaseId     = 1;
     this->e_Data->Text = this->e_Data->Text.UpperCase();
     BinData    = DecToHex(this->e_Data->Text);
     BinData    = HexToBin(BinData.SubString(1,1)) + HexToBin(BinData.SubString(2,1));
  }
  else
  {
     BasePrefix = "0x";
     BaseId     = 2;
     this->e_Data->Text = this->e_Data->Text.UpperCase();
     BinData    = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
  }

  while(BinData.Length() < 8)
  {
     BinData = "0" + BinData;
  }

  this->cds_MemOpCode->AsInteger   = this->cb_OpCode->ItemIndex;
  this->cds_MemData->AsString      = this->e_Data->Text;
  this->cds_MemRB->AsInteger       = StrToInt(this->cb_B->ItemIndex);
  this->cds_MemRC->AsInteger       = StrToInt(this->cb_C->ItemIndex);
  this->cds_MemRD->AsInteger       = StrToInt(this->cb_D->ItemIndex);
  this->cds_MemDataType->AsInteger = BaseId;

  switch (this->cb_OpCode->ItemIndex)
  {
    case 0: //WRITE
	{
      this->cds_MemHumData->AsString   = "SET( " + BasePrefix + this->e_Data->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0000" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 1: //READ Val
	{
      this->cds_MemHumData->AsString   = "READ( @" + BasePrefix + this->e_Data->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0001" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 2: //WRITE Val
	{
      this->cds_MemHumData->AsString   = "WRITE( @" + BasePrefix + this->e_Data->Text + " , <- $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "0010" + BinData + HexToBin(this->cb_D->Text);
      break;
    }
    case 3: //READ Reg
	{
      this->cds_MemHumData->AsString   = "READ( @$" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110111" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 4: //WRITE Reg
	{
      this->cds_MemHumData->AsString   = "WRITE( @$" + this->cb_C->Text + " , <- $" + this->cb_D->Text + " )";
      this->cds_MemCode->AsString      = "11111000" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 5: //IFZERO Reg
	{
      this->cds_MemHumData->AsString   = "IFZERO( $" + this->cb_B->Text + " ) Goto #$" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0011" + HexToBin(this->cb_B->Text) + "0000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 6: //IFZERO Val
	{
	  this->cds_MemHumData->AsString   = "IFZERO( $" + this->cb_B->Text + " ) Goto #" + BasePrefix + this->e_Data->Text;
	  this->cds_MemCode->AsString      = "0100" + HexToBin(this->cb_B->Text) + BinData;
      break;
    }
	case 7: //SKIPEQUAL
    {
	  this->cds_MemHumData->AsString   = "SKIPEQUAL( $" + this->cb_B->Text + " , $" + this->cb_C->Text + " )";
	  this->cds_MemCode->AsString      = "0101" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text);
	  break;
	}
	case 8: //SKIPGREATER
	{
	  this->cds_MemHumData->AsString   = "SKIPGREATER( $" + this->cb_B->Text + " , $" + this->cb_C->Text + " )";
	  this->cds_MemCode->AsString      = "1101" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text);
      break;
    }
    case 9: //ADD
	{
      this->cds_MemHumData->AsString   = "ADD( $" + this->cb_B->Text + " + $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0110" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 10: //SUBTRACT
	{
      this->cds_MemHumData->AsString   = "SUBSTRACT( $" + this->cb_B->Text + " - $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "0111" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 11: //INC
	{
      this->cds_MemHumData->AsString   = "INC( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111001" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 12: //DEC
	{
      this->cds_MemHumData->AsString   = "DEC( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111010" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 13: //AND
	{
      this->cds_MemHumData->AsString   = "AND( $" + this->cb_B->Text + " & " + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1000" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 14: //OR
	{
      this->cds_MemHumData->AsString   = "OR( $" + this->cb_B->Text + " | " + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1001" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 15: //XOR
	{
      this->cds_MemHumData->AsString   = "XOR( $" + this->cb_B->Text + " x " + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1010" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 16: //NOT
	{
      this->cds_MemHumData->AsString   = "NOT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110000" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 17: //LEFT SHIFT
	{
      this->cds_MemHumData->AsString   = "LEFTSH( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110001" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 18: //RIGHT SHIFT
	{
      this->cds_MemHumData->AsString   = "RIGHTSH( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110011" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 19: //LEFT ROTATE
	{
      this->cds_MemHumData->AsString   = "LEFTRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110010" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 20: //RIGHT ROTATE
	{
      this->cds_MemHumData->AsString   = "RIGHTRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11110100" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 21: //LEFTCRRT
	{
      this->cds_MemHumData->AsString   = "LEFTCRRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111100" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 22: //RIGHTCRRT
	{
      this->cds_MemHumData->AsString   = "RIGHTCRRT( $" + this->cb_C->Text + " ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "11111101" + HexToBin(this->cb_C->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 23: //JUMP Reg
	{
      this->cds_MemHumData->AsString   = "JUMP( ) Goto #$" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111101010000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 24: //JUMP Val
	{
      this->cds_MemHumData->AsString   = "JUMP( ) Goto #" + BasePrefix + this->e_Data->Text;
      this->cds_MemCode->AsString      = "11110110" + BinData;
      break;
    }
    case 25: //WIDEJUMP Reg
    {
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111100000000";//"1011";
      break;
    }
    case 26: //WIDEJUMP Val
    {
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111100000000";//"1100";
      break;
    }
    case 27: //CARRYFLG
	{
      this->cds_MemHumData->AsString   = "CARRYFLG( ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111110110000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 28: //RAND
	{
      this->cds_MemHumData->AsString   = "RAND( ) -> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "111111100000" + HexToBin(this->cb_D->Text);
      break;
    }
    case 29: //NOP
	{
      this->cds_MemHumData->AsString   = "NOP( )";
      this->cds_MemCode->AsString      = "1111111100000000";
      break;
    }

    case 30: //COPY AND
	{
      this->cds_MemHumData->AsString   = "* COPY( $" + this->cb_B->Text + " )-> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1000" + HexToBin(this->cb_B->Text) + HexToBin(this->cb_B->Text) + HexToBin(this->cb_D->Text);
      break;
    }
    case 31: //ERASE XOR
	{
      this->cds_MemHumData->AsString   = "* ERASE( )-> $" + this->cb_D->Text;
      this->cds_MemCode->AsString      = "1010" + HexToBin(this->cb_D->Text) + HexToBin(this->cb_D->Text) + HexToBin(this->cb_D->Text);
      break;
    }
  }
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
  this->cds_Mem->CreateDataSet();
  this->cds_Mem->Open();
  this->rb_Hex->Checked = true;
  this->LastDataType = 2;
  this->LastSelLine = 0;
  this->b_Add->Click();
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
  if (this->cds_Mem->State == dsBrowse)
  {
      //this->e_Sort->Text         = this->cds_MemSort->AsString;
      //this->e_Sort->Enabled      = true;
      this->cb_OpCode->ItemIndex = this->cds_MemOpCode->AsInteger;
      this->cb_B->ItemIndex      = this->cds_MemRB->AsInteger;
      this->cb_C->ItemIndex      = this->cds_MemRC->AsInteger;
      this->cb_D->ItemIndex      = this->cds_MemRD->AsInteger;
      switch (this->cds_MemDataType->AsInteger)
      {
        case 0:
        {
          this->rb_Bin->Checked = true; break;
        }
        case 1:
        {
          this->rb_Dec->Checked = true; break;
        }
        case 2:
        {
          this->rb_Hex->Checked = true; break;
        }
      }
      this->e_Data->Text         = this->cds_MemData->AsString;
      this->cb_OpCodeChange(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::b_DeleteClick(TObject *Sender)
{
  if(this->cds_Mem->RecordCount > 1)
  {
      if (Application->MessageBox( L"Delete Instruction ?", L"Instruction Node", MB_YESNO) == mrYes)
      {
        this->cds_Mem->Delete();
      }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Memory::e_DataKeyPress(TObject *Sender, char &Key)
{
  if(Key != VK_RETURN && Key != VK_TAB && Key != VK_LEFT && Key != VK_RIGHT && Key != VK_BACK && Key != VK_CLEAR &&
     Key != VK_ESCAPE && Key != VK_DELETE  && Key != VK_HOME && Key != VK_END && Key != VK_INSERT && Key != VK_CANCEL)
  {
      if(this->rb_Bin->Checked)
      {
         if(Key != '0' && Key != '1')
         {
             Key = 0;
         }
      }
      else if(this->rb_Dec->Checked)
      {
         if(Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' && Key != '8' && Key != '9')
         {
             Key = 0;
         }
      }
      else
      {
         if(Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
            Key != '8' && Key != '9' && Key != 'A' && Key != 'B' && Key != 'C' && Key != 'D' && Key != 'E' && Key != 'F' &&
            Key != 'a' && Key != 'b' && Key != 'c' && Key != 'd' && Key != 'e' && Key != 'f')
         {
             Key = 0;
         }
      }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_BinClick(TObject *Sender)
{
  if(this->e_Data->Text != "")
  {
    if(this->LastDataType == 1)
    {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = DecToHex(this->e_Data->Text);
       this->e_Data->Text = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
    }
    else if (this->LastDataType == 2)
    {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = HexToBin(this->e_Data->Text.SubString(1,1)) + HexToBin(this->e_Data->Text.SubString(2,1));
    }
  }
  this->LastDataType = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_DecClick(TObject *Sender)
{
  if(this->e_Data->Text != "")
  {
    if(this->LastDataType == 0)
    {
      this->e_Data->Text = BinToHex(this->e_Data->Text.SubString(1,4)) + BinToHex(this->e_Data->Text.SubString(5,4));
      this->e_Data->Text = IntToStr( (StrToInt(HexToDec(this->e_Data->Text.SubString(1,1))) * 16) + StrToInt(HexToDec(this->e_Data->Text.SubString(2,1))) );
    }
    else if (this->LastDataType == 2)
    {
       this->e_Data->Text = this->e_Data->Text.UpperCase();
       this->e_Data->Text = IntToStr( (StrToInt(HexToDec(this->e_Data->Text.SubString(1,1))) * 16) + StrToInt(HexToDec(this->e_Data->Text.SubString(2,1))) );
    }
  }
  this->LastDataType = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::rb_HexClick(TObject *Sender)
{
  if(this->e_Data->Text != "")
  {
    if(this->LastDataType == 0)
    {
      this->e_Data->Text = BinToHex(this->e_Data->Text.SubString(1,4)) + BinToHex(this->e_Data->Text.SubString(5,4));
    }
    else if (this->LastDataType == 1)
    {
      this->e_Data->Text = DecToHex(this->e_Data->Text);
    }
  }
  this->LastDataType = 2;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::cds_MemAfterScroll(TDataSet *DataSet)
{
  int Delta = this->cds_Mem->RecNo - this->LastSelLine;

  if(Delta < 128 && Delta > -128)
  {
    if(Delta >=0)
    {
      Delta = (Delta-1)+128;
    }
    else
    {
      Delta = abs(Delta);
      Delta = 128 - Delta;
    }
    this->l_AddrVal->Caption = DecToHex(IntToStr(Delta) );
  }
  else
  {
    this->l_AddrVal->Caption = "0x____";
  }
  this->LastSelLine = this->cds_Mem->RecNo;
}
//---------------------------------------------------------------------------
int Tf_Memory::DeltaToAddr(int Delta)
{
  int Target = 0;

  if(Delta <= 127 && Delta >= 0)
  {
     Delta = 128 - Delta;
     Target = this->cds_MemAddress->AsInteger - Delta;

     while(Target < 0)
     {
        Target = Target + this->cds_Mem->RecordCount;
     }
  }
  else if (Delta >= 128 && Delta <= 255)
  {
     Delta = (Delta - 128) + 1;
     Target = this->cds_MemAddress->AsInteger + Delta;

     while(Target >= this->cds_Mem->RecordCount)
     {
        Target = Target - this->cds_Mem->RecordCount;
     }
  }
  return Target;
}
//---------------------------------------------------------------------------
void Tf_Memory::MoveAddrByDelta(int Delta)
{
   int Target = DeltaToAddr(Delta);
   this->cds_Mem->DisableControls();
   this->cds_Mem->First();

   if(this->cds_Mem->RecordCount > 1 )
   {
       while(!this->cds_Mem->Eof && this->cds_MemAddress->AsInteger != Target)
       {
           this->cds_Mem->Next();
       }
   }
   this->cds_Mem->EnableControls();
}
//---------------------------------------------------------------------------

void __fastcall Tf_Memory::b_SaveClick(TObject *Sender)
{
  if (this->sd_Mem->Execute())
  {
    if(this->sd_Mem->FileName != "")
    {
      TBookmark CurrAddr;

	  this->cds_Mem->MergeChangeLog();
      //this->cds_Save->FieldDefs = this->cds_Mem->FieldDefs;
	  //this->cds_Save->co
	  this->cds_Mem->LogChanges = false;

      this->cds_Mem->DisableControls();
      CurrAddr = this->cds_Mem->GetBookmark();
      this->cds_Mem->First();
      while(!this->cds_Mem->Eof)
      {
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
  if (this->od_Mem->Execute())
  {
    if(this->od_Mem->FileName != "")
    {
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
   if(this->rb_Bin->Checked)
   {
      if(Data.Length() < 8)
      {
         while(Data.Length() < 8)
         {
             Data = "0" + Data;
         }
      }
      else
      {
         Data = Data.SubString(1,8);
      }
   }
   else if(this->rb_Dec->Checked)
   {
      Data = Data.SubString(1,3);
      if(Data == "")
      {
         Data = "0";
      }
      else if (StrToInt(Data) > 255)
      {
         Data = "255";
      }
   }
   else
   {
      if(Data.Length() < 2)
      {
         while(Data.Length() < 2)
         {
             Data = "0" + Data;
         }
      }
      else
      {
         Data = Data.SubString(1,2);
      }
   }
   this->e_Data->Text = Data;
}
//---------------------------------------------------------------------------


