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
         this->Canvas->TextOut(screenRect.left+(x*11)+12, screenRect.top+(y*18)+12, this->screenArray[x][y]);
      }
   }

}
//---------------------------------------------------------------------------
void __fastcall Tf_Terminal::tRefreshTimer(TObject *Sender)
{
   for (int x = 0; x < 51; x++) {
      for (int y = 0; y < 20; y++) {
         this->screenArray[x][y] = "";
      }
   }

   f_Ram->cds_Ram->First();
   while (!f_Ram->cds_Ram->Eof) {
      int page = HexToInt(f_Ram->cds_RamPage->AsString) - 252;
      if (page >= 0) {
         int line = f_Ram->cds_RamLine->AsInteger - 1;
         String value[8];

         value[0] = f_Ram->cds_RamField01->AsString;
         value[1] = f_Ram->cds_RamField23->AsString;
         value[2] = f_Ram->cds_RamField45->AsString;
         value[3] = f_Ram->cds_RamField67->AsString;
         value[4] = f_Ram->cds_RamField89->AsString;
         value[5] = f_Ram->cds_RamFieldAB->AsString;
         value[6] = f_Ram->cds_RamFieldCD->AsString;
         value[7] = f_Ram->cds_RamFieldEF->AsString;

         for (int i = 0; i < 8; i++) {
            if (value[i] >= 32) {
               int offset = (i*32) + line + (page * 5) ;
               screenArray[offset%50][offset/50].SetLength(1);
               screenArray[offset%50][offset/50][1] = static_cast<char>(HexToInt(value[i]));
            }
         }
      }
      f_Ram->cds_Ram->Next();
   }

   this->Invalidate();
}
//---------------------------------------------------------------------------
int Tf_Terminal::HexToInt(String Hex)
{
   String HexHigh = "";
   int OutVal;

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
