// ImGui Qt binding with OpenGL
// https://github.com/ocornut/imgui

#include "imgui.h"
#include "imgui_impl_qt.h"
#include "GL/gl.h"
#include "GL/freeglut.h"
#include "viewerwidget.h"
// Qt

// Data
static double       g_Time = 0.0f;
static bool         g_MousePressed[3] = { false, false, false };
static float        g_MouseWheel = 0.0f;
static GLuint       g_FontTexture = 0;
viewerWidget* cv;
// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
static void ImGui_ImplQt_RenderDrawLists(ImDrawList** const cmd_lists, int cmd_lists_count)
{
    if (cmd_lists_count == 0)
        return;

    // We are using the OpenGL fixed pipeline to make the example code simpler to read!
    // A probable faster way to render would be to collate all vertices from all cmd_lists into a single vertex buffer.
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers.
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context

    // Setup orthographic projection matrix
    const float width = ImGui::GetIO().DisplaySize.x;
    const float height = ImGui::GetIO().DisplaySize.y;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    for (int n = 0; n < cmd_lists_count; n++)
    {
        const ImDrawList* cmd_list = cmd_lists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->vtx_buffer.front();
        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

        int vtx_offset = 0;
        for (size_t cmd_i = 0; cmd_i < cmd_list->commands.size(); cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->commands[cmd_i];
            if (pcmd->user_callback)
            {
                pcmd->user_callback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->texture_id);
                glScissor((int)pcmd->clip_rect.x, (int)(height - pcmd->clip_rect.w), (int)(pcmd->clip_rect.z - pcmd->clip_rect.x), (int)(pcmd->clip_rect.w - pcmd->clip_rect.y));
                glDrawArrays(GL_TRIANGLES, vtx_offset, pcmd->vtx_count);
            }
            vtx_offset += pcmd->vtx_count;
        }
    }
    #undef OFFSETOF

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

static const char* ImGui_ImplQt_GetClipboardText()
{
    return "";
}

static void ImGui_ImplQt_SetClipboardText(const char* text)
{

}

void ImGui_ImplQt_MouseButtonCallback(viewerWidget*, int button, int action, int /*mods*/)
{
//    if (action == Qt_PRESS && button >= 0 && button < 3)
//        g_MousePressed[button] = true;
}

void ImGui_ImplQt_ScrollCallback(viewerWidget*, double /*xoffset*/, double yoffset)
{
//    g_MouseWheel += (float)yoffset; // Use fractional mouse wheel, 1.0 unit 5 lines.
}

void ImGui_ImplQt_KeyCallback(viewerWidget*, int key, int, int action, int mods)
{
//    ImGuiIO& io = ImGui::GetIO();
//    if (action == Qt_PRESS)
//        io.KeysDown[key] = true;
//    if (action == Qt_RELEASE)
//        io.KeysDown[key] = false;

//    (void)mods; // Modifiers are not reliable across systems
//    io.KeyCtrl = io.KeysDown[Qt_KEY_LEFT_CONTROL] || io.KeysDown[Qt_KEY_RIGHT_CONTROL];
//    io.KeyShift = io.KeysDown[Qt_KEY_LEFT_SHIFT] || io.KeysDown[Qt_KEY_RIGHT_SHIFT];
//    io.KeyAlt = io.KeysDown[Qt_KEY_LEFT_ALT] || io.KeysDown[Qt_KEY_RIGHT_ALT];
}

void ImGui_ImplQt_CharCallback(viewerWidget*, unsigned int c)
{
//    ImGuiIO& io = ImGui::GetIO();
//    if (c > 0 && c < 0x10000)
//        io.AddInputCharacter((unsigned short)c);
}

