#include "ImguiHandler.h"

#include "Resource/imgui.h"
#include "Resource/imgui_impl_win32.h"
#include "Resource/imgui_impl_dx11.h"

ImguiHandler::ImguiHandler() : m_showWindow(true) {
    // ============================== Setup ImGui context ==============================
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

ImguiHandler::~ImguiHandler() {
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}