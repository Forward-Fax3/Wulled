#include "app.h"

#include <iostream>

#include "Engine/src/core/renderer/renderer.h"
#include "Engine/src/core/renderer/Shader.h"


class ExampleLayer : public WLD::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (WLD::Input::IsKeyPressed(WLD_KEY_TAB))
			LOG_TRACE("Tab key is pressed (poll)!");
	}

	void OnImGuiDraw() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}
};

class RenderLayer : public WLD::Layer
{
public:
	RenderLayer()
		: Layer("Render")
	{
		// multicolour squire data
		float multiColourVertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};

		uint32_t multiColourIndices[] =
		{
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4,
		};

		std::string multiColourVertexSrc =
			R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec4 v_Colour;
			
			void main()
			{
				v_Colour = a_Colour;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string multiColourFragmentSrc =
			R"(
			#version 460 core
			
			layout(location = 0) out vec4 colour;

			in vec4 v_Colour;
			
			void main()
			{
				colour = v_Colour;
			}
		)";

		// background data
		float backgroundVertices[] =
		{
			-1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f
		};

		uint32_t backgroundIndices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		std::string backgroundVertexSrc =
			R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string backgroundFragmentSrc =
			R"(
			#version 460 core
			
			layout(location = 0) out vec4 colour;
			
			void main()
			{
				colour = vec4(1.0f, 105.0f / 255.0f, 180.0f / 255.0f, 1.0f);
			}
		)";

		// Vertex buffer and index buffer creation
		std::shared_ptr<WLD::VertexBuffer> vertexBuffer;
		std::shared_ptr<WLD::IndexBuffer> indexBuffer;

		// multicolour squire creation
		m_MultiColourShader.reset(WLD::Shader::Create(multiColourVertexSrc, multiColourFragmentSrc));
		m_MultiColourVertexArray.reset(WLD::VertexArray::Create());

		vertexBuffer.reset(WLD::VertexBuffer::Create(multiColourVertices, sizeof(multiColourVertices)));
		indexBuffer.reset(WLD::IndexBuffer::Create(multiColourIndices, sizeof(multiColourIndices) / sizeof(uint32_t)));

		vertexBuffer->SetLayout
		({
			{ WLD::ShaderDataType::Float3, "a_Position" },
			{ WLD::ShaderDataType::Float4, "a_Colour" }
		});

		m_MultiColourVertexArray->AddVertexBuffer(vertexBuffer);
		m_MultiColourVertexArray->SetIndexBuffer(indexBuffer);

		// background creation
		m_BackgroundShader.reset(WLD::Shader::Create(backgroundVertexSrc, backgroundFragmentSrc));
		m_BackgroundVA.reset(WLD::VertexArray::Create());

		vertexBuffer.reset(WLD::VertexBuffer::Create(backgroundVertices, sizeof(backgroundVertices)));
		indexBuffer.reset(WLD::IndexBuffer::Create(backgroundIndices, sizeof(backgroundIndices) / sizeof(uint32_t)));

		vertexBuffer->SetLayout
		({
			{ WLD::ShaderDataType::Float3, "a_Position" }
		});

		m_BackgroundVA->AddVertexBuffer(vertexBuffer);
		m_BackgroundVA->SetIndexBuffer(indexBuffer);
	}

	void OnUpdate() override
	{

		WLD::RenderCommand::Clear();
		WLD::Renderer::BeginScene();

		m_BackgroundShader->Bind();
		WLD::Renderer::Submit(m_BackgroundVA);

		m_MultiColourShader->Bind();
		WLD::Renderer::Submit(m_MultiColourVertexArray);

		WLD::Renderer::EndScene();
	}

private:
	std::shared_ptr<WLD::Shader> m_MultiColourShader;
	std::shared_ptr<WLD::VertexArray> m_MultiColourVertexArray;

	std::shared_ptr<WLD::Shader> m_BackgroundShader;
	std::shared_ptr<WLD::VertexArray> m_BackgroundVA;
};

class ImGuiDemo : public WLD::Layer
{
public:
	ImGuiDemo()
		: Layer("ImGuiDemo")
	{
	}

	virtual void OnImGuiDraw() override
	{
		ImGui::ShowDemoWindow();
	}
};

class SandBox : public WLD::Application
{
public:
	SandBox(bool* run)
		: Application(run)
	{
		std::cout << "sand box created" << std::endl;
		PushLayer(new ExampleLayer);
		PushLayer(new RenderLayer);
		PushOverlay(new ImGuiDemo);
	}

	~SandBox()
	{
		std::cout << "sand box destroyed" << std::endl;
	}

private:

};

WLD::Application* WLD::CreateApplication(bool* run)
{
	return new SandBox(run);
}
