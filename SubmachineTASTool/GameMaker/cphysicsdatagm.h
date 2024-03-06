#pragma once

namespace GM {

	struct CPhysicsDataGM {
		float* m_PhysicsVertices;
		bool m_IsPhysicsObject;
		bool m_IsPhysicsSensor;
		bool m_IsPhysicsAwake;
		bool m_IsPhysicsKinematic;
		int m_PhysicsShape;
		int m_PhysicsGroup;
		float m_PhysicsDensity;
		float m_PhysicsRestitution;
		float m_PhysicsLinearDamping;
		float m_PhysicsAngularDamping;
		float m_PhysicsFriction;
		int m_PhysicsVertexCount;
	};

}
