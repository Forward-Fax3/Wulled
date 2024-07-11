#pragma once
#include "Engine/src/Core/Log.h"
#include "Engine/src/Core/Application.h"
#include "Engine/src/Core/WLDMem.h"

#include "Engine/src/Core/Layers/Layer.h"

#include "Engine/src/Core/ImGui/ImGuiLayer.h"

#include "Engine/src/Core/Input.h"
#include "Engine/src/Core/KeyCodes.h"
#include "Engine/src/Core/MouseButtonCodes.h"

// Renderer
#include "Engine/src/Core/Graphics/Renderer/Renderer.h"
#include "Engine/src/Core/Graphics/Renderer/RenderCommand.h"

#include "Engine/src/Core/Graphics/Renderer/Buffer.h"
#include "Engine/src/Core/Graphics/Renderer/Shader.h"
#include "Engine/src/Core/Graphics/Renderer/Texture.h"
#include "Engine/src/Core/Graphics/Renderer/VertexArray.h"

#include "Engine/src/Platform/OpenGL/OpenGLShader.h"

#include "Engine/src/Core/Graphics/Camera/PerspectiveCamera.h"

// Entry Point
#ifdef ENTRY_POINT
#include "Engine/src/Core/EntryPoint.h"
#endif
