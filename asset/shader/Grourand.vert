
uniform sampler2D diffuse;           // マテリアルのdiffuseカラー
//vec4 diffuse = vec4(1.0);           // マテリアルのdiffuseカラー
uniform vec3 worldLightDirection;   // ワールド座標のディレクショナルライトの向き

layout (location = 0) in vec3 vertexPosition;   //頂点データ
layout (location = 1) in vec2 vertexUV;         //UVデータ
layout (location = 2) in vec3 vertexNormal;     //法線データ

layout (location = 3) out vec4 Color; // ピクセルシェーダ


uniform mat4 uTranslate;	
uniform mat4 uRotate;		
uniform mat4 uScale;		
uniform mat4 uViewProjection;	


void main()
{




    vec4 vertex = vec4(vertexPosition,1.0);
	mat4 model = uTranslate * uRotate * uScale;		
    mat3 mt = mat3(transpose(inverse(model)));
    gl_Position = uViewProjection * vertex;
    vec3 n = normalize(mt * vertexNormal); // 法線のm変換
    float nl = clamp(dot(n, normalize(-worldLightDirection)), 0.0, 1.0); // 法線とライトの内積を算出
    vec3 c = texture(diffuse,vertexUV).rgb * nl; // 最終色を算出
    c = clamp(c, 0.0, 1.0); // 0.0 ~ 1.0に色を収める
    Color = vec4(c, texture(diffuse,vertexUV).a);
}