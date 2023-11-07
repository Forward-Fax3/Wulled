#include "app.h"
#include "Engine/src/core/Log.h"

#include <iostream>

#include "Engine/src/core/renderer/renderer.h"
#include "Engine/src/core/renderer/Shader.h"

#include "glm/glm.hpp"
#include "Engine/src/core/Renderer/PerspectiveCamera.h"

namespace std
{
	pair<double, double> operator-(const pair<double, double>& lhs, const pair<double, double>& rhs)
	{
		return { lhs.first - rhs.first, lhs.second - rhs.second };
	}

	pair<double, double> operator+(const pair<double, double>& lhs, const pair<double, double>& rhs)
	{
		return { lhs.first + rhs.first, lhs.second + rhs.second };
	}
}


class ExampleLayer : public WLD::Layer
{
public:
	ExampleLayer()
		: Layer("Render")
	{
		// multicolour squire data
		float multiColourVertices[] =
		{
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
													   
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, -0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};

		uint32_t multiColourIndices[] =
		{
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4,

			2, 1, 7,
			1, 5, 7,
			5, 6, 7,
			6, 2, 7
		};

		std::string multiColourVertexSrc =
		R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;

			out vec4 v_Colour;
			uniform mat4 u_MVP;
			
			void main()
			{
				v_Colour = a_Colour;
				gl_Position = u_MVP * vec4(a_Position, 1.0);
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

		WLD::Window& window = WLD::Application::Get().GetWindow();
		m_Camera.reset(new WLD::PerspectiveCamera(45.0f, static_cast<float>(window.GetHeight()), static_cast<float>(window.GetWidth()), 0.001f, 100.0f));
	}

	void OnUpdate() override
	{
		WLD::RenderCommand::Clear();
		WLD::Renderer::BeginScene(m_Camera);

		WLD::Renderer::Submit(m_BackgroundVA, m_BackgroundShader);

		m_Camera->setPosition(getMovement());
		std::pair<double, double> rotation = getRotation();
		m_Camera->setRotation({ rotation.first / 2.0, rotation.second / 2.0, 0.0});
		glm::mat4 mvp = m_Camera->getProjection();

		WLD::Renderer::Submit(m_MultiColourVertexArray, m_MultiColourShader);

		WLD::Renderer::EndScene();
	}

	glm::vec3 getMovement()
	{
		static float x = 0.0f, y = 0.0f, z = 0.0f;

		float deltaTime = static_cast<float>(WLD::Application::Get().GetDeltaTime());

		if (WLD::Input::IsKeyPressed(WLD_KEY_DOWN) || WLD::Input::IsKeyPressed(WLD_KEY_S))		z += 1.0f * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_UP) || WLD::Input::IsKeyPressed(WLD_KEY_W))		z -= 1.0f * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_RIGHT) || WLD::Input::IsKeyPressed(WLD_KEY_D))		x += 1.0f * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_LEFT) || WLD::Input::IsKeyPressed(WLD_KEY_A))		x -= 1.0f * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_PAGE_UP) || WLD::Input::IsKeyPressed(WLD_KEY_R))	y += 1.0f * deltaTime;
		if (WLD::Input::IsKeyPressed(WLD_KEY_PAGE_DOWN) || WLD::Input::IsKeyPressed(WLD_KEY_F))	y -= 1.0f * deltaTime;

		return { x, y, z };
	}

	std::pair<double, double> getRotation()
	{
		std::pair<double, double> posNow = WLD::Input::GetMousePosition();
		static std::pair<double, double> lastPos = posNow;
		static std::pair<double, double> total = { 0.0, 0.0 };
		std::pair<double, double> delta = posNow - lastPos;

		if (WLD::Input::IsMousButtonPressed(WLD_MOUSE_BUTTON_RIGHT) || WLD::Input::IsKeyPressed(WLD_KEY_LEFT_CONTROL))
			total = total + delta;

		if (total.first < -360.0)       total.first  += 720.0;
		else if (total.first > 360.0)   total.first  -= 720.0;
		if (total.second < -360.0)      total.second += 720.0;
		else if (total.second > 360.0)  total.second -= 720.0;

		lastPos = posNow;
		return total;
	}

private:
	std::shared_ptr<WLD::Shader> m_MultiColourShader;
	std::shared_ptr<WLD::VertexArray> m_MultiColourVertexArray;

	std::shared_ptr<WLD::Shader> m_BackgroundShader;
	std::shared_ptr<WLD::VertexArray> m_BackgroundVA;
	std::shared_ptr<WLD::PerspectiveCamera> m_Camera;
};

class SandBox : public WLD::Application
{
public:
	SandBox(bool* run)
		: Application(run)
	{
		std::cout << "sand box created" << std::endl;
		PushLayer(new ExampleLayer);
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
