#pragma once
#include <cmath>
/// <summary>
/// 行列
/// </summary>
class Matrix4 {

private:
	/// <summary>
	/// X軸周りの回転行列
	/// </summary>
	/// <param name="radian">回転角</param>
	/// <returns></returns>
	Matrix4 Rot4X(const float &radian) const{
		Matrix4 RotX = Matrix4(
			1,		0,			 0,				0,
			0,	 cos(radian),	sin(radian),	0,
			0,	 -sin(radian),	cos(radian),	0,
			0,		0,			 0,				1);
		
		return RotX;
	}
	/// <summary>
	/// Y軸周りの回転行列
	/// </summary>
	/// <param name="radian">回転角</param>
	/// <returns>Y軸回転行列</returns>
	Matrix4 Rot4Y(const float &radian) const{
		Matrix4 RotY = Matrix4(
			cos(radian),	0,	 -sin(radian),	0,
			0,				1,		0,			0,
			sin(radian),	0,	 cos(radian),	0,
			0,				0,		0,			1);

		return RotY;
	}
	/// <summary>
	/// Z軸周りの回転行列
	/// </summary>
	/// <param name="radian">回転角</param>
	/// <returns></returns>
	Matrix4 Rot4Z(const float &radian) const{
		Matrix4 RotY = Matrix4(
			cos(radian),  sin(radian),	0,	0,
			-sin(radian), cos(radian),	0,	0,
			0,				0,			1,	0,
			0,				0,			0,	1);
		return RotY;
	}


	Matrix4 Scale(const Vector3& scale){
		Matrix4 Scale = Matrix4(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1);
		return Scale;
	}
	void Identity() {
		Matrix4 identity = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		*this = identity;
	}
public:
	// 行x列
	float m[4][4];


	// コンストラクタ
	Matrix4();

	// 成分を指定しての生成
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);


	/// <summary>
	/// スケーリングの行列を求める
	/// </summary>
	/// <param name="scale">スケール値</param>
	/// <returns></returns>
	Matrix4 ScaleMatrix(const Vector3& scale) {

		Matrix4 identity = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		Matrix4 Scale = Matrix4(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1);

		return identity *= Scale;
	}
	/// <summary>
	/// XYZの回転行列を求める
	/// </summary>
	/// <param name="rotation">回転角</param>
	/// <returns></returns>
	Matrix4 RotationMatrix(const Vector3& rotation){

		Matrix4 matRot = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		matRot *= Rot4Z(rotation.z);
		matRot *= Rot4X(rotation.x);
		matRot *= Rot4Y(rotation.y);
		Matrix4 identity = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		return	identity *= matRot;

	}
	/// <summary>
	/// 平行移動の行列を求める
	/// </summary>
	/// <param name="transform">移動値</param>
	/// <returns></returns>
	Matrix4 TranslationMatrix(const Vector3& transform){
		Matrix4 identity = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		Matrix4 matTrans = Matrix4(
			1,				0,			0,			0,
			0,				1,			0,			0,
			0,				0,			1,			0,
			transform.x, transform.y, transform.z,	1);

		return identity *= matTrans;
	}

	void TransMatrix(const Vector3& transform) {
		*this *= TranslationMatrix(transform);
	}


	
	/// <summary>
	/// スケール、回転、移動の変化を座標に変換する
	/// </summary>
	/// <param name="scale_">スケール値</param>
	/// <param name="rotation_">回転角</param>
	/// <param name="translation_">移動値</param>
	void WorldTransUpdate(const Vector3& scale_ , const Vector3& rotation_, const Vector3& translation_ ) {
		Matrix4 matScale, matRot, matTrans;
		matScale = matScale.ScaleMatrix(scale_);
		matRot = matRot.RotationMatrix(rotation_);
		matTrans = matTrans.TranslationMatrix(translation_);

		*this = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		*this *= matScale;
		*this *= matRot;
		*this *= matTrans;
	}
	// 代入演算子オーバーロード
	Matrix4& operator*=(const Matrix4& m2);
};

