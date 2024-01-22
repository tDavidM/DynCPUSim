//---------------------------------------------------------------------------

#ifndef NodeCPUH
#define NodeCPUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <XPMan.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
#include "GraphIO.h"
#include "GraphEdit.h"
#include "Memory.h"
#include "Ram.h"
#include <Vcl.Dialogs.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

#define VK_KEY_1 0x31
#define VK_KEY_2 0x32
#define VK_KEY_3 0x33
#define VK_KEY_4 0x34
#define VK_KEY_5 0x35
#define VK_KEY_6 0x36
//---------------------------------------------------------------------------
class TNode
{
private:
  int Type;

  int PinInUp, PinInDown, PinOutUp, PinOutDown;
  TNode /* *InUp, *InDown,*/ *NodeOutUp, *NodeOutDown;
  int  ActiveDelay;
  bool Active;
  bool InUpAct, InDownAct, InActiveUp, InActiveDown;
  //bool OutUpAct, OutDownAct;

public:
  int X, Y;

  String Name;
  String NameOutUp;
  String NameOutDown;

  int  IDNodeOutUp, IDNodeOutDown;

  int  InternalID;
  bool DeleteFlag;
  bool TagFlag;

  void Send(void);
  void Receive(bool pAct);
  void Work(void);

  void SetInUp(int pPin/*, TNode *pID*/);
  void SetInDown(int pPin/*, TNode *pID*/);
  void SetOutUp(int pPin, TNode *pID);
  void SetOutDown(int pPin, TNode *pID);

  void Reset(void);
  
  int GetPin_InUp(void);
  int GetPin_InDown(void);
  int GetPin_OutUp(void);
  int GetPin_OutDown(void);

  int  GetType(void);
  void SetType(int pType);

  bool GetActive(void);
  int  GetInOutType(void);

  TNode * GetNodeOutUp(void);
  TNode * GetNodeOutDown(void);

  TNode(int pIntID, int pX, int pY, int pType, String pName);
};

class Tf_CPUNode : public TForm
{
__published:	// Composants gérés par l'EDI
    TPanel *p_Area;
    TTimer *t_Work;
    TPanel *p_zoom;
    TLabel *l_gridZoom;
    TTrackBar *tb_Size;
    TXPManifest *XPManifest;
    TTimer *t_Draw;
	TTimer *t_DrawMulti1;
	TTimer *t_DrawMulti2;
	TTimer *t_DrawMulti3;
   TStatusBar *sb_Main;
   THeaderControl *HeaderControl1;
   TButton *b_Or;
   TButton *b_And;
   TButton *b_NOr;
   TButton *b_NAnd;
   TButton *b_XOr;
   TButton *b_Not;
   TPanel *p_DrawCmp;
   TButton *b_Init;
   TButton *b_Start;
   TButton *b_Step;
   TButton *b_Save;
   TButton *b_Reset;
   TCheckBox *cb_ActiveDraw;
   TCheckBox *cb_QuickEdit;
   TCheckBox *cb_ColorLine;
   TPanel *Panel1;
   TLabel *l_Speed;
   TTrackBar *tb_Speed;
   TSaveDialog *NodeSaveDialog;
   TOpenDialog *NodeOpenDialog;
   TXMLDocument *XMLDoc;
   TProgressBar *pgLoading;
    void __fastcall b_InitClick(TObject *Sender);
    void __fastcall b_StartClick(TObject *Sender);
    void __fastcall t_WorkTimer(TObject *Sender);
    void __fastcall b_StepClick(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall b_SaveClick(TObject *Sender);
    void __fastcall b_OrClick(TObject *Sender);
    void __fastcall tb_SizeChange(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
    void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall t_DrawTimer(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall t_DrawMulti1Timer(TObject *Sender);
	void __fastcall t_DrawMulti2Timer(TObject *Sender);
	void __fastcall t_DrawMulti3Timer(TObject *Sender);
   void __fastcall b_ResetClick(TObject *Sender);
   void __fastcall cb_ColorLineClick(TObject *Sender);
   void __fastcall tb_SpeedChange(TObject *Sender);

private:	// Déclarations de l'utilisateur
    void __fastcall AppMessage(TMsg& PassedMsg, bool& Handled);

    TList* NodeList;
	TList* SelectList;
	//TList* FollowList;
	TNode *NodeSelect;

    int NodeCmp;
    int NodeType;

	bool ItsUpdated;
	int DrawCmpItem;
	int DrawCmpLine;
   int DrawTimerSpeed;

    int MouseDownX, MouseDownY;
    int OffSetX, OffSetY;
    int ObjSize, GridSize;

	void ReadInput(void);
	void WriteOutput(void);
	void CallDrawArea(void);
	void DrawArea(int NbDraw);
	void TagFollowList(TNode *NodeTag, int Depth, bool Sel);

public:		// Déclarations de l'utilisateur
    __fastcall Tf_CPUNode(TComponent* Owner);
    void UpdateNode(void);
    void ResetAllNode(void);
	bool NodeNameExists(String pName);
	void EmptyFollowList(void);
};

//---------------------------------------------------------------------------
extern PACKAGE Tf_CPUNode *f_CPUNode;
//---------------------------------------------------------------------------
#endif
