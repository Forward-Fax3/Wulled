#include "apiset.h"


SetAPILayer::SetAPILayer(std::string name)
	: Layer(name)
{
}

SetAPILayer::~SetAPILayer()
{
}

void SetAPILayer::OnImGuiDraw()
{
	using namespace WLD::Graphics::Renderer;
	
	RendererAPI::API currentAPI = Renderer::GetAPI();
	static bool isOpenGL = currentAPI == RendererAPI::API::OpenGL;
	static bool isDx12 = currentAPI == RendererAPI::API::DirectX12;

	ImGui::Begin("Set API");
	ImGui::Text("Set API");
	ImGui::Checkbox("OpenGL", &isOpenGL);
	ImGui::Checkbox("DirectX12", &isDx12);

	bool submit = ImGui::Button("submit");
	ImGui::End();

	if (currentAPI != RendererAPI::API::OpenGL && isOpenGL)
	{
		currentAPI = RendererAPI::API::OpenGL;
		Renderer::SetNextAPI(currentAPI);
		isDx12 = false;
	}
	else if (currentAPI != RendererAPI::API::DirectX12 && isDx12)
	{
		currentAPI = RendererAPI::API::DirectX12;
		Renderer::SetNextAPI(currentAPI);
		isOpenGL = false;
	}

	if (submit)
	{
		bool* run = WLD::Application::Get().GetRun();
		run[0] = false;
		run[1] = true;
		run[2] = true;
	}
}

SetAPI::SetAPI(bool* run)
	: Application(run)
{
	PushLayer(new SetAPILayer("set api"));
}

SetAPI::~SetAPI()
{
}

