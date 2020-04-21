#pragma once
ref class FlickerLessPanel : public System::Windows::Forms::Panel
{

public:
	FlickerLessPanel() 
	{
		// For some weird reason, the "DoubleBuffered" parameter is protected instead
		// of public. Thus, the only way to change it is to create a subclass of the 
		// Panel class (FlickerLessPanel) and then change the parameter in the 
		// constructor of the subclass. Then, in the Form class member function 
		// InitComponents(), change the panel type from "Panel" to "FlickerlessPanel"

		this->DoubleBuffered = true;

		// Note: This approach makes it impossible for the Visual Studio IDE to 
		// generate the Design View of the form. Thus, you'll need to change the 
		// panel type back to regular "Panel" in order to view and graphically
		// edit the form.
	}
};
