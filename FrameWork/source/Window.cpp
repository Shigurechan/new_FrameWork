
#include <iostream>
#include <limits.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdio.h>
#include <wchar.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include "../header/Window.hpp"
#include "../header/Window_Use.hpp"
#include "../header/Camera.hpp"

std::shared_ptr<FrameWork::Window> FrameWork::currentWindow = nullptr;

// ##################################### クライアントコンテキスト　設定 ##################################### 
void FrameWork::SetCurrentWindow(std::shared_ptr<FrameWork::Window> w)
{
	FrameWork::currentWindow = w;
}

// ##################################### クライアントコンテキスト　取得 ##################################### 
std::shared_ptr<FrameWork::Window> FrameWork::GetCurrentWindow()
{
	return FrameWork::currentWindow;
}



// ##################################### クライアントコンテキスト　設定 ##################################### 
void FrameWork::SetCurrentWindowContext(std::shared_ptr<FrameWork::Window> win)
{
	FrameWork::currentWindow = win;
	glfwMakeContextCurrent(currentWindow->getContext());
}

// #####################################　キー入力 ##################################### 
int FrameWork::GetKeyInput(int key)
{
	return FrameWork::currentWindow->getKeyInput(key);	
}

// ##################################### コンストラクタ ##################################### 
FrameWork::Window::Window(glm::ivec2 s,std::string t)
{
	size = s;       //サイズ
	title = t;      //タイトル

    window = glfwCreateWindow(s.x, s.y, t.c_str(),NULL, NULL);

	//変数を初期化
	std::fill(std::begin(keyBoard), std::end(keyBoard), 0);			//キーボード入力配列を初期化
	std::fill(std::begin(key), std::end(key), 0);					//キーボード入力配列を初期化

	//コンテキストの作成に失敗
	if (window == NULL)
	{
		std::cerr << "ウインドウ生成失敗" << std::endl;
		exit(1);	//異常終了
	}
	
	atexit(glfwTerminate);	//プログラム終了時の処理を登録

    //デルタタイム
    deltaTime = 0.0f;
    prevDeltaTime = 0.0f;


	// OpenGL Verison 3.3 Core Profile　を選択する	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);				//アライメント
	glEnable(GL_TEXTURE_2D);							//テクスチャを有効
	glEnable(GL_ALPHA_TEST);							//アルファテスト
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//ブレンドタイプ
	glEnable(GL_BLEND);									//ブレンド有効
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);				//半透明
	glEnable(GL_CULL_FACE);					   			//カリング　有効
	glCullFace(GL_BACK);					   			//裏面を無効
	glEnable(GL_MULTISAMPLE);                           //マルチサンプル

	//イベント処理
	glfwSetWindowUserPointer(window, this);					//このインスタンスのthis
	glfwSetWindowSizeCallback(window, Resize_Event);		//ウインドウサイズ
	glfwSetKeyCallback(window, KeyInput_Event);				//キー入力

	atexit(glfwTerminate); //プログラム終了時の処理を登録
}

// ##################################### イベント処理 キー入力 ##################################### 
void FrameWork::Window::KeyInput_Event(GLFWwindow* win, int key, int scanCode, int action, int mods)
{
	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (action == GLFW_PRESS)
	{
		instance->key[key] += 1;
	}
	else if (action == GLFW_RELEASE)
	{
		instance->key[key] = 0;
	}
}

// ##################################### イベント処理　画面サイズ変更 ##################################### 
void FrameWork::Window::Resize_Event(GLFWwindow* const win, int width, int height)
{
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(win, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	Window* const instance = (Window*)glfwGetWindowUserPointer(win);

	if (instance != NULL)
	{
		instance->size.x = (GLfloat)fbWidth;
		instance->size.y = (GLfloat)fbHeight;		
	}
}

// ##################################### ウインドウサイズを取得 ##################################### 
const glm::ivec2 FrameWork::Window::getSize() const
{
	return size;
}

// ##################################### キー入力 ##################################### 
short int FrameWork::Window::getKeyInput(short int code)
{	
	return key[code];
}


// ##################################### bool 演算子 ##################################### 
FrameWork::Window::operator bool()
{

	glfwPollEvents();	//イベントを取り出す

	
#ifndef DEBUG
	//エラー処理
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{

		std::cerr <<"\n"<< "	glGetError(): 0x" << std::hex << err << std::endl;
	}
#endif
	
	//ESCキーで終了
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1)
	{
		return false;
	}

	//ウインドウを閉じる必要があれば false
	if (glfwWindowShouldClose(window) != 0)
	{
		return false;
	}
	else 
	{
		return true;
	}
}

// ##################################### ダブルバッファリング ##################################### 
void FrameWork::Window::SwapBuffer()
{	
    deltaTime = glfwGetTime() - prevDeltaTime;
    prevDeltaTime = glfwGetTime();

	glfwSwapBuffers(window);
}

// #####################################  デルタタイム ##################################### 
float FrameWork::Window::getDeltaTime()
{
    return deltaTime;
}

// ##################################### コンテキストを取得 ##################################### 
GLFWwindow* FrameWork::Window::getContext()
{
    return window;
}

// ##################################### デストラクタ ##################################### 
FrameWork::Window::~Window()
{
	glfwDestroyWindow(window);
}

