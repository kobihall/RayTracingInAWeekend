#include <iostream>
#include <chrono>

#include "Application.h"
#include "Image.h"

#include "color.h"
#include "vec3.h"

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
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastRenderTime);
		if(ImGui::Button("Render")) {
			Render();
		}
		ImGui::End();

		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		if(m_Image)
			ImGui::Image(m_Image->GetDescriptorSet(), {(float)m_Image->GetWidth(), (float)m_Image->GetHeight()});

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

		for(uint32_t j = 0; j < m_ViewportHeight; ++j){
			for(uint32_t i = 0; i < m_ViewportWidth; ++i){
				color pixel_color(double(i) / (m_ViewportWidth-1), double(j) / (m_ViewportHeight-1), 0.25);
				m_ImageData[(m_ViewportHeight - 1 - j)*m_ViewportWidth + i] = write_color(pixel_color);
			}
		}

		m_Image->SetData(m_ImageData);

		m_LastRenderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f;
	}
private:
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	std::shared_ptr<Image> m_Image;

	uint32_t* m_ImageData = nullptr;

	float m_LastRenderTime = 0.0f;
};

Application* CreateApplication(int argc, char** argv)
{
	AppSettings spec;
	spec.Name = "Raytracing Application";
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