//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphIO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_GraphIO *f_GraphIO;
//---------------------------------------------------------------------------
__fastcall Tf_GraphIO::Tf_GraphIO(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::Pin70Click(TObject *Sender)
{
  char Instruction[17];

  f_Memory->cds_Mem->First();

  //CPU boot, load first instruction
  if(this->Pin49->Checked)
  {
      strncpy(Instruction, AnsiString(f_Memory->cds_MemCode->AsString).c_str(),17);
      Instruction[16] = '\0';

      this->Pin1->Checked  = Instruction[0]  != '0';
      this->Pin2->Checked  = Instruction[1]  != '0';
      this->Pin3->Checked  = Instruction[2]  != '0';
      this->Pin4->Checked  = Instruction[3]  != '0';
      this->Pin5->Checked  = Instruction[4]  != '0';
      this->Pin6->Checked  = Instruction[5]  != '0';
      this->Pin7->Checked  = Instruction[6]  != '0';
      this->Pin8->Checked  = Instruction[7]  != '0';
      this->Pin9->Checked  = Instruction[8]  != '0';
      this->Pin10->Checked = Instruction[9]  != '0';
      this->Pin11->Checked = Instruction[10] != '0';
      this->Pin12->Checked = Instruction[11] != '0';
      this->Pin13->Checked = Instruction[12] != '0';
      this->Pin14->Checked = Instruction[13] != '0';
      this->Pin15->Checked = Instruction[14] != '0';
      this->Pin16->Checked = Instruction[15] != '0';
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::Pin30Click(TObject *Sender)
{
  //CPU RAM write flag
  if(this->Pin30->Checked)
  {
      //21-28
      String c1 = BinToHex(Pin21->Checked, Pin22->Checked, Pin23->Checked, Pin24->Checked);
      String c2 = BinToHex(Pin25->Checked, Pin26->Checked, Pin27->Checked, Pin28->Checked);
      String Addr = c2 + c1;

      //31-38
      c1 = BinToHex(Pin31->Checked, Pin32->Checked, Pin33->Checked, Pin34->Checked);
      c2 = BinToHex(Pin35->Checked, Pin36->Checked, Pin37->Checked, Pin38->Checked);
	  String Value = c2 + c1;

	  //61-68
	  c1 = BinToHex(Pin61->Checked, Pin62->Checked, Pin63->Checked, Pin64->Checked);
	  c2 = BinToHex(Pin65->Checked, Pin66->Checked, Pin67->Checked, Pin68->Checked);
	  String Page = c2 + c1;

      f_Ram->Set(Addr, Value, Page);
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Pin40Click(TObject *Sender)
{
  //CPU RAM write flag
  if(this->Pin40->Checked)
  {
      //21-28
      String c1 = BinToHex(Pin21->Checked, Pin22->Checked, Pin23->Checked, Pin24->Checked);
      String c2 = BinToHex(Pin25->Checked, Pin26->Checked, Pin27->Checked, Pin28->Checked);
	  String Addr = c2 + c1;

	  //61-68
	  c1 = BinToHex(Pin61->Checked, Pin62->Checked, Pin63->Checked, Pin64->Checked);
	  c2 = BinToHex(Pin65->Checked, Pin66->Checked, Pin67->Checked, Pin68->Checked);
	  String Page = c2 + c1;

	  char Value[9];

      f_Ram->Get(Addr, Value, Page);

      this->Pin41->Checked  = Value[7]  != '0';
      this->Pin42->Checked  = Value[6]  != '0';
      this->Pin43->Checked  = Value[5]  != '0';
      this->Pin44->Checked  = Value[4]  != '0';
      this->Pin45->Checked  = Value[3]  != '0';
      this->Pin46->Checked  = Value[2]  != '0';
      this->Pin47->Checked  = Value[1]  != '0';
      this->Pin48->Checked  = Value[0]  != '0';
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::Pin50Click(TObject *Sender)
{
  char Instruction[17];
  int Delta;

  //CPU clock rising edge
  if(this->Pin50->Checked)
  {
      //51-58
      String c1 = BinToHex(Pin51->Checked, Pin52->Checked, Pin53->Checked, Pin54->Checked);
      String c2 = BinToHex(Pin55->Checked, Pin56->Checked, Pin57->Checked, Pin58->Checked);

      Delta = StrToInt("0x" + c2 + c1);

      f_Memory->MoveAddrByDelta(Delta);

      strncpy(Instruction, AnsiString(f_Memory->cds_MemCode->AsString).c_str(),17);
      Instruction[16] = '\0';

      this->Pin1->Checked  = Instruction[0]  != '0';
      this->Pin2->Checked  = Instruction[1]  != '0';
      this->Pin3->Checked  = Instruction[2]  != '0';
      this->Pin4->Checked  = Instruction[3]  != '0';
      this->Pin5->Checked  = Instruction[4]  != '0';
      this->Pin6->Checked  = Instruction[5]  != '0';
      this->Pin7->Checked  = Instruction[6]  != '0';
      this->Pin8->Checked  = Instruction[7]  != '0';
      this->Pin9->Checked  = Instruction[8]  != '0';
      this->Pin10->Checked = Instruction[9]  != '0';
      this->Pin11->Checked = Instruction[10] != '0';
      this->Pin12->Checked = Instruction[11] != '0';
      this->Pin13->Checked = Instruction[12] != '0';
      this->Pin14->Checked = Instruction[13] != '0';
      this->Pin15->Checked = Instruction[14] != '0';
      this->Pin16->Checked = Instruction[15] != '0';
  }

  if (f_Memory->cb_StepByStep->Checked) {
     Pin29->Checked = true;
     if (!f_CPUNode->cb_ActiveDraw->Checked) {
        f_CPUNode->CallDrawArea(1);
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::Pin60Click(TObject *Sender)
{
  char Instruction[17];
  int  Addr;

  //CPU clock rising edge
  if (this->Pin60->Checked) {
      //71-78
      String c1 = BinToHex(Pin71->Checked, Pin72->Checked, Pin73->Checked, Pin74->Checked);
      String c2 = BinToHex(Pin75->Checked, Pin76->Checked, Pin77->Checked, Pin78->Checked);
      //51-58
      String c3 = BinToHex(Pin51->Checked, Pin52->Checked, Pin53->Checked, Pin54->Checked);
      String c4 = BinToHex(Pin55->Checked, Pin56->Checked, Pin57->Checked, Pin58->Checked);

      Addr = StrToInt("0x" + c2 + c1 + c4 + c3);

      f_Memory->MoveAddrByAbsolute(Addr);

      strncpy(Instruction, AnsiString(f_Memory->cds_MemCode->AsString).c_str(),17);
      Instruction[16] = '\0';

      this->Pin1->Checked  = Instruction[0]  != '0';
      this->Pin2->Checked  = Instruction[1]  != '0';
      this->Pin3->Checked  = Instruction[2]  != '0';
      this->Pin4->Checked  = Instruction[3]  != '0';
      this->Pin5->Checked  = Instruction[4]  != '0';
      this->Pin6->Checked  = Instruction[5]  != '0';
      this->Pin7->Checked  = Instruction[6]  != '0';
      this->Pin8->Checked  = Instruction[7]  != '0';
      this->Pin9->Checked  = Instruction[8]  != '0';
      this->Pin10->Checked = Instruction[9]  != '0';
      this->Pin11->Checked = Instruction[10] != '0';
      this->Pin12->Checked = Instruction[11] != '0';
      this->Pin13->Checked = Instruction[12] != '0';
      this->Pin14->Checked = Instruction[13] != '0';
      this->Pin15->Checked = Instruction[14] != '0';
      this->Pin16->Checked = Instruction[15] != '0';
  }

  if (f_Memory->cb_StepByStep->Checked) {
     Pin29->Checked = true;
     if (!f_CPUNode->cb_ActiveDraw->Checked) {
        f_CPUNode->CallDrawArea(1);
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall Tf_GraphIO::b_ResetClick(TObject *Sender)
{
  TCheckBox * CurrPin;

  DebugOutState = false;
  f_Memory->dbg_Mem->Color = clWindow;

  f_Memory->cds_Mem->First();
  f_CPUNode->ResetAllNode();
  f_CPUNode->sb_Main->SimpleText =	"Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink          Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";

  for(int i=0; i<=60; i++)
  {
     CurrPin = (TCheckBox*)this->FindComponent("Pin" + IntToStr(i));
     if (CurrPin != NULL)
        CurrPin->Checked = false;
  }
}
//---------------------------------------------------------------------------
char Tf_GraphIO::BinToHex(bool p1, bool p2, bool p3, bool p4 )
{
    if     (!p1 && !p2 && !p3 && !p4) { return '0'; }
    else if( p1 && !p2 && !p3 && !p4) { return '1'; }
    else if(!p1 &&  p2 && !p3 && !p4) { return '2'; }
    else if( p1 &&  p2 && !p3 && !p4) { return '3'; }
    else if(!p1 && !p2 &&  p3 && !p4) { return '4'; }
    else if( p1 && !p2 &&  p3 && !p4) { return '5'; }
    else if(!p1 &&  p2 &&  p3 && !p4) { return '6'; }
    else if( p1 &&  p2 &&  p3 && !p4) { return '7'; }
    else if(!p1 && !p2 && !p3 &&  p4) { return '8'; }
    else if( p1 && !p2 && !p3 &&  p4) { return '9'; }
    else if(!p1 &&  p2 && !p3 &&  p4) { return 'A'; }
    else if( p1 &&  p2 && !p3 &&  p4) { return 'B'; }
    else if(!p1 && !p2 &&  p3 &&  p4) { return 'C'; }
    else if( p1 && !p2 &&  p3 &&  p4) { return 'D'; }
    else if(!p1 &&  p2 &&  p3 &&  p4) { return 'E'; }
    else if( p1 &&  p2 &&  p3 &&  p4) { return 'F'; }
    else { return 0; } // =^.^= here's a kitty
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line1Click(TObject *Sender)
{
  //1-16
  String c1 = BinToHex(Pin1->Checked,  Pin2->Checked,  Pin3->Checked,  Pin4->Checked);
  String c2 = BinToHex(Pin5->Checked,  Pin6->Checked,  Pin7->Checked,  Pin8->Checked);
  String c3 = BinToHex(Pin9->Checked,  Pin10->Checked, Pin11->Checked, Pin12->Checked);
  String c4 = BinToHex(Pin13->Checked, Pin14->Checked, Pin15->Checked, Pin16->Checked);

  l_Line1->Caption = "[0x" + c4 + c3 + c2 + c1 + "]";
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line2Click(TObject *Sender)
{
  //51-58
  String c1 = BinToHex(Pin51->Checked, Pin52->Checked, Pin53->Checked, Pin54->Checked);
  String c2 = BinToHex(Pin55->Checked, Pin56->Checked, Pin57->Checked, Pin58->Checked);

  l_Line2->Caption = "[0x" + c2 + c1 + "]";

}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line3Click(TObject *Sender)
{
  //21-28
  String c1 = BinToHex(Pin21->Checked, Pin22->Checked, Pin23->Checked, Pin24->Checked);
  String c2 = BinToHex(Pin25->Checked, Pin26->Checked, Pin27->Checked, Pin28->Checked);

  l_Line3->Caption = "[0x" + c2 + c1 + "]";
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line4Click(TObject *Sender)
{
  //31-38
  String c1 = BinToHex(Pin31->Checked, Pin32->Checked, Pin33->Checked, Pin34->Checked);
  String c2 = BinToHex(Pin35->Checked, Pin36->Checked, Pin37->Checked, Pin38->Checked);

  l_Line4->Caption = "[0x" + c2 + c1 + "]";
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line5Click(TObject *Sender)
{
  //41-48
  String c1 = BinToHex(Pin41->Checked, Pin42->Checked, Pin43->Checked, Pin44->Checked);
  String c2 = BinToHex(Pin45->Checked, Pin46->Checked, Pin47->Checked, Pin48->Checked);

  l_Line5->Caption = "[0x" + c2 + c1 + "]";
}
//---------------------------------------------------------------------------


void __fastcall Tf_GraphIO::Pin29Click(TObject *Sender)
{
  if(Pin29->Checked != DebugOutState)
  {
	if(Pin29->Checked)
	{
	  DebugOutState = true;
	  Pin39->Checked = true;
	  f_Memory->dbg_Mem->Color = clRed;
	}
	else
	{
	  DebugOutState = false;
	  //f_Memory->dbg_Mem->Color = clWindow;
	}
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::FormCreate(TObject *Sender)
{
  DebugOutState = false;
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Pin39Click(TObject *Sender)
{
  f_Memory->dbg_Mem->Color = clWindow;
}
//---------------------------------------------------------------------------

void __fastcall Tf_GraphIO::Line6Click(TObject *Sender)
{
  //61-68
  String c1 = BinToHex(Pin61->Checked, Pin62->Checked, Pin63->Checked, Pin64->Checked);
  String c2 = BinToHex(Pin65->Checked, Pin66->Checked, Pin67->Checked, Pin68->Checked);

  l_Line6->Caption = "[0x" + c2 + c1 + "]";
}
//---------------------------------------------------------------------------


