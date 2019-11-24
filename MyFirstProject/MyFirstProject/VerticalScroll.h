#pragma once
#include "Camera.h"
class VerticalScroll
{
public:
	//HorizontalScroll();

	//Make sure that the camera is following the focus
	void Update();

	//getters
	Camera* GetCam() const;
	Transform* GetFocus() const;
	float GetOffset() const;

	//setters
	void SetCam(Camera* cam);
	void SetFocus(Transform* focus);
	void SetOffset(float offset);


private:
	Camera* m_cam = nullptr;
	Transform* m_focus = nullptr;

	float m_offset = 5.f;
};

//Sends Horizontal scrolling camera from Json file
inline void from_json(const nlohmann::json& j, VerticalScroll& horiScroll)
{
	horiScroll.SetOffset(j["Offset"]);
}
//sends horizontal to Json file
inline void to_json(nlohmann::json& j, const VerticalScroll& horiscroll)
{
	j["Offset"] = horiscroll.GetOffset();
}