bool ImGui_ImplQt_CreateDeviceObjects()
{
    ImGuiIO& io = ImGui::GetIO();

    // Build texture
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

    // Create texture
    glGenTextures(1, &g_FontTexture);
    glBindTexture(GL_TEXTURE_2D, g_FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

    return true;
}

void    ImGui_ImplQt_InvalidateDeviceObjects()
{
    if (g_FontTexture)
    {
        glDeleteTextures(1, &g_FontTexture);
        ImGui::GetIO().Fonts->TexID = 0;
        g_FontTexture = 0;
    }
}

bool    ImGui_ImplQt_Init(viewerWidget* viewer, bool install_callbacks)
{

    cv=viewer;
    ImGuiIO& io = ImGui::GetIO();
//    io.KeyMap[ImGuiKey_Tab] = Qt_KEY_TAB;                 // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
//    io.KeyMap[ImGuiKey_LeftArrow] = Qt_KEY_LEFT;
//    io.KeyMap[ImGuiKey_RightArrow] = Qt_KEY_RIGHT;
//    io.KeyMap[ImGuiKey_UpArrow] = Qt_KEY_UP;
//    io.KeyMap[ImGuiKey_DownArrow] = Qt_KEY_DOWN;
//    io.KeyMap[ImGuiKey_Home] = Qt_KEY_HOME;
//    io.KeyMap[ImGuiKey_End] = Qt_KEY_END;
//    io.KeyMap[ImGuiKey_Delete] = Qt_KEY_DELETE;
//    io.KeyMap[ImGuiKey_Backspace] = Qt_KEY_BACKSPACE;
//    io.KeyMap[ImGuiKey_Enter] = Qt_KEY_ENTER;
//    io.KeyMap[ImGuiKey_Escape] = Qt_KEY_ESCAPE;
//    io.KeyMap[ImGuiKey_A] = Qt_KEY_A;
//    io.KeyMap[ImGuiKey_C] = Qt_KEY_C;
//    io.KeyMap[ImGuiKey_V] = Qt_KEY_V;
//    io.KeyMap[ImGuiKey_X] = Qt_KEY_X;
//    io.KeyMap[ImGuiKey_Y] = Qt_KEY_Y;
//    io.KeyMap[ImGuiKey_Z] = Qt_KEY_Z;

    io.RenderDrawListsFn = ImGui_ImplQt_RenderDrawLists;
    io.SetClipboardTextFn = ImGui_ImplQt_SetClipboardText;
    io.GetClipboardTextFn = ImGui_ImplQt_GetClipboardText;

//    if (install_callbacks)
//    {
//        QtSetMouseButtonCallback(window, ImGui_ImplQt_MouseButtonCallback);
//        QtSetScrollCallback(window, ImGui_ImplQt_ScrollCallback);
//        QtSetKeyCallback(window, ImGui_ImplQt_KeyCallback);
//        QtSetCharCallback(window, ImGui_ImplQt_CharCallback);
//    }

    return true;
}

void ImGui_ImplQt_Shutdown()
{
//    ImGui_ImplQt_InvalidateDeviceObjects();
//    ImGui::Shutdown();
}

void ImGui_ImplQt_NewFrame()
{
    if (!g_FontTexture)
        ImGui_ImplQt_CreateDeviceObjects();

    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    display_w = cv->width();
    display_h = cv->height();
    io.DisplaySize = ImVec2((float)display_w, (float)display_h);

    // Setup time step
    double current_time =  0;//QtGetTime();
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f/60.0f);
    g_Time = current_time;

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from Qt callbacks polled in QtPollEvents())
//    if (QtGetWindowAttrib(g_Window, Qt_FOCUSED))
//    {
//        double mouse_x, mouse_y;
//        QtGetCursorPos(g_Window, &mouse_x, &mouse_y);
//        mouse_x *= (float)display_w / w;                        // Convert mouse coordinates to pixels
//        mouse_y *= (float)display_h / h;
//        io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
//    }
//    else
//    {
//        io.MousePos = ImVec2(-1,-1);
//    }

//    for (int i = 0; i < 3; i++)
//    {
//        io.MouseDown[i] = g_MousePressed[i] || QtGetMouseButton(g_Window, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
//        g_MousePressed[i] = false;
//    }

    io.MouseWheel = g_MouseWheel;
    g_MouseWheel = 0.0f;

    // Hide/show hardware mouse cursor
//    QtSetInputMode(g_Window, Qt_CURSOR, io.MouseDrawCursor ? Qt_CURSOR_HIDDEN : Qt_CURSOR_NORMAL);

    // Start the frame
    ImGui::NewFrame();
}
