#pragma once
#include "Engine/src/core/Log.h"
#include "Engine/src/core/application.h"
#include "Engine/src/core/WLDMem.h"

#include "Engine/src/core/layers/Layer.h"

#include "Engine/src/core/ImGui/ImGuiLayer.h"

#include "Engine/src/core/Input.h"
#include "Engine/src/core/KeyCodes.h"
#include "Engine/src/core/MouseButtonCodes.h"

// Renderer
#include "Engine/src/core/graphics/Renderer/Renderer.h"
#include "Engine/src/core/graphics/Renderer/RenderCommand.h"

#include "Engine/src/core/graphics/Renderer/Buffer.h"
#include "Engine/src/core/graphics/Renderer/Shader.h"
#include "Engine/src/core/graphics/Renderer/texture.h"
#include "Engine/src/core/graphics/Renderer/VertexArray.h"

#include "Engine/src/core/graphics/camera/PerspectiveCamera.h"

// Entry Point
#ifdef ENTRY_POINT
#include "Engine/src/core/EntryPoint.h"
#endif
