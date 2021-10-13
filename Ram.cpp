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
void __fastcall Tf_Ram::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = false;    
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::FormCreate(TObject *Sender)
{
  this->LastX = -1;
  this->LastY = -1;

  this->CurrentPage = "00";
  this->e_Page->Text = this->CurrentPage;
  f_Ram->Caption = "RAM page: 0x" + this->CurrentPage;
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

  for(int i=1;i<=32;i++)
  {
	 for(int j=1;j<=8;j++)
	 {
		this->sg_Ram->Cells[j][i] = "00";
	 }
  }
  this->LastDataType = 2;
  this->rb_Hex->Checked = true;

  this->cds_Ram->CreateDataSet();
  this->cds_Ram->Open();
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::sg_RamKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_RETURN)
     e_PageExit(Sender);
  else if(Key != VK_TAB && Key != VK_LEFT && Key != VK_RIGHT && Key != VK_BACK && Key != VK_CLEAR &&
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
void __fastcall Tf_Ram::sg_RamExit(TObject *Sender)
{
   for(int i=1;i<=32;i++)
   {
       for(int j=1;j<=8;j++)
       {
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

   if(X != -1 && Y != -1)
   {
       Data = this->sg_Ram->Cells[X][Y];
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
			 Data = Data.SubString(1,8);
       }
       else if(this->rb_Dec->Checked)
       {
          Data = Data.SubString(1,3);
          if(Data == "")
          {
             Data = "0";
          }
		  else if (StrToInt(Data) > 255)
			 Data = "255";
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
			 Data = Data.SubString(1,2);
       }
       this->sg_Ram->Cells[X][Y] = Data;
   }
}
//---------------------------------------------------------------------------
String Tf_Ram::BinToHex(String Hex)
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
String Tf_Ram::HexToDec(String Hex)
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
String Tf_Ram::HexToBin(String Hex)
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
String Tf_Ram::DecToHex(String Hex)
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
void __fastcall Tf_Ram::rb_BinClick(TObject *Sender)
{
   String Data;

   Data = this->e_Page->Text;
   if(this->LastDataType == 1)
   {
	 Data = Data.UpperCase();
	 Data = DecToHex(Data);
	 Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
   }
   else if (this->LastDataType == 2)
   {
	 Data = Data.UpperCase();
	 Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 8;

   for(int i=1;i<=32;i++)
   {
       for(int j=1;j<=8;j++)
       {
          Data = this->sg_Ram->Cells[j][i];
		  if(this->LastDataType == 1)
		  {
			 Data = Data.UpperCase();
			 Data = DecToHex(Data);
			 Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
		  }
		  else if (this->LastDataType == 2)
		  {
			 Data = Data.UpperCase();
			 Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
		  }
          this->sg_Ram->Cells[j][i] = Data;
       }
   }
   this->LastDataType = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::rb_DecClick(TObject *Sender)
{
   String Data;

   Data = this->e_Page->Text;
   if(this->LastDataType == 0)
   {
	 Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
	 Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1,1))) * 16) + StrToInt(HexToDec(Data.SubString(2,1))) );
   }
   else if (this->LastDataType == 2)
   {
	 Data = Data.UpperCase();
	 Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1,1))) * 16) + StrToInt(HexToDec(Data.SubString(2,1))) );
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 3;

   for(int i=1;i<=32;i++)
   {
       for(int j=1;j<=8;j++)
       {
            Data = this->sg_Ram->Cells[j][i];
			if(this->LastDataType == 0)
			{
			  Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
			  Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1,1))) * 16) + StrToInt(HexToDec(Data.SubString(2,1))) );
			}
			else if (this->LastDataType == 2)
			{
			   Data = Data.UpperCase();
			   Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1,1))) * 16) + StrToInt(HexToDec(Data.SubString(2,1))) );
			}
            this->sg_Ram->Cells[j][i] = Data;
       }
   }
  this->LastDataType = 1;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::rb_HexClick(TObject *Sender)
{
   String Data;

   Data = this->e_Page->Text;
   if(this->LastDataType == 0)
   {
     Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
   }
   else if (this->LastDataType == 1)
   {
	 Data = DecToHex(Data);
   }
   this->e_Page->Text = Data;
   this->e_Page->MaxLength = 2;

   for(int i=1;i<=32;i++)
   {
       for(int j=1;j<=8;j++)
       {
            Data = this->sg_Ram->Cells[j][i];
			if(this->LastDataType == 0)
			{
			  Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
			}
			else if (this->LastDataType == 1)
			{
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
  String Data;

  for(int i=1;i<=32;i++)
  {
    this->cds_Ram->Insert();

    cds_RamLine->AsInteger = i;

    for(int j=1;j<=8;j++)
    {
        Data = this->sg_Ram->Cells[j][i];

		if(this->rb_Bin->Checked)
		   Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
		else if(this->rb_Dec->Checked)
		   Data = DecToHex(Data);

        switch(j)
		{
            case 1: { cds_RamField01->AsString = Data; break;}
            case 2: { cds_RamField23->AsString = Data; break;}
            case 3: { cds_RamField45->AsString = Data; break;}
            case 4: { cds_RamField67->AsString = Data; break;}
            case 5: { cds_RamField89->AsString = Data; break;}
            case 6: { cds_RamFieldAB->AsString = Data; break;}
            case 7: { cds_RamFieldCD->AsString = Data; break;}
            case 8: { cds_RamFieldEF->AsString = Data; break;}
        }
    }

    this->cds_Ram->Post();
  }

  if (sd_Ram->Execute())
  {
	if(sd_Ram->FileName != "")
      cds_Ram->SaveToFile(sd_Ram->FileName, dfXML);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Ram::b_LoadClick(TObject *Sender)
{
  String Data;
  int Line;

  if (od_Ram->Execute())
  {
	if(od_Ram->FileName != "")
	{
	  this->rb_Hex->Checked = true;
	  this->CurrentPage = "00";
	  this->e_Page->Text = this->CurrentPage;
	  f_Ram->Caption = "RAM page: 0x" + this->CurrentPage;
	  this->cds_Ram->Filter = "Page='00'";
	  cds_Ram->LoadFromFile(od_Ram->FileName);
	}
  }

  this->cds_Ram->First();
  while(!this->cds_Ram->Eof)
  {
	if(cds_RamPage->AsString == this->CurrentPage)
	{
	  Line = cds_RamLine->AsInteger;

	  this->sg_Ram->Cells[1][Line] = cds_RamField01->AsString;
	  this->sg_Ram->Cells[2][Line] = cds_RamField23->AsString;
	  this->sg_Ram->Cells[3][Line] = cds_RamField45->AsString;
	  this->sg_Ram->Cells[4][Line] = cds_RamField67->AsString;
	  this->sg_Ram->Cells[5][Line] = cds_RamField89->AsString;
	  this->sg_Ram->Cells[6][Line] = cds_RamFieldAB->AsString;
	  this->sg_Ram->Cells[7][Line] = cds_RamFieldCD->AsString;
	  this->sg_Ram->Cells[8][Line] = cds_RamFieldEF->AsString;
	}

	this->cds_Ram->Next();
  }
}
//---------------------------------------------------------------------------
void Tf_Ram::AddrToXY(String Addr, int &X, int &Y)
{
    String High = Addr.SubString(1,1);
    int    Low  = StrToInt( "0x" + Addr.SubString(2,1) );

    Y = Low + 1;
         if(High == "0") {X = 1;}
    else if(High == "1") {X = 1; Y += 16; }
    else if(High == "2") {X = 2;}
    else if(High == "3") {X = 2; Y += 16; }
    else if(High == "4") {X = 3;}
    else if(High == "5") {X = 3; Y += 16; }
    else if(High == "6") {X = 4;}
    else if(High == "7") {X = 4; Y += 16; }
    else if(High == "8") {X = 5;}
    else if(High == "9") {X = 5; Y += 16; }
    else if(High == "A") {X = 6;}
    else if(High == "B") {X = 6; Y += 16; }
    else if(High == "C") {X = 7;}
    else if(High == "D") {X = 7; Y += 16; }
    else if(High == "E") {X = 8;}
    else if(High == "F") {X = 8; Y += 16; }
}
//---------------------------------------------------------------------------
void Tf_Ram::Set(String Addr, String Value, String Page)
{
   int X, Y;
   String Data;

   this->AddrToXY(Addr, X, Y);

   if(this->rb_Bin->Checked)
   {
	   Data = Value.UpperCase();
	   Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
   }
   else if(this->rb_Dec->Checked)
   {
	   Data = Value.UpperCase();
	   Data = IntToStr( (StrToInt(HexToDec(Data.SubString(1,1))) * 16) + StrToInt(HexToDec(Data.SubString(2,1))) );
   }
   else
   {
	   Data = Value;
   }

   this->sg_Ram->Cells[X][Y] = Data;

   if (this->CurrentPage != Page)
   {
	  this->SwapPage(this->CurrentPage, Page);
   }
}
//---------------------------------------------------------------------------
void Tf_Ram::Get(String Addr, char *Value, String Page)
{
   int X, Y;
   String Data;

   this->AddrToXY(Addr, X, Y);
   Data = this->sg_Ram->Cells[X][Y];

   if(this->rb_Dec->Checked)
   {
             Data = DecToHex(Data);
             Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
   }
   else if (this->rb_Hex->Checked)
   {
             Data = Data.UpperCase();
             Data = HexToBin(Data.SubString(1,1)) + HexToBin(Data.SubString(2,1));
   }

   strncpy(Value,AnsiString(Data).c_str(),8);
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::sg_RamSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   this->CleanUpData(this->LastX, this->LastY);

   this->LastX = ACol;
   this->LastY = ARow;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Ram::e_PageExit(TObject *Sender)
{
   String Data = this->e_Page->Text.UpperCase();

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
		 Data = Data.SubString(1,8);

	  this->e_Page->Text = Data;
	  Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
   }
   else if(this->rb_Dec->Checked)
   {
      Data = Data.SubString(1,3);
      if(Data == "")
      {
         Data = "0";
      }
	  else if (StrToInt(Data) > 255)
		 Data = "255";

	  this->e_Page->Text = Data;
	  Data = DecToHex(Data);
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
		 Data = Data.SubString(1,2);

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

   for(int i=1;i<=32;i++)
   {
	 if(this->cds_Ram->Locate("Line", i, SrOpt))
	   this->cds_Ram->Edit();
	 else
	 {
	   this->cds_Ram->Insert();
	   this->cds_RamLine->AsInteger = i;
	   this->cds_RamPage->AsString = this->CurrentPage;
     }

	 for(int j=1;j<=8;j++)
	 {
		 Data = this->sg_Ram->Cells[j][i];
		 this->sg_Ram->Cells[j][i] = "00";

		 if(this->rb_Bin->Checked)
			Data = BinToHex(Data.SubString(1,4)) + BinToHex(Data.SubString(5,4));
		 else if(this->rb_Dec->Checked)
			Data = DecToHex(Data);

		 switch(j)
		 {
			 case 1: { cds_RamField01->AsString = Data; break;}
			 case 2: { cds_RamField23->AsString = Data; break;}
			 case 3: { cds_RamField45->AsString = Data; break;}
			 case 4: { cds_RamField67->AsString = Data; break;}
			 case 5: { cds_RamField89->AsString = Data; break;}
			 case 6: { cds_RamFieldAB->AsString = Data; break;}
			 case 7: { cds_RamFieldCD->AsString = Data; break;}
			 case 8: { cds_RamFieldEF->AsString = Data; break;}
		 }
	 }

	 this->cds_Ram->Post();
   }

   this->CurrentPage = New.UpperCase();
   f_Ram->Caption = "RAM page: 0x" + this->CurrentPage;
   this->cds_Ram->Filter = "Page='" + this->CurrentPage + "'";
   //this->cds_Ram->RecordCount

   if(this->rb_Bin->Checked)
	 Mode = 0;
   else if(this->rb_Dec->Checked)
	 Mode = 1;

   this->rb_Hex->Checked = true;
   this->cds_Ram->First();
   while(!this->cds_Ram->Eof)
   {
	 if(this->cds_RamPage->AsString == this->CurrentPage)
	 {
	   Line = this->cds_RamLine->AsInteger;

	   this->sg_Ram->Cells[1][Line] = cds_RamField01->AsString;
	   this->sg_Ram->Cells[2][Line] = cds_RamField23->AsString;
	   this->sg_Ram->Cells[3][Line] = cds_RamField45->AsString;
	   this->sg_Ram->Cells[4][Line] = cds_RamField67->AsString;
	   this->sg_Ram->Cells[5][Line] = cds_RamField89->AsString;
	   this->sg_Ram->Cells[6][Line] = cds_RamFieldAB->AsString;
	   this->sg_Ram->Cells[7][Line] = cds_RamFieldCD->AsString;
	   this->sg_Ram->Cells[8][Line] = cds_RamFieldEF->AsString;
	 }

	 this->cds_Ram->Next();
   }

   if(this->CurrentPage != this->e_Page->Text)
	  this->e_Page->Text = this->CurrentPage;
   this->ud_Page->Position = (StrToInt(HexToDec(this->CurrentPage.SubString(1,1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2,1)));

   if(Mode == 0)
	 this->rb_Bin->Checked = true;
   else if(Mode == 1)
	 this->rb_Dec->Checked = true;
}

//---------------------------------------------------------------------------

void __fastcall Tf_Ram::b_ImportClick(TObject *Sender)
{
  ifstream FileId;
  String Buffer;  //65536
  String Byte;
  char fBuffer[512];
  int  LengthLeft;
  int  FirstI;
  int  NbPage = (StrToInt(HexToDec(this->CurrentPage.SubString(1,1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2,1)));
  bool FirstPage = true;

  if (od_Import->Execute())
  {
	if(od_Import->FileName != "")
	{
	  FileId.open(od_Import->FileName.c_str());
	  if(!FileId.fail() && !FileId.bad())
	  {
		this->rb_Hex->Checked = true;
		while(!FileId.eof() && NbPage<256)
		{
		  FileId.getline(fBuffer, 512);
		  Buffer = fBuffer;

		  if(!FirstPage) //I know...
		  {
			this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage) ));
			this->sg_Ram->Row=1;
            this->sg_Ram->Col=1;
		  }

		  FirstI = this->sg_Ram->Row;
		  for(int j=this->sg_Ram->Col;j<=8;j++)
		  {
			 for(int i=FirstI;i<=32;i++)
			 {
				if (Buffer.Length() == 1 )
				   Buffer = Buffer + "0";

				Byte = Buffer.SubString(0, 2);
				if (Byte != "  ")
				   this->sg_Ram->Cells[j][i] = Byte;
				Buffer = Buffer.SubString(3, Buffer.Length());

				if(Buffer.Length() == 0 )
				   break;
			 }
			 if(Buffer.Length() == 0 )
				break;
			 else
				FirstI = 1;
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
  int  NbPage = (StrToInt(HexToDec(this->CurrentPage.SubString(1,1))) * 16) + StrToInt(HexToDec(this->CurrentPage.SubString(2,1)));
  if(Button == btNext && NbPage < 255)
	this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage+1) ));
  else if(Button == btPrev && NbPage > 0)
	this->SwapPage(this->CurrentPage, DecToHex(IntToStr(NbPage-1) ));
}
//---------------------------------------------------------------------------

