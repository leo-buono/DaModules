#include "AssignmentChallenge2.h"
Selectable AssignmentChallenge2::m_selectable = Selectable("Player Controller");

void AssignmentChallenge2::CreateTab()
{
	bool temp = false;
	if (ImGui::BeginTabItem(m_selectable.GetName().c_str(), m_selectable.GetSelected()))
	{
		temp = true;
		ImGui::EndTabItem();
	}
	if (temp)
	{
		CreateEditor();
	}
}

void AssignmentChallenge2::CreateEditor()
{
	vec3 position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
	if (ImGui::DragFloat3("Position", &position.x, 0.1f, -500.f, 500.f))
	{
		ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPosition(position);
	}
	Degrees rotation = Transform::ToDegrees(-ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).GetRotationAngleZ());
	if (ImGui::DragFloat("Camera Angle", &rotation, 0.1f, -360.f, 360.f))
	{
		ECS::GetComponent<Camera>(EntityIdentifier::MainCamera()).SetRotationAngleZ(Transform::ToRadians(-rotation));
	}
	if (ImGui::Button("Animation switch", ImVec2(150.f, 20.f)))
	{
		if (ECS::GetComponent<AnimationController>(1).GetActiveAnim() == 0)
		{
			ECS::GetComponent<AnimationController>(1).SetActiveAnim(1);
		}
		else
		{
			ECS::GetComponent<AnimationController>(1).SetActiveAnim(0);
		}
	}
}
