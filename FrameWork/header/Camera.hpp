#ifndef ___CAMERA_HPP_
#define ___CAMERA_HPP_

#include <iostream>
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../header/Shader.hpp"

/*#########################################################################
# Cameraクラス

説明
	
###########################################################################*/


namespace FrameWork
{
	class Camera
	{

	public:

		Camera();				//コンストラクタ
		~Camera();				//デストラクタ
		
		// ###################### 設定　関係 ###################### 
		void setPosition(glm::vec3 p);	//座標
		void setLook(glm::vec3 l);		//視線

		// ###################### 取得　関係 ###################### 
		glm::vec3 getPosition();	//座標
		glm::vec3 getLook();		//視線

		// ###################### カメラ行列　関係 ###################### 
		glm::mat4 getViewPerspective();		//透視投影
		glm::mat4 getViewOrthographic();	//正射投影

		void RendererBuffer();	//描画
		void ClearBuffer();		//クリア
	

		GLuint getColorBuffer();
		GLuint getDepthBuffer();

		void setColorBuffer(GLuint frame);
		void setDepthBuffer(GLuint frame);

		void setSkyBox(GLuint tex);	//スカイボックスを設定


	private:


		
		glm::vec3 position;		//座標
		glm::vec3 vecLook;		//向き
		glm::mat4 view;			//ビュー

		GLuint frameBufferFBO;
		GLuint frameBuffer;

		GLuint depthMapFBO;
		GLuint depthMap;

		GLuint rbo;
	
		//フレームバッファ
		GLuint quadVAO;
		GLuint quadVBO;
		
		GLuint colorBufferFBO;
		GLuint colorBuffer;

		std::shared_ptr<FrameWork::Shader> shader;


		float quad[24] =
		{
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
		};

	};
}
#endif