//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Terminal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_Terminal *f_Terminal;

class TPanelCracker : public Extctrls::TPanel {
public:
    __property Canvas; // Unhides the protected Canvas property
};

//---------------------------------------------------------------------------
__fastcall Tf_Terminal::Tf_Terminal(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::FormPaint(TObject *Sender)
{
   (void)Sender;

   TRect screenRect;

   screenRect.init(this->pScreen->Left,  this->pScreen->Top,
                   this->pScreen->Width, this->pScreen->Height);

   this->Canvas->Brush->Color = clBlack;
   this->Canvas->FillRect(screenRect);
   this->Canvas->Font->Name = "Arial";
   this->Canvas->Font->Size = 12;
   this->Canvas->Font->Color = clLime;

   for (int x = 0; x < 51; x++) {
      for (int y = 0; y < 20; y++) {
         this->Canvas->TextOut(screenRect.left+(x*11)+12, screenRect.top+(y*18)+12,
                               static_cast<char>(this->screenArray[x][y]));
      }
   }

}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::tRefreshTimer(TObject *Sender)
{
   (void)Sender;

   RefreshScreen();
}
//---------------------------------------------------------------------------
void Tf_Terminal::RefreshScreen(void)
{
   for (int x = 0; x < 51; x++) {
      for (int y = 0; y < 20; y++) {
         this->screenArray[x][y] = 0;//"";
      }
   }

   String filter = f_Ram->cds_Ram->Filter;
   f_Ram->cds_Ram->Filter = "Page>'FB'";
   f_Ram->cds_Ram->First();

   while (!f_Ram->cds_Ram->Eof) {
      int page = HexToInt(f_Ram->cds_RamPage->AsString) - 252;
      if (page >= 0) {
         int line = f_Ram->cds_RamLine->AsInteger - 1;
         String valueHex[8];

         valueHex[0] = f_Ram->cds_RamField01->AsString;
         valueHex[1] = f_Ram->cds_RamField23->AsString;
         valueHex[2] = f_Ram->cds_RamField45->AsString;
         valueHex[3] = f_Ram->cds_RamField67->AsString;
         valueHex[4] = f_Ram->cds_RamField89->AsString;
         valueHex[5] = f_Ram->cds_RamFieldAB->AsString;
         valueHex[6] = f_Ram->cds_RamFieldCD->AsString;
         valueHex[7] = f_Ram->cds_RamFieldEF->AsString;

         for (int i = 0; i < 8; i++) {
            int value = HexToInt(valueHex[i]);

            if (value >= 32) {
               int offset = (i*32) + line + (page * 256) - page;
               screenArray[offset%51][offset/51] = value;
            }
         }
      }
      f_Ram->cds_Ram->Next();
   }
   f_Ram->cds_Ram->Filter = filter;

   this->Invalidate();
}
//---------------------------------------------------------------------------
int Tf_Terminal::HexToInt(String Hex)
{
   String HexHigh = "";
   int OutVal;

   if (Hex.Length() < 1) {
      return 0;
   }

   if (Hex.Length() > 1) {
      HexHigh = Hex.SubString(1, 1);
      Hex     = Hex.SubString(2, 1);
   }


   switch (Hex[1]) {
      case '0': OutVal = 0;  break;
      case '1': OutVal = 1;  break;
      case '2': OutVal = 2;  break;
      case '3': OutVal = 3;  break;
      case '4': OutVal = 4;  break;
      case '5': OutVal = 5;  break;
      case '6': OutVal = 6;  break;
      case '7': OutVal = 7;  break;
      case '8': OutVal = 8;  break;
      case '9': OutVal = 9;  break;
      case 'A': OutVal = 10; break;
      case 'B': OutVal = 11; break;
      case 'C': OutVal = 12; break;
      case 'D': OutVal = 13; break;
      case 'E': OutVal = 14; break;
      case 'F': OutVal = 15; break;
      default:  OutVal = 0;
   }

   if (HexHigh != "") {
      switch (HexHigh[1]) {
         case '0': break;
         case '1': OutVal += 16;  break;
         case '2': OutVal += 32;  break;
         case '3': OutVal += 48;  break;
         case '4': OutVal += 64;  break;
         case '5': OutVal += 80;  break;
         case '6': OutVal += 96;  break;
         case '7': OutVal += 112; break;
         case '8': OutVal += 128; break;
         case '9': OutVal += 144; break;
         case 'A': OutVal += 160; break;
         case 'B': OutVal += 176; break;
         case 'C': OutVal += 192; break;
         case 'D': OutVal += 208; break;
         case 'E': OutVal += 224; break;
         case 'F': OutVal += 240; break;
      }
   }

   return OutVal;
}
//---------------------------------------------------------------------------
void Tf_Terminal::IOOut(String cmdHex, String valueHex)
{
   int cmd   = HexToInt(cmdHex);
   int value = HexToInt(valueHex);

   if (cmd == 0x01) {
      switch (value) {
         case 0x00 : this->RefreshScreen(); break;
         case 0x01 : this->pBuzy->Color = clLime; break;
         case 0x02 : this->pBuzy->Color = clRed; break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::sbBootClick(TObject *Sender)
{
   (void)Sender;

   if (this->sbBoot->Down) {
      f_GraphIO->Pin70->Checked = true;
   } else {
      f_GraphIO->Pin70->Checked = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::sbHaltClick(TObject *Sender)
{
   (void)Sender;

   f_GraphIO->Pin39->Checked = this->sbHalt->Down;
}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::FormCreate(TObject *Sender)
{
   (void)Sender;

   this->sbBoot->Down = true;
   this->sbBoot->Caption = "Reset";
   this->sbHalt->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall Tf_Terminal::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
   (void)Sender;

   if (Key >= 0x20 && Key <= 0x7E) {
      this->lValue->Caption = "0x" + IntToHex(Key, 2) + " (" + Key + ")";
      this->pInterrupt->Color = clYellow;

      char value = Key;

      f_GraphIO->SetIO(0x01, value);
      f_GraphIO->Pin18->Checked = true;

      Key = 0;
   }
}
//---------------------------------------------------------------------------

