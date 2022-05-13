#pragma once
/// <summary>
/// 行列
/// </summary>
class Matrix4 {

private:
	Matrix4 Rot4X(const float &radian) const{
		Matrix4 RotX = Matrix4(
			1,		0,			 0,				0,
			0,	 cos(radian),	sin(radian),	0,
			0,	 -sin(radian),	cos(radian),	0,
			0,		0,			 0,				1);
		
		return RotX;
	}

	Matrix4 Rot4Y(const float &radian) const{
		Matrix4 RotY = Matrix4(
			cos(radian),	0,	 -sin(radian),	0,
			0,				1,		0,			0,
			sin(radian),	0,	 cos(radian),	0,
			0,				0,		0,			1);

		return RotY;
	}

	Matrix4 Rot4Z(const float &radian) const{
		Matrix4 RotY = Matrix4(
			cos(radian),  sin(radian),	0,	0,
			-sin(radian), cos(radian),	0,	0,
			0,				0,			1,	0,
			0,				0,			0,	1);
		return RotY;
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



	Matrix4 ScaleMatrix(const Vector3& v) {

		Matrix4 identity = Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		Matrix4 Scale = Matrix4(
			v.x, 0, 0, 0,
			0, v.y, 0, 0,
			0, 0, v.z, 0,
			0, 0, 0, 1);

		return identity *= Scale;
	}
	Matrix4 RotationMatrix(const Vector3 rotation){

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
	
	Matrix4 TranslationMatrix(const Vector3 transform){
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


	// 代入演算子オーバーロード
	Matrix4& operator*=(const Matrix4& m2);
	
};

