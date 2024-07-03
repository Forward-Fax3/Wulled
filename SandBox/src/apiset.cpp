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
	using namespace WLD;
	
	RendererAPI::API currentAPI = Renderer::GetAPI();
	static bool isOpenGL = currentAPI == RendererAPI::API::OpenGL;
	static bool isDx12 = currentAPI == RendererAPI::API::DirectX12;
	static bool isVulkan = currentAPI == RendererAPI::API::Vulkan;

	ImGui::Begin("Set API");
	ImGui::Text("Set API");
	ImGui::Checkbox("OpenGL", &isOpenGL);
//	ImGui::Checkbox("DirectX12", &isDx12);
	ImGui::Checkbox("Vulkan", &isVulkan);
	ImGui::Text("More API's to come");

	bool submit = ImGui::Button("submit");
	ImGui::End();

	if (currentAPI != RendererAPI::API::OpenGL && isOpenGL)
	{
		currentAPI = RendererAPI::API::OpenGL;
		Renderer::SetNextAPI(currentAPI);
		isDx12 = false;
		isVulkan = false;
	}
	else if (currentAPI != RendererAPI::API::DirectX12 && isDx12)
	{
		currentAPI = RendererAPI::API::DirectX12;
		Renderer::SetNextAPI(currentAPI);
		isOpenGL = false;
		isVulkan = false;
	}
	else if (currentAPI != RendererAPI::API::Vulkan && isVulkan)
	{
		currentAPI = RendererAPI::API::Vulkan;
		Renderer::SetNextAPI(currentAPI);
		isOpenGL = false;
		isDx12 = false;
	}

	if (submit)
	{
		bool* run = WLD::Application::Get().GetRun();
		run[3] = true;
	}
}

SetAPI::SetAPI(bool* run)
	: Application(run)
{
	PushLayer(CreateMemory(SetAPILayer, "set api"));
}

SetAPI::~SetAPI()
{
}

