#pragma once
#include "Engine/src/Core/Log.h"
#include "Engine/src/Core/application.h"
#include "Engine/src/core/WLDMem.h"

#include "Engine/src/Core/Layers/Layer.h"

#include "Engine/src/Core/ImGui/ImGuiLayer.h"

#include "Engine/src/core/Input.h"
#include "Engine/src/core/KeyCodes.h"
#include "Engine/src/core/MouseButtonCodes.h"

// -------------------- Renderer ------------------------
#include "Engine/src/core/graphics/renderer/renderer.h"
#include "Engine/src/core/graphics/Renderer/RenderCommand.h"

#include "Engine/src/core/graphics/renderer/Buffer.h"
#include "Engine/src/core/graphics/renderer/Shader.h"
#include "Engine/src/core/graphics/renderer/Texture.h"
#include "Engine/src/core/graphics/renderer/VertexArray.h"

#include "Engine/src/platform/OpenGL/Shader.h"

#include "Engine/src/core/graphics/camera/PerspectiveCamera.h"
//-------------------------------------------------------

//--------------------- Entry Point ---------------------
#ifdef ENTRY_FILE
#include "Engine/src/Core/EntryPoint.h"
#endif
//-------------------------------------------------------