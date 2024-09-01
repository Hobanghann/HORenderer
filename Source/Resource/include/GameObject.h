#pragma once

namespace HO {
	class GameObject : public Object{
	public:
		GameObject(std::string InName, Mesh* InMesh) : Object(this), mName(InName), mMesh(InMesh){}
		void Update(float InDeltaTime) override;

		inline Mesh* GetMesh() const;
		inline Vector3 GetPosition() const;

		bool IsItInView(const GameObject* InObejct, float InFOV) const;
		bool IsItOutOfView(const GameObject* InObejct, float InFOV) const;
		bool IsItOnFront(const GameObject* InObject) const;
		bool IsItOnBehind(const GameObject* InObject) const;

	private:
		std::string mName;
		Mesh* mMesh;
	};
}


HO::Mesh* HO::GameObject::GetMesh() const {
	return mMesh;
}

HO::Vector3 HO::GameObject::GetPosition() const {
	return mTransformComponent.GetPosition();
}