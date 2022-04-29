#ifndef ___WINDOW_USE_HPP_
#define ___WINDOW_USE_HPP_

#include "Window.hpp"
namespace FrameWork
{
//    class Window;

    void SetCurrentWindow(std::shared_ptr<FrameWork::Window> c);
    std::shared_ptr<FrameWork::Window> GetCurrentWindow();

    void SetCurrentWindowContext(std::shared_ptr<FrameWork::Window> win); 	//クライアントコンテキスト　設定

    int GetKeyInput(int key);												//キー入力
}


#endif
