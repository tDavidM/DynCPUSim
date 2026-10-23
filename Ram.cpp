//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include <string>

#include "Ram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_Ram *f_Ram;
//---------------------------------------------------------------------------
__fastcall Tf_Ram::Tf_Ram(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::FormCreate(TObject *Sender)
{
   (void)Sender;

   this->LastX = -1;
   this->LastY = -1;

   this->CurrentPage = "00";
   this->e_Page->Text = this->CurrentPage;
   this->Caption = "RAM page: 0x" + this->CurrentPage;
   this->cds_Ram->Filter = "Page='00'";

   this->sg_Ram->ColWidths[0] = 16;

   this->sg_Ram->Cells[1][0]  = "00 - 1F";
   this->sg_Ram->Cells[2][0]  = "20 - 3F";
   this->sg_Ram->Cells[3][0]  = "40 - 5F";
   this->sg_Ram->Cells[4][0]  = "60 - 7F";
   this->sg_Ram->Cells[5][0]  = "80 - 9F";
   this->sg_Ram->Cells[6][0]  = "A0 - BF";
   this->sg_Ram->Cells[7][0]  = "C0 - DF";
   this->sg_Ram->Cells[8][0]  = "E0 - FF";

   this->sg_Ram->Cells[0][1]  = "0";
   this->sg_Ram->Cells[0][2]  = "1";
   this->sg_Ram->Cells[0][3]  = "2";
   this->sg_Ram->Cells[0][4]  = "3";
   this->sg_Ram->Cells[0][5]  = "4";
   this->sg_Ram->Cells[0][6]  = "5";
   this->sg_Ram->Cells[0][7]  = "6";
   this->sg_Ram->Cells[0][8]  = "7";
   this->sg_Ram->Cells[0][9]  = "8";
   this->sg_Ram->Cells[0][10] = "9";
   this->sg_Ram->Cells[0][11] = "A";
   this->sg_Ram->Cells[0][12] = "B";
   this->sg_Ram->Cells[0][13] = "C";
   this->sg_Ram->Cells[0][14] = "D";
   this->sg_Ram->Cells[0][15] = "E";
   this->sg_Ram->Cells[0][16] = "F";
   this->sg_Ram->Cells[0][17] = "0";
   this->sg_Ram->Cells[0][18] = "1";
   this->sg_Ram->Cells[0][19] = "2";
   this->sg_Ram->Cells[0][20] = "3";
   this->sg_Ram->Cells[0][21] = "4";
   this->sg_Ram->Cells[0][22] = "5";
   this->sg_Ram->Cells[0][23] = "6";
   this->sg_Ram->Cells[0][24] = "7";
   this->sg_Ram->Cells[0][25] = "8";
   this->sg_Ram->Cells[0][26] = "9";
   this->sg_Ram->Cells[0][27] = "A";
   this->sg_Ram->Cells[0][28] = "B";
   this->sg_Ram->Cells[0][29] = "C";
   this->sg_Ram->Cells[0][30] = "D";
   this->sg_Ram->Cells[0][31] = "E";
   this->sg_Ram->Cells[0][32] = "F";

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         this->sg_Ram->Cells[j][i] = "00";
      }
   }
   this->LastDataType = 2;
   this->rb_Hex->Checked = true;

   this->cds_Ram->CreateDataSet();
   this->cds_Ram->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::FormShow(TObject *Sender)
{
   (void)Sender;

   this->Left = 5;
   this->Top = 5;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   (void)Sender;

   CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::sg_RamKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN) {
      e_PageExit(Sender);
   } else if (Key != VK_TAB && Key != VK_LEFT && Key != VK_RIGHT && Key != VK_BACK && Key != VK_CLEAR &&
              Key != VK_ESCAPE && Key != VK_DELETE  && Key != VK_HOME && Key != VK_END && Key != VK_INSERT && Key != VK_CANCEL) {
      if (this->rb_Bin->Checked) {
         if (Key != '0' && Key != '1') {
            Key = 0;
         }
      } else if (this->rb_Dec->Checked) {
         if (Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' && Key != '8' && Key != '9') {
            Key = 0;
         }
      } else {
         if (Key != '0' && Key != '1' && Key != '2' && Key != '3' && Key != '4' && Key != '5' && Key != '6' && Key != '7' &&
             Key != '8' && Key != '9' && Key != 'A' && Key != 'B' && Key != 'C' && Key != 'D' && Key != 'E' && Key != 'F' &&
             Key != 'a' && Key != 'b' && Key != 'c' && Key != 'd' && Key != 'e' && Key != 'f') {
            Key = 0;
         }
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::sg_RamSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   (void)Sender;
   (void)CanSelect;

   this->CleanUpData(this->LastX, this->LastY);

   this->LastX = ACol;
   this->LastY = ARow;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::sg_RamExit(TObject *Sender)
{
   (void)Sender;

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         this->CleanUpData(j, i);
      }
   }
   this->LastX = -1;
   this->LastY = -1;
}
//---------------------------------------------------------------------------
void Tf_Ram::CleanUpData(int X, int Y)
{
   String Data;

   if (X != -1 && Y != -1) {
      Data = this->sg_Ram->Cells[X][Y];
      if (this->rb_Bin->Checked) {
         if (Data.Length() < 8) {
            while (Data.Length() < 8) {
               Data = "0" + Data;
            }
         } else {
            Data = Data.SubString(1, 8);
         }
      } else if (this->rb_Dec->Checked) {
         Data = Data.SubString(1,3);
         if (Data == "") {
            Data = "0";
         } else if (StrToInt(Data) > 255) {
            Data = "255";
         }
      } else {
         if (Data.Length() < 2) {
            while (Data.Length() < 2) {
               Data = "0" + Data;
            }
         } else {
            Data = Data.SubString(1, 2);
         }
      }
      this->sg_Ram->Cells[X][Y] = Data.UpperCase();

      TLocateOptions SrOpt;
      if (this->cds_Ram->Locate("Line", Y, SrOpt)) {
         this->cds_Ram->Edit();
      } else {
         this->cds_Ram->Insert();
         this->cds_RamLine->AsInteger = Y;
         this->cds_RamPage->AsString = this->CurrentPage;
      }

      if (this->rb_Bin->Checked) {
         Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
      } else if (this->rb_Dec->Checked) {
         Data = DecToHex(Data);
      }

      switch(X) {
         case 1: { this->cds_RamField01->AsString = Data; break;}
         case 2: { this->cds_RamField23->AsString = Data; break;}
         case 3: { this->cds_RamField45->AsString = Data; break;}
         case 4: { this->cds_RamField67->AsString = Data; break;}
         case 5: { this->cds_RamField89->AsString = Data; break;}
         case 6: { this->cds_RamFieldAB->AsString = Data; break;}
         case 7: { this->cds_RamFieldCD->AsString = Data; break;}
         case 8: { this->cds_RamFieldEF->AsString = Data; break;}
      }
      this->cds_Ram->Post();
   }
}
//---------------------------------------------------------------------------
String Tf_Ram::BinToHex(String Hex)
{
        if (Hex == "1111") { return "F"; }
   else if (Hex == "1110") { return "E"; }
   else if (Hex == "1101") { return "D"; }
   else if (Hex == "1100") { return "C"; }
   else if (Hex == "1011") { return "B"; }
   else if (Hex == "1010") { return "A"; }
   else if (Hex == "1001") { return "9"; }
   else if (Hex == "1000") { return "8"; }
   else if (Hex == "0111") { return "7"; }
   else if (Hex == "0110") { return "6"; }
   else if (Hex == "0101") { return "5"; }
   else if (Hex == "0100") { return "4"; }
   else if (Hex == "0011") { return "3"; }
   else if (Hex == "0010") { return "2"; }
   else if (Hex == "0001") { return "1"; }
   else if (Hex == "0000") { return "0"; }
   else { return "0"; } // =^.^= here's a kitty
}
//---------------------------------------------------------------------------
String Tf_Ram::HexToDec(String Hex)
{
   switch (Hex[1]) {
      case '0' : return "0";
      case '1' : return "1";
      case '2' : return "2";
      case '3' : return "3";
      case '4' : return "4";
      case '5' : return "5";
      case '6' : return "6";
      case '7' : return "7";
      case '8' : return "8";
      case '9' : return "9";
      case 'A' : return "10";
      case 'B' : return "11";
      case 'C' : return "12";
      case 'D' : return "13";
      case 'E' : return "14";
      case 'F' : return "15";
      default:  return "0";
   }
}
//---------------------------------------------------------------------------
String Tf_Ram::HexToBin(String Hex)
{
   switch (Hex[1]) {
      case '0' : return "0000";
      case '1' : return "0001";
      case '2' : return "0010";
      case '3' : return "0011";
      case '4' : return "0100";
      case '5' : return "0101";
      case '6' : return "0110";
      case '7' : return "0111";
      case '8' : return "1000";
      case '9' : return "1001";
      case 'A' : return "1010";
      case 'B' : return "1011";
      case 'C' : return "1100";
      case 'D' : return "1101";
      case 'E' : return "1110";
      case 'F' : return "1111";
      default:  return "0000";
   }
}
//---------------------------------------------------------------------------
String Tf_Ram::DecToHex(String Hex)
{
   int Dec = StrToIntDef(Hex, 0); // Maybe use HexToDec(Hex[1]) ?
   int Div;
   String Stack = "";

   if (Dec > 255) {
      return "0";
   } else if (Dec < 0) {
      return "0";
   } else {
      Div = Dec / 16;
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
      Div = Dec % 16;
      switch(Div) {
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
void __fastcall Tf_Ram::rb_BinClick(TObject *Sender)
{
   (void)Sender;

   String Data;

   Data = this->e_Page->Text;
   if (this->LastDataType == 1) {
      Data = Data.UpperCase();
      Data = DecToHex(Data);
      Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
   } else if (this->LastDataType == 2) {
      Data = Data.UpperCase();
      Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 8;

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         Data = this->sg_Ram->Cells[j][i];
         if (this->LastDataType == 1) {
            Data = Data.UpperCase();
            Data = DecToHex(Data);
            Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
         } else if (this->LastDataType == 2) {
            Data = Data.UpperCase();
            Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
         }
         this->sg_Ram->Cells[j][i] = Data;
      }
   }
   this->LastDataType = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::rb_DecClick(TObject *Sender)
{
   (void)Sender;

   String Data;

   Data = this->e_Page->Text;
   if (this->LastDataType == 0) {
      Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
      Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1, 1))) * 16) + StrToInt(HexToDec(Data.SubString(2, 1))) );
   } else if (this->LastDataType == 2) {
      Data = Data.UpperCase();
      Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1, 1))) * 16) + StrToInt(HexToDec(Data.SubString(2, 1))) );
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 3;

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         Data = this->sg_Ram->Cells[j][i];
         if ( this->LastDataType == 0) {
            Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5, 4));
            Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1, 1))) * 16) + StrToInt(HexToDec(Data.SubString(2, 1))) );
         } else if (this->LastDataType == 2) {
            Data = Data.UpperCase();
            Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1, 1))) * 16) + StrToInt(HexToDec(Data.SubString(2, 1))) );
         }
         this->sg_Ram->Cells[j][i] = Data;
      }
   }
   this->LastDataType = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::rb_HexClick(TObject *Sender)
{
   (void)Sender;

   String Data;

   Data = this->e_Page->Text;
   if (this->LastDataType == 0) {
      Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
   } else if (this->LastDataType == 1) {
      Data = DecToHex(Data);
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 2;

   for (int i = 1; i <= 32; i++) {
      for(int j = 1; j <= 8; j++) {
         Data = this->sg_Ram->Cells[j][i];
         if (this->LastDataType == 0) {
            Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
         } else if (this->LastDataType == 1) {
            Data = DecToHex(Data);
         }
         this->sg_Ram->Cells[j][i] = Data;
      }
   }
   this->LastDataType = 2;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::b_SaveClick(TObject *Sender)
{
   (void)Sender;

   String Data;

   for (int i = 1; i <= 32; i++) {
      this->cds_Ram->Insert();

      this->cds_RamLine->AsInteger = i;

      for (int j = 1; j <= 8; j++) {
         Data = this->sg_Ram->Cells[j][i];

         if (this->rb_Bin->Checked) {
            Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
         } else if (this->rb_Dec->Checked) {
            Data = DecToHex(Data);
         }

         switch(j) {
            case 1: { this->cds_RamField01->AsString = Data; break;}
            case 2: { this->cds_RamField23->AsString = Data; break;}
            case 3: { this->cds_RamField45->AsString = Data; break;}
            case 4: { this->cds_RamField67->AsString = Data; break;}
            case 5: { this->cds_RamField89->AsString = Data; break;}
            case 6: { this->cds_RamFieldAB->AsString = Data; break;}
            case 7: { this->cds_RamFieldCD->AsString = Data; break;}
            case 8: { this->cds_RamFieldEF->AsString = Data; break;}
         }
      }
      this->cds_Ram->Post();
   }

   if (this->sd_Ram->Execute()) {
      if (this->sd_Ram->FileName != "") {
         this->cds_Ram->SaveToFile(this->sd_Ram->FileName, dfXML);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::b_LoadClick(TObject *Sender)
{
   (void)Sender;

   String Data;
   int Line;

   if (this->od_Ram->Execute()) {
      if (this->od_Ram->FileName != "") {
         this->rb_Hex->Checked = true;
         this->CurrentPage = "00";
         this->e_Page->Text = this->CurrentPage;
         this->Caption = "RAM page: 0x" + this->CurrentPage;
         this->cds_Ram->Filter = "Page='00'";
         this->cds_Ram->LoadFromFile(this->od_Ram->FileName);
      }
   }

   this->cds_Ram->First();
   while (!this->cds_Ram->Eof) {
      if (this->cds_RamPage->AsString == this->CurrentPage) {
         Line = this->cds_RamLine->AsInteger;

         this->sg_Ram->Cells[1][Line] = this->cds_RamField01->AsString;
         this->sg_Ram->Cells[2][Line] = this->cds_RamField23->AsString;
         this->sg_Ram->Cells[3][Line] = this->cds_RamField45->AsString;
         this->sg_Ram->Cells[4][Line] = this->cds_RamField67->AsString;
         this->sg_Ram->Cells[5][Line] = this->cds_RamField89->AsString;
         this->sg_Ram->Cells[6][Line] = this->cds_RamFieldAB->AsString;
         this->sg_Ram->Cells[7][Line] = this->cds_RamFieldCD->AsString;
         this->sg_Ram->Cells[8][Line] = this->cds_RamFieldEF->AsString;
      }
      this->cds_Ram->Next();
   }
}
//---------------------------------------------------------------------------
void Tf_Ram::AddrToXY(String Addr, int &X, int &Y)
{
   char high = Addr[1];
   int  Low  = StrToIntDef( "0x" + Addr[2], 0 );

   Y = Low + 1;
   switch (high) {
      case '0' : X = 1;          break;
      case '1' : X = 1; Y += 16; break;
      case '2' : X = 2;          break;
      case '3' : X = 2; Y += 16; break;
      case '4' : X = 3;          break;
      case '5' : X = 3; Y += 16; break;
      case '6' : X = 4;          break;
      case '7' : X = 4; Y += 16; break;
      case '8' : X = 5;          break;
      case '9' : X = 5; Y += 16; break;
      case 'A' : X = 6;          break;
      case 'B' : X = 6; Y += 16; break;
      case 'C' : X = 7;          break;
      case 'D' : X = 7; Y += 16; break;
      case 'E' : X = 8;          break;
      case 'F' : X = 8; Y += 16; break;
   }
}
//---------------------------------------------------------------------------
void Tf_Ram::Set(String Addr, String Value, String Page)
{
   int X, Y;
   String Data;

   this->AddrToXY(Addr, X, Y);

   if (this->rb_Bin->Checked) {
      Data = Value.UpperCase();
      Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
   } else if (this->rb_Dec->Checked) {
      Data = Value.UpperCase();
      Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1, 1))) * 16) + StrToInt(HexToDec(Data.SubString(2, 1))) );
   } else {
      Data = Value;
   }

   if (this->CurrentPage != Page) {
      this->SwapPage(this->CurrentPage, Page);
   }

   this->sg_Ram->Cells[X][Y] = Data;
   this->CleanUpData(X, Y);
}
//---------------------------------------------------------------------------
void Tf_Ram::Get(String Addr, char *Value, String Page)
{
   int X, Y;
   String Data;

   if (this->CurrentPage != Page) {
      this->SwapPage(this->CurrentPage, Page);
   }

   this->AddrToXY(Addr, X, Y);
   Data = this->sg_Ram->Cells[X][Y];

   if (this->rb_Dec->Checked) {
      Data = DecToHex(Data);
      Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
   } else if (this->rb_Hex->Checked) {
      Data = Data.UpperCase();
      Data = HexToBin(Data.SubString(1, 1)) + HexToBin(Data.SubString(2, 1));
   }

   strncpy(Value,AnsiString(Data).c_str(),8);
}
//---------------------------------------------------------------------------
TClientDataSet* Tf_Ram::GetDMA(void)
{
   return this->cds_Ram;
}
//---------------------------------------------------------------------------
String __fastcall Tf_Ram::GetDMAField(int id)
{
   switch (id) {
      case FIELD_PAGE  : return this->cds_RamPage->AsString;
      case FIELD_LINE  : return this->cds_RamLine->AsString;
      case FIELD_00_1F : return this->cds_RamField01->AsString;
      case FIELD_20_3F : return this->cds_RamField23->AsString;
      case FIELD_40_5F : return this->cds_RamField45->AsString;
      case FIELD_60_7F : return this->cds_RamField67->AsString;
      case FIELD_80_9F : return this->cds_RamField89->AsString;
      case FIELD_A0_BF : return this->cds_RamFieldAB->AsString;
      case FIELD_C0_DF : return this->cds_RamFieldCD->AsString;
      case FIELD_E0_FF : return this->cds_RamFieldEF->AsString;
      default : return "";
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::e_PageExit(TObject *Sender)
{
   (void)Sender;

   String Data = this->e_Page->Text.UpperCase();

   if (this->rb_Bin->Checked) {
      if (Data.Length() < 8) {
         while (Data.Length() < 8) {
            Data = "0" + Data;
         }
      } else {
         Data = Data.SubString(1, 8);
      }

      this->e_Page->Text = Data;
      Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
   } else if (this->rb_Dec->Checked) {
      Data = Data.SubString(1,3);
      if (Data == "") {
         Data = "0";
      } else if (StrToInt(Data) > 255) {
         Data = "255";
      }

      this->e_Page->Text = Data;
      Data = DecToHex(Data);
   } else {
      if (Data.Length() < 2){
         while (Data.Length() < 2) {
            Data = "0" + Data;
         }
      } else {
         Data = Data.SubString(1, 2);
      }
      this->e_Page->Text = Data;
   }
   this->SwapPage(this->CurrentPage, Data);
}
//---------------------------------------------------------------------------

void Tf_Ram::SwapPage(String Current, String New)
{
   String Data;
   int Line;
   int Mode = 2;
   TLocateOptions SrOpt; // ?? loCaseInsensitive

   for (int i = 1; i <= 32; i++) {
      if (this->cds_Ram->Locate("Line", i, SrOpt)) {
         this->cds_Ram->Edit();
      } else {
         this->cds_Ram->Insert();
         this->cds_RamLine->AsInteger = i;
         this->cds_RamPage->AsString = this->CurrentPage;
      }

      for (int j = 1; j <= 8; j++) {
         Data = this->sg_Ram->Cells[j][i];
         this->sg_Ram->Cells[j][i] = "00";

         if (this->rb_Bin->Checked) {
            Data = BinToHex(Data.SubString(1, 4)) + BinToHex(Data.SubString(5, 4));
         } else if (this->rb_Dec->Checked) {
            Data = DecToHex(Data);
         }

         switch(j) {
            case 1: { this->cds_RamField01->AsString = Data; break;}
            case 2: { this->cds_RamField23->AsString = Data; break;}
            case 3: { this->cds_RamField45->AsString = Data; break;}
            case 4: { this->cds_RamField67->AsString = Data; break;}
            case 5: { this->cds_RamField89->AsString = Data; break;}
            case 6: { this->cds_RamFieldAB->AsString = Data; break;}
            case 7: { this->cds_RamFieldCD->AsString = Data; break;}
            case 8: { this->cds_RamFieldEF->AsString = Data; break;}
         }
      }
      this->cds_Ram->Post();
   }

   this->CurrentPage = New.UpperCase();
   this->Caption = "RAM page: 0x" + this->CurrentPage;
   this->cds_Ram->Filter = "Page='" + this->CurrentPage + "'";
   //this->cds_Ram->RecordCount

   if (this->rb_Bin->Checked) {
      Mode = 0;
   } else if (this->rb_Dec->Checked) {
      Mode = 1;
   }

   this->rb_Hex->Checked = true;
   this->cds_Ram->First();
   while (!this->cds_Ram->Eof) {
      if (this->cds_RamPage->AsString == this->CurrentPage) {
         Line = this->cds_RamLine->AsInteger;

         this->sg_Ram->Cells[1][Line] = this->cds_RamField01->AsString;
         this->sg_Ram->Cells[2][Line] = this->cds_RamField23->AsString;
         this->sg_Ram->Cells[3][Line] = this->cds_RamField45->AsString;
         this->sg_Ram->Cells[4][Line] = this->cds_RamField67->AsString;
         this->sg_Ram->Cells[5][Line] = this->cds_RamField89->AsString;
         this->sg_Ram->Cells[6][Line] = this->cds_RamFieldAB->AsString;
         this->sg_Ram->Cells[7][Line] = this->cds_RamFieldCD->AsString;
         this->sg_Ram->Cells[8][Line] = this->cds_RamFieldEF->AsString;
      }
      this->cds_Ram->Next();
   }
   if (this->CurrentPage != this->e_Page->Text) {
      this->e_Page->Text = this->CurrentPage;
   }
   this->ud_Page->Position = (StrToInt(HexToDec(this->CurrentPage.SubString(1, 1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2, 1)));

   if (Mode == 0) {
      this->rb_Bin->Checked = true;
   } else if (Mode == 1) {
      this->rb_Dec->Checked = true;
   }
}

//---------------------------------------------------------------------------

void __fastcall Tf_Ram::b_ImportClick(TObject *Sender)
{
   (void)Sender;

   ifstream FileId;
   String Buffer;  //65536
   String Byte;
   char fBuffer[512];
   int  LengthLeft;
   int  FirstI;
   int  NbPage = (StrToInt(HexToDec(this->CurrentPage.SubString(1, 1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2, 1)));
   bool FirstPage = true;

   if (od_Import->Execute()) {
      if (od_Import->FileName != "") {
         FileId.open(od_Import->FileName.c_str());
         if (!FileId.fail() && !FileId.bad()) {
            this->rb_Hex->Checked = true;
            while (!FileId.eof() && NbPage < 256) {
               FileId.getline(fBuffer, 512);
               Buffer = fBuffer;

               if (!FirstPage) { //I know...
                  this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage) ));
                  this->sg_Ram->Row=1;
                  this->sg_Ram->Col=1;
               }

               FirstI = this->sg_Ram->Row;
               for (int j = this->sg_Ram->Col; j <= 8; j++) {
                  for (int i = FirstI; i <= 32; i++) {
                     if (Buffer.Length() == 1 ) {
                        Buffer = Buffer + "0";
                     }

                     Byte = Buffer.SubString(0, 2);
                     if (Byte != "  ") {
                        this->sg_Ram->Cells[j][i] = Byte;
                     }
                     Buffer = Buffer.SubString(3, Buffer.Length());

                     if (Buffer.Length() == 0 ) {
                        break;
                     }
                  }
                  if (Buffer.Length() == 0 ) {
                     break;
                  } else {
                     FirstI = 1;
                  }
               }
               NbPage++;
               FirstPage = false;
            }//While
            //this->rb_Hex->Checked = true;
         }
         FileId.close();
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::ud_PageClick(TObject *Sender, TUDBtnType Button)
{
   (void)Sender;

   int  NbPage = (StrToInt(HexToDec(this->CurrentPage.SubString(1, 1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2, 1)));
   if (Button == btNext && NbPage < 255) {
      this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage + 1)));
   } else if (Button == btPrev && NbPage > 0) {
      this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage - 1)));
   }
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::b_ClearPClick(TObject *Sender)
{
   (void)Sender;

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         if (this->rb_Bin->Checked) {
            this->sg_Ram->Cells[j][i] = "00000000";
         } else if(this->rb_Dec->Checked) {
            this->sg_Ram->Cells[j][i] = "0";
         } else {
            this->sg_Ram->Cells[j][i] = "00";
         }
      }
   }
}
//---------------------------------------------------------------------------

