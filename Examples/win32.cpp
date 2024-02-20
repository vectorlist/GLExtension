
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
    glEnable(GL_PROGRAM_POINT_SIZE);

    //# colum major
    //      | col0 col1 col2 col3
    // row0 |  0    4    8   12
    // row1 |  1    5    9   13
    // row2 |  2    6   10   14
    // row3 |  3    7   11   15

    //# row major
    //      | col0 col1 col2 col3
    // row0 |  0    1    2    3
    // row1 |  4    5    6    7
    // row2 |  8    9   10   11
    // row3 | 12   13   14   15

    //mat4 = {col0, col1, col2, col3}
    //mat4 = { vec4(0,1,2,3), vec4(4,5,6,7),...}
    

    LPCSTR vertCode = R"(
    #version 460 core

    out gl_PerVertex
    {
        vec4 gl_Position;
        float gl_PointSize;
    };

    void main(void){
        const vec3 vtx[] = {
            vec3(-0.5,0.2,0.5),
            vec3(0.0,0.4,0.5),
            vec3(0.5,0.6,0.5)
        };

        mat4 mat = {
            vec4(1,0,0,0),
            vec4(0,1,0,0),
            vec4(0,0,1,0),
            vec4(0,0,0,1)
        };

        gl_Position = mat * vec4(vtx[gl_VertexID],1);
        gl_PointSize = 40;
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
        //glPointSize(50.f);
        glDrawArrays(GL_POINTS, 0, 3);

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

