#pragma once

namespace HO {
	class GameObject : public Object{
	public:
		GameObject(std::string InName, const Mesh* InMesh): 
		Object(this), 
		mName(InName), 
		mMesh(InMesh)
		{}
		void Update(float InDeltaTime) override;

		inline std::string GetName() const;
		inline const Mesh* GetMesh() const;
		inline Vector3 GetPosition() const;
		inline bool IsMainObject() const;

		inline void SetMainObject();

		bool IsItInView(const GameObject* InObejct, float InFOV) const;
		bool IsItOutOfView(const GameObject* InObejct, float InFOV) const;
		bool IsItOnFront(const GameObject* InObject) const;
		bool IsItOnBehind(const GameObject* InObject) const;

		inline bool IsInFrustrum() const;
		inline void SetInFrustrum();
		inline void GetOutOfFrustrum();

	private:
		std::string mName;
		const Mesh* mMesh;

		bool mbIsMainObject = false;
		bool mbIsInFrustrum = true;
	};
}


const HO::Mesh* HO::GameObject::GetMesh() const {
	return mMesh;
}

HO::Vector3 HO::GameObject::GetPosition() const {
	return mTransformComponent.GetPosition();
}

std::string HO::GameObject::GetName() const{
	return mName;
}

bool HO::GameObject::IsMainObject() const{
	return mbIsMainObject;
}

void HO::GameObject::SetMainObject(){
	mbIsMainObject = true;
}

bool HO::GameObject::IsInFrustrum() const{
	return mbIsInFrustrum;
}
void HO::GameObject::SetInFrustrum(){
	mbIsInFrustrum = true;
}
void HO::GameObject::GetOutOfFrustrum(){
	mbIsInFrustrum = false;
}