void Tf_Ram::ResetState(void)
{
   this->cds_Ram->Filter = "";
   this->cds_Ram->First();
   while (!this->cds_Ram->Eof) {
      this->cds_Ram->Edit();
      this->cds_RamField01->AsString = "00";
      this->cds_RamField23->AsString = "00";
      this->cds_RamField45->AsString = "00";
      this->cds_RamField67->AsString = "00";
      this->cds_RamField89->AsString = "00";
      this->cds_RamFieldAB->AsString = "00";
      this->cds_RamFieldCD->AsString = "00";
      this->cds_RamFieldEF->AsString = "00";
      this->cds_Ram->Post();
      this->cds_Ram->Next();
   }
   this->cds_Ram->Filter = "Page='00'";

   this->b_ClearP->Click();
   this->LastDataType = 2;
   this->rb_Hex->Checked = true;

   this->LastX = -1;
   this->LastY = -1;

   this->CurrentPage = "00";
   this->e_Page->Text = this->CurrentPage;
   this->Caption = "RAM page: 0x" + this->CurrentPage;

   for (int i = 1; i <= 32; i++) {
      for (int j = 1; j <= 8; j++) {
         this->sg_Ram->Cells[j][i] = "00";
      }
   }
}
//---------------------------------------------------------------------------

