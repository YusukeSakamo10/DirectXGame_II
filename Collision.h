#pragma once
struct CircleCollider {
	float x, y, z, r;
};


class Collision {
protected:
	CircleCollider collider;
	void UpdateTranslation(Vector3 translation) {
		collider.x = translation.x;
		collider.y = translation.y;
		collider.z = translation.z;
	};
public:
	virtual void OnCollisionEnter() = 0;
	bool Circle3dCollision(const CircleCollider& colliderA, const CircleCollider& colliderB) {
		float x = (colliderA.x - colliderB.x) * (colliderA.x - colliderB.x);
		float y = (colliderA.y - colliderB.y) * (colliderA.y - colliderB.y);
		float z = (colliderA.z - colliderB.z) * (colliderA.z - colliderB.z);
		float r = (colliderA.r + colliderB.r) * (colliderA.r + colliderB.r);
		if (r >= (x + y + z)) {
			return true;
		}
		return false;
	}
	bool Circle3dCollision(const CircleCollider& colliderB) {
		float x = (collider.x - colliderB.x) * (collider.x - colliderB.x);
		float y = (collider.y - colliderB.y) * (collider.y - colliderB.y);
		float z = (collider.z - colliderB.z) * (collider.z - colliderB.z);
		float r = (collider.r + colliderB.r) * (collider.r + colliderB.r);
		if (r >= (x + y + z)) {
			return true;
		}
		return false;
	}
	CircleCollider GetCircleCollider() { return collider; }

};