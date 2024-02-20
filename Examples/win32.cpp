
#include <GLExtension.h>
#include <assert.h>


LRESULT WINAPI WndProc(HWND, UINT, WPARAM,LPARAM);

int main(int args, char* argv[])
{
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(wc);
    wc.lpszClassName = TEXT("Example");
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(DKGRAY_BRUSH));
    
    ATOM res =  RegisterClassEx(&wc);


    HWND hwnd = CreateWindowEx(NULL, wc.lpszClassName, TEXT("Example"), 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, 600, 300, 700, 500, nullptr, (HMENU)0, wc.hInstance, 0);

    HGLRC rc = GL::CreateGLContext(hwnd);
    HDC dc = GetDC(hwnd);

    LPCSTR vertCode = R"(
    #version 460 core

    out gl_PerVertex{
        vec4 gl_Position;
    }
    void main(void){
        gl_Position = vec4(0,0,0.5,1);
    }
    )";

    LPCSTR pixelCode = R"(
    #version 460 core
    out vec4 color;
    void main(void){
        color = vec4(0.7,0.7,0.8,1);
    }
    )";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertCode, NULL);
    glCompileShader(vs);

    GLuint ps = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(ps, 1, &pixelCode, NULL);
    glCompileShader(ps);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, ps);

    glLinkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(ps);

    GLuint vao{};
    glCreateVertexArrays(1, &vao);


    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
            PostQuitMessage(0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f,0.3f,0.4f,1.f);

        glBindVertexArray(vao);
        glUseProgram(prog);
        glPointSize(50.f);
        glDrawArrays(GL_POINTS, 0, 1);

        SwapBuffers(dc);
    }

    glDeleteBuffers(1, &vao);
    glDeleteProgram(prog);
    GL::ReleaseContext(hwnd, rc, dc); 
    DestroyWindow(hwnd);   

    return 0;
};

LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp,LPARAM lp){
    return DefWindowProc(hwnd, msg, wp, lp);
}

