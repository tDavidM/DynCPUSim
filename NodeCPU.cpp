//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <iostream>
#include <fstream>

#include "NodeCPU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tf_CPUNode *f_CPUNode;
//---------------------------------------------------------------------------
//Constructor for a Node
TNode::TNode(int pIntID, int pX, int pY, int pType, char *pName)
{
    this->InternalID = pIntID;
    strncpy(this->Name,pName,sizeof(this->Name));
    this->Name[sizeof(this->Name)-1] = '\0';

    this->X = pX;
    this->Y = pY;
    this->Type = pType;
	 this->DeleteFlag = false;
	 this->TagFlag = false;

    //Each Node has 2 input and 2 output (exept for NOT which only eval Up)
    this->IDInUp    = 0;
    this->IDInDown  = 0;
    this->IDOutUp   = 0;
    this->IDOutDown = 0;

    //Output on eigther a Pin or an other Node
    this->NameOutUp[0]   = '\0';
    this->NameOutDown[0] = '\0';
    this->OutUp   = NULL;
    this->OutDown = NULL;

    //Internal State
    this->Active      = false;
    this->ActiveDelay = 0;

    //State of Input Pins
    this->InActiveUp   = false;
    this->InActiveDown = false;

    //Activity on Inputs
    this->InUpAct    = false;
    this->InDownAct  = false;

    //this->OutUpAct   = false;
    //this->OutDownAct = false;
}
//---------------------------------------------------------------------------
//Set Pin number to Input Up
void TNode::SetInUp(int vID/*, TNode *pID*/)
{
  this->IDInUp = vID;
  //this->InUp = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Input Down
void TNode::SetInDown(int vID/*, TNode *pID*/)
{
  this->IDInDown = vID;
  //this->InDown = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Output Up
void TNode::SetOutUp(int vID, TNode *pID) 
{
  this->IDOutUp = vID;
  this->OutUp = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Output Down
void TNode::SetOutDown(int vID, TNode *pID)
{
  this->IDOutDown = vID;
  this->OutDown = pID;
}
//---------------------------------------------------------------------------
//Get Pin number for Input Up
int TNode::GetID_InUp(void)
{
  return this->IDInUp;
}
//---------------------------------------------------------------------------
//Get Pin number for Input Down
int TNode::GetID_InDown(void)
{
  return this->IDInDown;
}
//---------------------------------------------------------------------------
//Get Pin number for Output Up
int TNode::GetID_OutUp(void)
{
  return this->IDOutUp;
}
//---------------------------------------------------------------------------
//Get Pin number for Output Down
int TNode::GetID_OutDown(void)
{
  return this->IDOutDown;
}
//---------------------------------------------------------------------------
//Get pointer to Output Node Up
TNode * TNode::GetOutUp(void)
{
  return this->OutUp; //gives the Output Up node
}
//---------------------------------------------------------------------------
//Get pointer to Output Node Down
TNode * TNode::GetOutDown(void)
{
  return this->OutDown; //gives the Output Down node
}
//---------------------------------------------------------------------------
//Get Actual Internal State
bool TNode::GetActive(void)
{
  return this->Active || (this->ActiveDelay > 0); //Gives the Node internal state
}
//---------------------------------------------------------------------------
//Get Type of Node
int TNode::GetType(void)
{
  return this->Type;
}
//---------------------------------------------------------------------------
//Set Type of Node
void TNode::SetType(int pType)
{
  this->Type = pType;
}
//---------------------------------------------------------------------------
//Check if connected to a Pin (In or Out) or not
int TNode::GetInOutType(void)
{
  if(this->IDInUp > 0 || this->IDInDown > 0)
  {
    return 1; //Input, Green/Yellow
  }
  else if(this->IDOutUp > 0 || this->IDOutDown > 0)
  {
    return 2; //Output, Blue/Purple
  }
  else
  {
    return 0; //Normal, Black/Red
  } 
}
//---------------------------------------------------------------------------
//Reset Internal State, Inputs States and Activity on Inputs
void TNode::Reset(void)
{
    this->InUpAct      = false;
    this->InActiveUp   = false;
    this->InDownAct    = false;
    this->InActiveDown = false;
    this->Active       = false;
    this->ActiveDelay  = 0;
}
//---------------------------------------------------------------------------
//Trigger Activity on Inputs and Set Input States, DOES NOT change Internal State
void TNode::Receive(bool pAct)
{
  //When a node receives input, it is stacked in Up than Down
  if(!this->DeleteFlag)
  {
      if(!this->InActiveUp)
      {
        this->InUpAct = pAct;
        this->InActiveUp = true;
      }
      else if (!this->InActiveDown)
      {
        this->InDownAct = pAct;
        this->InActiveDown = true;
      }
  }
}
//---------------------------------------------------------------------------
//Notifies Output Nodes of Internal State
void TNode::Send()
{
  TNode* NodeCurr;
  
  //Each node sends internal state to Up and Down Output Node by calling remote Receive methode
  if(!this->DeleteFlag)
  {
      NodeCurr = this->OutUp;
      if(NodeCurr != NULL)
      {
        NodeCurr->Receive(this->Active || (this->ActiveDelay > 0));
      }

      NodeCurr = this->OutDown;
      if(NodeCurr != NULL)
      {
        NodeCurr->Receive(this->Active || (this->ActiveDelay > 0));
      }
  }
}
//---------------------------------------------------------------------------
//Update Internal State according to Inputs States, Reset Inputs Activities
void TNode::Work(void)
{
  //Update internal state
  switch (this->Type)
  {
    case 0: //OR
	{
	  this->Active = this->InUpAct || this->InDownAct;
      break;
	}
	case 1: //AND
	{
	  this->Active = this->InUpAct && this->InDownAct;
      break;
	}
	case 2: //NOR
	{
	  this->Active = !(this->InUpAct || this->InDownAct);
      break;
	}
	case 3: //NAND
	{
      //this->ActiveDelay = this->Active;
	  this->Active = !(this->InUpAct && this->InDownAct);
      //this->ActiveDelay = this->Active ? 3 : this->ActiveDelay - 1;
      break;
	}
	case 4: //XOR
	{
	  this->Active = this->InUpAct != this->InDownAct;
      break;
	}
	case 5: //NOT
	{
	  this->Active = ! this->InUpAct;
      break;
	}
  }

  //Reset the Inputs
  this->InUpAct   = false;
  this->InDownAct = false;

  //reset the receive "stack"
  this->InActiveUp   = false;
  this->InActiveDown = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall Tf_CPUNode::Tf_CPUNode(TComponent* Owner)
    : TForm(Owner)
{
  this->NodeList = new TList;
  this->SelectList = new TList;
  this->NodeSelect = NULL;
  this->NodeType = 0;
  this->NodeCmp = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_InitClick(TObject *Sender)
{
  ifstream FileId;
  bool LineOk;
  TNode* Node;
  TNode* NodeCible;
  int X, Y, Type;
  int LineCmp;
  char Name[50];
  char Buffer[200];
  char *SubBuff;
  int PinInUp, PinInDown, PinOutUp, PinOutDown;
  char NameInUp[50], NameInDown[50], NameOutUp[50], NameOutDown[50];

  this->sb_Main->Panels->Items[0]->Text = "Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink          Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";

  //Flush all nodes...if any
  for(int i = 0; i<NodeCmp; i++)
  {
     Node = (TNode*)this->NodeList->Items[i];
     delete Node;
  }

  this->NodeSelect = NULL;
  this->NodeType = 0;
  this->NodeCmp = 0;

  FileId.open("NodeList.ndl");
  if(FileId.fail() || FileId.bad())
  {
    return;
  }

  LineOk = true;

  while (!FileId.eof())
  {
     FileId.getline(Buffer,200);
     if(LineOk)
     {
       //Chop line by ;
       SubBuff = strtok (Buffer,";");
       if (SubBuff != NULL){strncpy(Name,SubBuff,50); Name[49]='\0'; SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){X          = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){Y          = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){Type       = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){PinInUp    = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){PinInDown  = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){PinOutUp   = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){PinOutDown = StrToInt(SubBuff); SubBuff = strtok (NULL, ";");} else {LineOk = false;}
       if (SubBuff != NULL){strncpy(NameOutUp,SubBuff,50);   NameOutUp[49]='\0';   SubBuff = strtok (NULL, ";");} else {NameOutUp[0] = '\0';}
       if (SubBuff != NULL){strncpy(NameOutDown,SubBuff,50); NameOutDown[49]='\0'; SubBuff = strtok (NULL, ";");}else {NameOutDown[0] = '\0';}

       //Init each Node with all Info from File
       if (LineOk)
       {
           Node = new TNode(NodeCmp, X, Y, Type, Name);
           this->NodeList->Add(Node);
           if (PinInUp != 0)    { Node->SetInUp(PinInUp); }
           if (PinInDown != 0)  { Node->SetInDown(PinInDown); }
           if (PinOutUp != 0)   { Node->SetOutUp(PinOutUp, NULL); }
           if (PinOutDown != 0) { Node->SetOutDown(PinOutDown, NULL); }
           if(strlen(NameOutUp) > 0)  { strncpy(Node->NameOutUp,NameOutUp,50); Node->NameOutUp[49]='\0'; }
           if(strlen(NameOutDown) > 0){ strncpy(Node->NameOutDown,NameOutDown,50); Node->NameOutDown[49]='\0'; }
           NodeCmp++; //0

           NameOutUp[0]   = '\0';
           NameOutDown[0] = '\0';
       }
     }
  }

  FileId.close();

  //Look for each Node with a Output Name in Up or Down and Links it to the coresponding "Downstream" Node
  for(int j = 0; j<NodeCmp; j++)
  {
    Node = (TNode*)this->NodeList->Items[j];
    if(strlen(Node->NameOutUp) > 0)
    {
       for(int i = 0; i<NodeCmp; i++)
       {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if(strncmp(NodeCible->Name, Node->NameOutUp, sizeof(Node->NameOutUp)) == 0)
          {
            Node->SetOutUp(0,NodeCible);
            i = NodeCmp;
          }
       }
    }
    if(strlen(Node->NameOutDown) > 0)
    {
       for(int i = 0; i<NodeCmp; i++)
       {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if(strncmp(NodeCible->Name, Node->NameOutDown, sizeof(Node->NameOutDown)) == 0)
          {
            Node->SetOutDown(0,NodeCible);
            i = NodeCmp;
          }
       }
    }
  }

  //Update internal state for Not gates
  for(int i = 0; i<NodeCmp; i++)
  {
     Node = (TNode*)this->NodeList->Items[i];
     Node->Work();
     Node->Send();
  }

  this->CallDrawArea();
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_SaveClick(TObject *Sender)
{
  ofstream FileId;
  String Buffer;
  TNode* NodeCurr;

  FileId.open("NodeList.ndl");

  if(FileId.fail() || FileId.bad())
  {
    ShowMessage("Error");
    return;
  }
  for (int i = 0; i<NodeCmp; i++)
  {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     if(! NodeCurr->DeleteFlag)
     {
         Buffer = NodeCurr->Name;
         Buffer = Buffer + ';'
                  + IntToStr(NodeCurr->X) + ';' + IntToStr(NodeCurr->Y)
                  + ';' + IntToStr(NodeCurr->GetType())
                  + ';' + IntToStr(NodeCurr->GetID_InUp())  + ';' + IntToStr(NodeCurr->GetID_InDown())
                  + ';' + IntToStr(NodeCurr->GetID_OutUp()) + ';' + IntToStr(NodeCurr->GetID_OutDown())
                  + ';' + NodeCurr->NameOutUp + ';' + NodeCurr->NameOutDown + ';';
         FileId<< Buffer.c_str() << "\n";
     }
  }
  FileId.close();
  this->ItsUpdated = false;
  
  if(FileId.fail())
  {
    ShowMessage("Error");
    return;
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_StartClick(TObject *Sender)
{
  this->t_Work->Interval = this->DrawTimerSpeed;
  this->t_Draw->Interval = this->DrawTimerSpeed;
  this->t_Work->Enabled  = !this->t_Work->Enabled;
  this->t_Draw->Enabled  = this->t_Work->Enabled;
  if (this->t_Work->Enabled)
    this->b_Start->Caption = "Pause";
  else
    this->b_Start->Caption = "Start";
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::t_WorkTimer(TObject *Sender)
{
  TNode* NodeCurr;
  TNode* NodeUp;
  TNode* NodeDown;

  //Read from Input
  this->ReadInput();

  //Communicate internal state
  for(int i = 0; i<NodeCmp; i++)
  {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     if(! NodeCurr->DeleteFlag)
     {
       NodeCurr->Send();
     }
  }

  //Update internal state
  for(int i = 0; i<NodeCmp; i++)
  {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     if(! NodeCurr->DeleteFlag)
     {
       NodeCurr->Work();
     }
  }

  //Write to Output
  this->WriteOutput();
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::t_DrawTimer(TObject *Sender)
{
  if(this->cb_ActiveDraw->Checked) {
     //Draw
     this->CallDrawArea();
  }
}
//---------------------------------------------------------------------------

void Tf_CPUNode::ResetAllNode(void)
{
  TNode* NodeCurr;

  for(int i = 0; i<NodeCmp; i++)
  {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    NodeCurr->Reset();
  }

  //Update internal state for Not gates
  for(int i = 0; i<NodeCmp; i++)
  {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     NodeCurr->Work();
     NodeCurr->Send();
  }

  //Draw
  this->CallDrawArea();
}
//---------------------------------------------------------------------------
void Tf_CPUNode::ReadInput(void)
{
  TNode* NodeCurr;
  TCheckBox * CurrPin;
  int IDUp, IDDown;

  //Scan for Node with Input Pin ID
  for(int i = 0; i<NodeCmp; i++)
  {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    IDUp = NodeCurr->GetID_InUp();
    IDDown = NodeCurr->GetID_InDown();

    if(! NodeCurr->DeleteFlag)
    {
        //Pin connected to Input Up
        if(IDUp > 0)
        {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDUp));
          if (CurrPin != NULL)
          {
            NodeCurr->Receive(CurrPin->Checked);
          }
        }

        //Pin connected to Input Down
        if(IDDown > 0)
        {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDDown));
          if (CurrPin != NULL)
          {
            NodeCurr->Receive(CurrPin->Checked);
          }
        }
    }
  }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::WriteOutput(void)
{
  TNode* NodeCurr;
  TCheckBox * CurrPin;
  int IDUp, IDDown;

  //Scan for Node with Output Pin ID
  for(int i = 0; i<NodeCmp; i++)
  {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    IDUp = NodeCurr->GetID_OutUp();
    IDDown = NodeCurr->GetID_OutDown();

    if(! NodeCurr->DeleteFlag)
    {
        //Pin connected to Output Up
        if(IDUp > 0)
        {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDUp));
          if (CurrPin != NULL)
          {
            CurrPin->Checked = NodeCurr->GetActive();
          }
        }

        //Pin connected to Output Down
        if(IDDown > 0)
        {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDDown));
          if (CurrPin != NULL)
          {
            CurrPin->Checked = NodeCurr->GetActive();
          }
        }
     }
  }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::CallDrawArea(void)
{
  DrawCmpItem = 0;
  DrawCmpLine = 0;
  t_DrawMulti1Timer(this);
  t_DrawMulti2Timer(this);
  t_DrawMulti3Timer(this);
  this->DrawArea(0);
  this->p_DrawCmp->Caption = "Draw: " + IntToStr(DrawCmpItem) + " - " + IntToStr(DrawCmpLine);
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::t_DrawMulti1Timer(TObject *Sender)
{
  this->DrawArea(1);
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::t_DrawMulti2Timer(TObject *Sender)
{
  this->DrawArea(2);
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::t_DrawMulti3Timer(TObject *Sender)
{
  this->DrawArea(3);
}
//---------------------------------------------------------------------------
void Tf_CPUNode::DrawArea(int NbDraw)
{
  TNode* NodeCurr;
  TNode* NodeUp;
  TNode* NodeDown;

  int StartX = OffSetX + this->p_Area->Left;
  int StartY = OffSetY + this->p_Area->Top;
  int MaxX   = this->p_Area->Left + this->p_Area->Width;
  int MaxY   = this->p_Area->Top  + this->p_Area->Height;

  TPoint Triangle[3];

  this->Canvas->Brush->Color = clBtnFace;
  this->Canvas->Pen->Color   = clBlack;
  //this->Canvas->FillRect(ClientRect);

  for(int i = 0; i<NodeCmp; i++)
  {
	 if(i%4 == NbDraw)
	 {
		 //Node, Black Inactive, Red Active
		 NodeCurr = (TNode*)this->NodeList->Items[i];

		 if (NodeCurr->TagFlag)
		   this->Canvas->Brush->Color = clGray;
		 else
		   this->Canvas->Brush->Color = clBlack;
		 this->Canvas->Pen->Color   = clBlack;

		 if(! NodeCurr->DeleteFlag)
		 {
		   if((StartX + (NodeCurr->X * GridSize)) > 0 &&
			  (StartY + (NodeCurr->Y * GridSize)) > 0 &&
			  (StartX + (NodeCurr->X * GridSize)) < MaxX &&
			  (StartY + (NodeCurr->Y * GridSize)) < MaxY )
		   {
			 DrawCmpItem++;
			 if(NodeCurr == NodeSelect)
			 {
				 this->Canvas->Brush->Color = clWhite;
			 }
			 else if(NodeCurr->GetInOutType() == 0 && NodeCurr->GetActive())
			 {
				 if (NodeCurr->TagFlag)
				   this->Canvas->Brush->Color = clLtGray;
				 else
				   this->Canvas->Brush->Color = clRed;
			 }
			 //Input, Green/Yellow
			 else if(NodeCurr->GetInOutType() == 1)
			 {
			   if (NodeCurr->GetActive())
				 this->Canvas->Brush->Color = clYellow;
			   else
				 this->Canvas->Brush->Color = clGreen;
			 }
			 //Output, Blue/Purple
			 else if(NodeCurr->GetInOutType() == 2)
			 {
			   if (NodeCurr->GetActive())
				 this->Canvas->Brush->Color = clPurple;
			   else
				 this->Canvas->Brush->Color = clBlue;
			 }

			 switch(NodeCurr->GetType())
			 {
			   case 0: //OR Circle
			   {
				   this->Canvas->Ellipse(StartX + (NodeCurr->X * GridSize),
										 StartY + (NodeCurr->Y * GridSize),
										 StartX + (NodeCurr->X * GridSize) + ObjSize,
										 StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 1: //AND Square
			   {
				   this->Canvas->Rectangle(StartX + (NodeCurr->X * GridSize),
										   StartY + (NodeCurr->Y * GridSize),
										   StartX + (NodeCurr->X * GridSize) + ObjSize,
										   StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 2: //NOR Circle with a Point
			   {
				   this->Canvas->Ellipse(StartX + (NodeCurr->X * GridSize),
										 StartY + (NodeCurr->Y * GridSize),
										 StartX + (NodeCurr->X * GridSize) + ObjSize,
										 StartY + (NodeCurr->Y * GridSize) + ObjSize);

				   //this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize));
				   Triangle[0] = Point(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize));
				   Triangle[1] = Point(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point(StartX + (NodeCurr->X * GridSize) + ObjSize + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Polygon(Triangle, 2);
				   break;
			   }
			   case 3: //NAND Square with a Point
			   {
				   this->Canvas->Rectangle(StartX + (NodeCurr->X * GridSize),
										   StartY + (NodeCurr->Y * GridSize),
										   StartX + (NodeCurr->X * GridSize) + ObjSize,
										   StartY + (NodeCurr->Y * GridSize) + ObjSize);

				   //this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize));
				   Triangle[0] = Point(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize));
				   Triangle[1] = Point(StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point(StartX + (NodeCurr->X * GridSize) + ObjSize + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Polygon(Triangle, 2);
				   break;
			   }
			   case 4: //XOR Circle with a White +
			   {
				   this->Canvas->Ellipse(StartX + (NodeCurr->X * GridSize),
										 StartY + (NodeCurr->Y * GridSize),
										 StartX + (NodeCurr->X * GridSize) + ObjSize,
										 StartY + (NodeCurr->Y * GridSize) + ObjSize);

				   if(NodeCurr == NodeSelect)
					 this->Canvas->Pen->Color = clBlack;
				   else
					 this->Canvas->Pen->Color = clWhite;
				   this->Canvas->MoveTo( StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) );
				   this->Canvas->LineTo( StartX + (NodeCurr->X * GridSize) + (ObjSize/2), StartY + (NodeCurr->Y * GridSize) + ObjSize );
				   this->Canvas->MoveTo( StartX + (NodeCurr->X * GridSize)              , StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->LineTo( StartX + (NodeCurr->X * GridSize) + ObjSize    , StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Pen->Color = clBlack;
				   break;
			   }
			   case 5: //NOT Triangle
			   {
				   //this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize));
				   Triangle[0] = Point(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize));
				   Triangle[1] = Point(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point(StartX + (NodeCurr->X * GridSize) + ObjSize, StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Polygon(Triangle, 2);
				   break;
			   }
			 }
		   }//if in bounds

		   this->Canvas->Brush->Color = clBlack;
		   if(NodeCurr->GetActive())
		   {
			   if (NodeCurr->TagFlag)
				 this->Canvas->Pen->Color = clYellow;
			   else
				 this->Canvas->Pen->Color = clRed;
		   }
		   else
		   {
			   if (NodeCurr->TagFlag)
				 this->Canvas->Pen->Color = clSilver;
			   else
				 this->Canvas->Pen->Color = clBlack;
		   }

		   //Line Out Up
		   NodeUp = NodeCurr->GetOutUp();
		   if (NodeUp != NULL)
		   {
			   if(!( ((StartX + (NodeCurr->X * GridSize)) < 0    && (StartX + (NodeUp->X * GridSize)) < 0    )||
					 ((StartX + (NodeCurr->X * GridSize)) > MaxX && (StartX + (NodeUp->X * GridSize)) > MaxX )  ) ||
				  !( ((StartY + (NodeCurr->Y * GridSize)) < 0    && (StartY + (NodeUp->Y * GridSize)) < 0    )||
					 ((StartY + (NodeCurr->Y * GridSize)) > MaxY && (StartY + (NodeUp->Y * GridSize)) > MaxY )  )   )
			   {
				 this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize) +  ObjSize,
									  StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				 this->Canvas->LineTo(StartX + (NodeUp->X * GridSize),
									  StartY + (NodeUp->Y * GridSize) + (ObjSize/2) );
				 DrawCmpLine++;
			   }
		   }

		   //Line Out Down
		   NodeDown = NodeCurr->GetOutDown();
		   if (NodeDown != NULL)
		   {
			   if(!( ((StartX + (NodeCurr->X * GridSize)) < 0    && (StartX + (NodeDown->X * GridSize)) < 0    )||
					 ((StartX + (NodeCurr->X * GridSize)) > MaxX && (StartX + (NodeDown->X * GridSize)) > MaxX )  ) ||
				  !( ((StartY + (NodeCurr->Y * GridSize)) < 0    && (StartY + (NodeDown->Y * GridSize)) < 0    )||
					 ((StartY + (NodeCurr->Y * GridSize)) > MaxY && (StartY + (NodeDown->Y * GridSize)) > MaxY )  )   )
			   {
				 this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize) +  ObjSize,
									  StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				 this->Canvas->LineTo(StartX + (NodeDown->X * GridSize),
									  StartY + (NodeDown->Y * GridSize) + (ObjSize/2) );
				 DrawCmpLine++;
			   }
		   }
		 }
	  }//if modulo
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_StepClick(TObject *Sender)
{
  this->t_WorkTimer(Sender);
  this->t_DrawTimer(Sender);
}
//---------------------------------------------------------------------------
void Tf_CPUNode::UpdateNode(void)
{
  //TNode* Node;
  TNode* NodeCible;

  this->ItsUpdated = true;
  TagFollowList(this->NodeSelect, 10, false);

  //Read data from Edit Window and Update the selected Node
  strncpy(NodeSelect->Name, AnsiString(f_GraphEdit->e_Name->Text).c_str(), 50);
  NodeSelect->X = StrToInt(f_GraphEdit->e_PosX->Text);
  NodeSelect->Y = StrToInt(f_GraphEdit->e_PosY->Text);
  NodeSelect->SetType(f_GraphEdit->cb_Type->ItemIndex);
  strncpy(NodeSelect->NameOutUp, AnsiString(f_GraphEdit->e_NameOutUp->Text).c_str(), 50);
  strncpy(NodeSelect->NameOutDown, AnsiString(f_GraphEdit->e_NameOutDown->Text).c_str(), 50);

  NodeSelect->SetInUp(StrToInt(f_GraphEdit->e_PinIDInUp->Text));
  NodeSelect->SetInDown(StrToInt(f_GraphEdit->e_PinIDInDown->Text));

  NodeSelect->DeleteFlag = f_GraphEdit->cb_Delete->Checked;

  if(NodeSelect->DeleteFlag)
  {
    NodeSelect->SetInUp(0);
    NodeSelect->SetInDown(0);
    strncat(NodeSelect->Name, "DELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETE", sizeof(NodeSelect->Name));
  }

  //If Node Name changed or deleted, update Nodes conneted to it "Upstream"
  for(int i = 0; i<NodeCmp; i++)
  {
    NodeCible = (TNode*)this->NodeList->Items[i];
    if(strncmp(AnsiString(f_GraphEdit->l_SaveName->Caption).c_str(), NodeCible->NameOutUp, sizeof(NodeCible->NameOutUp)) == 0)
    {
	   if(NodeSelect->DeleteFlag)
       {
          NodeCible->NameOutUp[0] = '\0';
          NodeCible->SetOutUp(0, NULL);
       }
       else if(f_GraphEdit->l_SaveName->Caption != f_GraphEdit->e_Name->Text)
       {
          strncpy(NodeCible->NameOutUp, AnsiString(f_GraphEdit->e_Name->Text).c_str(), sizeof(NodeCible->NameOutUp));
       }
    }
    if(strncmp(AnsiString(f_GraphEdit->l_SaveName->Caption).c_str(), NodeCible->NameOutDown, sizeof(NodeCible->NameOutDown)) == 0)
    {
       if(NodeSelect->DeleteFlag)
       {
          NodeCible->NameOutDown[0] = '\0';
          NodeCible->SetOutDown(0, NULL);
       }
       else if(f_GraphEdit->l_SaveName->Caption != f_GraphEdit->e_Name->Text)
       {
          strncpy(NodeCible->NameOutDown, AnsiString(f_GraphEdit->e_Name->Text).c_str(), sizeof(NodeCible->NameOutUp));
       }
    }
  }
  //If Output Node Up Changed / Removed
  if (f_GraphEdit->e_NameOutUp->Text != f_GraphEdit->l_NameOutUp->Caption || NodeSelect->DeleteFlag)
  {
    if(strlen(NodeSelect->NameOutUp) > 0)
    {
       int i = 0;
       while(i<NodeCmp)
       {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if(NodeSelect->DeleteFlag || strncmp(NodeCible->Name, NodeSelect->NameOutUp, sizeof(NodeSelect->NameOutUp)) == 0)
          {
            NodeSelect->SetOutUp(0,NodeCible);
            i = NodeCmp;
          }
          //}
          i++;
       }
    }
    else
    {
       NodeSelect->SetOutUp(0,NULL);
    }
  }
  //If Output Node Down Changed / Removed
  if (f_GraphEdit->e_NameOutDown->Text != f_GraphEdit->l_NameOutDown->Caption || NodeSelect->DeleteFlag)
  {
    if(strlen(NodeSelect->NameOutDown) > 0)
    {
       int i = 0;
       while(i<NodeCmp)
       {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if(NodeSelect->DeleteFlag || strncmp(NodeCible->Name, NodeSelect->NameOutDown, sizeof(NodeSelect->NameOutDown)) == 0)
          {
            NodeSelect->SetOutDown(0,NodeCible);
            i = NodeCmp;
          }
          i++;
       }
    }
    else
    {
       NodeSelect->SetOutDown(0,NULL);
    }
  }

  //Update Output if Removed
  if(f_GraphEdit->e_NameOutUp->Text == "")
  {
    NodeSelect->SetOutUp(StrToInt(f_GraphEdit->e_PinIDOutUp->Text), NULL);
  }
  if(f_GraphEdit->e_NameOutDown->Text == "")
  {
    NodeSelect->SetOutDown(StrToInt(f_GraphEdit->e_PinIDOutDown->Text), NULL);
  }
  if(NodeSelect->DeleteFlag)
  {
    NodeSelect->SetOutUp(0,   NULL);
    NodeSelect->SetOutDown(0, NULL);
  }

  if(!NodeSelect->DeleteFlag)
  {
	if(this->cb_ColorLine->Checked)
	  TagFollowList(this->NodeSelect, 10, true);
  }

  //Reset Stored "Previous" names
  f_GraphEdit->l_SaveName->Caption    = NodeSelect->Name;
  f_GraphEdit->l_NameOutUp->Caption   = NodeSelect->NameOutUp;
  f_GraphEdit->l_NameOutDown->Caption = NodeSelect->NameOutDown;

  //Draw
  this->Invalidate();
  this->CallDrawArea();
}
//---------------------------------------------------------------------------
//Set a button font to Bold
void __fastcall Tf_CPUNode::b_OrClick(TObject *Sender)
{
  TButton *SelType = static_cast<TButton*>(Sender);

  this->b_Or->Font->Style   = this->b_Or->Font->Style   >> fsBold;
  this->b_And->Font->Style  = this->b_And->Font->Style  >> fsBold;
  this->b_NOr->Font->Style  = this->b_NOr->Font->Style  >> fsBold;
  this->b_NAnd->Font->Style = this->b_NAnd->Font->Style >> fsBold;
  this->b_XOr->Font->Style  = this->b_XOr->Font->Style  >> fsBold;
  this->b_Not->Font->Style  = this->b_Not->Font->Style  >> fsBold;

  this->NodeType = SelType->Tag;
  SelType->Font->Style = SelType->Font->Style << fsBold;
}
//---------------------------------------------------------------------------

bool Tf_CPUNode::NodeNameExists(char *pName)
{
    TNode* NodeCurr;
    bool Found = false;

    for(int i = 0; i<NodeCmp; i++)
    {
       NodeCurr = (TNode*)this->NodeList->Items[i];
       if(! NodeCurr->DeleteFlag)
       {
          if(strncmp(pName, NodeCurr->Name, sizeof(NodeCurr->Name)) == 0)
          {
             Found = true;
             i = NodeCmp;
          }
       }
    }
    return Found;
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  TNode* NodeCurr;
  int pX, pY, Type;
  String Name;

  int StartX = OffSetX + p_Area->Left;
  int StartY = OffSetY + p_Area->Top;
  bool Found;

  //Left Click = Select
  if(Button == mbLeft && !(Shift.Contains(ssCtrl) || Shift.Contains(ssShift) || Shift.Contains(ssAlt)))
  {
	  this->SelectList->Clear();

      this->MouseDownX = X;
	  this->MouseDownY = Y;
      for(int i = 0; i<NodeCmp; i++)
      {
         NodeCurr = (TNode*)this->NodeList->Items[i];
         if(! NodeCurr->DeleteFlag)
         {
             if(   X >= (StartX + (NodeCurr->X * GridSize))
                && X <  (StartX + (NodeCurr->X * GridSize) + ObjSize)
                && Y >= (StartY + (NodeCurr->Y * GridSize))
                && Y <  (StartY + (NodeCurr->Y * GridSize) + ObjSize) )
			 {
				if(this->cb_ColorLine->Checked)
				   TagFollowList(this->NodeSelect, 10, false);
				this->NodeSelect = NodeCurr;
				if(this->cb_ColorLine->Checked)
				   TagFollowList(this->NodeSelect, 10, true);
                this->CallDrawArea();

                f_GraphEdit->l_InternalID->Caption = IntToStr(NodeCurr->InternalID);
                f_GraphEdit->e_Name->Text = NodeCurr->Name;
                f_GraphEdit->cb_Delete->Checked = NodeCurr->DeleteFlag;
                f_GraphEdit->l_SaveName->Caption = NodeCurr->Name;
                f_GraphEdit->e_PosX->Text = IntToStr(NodeCurr->X);
                f_GraphEdit->e_PosY->Text = IntToStr(NodeCurr->Y);
                f_GraphEdit->cb_Type->ItemIndex = NodeCurr->GetType();

                f_GraphEdit->e_NameOutUp->Text = NodeCurr->NameOutUp;
                f_GraphEdit->e_NameOutDown->Text = NodeCurr->NameOutDown;
                f_GraphEdit->l_NameOutUp->Caption = NodeCurr->NameOutUp;
                f_GraphEdit->l_NameOutDown->Caption = NodeCurr->NameOutDown;

                f_GraphEdit->e_PinIDInUp->Text = IntToStr(NodeCurr->GetID_InUp());
                f_GraphEdit->e_PinIDInDown->Text = IntToStr(NodeCurr->GetID_InDown());
                f_GraphEdit->e_PinIDOutUp->Text = IntToStr(NodeCurr->GetID_OutUp());
                f_GraphEdit->e_PinIDOutDown->Text = IntToStr(NodeCurr->GetID_OutDown());

                f_GraphEdit->Visible = true;
                i = NodeCmp;
             }
         }
      }
  }
  //Right Click = Move Selected
  else if(Button == mbRight && NodeSelect != NULL)
  {
    this->SelectList->Clear();
    this->ItsUpdated = true;

	NodeSelect->X = (X - StartX) / GridSize;
	NodeSelect->Y = (Y - StartY) / GridSize;
	f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
	f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);

    //Draw
    this->Invalidate();
	this->CallDrawArea();
  }
  //Middle Click = Create
  else if(Button == mbMiddle)
  {
    this->SelectList->Clear();
    this->ItsUpdated = true;

    pX = (X - StartX) / GridSize;
    pY = (Y - StartY) / GridSize;

    int NodeNameNumber = NodeCmp;
	Name = "Node" + IntToStr(NodeNameNumber);
    while(NodeNameExists(AnsiString(Name).c_str()))
    {
      NodeNameNumber++;
      Name = "Node" + IntToStr(NodeNameNumber);
    }

    NodeCurr = new TNode(NodeCmp, pX, pY, NodeType, AnsiString(Name).c_str());
    NodeCmp++;

	this->NodeList->Add(NodeCurr);
	TagFollowList(this->NodeSelect, 10, false);
	this->NodeSelect = NodeCurr;

    //Draw
    this->CallDrawArea();
  }
  //Left Click + Shift or Ctlr = Link Selected
  else if(Button == mbLeft && (Shift.Contains(ssCtrl) || Shift.Contains(ssShift)))
  {
      this->MouseDownX = X;
      this->MouseDownY = Y;

      if(NodeSelect != NULL)
      {
          Found = false;

          for(int i = 0; i<NodeCmp; i++)
          {
             NodeCurr = (TNode*)this->NodeList->Items[i];
             if(! NodeCurr->DeleteFlag)
             {
                 if(   X >= (StartX + (NodeCurr->X * GridSize))
                    && X <  (StartX + (NodeCurr->X * GridSize) + ObjSize)
                    && Y >= (StartY + (NodeCurr->Y * GridSize))
                    && Y <  (StartY + (NodeCurr->Y * GridSize) + ObjSize) )
                 {
                    //this->NodeSelect = NodeCurr;
                    if (Shift.Contains(ssShift))
                    {
                      f_GraphEdit->e_NameOutUp->Text = NodeCurr->Name;
                    }
                    else if(Shift.Contains(ssCtrl))
                    {
                      f_GraphEdit->e_NameOutDown->Text = NodeCurr->Name;
                    }
                    f_GraphEdit->Visible = true;
                    Found = true;
                    i = NodeCmp;
                 }
             }
          }
          if(Found)
          {
              this->SelectList->Clear();

              UpdateNode();
              if (Shift.Contains(ssShift))
              {
                f_GraphEdit->l_NameOutUp->Caption = NodeCurr->Name;
              }
              else if(Shift.Contains(ssCtrl))
              {
                f_GraphEdit->l_NameOutDown->Caption = NodeCurr->Name;
              }
              //Draw
              this->CallDrawArea();
          }
      }
  }
  //Left Click + Alt = Link Remove
  else if(Button == mbLeft && Shift.Contains(ssAlt))
  {
      this->SelectList->Clear();

      this->MouseDownX = X;
      this->MouseDownY = Y;
      for(int i = 0; i<NodeCmp; i++)
      {
         NodeCurr = (TNode*)this->NodeList->Items[i];
         if(! NodeCurr->DeleteFlag)
         {
             if(   X >= (StartX + (NodeCurr->X * GridSize))
                && X <  (StartX + (NodeCurr->X * GridSize) + ObjSize)
                && Y >= (StartY + (NodeCurr->Y * GridSize))
                && Y <  (StartY + (NodeCurr->Y * GridSize) + ObjSize) )
			 {
				TagFollowList(this->NodeSelect, 10, false);
				this->NodeSelect = NodeCurr;

                this->NodeSelect->NameOutUp[0] = '\0';
                this->NodeSelect->SetOutUp(0, NULL);
                this->NodeSelect->NameOutDown[0] = '\0';
                this->NodeSelect->SetOutDown(0, NULL);
                //Draw
                this->Invalidate();
                this->CallDrawArea();

                f_GraphEdit->l_InternalID->Caption = IntToStr(NodeCurr->InternalID);
                f_GraphEdit->e_Name->Text = NodeCurr->Name;
                f_GraphEdit->cb_Delete->Checked = NodeCurr->DeleteFlag;
                f_GraphEdit->l_SaveName->Caption = NodeCurr->Name;
                f_GraphEdit->e_PosX->Text = IntToStr(NodeCurr->X);
                f_GraphEdit->e_PosY->Text = IntToStr(NodeCurr->Y);
                f_GraphEdit->cb_Type->ItemIndex = NodeCurr->GetType();

                f_GraphEdit->e_NameOutUp->Text = NodeCurr->NameOutUp;
                f_GraphEdit->e_NameOutDown->Text = NodeCurr->NameOutDown;
                f_GraphEdit->l_NameOutUp->Caption = NodeCurr->NameOutUp;
                f_GraphEdit->l_NameOutDown->Caption = NodeCurr->NameOutDown;

                f_GraphEdit->e_PinIDInUp->Text = IntToStr(NodeCurr->GetID_InUp());
                f_GraphEdit->e_PinIDInDown->Text = IntToStr(NodeCurr->GetID_InDown());
                f_GraphEdit->e_PinIDOutUp->Text = IntToStr(NodeCurr->GetID_OutUp());
                f_GraphEdit->e_PinIDOutDown->Text = IntToStr(NodeCurr->GetID_OutDown());

                f_GraphEdit->Visible = true;
                i = NodeCmp;
             }
         }
      }
  }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::TagFollowList(TNode *NodeTag, int Depth, bool Sel)
{
  if(Depth > 0 && NodeTag != NULL)
  {
	NodeTag->TagFlag = Sel;
	TagFollowList(NodeTag->GetOutUp(), Depth-1, Sel);
	TagFollowList(NodeTag->GetOutDown(), Depth-1, Sel);
  }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::EmptyFollowList(void)
{
   TagFollowList(this->NodeSelect, 10, false);
}

//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::tb_SizeChange(TObject *Sender)
{
  double PreviousGridSize = GridSize;
  double CurrentGridSize;
  double ZoomFactor;
  double dX, dY, pX, pY;
  double cW, cH;

  cW = this->ClientWidth;
  cH = this->ClientHeight;
  pX = cW / 2.0;
  pY = cH / 2.0;

  dX = this->OffSetX;
  dY = this->OffSetY;

  //Update zoom by steps
  switch (tb_Size->Position) //1.35 factor
  {                   
    case 9: {this->ObjSize = 2;  this->GridSize = 3;  break;}
    case 8: {this->ObjSize = 3;  this->GridSize = 4;  break;}
    case 7: {this->ObjSize = 4;  this->GridSize = 5;  break;}
    case 6: {this->ObjSize = 5;  this->GridSize = 7;  break;}
    case 5: {this->ObjSize = 7;  this->GridSize = 10;  break;}
    case 4: {this->ObjSize = 9;  this->GridSize = 13;  break;}
    case 3: {this->ObjSize = 12;  this->GridSize = 18;  break;}
    case 2: {this->ObjSize = 16;  this->GridSize = 25;  break;}
    case 1: {this->ObjSize = 22;  this->GridSize = 33;  break;}
    case 0: {this->ObjSize = 30;  this->GridSize = 45;  break;}
  }

  CurrentGridSize = GridSize;
  ZoomFactor = (CurrentGridSize / PreviousGridSize);

  this->OffSetX = ( dX * ZoomFactor) - ( (pX * ZoomFactor) - pX);
  this->OffSetY = ( dY * ZoomFactor) - ( (pY * ZoomFactor) - pY);

  //Draw
  this->Invalidate();
  this->CallDrawArea();
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
  //Reset last mouse position
  this->MouseDownX = MousePos.x;
  this->MouseDownY = MousePos.y;

  //Mouse Wheel update Zoom
  if( WheelDelta > 0)
  {
    this->tb_Size->Position--;
  }
  else
  {
    this->tb_Size->Position++;
  }

  Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::AppMessage(TMsg& PassedMsg, bool& Handled)
{
  if(PassedMsg.message == WM_KEYDOWN )
  {
	  // add support for SelectList ??? :p
	  
	  if(Screen->ActiveForm == f_CPUNode)
	  {
		  //Catch arrows for mouvment
		  switch (PassedMsg.wParam)
		  {
			case VK_UP:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL)
			  {
				NodeSelect->Y--;
				f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);
			  }
			  else
				this->OffSetY += (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea();
			  break;
			}
			case VK_DOWN:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL)
			  {
				NodeSelect->Y++;
				f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);
			  }
			  else
				this->OffSetY -= (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea();
			  break;
			}
			case VK_LEFT:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL)
			  {
				NodeSelect->X--;
				f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
			  }
			  else
				this->OffSetX += (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea();
			  break;
			}
			case VK_RIGHT:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL)
			  {
				NodeSelect->X++;
				f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
			  }
			  else
				this->OffSetX -= (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea();
			  break;
			}
			case VK_SPACE:
			{
			  this->OffSetX = 0;
			  this->OffSetY = 0;
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea();
			  break;
			}
		  }
	  }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Key == VK_DELETE && NodeSelect != NULL)
  {
    if (Application->MessageBox( L"Delete Node ?", L"Delete Node", MB_YESNO) == mrYes)
    {
	  f_GraphEdit->cb_Delete->Checked = true;
	  this->UpdateNode();
    }
  }
  else if(Key == VK_KEY_1 || Key == VK_NUMPAD1)
    b_Or->Click();
  else if(Key == VK_KEY_2 || Key == VK_NUMPAD2)
    b_And->Click();
  else if(Key == VK_KEY_3 || Key == VK_NUMPAD3)
    b_NOr->Click();
  else if(Key == VK_KEY_4 || Key == VK_NUMPAD4)
    b_NAnd->Click();
  else if(Key == VK_KEY_5 || Key == VK_NUMPAD5)
    b_XOr->Click();
  else if(Key == VK_KEY_6 || Key == VK_NUMPAD6)
	b_Not->Click();
  else if (this->cb_QuickEdit->Checked)
  {
	if(Key == 'O' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 0;
	else if(Key == 'A' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 1;
	else if(Key == 'R' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 2;
	else if(Key == 'D' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 3;
	else if(Key == 'X' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 4;
	else if(Key == 'N' && NodeSelect != NULL)
	  f_GraphEdit->cb_Type->ItemIndex = 5;

	UpdateNode();
  }
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::FormCreate(TObject *Sender)
{
  Application->OnMessage = AppMessage;
  this->sb_Main->Parent = this;
  this->sb_Main->Panels->Items[0]->Text = "Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink          Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";
  //Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2)

  this->ItsUpdated = false;

  this->DrawTimerSpeed = 150;
  this->OffSetX = 0;
  this->OffSetY = 0;
  this->ObjSize = 12;
  this->GridSize = 18;
  this->tb_Size->Position = 3;
  this->tb_Speed->Position = 15;
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  TNode* NodeCurr;
  String Name;
  int Type;

  int StartX = this->OffSetX + this->p_Area->Left;
  int StartY = this->OffSetY + this->p_Area->Top;
  int UpdateOffSetX;
  int UpdateOffSetY;

  //Catch cursor mouvment when "drag & drop" of the Canvas
  if(Shift.Contains(ssLeft) && !(Shift.Contains(ssCtrl) || Shift.Contains(ssShift))
     && (X <= this->MouseDownX-GridSize || X >= this->MouseDownX+GridSize || Y <= this->MouseDownY-GridSize || Y >= this->MouseDownY+GridSize) )
  {
      this->OffSetX += X - this->MouseDownX;
      this->OffSetY += Y - this->MouseDownY;
      this->MouseDownX = X;
      this->MouseDownY = Y;
      //Draw
      //this->Invalidate();
      this->Canvas->Brush->Color = clBtnFace;
      this->Canvas->Pen->Color = clBlack;
      this->Canvas->FillRect(ClientRect);
      this->CallDrawArea();

      this->sb_Main->Panels->Items[0]->Text = "Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";
  }
  else if(Shift.Contains(ssLeft) && Shift.Contains(ssShift) && !Shift.Contains(ssCtrl))
  {
	  this->SelectList->Clear();
      for(int i = 0; i<NodeCmp; i++)
      {
          NodeCurr = (TNode*)this->NodeList->Items[i];
          if(! NodeCurr->DeleteFlag)
          {
             if(  (  (this->MouseDownX < X && StartX+(NodeCurr->X*GridSize) >= this->MouseDownX && StartX+(NodeCurr->X*GridSize) <= X)
                   ||(this->MouseDownX > X && StartX+(NodeCurr->X*GridSize) <= this->MouseDownX && StartX+(NodeCurr->X*GridSize) >= X) )
                &&(  (this->MouseDownY < Y && StartY+(NodeCurr->Y*GridSize) >= this->MouseDownY && StartY+(NodeCurr->Y*GridSize) <= Y)
                   ||(this->MouseDownY > Y && StartY+(NodeCurr->Y*GridSize) <= this->MouseDownY && StartY+(NodeCurr->Y*GridSize) >= Y) ) )
             {
				this->SelectList->Add(NodeCurr);
             }
          }
      }
      //Draw
      //this->Invalidate();
      this->Canvas->Brush->Color = clBtnFace;
      this->Canvas->Pen->Color = clGreen;
      this->Canvas->FillRect(ClientRect);
      this->Canvas->Rectangle(this->MouseDownX, this->MouseDownY, X, Y);
      this->CallDrawArea();
  }
  else if(Shift.Contains(ssLeft) && !Shift.Contains(ssShift) && Shift.Contains(ssCtrl)
          && (X <= this->MouseDownX-GridSize || X >= this->MouseDownX+GridSize || Y <= this->MouseDownY-GridSize || Y >= this->MouseDownY+GridSize))
  {
      UpdateOffSetX = (X - this->MouseDownX) / GridSize ;
      UpdateOffSetY = (Y - this->MouseDownY) / GridSize ;
      this->MouseDownX = X;
      this->MouseDownY = Y;
      
      for(int i = 0; i<this->SelectList->Count; i++)
      {
          NodeCurr = (TNode*)this->SelectList->Items[i];
		  NodeCurr->X += UpdateOffSetX;
          NodeCurr->Y += UpdateOffSetY;
          this->ItsUpdated = true;
      }
      //Draw
      //this->Invalidate();
      this->Canvas->Brush->Color = clBtnFace;
      this->Canvas->Pen->Color = clBlack;
      this->Canvas->FillRect(ClientRect);
      this->CallDrawArea();
  }
  //Update status bar Info for Node Name/Type
  else
  {
      for(int i = 0; i<NodeCmp; i++)
      {
         NodeCurr = (TNode*)this->NodeList->Items[i];
         if(! NodeCurr->DeleteFlag)
         {
             if(   X >= (StartX + (NodeCurr->X * GridSize))
                && X <  (StartX + (NodeCurr->X * GridSize) + ObjSize)
                && Y >= (StartY + (NodeCurr->Y * GridSize))
                && Y <  (StartY + (NodeCurr->Y * GridSize) + ObjSize) )
             {
                //Type = NodeCurr->GetType();
                Name = NodeCurr->Name;
                Type = NodeCurr->GetType();

                this->sb_Main->Panels->Items[0]->Text = Name + " [" + f_GraphEdit->cb_Type->Items->Strings[Type] + "]";

                i = NodeCmp;
             }
         }
      }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormPaint(TObject *Sender)
{
   this->CallDrawArea();
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(this->ItsUpdated && Application->MessageBox( L"Save changes before Quit?", L"Save changes", MB_YESNO) == mrYes)
  {
      this->b_Save->Click();
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::b_ResetClick(TObject *Sender)
{
  TCheckBox * CurrPin;

  f_GraphIO->DebugOutState = false;
  f_Memory->dbg_Mem->Color = clWindow;

  f_Memory->cds_Mem->First();
  this->ResetAllNode();
  this->sb_Main->SimpleText =	"Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink          Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";

  for(int i=0; i<=80; i++)
  {
     CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(i));
     if (CurrPin != NULL)
     {
        CurrPin->Checked = false;
     }
  }

  f_GraphIO->Pin70->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::cb_ColorLineClick(TObject *Sender)
{
  if(!this->cb_ColorLine->Checked)
    this->EmptyFollowList();
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::tb_SpeedChange(TObject *Sender)
{
  switch (tb_Speed->Position) {
    case 1:  { this->DrawTimerSpeed = 1;     break;}
    case 2:  { this->DrawTimerSpeed = 2;     break;}
    case 3:  { this->DrawTimerSpeed = 3;     break;}
    case 4:  { this->DrawTimerSpeed = 5;     break;}
    case 5:  { this->DrawTimerSpeed = 7;     break;}
    case 6:  { this->DrawTimerSpeed = 10;    break;}
    case 7:  { this->DrawTimerSpeed = 15;    break;}
    case 8:  { this->DrawTimerSpeed = 20;    break;}
    case 9:  { this->DrawTimerSpeed = 25;    break;}
    case 10: { this->DrawTimerSpeed = 30;    break;}
    case 11: { this->DrawTimerSpeed = 40;    break;}
    case 12: { this->DrawTimerSpeed = 50;    break;}
    case 13: { this->DrawTimerSpeed = 75;    break;}
    case 14: { this->DrawTimerSpeed = 100;   break;}
    case 15: { this->DrawTimerSpeed = 150;   break;} //Default
    case 16: { this->DrawTimerSpeed = 200;   break;}
    case 17: { this->DrawTimerSpeed = 300;   break;}
    case 18: { this->DrawTimerSpeed = 500;   break;}
    case 19: { this->DrawTimerSpeed = 700;   break;}
    case 20: { this->DrawTimerSpeed = 1000;  break;}
    case 21: { this->DrawTimerSpeed = 1500;  break;}
    case 22: { this->DrawTimerSpeed = 2000;  break;}
    case 23: { this->DrawTimerSpeed = 2500;  break;}
    case 24: { this->DrawTimerSpeed = 3000;  break;}
    case 25: { this->DrawTimerSpeed = 4000;  break;}
    case 26: { this->DrawTimerSpeed = 5000;  break;}
    case 27: { this->DrawTimerSpeed = 7500;  break;}
    case 28: { this->DrawTimerSpeed = 10000; break;}
  }

  this->t_Work->Interval = this->DrawTimerSpeed;
  this->t_Draw->Interval = this->DrawTimerSpeed;
}
//---------------------------------------------------------------------------

