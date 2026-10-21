//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Memory.cpp", f_Memory);
USEFORM("NodeCPU.cpp", f_CPUNode);
USEFORM("Ram.cpp", f_Ram);
USEFORM("GraphIO.cpp", f_GraphIO);
USEFORM("GraphEdit.cpp", f_GraphEdit);
USEFORM("ErrorList.cpp", f_ErrorList);
USEFORM("Terminal.cpp", f_Terminal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
      Application->Initialize();
      Application->CreateForm(__classid(Tf_CPUNode), &f_CPUNode);
      Application->CreateForm(__classid(Tf_GraphIO), &f_GraphIO);
      Application->CreateForm(__classid(Tf_GraphEdit), &f_GraphEdit);
      Application->CreateForm(__classid(Tf_Memory), &f_Memory);
      Application->CreateForm(__classid(Tf_Ram), &f_Ram);
      Application->CreateForm(__classid(Tf_ErrorList), &f_ErrorList);
      Application->CreateForm(__classid(Tf_Terminal), &f_Terminal);
      Application->Run();
   }
   catch (Exception &exception)
   {
      Application->ShowException(&exception);
   }
   catch (...)
   {
      try
      {
         throw Exception("");
      }
      catch (Exception &exception)
      {
         Application->ShowException(&exception);
      }
   }
   return 0;
}
//---------------------------------------------------------------------------
