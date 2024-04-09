#pragma once

class CAimBot
{
public:
	void Run( CCSPlayerController* pEntity, C_CSPlayerPawn* pPawn);
private:
	// functions
	void UpdateValues( );

	void __fastcall CalcAngle(Vector& src, Vector& dst, QAngle& angles);

	// variables
	bool m_bShouldRCS = false;
	float m_flRCSAmount = 0.0f;
	float m_flSmoothness = 0.0f;
	float m_flFOV = 0.0f;
};

inline CAimBot g_AimBot;