#define MAIN_FORM LinkageSimulator
#define PROJECT_NAME ps07LinkageSimulator
#include "LinkEditor.h"
#include "LinkageSimulator.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(cli::array <String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PROJECT_NAME::MAIN_FORM form;
	Application::Run(% form);
	return 0;
}

#undef MAIN_FORM
#undef PROJECT_NAME

void ps07LinkageSimulator::LinkageSimulator::showLinkEditor(Link* aLink)
{
	using namespace ps05LinkEditor;
	if (theEditor == nullptr || !theEditor->Visible)
		theEditor = gcnew LinkEditor;

	//theEditor->ShowDialog(); // if we want to "freeze" LinkageSimulator
	theEditor->Show();   // if we want to have both forms functionable

	if (theEditor->Visible) {
		int temp = 1;
		if (aLink == nullptr)
			aLink = new Link();
		((LinkEditor^)theEditor)->setLink(aLink);
		((LinkEditor^)theEditor)->setSimulator(this);
		theEditor->Refresh();
	}

}