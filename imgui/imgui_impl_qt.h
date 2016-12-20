// ImGui Qt binding with OpenGL
// https://github.com/ocornut/imgui

class viewerWidget;
bool        ImGui_ImplQt_Init(viewerWidget* viewer, bool install_callbacks);
void        ImGui_ImplQt_Shutdown();
void        ImGui_ImplQt_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
void        ImGui_ImplQt_InvalidateDeviceObjects();
bool        ImGui_ImplQt_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
void        ImGui_ImplQt_MouseButtonCallback(viewerWidget* window, int button, int action, int mods);
void        ImGui_ImplQt_ScrollCallback(viewerWidget* window, double xoffset, double yoffset);
void        ImGui_ImplQt_KeyCallback(viewerWidget* window, int key, int scancode, int action, int mods);
void        ImGui_ImplQt_CharCallback(viewerWidget* window, unsigned int c);
