#ifndef ___WINDOW_HPP_
#define ___WINDOW_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.hpp"
/*#########################################################################
# Windowコンテキストクラス

説明

###########################################################################*/

namespace FrameWork
{

	class Window
	{

	public:

		Window(glm::ivec2 s,std::string t);	                //コンストラクタ
		~Window();					                        //デストラクタ

		operator bool();			//bool 演算子
		void SwapBuffer();	        //ダブルバッファリング
		void ClearTextInput();		//テキスト入力をクリア

		const glm::ivec2 getSize() const;			//サイズを取得
		short int getKeyInput(short int key);		//キー入力

		//イベント処理
		static void Resize_Event(GLFWwindow* const win, int width, int height);				        	//画面サイズ変更
		static void KeyInput_Event(GLFWwindow* win, int key, int scanCode, int action, int mods);	    //キー入力

        float getDeltaTime();       //デルタタイム取得
        GLFWwindow* getContext();   //コンテキストを取得

		FrameWork::Camera getCamera();
	private:


		std::string title;
		glm::ivec2 size;

		GLFWwindow* window;	//ウインドウコンテキスト

		short int keyBoard[500];	//キー入力
		GLbyte key[500];			//キー入力イベント処理

        //デルタタイム
        float deltaTime;
        float prevDeltaTime;


	};

    
    extern std::shared_ptr<FrameWork::Window> currentWindow;  // クライアントコンテキスト

    void SetCurrentWindowContext(std::shared_ptr<FrameWork::Window> win); 	//クライアントコンテキスト　設定
	int getKeyInput(int key);												//キー入力


}
#endif