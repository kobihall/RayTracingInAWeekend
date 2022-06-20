#include "Application.h"

extern Application* CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

int main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{
		Application* app = CreateApplication(argc, argv);
		app->Run();
		delete app;
	}

		return 0;
}

class ExampleLayer : public Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Application* CreateApplication(int argc, char** argv)
{
	AppSettings spec;
	spec.Name = "ImGui Example";
    spec.Width = 1600;
    spec.Height = 900;

	Application* app = new Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}