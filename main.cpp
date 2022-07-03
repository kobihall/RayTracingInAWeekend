#include <iostream>
#include <chrono>

#include "Application.h"
#include "Image.h"
#include "Renderer.h"


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
	ExampleLayer(){
		m_renderer = Renderer();
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastRenderTime);
		if(ImGui::Button("Render")) {
			Render();
		}
		ImGui::Checkbox("Render every frame", &m_everyFrame);
		if(m_everyFrame){
			Render();
		}
		ImGui::Text("Viewport width: %d", m_ViewportWidth);
		ImGui::Text("Viewport height: %d", m_ViewportHeight);
		ImGui::Checkbox("MSAA", &m_renderer.settings.MSAA);
		if(m_renderer.settings.MSAA){
			ImGui::SliderInt("# of samples", &m_renderer.settings.msaaSamples, 1, 100);
		}
		ImGui::End();

		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		if(m_Image)
			ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()}, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}

	void Render()
	{
		auto m_Start = std::chrono::high_resolution_clock::now();
		
		if(!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight()) {
			m_Image = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
		}

		m_renderer.render(m_ImageData, m_ViewportWidth, m_ViewportHeight);

		m_Image->SetData(m_ImageData);

		m_LastRenderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f;
	}
private:
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	std::shared_ptr<Image> m_Image;

	Renderer m_renderer;

	uint32_t* m_ImageData = nullptr;

	float m_LastRenderTime = 0.0f;
	bool m_everyFrame = false;
};

Application* CreateApplication(int argc, char** argv)
{
	AppSettings spec;
	spec.Name = "Raytracing Application";
    spec.Width = 456;
    spec.Height = 324;

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