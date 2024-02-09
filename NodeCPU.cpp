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
TNode::TNode(int pIntID, int pX, int pY, int pType, String pName)
{
    this->InternalID = pIntID;
    this->Name = pName;

    this->X = pX;
    this->Y = pY;
    this->Type = pType;
	 this->DeleteFlag = false;
	 this->TagFlag = false;

    //Each Node has 2 input and 2 output (exept for NOT which only eval Up)
    this->PinInUp    = 0;
    this->PinInDown  = 0;
    this->PinOutUp   = 0;
    this->PinOutDown = 0;

    //Output on eigther a Pin or an other Node
    this->NameOutUp     = "";
    this->NameOutDown   = "";
    this->NodeOutUp     = NULL;
    this->NodeOutDown   = NULL;
    this->IDNodeOutUp   = -1;
    this->IDNodeOutDown = -1;

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
void TNode::SetInUp(int pPin/*, TNode *pID*/)
{
  this->PinInUp = pPin;
  //this->InUp = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Input Down
void TNode::SetInDown(int pPin/*, TNode *pID*/)
{
  this->PinInDown = pPin;
  //this->InDown = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Output Up
void TNode::SetOutUp(int pPin, TNode *pID)
{
  this->PinOutUp = pPin;
  this->NodeOutUp = pID;
}
//---------------------------------------------------------------------------
//Set Pin number to Output Down
void TNode::SetOutDown(int pPin, TNode *pID)
{
  this->PinOutDown = pPin;
  this->NodeOutDown = pID;
}
//---------------------------------------------------------------------------
//Get Pin number for Input Up
int TNode::GetPin_InUp(void)
{
  return this->PinInUp;
}
//---------------------------------------------------------------------------
//Get Pin number for Input Down
int TNode::GetPin_InDown(void)
{
  return this->PinInDown;
}
//---------------------------------------------------------------------------
//Get Pin number for Output Up
int TNode::GetPin_OutUp(void)
{
  return this->PinOutUp;
}
//---------------------------------------------------------------------------
//Get Pin number for Output Down
int TNode::GetPin_OutDown(void)
{
  return this->PinOutDown;
}
//---------------------------------------------------------------------------
//Get pointer to Output Node Up
TNode * TNode::GetNodeOutUp(void)
{
  return this->NodeOutUp; //gives the Output Up node
}
//---------------------------------------------------------------------------
//Get pointer to Output Node Down
TNode * TNode::GetNodeOutDown(void)
{
  return this->NodeOutDown; //gives the Output Down node
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
  if(this->PinInUp > 0 || this->PinInDown > 0)
    return 1; //Input, Green/Yellow
  else if(this->PinOutUp > 0 || this->PinOutDown > 0)
    return 2; //Output, Blue/Purple
  else
    return 0; //Normal, Black/Red
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
  if (!this->DeleteFlag) {
      if (!this->InActiveUp) {
        this->InUpAct = pAct;
        this->InActiveUp = true;
      } else if (!this->InActiveDown) {
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
  if (!this->DeleteFlag) {
      NodeCurr = this->NodeOutUp;
      if (NodeCurr != NULL)
        NodeCurr->Receive(this->Active || (this->ActiveDelay > 0));

      NodeCurr = this->NodeOutDown;
      if (NodeCurr != NULL)
        NodeCurr->Receive(this->Active || (this->ActiveDelay > 0));
  }
}
//---------------------------------------------------------------------------
//Update Internal State according to Inputs States, Reset Inputs Activities
void TNode::Work(void)
{
  //Update internal state
  switch (this->Type) {
    case 0: { //OR
	  this->Active = this->InUpAct || this->InDownAct;
      break;
	}
	case 1: { //AND
	  this->Active = this->InUpAct && this->InDownAct;
      break;
	}
	case 2: { //NOR
	  this->Active = !(this->InUpAct || this->InDownAct);
      break;
	}
	case 3: { //NAND
      //this->ActiveDelay = this->Active;
	  this->Active = !(this->InUpAct && this->InDownAct);
      //this->ActiveDelay = this->Active ? 3 : this->ActiveDelay - 1;
      break;
	}
	case 4: { //XOR
	  this->Active = this->InUpAct != this->InDownAct;
      break;
	}
	case 5: { //NOT
	  this->Active = ! this->InUpAct;
      break;
	}
	case 6: { //Link
	  this->Active = this->InUpAct || this->InDownAct;
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
  this->MainCanvas = new TBitmap;
  this->NodeList = new TList;
  this->SelectList = new TList;
  this->AnnotationList = new TList;
  this->NodeSelect = NULL;
  this->NodeType = 0;
  this->NodeCmp = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_InitClick(TObject *Sender)
{
  TNode* Node;
  TNode* NodeCible;
  int X, Y, Type;
  int ListNodeCount, LinkCount, NodeTypeCount;
  String Name, FileType;

  int ID, IDOutUp, IDOutDown;
  int PinInUp, PinInDown, PinOutUp, PinOutDown;
  String NameInUp, NameInDown, NameOutUp, NameOutDown;

  this->sb_Main->Panels->Items[0]->Text = "Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink          Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";

   if (this->NodeOpenDialog->Execute()) {

     //Flush all nodes...if any
     for (int i = 0; i<this->NodeCmp; i++) {
        Node = (TNode*)this->NodeList->Items[i];
        delete Node;
     }

     this->NodeList->Clear();

     this->NodeSelect = NULL;
     this->NodeType = 0;
     this->NodeCmp = 0;
     this->NodeMaxID = 0;
     this->pgLoading->Position = 0;

      try {
         this->XMLDoc->FileName = this->NodeOpenDialog->FileName;
         this->XMLDoc->Active = true;
         _di_IXMLNode XmlRoot = XMLDoc->DocumentElement;
         //_di_IXMLNode Param = XmlRoot->ChildNodes->Nodes[0];
         FileType = XmlRoot->GetAttribute("Type");
         if (FileType == "Dyn CPU Sim") {

            _di_IXMLNode InstructionSet = XmlRoot->ChildNodes->Nodes[0];
            f_Memory->LoadInstructionSet(InstructionSet);
            this->InstructionSetXML = InstructionSet;

            _di_IXMLNode Annotation = XmlRoot->ChildNodes->Nodes[1];
            this->LoadAnnotation(Annotation);
            this->AnnotationXML = Annotation;

            _di_IXMLNode Param = XmlRoot->ChildNodes->Nodes[2];
            LinkCount = Param->GetAttribute("LinkCount");

            /*_di_IXMLNode OrType = Param->ChildNodes->Nodes[0];
              NodeTypeCount = OrType->GetAttribute("Count");

              _di_IXMLNode AndType = Param->ChildNodes->Nodes[1];
              NodeTypeCount = AndType->GetAttribute("Count");

              _di_IXMLNode NorType = Param->ChildNodes->Nodes[2];
              NodeTypeCount = NorType->GetAttribute("Count");

              _di_IXMLNode NandType = Param->ChildNodes->Nodes[3];
              NodeTypeCount = NandType->GetAttribute("Count");

              _di_IXMLNode XorType = Param->ChildNodes->Nodes[4];
              NodeTypeCount = XorType->GetAttribute("Count");

              _di_IXMLNode NotType = Param->ChildNodes->Nodes[5];
              NodeTypeCount = NotType->GetAttribute("Count");*/

            _di_IXMLNode NodeState = XmlRoot->ChildNodes->Nodes[3];
            ListNodeCount = StrToInt(NodeState->GetAttribute("NodeCount"));
            this->pgLoading->Max = ListNodeCount*2;

            _di_IXMLNodeList AllNode = NodeState->ChildNodes;
            if (ListNodeCount != AllNode->Count)
               ShowMessage("Error NodeCount");

            for(int i = 0; i < AllNode->Count; i++) {
               ID   = AllNode->Get(i)->GetAttribute("ID");
               Name = AllNode->Get(i)->GetAttribute("Name");

               _di_IXMLNode NodeType   = AllNode->Get(i)->ChildNodes->Nodes[0];
               _di_IXMLNode NodePos    = AllNode->Get(i)->ChildNodes->Nodes[1];
               _di_IXMLNode NodeOut    = AllNode->Get(i)->ChildNodes->Nodes[2];
               _di_IXMLNode NodePinIn  = AllNode->Get(i)->ChildNodes->Nodes[3];
               _di_IXMLNode NodePinOut = AllNode->Get(i)->ChildNodes->Nodes[4];

               Type = NodeType->GetAttribute("Code");
               //TypeName = NodeType->GetAttribute("Name");
               X = NodePos->GetAttribute("X");
               Y = NodePos->GetAttribute("Y");
               IDOutUp     = NodeOut->GetAttribute("IDUp");
               IDOutDown   = NodeOut->GetAttribute("IDDown");
               NameOutUp   = NodeOut->GetAttribute("NameUp");
               NameOutDown = NodeOut->GetAttribute("NameDown");
               //NodeOut->Text;
               PinInUp   = NodePinIn->GetAttribute("NbUp");
               PinInDown = NodePinIn->GetAttribute("NbDown");
               //NodePinIn->Text;
               PinOutUp   = NodePinOut->GetAttribute("NbUp");
               PinOutDown = NodePinOut->GetAttribute("NbDown");
               //NodePinOut->Text;

               if (this->NodeMaxID < ID)
                  this->NodeMaxID = ID;

               Node = new TNode(ID, X, Y, Type, Name);
               this->NodeList->Add(Node);

               if (PinInUp    != 0)
                  Node->SetInUp(PinInUp);
               if (PinInDown  != 0)
                  Node->SetInDown(PinInDown);
               if (PinOutUp   != 0)
                  Node->SetOutUp(PinOutUp, NULL);
               if (PinOutDown != 0)
                  Node->SetOutDown(PinOutDown, NULL);

               if (IDOutUp != -1) {
                 Node->IDNodeOutUp = IDOutUp;
                 //NodeCible = (TNode*)this->NodeList->Items[IDOutUp];
                 //Node->SetOutUp(0,NodeCible);
               }

               if (IDOutDown != -1) {
                 Node->IDNodeOutDown = IDOutDown;
                 //NodeCible = (TNode*)this->NodeList->Items[IDOutDown];
                 //Node->SetOutDown(0,NodeCible);
               }

               if(NameOutUp   != "")
                  Node->NameOutUp   = NameOutUp;
               if(NameOutDown != "")
                  Node->NameOutDown = NameOutDown;
               this->NodeCmp++;

               NameOutUp = "";
               NameOutDown = "";
               this->pgLoading->Position++;
            }
         } else
           ShowMessage("Error Invalid File");
         this->XMLDoc->Active = false;

         Node = NULL;
         //Look for each Node with a Output ID in Up or Down and Links it to the coresponding "Downstream" Node
         for (int i = 0; i<this->NodeCmp; i++) {
            Node = (TNode*)this->NodeList->Items[i];
            if (Node->IDNodeOutUp != -1) {
               for(int j = 0; j<NodeCmp; j++) {
                  NodeCible = (TNode*)this->NodeList->Items[j];
                  if (Node->IDNodeOutUp == NodeCible->InternalID) {

                     if (NodeCible->Name == Node->NameOutUp) {
                        Node->SetOutUp(0,NodeCible);
                     } else
                        ShowMessage("NodeID:"+IntToStr(Node->InternalID)+"("+Node->Name+") Error[Up]["+NodeCible->Name+"]:"+
                                      IntToStr(Node->IDNodeOutUp)+"("+NodeCible->Name+")"); //throw;
                  }
               }
            }
            if (Node->IDNodeOutDown != -1) {
               for(int j = 0; j<NodeCmp; j++) {
                  NodeCible = (TNode*)this->NodeList->Items[j];
                  if (Node->IDNodeOutDown == NodeCible->InternalID) {

                     if (NodeCible->Name == Node->NameOutDown) {
                        Node->SetOutDown(0,NodeCible);
                     } else
                        ShowMessage("NodeID:"+IntToStr(Node->InternalID)+"("+Node->Name+") Error[Up]["+NodeCible->Name+"]:"+
                                      IntToStr(Node->IDNodeOutUp)+"("+NodeCible->Name+")"); //throw;
                  }
               }
            }
            this->pgLoading->Position++;
         }
     }
	  catch (Exception &E) {
		  Application->MessageBox( L"Invalid File", L"Loading Error", MB_OK | MB_ICONINFORMATION);
     }

     //Update internal state for Not gates
     for (int i = 0; i<NodeCmp; i++) {
        Node = (TNode*)this->NodeList->Items[i];
        Node->Work();
     }
     //Update internal state for Not gates, must be done in 2 loops
     for (int i = 0; i<NodeCmp; i++) {
        Node = (TNode*)this->NodeList->Items[i];
        Node->Send();
     }
   }

   this->pgLoading->Position = 0;
   this->CallDrawArea(1);
}

//---------------------------------------------------------------------------
/*
<?xml version="1.0"?>
<FileType Type="Dyn CPU Sim">
  <Param LinkCount="12000">
    <OR count="1200"></OR>
    <AND count="1000"></AND>
    <NOR count="1000"></NOR>
    <NAND count="1000"></NAND>
    <XOR count="1000"></XOR>
    <NOT count="1000"></NOT>
  </Param>
  <NodeState NodeCount="6209">
    <Node ID="124" Name="ClockPin">
      <Type Code="1" Name="OR"></Type>
      <Position X="250" Y="250"></Position>
      <Output IDUp="125" IDDown="128" NameUp="ClockPin2" NameDown="ClockPin3">True</Output>
      <PinIn NbUp="1" NbDown="0">True</PinIn>
      <PinOut NbUp="0" NbDown="0">False</PinOut>
    </Node>
<!--[...]-->
  </NodeState>
</FileType>
*/

//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::b_SaveClick(TObject *Sender)
{
   TNode* NodeCurr;
   int CountOr=0, CountAnd=0, CountNor=0, CountNand=0, CountXor=0, CountNot=0;
   int CountLink = 0, CountNode = 0;

   //this->NodeSaveDialog->Title = this->CPUName;
   this->NodeSaveDialog->FileName = this->NodeOpenDialog->FileName; //"NodeList_XML.Ndl";
   this->pgLoading->Position = 0;

   if (this->NodeCmp > 0 && this->NodeSaveDialog->Execute() == true)
   {
     _di_IXMLDocument XmlRoot = NewXMLDocument();
     XmlRoot->Options = TXMLDocOptions() << doNodeAutoIndent;

	  _di_IXMLNode FileType = XmlRoot->CreateElement("FileType", "");
     XmlRoot->ChildNodes->Add(FileType);
	  FileType->SetAttribute("Type", (String)"Dyn CPU Sim");

     FileType->ChildNodes->Add(this->InstructionSetXML);

     FileType->ChildNodes->Add(this->AnnotationXML);

     for (int i = 0; i<this->NodeCmp; i++)
     {
        NodeCurr = (TNode*)this->NodeList->Items[i];
        if(! NodeCurr->DeleteFlag)
        {
           CountNode++;
           if(NodeCurr->NameOutUp != "")
             CountLink++;
           if(NodeCurr->NameOutDown != "")
             CountLink++;

			  switch(NodeCurr->GetType())
			  { case 0:{CountOr++;   break; }
			    case 1:{CountAnd++;  break; }
             case 2:{CountNor++;  break; }
             case 3:{CountNand++; break; }
             case 4:{CountXor++;  break; }
             case 5:{CountNot++;  break; }
           }

        }
     }

        _di_IXMLNode Param = XmlRoot->CreateElement("Param", "");
        FileType->ChildNodes->Add(Param);
		  Param->SetAttribute("LinkCount", (int) CountLink );

           _di_IXMLNode OrType = XmlRoot->CreateElement("OR", "");
           Param->ChildNodes->Add(OrType);
           OrType->SetAttribute("Count", (int) CountOr );
           //OrType->Text = "";
           _di_IXMLNode AndType = XmlRoot->CreateElement("AND", "");
           Param->ChildNodes->Add(AndType);
           AndType->SetAttribute("Count", (int) CountAnd );
           //AndType->Text = "";
           _di_IXMLNode NorType = XmlRoot->CreateElement("NOR", "");
           Param->ChildNodes->Add(NorType);
           NorType->SetAttribute("Count", (int) CountNor );
           //Nor->Text = "";
           _di_IXMLNode NandType = XmlRoot->CreateElement("NAND", "");
           Param->ChildNodes->Add(NandType);
           NandType->SetAttribute("Count", (int) CountNand );
           //NandType->Text = "";
           _di_IXMLNode XorType = XmlRoot->CreateElement("XOR", "");
           Param->ChildNodes->Add(XorType);
           XorType->SetAttribute("Count", (int) CountXor );
           //XorType->Text = "";
           _di_IXMLNode NotType = XmlRoot->CreateElement("NOT", "");
           Param->ChildNodes->Add(NotType);
           NotType->SetAttribute("Count", (int) CountNot );
           //NotType->Text = "";

        _di_IXMLNode NodeState = XmlRoot->CreateElement("NodeState", "");
        FileType->ChildNodes->Add(NodeState);
        NodeState->SetAttribute("NodeCount", (int) CountNode);

        _di_IXMLNode Node;
        _di_IXMLNode Type;
        _di_IXMLNode Position;
        _di_IXMLNode Output;
        _di_IXMLNode PinIn;
        _di_IXMLNode PinOut;

     this->pgLoading->Max = this->NodeCmp;
     for (int i = 0; i<this->NodeCmp; i++)
     {
        NodeCurr = (TNode*)this->NodeList->Items[i];
        if(! NodeCurr->DeleteFlag)
        {
           _di_IXMLNode Node = XmlRoot->CreateElement("Node", "");
           NodeState->ChildNodes->Add(Node);
           Node->SetAttribute("ID",  (int) NodeCurr->InternalID);
           Node->SetAttribute("Name",(String) NodeCurr->Name);

              _di_IXMLNode Type = XmlRoot->CreateElement("Type", "");
              Node->ChildNodes->Add(Type);
              Type->SetAttribute("Code",(int) NodeCurr->GetType());
              Type->SetAttribute("Name",(String) NodeCurr->GetType()==0?"OR":
                                                    NodeCurr->GetType()==1?"AND":
                                                       NodeCurr->GetType()==2?"NOR":
                                                          NodeCurr->GetType()==3?"NAND":
                                                             NodeCurr->GetType()==4?"XOR":
                                                                NodeCurr->GetType()==5?"NOT":"LNK");

              _di_IXMLNode Position = XmlRoot->CreateElement("Position", "");
              Node->ChildNodes->Add(Position);
              Position->SetAttribute("X",(int) NodeCurr->X);
              Position->SetAttribute("Y",(int) NodeCurr->Y);

              _di_IXMLNode Output = XmlRoot->CreateElement("Output", "");
              Node->ChildNodes->Add(Output);
              Output->SetAttribute("IDUp",   NodeCurr->NameOutUp!=""   ? NodeCurr->GetNodeOutUp()->InternalID   :-1);
              Output->SetAttribute("IDDown", NodeCurr->NameOutDown!="" ? NodeCurr->GetNodeOutDown()->InternalID :-1);
              Output->SetAttribute("NameUp",  (String) NodeCurr->NameOutUp);
              Output->SetAttribute("NameDown",(String) NodeCurr->NameOutDown);
              Output->Text = NodeCurr->GetActive() ? "True" : "False";

              _di_IXMLNode PinIn = XmlRoot->CreateElement("PinIn", "");
              Node->ChildNodes->Add(PinIn);
              PinIn->SetAttribute("NbUp",  (int) NodeCurr->GetPin_InUp());
              PinIn->SetAttribute("NbDown",(int) NodeCurr->GetPin_InDown());
              PinIn->Text = NodeCurr->GetPin_InUp()==0 && NodeCurr->GetPin_InDown()==0 ? "False" : "True";

              _di_IXMLNode PinOut = XmlRoot->CreateElement("PinOut", "");
              Node->ChildNodes->Add(PinOut);
              PinOut->SetAttribute("NbUp",  (int) NodeCurr->GetPin_OutUp());
              PinOut->SetAttribute("NbDown",(int) NodeCurr->GetPin_OutDown());
              PinOut->Text = NodeCurr->GetPin_OutUp()==0 && NodeCurr->GetPin_OutDown()==0 ? "False" : "True";
        }
        this->pgLoading->Position++;
     }
     this->ItsUpdated = false;
     XmlRoot->SaveToFile(this->NodeSaveDialog->FileName);
     this->pgLoading->Position = 0;
   }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::LoadAnnotation(_di_IXMLNode pAnnotation)
{
   String ID, Name, Type, R, G, B;
   TPoint PointA, PointB;
   TStringList *AnnotationData;

   _di_IXMLNodeList AllAnnotation = pAnnotation->ChildNodes;

   for(int i = 0; i < AllAnnotation->Count; i++) {
      ID           = AllAnnotation->Get(i)->GetAttribute("ID");
      Name         = AllAnnotation->Get(i)->GetAttribute("Name");
      Type         = AllAnnotation->Get(i)->GetAttribute("Type");

      AnnotationData = new TStringList;
      //AnnotationData->NameValueSeparator = '=';
      this->AnnotationList->Add(AnnotationData);

      AnnotationData->Add(Name); // 0
      AnnotationData->Add(Type); // 1

      _di_IXMLNode AnnotationInfo = AllAnnotation->Get(i)->ChildNodes->Nodes[0];
      R = AnnotationInfo->GetAttribute("R");
      G = AnnotationInfo->GetAttribute("G");
      B = AnnotationInfo->GetAttribute("B");
      AnnotationData->Add("Hue:R=" + R + ",G=" + G + ".B=" + B); // 2

      _di_IXMLNode AnnotationPoint;
      if (Type == "Rect") {
         AnnotationPoint = AllAnnotation->Get(i)->ChildNodes->Nodes[1];
         PointA.X = AnnotationPoint->GetAttribute("X");
         PointA.Y = AnnotationPoint->GetAttribute("Y");

         AnnotationPoint = AllAnnotation->Get(i)->ChildNodes->Nodes[2];
         PointB.X = AnnotationPoint->GetAttribute("X");
         PointB.Y = AnnotationPoint->GetAttribute("Y");

         AnnotationData->Add("X=" + IntToStr((int)PointA.X) + ",Y=" + IntToStr((int)PointA.Y)); // 3
         AnnotationData->Add("X=" + IntToStr((int)PointB.X) + ",Y=" + IntToStr((int)PointB.Y)); // 4

         AnnotationData->Add("Draw=False"); // 5
      }

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
  for (int i = 0; i<NodeCmp; i++) {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     if(! NodeCurr->DeleteFlag)
       NodeCurr->Send();
  }

  //Update internal state
  for (int i = 0; i<NodeCmp; i++) {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     if(! NodeCurr->DeleteFlag)
       NodeCurr->Work();
  }

  //Write to Output
  this->WriteOutput();
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::t_DrawTimer(TObject *Sender)
{
  if(this->cb_ActiveDraw->Checked)
     this->CallDrawArea(1);
}
//---------------------------------------------------------------------------

void Tf_CPUNode::ResetAllNode(void)
{
  TNode* NodeCurr;

  for (int i = 0; i<this->NodeCmp; i++) {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    NodeCurr->Reset();
  }

  //Update internal state for Not gates
  for (int i = 0; i<this->NodeCmp; i++) {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     NodeCurr->Work();
  }
  //Update internal state for Not gates
  for (int i = 0; i<this->NodeCmp; i++) {
     NodeCurr = (TNode*)this->NodeList->Items[i];
     NodeCurr->Send();
  }

  //Draw
  this->CallDrawArea(1);
}
//---------------------------------------------------------------------------
void Tf_CPUNode::ReadInput(void)
{
  TNode* NodeCurr;
  TCheckBox * CurrPin;
  int IDUp, IDDown;

  //Scan for Node with Input Pin ID
  for (int i = 0; i<NodeCmp; i++) {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    IDUp = NodeCurr->GetPin_InUp();
    IDDown = NodeCurr->GetPin_InDown();

    if (! NodeCurr->DeleteFlag) {
        //Pin connected to Input Up
        if (IDUp > 0) {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDUp));
          if (CurrPin != NULL)
            NodeCurr->Receive(CurrPin->Checked);
        }

        //Pin connected to Input Down
        if (IDDown > 0) {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDDown));
          if (CurrPin != NULL)
            NodeCurr->Receive(CurrPin->Checked);
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
  for (int i = 0; i<NodeCmp; i++) {
    NodeCurr = (TNode*)this->NodeList->Items[i];
    IDUp = NodeCurr->GetPin_OutUp();
    IDDown = NodeCurr->GetPin_OutDown();

    if (! NodeCurr->DeleteFlag) {
        //Pin connected to Output Up
        if (IDUp > 0) {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDUp));
          if (CurrPin != NULL)
            CurrPin->Checked = NodeCurr->GetActive();
        }

        //Pin connected to Output Down
        if (IDDown > 0) {
          CurrPin = (TCheckBox*)f_GraphIO->FindComponent("Pin" + IntToStr(IDDown));
          if (CurrPin != NULL)
            CurrPin->Checked = NodeCurr->GetActive();
        }
     }
  }
}
//---------------------------------------------------------------------------
void Tf_CPUNode::CallDrawArea(int pMode)
{
  TBitmap* Buffer = new TBitmap;
  TRect  SrcRect, DestRect;

  DrawCmpItem = 0;
  DrawCmpLine = 0;
  //t_DrawMulti1Timer(this);
  //t_DrawMulti2Timer(this);
  //t_DrawMulti3Timer(this);
  //this->DrawArea(0);
  this->p_DrawCmp->Caption = "Draw: " + IntToStr(DrawCmpItem) + " - " + IntToStr(DrawCmpLine);

  if (pMode == 1)
     this->DrawBuffer(0);

  SrcRect.init(OffSetX, OffSetY, OffSetX + this->p_Area->Width, OffSetY + this->p_Area->Height);
  DestRect.init(0, 0, this->p_Area->Width, this->p_Area->Height);

  Buffer->Height = this->p_Area->Height;
  Buffer->Width  = this->p_Area->Width ;
  Buffer->HandleType = bmDIB; // allows use of ScanLine
  Buffer->PixelFormat = pf24bit;

  Buffer->Canvas->CopyRect(DestRect, this->MainCanvas->Canvas, SrcRect);

  this->Canvas->Draw(this->p_Area->Left, this->p_Area->Top, Buffer);

  Buffer->Free();
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::t_DrawMulti1Timer(TObject *Sender)
{
  //this->DrawArea(1);
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::t_DrawMulti2Timer(TObject *Sender)
{
  //this->DrawArea(2);
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::t_DrawMulti3Timer(TObject *Sender)
{
  //this->DrawArea(3);
  //HeaderControl->Repaint();
}
//---------------------------------------------------------------------------
void Tf_CPUNode::DrawBuffer(int NbDraw)
{
  TNode* NodeCurr;
  TNode* NodeUp;
  TNode* NodeDown;

  TPoint Triangle[3];

  this->MainCanvas->Canvas->Brush->Color  = clWhite;
  this->MainCanvas->Canvas->Pen->Color    = clBlue;
  this->MainCanvas->Canvas->Rectangle(0, 0, (800*this->GridSize)+10, (300*this->GridSize)+10);

  this->MainCanvas->Canvas->Brush->Color = clBtnFace;
  this->MainCanvas->Canvas->Pen->Color   = clBlack;
  //this->MainCanvas->Canvas->FillRect(ClientRect);

  for (int i = 0; i<NodeCmp; i++) {
	 //if (i%4 == NbDraw) {
		 //Node, Black Inactive, Red Active
		 NodeCurr = (TNode*)this->NodeList->Items[i];

		 if (NodeCurr->TagFlag)
		   this->MainCanvas->Canvas->Brush->Color = clGray;
		 else
		   this->MainCanvas->Canvas->Brush->Color = clBlack;
		 this->MainCanvas->Canvas->Pen->Color   = clBlack;

		 if (! NodeCurr->DeleteFlag) {

			 if(NodeCurr == NodeSelect)
				 this->MainCanvas->Canvas->Brush->Color = clWhite;
			 else if(NodeCurr->GetInOutType() == 0 && NodeCurr->GetActive()) {
				 if (NodeCurr->TagFlag)
				   this->MainCanvas->Canvas->Brush->Color = clLtGray;
				 else
				   this->MainCanvas->Canvas->Brush->Color = clRed;
			 } else if(NodeCurr->GetInOutType() == 1) {
          //Input, Green/Yellow
			   if (NodeCurr->GetActive())
				 this->MainCanvas->Canvas->Brush->Color = clYellow;
			   else
				 this->MainCanvas->Canvas->Brush->Color = clGreen;
			 } else if(NodeCurr->GetInOutType() == 2) {
          //Output, Blue/Purple
			   if (NodeCurr->GetActive())
				 this->MainCanvas->Canvas->Brush->Color = clPurple;
			   else
				 this->MainCanvas->Canvas->Brush->Color = clBlue;
			 }

			 switch(NodeCurr->GetType()) {
			   case 0: { //OR Circle
				   this->MainCanvas->Canvas->Ellipse( NodeCurr->X * GridSize,
										                    NodeCurr->Y * GridSize,
                                                 (NodeCurr->X * GridSize) + ObjSize,
										                   (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 1: { //AND Square
				   this->MainCanvas->Canvas->Rectangle( NodeCurr->X * GridSize,
										                      NodeCurr->Y * GridSize,
										                     (NodeCurr->X * GridSize) + ObjSize,
										                     (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 2: { //NOR Circle with a Point
				   this->MainCanvas->Canvas->Ellipse( NodeCurr->X * GridSize,
										                    NodeCurr->Y * GridSize,
                                                 (NodeCurr->X * GridSize) + ObjSize,
                                                 (NodeCurr->Y * GridSize) + ObjSize);

				   //this->MainCanvas->Canvas->MoveTo((NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize));
				   Triangle[0] = Point((NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize));
				   Triangle[1] = Point((NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point((NodeCurr->X * GridSize) + ObjSize + (ObjSize/2), (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->Polygon(Triangle, 2);
				   break;
			   }
			   case 3: { //NAND Square with a Point
				   this->MainCanvas->Canvas->Rectangle( NodeCurr->X * GridSize,
										                      NodeCurr->Y * GridSize,
										                     (NodeCurr->X * GridSize) + ObjSize,
                                                   (NodeCurr->Y * GridSize) + ObjSize);

				   //this->MainCanvas->Canvas->MoveTo( (NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize));
				   Triangle[0] = Point((NodeCurr->X * GridSize) + (ObjSize/2),  (NodeCurr->Y * GridSize));
				   Triangle[1] = Point((NodeCurr->X * GridSize) + (ObjSize/2),  (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point((NodeCurr->X * GridSize) + ObjSize + (ObjSize/2), (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->Polygon(Triangle, 2);
				   break;
			   }
			   case 4: { //XOR Circle with a White +
				   this->MainCanvas->Canvas->Ellipse( NodeCurr->X * GridSize,
                                                  NodeCurr->Y * GridSize,
										                   (NodeCurr->X * GridSize) + ObjSize,
										                   (NodeCurr->Y * GridSize) + ObjSize);

				   if(NodeCurr == NodeSelect)
					 this->MainCanvas->Canvas->Pen->Color = clBlack;
				   else
					 this->MainCanvas->Canvas->Pen->Color = clWhite;
				   this->MainCanvas->Canvas->MoveTo( (NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize) );
				   this->MainCanvas->Canvas->LineTo( (NodeCurr->X * GridSize) + (ObjSize/2), (NodeCurr->Y * GridSize) + ObjSize );
				   this->MainCanvas->Canvas->MoveTo( (NodeCurr->X * GridSize)              , (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->LineTo( (NodeCurr->X * GridSize) + ObjSize    , (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->Pen->Color = clBlack;
				   break;
			   }
			   case 5: { //NOT Triangle
				   //this->MainCanvas->Canvas->MoveTo( (NodeCurr->X * GridSize),  (NodeCurr->Y * GridSize));
				   Triangle[0] = Point( (NodeCurr->X * GridSize), (NodeCurr->Y * GridSize));
				   Triangle[1] = Point( (NodeCurr->X * GridSize), (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point( (NodeCurr->X * GridSize) + ObjSize, (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->Polygon(Triangle, 2);
				   break;
			   }
            case 6: { //LINK Line
				   if (NodeCurr == NodeSelect)
					   this->MainCanvas->Canvas->Pen->Color = clWhite;
               else if (NodeCurr->GetActive()) {
				      if (NodeCurr->TagFlag)
				         this->MainCanvas->Canvas->Pen->Color = clLtGray;
				      else
				         this->MainCanvas->Canvas->Pen->Color = clRed;
			      } else
					   this->MainCanvas->Canvas->Pen->Color = clBlack;

				   this->MainCanvas->Canvas->MoveTo( (NodeCurr->X * GridSize)           , (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->LineTo( (NodeCurr->X * GridSize) + ObjSize , (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->MainCanvas->Canvas->Pen->Color = clBlack;
				   break;
            }
			 }

		   this->MainCanvas->Canvas->Brush->Color = clBlack;
		   if (NodeCurr->GetActive()) {
			   if (NodeCurr->TagFlag)
				 this->MainCanvas->Canvas->Pen->Color = clYellow;
			   else
				 this->MainCanvas->Canvas->Pen->Color = clRed;
		   } else {
			   if (NodeCurr->TagFlag)
				 this->MainCanvas->Canvas->Pen->Color = clSilver;
			   else
				 this->MainCanvas->Canvas->Pen->Color = clBlack;
		   }

		   //Line Out Up
		   NodeUp = NodeCurr->GetNodeOutUp();
		   if (NodeUp != NULL) {
				 this->MainCanvas->Canvas->MoveTo((NodeCurr->X * GridSize) +  ObjSize,
									                   (NodeCurr->Y * GridSize) + (ObjSize/2) );
				 this->MainCanvas->Canvas->LineTo((NodeUp->X * GridSize),
									                   (NodeUp->Y * GridSize) + (ObjSize/2) );
		   }

		   //Line Out Down
		   NodeDown = NodeCurr->GetNodeOutDown();
		   if (NodeDown != NULL) {
				 this->MainCanvas->Canvas->MoveTo((NodeCurr->X * GridSize) +  ObjSize,
									                   (NodeCurr->Y * GridSize) + (ObjSize/2) );
				 this->MainCanvas->Canvas->LineTo((NodeDown->X * GridSize),
									                   (NodeDown->Y * GridSize) + (ObjSize/2) );
		   }
		 }
	  //}//if modulo
  }
}

//---------------------------------------------------------------------------
void Tf_CPUNode::DrawArea(int NbDraw)
{
/*  TNode* NodeCurr;
  TNode* NodeUp;
  TNode* NodeDown;

  int StartX = OffSetX + this->p_Area->Left;
  int StartY = OffSetY + this->p_Area->Top;
  int MaxX   = this->p_Area->Left + this->p_Area->Width;
  int MaxY   = this->p_Area->Top  + this->p_Area->Height;

  TPoint Triangle[3];

  this->Canvas->Refresh();

  this->Canvas->Brush->Color = clBtnFace;
  this->Canvas->Pen->Color   = clBlack;
  //this->Canvas->FillRect(ClientRect);

  for (int i = 0; i<NodeCmp; i++) {
	 if (i%4 == NbDraw) {
		 //Node, Black Inactive, Red Active
		 NodeCurr = (TNode*)this->NodeList->Items[i];

		 if (NodeCurr->TagFlag)
		   this->Canvas->Brush->Color = clGray;
		 else
		   this->Canvas->Brush->Color = clBlack;
		 this->Canvas->Pen->Color   = clBlack;

		 if (! NodeCurr->DeleteFlag) {
		   if((StartX + (NodeCurr->X * GridSize)) > 0 &&
			  (StartY + (NodeCurr->Y * GridSize)) > 0 &&
			  (StartX + (NodeCurr->X * GridSize)) < MaxX &&
			  (StartY + (NodeCurr->Y * GridSize)) < MaxY )
		   {
			 DrawCmpItem++;
			 if(NodeCurr == NodeSelect)
				 this->Canvas->Brush->Color = clWhite;
			 else if(NodeCurr->GetInOutType() == 0 && NodeCurr->GetActive()) {
				 if (NodeCurr->TagFlag)
				   this->Canvas->Brush->Color = clLtGray;
				 else
				   this->Canvas->Brush->Color = clRed;
			 } else if(NodeCurr->GetInOutType() == 1) {
          //Input, Green/Yellow
			   if (NodeCurr->GetActive())
				 this->Canvas->Brush->Color = clYellow;
			   else
				 this->Canvas->Brush->Color = clGreen;
			 } else if(NodeCurr->GetInOutType() == 2) {
          //Output, Blue/Purple
			   if (NodeCurr->GetActive())
				 this->Canvas->Brush->Color = clPurple;
			   else
				 this->Canvas->Brush->Color = clBlue;
			 }

			 switch(NodeCurr->GetType()) {
			   case 0: { //OR Circle
				   this->Canvas->Ellipse(StartX + (NodeCurr->X * GridSize),
										 StartY + (NodeCurr->Y * GridSize),
										 StartX + (NodeCurr->X * GridSize) + ObjSize,
										 StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 1: { //AND Square
				   this->Canvas->Rectangle(StartX + (NodeCurr->X * GridSize),
										   StartY + (NodeCurr->Y * GridSize),
										   StartX + (NodeCurr->X * GridSize) + ObjSize,
										   StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   break;
			   }
			   case 2: { //NOR Circle with a Point
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
			   case 3: { //NAND Square with a Point
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
			   case 4: { //XOR Circle with a White +
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
			   case 5: { //NOT Triangle
				   //this->Canvas->MoveTo(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize));
				   Triangle[0] = Point(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize));
				   Triangle[1] = Point(StartX + (NodeCurr->X * GridSize), StartY + (NodeCurr->Y * GridSize) + ObjSize);
				   Triangle[2] = Point(StartX + (NodeCurr->X * GridSize) + ObjSize, StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Polygon(Triangle, 2);
				   break;
			   }
            case 6: { //LINK Line
				   if (NodeCurr == NodeSelect)
					   this->Canvas->Pen->Color = clWhite;
               else if (NodeCurr->GetActive()) {
				      if (NodeCurr->TagFlag)
				         this->Canvas->Pen->Color = clLtGray;
				      else
				         this->Canvas->Pen->Color = clRed;
			      } else
					   this->Canvas->Pen->Color = clBlack;

				   this->Canvas->MoveTo( StartX + (NodeCurr->X * GridSize)              , StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->LineTo( StartX + (NodeCurr->X * GridSize) + ObjSize    , StartY + (NodeCurr->Y * GridSize) + (ObjSize/2) );
				   this->Canvas->Pen->Color = clBlack;
				   break;
            }
			 }
		   }//if in bounds

		   this->Canvas->Brush->Color = clBlack;
		   if (NodeCurr->GetActive()) {
			   if (NodeCurr->TagFlag)
				 this->Canvas->Pen->Color = clYellow;
			   else
				 this->Canvas->Pen->Color = clRed;
		   } else {
			   if (NodeCurr->TagFlag)
				 this->Canvas->Pen->Color = clSilver;
			   else
				 this->Canvas->Pen->Color = clBlack;
		   }

		   //Line Out Up
		   NodeUp = NodeCurr->GetNodeOutUp();
		   if (NodeUp != NULL) {
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
		   NodeDown = NodeCurr->GetNodeOutDown();
		   if (NodeDown != NULL) {
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
  }*/
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
  NodeSelect->Name = f_GraphEdit->e_Name->Text;
  NodeSelect->X = StrToInt(f_GraphEdit->e_PosX->Text);
  NodeSelect->Y = StrToInt(f_GraphEdit->e_PosY->Text);
  NodeSelect->SetType(f_GraphEdit->cb_Type->ItemIndex);
  NodeSelect->NameOutUp   = f_GraphEdit->e_NameOutUp->Text;
  NodeSelect->NameOutDown = f_GraphEdit->e_NameOutDown->Text;

  NodeSelect->SetInUp(StrToInt(f_GraphEdit->e_PinIDInUp->Text));
  NodeSelect->SetInDown(StrToInt(f_GraphEdit->e_PinIDInDown->Text));

  NodeSelect->DeleteFlag = f_GraphEdit->cb_Delete->Checked;

  if(NodeSelect->DeleteFlag)
  {
    NodeSelect->SetInUp(0);
    NodeSelect->SetInDown(0);
    NodeSelect->Name = NodeSelect->Name + "DELETEDELETEDELETEDELETEDELETE" ;
  }

  //If Node Name changed or deleted, update Nodes conneted to it "Upstream"
  for (int i = 0; i<NodeCmp; i++) {
    NodeCible = (TNode*)this->NodeList->Items[i];
    if (f_GraphEdit->l_SaveName->Caption == NodeCible->NameOutUp) {
	    if (NodeSelect->DeleteFlag) {
          NodeCible->NameOutUp = "";
          NodeCible->SetOutUp(0, NULL);
       } else if (f_GraphEdit->l_SaveName->Caption != f_GraphEdit->e_Name->Text) {
          NodeCible->NameOutUp = f_GraphEdit->e_Name->Text;
       }
    }
    if (f_GraphEdit->l_SaveName->Caption == NodeCible->NameOutDown) {
       if (NodeSelect->DeleteFlag) {
          NodeCible->NameOutDown = "";
          NodeCible->SetOutDown(0, NULL);
       } else if (f_GraphEdit->l_SaveName->Caption != f_GraphEdit->e_Name->Text) {
          NodeCible->NameOutDown = f_GraphEdit->e_Name->Text;
       }
    }
  }
  //If Output Node Up Changed / Removed
  if (f_GraphEdit->e_NameOutUp->Text != f_GraphEdit->l_NameOutUp->Caption || NodeSelect->DeleteFlag) {
    if (NodeSelect->NameOutUp != "") {
       int i = 0;
       while (i<NodeCmp) {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if(NodeSelect->DeleteFlag || NodeCible->Name == NodeSelect->NameOutUp) {
            NodeSelect->SetOutUp(0,NodeCible);
            i = NodeCmp;
          }
          i++;
       }
    } else {
       NodeSelect->SetOutUp(0,NULL);
    }
  }
  //If Output Node Down Changed / Removed
  if (f_GraphEdit->e_NameOutDown->Text != f_GraphEdit->l_NameOutDown->Caption || NodeSelect->DeleteFlag) {
    if (NodeSelect->NameOutDown != "") {
       int i = 0;
       while (i<NodeCmp) {
          NodeCible = (TNode*)this->NodeList->Items[i];
          if (NodeSelect->DeleteFlag || NodeCible->Name == NodeSelect->NameOutDown) {
            NodeSelect->SetOutDown(0,NodeCible);
            i = NodeCmp;
          }
          i++;
       }
    } else {
       NodeSelect->SetOutDown(0,NULL);
    }
  }

  //Update Output if Removed
  if (f_GraphEdit->e_NameOutUp->Text == "")
    NodeSelect->SetOutUp(StrToInt(f_GraphEdit->e_PinIDOutUp->Text), NULL);

  if (f_GraphEdit->e_NameOutDown->Text == "")
    NodeSelect->SetOutDown(StrToInt(f_GraphEdit->e_PinIDOutDown->Text), NULL);

  if (NodeSelect->DeleteFlag) {
    NodeSelect->SetOutUp(0,   NULL);
    NodeSelect->SetOutDown(0, NULL);
  }

  if(!NodeSelect->DeleteFlag) {
	if(this->cb_ColorLine->Checked)
	  TagFollowList(this->NodeSelect, 10, true);
  }

  //Reset Stored "Previous" names
  f_GraphEdit->l_SaveName->Caption    = NodeSelect->Name;
  f_GraphEdit->l_NameOutUp->Caption   = NodeSelect->NameOutUp;
  f_GraphEdit->l_NameOutDown->Caption = NodeSelect->NameOutDown;

  //Draw
  this->Invalidate();
  this->CallDrawArea(1);
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

bool Tf_CPUNode::NodeNameExists(String pName)
{
    TNode* NodeCurr;
    bool Found = false;

    for (int i = 0; i<NodeCmp; i++) {
       NodeCurr = (TNode*)this->NodeList->Items[i];
       if (! NodeCurr->DeleteFlag) {
          if (pName == NodeCurr->Name) {
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

  bool Found;

  this->sb_Main->SimpleText =	"Mouse: Left=Select, Right=Move, Middle=Create, Shift+Left=Link(1), Ctrl+Left=Link(2), Alt+Left=Unlink";

  //Left Click = Select
  if (Button == mbLeft && !(Shift.Contains(ssCtrl) || Shift.Contains(ssShift) || Shift.Contains(ssAlt))) {
	  this->SelectList->Clear();

     this->MouseDownX = X;
	  this->MouseDownY = Y;
     for (int i = 0; i<NodeCmp; i++) {
         NodeCurr = (TNode*)this->NodeList->Items[i];
         if (! NodeCurr->DeleteFlag) {
             if(   X >= ( (NodeCurr->X * GridSize)            - OffSetX) + this->p_Area->Left
                && X <  (((NodeCurr->X * GridSize) + ObjSize) - OffSetX) + this->p_Area->Left
                && Y >= ( (NodeCurr->Y * GridSize)            - OffSetY) + this->p_Area->Top
                && Y <  (((NodeCurr->Y * GridSize) + ObjSize) - OffSetY) + this->p_Area->Top ) {

                if(this->cb_ColorLine->Checked)
                   TagFollowList(this->NodeSelect, 10, false);
                this->NodeSelect = NodeCurr;

                if(this->cb_ColorLine->Checked)
                   TagFollowList(this->NodeSelect, 10, true);
                this->CallDrawArea(1);

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

                f_GraphEdit->e_PinIDInUp->Text = IntToStr(NodeCurr->GetPin_InUp());
                f_GraphEdit->e_PinIDInDown->Text = IntToStr(NodeCurr->GetPin_InDown());
                f_GraphEdit->e_PinIDOutUp->Text = IntToStr(NodeCurr->GetPin_OutUp());
                f_GraphEdit->e_PinIDOutDown->Text = IntToStr(NodeCurr->GetPin_OutDown());

                f_GraphEdit->Visible = true;
                i = NodeCmp;
             }
         }
      }
  }
  //Right Click = Move Selected
  else if(Button == mbRight && NodeSelect != NULL) {
    this->SelectList->Clear();
    this->ItsUpdated = true;

	 NodeSelect->X = ((X + OffSetX) - this->p_Area->Left) / GridSize;
    NodeSelect->Y = ((Y + OffSetY) - this->p_Area->Top) / GridSize;
    f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
    f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);

    //Draw
    this->Invalidate();
    this->CallDrawArea(1);
  }
  //Middle Click = Create
  else if(Button == mbMiddle)
  {
    this->SelectList->Clear();
    this->ItsUpdated = true;

    pX = ((X + OffSetX) - this->p_Area->Left) / GridSize;
    pY = ((Y + OffSetY) - this->p_Area->Top) / GridSize;

    if(this->FlagNewNode)
       ShowMessage("Double Node");
    else {
       this->NodeMaxID++;
       Name = "Node" + IntToStr(this->NodeMaxID);
       while (NodeNameExists(Name)) {
         this->NodeMaxID++;
         Name = "Node" + IntToStr(this->NodeMaxID);
       }

       NodeCurr = new TNode(this->NodeMaxID, pX, pY, NodeType, Name);
       NodeCmp++;

       this->NodeList->Add(NodeCurr);
       this->FlagNewNode = false;
       TagFollowList(this->NodeSelect, 10, false);
       this->NodeSelect = NodeCurr;
    }

    //Draw
    this->CallDrawArea(1);
  }
  //Left Click + Shift or Ctlr = Link Selected
  else if (Button == mbLeft && (Shift.Contains(ssCtrl) || Shift.Contains(ssShift))) {
      this->MouseDownX = X;
      this->MouseDownY = Y;

      if (NodeSelect != NULL) {
          Found = false;

          for (int i = 0; i<NodeCmp; i++) {
             NodeCurr = (TNode*)this->NodeList->Items[i];
             if (! NodeCurr->DeleteFlag) {
                 if(   X >= ( (NodeCurr->X * GridSize)            - OffSetX) + this->p_Area->Left
                    && X <  (((NodeCurr->X * GridSize) + ObjSize) - OffSetX) + this->p_Area->Left
                    && Y >= ( (NodeCurr->Y * GridSize)            - OffSetY) + this->p_Area->Top
                    && Y <  (((NodeCurr->Y * GridSize) + ObjSize) - OffSetY) + this->p_Area->Top)
                 {
                    //this->NodeSelect = NodeCurr;
                    if (Shift.Contains(ssShift))
                      f_GraphEdit->e_NameOutUp->Text = NodeCurr->Name;
                    else if(Shift.Contains(ssCtrl))
                      f_GraphEdit->e_NameOutDown->Text = NodeCurr->Name;

                    f_GraphEdit->Visible = true;
                    Found = true;
                    i = NodeCmp;
                 }
             }
          }
          if(Found) {
              this->SelectList->Clear();

              UpdateNode();
              if (Shift.Contains(ssShift))
                f_GraphEdit->l_NameOutUp->Caption = NodeCurr->Name;
              else if(Shift.Contains(ssCtrl))
                f_GraphEdit->l_NameOutDown->Caption = NodeCurr->Name;

              //Draw
              this->CallDrawArea(1);
          }
      }
  }
  //Left Click + Alt = Link Remove
  else if (Button == mbLeft && Shift.Contains(ssAlt))
  {
     this->SelectList->Clear();

     this->MouseDownX = X;
     this->MouseDownY = Y;
     for (int i = 0; i<NodeCmp; i++) {
        NodeCurr = (TNode*)this->NodeList->Items[i];
        if (! NodeCurr->DeleteFlag) {
            if(   X >=  ( (NodeCurr->X * GridSize)            - OffSetX) + this->p_Area->Left
                && X <  (((NodeCurr->X * GridSize) + ObjSize) - OffSetX) + this->p_Area->Left
                && Y >= ( (NodeCurr->Y * GridSize)            - OffSetY) + this->p_Area->Top
                && Y <  (((NodeCurr->Y * GridSize) + ObjSize) - OffSetY) + this->p_Area->Top) {

				   TagFollowList(this->NodeSelect, 10, false);
				   this->NodeSelect = NodeCurr;

               this->NodeSelect->NameOutUp = "";
               this->NodeSelect->SetOutUp(0, NULL);
               this->NodeSelect->NameOutDown = "";
               this->NodeSelect->SetOutDown(0, NULL);
               //Draw
               this->Invalidate();
               this->CallDrawArea(1);

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

               f_GraphEdit->e_PinIDInUp->Text = IntToStr(NodeCurr->GetPin_InUp());
               f_GraphEdit->e_PinIDInDown->Text = IntToStr(NodeCurr->GetPin_InDown());
               f_GraphEdit->e_PinIDOutUp->Text = IntToStr(NodeCurr->GetPin_OutUp());
               f_GraphEdit->e_PinIDOutDown->Text = IntToStr(NodeCurr->GetPin_OutDown());

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
  if (Depth > 0 && NodeTag != NULL) {
	NodeTag->TagFlag = Sel;
	TagFollowList(NodeTag->GetNodeOutUp(), Depth-1, Sel);
	TagFollowList(NodeTag->GetNodeOutDown(), Depth-1, Sel);
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

  this->MainCanvas->Canvas->Brush->Color  = clWhite;
  this->MainCanvas->Canvas->Pen->Color    = clWhite;
  this->MainCanvas->Canvas->Rectangle(-15, -15, (800*this->GridSize)+15, (300*this->GridSize)+15);

  //Update zoom by steps
  switch (tb_Size->Position) //1.35 factor
  {                   
    case 9: {this->ObjSize = 2;  this->GridSize = 3;  break;}
    case 8: {this->ObjSize = 3;  this->GridSize = 4;  break;}
    case 7: {this->ObjSize = 4;  this->GridSize = 5;  break;}  //4000->1500
    case 6: {this->ObjSize = 5;  this->GridSize = 7;  break;}
    case 5: {this->ObjSize = 7;  this->GridSize = 10;  break;}
    case 4: {this->ObjSize = 9;  this->GridSize = 13;  break;}
    case 3: {this->ObjSize = 12;  this->GridSize = 18;  break;}
    //case 2: {this->ObjSize = 16;  this->GridSize = 25;  break;}
    //case 1: {this->ObjSize = 22;  this->GridSize = 33;  break;}
    //case 0: {this->ObjSize = 30;  this->GridSize = 45;  break;}
  }

  CurrentGridSize = GridSize;
  ZoomFactor = (CurrentGridSize / PreviousGridSize);

  this->OffSetX = ( dX * ZoomFactor) + ( (pX * ZoomFactor) - pX);
  this->OffSetY = ( dY * ZoomFactor) + ( (pY * ZoomFactor) - pY);

  this->MainCanvas->Height = (300 * this->GridSize) + 22;
  this->MainCanvas->Width  = (800 * this->GridSize) + 22;

  //Draw
  this->Invalidate();
  this->CallDrawArea(1);
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
    this->tb_Size->Position--;
  else
    this->tb_Size->Position++;

  Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall Tf_CPUNode::AppMessage(TMsg& PassedMsg, bool& Handled)
{
  if (PassedMsg.message == WM_KEYDOWN ) {
	  // add support for SelectList ??? :p
	  
	  if (Screen->ActiveForm == f_CPUNode) {
		  //Catch arrows for mouvment
		  switch (PassedMsg.wParam) {
			case VK_UP:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL) {
				 NodeSelect->Y--;
				 f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);
			  } else
				 this->OffSetY += (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea(1);
			  break;
			}
			case VK_DOWN:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL) {
				 NodeSelect->Y++;
				 f_GraphEdit->e_PosY->Text = IntToStr(NodeSelect->Y);
			  } else
				 this->OffSetY -= (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea(1);
			  break;
			}
			case VK_LEFT:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL) {
				 NodeSelect->X--;
				 f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
			  } else
				 this->OffSetX += (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea(1);
			  break;
			}
			case VK_RIGHT:
			{
			  if (this->cb_QuickEdit->Checked && NodeSelect != NULL) {
				 NodeSelect->X++;
				 f_GraphEdit->e_PosX->Text = IntToStr(NodeSelect->X);
			  } else
			   	this->OffSetX -= (GridSize * ((tb_Size->Position + 1) * 10) );
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea(1);
			  break;
			}
			case VK_SPACE:
			{
			  this->OffSetX = 0;
			  this->OffSetY = 0;
			  Handled = true;
			  this->Invalidate();
			  this->CallDrawArea(1);
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
  if (Key == VK_DELETE && NodeSelect != NULL) {
    if (Application->MessageBox( L"Delete Node ?", L"Delete Node", MB_YESNO) == mrYes) {
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
  else if (this->cb_QuickEdit->Checked) {
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
    else if(Key == 'L' && NodeSelect != NULL)
      f_GraphEdit->cb_Type->ItemIndex = 6;

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
  this->OffSetX = -22;
  this->OffSetY = -22;
  this->ObjSize = 4;
  this->GridSize = 5;
  this->tb_Size->Position = 7;
  this->tb_Speed->Position = 15;
  this->FlagNewNode = false;
  this->AnnotationDrawn = false;

  this->MainCanvas->Height = (300 * this->GridSize) + 22;
  this->MainCanvas->Width  = (800 * this->GridSize) + 22;
  this->MainCanvas->HandleType = bmDIB; // allows use of ScanLine
  this->MainCanvas->PixelFormat = pf24bit;

}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  TNode* NodeCurr;
  String Name;
  int Type;

  TStringList *AnnotationSelect;
  TRect  SrcRect, DestRect;
  String PointA, PointB, DrawFlag, Hue;
  int UpLX, UpLY, DownRX, DownRY;
  bool AnnotationFound = false;
  TBitmap* AnnotationCanvas;
  TColor SelectPixel;
  float ColorR, ColorG, ColorB;
  int ColorInt;
  String ColR, ColG, ColB;
  Byte *pyx;

  int UpdateOffSetX;
  int UpdateOffSetY;

  //Catch cursor mouvment when "drag & drop" of the Canvas
  if(Shift.Contains(ssLeft) && !(Shift.Contains(ssCtrl) || Shift.Contains(ssShift))
     && (X <= this->MouseDownX-GridSize || X >= this->MouseDownX+GridSize || Y <= this->MouseDownY-GridSize || Y >= this->MouseDownY+GridSize) )
   {
   //Move view
      this->OffSetX -= X - this->MouseDownX;
      this->OffSetY -= Y - this->MouseDownY;
      this->MouseDownX = X;
      this->MouseDownY = Y;
      //Draw
      //this->Invalidate();
      //this->Canvas->Brush->Color = clBtnFace;
      //this->Canvas->Pen->Color = clBlack;
      //this->Canvas->FillRect(ClientRect);
      this->CallDrawArea(0);

      this->sb_Main->Panels->Items[0]->Text = "Drag & drop: Left=Scroll, Shift+Left=Select, Ctrl+Left=Move";
  } else if (Shift.Contains(ssLeft) && Shift.Contains(ssShift) && !Shift.Contains(ssCtrl)) {
  //Select (Shift)
	  this->SelectList->Clear();
      for (int i = 0; i<NodeCmp; i++) {
          NodeCurr = (TNode*)this->NodeList->Items[i];
          if(! NodeCurr->DeleteFlag) {
             if(  (  (   this->MouseDownX < X
                      && ((NodeCurr->X*GridSize)-OffSetX)+this->p_Area->Left >= this->MouseDownX
                      && ((NodeCurr->X*GridSize)-OffSetX)+this->p_Area->Left <= X)
                   ||(   this->MouseDownX > X
                      && ((NodeCurr->X*GridSize)-OffSetX)+this->p_Area->Left <= this->MouseDownX
                      && ((NodeCurr->X*GridSize)-OffSetX)+this->p_Area->Left >= X) )
                &&(  (   this->MouseDownY < Y
                      && ((NodeCurr->Y*GridSize)-OffSetY)+this->p_Area->Top  >= this->MouseDownY
                      && ((NodeCurr->Y*GridSize)-OffSetY)+this->p_Area->Top <= Y)
                   ||(   this->MouseDownY > Y
                      && ((NodeCurr->Y*GridSize)-OffSetY)+this->p_Area->Top  <= this->MouseDownY
                      && ((NodeCurr->Y*GridSize)-OffSetY)+this->p_Area->Top >= Y) ) ) {
				    this->SelectList->Add(NodeCurr);
             }
          }
      }
      //Draw
      //this->Invalidate();
      this->CallDrawArea(0);

      this->Canvas->Brush->Color = clBtnFace;
      this->Canvas->Pen->Color = clGreen;
      this->Canvas->Pen->Width = 2;
      this->Canvas->MoveTo(this->MouseDownX, this->MouseDownY);
      this->Canvas->LineTo(X,this->MouseDownY);
      this->Canvas->LineTo(X, Y);
      this->Canvas->LineTo(this->MouseDownX, Y);
      this->Canvas->LineTo(this->MouseDownX, this->MouseDownY);
      this->Canvas->Pen->Width = 1;

  } else if(Shift.Contains(ssLeft) && !Shift.Contains(ssShift) && Shift.Contains(ssCtrl)
            && (X <= this->MouseDownX-GridSize || X >= this->MouseDownX+GridSize || Y <= this->MouseDownY-GridSize || Y >= this->MouseDownY+GridSize))
  {
  //Move Selection (Ctrl)
      UpdateOffSetX = (X - this->MouseDownX) / GridSize ;
      UpdateOffSetY = (Y - this->MouseDownY) / GridSize ;
      this->MouseDownX = X;
      this->MouseDownY = Y;
      
      for (int i = 0; i<this->SelectList->Count; i++) {
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
      this->CallDrawArea(1);
  } else {
  //Update status bar Info for Node Name/Type
      for (int i = 0; i<NodeCmp; i++) {
         NodeCurr = (TNode*)this->NodeList->Items[i];
         if (! NodeCurr->DeleteFlag) {
             if(   X >= ( (NodeCurr->X * GridSize)            - OffSetX)+this->p_Area->Left
                && X <  (((NodeCurr->X * GridSize) + ObjSize) - OffSetX)+this->p_Area->Left
                && Y >= ( (NodeCurr->Y * GridSize)            - OffSetY)+this->p_Area->Top
                && Y <  (((NodeCurr->Y * GridSize) + ObjSize) - OffSetY)+this->p_Area->Top )
             {
                //Type = NodeCurr->GetType();
                Name = NodeCurr->Name;
                Type = NodeCurr->GetType();

                this->sb_Main->Panels->Items[0]->Text = Name + " [" + f_GraphEdit->cb_Type->Items->Strings[Type] + "]";
                //this->Hint = Name + " [" + f_GraphEdit->cb_Type->Items->Strings[Type] + "]";
                //f_CPUNode->Hint

                i = NodeCmp;
             }
         }
      }

      if (cb_Annotation->Checked) {
         for(int i = 0; i<AnnotationList->Count ; i++) {
            AnnotationSelect = (TStringList*)AnnotationList->Items[i];
            PointA = AnnotationSelect->Strings[3];
            PointB = AnnotationSelect->Strings[4];
            DrawFlag = AnnotationSelect->Strings[5];
            if (DrawFlag == "Draw=True") {
               UpLX   = StrToInt( PointA.SubString(3, PointA.Pos(",")-3) )              ;
               UpLY   = StrToInt( PointA.SubString(PointA.Pos(",")+3, PointA.Length()) );
               DownRX = StrToInt( PointB.SubString(3, PointB.Pos(",")-3) )              ;
               DownRY = StrToInt( PointB.SubString(PointB.Pos(",")+3, PointB.Length()) );

               UpLX   = ( UpLX * GridSize) - OffSetX;
               UpLY   = ( UpLY * GridSize) - OffSetY;
               DownRX = ((DownRX + ObjSize) * GridSize) - OffSetX;
               DownRY = ((DownRY + ObjSize) * GridSize) - OffSetY;

               if(!(   X >= UpLX
                    && X <  DownRX
                    && Y >= UpLY
                    && Y <  DownRY) )
               {
                  AnnotationSelect->Strings[5] = "Draw=False";

                  AnnotationCanvas = new TBitmap;

                  UpLX   = UpLX   ;
                  UpLY   = UpLY   ;
                  DownRX = DownRX ;
                  DownRY = DownRY ;

                  int Height=DownRY-UpLY ,Width=DownRX-UpLX;
                  SrcRect.init(UpLX+OffSetX, UpLY+OffSetY, DownRX+OffSetX, DownRY+OffSetY);
                  DestRect.init(0, 0, Width, Height);

                  AnnotationCanvas->Height = Height;
                  AnnotationCanvas->Width  = Width ;
                  AnnotationCanvas->HandleType = bmDIB; // allows use of ScanLine
                  AnnotationCanvas->PixelFormat = pf24bit;
                  AnnotationCanvas->Canvas->CopyRect(DestRect, this->MainCanvas->Canvas, SrcRect);

                  this->Canvas->Draw(UpLX+this->p_Area->Left, UpLY+this->p_Area->Top, AnnotationCanvas);
                  AnnotationCanvas->Free();
               }
            }
         }
         for(int i = 0; i<AnnotationList->Count ; i++) {
            AnnotationSelect = (TStringList*)AnnotationList->Items[i];
            Hue    = AnnotationSelect->Strings[2];
            PointA = AnnotationSelect->Strings[3];
            PointB = AnnotationSelect->Strings[4];

            DrawFlag = AnnotationSelect->Strings[5];

            UpLX   = StrToInt( PointA.SubString(3, PointA.Pos(",")-3) )              ;
            UpLY   = StrToInt( PointA.SubString(PointA.Pos(",")+3, PointA.Length()) );
            DownRX = StrToInt( PointB.SubString(3, PointB.Pos(",")-3) )              ;
            DownRY = StrToInt( PointB.SubString(PointB.Pos(",")+3, PointB.Length()) );

            UpLX   = ( UpLX * GridSize) - OffSetX;
            UpLY   = ( UpLY * GridSize) - OffSetY;
            DownRX = ((DownRX + ObjSize) * GridSize) - OffSetX;
            DownRY = ((DownRY + ObjSize) * GridSize) - OffSetY;

            if(   X >= UpLX
               && X <  DownRX
               && Y >= UpLY
               && Y <  DownRY )
            {

               AnnotationFound = true;
               this->AnnotationDrawn = true;
               if (DrawFlag == "Draw=False") {
                  AnnotationSelect->Strings[5] = "Draw=True";

                  AnnotationCanvas = new TBitmap;

                  UpLX   = UpLX   ;
                  UpLY   = UpLY   ;
                  DownRX = DownRX ;
                  DownRY = DownRY ;


                  int Height=DownRY-UpLY ,Width=DownRX-UpLX;
                  SrcRect.init(UpLX+OffSetX, UpLY+OffSetY, DownRX+OffSetX, DownRY+OffSetY);
                  DestRect.init(0, 0, Width, Height);

                  AnnotationCanvas->Height = Height;
                  AnnotationCanvas->Width  = Width ;
                  AnnotationCanvas->HandleType = bmDIB; // allows use of ScanLine
                  AnnotationCanvas->PixelFormat = pf24bit;
                  AnnotationCanvas->Canvas->CopyRect(DestRect, this->MainCanvas->Canvas, SrcRect);

                  //"Hue:R=" + R + ",V=" + V + ".B=" + B
                  //int R=StrToInt(e_R->Text),V=StrToInt(e_V->Text),B=StrToInt(e_B->Text);

                  ColR = Hue.SubString(7,Hue.Pos(",")-7);
                  ColG = Hue.SubString(Hue.Pos(",")+3,Hue.Pos(".")-Hue.Pos(",")-3);
                  ColB = Hue.SubString(Hue.Pos(".")+3,Hue.Length());

                  ColorR = 1.0-(StrToInt(ColR)/200.0);
                  ColorG = 1.0-(StrToInt(ColG)/200.0);
                  ColorB = 1.0-(StrToInt(ColB)/200.0);

                  for (int y = 0; y < Height; y++) {
                     pyx=(Byte *)AnnotationCanvas->ScanLine[y];
                     for (int x = 0; x < Width; x++) {
                        ColorInt = (pyx[x*3] * ColorG) * ColorR ; // Blue
                        if (ColorInt > 255)
                           pyx[x*3] = 255;
                        else
                           pyx[x*3] = ColorInt;

                        ColorInt = (pyx[x*3 + 1] * ColorR) * ColorB ; //Green
                        if (ColorInt > 255)
                           pyx[x*3 + 1] = 255;
                        else
                           pyx[x*3 + 1] = ColorInt;

                        ColorInt = (pyx[x*3 + 2] * ColorB) * ColorG ; //Red
                        if (ColorInt > 255)
                           pyx[x*3 + 2] = 255;
                        else
                           pyx[x*3 + 2] = ColorInt;
                     }
                  }

                  AnnotationCanvas->Canvas->TextOutA(10,10, AnnotationSelect->Strings[0]);

                  this->Canvas->Draw(UpLX+this->p_Area->Left, UpLY+this->p_Area->Top, AnnotationCanvas);
                  AnnotationCanvas->Free();

                  /*
                  this->Canvas->Brush->Color = clBtnFace;
                  this->Canvas->Pen->Color = clBlue;
                  this->Canvas->Pen->Width = 2;
                  this->Canvas->MoveTo(UpLX, UpLY);
                  this->Canvas->LineTo(DownRX, UpLY);
                  this->Canvas->LineTo(DownRX, DownRY);
                  this->Canvas->LineTo(UpLX, DownRY);
                  this->Canvas->LineTo(UpLX, UpLY);
                  this->Canvas->Pen->Width = 1;
                  */
               }
            } else {
               AnnotationSelect->Strings[5] = "Draw=False";
               //this->CallDrawArea(0);
               //AnnotationSelect->Canvas->CopyRect(DestRect, this->MainCanvas->Canvas, SrcRect);
               //this->Canvas->Draw(this->p_Area->Left, this->p_Area->Top, AnnotationSelect);
            }
         }
         if (!AnnotationFound && this->AnnotationDrawn) {
            this->AnnotationDrawn = false;
            this->Invalidate();
            this->CallDrawArea(0);
         }

      }
  }
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormPaint(TObject *Sender)
{
   this->CallDrawArea(0);
}
//---------------------------------------------------------------------------

void __fastcall Tf_CPUNode::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  if(this->ItsUpdated && Application->MessageBox( L"Save changes before Quit?", L"Save changes", MB_YESNO) == mrYes)
      this->b_Save->Click();
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

void __fastcall Tf_CPUNode::cb_QuickEditMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
   this->sb_Main->Panels->Items[0]->Text = "Keyboard: O=Or, A=And, R=Nor, D=Nand, X=Xor, N=Not";
}
//---------------------------------------------------------------------------

