#pragma once

namespace HO {
	class Object {
	public:
		Object(Object *InOwner): mTransformComponent(InOwner), mInputHandler(InOwner) {}
		virtual void Update(float InDeltaTime) = 0;

		inline Transform& GetTransform();
		inline ObjectInputHandler& GetInputHandler();

		virtual ~Object() {}
	protected:
		Transform mTransformComponent;
		ObjectInputHandler mInputHandler;
	};
}

HO::Transform& HO::Object::GetTransform() {
	return mTransformComponent;
}

HO::ObjectInputHandler& HO::Object::GetInputHandler() {
	return mInputHandler;
}
