#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../FrameWork/header/FrameWork.hpp"

#include "../header/Entry.hpp"

int main()
{
    
    if (glfwInit() == GL_FALSE)
	{
		std::cerr << "glfw を初期化出来ません。" << std::endl;
	}

    std::shared_ptr<FrameWork::Window> window = std::make_shared<FrameWork::Window>(glm::ivec2(840,680),"sample");
                            
    FrameWork::SetCurrentWindowContext(window);
    
    if (glewInit() != GLEW_OK)
	{
		std::cerr << "glew を初期化出来ません。" << std::endl;
	}

    FrameWork::Init();  //フレームワークを初期化

    FrameWork::SetCurrentCamera(std::make_shared<FrameWork::Camera>());   //カメラ初期化

    std::shared_ptr<Entry> entry = std::make_shared<Entry>();

    while(*FrameWork::GetCurrentWindow())
    {
        FrameWork::GetCurrentCamera()->ClearBuffer();


        entry->Update();
        entry->Renderer();



        FrameWork::GetCurrentCamera()->RendererBuffer();
        FrameWork::GetCurrentWindow()->SwapBuffer();
    }



    return 0;
}